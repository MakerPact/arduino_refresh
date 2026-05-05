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
