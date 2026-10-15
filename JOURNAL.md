---
title: "YieldGuard"
github: "https://github.com/msafeerhassan/yieldguard"
description: "An ESP32 Based Project for automatically logging Milk Weight to prevent fraud - For Real World Use."
created_at: "2026-10-01"
total_time: "7h 18m"
---

# October 1, 2026: Finalized the Project Workflow - Imported from Macondo
<!-- fabricate:entry 46 -->

IMPORTED FROM MACONDO

Last night, I got the idea of the project. I started research online of what possibly I could do - I found that we can have weight sensors that can be used to measure the weight of milk but one thing that was confusing me was the workflow. I constantly thought about it and decided how would it work. Basically the load cell would be mounted right below the milk jar to measure the weight. It will let milk accumulate and measure the weight as it does. I will add a variable in code of the constant mass means the original mass of Jar when it's empty. Then when the milkman lifts it up, he the mass will instantly drop to ZERO. Then it will wait for 45 seconds to ensure the accuracy that actually milk is being taken by milkman. Then the ESP32 that will be connected to the WiFi will send a WhatsApp message of the total milk collected in that session and will automatically reset for the next session. It might need a bit more fine-tuning but atleast the rough idea is OK to proceed ahead. Then I did research on the components we need. I got to know it will be Tier 4 project capped at $50 maximum funding so I was determined to make it as cheapest as possible. I decided to use ESP32 DevKitC V4 Wroom32D because that was the cheapest and most feasible option available. I chose a 100KG Load cell because average weight of one session is somewhat 60-80kg so it was the best and most scalable option available. I have decided to use HX711 Module for amplifying the signal from load cell. As it will be used in real world, we have to maintain constant permanent power source. For that, I have decided to plug it directly into the nearest switch board using a Phone Charger of 5V 2A with a Micro-USB Cable. I initially wanted to create a custom case for it but now I have decided to use a pre-made IP65 Waterproof Plastic Junction Box because its even cheaper than the shipping of Custom 3D Printed Case. Atlast, we will base it whole on a PCB and PCB will be ordered by PCBWay because it provides the cheapest option. Here's the BoM I have made - it's neither complete nor finalized and can have some changes but is enough to give an idea:

