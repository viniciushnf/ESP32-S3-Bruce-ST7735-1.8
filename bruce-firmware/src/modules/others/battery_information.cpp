/**
 * @file battery_information.cpp
 * @author Vinicius Henrique (https://github.com/viniciushnf)
 * @brief Battery Information
 * @version 0.1
 * @date 2026-05-20
 */

#include "battery_information.h"
#include "core/display.h"
#include <Arduino.h>

#define MAX_WAIT 10000

int Battery_information::ADC_pin = 10;             // Battery voltage divider on GPIO 10
float Battery_information::minimum_voltage = 3.10; // Minimum voltage. When it shows 0%
float Battery_information::maximum_voltage = 4.16; // Battery charged. When it shows 100%

int Battery_information::ADC_resolution = 4095;
float Battery_information::voltage_reference = 3.3;
int Battery_information::percentage = 0;
unsigned long Battery_information::last_update = 0;
int Battery_information::update_delay = 15000;

Battery_information::Battery_information() {
    analogReadResolution(12);

    // Important for ESP32-S3
    analogSetPinAttenuation(ADC_pin, ADC_11db);

    Battery_information::loop();
}

void Battery_information::loop() {

    returnToMenu = false;
    bool while_loop = true;

    while (while_loop) {

        if (check(EscPress) || returnToMenu) { while_loop = false; }

        drawMainBorderWithTitle("Battery Info");

        float adc_raw = Battery_information::getADC(512, 200);

        // Converts ADC to actual voltage on the pin.
        float adc_voltage =
            (adc_raw * Battery_information::voltage_reference) / (float)Battery_information::ADC_resolution;

        /*
            Divider:
            R1 = 100k
            R2 = 100k
            Ideal relationship:
            battery = adc * 2
            Measured calibration factor:
            4.011 / 3.780 = 1.0611
            Final factor:
            2.0 * 1.0611 = 2.122
        */

        float battery_voltage = adc_voltage * 2.122;

        int battery_percentage = constrain(
            ((battery_voltage - Battery_information::minimum_voltage) /
             (Battery_information::maximum_voltage - Battery_information::minimum_voltage)) *
                100.0,
            0,
            100
        );

        Battery_information::percentage = battery_percentage;
        Battery_information::last_update = millis();

        tft.setTextSize(FP);

        padprintln("");

        padprintln("Battery Percentage: " + String(battery_percentage));
        padprintln("");

        padprintln("Battery Voltage: " + String(battery_voltage, 3));
        padprintln("");

        padprintln("ADC Voltage: " + String(adc_voltage, 3));
        padprintln("");

        padprintln("ADC Value: " + String(adc_raw));

        int tmp = millis();

        while (millis() - tmp < MAX_WAIT && while_loop) {

            if (check(EscPress) || returnToMenu) { while_loop = false; }
        }
    }
}

float Battery_information::getADC(int ADCsamples, int sampleDelay) {
    long sample_counter = 0;

    // Discard initial readings.
    for (int i = 0; i < 10; i++) {
        analogRead(Battery_information::ADC_pin);
        delayMicroseconds(50);
    }
    for (int i_sample = 0; i_sample < ADCsamples; i_sample++) {
        sample_counter += analogRead(Battery_information::ADC_pin);
        delayMicroseconds(sampleDelay);
    }
    return (float)sample_counter / ADCsamples;
}

float Battery_information::getADCvoltage() {
    float ADCreading = Battery_information::getADC(64, 100);
    return (ADCreading * Battery_information::voltage_reference) / (float)Battery_information::ADC_resolution;
}

float Battery_information::batteryVoltage() { return Battery_information::getADCvoltage() * 2.122; }

int Battery_information::getBatteryPercentage() {

    if ((millis() - Battery_information::last_update) > Battery_information::update_delay ||
        Battery_information::last_update == 0) {

        float adc_raw = Battery_information::getADC(512, 200);

        float adc_voltage =
            (adc_raw * Battery_information::voltage_reference) / (float)Battery_information::ADC_resolution;

        float battery_voltage = adc_voltage * 2.122;

        int battery_percentage = constrain(
            ((battery_voltage - Battery_information::minimum_voltage) /
             (Battery_information::maximum_voltage - Battery_information::minimum_voltage)) *
                100.0,
            0,
            100
        );

        Battery_information::percentage = battery_percentage;
        Battery_information::last_update = millis();
    }

    return Battery_information::percentage;
}
