import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

# Set up the dependency
DEPENDENCIES = ["uart"]

# Define the namespace
uart_centralna_ns = cg.esphome_ns.namespace('uart_centralna')
MyCustomUARTComponent = uart_centralna_ns.class_('MyCustomUARTComponent', cg.Component, uart.UARTDevice)

# Configuration schema
CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(MyCustomUARTComponent)})
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)

# Register the component
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
