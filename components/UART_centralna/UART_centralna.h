#include "esphome.h"

class MyCustomUARTComponent : public Component, public UARTDevice {
 public:
  MyCustomUARTComponent(UARTComponent *parent) : UARTDevice(parent) {}

  void loop() override {
    // Read all available bytes from UART
    while (available()) {
      // Read one byte
      char c = read();
      // Add your custom processing here, e.g., store in a buffer
      buffer_ += c;

      // Optional: Process buffer if a newline is detected
      if (c == '\n') {
        // Log the received line
        ESP_LOGD("custom_uart", "Received: %s", buffer_.c_str());
        // Clear the buffer after processing
        buffer_.clear();
      }
    }
  }

 protected:
  std::string buffer_;
};
