#include <WiFi.h>
#include "neoMatrix.h"

// déclarations wifi
#define NOMBREWIFI 3
char* ssid[NOMBREWIFI] = {"ruchette", "leMoutz", "iphoneMax"};
char* pass[NOMBREWIFI] = {"2471-3586-0917-2483", "1234-5678", "trckpehtey3m"};

// connect wifi
void wifiConnect(char* ssid, char* pass) {
  WiFi.begin(ssid, pass);
  for (int i=0; i<2; i++) {
    if (WiFi.status() != WL_CONNECTED) delay(1000);
    else break;
  }
}
// ---------------
// wifi and sync time
void wifiOn() {
  // try to connect to wifi
  do {
    for (int i=0; i<NOMBREWIFI; i++) {
      if (WiFi.status() != WL_CONNECTED) {
        wifiLedsOn(i+1); // affiche le no du wifi 
        wifiConnect(ssid[i], pass[i]);
      }
    }
  } while (WiFi.status() != WL_CONNECTED);
    // affichage l'adresse IP sur la wordClock
  textDisplay(WiFi.localIP().toString()); // affiche l'adresse ip
}
void wifiOff() {
  WiFi.disconnect();
  wifiLedsOff();
}
IPAddress getLocalIP() {
    return WiFi.localIP();
}
