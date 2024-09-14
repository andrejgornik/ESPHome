#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace uart_centralna {

class MyCustomUARTComponent : public uart::UARTDevice, public Component {
 public:
  void setup() override {}
  void loop() override {
    while (available()) {
      char c = read();
      buffer_ += c;

      if (c == '\n') {
        ESP_LOGD("uart_centralna", "Received: %s", buffer_.c_str());
        buffer_.clear();
      }
    }
  }
  void dump_config() override { ESP_LOGCONFIG(TAG, "UART Centralna Component"); }

 protected:
  std::string buffer_;
};

}  // namespace uart_centralna
}  // namespace esphome
