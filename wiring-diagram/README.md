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

| I2C | ESP32-S3 |
|---------|---------------|
| SDA | GPIO 18 |
| SCL | GPIO 8 |

### Infrared

| IR | ESP32-S3 |
|---------|---------------|
| TX | GPIO 1 |
| RX | GPIO 2 |

### GPS

| GPS Pin | ESP32-S3 |
|---------|---------------|
| TX → ESP32 RX | GPIO 38 |
| RX → ESP32 TX | GPIO 17 |

### Battery Monitoring

| Signal | ESP32-S3 |
|---------|---------------|
| BAT | GPIO 10 |


---


## :warning: Attention:

* I recommend testing all components on a breadboard before assembling the final device. Be sure to verify the pinout,
operating voltage, and specifications of each module, as different versions may have different requirements.

* Carefully check the power connections and ensure that all modules are compatible with your chosen power supply.

* Testing everything beforehand can help identify wiring issues, compatibility problems, and configuration mistakes before the final assembly.