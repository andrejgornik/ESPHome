#include "esphome/core/log.h"
#include "UART_centralna.h"
#include "esphome/components/json/json_util.h"
#include "ArduinoJson.h"

namespace esphome {
namespace uart_centralna {

static const char *TAG = "uart_centralna";

void MyCustomUARTComponent::loop() {
  while (available()) {
    char c = read();
    buffer_ += c;

    if (c == '\n') {
      ESP_LOGD(TAG, "Received: %s", buffer_.c_str());
      
      // Parse JSON
      DynamicJsonDocument json_doc(1024);
      auto error = deserializeJson(json_doc, buffer_);
      if (error) {
        ESP_LOGW(TAG, "JSON parsing error: %s", error.c_str());
      } else {
        JsonObject root = json_doc.as<JsonObject>();
        for (const auto &sensor_info : this->sensors_) {
          const char *json_key = sensor_info.json_key.c_str();
          if (root.containsKey(json_key)) {
            float value = root[json_key].as<float>();
            sensor_info.sensor->publish_state(value);
            ESP_LOGD(TAG, "Published sensor: %s -> %.2f", json_key, value);
          }
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
  this->write_str(send_json);
  this->write_str("\n");

  ESP_LOGD(TAG, "Sent command: %s", send_json);
}

}  // namespace uart_centralna
}  // namespace esphome
 