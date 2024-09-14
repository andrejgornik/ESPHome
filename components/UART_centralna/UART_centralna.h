#include "esphome.h"

namespace CustomUART {
  class MyUARTComponent : public Component, public UARTDevice {
  public:
    MyUARTComponent(UARTComponent *parent) : UARTDevice(parent) {}

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
}  // namespace CustomUART
