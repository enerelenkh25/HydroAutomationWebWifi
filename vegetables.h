// vegetables.h
#ifndef VEGETABLES_H
#define VEGETABLES_H

struct Vegetable {
    const char* name;
    float phLow;
    float phHigh;
    int harvestingTimeWeeks;
    int lightDurationHours;
    const char* suitableLightColor;
    int wavelengthLow;
    int wavelengthHigh;
};

const Vegetable celery = {"Celery", 5.8, 6.2, 10, 14, "Balanced Spectrum (mix of blue and red)", 400, 700};
const Vegetable spinach = {"Spinach", 6.0, 7.0, 6, 12, "Balanced Spectrum (mix of blue and red)", 400, 700};
const Vegetable springOnions = {"Spring Onions", 6.0, 7.0, 10, 12, "Balanced Spectrum (mix of blue and red)", 400, 700};
const Vegetable tomatoes = {"Tomatoes", 5.5, 6.5, 12, 14, "Balanced Spectrum (mix of blue and red)", 580, 700};
const Vegetable mint = {"Mint", 6.0, 7.0, 0, 12, "Vibrant Blue (aromatic leaves)", 400, 490};
const Vegetable cilantro = {"Cilantro", 6.0, 7.0, 0, 12, "Blue light (leafy growth)", 400, 490};
const Vegetable kale = {"Kale", 6.0, 7.0, 8, 12, "Blue light (leafy growth)", 400, 490};
const Vegetable lettuce = {"Lettuce", 5.5, 6.5, 6, 12, "Blue light (leafy growth)", 400, 490};
const Vegetable basil = {"Basil", 5.5, 6.5, 0, 12, "Blue light (vegetative growth)", 400, 490};
const Vegetable beans = {"Beans", 6.0, 7.0, 8, 12, "Warm reddish (flowering and fruiting)", 580, 700};
const Vegetable chard = {"Chard", 6.0, 7.0, 8, 12, "Warm reddish (flowering and fruiting)", 400, 700};
const Vegetable peppers = {"Peppers", 5.5, 6.5, 12, 14, "Combination of blue and red (fruit formation)", 580, 700};
const Vegetable cucumbers = {"Cucumbers", 5.8, 6.2, 8, 14, "Combination of blue and red (fruit formation)", 580, 700};
const Vegetable beets = {"Beets", 6.0, 7.0, 10, 12, "Red light (root development)", 580, 700};
const Vegetable radishes = {"Radishes", 5.5, 6.5, 4, 12, "Red light (root development)", 400, 700};

// Phases
struct Phase {
    const char* name;
    int humidityLow;
    int humidityHigh;
    int daylightTempLow;
    int daylightTempHigh;
    int nightTempLow;
    int nightTempHigh;
    int waterTempLow;
    int waterTempHigh;
};

const Phase germination = {"Germination", 65, 70, 20, 30, 15, 20, 20, 25};
const Phase seeding = {"Seeding", 60, 70, 18, 24, 15, 20, 18, 22};
const Phase vegetativeGrowth = {"Vegetative Growth", 50, 70, 20, 25, 18, 22, 20, 24};
const Phase flowering = {"Flowering", 40, 50, 22, 28, 18, 22, 22, 26};
const Phase pollination = {"Pollination", 45, 55, 25, 30, 20, 25, 25, 28};
const Phase fruit = {"Fruit", 45, 55, 20, 25, 18, 22, 20, 25};

// Current Settings
Vegetable currentVegetable = celery;
Phase currentPhase = vegetativeGrowth;

void selectVegetable(const Vegetable& vegetable) {
    currentVegetable = vegetable;
}

void selectPhase(const Phase& phase) {
    currentPhase = phase;
}

#endif
