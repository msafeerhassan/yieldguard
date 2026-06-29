#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>
#include <HX711.h>

#define WIFI_SSID "NetworkName"
#define WIFI_PASSWORD "NetworkPassword"
#define WHATSAPP_NUMBER "WhatsAppNumberForAlerts"
#define CALLMEBOT_APIKEY "APIKEY"

#define HX711_DOUT_PIN 4
#define HX711_SCK_PIN 5

#define LOADCELL_OFFSET 50682624L
#define LOADCELL_FACTOR 5895.6550f

#define STABILITY_TOLERANCE 100.0f
#define STABILITY_DURATION (3UL * 60UL * 1000UL)
#define MIN_WEIGHT_TO_TRACK 100.0f
#define INTERVAL_MS 1000UL

HX711 scale;

float refWeight = 0.0f;
unsigned long stableSince = 0;
bool isTrackingStability = false;
bool alertSent = false;
unsigned long lastSample = 0;

void connectWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED) {
        delay(300);
        if (millis() - start > 20000) {
            WiFi.disconnect();
            delay(500);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        start = millis();
        }
    }

    Serial.print("WiFi Connected. IP: ");
    Serial.println(WiFi.localIP());
}

void ensureWifi() {
    if (WiFi.status() != WL_CONNECTED) connectWifi();
}

bool sendWhatsappMsg(const String &message) {
    ensureWifi();
    String url = "https://api.callmebot.com/whatsapp.php?phone=" + String(WHATSAPP_NUMBER) +
               "&apikey=" + String(CALLMEBOT_APIKEY) + "&text=" + urlEncode(message);
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.GET();
    bool success = (httpResponseCode == 200);
    Serial.println(success ? "Whatsapp Message Sent." : "Failed to send message");
    http.end();
    return success;
}

void setupLoadCell() {
    scale.begin(HX711_DOUT_PIN, HX711_SCK_PIN);
    scale.wait_ready_timeout(3000);
    scale.set_offset(LOADCELL_OFFSET);
    scale.set_scale(LOADCELL_FACTOR);
}

float readWeight() {
    if (!scale.wait_ready_timeout(500)) return NAN;
    return scale.get_units(5);
}

void resetStabilityTracking(float newRef) {
    refWeight = newRef;
    stableSince = millis();
    isTrackingStability = true;
    alertSent = false;
}

void clearStabilityTracking() {
    isTrackingStability = false;
    alertSent = false;
}

void handleNewReading(float weight) {
    if (weight < MIN_WEIGHT_TO_TRACK) {
        clearStabilityTracking();
        return ;
    }

    if (!isTrackingStability) {
        resetStabilityTracking(weight);
        return ;
    }

    float delta = fabs(weight - refWeight);

    if (delta <= STABILITY_TOLERANCE) {
        unsigned long stableFor = millis() - stableSince;

        if (!alertSent && stableFor >= STABILITY_DURATION) {
            char msg[160];
            snprintf(msg, sizeof(msg), "YeildGuard Alert: Weight Stabilized at %.1f g for %lu minutes", refWeight, (unsigned long)(STABILITY_DURATION / 60000UL));
            Serial.println(msg);
            sendWhatsappMsg(String(msg));
            alertSent = true;
        }
    }
    else {
        resetStabilityTracking(weight);
    }
}

void setup() {
    Serial.begin(115200);
    unsigned long start = millis();
    while (!Serial && millis() - start < 3000) delay(10);

    setupLoadCell();
    connectWifi();
}


void loop() {
    unsigned long now = millis();
    if (now - lastSample >= INTERVAL_MS) {
        lastSample = now;
        float weight = readWeight();
        if (isnan(weight)) return;

        Serial.print("Weight: ");
        Serial.println(weight, 1);

        handleNewReading(weight);
    }
}