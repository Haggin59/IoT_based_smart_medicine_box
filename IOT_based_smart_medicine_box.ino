
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLYnOGtuuu"
#define BLYNK_DEVICE_NAME "assssd"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"




#define REPORTING_PERIOD_MS     1000

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

PulseOximeter pox;

//float BPM,SpO2;
int temp;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
    Serial.println("Beat!");
}



void setup()
{
 // pinMode(2, OUTPUT); // Initialise digital pin 2 as an output pin
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter..");
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
       
    }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);  
  pox.setOnBeatDetectedCallback(onBeatDetected);  
 
  delay(100);

  BlynkEdgent.begin();
}

void loop() {


pox.update();
BlynkEdgent.run();
//delay(1000);

  //BPM = pox.getHeartRate();
 // SpO2 = pox.getSpO2();
   temp= analogRead(A0)*0.32;
   Blynk.virtualWrite(V3,temp);
   if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
         
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");
        Blynk.virtualWrite(V1,pox.getSpO2());
        Blynk.virtualWrite(V2,pox.getHeartRate());

        tsLastReport = millis();
    }

 
}
