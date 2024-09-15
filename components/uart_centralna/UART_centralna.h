#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/json/json_util.h"  // Include json_util to handle JSON parsing

namespace esphome {
namespace uart_centralna {

class MyCustomUARTComponent : public uart::UARTDevice, public Component {
 public:
  MyCustomUARTComponent(esphome::uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

  void setup() override {}
  void loop() override;
  void dump_config() override;
  
  // Method to create and return text sensors
  esphome::text_sensor::TextSensor *create_text_sensor(const std::string &name) {
    auto *sensor = new esphome::text_sensor::TextSensor();
    sensor->set_name(name.c_str());
    text_sensors_.push_back(sensor);
    return sensor;
  }

 protected:
  std::string buffer_;
  std::vector<esphome::text_sensor::TextSensor *> text_sensors_;
};

}  // namespace uart_centralna
}  // namespace esphome
