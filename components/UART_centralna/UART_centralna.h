#include "esphome.h"

class MyCustomComponent : public Component, public UARTDevice {
 public:
  MyCustomComponent(UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override {
    // nothing to do here
  }
  void loop() override {
    // Use Arduino API to read data, for example
    String line = readString();
    int i = parseInt();
    while (available()) {
      char c = read();
    }
    // etc
  }
};