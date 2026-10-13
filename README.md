# Metromap

<!--
OUTLINE ONLY - replace every comment with your own words, then delete the comment.
Aim: a recruiter understands the project within a minute. Short is fine.
-->

![Metromap with all LEDs lit](docs/images/map-lit.jpg)

A map of the Budapest metro, designed to show trains moving on all four lines. There are 96 LEDs on the map: two at each station (one per direction) and one at each terminus. They are hand-wired and soldered onto the map and driven by an ESP32 through a custom PCB. Right now it runs a simulated train animation; live data from BKK is the next step.

I'd seen lit-up metro maps of other cities online, but none of Budapest, and I didn't like the design of the ones I found. Since I'm studying electrical engineering anyway, I decided to build my own.

## How it works

The LEDs are driven by two MAX7219 chips, controlled by an ESP32. Each chip has 16 outputs: 8 DIG (digit) pins that sink current and 8 SEG (segment) pins that source it. Each LED sits where one DIG line and one SEG line cross, so one chip can control 64 LEDs and the two together 128.

Only one DIG line is active at a time. The chip sets the SEG lines for the LEDs that should be lit in that row, pulls the DIG line low, then moves on to the next row. It cycles through all 8 rows hundreds of times a second, so every lit LED looks constantly on.

The two chips are daisy-chained: they share the ESP32's clock and load pins, and U1's data output feeds U2's data input. The ESP32 shifts out 32 bits, a 16-bit word for each chip (an 8-bit register address and 8 bits of data, which set the SEG lines for one DIG row), and then a pulse on LOAD makes both chips apply them at the same time.

There are 96 LEDs, so one chip wasn't enough. I split them by metro line, so each line stays on a single chip and both chips stay under the 64-LED limit:

| Chip | Lines | LEDs used | Spare slots |
|---|---|---|---|
| U1 | M1 + M2 | 40 | 24 |
| U2 | M3 + M4 | 56 | 8 |

Every LED has an ID (1–96) and is assigned a chip, a DIG and a SEG. This mapping table is in [station_map.h](firmware/metromap/station_map.h) (also as [a CSV](hardware/led-mapping.csv)).

The firmware builds on this table:

- **One LED by ID**: looks the ID up in the table and turns on that chip/DIG/SEG.
- **Walk test**: lights every LED in turn, 1 to 96, and prints its station to the Serial Monitor, so wiring mistakes are easy to spot.
- **Train mode**: each line gets a route, from one terminus out along the forward LEDs and back along the backward ones, and four trains, one per line, move one stop at a time.

## Hardware

![The bare PCB](docs/images/pcb-blank-silkscreen.jpg)

I designed the driver PCB myself in KiCAD and had it made by NYÁKÁRUHÁZ Kft. It holds both MAX7219s in DIP sockets, so the soldering heat couldn't damage the chips. Every DIG and SEG pin goes to a labelled pad.

![The finished map with the driver board and ESP32](docs/images/map-overview.jpg)

From each pad, a wire runs to the back of the map, where it connects to the right LEDs. That's around 150 solder joints in total, all by hand.

![The rear wiring](docs/images/rear-wiring.jpg)
*The back of the map. Every wire is labelled in pencil with its DIG/SEG line.*

| Part | What |
|---|---|
| Microcontroller | ESP32-WROOM-32U dev board |
| LED drivers | 2 × MAX7219 (DIP-24, socketed) |
| PCB | Own design in KiCAD, made by NYÁKÁRUHÁZ Kft. |
| LEDs | 96, one colour per line |
| Map | Printed poster on cardboard |
| Power | 5 V from USB, via the ESP32 |

Design files: [schematic (PDF)](hardware/Metromap%20schematic.pdf) · [KiCAD project](hardware/kicad/) · [3D render](docs/images/pcb-3d.png)

### What I'd do differently

- **The wiring.** It works, but it's hard to trace and service. Next time I'd group the LEDs on small boards or connectors behind each line, with ribbon cable to the driver board.
- **The ISET resistor.** Both chips share one 10 kΩ R1, but each MAX7219 should have its own. According to the datasheet’s output current curves, a shared resistor behaves roughly like 20 kΩ per chip, about 25 mA peak per segment instead of about 45 mA, and the split between the chips isn’t guaranteed to be even. It works and the brightness looks fine, but a second version would give each chip its own resistor.

## Build and flash

<!-- Arduino IDE version, ESP32 board package, MD_MAX72xx (or whichever library
     you end up using), board selection, which sketch to open. -->

## What went wrong and how I fixed it

<!-- Best entry from docs/bring-up-log.md: symptom, suspicion, measurement, cause. -->

## What's next

<!-- Wi-Fi, live BKK timetable data, web interface. -->
