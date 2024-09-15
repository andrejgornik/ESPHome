// UART_centralna.h
#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"  // Include the sensor component

namespace esphome {
namespace uart_centralna {

class MyCustomUARTComponent : public uart::UARTDevice, public Component {
 public:
  MyCustomUARTComponent(esphome::uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

  void setup() override {}
  void loop() override;
  void dump_config() override;

  // Method to create and return sensor objects
  esphome::sensor::Sensor *create_temperature_sensor(const std::string &name) {
    auto *sensor = new esphome::sensor::Sensor();
    sensor->set_name(name.c_str());
    sensors_.push_back(sensor);
    return sensor;
  }

  esphome::sensor::Sensor *create_power_sensor(const std::string &name) {
    auto *sensor = new esphome::sensor::Sensor();
    sensor->set_name(name.c_str());
    sensors_.push_back(sensor);
    return sensor;
  }

  // Method to send command to the Arduino over UART
  void send_command(float desired_temp, float pid_power, bool tc_power);

 protected:
  std::string buffer_;
  std::vector<esphome::sensor::Sensor *> sensors_;
};

}  // namespace uart_centralna
}  // namespace esphome