![](https://fabricate.hackclub-assets.com/2891bb6b916e4599416ebdff9e96ea6f210f688abb82edac57bcc9a57a1a15db/image.png)

I wanted to order most of components locally using epro.pk but the website is down right now so I have chose the items on AliExpress and will shift to ePro once the website is up - it will help avoid those taxes.

**Total time spent: 2h**

# October 1, 2026 (entry 2): Designed the Schematic Diagram - IMPORTED FROM MACONDO
<!-- fabricate:entry 47 -->

So basically as I mentioned in previous journal that the BoM isn't complete and finalized yet - I meant this in terms of the sourcing of the components. Unfortunately it isn't still finalized because the website I am looking to source locally from is currently down. Therefore I decided to not waste time and head to schematic diagram design because components are finalized regardless of their sourcing site. Firstly, I knew that the symbol and footprint of HX711 and ESP32 DevKitC V4 won't be available in the KiCad so I went straight to the Google, searched for these and found suitable ones. I loaded them in KiCad. One thing I noticed was that the symbol/footprint of the HX711 didn't resembled the module I was trying to purchase so on further research I came to know that in some modules, one pin is removed because that's not neccessary - the pin is the one which connects to the yellow wire of load cell and is primarily for stability etc purposes. Anyways, I started schematic diagram. I went online and searched for the wiring and checked some images and quickly understood how they are supposed to be wired - one confusion that came was with the symbol of HX711 - it had B+ and B- pins that I didn't understood what are for but I came to know they are supposed to be left unused so I did that. I was first trying to wire using the simple wire tool in KiCad but remembered to keep the design clean so I used those net labels. After this, I resolved the issues that DRC was giving. At last, I attached text above each component for ease of understanding. I also assigned the appropriate footprints to each of the symbol. Now I am fully ready to make PCB.

![](https://fabricate.hackclub-assets.com/2d4cd5472c69df50054a6f3fd5521a97b119ef7d817a48e15bd995ede7f8c951/image.png)

**Total time spent: 42m**

# October 1, 2026 (entry 3): Designed the whole PCB - IMPORTED FROM MACONDO
<!-- fabricate:entry 48 -->

So as I mentioned in previous journal that schematic diagram is ready to be converted to PCB so I did the same. I imported the footprints in KiCad and then estimated the size of PCB - at first, I made it about 70mm by 65mm but I found that there is quite much space still left so I decided to shorten it. I tried to place components as close as possible. Doing this, I came to know that 60mm by 55mm would work perfectly so I did the same - the PCB shape is rectangular. Then I started the routing - the routing wasn't complex. I connected the route of socket for 100kg load cell on front copper plane and the rest on the back copper plane. Then I wrote some text like for designing purposes and for assembling purpose as well. As I said it will be actually used at our farm so I also added a logo of our cattle farm - in fact, this step took quite long time than expected because when i exported the image onto clipboard using kicad image tool, it pasted it on front silkscreen whereas it was supposed to be on the back one because on front, components will place so logo will hide. I tried converting it within the PCB editor but failed. I searched online and found that I have to edit it as footprint so I did this. I shifted all elements of it on back silkscreen and reimported it in pcb editor to place on PCB board but unfortunately the mirroring wasn't correct - idk if that's what we say to it... like it was unreadable - i tried mirroring it in pcb editor but it didn't worked out so I again went to footprint editor and did this individually on each element and then realigned elements to form the logo as they were misplaced when mirroring. At last, i imporrted it in pcb editor and it worked. I aligned the texts perfectly and rounded the corners and then exported it using that fabrication toolkit to the gerbers and production files. Since its going to be PCB instead of PCBA so I deleted the production files keeping only gerber files. PCB is now ready. Next I will decide to whether buy a 3d case or make one and then 3d print it. oh wait - i realised i have placed the footprint of the connector in wrong dimension - lemme fix it right now. I have fixed this too. One thing I didn't said earlier is that I am constantly commiting all the changes to the github repo of this project too. I think now PCB is alright and finished.

![](https://fabricate.hackclub-assets.com/97658c3ee5a060595fa99ba6696a24714ea208e4e8c8544ffed6447a910390f2/image.png)

**Total time spent: 42m**

# October 1, 2026 (entry 4): Update PCB/Schematic & Completed BoM - IMPORTED FROM MACONDO
<!-- fabricate:entry 49 -->

So basically I went online to check for the sourcing like of the ESP32 DevKitC V4 but during that, I found an ultra compact ESP32 named ESP32 C3 SuperMini. I found this to be perfect for my project as it has only 16 pins and am gonna use at most 4-5 pins. It is comparitively cheaper and small so will use less resources and space and the case can be even smaller. So I went online to find its symbol and footprint. I found its symbol but had to make footprint by myself using the dimensions mentioned on google - i hope it works. Moreover, I have finalized the BoM including the sourcing link - the estimated cost of the whole project is $40. I am going to use PCBWay for fabrication because it gives PCB at minimum cost of $15 while JLCPCB offers at $30 minimum so a quite great difference. Anyways, I also modified the PCB to fit the changed component and now its quite small about 50mm by 40mm. I have to do routing now. The BoM and Schematic are finalized. I also have mentioned sourcing links of other products in BoM and that's final I guess.

![](https://fabricate.hackclub-assets.com/c3aeb325c6e5236a8736d29aaf8587a06c36d556f508059397c4e848eeaf0383/image.png)

**Total time spent: 54m**

# October 1, 2026 (entry 5): Routed PCB and did 3D Design and BoM Completion
<!-- fabricate:entry 50 -->

So basically I have routed the components on PCB:

![](https://fabricate.hackclub-assets.com/5d7dc86978958835c3e11cc7c12a9d012e7720e05ec9cfd742aaba716a3d7a00/image.png)

![](https://fabricate.hackclub-assets.com/4851134d3c705023d78c20a6ab871a9f00f85764be8f8f8322faeb5b470a5774/image.png)

Then I went online to decide whether I should make a custom 3D Case or use the pre-built one. I got the lowest quote of $2.5 from a guy in Printing Legion from Pakistan but upon searching online, I found epro.pk offered a bigger case and that too for just about $0.6 - like its quite cheap and usable as it is IP65 Rated waterproof. So I added it in BoM and the BoM is done now. Then I went online to find the 3D Model of the case but I failed to do so I turned on Fusion360, created a simple case that doesn't resemble the one on epro exactly but is somewhat a basic sketch of it so I can use it. Then I assembled all components on 3D design of PCB and placed PCB inside that case and it fitted well. I think the project is ready to be shipped except incomplete readme and no firmware that I will work on next.

![](https://fabricate.hackclub-assets.com/54cac102b6049d8392d4cafbaec64b025447cc05a502626b3fdae95858e602da/image.png)

![](https://fabricate.hackclub-assets.com/b56709774da2593237ec04b8029505f74e18f707aff6de508a6a513cc8feb26b/image.png)

![](https://fabricate.hackclub-assets.com/83e9660f399b8296a3de05db970add2534f79ac69fda1ac39f0a4a1ad4fbf213/image.png)

**Total time spent: 1h 6m**

# October 1, 2026 (entry 6): Coded Firmware - Tracked by Hackatime
<!-- fabricate:entry 51 -->

I can't find any option to Link Hackatime so am directly making a journal that I also coded firmware which took 1.6 hours.

![](https://fabricate.hackclub-assets.com/6c552cd0542296c07a5ef359ad2ab660073b7184adbbcd1ede7ba1cc7c82dba9/image.png)

Macondo Project Link: https://macondo.hackclub.com/projects/6487

**Total time spent: 1h 36m**

# October 1, 2026 (entry 7): Updated BoM
<!-- fabricate:entry 52 -->

So this project is basically imported from Macondo since they are no longer accepting such projects. Here is the link: https://macondo.hackclub.com/projects/6487

So basically in macondo, I planned to only make design and get gold for purchasing items but now in fabricate, I am looking to make its real build as well so I want funding also. For that purpose, I have fine-tuned the BoM.

![](https://fabricate.hackclub-assets.com/ecebfde4e549e8d52313f91d6eee3b6a2f980e369e217dc9a07fde0c70b2dacd/image.png)

**Total time spent: 18m**
