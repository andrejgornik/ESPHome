#include "esphome.h"

namespace UART_centralna {  // Ensure the namespace matches
  class MyCustomUARTComponent : public Component, public UARTDevice {
  public:
    MyCustomUARTComponent(UARTComponent *parent) : UARTDevice(parent) {}

    void loop() override {
      while (available()) {
        char c = read();
        buffer_ += c;

        if (c == '\n') {
          ESP_LOGD("custom_uart", "Received: %s", buffer_.c_str());
          buffer_.clear();
        }
      }
    }

  protected:
    std::string buffer_;
  };
}  // namespace UART_centralna
