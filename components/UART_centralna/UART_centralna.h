#include "esphome.h"

namespace my_custom_uart_component {  // Wrap in a namespace
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
}  // namespace my_custom_uart_component
