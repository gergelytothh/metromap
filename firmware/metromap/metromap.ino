// Metromap firmware - ESP32 driving two daisy-chained MAX7219s.
//
// Board wiring (ESP32 -> driver PCB):
//   DIN        GPIO23  (VSPI MOSI)
//   CLK        GPIO18  (VSPI SCK)
//   LOAD / CS  GPIO5
//
// This is a starting point, not finished firmware. Paste your current
// "light all" code in here first, then build the three first-release
// pieces on top of it:
//
//   1. setStation(line, stop, dir, on)  - look the LED up in LED_MAP and
//                                         set that one LED
//   2. walkTest()                       - light all 96 LEDs one at a time,
//                                         in LED_MAP order
//   3. trainMode()                      - one train moving station to station
//                                         along each line

#include <MD_MAX72xx.h>
#include <SPI.h>
#include "station_map.h"

const int PIN_DIN = 23;
const int PIN_CLK = 18;
const int PIN_CS  = 5;

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 2  // two MAX7219 chips in the chain

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, PIN_CS, MAX_DEVICES);

// Turn one LED on or off by its chip / DIG / SEG pins.
// Use the same numbers as the chip, dig and seg columns in station_map.h:
//   chipIndex: 0 = U1 (M1 + M2), 1 = U2 (M3 + M4)
//   dig:       0..7 = DIG0..DIG7
//   seg:       0..6 = SEG_A..SEG_G, 7 = SEG_DP
void setMultiChipLed(uint8_t chipIndex, uint8_t dig, uint8_t seg, bool state) {
  // The library's row is the DIG pin.
  uint8_t row = dig;

  // The library's column is the SEG pin, in reverse order (SEG_A = 6 ...
  // SEG_G = 0, SEG_DP = 7). Each chip has 8 columns, so chip 1 starts at 8.
  uint8_t localCol = (seg == 7) ? 7 : (6 - seg);
  uint8_t globalCol = (chipIndex * 8) + localCol;

  mx.setPoint(row, globalCol, state);
}

void setup() {
  mx.begin();

  // Full brightness on both chips
  mx.control(0, MAX_DEVICES - 1, MD_MAX72XX::INTENSITY, MAX_INTENSITY);

  // Light all LEDs: every row and column on both chips
  for (uint8_t dev = 0; dev < MAX_DEVICES; dev++) {
    for (uint8_t row = 0; row < 8; row++) {
      for (uint8_t col = 0; col < 8; col++) {
        mx.setPoint(row, (dev * 8) + col, true);
      }
    }
  }
}

void loop() {
  // Nothing to do; the LEDs stay on
}
