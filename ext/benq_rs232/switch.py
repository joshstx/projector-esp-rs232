import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import CONF_ID

from . import benq_rs232_ns, BenqRs232  # main component class

CONF_BENQ_RS232_ID = "benq_rs232_id"
CONF_OPTIMISTIC = "optimistic"

BenqPowerSwitch = benq_rs232_ns.class_("BenqPowerSwitch", switch.Switch, cg.Component)

CONFIG_SCHEMA = switch.switch_schema(BenqPowerSwitch).extend(
    {
        cv.Required(CONF_BENQ_RS232_ID): cv.use_id(BenqRs232),
        cv.Optional(CONF_OPTIMISTIC, default=True): cv.boolean,
    }
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    await cg.register_component(var, config)
    await switch.register_switch(var, config)

    parent = await cg.get_variable(config[CONF_BENQ_RS232_ID])
    cg.add(var.set_parent(parent))
    cg.add(var.set_optimistic(config[CONF_OPTIMISTIC]))
    cg.add(parent.set_power_switch(var))
