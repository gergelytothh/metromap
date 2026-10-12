# Metromap

<!--
OUTLINE ONLY - replace every comment with your own words, then delete the comment.
Aim: a recruiter understands the project within a minute. Short is fine.
-->

![Metromap with all LEDs lit](docs/images/map-lit.jpg)

<!-- One or two sentences: what Metromap is and why you built it. -->

## How it works

<!-- The addressing scheme: 52 stations, 96 LEDs, two MAX7219s, 8x8 each.
     How a (line, station, direction) becomes (chip, DIG row, SEG column).
     Point to firmware/metromap/station_map.h and hardware/led-mapping.csv. -->

## Hardware

<!-- Short summary: ESP32, 2x MAX7219 daisy-chained over SPI, your KiCAD PCB,
     192 hand-soldered leads. Link the schematic PDF and PCB render in hardware/. -->

## Build and flash

<!-- Arduino IDE version, ESP32 board package, MD_MAX72xx (or whichever library
     you end up using), board selection, which sketch to open. -->

## What went wrong and how I fixed it

<!-- Best entry from docs/bring-up-log.md: symptom, suspicion, measurement, cause. -->

## What's next

<!-- Wi-Fi, live BKK timetable data, web interface. -->
