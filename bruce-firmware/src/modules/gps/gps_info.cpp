/**
 * @file gps_info.cpp
 * @author Vinicius Henrique (https://github.com/viniciushnf)
 * @brief GPS Info
 * @version 0.1
 * @date 2026-05-24
 */

#include "gps_info.h"
#include "core/display.h"
#include "core/mykeyboard.h"
#include "core/sd_functions.h"
#include "core/utils.h"
#include "current_year.h"

#define MAX_WAIT 5000

GPSInfo::GPSInfo() { setup(); }

void GPSInfo::setup() {
    ioExpander.turnPinOnOff(IO_EXP_GPS, HIGH);
    display_banner();
    padprintln("Initializing...");

    GPStimeWaitSignal = millis();
    GPSlastUpdate = 0;

    if (!begin_gps()) return;

    return loop();
}

bool GPSInfo::begin_gps() {
    GPSserial.begin(
        bruceConfigPins.gpsBaudrate, SERIAL_8N1, bruceConfigPins.gps_bus.rx, bruceConfigPins.gps_bus.tx
    );

    int count = 0;
    padprintln("Waiting for GPS data");

    unsigned long start_millis_gps_serial = millis();
    while (GPSserial.available() <= 0) {
        if (millis() - start_millis_gps_serial > 30000) {
            displayError("GPS timeout: 30s", true);
            end();
            return false;
        }
        if (check(EscPress)) {
            end();
            return false;
        }
        displayTextLine("Waiting GPS: " + String(count) + "s");
        count++;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    gpsConnected = true;
    return true;
}

void GPSInfo::end() {
    GPSserial.end();

    returnToMenu = true;
    gpsConnected = false;
}

void GPSInfo::display_banner() {
    drawMainBorderWithTitle("GPS Info");
    tft.setCursor(0, BORDER_PAD_Y + 22);
}

int GPSInfo::get_days_in_month(int month, int year) {
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month < 1 || month > 12) { return 31; }
    if (month == 2) {
        bool leapYear = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
        if (leapYear) { return 29; }
    }
    return daysInMonth[month - 1];
}

void GPSInfo::update_gps_data() {
    while (GPSserial.available() > 0) { gps.encode(GPSserial.read()); }

    if (gps.location.isUpdated()) {
        GPSlastUpdate = millis();
        latitude = gps.location.lat();
        longitude = gps.location.lng();
    }

    if (gps.altitude.isUpdated()) { altitude = gps.altitude.meters(); }
    if (gps.speed.isUpdated()) { speedKmph = gps.speed.kmph(); }
    if (gps.course.isUpdated()) { course = gps.course.deg(); }
    if (gps.satellites.isUpdated()) { satellites = gps.satellites.value(); }
    if (gps.hdop.isUpdated()) { hdop = gps.hdop.hdop(); }
    if (hdop > 99) { hdop = 100; }

    if (gps.date.isValid() && gps.time.isValid() && (gps.date.isUpdated() || gps.time.isUpdated())) {

        day = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();

        snprintf(
            gps_time_utc,
            sizeof(gps_time_utc),
            "%04d-%02d-%02d %02d:%02d:%02d",
            year,
            month,
            day,
            hour,
            minute,
            second
        );
        snprintf(
            gps_time_utc_iso,
            sizeof(gps_time_utc_iso),
            "%04d-%02d-%02dT%02d:%02d:%02dZ",
            year,
            month,
            day,
            hour,
            minute,
            second
        );

        // Convert UTC time from GPS to local time zone
        hour += bruceConfig.tmz;
        while (hour < 0) {
            hour += 24;
            day--;
            if (day < 1) {
                month--;
                if (month < 1) {
                    month = 12;
                    year--;
                }
                day = get_days_in_month(month, year);
            }
        }
        while (hour >= 24) {
            hour -= 24;
            day++;
            if (day > get_days_in_month(month, year)) {
                day = 1;
                month++;
                if (month > 12) {
                    month = 1;
                    year++;
                }
            }
        }
    }
}

void GPSInfo::display_gps_data() {
    if (hdop > 99) {
        padprintln("Sat: " + String(satellites) + "       HDOP: 100", 1);
    } else {
        padprintln("Sat: " + String(satellites) + "       HDOP: " + String(hdop, 1), 1);
    }
    padprintln("Speed: " + String(speedKmph, 1) + "   Alt: " + String(altitude, 0), 1);
    // padprintln(" course: " + String(course));
    padprintln("");

    if (day < 32 && year > 2024 && day > 0 && second < 61) {
        padprintln(
            String(year) + "-" + gps_two_digits(month) + "-" + gps_two_digits(day) + "     " +
                gps_two_digits(hour) + ":" + gps_two_digits(minute) + ":" + gps_two_digits(second),
            1
        );
        padprintln("");
    }

    padprintln("Lat: " + String(latitude, 6), 1);
    padprintln("Lng: " + String(longitude, 6), 1);

    padprintln("");

    if (GPSlastUpdate > 0) {
        if (((millis() - GPSlastUpdate) / 1000) > 1) {
            printFootnote("Last update: " + String((millis() - GPSlastUpdate) / 1000) + "s");
        }
    } else {
        printFootnote("Waiting for updates...");
    }
}

