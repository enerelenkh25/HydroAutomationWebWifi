#ifndef VEGETABLES_H
#define VEGETABLES_H

#include <Arduino.h>

// Seed and Phase Tables
struct SeedData {
    const char* name;
    float phLow;
    float phHigh;
    int lightDuration;
};

const SeedData seedTable[] = {
    {"basil", 5.5, 6.5, 16},
    {"tomato", 5.5, 6.5, 18},
    {"lettuce", 5.5, 6.0, 14},
    {"beans", 6.0, 7.0, 16},
    {"beets", 6.0, 6.5, 14},
    {"celery", 6.0, 7.0, 18},
    {"chard", 6.0, 6.8, 14},
    {"cilantro", 6.5, 7.5, 14},
    {"cucumbers", 5.5, 6.5, 18},
    {"kale", 6.0, 7.5, 16},
    {"mint", 6.0, 7.0, 16},
    {"peppers", 5.5, 6.0, 18},
    {"radishes", 5.5, 6.8, 16},
    {"spinach", 6.0, 7.0, 16},
    {"springOnions", 6.0, 7.0, 14}
};

struct PhaseData {
    const char* name;
    int tempLow;
    int tempHigh;
    int humidityLow;
    int humidityHigh;
};

const PhaseData phaseTable[] = {
    {"Germination", 22, 24, 80, 90},
    {"Seeding", 18, 22, 60, 70},
    {"Vegetative Growth", 24, 28, 60, 70},
    {"Flowering", 18, 24, 50, 60},
    {"Pollination", 20, 25, 40, 50},
    {"Fruit", 18, 24, 40, 50}
};

struct VegetableData {
    const char* seed;
    const char* phase;
    float phLow;
    float phHigh;
    int tempLow;
    int tempHigh;
    int humidityLow;
    int humidityHigh;
    int lightDuration;
};

VegetableData currentVegetable;

void vegetablesInit() {
    currentVegetable = {"tomato", "Vegetative Growth", 5.5, 6.5, 24, 28, 60, 70, 18};
}

void manageVegetables(const char* seed, const char* phase) {
    for (int i = 0; i < sizeof(seedTable) / sizeof(seedTable[0]); i++) {
        if (strcmp(seedTable[i].name, seed) == 0) {
            currentVegetable.seed = seedTable[i].name;
            currentVegetable.phLow = seedTable[i].phLow;
            currentVegetable.phHigh = seedTable[i].phHigh;
            currentVegetable.lightDuration = seedTable[i].lightDuration;
            break;
        }
    }

    for (int i = 0; i < sizeof(phaseTable) / sizeof(phaseTable[0]); i++) {
        if (strcmp(phaseTable[i].name, phase) == 0) {
            currentVegetable.phase = phaseTable[i].name;
            currentVegetable.tempLow = phaseTable[i].tempLow;
            currentVegetable.tempHigh = phaseTable[i].tempHigh;
            currentVegetable.humidityLow = phaseTable[i].humidityLow;
            currentVegetable.humidityHigh = phaseTable[i].humidityHigh;
            break;
        }
    }
}

#endif
