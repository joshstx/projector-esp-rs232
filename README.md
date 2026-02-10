+code-14-cNormalh1+h1-4**BenQ Projector RS-232 (ESPHome external
component)**

+code-14-c+p-5An ESPHome external component that:

+code-14-cul-7

-   polls a BenQ projector over RS-232 for power status

+code-14-cul-7

-   exposes the raw reply and power state as entities

+code-14-cul-7

-   provides a **native** Home Assistant switch entity to turn the
    projector on/off (no HA template switch)

+code-14-cNormalh2+h2-9**Wiring**

+code-14-c+p-5Use a MAX3232 (or equivalent) TTL\<-\>RS232 level shifter
between the ESP32 UART and the projector RS-232 port.

+code-14-cNormalh2+h2-9**Install / Use**

+code-14-c+p-5

1.  Exctract file contents to the ESPHome folder in Home Assistant

+code-14-c+p-5

1.  Open ESPHome Web UI in the ESPHome App (previously know as Add-Ons)

+code-14-c+p-5

1.  Assemble and add the ESP32 device into ESPHome

+code-14-c+p-5

1.  If you do not already have a secrets.yaml in your ESPHome update and
    rename the "secrets.yaml.example" to simply "secrets.yaml"

+code-14-c+p-5

1.  Validate the yaml in ESPhome

+code-14-c+p-5

1.  Install the software onto the device

+code-14-c+p-5See benq.yaml for a complete working example.

+code-14-cNormalh2+h2-9**Notes**

+code-14-cul-7

-   optimistic: true updates the switch state immediately when you press
    it.\
    \
    If you prefer the switch to only update after the next RS-232
    reply/poll, set optimistic: false.

+code-14-cul-7

-   I do not need to change the source or any other commands so I did
    not add any other commands.

+code-14-cul-7

-   AI was used as a coding assistant, but the project was developed,
    tested, and integrated manually.

+code-14-cNormalh2+h2-9**License**

+code-14-c+p-5MIT (see LICENSE).

+code-14-c+p-5
