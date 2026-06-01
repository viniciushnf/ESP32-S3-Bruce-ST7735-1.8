/**
 * @file quickAccess.cpp
 * @author Vinicius Henrique (https://github.com/viniciushnf)
 * @brief Quick Access
 * @version 0.1
 * @date 2026-05-21
 */

#include "quickAccess.h"
#include "../modules/NRF24/nrf_jammer.h"
#include "core/display.h"
#include "core/sd_functions.h"
#include "core/utils.h"
#include "core/wifi/webInterface.h"
#include "core/wifi/wifi_common.h"
#include "modules/others/battery_information.h"
#include <Arduino.h>

void quickAccess() {
    Serial.println("Open Quick Access");
    menuOptionLabel = "Quick Access";
    options.clear();
    if (WiFi.status() != WL_CONNECTED) {
        options = {
            {"Connect to Wifi", lambdaHelper(wifiConnectMenu, WIFI_STA)},
            {"Start WiFi AP", [=]() {
                 wifiConnectMenu(WIFI_AP);
                 displayInfo("pwd: " + bruceConfig.wifiAp.pwd, true);
             }},
        };
    }
    if (setupSdCard()) options.push_back({"SD Card", [=]() { loopSD(SD); }});
    options.push_back({"WebUI", loopOptionsWebUi});
    options.push_back({"NRF Jammer", nrf_jammer});
    options.push_back({"Battery Info", [=]() { Battery_information::loop(); }});

    addOptionToMainMenu();

    // loopOptions(options, MENU_TYPE_SUBMENU, "Quick Access");
    loopOptions(options);
}
