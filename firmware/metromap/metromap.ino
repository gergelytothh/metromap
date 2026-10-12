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

#include "station_map.h"

const int PIN_DIN = 23;
const int PIN_CLK = 18;
const int PIN_CS  = 5;

void setup() {
}

void loop() {
}
