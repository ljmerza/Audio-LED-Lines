# Audio LED Lines

An Arduino project that creates colorful LED animations synchronized with audio input using the MSGEQ7 audio spectrum analyzer chip.

## Demo

Watch the project in action: [YouTube Demo](https://www.youtube.com/watch?v=_NK44yXXayU)

## Overview

This project provides two different implementations for creating animated LED lines that respond to audio:

1. **ledlines** - Audio-reactive LED lines using MSGEQ7 chip for real-time audio analysis
2. **ledLinesDelay** - Independent LED lines with customizable delays and patterns

## Hardware Requirements

- Arduino board (Leonardo, Uno, etc.)
- NeoPixel LED strip (90 LEDs recommended)
- MSGEQ7 audio spectrum analyzer chip (for ledlines version)
- Appropriate power supply for LED strip
- Resistors and capacitors as per MSGEQ7 datasheet

## Software Requirements

- Arduino IDE
- [FastLED library](https://github.com/FastLED/FastLED)

## Installation

1. Install the Arduino IDE
2. Install the FastLED library via Arduino Library Manager
3. Clone this repository
4. Open the desired `.ino` file in Arduino IDE
5. Configure the settings for your LED strip (see Configuration section)
6. Upload to your Arduino board

## Configuration

### ledlines/ledlines.ino

Key parameters you can adjust:

- `NUM_LEDS` - Total number of LEDs in your strip (default: 90)
- `DATA_PIN` - Arduino pin connected to LED strip data (default: 5)
- `LINELENGTH` - Length of each LED line (default: 4)
- `NUMBEROFLINES` - Number of simultaneous LED lines (default: 14)
- `HUESPEED` - Speed of color change (default: 5)
- `LEDSPEED` - Movement speed in milliseconds (default: 0)

Audio chip pins:
- `analogPin` - Analog input from MSGEQ7 (default: 0)
- `strobePin` - MSGEQ7 strobe pin (default: 13)
- `resetPin` - MSGEQ7 reset pin (default: 3)

### ledLinesDelay/ledLines.ino

Key parameters you can adjust:

- `NUM_LEDS` - Total number of LEDs in your strip (default: 90)
- `DATA_PIN` - Arduino pin connected to LED strip data (default: 5)
- `LINELENGTH` - Length of each LED line (default: 5)
- `STRIPNUMB` - Number of LED lines (default: 7)
- `HUESPEED` - Speed of color change (default: 2)

## Wiring

### MSGEQ7 Connections (for ledlines version)

- MSGEQ7 OUT pin → Arduino analog pin (A0)
- MSGEQ7 STROBE pin → Arduino digital pin 13
- MSGEQ7 RESET pin → Arduino digital pin 3
- Follow [MSGEQ7 datasheet](https://www.sparkfun.com/datasheets/Components/General/MSGEQ7.pdf) for complete circuit

### LED Strip Connections

- LED strip DATA → Arduino pin 5 (or configured DATA_PIN)
- LED strip VCC → External 5V power supply
- LED strip GND → Common ground with Arduino

## Features

- Real-time audio visualization (ledlines)
- Customizable color patterns
- Multiple independent LED lines
- Smooth HSV color transitions
- Configurable speeds and delays

## Author

Leonardo Merza - [https://lmerza.com](https://lmerza.com)

## License

This project is open source and available for personal and educational use.