void GPSInfo::loop() {
    returnToMenu = false;
    bool openGpsMenu = false;

    while (1) {
        display_banner();
        if (check(EscPress) || returnToMenu) return end();

        if (GPSserial.available() > 0) {
            update_gps_data();
            display_gps_data();
        } else {
            padprintln(" No signal from GPS module", 1);
            padprintln(" Waiting time: " + String((millis() - GPStimeWaitSignal) / 1000) + " s", 1);
        }

        int tmp = millis();
        while (millis() - tmp < MAX_WAIT && !gps.location.isUpdated() && !openGpsMenu) {
            if (check(EscPress) || returnToMenu) return end();
            if (check(SelPress)) { openGpsMenu = true; }
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }

        if (openGpsMenu) {
            openGpsMenu = false;
            options = {
                {"Save GPS Data", [=]() { save_gps_data(); }},
                {"Back",          [=]() {}                  }
            };
            loopOptions(options);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void GPSInfo::save_gps_data() {
    if (!gps.location.isValid()) {
        displayError("GPS location not valid", true);
        Serial.println("GPS location not valid");
        return;
    }

    String namePlace = keyboard("", 20, "Name of the place");
    String gpsDataFilename = keyboard("", 20, "GPS data file name");

    String namePlace_replace = correct_gps_filename(namePlace);
    namePlace_replace.replace("_", "");
    String gpsDataFilename_replace = correct_gps_filename(gpsDataFilename);
    gpsDataFilename_replace.replace("_", "");
    if (gpsDataFilename_replace == "") {
        if (namePlace_replace == "") {
            String defaultName = String(year) + gps_two_digits(month) + gps_two_digits(day) + "_" +
                                 gps_two_digits(hour) + gps_two_digits(minute) + gps_two_digits(second);
            gpsDataFilename = defaultName;
        } else {
            gpsDataFilename = correct_gps_filename(namePlace);
        }
    }
    if (gpsDataFilename.endsWith(".txt")) { gpsDataFilename.remove(gpsDataFilename.length() - 4); }
    gpsDataFilename = correct_gps_filename(gpsDataFilename);
    gpsDataFilename = gpsDataFilename + ".txt";

    FS *fs;
    if (!getFsStorage(fs)) {
        padprintln("Storage setup error");
        displayError("Storage setup error", true);
        returnToMenu = true;
        return;
    }
    if (!(*fs).exists("/BruceGPS_data")) (*fs).mkdir("/BruceGPS_data");
    bool is_new_file = !(*fs).exists("/BruceGPS_data/" + gpsDataFilename);
    File file = (*fs).open("/BruceGPS_data/" + gpsDataFilename, is_new_file ? FILE_WRITE : FILE_APPEND);
    if (!file) {
        padprintln("Failed to open file for writing");
        returnToMenu = true;
        return;
    }

    String hdop_precision = "";
    if (hdop < 1) {
        hdop_precision = "excellent";
    } else if (hdop < 2) {
        hdop_precision = "good";
    } else if (hdop < 5) {
        hdop_precision = "intermediate";
    } else if (hdop < 10) {
        hdop_precision = "bad";
    } else {
        hdop_precision = "very bad";
    }

    file.println("- - - - GPS data - - - -");
    file.println("");
    if (namePlace_replace != "") { file.println("Place: " + namePlace); }
    file.printf("Date: %04d-%02d-%02d\n", year, month, day);
    file.printf("Time: %02d:%02d:%02d\n", hour, minute, second);
    file.println("");
    file.printf("Satellites: %d\n", satellites);
    file.printf("HDOP: %.2f\n", hdop);
    file.println("GPS accuracy: " + hdop_precision);
    file.printf("Speed: %.2f Km/h\n", speedKmph);
    file.printf("Altitude: %.2f\n", altitude);
    file.printf("Course: %.2f\n", course);
    file.println("");
    file.printf("Latitude: %.6f\n", latitude);
    file.printf("Longitude: %.6f\n", longitude);
    file.println("");
    file.printf("UTC DateTime: %s\n", gps_time_utc);
    file.printf("UTC ISO 8601: %s\n", gps_time_utc_iso);
    file.println("");
    file.println("- - - - - - - - - - - -");
    file.println("Developed by:");
    file.println("> ViniciusHNF");
    file.println("  - https://github.com/viniciushnf/ESP32-S3-Bruce-ST7735-1.8");
    file.println("> Bruce Firmware");
    file.println("  - https://bruce.computer/");
    file.println("- - - - - - - - - - - -");
    file.println("");
    file.println("");
    file.println("");

    file.flush();
    file.close();

    String successful_text_file = "";
    if (is_new_file) {
        successful_text_file = "Saved file: BruceGPS_data/" + gpsDataFilename;
    } else {
        successful_text_file = "File modified: BruceGPS_data/" + gpsDataFilename;
    }
    Serial.println(successful_text_file);
    displaySuccess(successful_text_file, true);
}

String GPSInfo::correct_gps_filename(String name) {
    name.replace(" ", "_");
    name.replace("/", "");
    name.replace("\\", "");
    name.replace(":", "");
    name.replace("*", "");
    name.replace("?", "");
    name.replace("\"", "");
    name.replace("<", "");
    name.replace(">", "");
    name.replace("|", "");

    return name;
}

String GPSInfo::gps_two_digits(int value) {
    if (value < 10) { return "0" + String(value); }
    return String(value);
}
