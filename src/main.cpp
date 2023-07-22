#include <M5StickCPlus.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// import headers wordclock
#include "timeSync.h"
#include "webServerWC.h"
#include "wordClock.h"
#include "wifiConnect.h"

// ---------------
// programme principal
// ---------------
void setup() {
  // initialisation du M5StrickC-Plus
  M5.begin();
  // initialisation de la wordClock
  wordClockBegin();
  // activer le wifi
  wifiOn();
  // synchronise l'heure internet
  setInternetTime();
  // activer le serveur web
  serverWebBegin();
}
void loop() {
  M5.update();
  serverWebHandleClient();
  timeSync();
  wordClockDisplay();
  delay(1000);  
}