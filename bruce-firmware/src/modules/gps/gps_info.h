/**
 * @file gps_info.h
 * @author Vinicius Henrique (https://github.com/viniciushnf)
 * @brief GPS Info
 * @version 0.1
 * @date 2026-05-24
 */

#ifndef __GPS_INFO_H__
#define __GPS_INFO_H__

#include <TinyGPS++.h>
#include <globals.h>

class GPSInfo {
public:
    GPSInfo();
    void setup();
    void loop();

private:
    TinyGPSPlus gps;
    HardwareSerial GPSserial = HardwareSerial(2);
    unsigned long GPStimeWaitSignal = 0;
    unsigned long GPSlastUpdate = 0;

    double latitude = 0.0;
    double longitude = 0.0;
    double altitude = 0.0;
    double speedKmph = 0.0;
    double course = 0.0;
    int satellites = 0;
    double hdop = 0.0;

    int year = 0, month = 0, day = 0;
    int hour = 0, minute = 0, second = 0;

    char gps_time_utc[32] = "No data";
    char gps_time_utc_iso[32] = "No data";

    bool begin_gps(void);
    void end(void);
    void display_banner(void);
    void update_gps_data(void);
    void display_gps_data(void);
    void save_gps_data(void);
    String correct_gps_filename(String name);
    String gps_two_digits(int value);
    int get_days_in_month(int month, int year);
};

#endif
