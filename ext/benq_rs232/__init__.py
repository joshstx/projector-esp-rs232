import os

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, text_sensor
from esphome.const import CONF_ID, CONF_UART_ID, CONF_UPDATE_INTERVAL
from esphome.core import CORE

DEPENDENCIES = ["uart", "text_sensor", "switch"]
AUTO_LOAD = ["text_sensor", "switch"]

benq_rs232_ns = cg.esphome_ns.namespace("benq_rs232")
BenqRs232 = benq_rs232_ns.class_("BenqRs232", cg.PollingComponent, uart.UARTDevice)

CONF_RAW = "raw"
CONF_POWER_STATE = "power_state"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(BenqRs232),
            cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
            cv.Optional(CONF_UPDATE_INTERVAL, default="10s"): cv.update_interval,
            cv.Optional(CONF_RAW): text_sensor.text_sensor_schema(),
            cv.Optional(CONF_POWER_STATE): text_sensor.text_sensor_schema(),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    include_dir = os.path.join(CORE.config_dir, "ext", "benq_rs232", "include")
    cg.add_platformio_option("build_flags", [f"-I{include_dir}"])
    cg.add_global(cg.RawStatement('#include "benq_rs232.h"'))

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))

    if CONF_RAW in config:
        raw = await text_sensor.new_text_sensor(config[CONF_RAW])
        cg.add(var.set_raw(raw))

    if CONF_POWER_STATE in config:
        pwr = await text_sensor.new_text_sensor(config[CONF_POWER_STATE])
        cg.add(var.set_power_state(pwr))
