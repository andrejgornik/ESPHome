#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace uart_centralna {

class MyCustomUARTComponent : public uart::UARTDevice, public Component {
 public:
  void setup() override {}
  void loop() override;
  void dump_config() override;  // Declaration only

 protected:
  std::string buffer_;
};

}  // namespace uart_centralna
}  // namespace esphome
