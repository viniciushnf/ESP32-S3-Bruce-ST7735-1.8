#ifndef PINS_ARDUINO_H_
#define PINS_ARDUINO_H_

// As definições abaixo já são fornecidas pelos build_flags do .ini,
// mas é seguro mantê-las como fallback.

// Display
#ifndef TFT_CS
#define TFT_CS 10
#endif
#ifndef TFT_DC
#define TFT_DC 8
#endif
#ifndef TFT_RST
#define TFT_RST 9
#endif
#ifndef TFT_MOSI
#define TFT_MOSI 11
#endif
#ifndef TFT_SCLK
#define TFT_SCLK 12
#endif
#ifndef TFT_BL
#define TFT_BL -1
#endif

// Joystick
#ifndef SEL_BTN
#define SEL_BTN 13
#endif
#ifndef JOY_X
#define JOY_X 6
#endif
#ifndef JOY_Y
#define JOY_Y 7
#endif

#endif
