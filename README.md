<p align="center">
  <img src="https://raw.githubusercontent.com/viniciushnf/ESP32-S3-Bruce-ST7735-1.8/refs/heads/main/images/banner-github.png" alt="ESP32-S3 Bruce Firmware Banner" width="100%">
</p>

# ESP32-S3 + Bruce Firmware | 1.8" ST7735 Display, GPS, NFC, NRF24L01, IR & Joystick

This project combines multiple modules into a single portable Bruce Firmware device, including a TFT display, GPS navigation, NFC communication, NRF24L01 RF communication, infrared functionality, joystick control, SD card storage, and battery monitoring.

---

## YouTube Video

<p align="center">
  <a href="https://www.youtube.com/watch?v=Ke6ndQEae68">
    <img src="https://img.youtube.com/vi/Ke6ndQEae68/maxresdefault.jpg" alt="YouTube Video" width="800">
  </a>
</p>

**Video:**
https://www.youtube.com/watch?v=Ke6ndQEae68

---

## Hardware Used

* ESP32-S3
* 1.8" ST7735 TFT Display with SD Card Reader
* NEO-6M GPS Module
* PN532 NFC Module
* NRF24L01 with Adapter
* Infrared Transmitter and Receiver
* Joystick
* 18650 Li-ion Battery
* TP4056 + MT3608 Battery Charging and 5V Regulation Module

---

## Other Components Used

* Wires
* 2× Perfboards (26 × 31 holes / 70 × 90 mm)
* Nylon Screws and Spacers
* On/Off Switch
* 18650 Battery Holder
* Male and Female Pin Headers
* 1× 100 Ω Resistor
* 1× 220 Ω Resistor
* 1× 1 kΩ Resistor
* 2× 100 kΩ Resistors
* 2× 100 nF Ceramic Capacitors
* 1× 2N2222 Transistor

---

## Wiring Diagram and Documentation

The module pinout can be found in: wiring-diagram/pinout.txt

The wiring diagram can be found in: wiring-diagram/wiring-diagram.png

Hardware assembly photos can be found in: images/

The installation guide can be found in: installation-guide.txt

---

## Bruce Firmware Modifications

* Several Bruce Firmware files were modified to adapt the interface to the 1.8" ST7735 display.
* Additional features and improvements were added to the firmware.
* The installation guide explaining how to upload the modified firmware can be found in: installation-guide.txt

---

## Battery Life

* During testing, the device achieved more than **8 hours of continuous operation** using a **3000 mAh 18650 Li-ion battery**.
* Actual battery life may vary depending on several factors, including battery capacity and quality, display brightness, active modules, enabled features, wireless activity, and overall device usage.
* As a result, operating time may be shorter or longer than the value observed during testing.

---

## Important Notes

* All features were tested under controlled conditions. Performance may vary depending on hardware variations and configuration.
* I recommend testing all components on a breadboard before assembling the final device. Be sure to verify the pinout, operating voltage, and specifications of each module, as different versions may have different requirements.
* Carefully check all power connections and ensure that every module is compatible with your chosen power supply. Testing everything beforehand can help identify wiring issues, compatibility problems, and configuration mistakes before final assembly.

---

## Bruce Firmware

Official Bruce Firmware project:

* https://bruce.computer/
* https://github.com/BruceDevices/firmware

---

## Disclaimer

* This project is intended for educational, research, and development purposes only.
* The author assumes no responsibility for any damage to hardware, software, property, legal issues, or data resulting from the use or misuse of the information, files, or materials provided in this repository.
* Users are responsible for ensuring compliance with all applicable laws, regulations, and policies in their jurisdiction. This project should only be used in authorized environments and in a responsible and ethical manner.
* No warranty is provided regarding the accuracy, completeness, reliability, or suitability of the hardware designs, firmware modifications, wiring diagrams, or documentation contained in this repository.
* By using this project, you acknowledge that you do so at your own risk.
