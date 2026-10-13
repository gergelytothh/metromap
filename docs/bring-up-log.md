# Bring-up log

Problems and findings from building and testing the map, one entry each: what I saw, what I suspected, what I checked, and what it turned out to be.

---

### 2026-08 - Addressing lit the wrong LEDs

- **Symptom:** For a long time the addressing didn't work: setting an LED by its DIG/SEG lit a different LED on the map.
- **Suspected:** Not obvious at first, so I tested systematically instead of guessing.
- **Measured / tested:** Lit one address at a time and wrote down which LED actually came on for each try, until a pattern appeared.
- **Actual cause:** The MD_MAX72xx library numbers the columns in a different order from the chip's SEG pins: SEG_A is column 6, down to SEG_G at column 0, and only SEG_DP stays at column 7.
- **Fix:** One line in the firmware that translates SEG to the library's column: `(seg == 7) ? 7 : (6 - seg)`. Tested the theory LED by LED, and it held.

### 2026-10-14 - Shared ISET resistor: more current or less?

- **Symptom:** Design review, not a fault. The board works, but R1 (10 kΩ) is shared between the ISET pins of both MAX7219s, while each chip should have its own.
- **Suspected:** I thought sharing it would let more current through, so the LEDs wouldn't be dimmed, and that a separate resistor per chip would make them dimmer.
- **Measured / tested:** Checked the datasheet's "Segment driver output current vs output voltage" curves. Each chip takes a share of the current through R1 as its reference, so two chips on one 10 kΩ behave roughly like 20 kΩ each: about 25 mA peak per segment instead of about 45 mA.
- **Actual cause:** The opposite of what I expected. Sharing roughly halves the LED current, and the split between the chips isn't guaranteed to be even.
- **Fix:** None needed for now, since the brightness looks fine. A second version of the board would give each chip its own resistor.