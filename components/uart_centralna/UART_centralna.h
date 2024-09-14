#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/text_sensor/text_sensor.h"  // Include text_sensor

namespace esphome {
namespace uart_centralna {

class MyCustomUARTComponent : public uart::UARTDevice, public Component {
 public:
  // Use fully qualified namespace for UARTComponent
  MyCustomUARTComponent(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

  void setup() override {}
  void loop() override;
  void dump_config() override;

  // Method to create and return text sensors
  text_sensor::TextSensor *create_text_sensor(const std::string &name) {
    auto *sensor = new text_sensor::TextSensor();
    // Use c_str() to pass a const char* to set_name
    sensor->set_name(name.c_str());
    text_sensors_.push_back(sensor);
    return sensor;
  }

 protected:
  std::string buffer_;
  std::vector<text_sensor::TextSensor *> text_sensors_;  // Use fully qualified namespace
};

}  // namespace uart_centralna
}  // namespace esphome
