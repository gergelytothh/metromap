// Metromap firmware - ESP32 driving two daisy-chained MAX7219s.
//
// Board wiring (ESP32 -> driver PCB):
//   DIN        GPIO23  (VSPI MOSI)
//   CLK        GPIO18  (VSPI SCK)
//   LOAD / CS  GPIO5
//
// First release. The functions in this file:
//
//   setStation(chip, dig, seg, on)      - turn one LED on or off by its
//                                         chip / DIG / SEG (from LED_MAP)
//   setLedById(id, on)                  - turn one LED on or off by its id (1..96)
//   lightAll()                          - turn every LED on (test, off by default)
//   walkTest()                          - light all 96 LEDs one at a time,
//                                         in LED_MAP order
//   trainMode()                         - four trains, one on each line, all
//                                         going back and forth at the same time
//
// Choose walkTest() or trainMode() in loop().

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
void setStation(uint8_t chipIndex, uint8_t dig, uint8_t seg, bool state) {
  // The library's row is the DIG pin.
  uint8_t row = dig;

  // The library's column is the SEG pin, in reverse order (SEG_A = 6 ...
  // SEG_G = 0, SEG_DP = 7). Each chip has 8 columns, so chip 1 starts at 8.
  uint8_t localCol = (seg == 7) ? 7 : (6 - seg);
  uint8_t globalCol = (chipIndex * 8) + localCol;

  mx.setPoint(row, globalCol, state);
}

// Turn one LED on or off by its id (1..96, the first column in LED_MAP).
void setLedById(uint8_t id, bool state) {
  // Ignore ids that don't exist
  if (id < 1 || id > LED_COUNT) {
    return;
  }

  // Ids start at 1 but array positions start at 0, so id 1 is LED_MAP[0]
  const LedAddr& led = LED_MAP[id - 1];
  setStation(led.chip, led.dig, led.seg, state);
}

// Light all LEDs: every row and column on both chips
void lightAll() {
  for (uint8_t dev = 0; dev < MAX_DEVICES; dev++) {
    for (uint8_t row = 0; row < 8; row++) {
      for (uint8_t col = 0; col < 8; col++) {
        mx.setPoint(row, (dev * 8) + col, true);
      }
    }
  }
}

const unsigned long WALK_DELAY_MS = 300;  // how long each LED stays on

// Light the LEDs one at a time, id 1 to 96, so only one is on at once.
// Prints each LED to the Serial Monitor so you can check it is the right one.
void walkTest() {
  for (uint8_t id = 1; id <= LED_COUNT; id++) {
    const LedAddr& led = LED_MAP[id - 1];
    Serial.print(id);
    Serial.print(": ");
    Serial.println(led.station);

    setLedById(id, true);
    delay(WALK_DELAY_MS);
    setLedById(id, false);
  }
}

const unsigned long TRAIN_DELAY_MS = 750;  // how long the trains stay at each stop
const uint8_t LINE_COUNT = 4;              // M1, M2, M3, M4

// Each line's route as a list of LED ids, built once in setup():
//   Out:  the line's FWD LEDs, first terminus to last terminus.
//   Back: the line's BWD LEDs in reverse order.
// After the last id the train goes back to the start of the list (the first
// terminus), so it goes round and round. Every LED on the line is in the
// route exactly once. For M1: 1, 2, 4, 6 ... 18, 20, 19, 17 ... 5, 3
uint8_t trainRoute[LINE_COUNT][LED_COUNT];
uint8_t trainRouteLen[LINE_COUNT];  // how many ids are in each route
uint8_t trainPos[LINE_COUNT];       // where each train is in its route

// Fill in the route for one line.
void buildTrainRoute(Line line) {
  uint8_t len = 0;

  // Out
  for (uint8_t id = 1; id <= LED_COUNT; id++) {
    const LedAddr& led = LED_MAP[id - 1];
    if (led.line == line && led.dir == FWD) {
      trainRoute[line][len] = id;
      len++;
    }
  }

  // Back (id counts down, so stops come in reverse order)
  for (uint8_t id = LED_COUNT; id >= 1; id--) {
    const LedAddr& led = LED_MAP[id - 1];
    if (led.line == line && led.dir == BWD) {
      trainRoute[line][len] = id;
      len++;
    }
  }

  trainRouteLen[line] = len;
  trainPos[line] = 0;  // every train starts at its first terminus
}

// Four trains, one on each line, all moving at the same time.
// Each call moves every train one stop, so loop() keeps them going.
void trainMode() {
  // Light each train where it is now
  for (uint8_t line = 0; line < LINE_COUNT; line++) {
    setLedById(trainRoute[line][trainPos[line]], true);
  }

  delay(TRAIN_DELAY_MS);

  // Turn them off and move each train to its next stop.
  // % wraps the position back to 0 after the end of the route.
  for (uint8_t line = 0; line < LINE_COUNT; line++) {
    setLedById(trainRoute[line][trainPos[line]], false);
    trainPos[line] = (trainPos[line] + 1) % trainRouteLen[line];
  }
}

void setup() {
  Serial.begin(115200);

  mx.begin();

  // Full brightness on both chips
  mx.control(0, MAX_DEVICES - 1, MD_MAX72XX::INTENSITY, MAX_INTENSITY);

  // Start with every LED off
  mx.clear();

  // lightAll();  // uncomment to turn every LED on as a test

  // Work out each line's route for trainMode()
  buildTrainRoute(M1);
  buildTrainRoute(M2);
  buildTrainRoute(M3);
  buildTrainRoute(M4);
}

void loop() {
  // Runs again and again. Pick one:
  // walkTest();
  trainMode();
}
