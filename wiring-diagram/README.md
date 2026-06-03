# PINOUT

## :electric_plug: Module pin ---> ESP32-S3 GPIO

### Display

| Display Pin | ESP32-S3 |
|------------|---------------|
| LED BL | GPIO 4 |
| SCK (SCLK) | GPIO 5 |
| SDA (MOSI) | GPIO 6 |
| A0 (DC) | GPIO 7 |
| RESET | GPIO 15 |
| CS | GPIO 16 |

### SD Card

| SD Card Pin | ESP32-S3 |
|------------|---------------|
| CS | GPIO 40 |
| MOSI | GPIO 6 |
| MISO | GPIO 41 |
| SCK | GPIO 5 |

### NRF24L01

| NRF24L01 Pin | ESP32-S3 |
|-------------|---------------|
| CE | GPIO 21 |
| CSN / SS | GPIO 47 |
| SCK | GPIO 5 |
| MOSI | GPIO 6 |
| MISO | GPIO 41 |
| IRQ | GPIO 35 |

### Joystick

| Joystick Pin | ESP32-S3 |
|-------------|---------------|
| VR-X | GPIO 12 |
| VR-Y | GPIO 13 |
| SW | GPIO 14 |

### I2C

| I2C Pin | ESP32-S3 |
|---------|---------------|
| SDA | GPIO 18 |
| SCL | GPIO 8 |

### Infrared

| IR Pin | ESP32-S3 |
|---------|---------------|
| TX | GPIO 1 |
| RX | GPIO 2 |

### GPS

| GPS Pin | ESP32-S3 |
|---------|---------------|
| GPS TX → ESP32 RX | GPIO 38 |
| GPS RX → ESP32 TX | GPIO 17 |

### Battery Monitoring

| Signal | ESP32-S3 |
|---------|---------------|
| BAT | GPIO 10 |


---


<p align="center">
  <img src="https://raw.githubusercontent.com/viniciushnf/ESP32-S3-Bruce-ST7735-1.8/refs/heads/main/wiring-diagram/wiring-diagram.png" alt="ESP32-S3 pinout" width="100%">
</p>

---

## :warning: Attention:

* I recommend testing all components on a breadboard before assembling the final device. Be sure to verify the pinout,
operating voltage, and specifications of each module, as different versions may have different requirements.

* Carefully check the power connections and ensure that all modules are compatible with your chosen power supply.

* Testing everything beforehand can help identify wiring issues, compatibility problems, and configuration mistakes before the final assembly.

---

## :battery: Battery Charger and Monitoring Circuit

* This project uses a J5019 module, which combines a TP4056 Li-ion battery charger and an MT3608 boost converter. The TP4056 safely charges the 18650 battery, while the MT3608 boosts the battery voltage to a stable 5V output for the ESP32-S3.

* Battery voltage is monitored using a voltage divider made of two 100 kΩ resistors, reducing the battery voltage by half before it reaches the ESP32-S3 ADC pin. This is necessary because a Li-ion battery can reach 4.2V, which is too high for direct ADC measurement.

* A 100 nF capacitor helps filter noise and improves battery voltage readings. Always verify your module specifications and test the circuit before final assembly.

---

## :information_source: NRF24L01 adapter

* The NRF24L01 is sensitive to power supply fluctuations and can become unstable when powered directly from the ESP32-S3. 

* The NRF24L01 adapter includes a voltage regulator and filtering capacitors that provide a stable 3.3V supply, improving reliability, communication range, and overall performance. 

* Using the adapter is highly recommended to prevent connection issues, random resets, and packet loss.