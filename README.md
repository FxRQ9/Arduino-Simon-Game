# Arduino Simon Memory Game

## Overview

A Simon-style memory game built with an Arduino Uno R3, three LEDs, three pushbuttons, and a piezo buzzer. Watch and listen to a sequence, then repeat it by pressing the matching buttons. Each completed level adds one more step to remember.

I built this project to practice C++, explore the basics of object-oriented programming (OOP), and learn how to connect software with electronic components.

## Demo

*Project photos and a gameplay video will be added here.*

## Components

The following bill of materials is based on `bom.csv`:

| Component | Quantity | Reference |
| --- | --- | --- |
| Arduino Uno R3 | 1 | U1 |
| Small breadboard | 1 | 1 (breadboard reference in the BOM) |
| 220 Ω resistor | 3 | R1, R2, R3 |
| Green LED | 2 | D1, D3 |
| Red LED | 1 | D2 |
| Pushbutton | 3 | S1, S2, S3 |
| Piezo buzzer | 1 | PIEZO1 |

You will also need jumper wires and a USB data cable to connect the Arduino to your computer.

## Wiring

*A circuit diagram and a photo of the wiring will be added here.*

The firmware uses these pin assignments:

| Function | Arduino Uno pin |
| --- | --- |
| LED 1 | D11 |
| LED 2 | D12 |
| LED 3 | D13 |
| Button 1 | D2 |
| Button 2 | D3 |
| Button 3 | D4 |
| Piezo buzzer | D8 |

- Connect each LED through its own 220 Ω current-limiting resistor, with its cathode connected to GND.
- Connect each button between its assigned input pin and GND. The code uses `INPUT_PULLUP`, so a pressed button reads `LOW`.
- Connect the piezo buzzer between D8 and GND.
- Use a common ground for all components. Button 1 corresponds to LED 1, and so on.

## Build and Upload

### Requirements

- PlatformIO Core, or Visual Studio Code with the PlatformIO IDE extension
- An Arduino Uno R3 and a USB data cable

Open the project folder containing `platformio.ini`. Run the commands below from a terminal in that folder. PlatformIO installs the configured board tools and ArduinoSTL dependency when you build.

### Build the Firmware

```bash
pio run -e uno
```

Alternatively, click the **✓ Build** button in the PlatformIO toolbar.

### Upload to the Arduino

Connect the Arduino Uno to your computer using a USB data cable, then run:

```bash
pio run -e uno -t upload
```

Alternatively, click the **→ Upload** button in the PlatformIO toolbar.

If PlatformIO cannot detect the board automatically, specify its port:

```bash
pio run -e uno -t upload --upload-port YOUR_PORT
```

Replace `YOUR_PORT` with your board's port, such as `/dev/ttyUSB0` on Linux or `COM3` on Windows.

### View the Score

Open the serial monitor at 9600 baud:

```bash
pio device monitor -b 9600
```

The game prints the accumulated score after each completed level. Press `Ctrl+C` to close the monitor.

## How to Play

1. Power on or reset the Arduino. One LED lights up and the buzzer plays its matching tone.
2. Wait for playback to finish, then press the button corresponding to that LED.
3. Each correct step earns **10 points**. After you complete the level, the game prints your accumulated score to the serial monitor.
4. The next level replays the previous sequence with one additional step. Watch and listen carefully, then repeat the entire sequence in order.
5. If you press the wrong button, all three LEDs light up briefly and the buzzer plays an error tone. The score resets to zero, and the game automatically starts again at level 1 with a newly generated sequence.

The sequence uses pseudorandom numbers, so a new game can share steps with an earlier game. See the limitations below for the behavior after a board reset.

## What I Learned

This project helped me understand how to organize a C++ project and use classes to separate button input handling from game logic. It also showed me the value of clear variable names, readable code, and comments that explain the purpose of a section.

I practiced several programming and electronics concepts:

- **Button debouncing:** using `millis()` and a 50 ms stability interval to filter mechanical switch bounce.
- **Sequence storage:** using `std::vector` to store the generated sequence and the player's input.
- **Digital input and output:** reading buttons with `INPUT_PULLUP` and controlling LEDs with `digitalWrite()`.
- **Sound feedback:** generating distinct tones with `tone()`.
- **Game state:** tracking the level, score, and current step, and resetting them after an incorrect input.
- **Serial communication:** displaying the score in the serial monitor.

## Limitations and Planned Improvements

- **Blocking delays:** playback and button feedback use `delay()`, which pauses button polling. A future improvement is to use a state machine with `millis()` for timing.
- **Repeatable randomness after reset:** the code does not currently call `randomSeed()`, so the pseudorandom sequence repeats from the same starting state after a board reset. Seeding the generator is a planned improvement.
- **Limited sequence capacity:** the sequence grows dynamically on a board with limited RAM, and the level and step counters use 8-bit values. A future version should define a maximum level and handle reaching it.
- **Code cleanup:** some button-handling logic is repeated, and older commented-out code remains. Refactoring these sections would make the project easier to maintain.
- **Documentation:** project photos, a circuit diagram, and a gameplay video still need to be added.
