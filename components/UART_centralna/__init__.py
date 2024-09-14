# This is an initialization file for the UART_centralna component

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import uart
from esphome.const import CONF_ID

# Define the namespace and class in ESPHome
uart_centralna_ns = cg.esphome_ns.namespace('uart_centralna')
MyCustomUARTComponent = uart_centralna_ns.class_('MyCustomUARTComponent', cg.Component, uart.UARTDevice)

# Define configuration schema (if needed)
CONFIG_SCHEMA = uart.UART_DEVICE_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(MyCustomUARTComponent),
})

# Register the component
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
