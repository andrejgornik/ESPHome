#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"  // Include the sensor component
#include <vector>

namespace esphome {
namespace uart_centralna {

struct SensorInfo {
  esphome::sensor::Sensor *sensor;
  std::string json_key;
};

class MyCustomUARTComponent : public uart::UARTDevice, public Component {
 public:
  MyCustomUARTComponent(esphome::uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

  void setup() override {}
  void loop() override;
  void dump_config() override;

  // Method to create and return sensor objects
  esphome::sensor::Sensor *create_sensor(const std::string &json_key, const std::string &display_name) {
    auto *sensor = new esphome::sensor::Sensor();
    sensor->set_name(display_name.c_str());
    sensors_.push_back({sensor, json_key});
    return sensor;
  }

  // Method to send command to the Arduino over UART
  void send_command(float desired_temp, float pid_power, bool tc_power);

 protected:
  std::string buffer_;
  std::vector<SensorInfo> sensors_;
};

}  // namespace uart_centralna
}  // namespace esphome
