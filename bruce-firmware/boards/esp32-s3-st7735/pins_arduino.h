//   Developed by ViniciusHNF
//   GitHub Repository: https://github.com/viniciushnf/ESP32-S3-Bruce-ST7735-1.8

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

// SPI Display
#define SPI_SS_PIN 11
#define SPI_MOSI_PIN 6
#define SPI_MISO_PIN 41
#define SPI_SCK_PIN 5

#define USE_HSPI_PORT

#define HAS_5_BUTTONS

// Display ST7735
// #define USER_SETUP_LOADED // Já foi definido
// #define ST7735_DRIVER // Já foi definido
// #define TFT_WIDTH 128
// #define TFT_HEIGHT 160
// #define ST7735_BLACKTAB
// #define TFT_RGB_ORDER TFT_BGR // Colour order Blue-Green-Red
#define TFT_BACKLIGHT_ON HIGH
#define TFT_BL 4
#define TFT_CS 16
#define TFT_DC 7
#define TFT_RST 15
#define TFT_MOSI 6
#define TFT_SCLK 5
#define TFT_MISO 41

// #define SPI_FREQUENCY 40000000 // Original
// #define SPI_FREQUENCY 10000000
// #define SPI_READ_FREQUENCY 16000000

#define ROTATION 1
#define MINBRIGHT 1

#define USB_VID 0x303a
#define USB_PID 0x1001

#define PIN_RGB_LED 48
// BUILTIN_LED can be used in new Arduino API digitalWrite() like in Blink.ino
static const uint8_t LED_BUILTIN = SOC_GPIO_PIN_COUNT + PIN_RGB_LED;
#define BUILTIN_LED LED_BUILTIN // backward compatibility
#define LED_BUILTIN LED_BUILTIN // allow testing #ifdef LED_BUILTIN
// RGB_BUILTIN and RGB_BRIGHTNESS can be used in new Arduino API rgbLedWrite()
#define RGB_BUILTIN LED_BUILTIN
#define RGB_BRIGHTNESS 64

// =============================================
// RGB LED (WS2812 NeoPixel)
// =============================================
// #define HAS_RGB_LED 1
// #define RGB_LED 48
// #define LED_TYPE WS2812B
// #define LED_ORDER GRB
// #define LED_TYPE_IS_RGBW 0
// #define LED_COUNT 1

// =============================================
// GPS
// =============================================
// RX -> 38
// TX -> 17

static const uint8_t TX = 43;
static const uint8_t RX = 44;

static const uint8_t SDA = 18;
static const uint8_t SCL = 8;

static const uint8_t SS = 11; // Just so it's not empty.
static const uint8_t MOSI = 6;
static const uint8_t MISO = 41;
static const uint8_t SCK = 5;

static const uint8_t A0 = 1;
static const uint8_t A1 = 2;
static const uint8_t A2 = 3;
static const uint8_t A3 = 4;
static const uint8_t A4 = 5;
static const uint8_t A5 = 6;
static const uint8_t A6 = 7;
static const uint8_t A7 = 8;
static const uint8_t A8 = 9;
static const uint8_t A9 = 10;
static const uint8_t A10 = 11;
static const uint8_t A11 = 12;
static const uint8_t A12 = 13;
static const uint8_t A13 = 14;
static const uint8_t A14 = 15;
static const uint8_t A15 = 16;
static const uint8_t A16 = 17;
static const uint8_t A17 = 18;
static const uint8_t A18 = 19;
static const uint8_t A19 = 20;

static const uint8_t T1 = 1;
static const uint8_t T2 = 2;
static const uint8_t T3 = 3;
static const uint8_t T4 = 4;
static const uint8_t T5 = 5;
static const uint8_t T6 = 6;
static const uint8_t T7 = 7;
static const uint8_t T8 = 8;
static const uint8_t T9 = 9;
static const uint8_t T10 = 10;
static const uint8_t T11 = 11;
static const uint8_t T12 = 12;
static const uint8_t T13 = 13;
static const uint8_t T14 = 14;

#endif /* Pins_Arduino_h */
