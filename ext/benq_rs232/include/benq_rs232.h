#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/switch/switch.h"

#include <string>
#include <cctype>
#include <cstring>

namespace esphome {
namespace benq_rs232 {

class BenqRs232;  // forward declare parent for the switch

class BenqPowerSwitch : public switch_::Switch, public Component {
 public:
  void set_parent(BenqRs232 *parent) { parent_ = parent; }
  void set_optimistic(bool optimistic) { optimistic_ = optimistic; }

 protected:
  void write_state(bool state) override;

  BenqRs232 *parent_{nullptr};
  bool optimistic_{true};
};

class BenqRs232 : public PollingComponent, public uart::UARTDevice {
 public:
  BenqRs232() = default;

  void set_raw(text_sensor::TextSensor *raw) { raw_ = raw; }
  void set_power_state(text_sensor::TextSensor *power_state) { power_state_ = power_state; }
  void set_power_switch(BenqPowerSwitch *sw) { power_switch_ = sw; }

  void setup() override {
    // Nothing needed yet
  }

  void update() override {
    // Ask projector for power status
    static const char cmd[] = "\r*pow=?#\r";
    this->write_array(reinterpret_cast<const uint8_t *>(cmd), sizeof(cmd) - 1);
  }

  void send_power(bool on) {
    // BenQ protocol uses lowercase in many docs; projector is case-insensitive.
    const char *cmd = on ? "\r*pow=on#\r" : "\r*pow=off#\r";
    this->write_array(reinterpret_cast<const uint8_t *>(cmd), std::strlen(cmd));
  }

  void loop() override {
    while (this->available()) {
      char c = static_cast<char>(this->read());

      // End of message
      if (c == '\n' || c == '\r' || c == '#') {
        if (!line_.empty()) {
          // Publish raw response
          if (raw_ != nullptr) {
            raw_->publish_state(line_);
          }

          // Parse state
          parse_power_(line_);
          line_.clear();
        }
        continue;
      }

      // Keep printable chars only
      if (c >= 32 && c <= 126) {
        // Safety: avoid runaway buffering if the device spews without terminators
        if (line_.size() < kMaxLineLen) {
          line_.push_back(c);
        }
      }
    }
  }

 protected:
  void parse_power_(const std::string &line) {
    std::string s = line;

    // Uppercase
    for (auto &ch : s) {
      ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    }

    bool has_on = (s.find("POW=ON") != std::string::npos) || (s.find("POW=1") != std::string::npos);
    bool has_off = (s.find("POW=OFF") != std::string::npos) || (s.find("POW=0") != std::string::npos);

    if (!has_on && !has_off) {
      return;
    }

    if (power_state_ != nullptr) {
      power_state_->publish_state(has_on ? "ON" : "OFF");
    }

    if (power_switch_ != nullptr) {
      power_switch_->publish_state(has_on);
    }
  }

  static constexpr size_t kMaxLineLen{96};

  text_sensor::TextSensor *raw_{nullptr};
  text_sensor::TextSensor *power_state_{nullptr};
  BenqPowerSwitch *power_switch_{nullptr};

  std::string line_;
};

// ---- Inline implementations that need full class definitions ----

inline void BenqPowerSwitch::write_state(bool state) {
  if (parent_ != nullptr) {
    parent_->send_power(state);
  }

  // If optimistic, reflect immediately; otherwise wait for RS232 poll/response
  if (optimistic_) {
    this->publish_state(state);
  }
}

}  // namespace benq_rs232
}  // namespace esphome
