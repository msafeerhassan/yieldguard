#include <Arduino.h>
#include <HX711.h>

const int HX711_DOUT_PIN = 4;
const int HX711_SCK_PIN = 5;

HX711 scale;

void printMenu() {
    Serial.println();
    Serial.println("t = Tare, r = raw Reading, c = calibrate, w = weight, ? = Menu");
}

void setup() {
    Serial.begin(115200);
    unsigned long start = millis();
    while (!Serial && millis() - start < 3000)
    {
        delay(10);
    }

    scale.begin(HX711_DOUT_PIN, HX711_SCK_PIN);
    
    if (scale.wait_ready_timeout(2000)) {
        Serial.println("HX711 Found.");
    }
    else {
        Serial.println("HX711 Missing - Please check wiring");
    }

    scale.set_scale();
    scale.set_offset(0);
    printMenu();

    Serial.println("Remove all weight and then sent 't' to tare.");
}

void tare() {
    scale.tare(20);
    Serial.println("Tare Complete. Offset = ");
    Serial.println(scale.get_offset());
}

void showRaw() {
    if (!scale.wait_ready_timeout(1000)) {
        Serial.println("HX711 not ready");
        return ;
    }
    Serial.println("Raw Reading: ");
    Serial.println(scale.get_value(10));
}

void calibrate() {
    Serial.println("Place know weight and then type it in grams and hit Enter: ");

    while (!Serial.available()) {
        delay(50);
    }

    String input = Serial.readStringUntil('\n');
    input.trim();

    float knowWeight = input.toFloat();

    if (knowWeight <= 0) {
        Serial.println("Invalid Weight.");
        return ;
    }

    long rawValue = scale.get_value(20);

    if (rawValue == 0) {
        Serial.println("Raw Reading was 0 - check circuit please");
        return ;
    }

    float calibrationFactor = (float)rawValue / knowWeight;

    Serial.print("Load Cell Offset = ");
    Serial.println(scale.get_offset());
    Serial.print("Load Cell Factor = ");
    Serial.println(calibrationFactor, 4);

    scale.set_scale(calibrationFactor);
    Serial.println("Send 'w' to verify");
}

void showWeight() {
    if (!scale.wait_ready_timeout(1000)) {
        Serial.println("HX711 not ready");
        return ;
    }

    Serial.print("Weight: ");
    Serial.print(scale.get_units(10), 1);
    Serial.println(" g");
}


void loop() {
    if(Serial.available()) {
        char c = Serial.read();

        switch (c)
        {
            case 't' : case 'T' : tare(); break;
            case 'r' : case 'R' : showRaw(); break;
            case 'c' : case 'C' : calibrate(); break;
            case 'w' : case 'W' : showWeight(); break;
            case '?' : printMenu(); break;
        }
    }

    delay(20);
}