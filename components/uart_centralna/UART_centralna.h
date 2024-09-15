#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include <ArduinoJson.h>  // Include ArduinoJson

namespace esphome {
namespace uart_centralna {

class MyCustomUARTComponent : public uart::UARTDevice, public Component {
 public:
  MyCustomUARTComponent(esphome::uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

  void setup() override {}
  void loop() override;
  void dump_config() override;

  // Methods to create and return sensors
  sensor::Sensor *create_temperature_sensor(const std::string &name) {
    auto *sensor = new sensor::Sensor();
    sensor->set_name(name.c_str());
    temperature_sensors_.push_back(sensor);
    return sensor;
  }

  sensor::Sensor *create_power_sensor(const std::string &name) {
    auto *sensor = new sensor::Sensor();
    sensor->set_name(name.c_str());
    power_sensors_.push_back(sensor);
    return sensor;
  }

  esphome::text_sensor::TextSensor *create_text_sensor(const std::string &name) {
    auto *sensor = new esphome::text_sensor::TextSensor();
    sensor->set_name(name.c_str());
    text_sensors_.push_back(sensor);
    return sensor;
  }

  // Method to send command to the Arduino over UART
  void send_command(float desired_temp, float pid_power, bool tc_power);

 protected:
  std::string buffer_;
  std::vector<sensor::Sensor *> temperature_sensors_;
  std::vector<sensor::Sensor *> power_sensors_;
  std::vector<esphome::text_sensor::TextSensor *> text_sensors_;
};

}  // namespace uart_centralna
}  // namespace esphome
