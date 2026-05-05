# Sample Library

## Overview
This is a sample library demonstrating the structure for Arduino libraries in the Arduino Refresh project.

## Features
- Example feature 1
- Example feature 2
- Easy to use API

## Installation
1. Copy the `src` folder to your Arduino libraries folder
2. Restart the Arduino IDE
3. Include the library in your sketch: `#include <SampleLibrary.h>`

## Usage

### Basic Example
```cpp
#include <SampleLibrary.h>

SampleLibrary sample;

void setup() {
  Serial.begin(9600);
  sample.begin();
}

void loop() {
  sample.update();
  delay(1000);
}
```

## API Reference

### `begin()`
Initialize the library.

### `update()`
Update the library state (call in loop).

## Contributing
Please submit pull requests to this library's repository.
