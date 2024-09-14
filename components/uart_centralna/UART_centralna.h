#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace uart_centralna {

class MyCustomUARTComponent : public uart::UARTDevice, public Component {
 public:
  // Modify the constructor to accept a UARTComponent pointer
  MyCustomUARTComponent(UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override {}
  void loop() override;
  void dump_config() override;
  
  // Method to create and return text sensors
  text_sensor::TextSensor *create_text_sensor(const std::string &name) {
    auto *sensor = new text_sensor::TextSensor();
    sensor->set_name(name);
    text_sensors_.push_back(sensor);
    return sensor;
  }

 protected:
  std::string buffer_;
  std::vector<text_sensor::TextSensor *> text_sensors_;
};

}  // namespace uart_centralna
}  // namespace esphome
