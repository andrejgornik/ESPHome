#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include <vector>

namespace esphome {
namespace uart_centralna {

class MyCustomUARTComponent : public uart::UARTDevice, public Component {
 public:
  MyCustomUARTComponent(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

  void setup() override {}
  void loop() override;
  void dump_config() override;

  // Method to create and return text sensors
  text_sensor::TextSensor *create_text_sensor(const std::string &name) {
    auto *sensor = new text_sensor::TextSensor();
    sensor->set_name(name.c_str());
    this->text_sensors_.push_back(sensor);
    return sensor;
  }

  void send_command(float desired_temp, float pid_power, bool tc_power);

 protected:
  std::string buffer_;
  std::vector<text_sensor::TextSensor *> text_sensors_;
};

}  // namespace uart_centralna
}  // namespace esphome
