/**
 * @file battery_information.h
 * @author Vinicius Henrique (https://github.com/viniciushnf)
 * @brief Battery Information
 * @version 0.1
 * @date 2026-05-20
 */

#ifndef BATTERY_INFORMATION_H
#define BATTERY_INFORMATION_H

#include <Arduino.h>
#include <globals.h>

class Battery_information {
public:
    Battery_information();
    static void loop();

    static int ADC_pin;
    static int ADC_resolution;
    static float voltage_reference;

    static float minimum_voltage; // 0% battery
    static float maximum_voltage; // 100% battery
    static int percentage;
    static unsigned long last_update;
    static int update_delay;

    static float getADC(int ADCsamples = 32, int sampleDelay = 50);
    static float getADCvoltage();
    static float batteryVoltage();
    static int getBatteryPercentage();
};

#endif
