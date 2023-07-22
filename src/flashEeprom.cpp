#include <EEPROM.h>

// define the number of bytes you want to access
#define EEPROM_SIZE 4
#define ADDRESS_BRIGHTNESSNORMAL 0
#define ADDRESS_BRIGHTNESSREDUCED 1
#define ADDRESS_COLOR 2

void eepromBegin() {
    EEPROM.begin(EEPROM_SIZE);
}

uint8_t readBrightnessNormal() {
    uint8_t brightnessNormal;
    EEPROM.get(ADDRESS_BRIGHTNESSNORMAL, brightnessNormal);
    return brightnessNormal;
}
uint8_t readBrightnessReduced() {
    uint8_t brightnessReduced;
    EEPROM.get(ADDRESS_BRIGHTNESSREDUCED, brightnessReduced);
    return brightnessReduced;
}
void writeBrightnessNormal(uint8_t brightnessNormal) {
    // seulement des mises à jour pour limiter le nombre d'écritures
    if (readBrightnessNormal() != brightnessNormal) {
        EEPROM.put(ADDRESS_BRIGHTNESSNORMAL, brightnessNormal);
        EEPROM.commit();
    }
}
void writeBrightnessReduced(uint8_t brightnessReduced) {
    if (readBrightnessReduced() != brightnessReduced) {
        EEPROM.put(ADDRESS_BRIGHTNESSREDUCED, brightnessReduced);
        EEPROM.commit();
    }
}

uint16_t readColor() {
    uint16_t c;
    EEPROM.get(ADDRESS_COLOR, c);
    return c;
}
void writeColor(uint16_t color) {
    if (readColor() != color) {
        EEPROM.put(ADDRESS_COLOR, color);
        EEPROM.commit();
    }
}
