#include "esphome/core/log.h"
#include "UART_centralna.h"
#include "esphome/core/hal.h"
#include "esphome/core/application.h"
#include "esphome/components/json/json_util.h"

namespace esphome {
namespace uart_centralna {

static const char *TAG = "uart_centralna";

void MyCustomUARTComponent::loop() {
  while (available()) {
    char c = read();
    buffer_ += c;

    if (c == '\n') {
      ESP_LOGD(TAG, "Received: %s", buffer_.c_str());
      // Parse the buffer here
      if (buffer_.front() == '#') {
        std::string json_str = buffer_.substr(1);  // Remove the '#' character
        // Parse JSON
        std::string error;
        json::parse_json(json_str, [this](const json::JsonObject &root) {
          // Extract values and publish to text sensors
          for (auto *sensor : this->text_sensors_) {
            const char *name = sensor->get_name().c_str();
            if (root.containsKey(name)) {
              auto value = root[name];
              sensor->publish_state(value.as<std::string>());
            }
          }
        }, &error);
        if (!error.empty()) {
          ESP_LOGW(TAG, "JSON parsing error: %s", error.c_str());
        }
      }
      buffer_.clear();
    }
  }
}

void MyCustomUARTComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "UART Centralna Component");
}

void MyCustomUARTComponent::send_command(float desired_temp, float pid_power, bool tc_power) {
  std::string on_off_text = tc_power ? "ON" : "OFF";

  char send_json[256];
  snprintf(send_json, sizeof(send_json),
           "{\"device\":\"raspberry\",\"desired_temperature\":%.2f,\"PID_power\":%.2f,\"TC_power\":\"%s\"}",
           desired_temp, pid_power, on_off_text.c_str());

  // Send over UART
  this->write_str("#");
  this->write_str(send_json);
  this->write_str("\n");

  ESP_LOGD(TAG, "Sent command: %s", send_json);
}

}  // namespace uart_centralna
}  // namespace esphome
