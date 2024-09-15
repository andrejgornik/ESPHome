// UART_centralna.h
#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include <vector>

namespace esphome {
namespace uart_centralna {

struct SensorInfo {
  esphome::sensor::Sensor *sensor;
  std::string json_key;
};

struct TextSensorInfo {
  esphome::text_sensor::TextSensor *sensor;
  std::string json_key;
};

struct BinarySensorInfo {
  esphome::binary_sensor::BinarySensor *sensor;
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

  // Method to create and return text sensor objects
  esphome::text_sensor::TextSensor *create_text_sensor(const std::string &json_key, const std::string &display_name) {
    auto *text_sensor = new esphome::text_sensor::TextSensor();
    text_sensor->set_name(display_name.c_str());
    text_sensors_.push_back({text_sensor, json_key});
    return text_sensor;
  }

  // Method to create and return binary sensor objects
  esphome::binary_sensor::BinarySensor *create_binary_sensor(const std::string &json_key, const std::string &display_name) {
    auto *binary_sensor = new esphome::binary_sensor::BinarySensor();
    binary_sensor->set_name(display_name.c_str());
    binary_sensors_.push_back({binary_sensor, json_key});
    return binary_sensor;
  }

  // Method to send command to the Arduino over UART
  void send_command(float desired_temp, float pid_power, bool tc_power);

 protected:
  std::string buffer_;
  std::vector<SensorInfo> sensors_;
  std::vector<TextSensorInfo> text_sensors_;
  std::vector<BinarySensorInfo> binary_sensors_;
};

}  // namespace uart_centralna
}  // namespace esphome
