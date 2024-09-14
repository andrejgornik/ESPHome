#include "esphome/components/uart/uart.h"
#include "esphome/core/component.h"

namespace uart_centralna {  // Use the matching namespace

class MyCustomUARTComponent : public esphome::Component, public esphome::uart::UARTDevice {
 public:
  MyCustomUARTComponent(esphome::uart::UARTComponent *parent) : esphome::uart::UARTDevice(parent) {}

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

 protected:
  std::string buffer_;
};

}  // namespace uart_centralna
