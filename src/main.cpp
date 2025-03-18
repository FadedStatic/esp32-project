#include <Arduino.h>

#include <cstdint>
#include <array>
#include <map>
#include <vector>
#pragma pack(push, 1)  // Save previous alignment and set byte alignment

enum pin_resolving : std::uint8_t {
  START = 34, // these two pins are designated input-only
  GUITAR = 39, // not a waste
  POTENTIOMETER = 36,
  RED_1 = 25,
  GREEN_1 = 33,
  BLUE_1 = 32,
  BLUE_2 = 26,
  GREEN_2 = 27,
  RED_2 = 14,
  BLUE_3 = 12,
  GREEN_3 = 13,
  RED_3 = 4,
  BLUE_4 = 16,
  GREEN_4 = 17,
  RED_4 = 22,
  RED_AUX_1 = 18,
  RED_AUX_2 = 21,
  YELLOW_AUX = 19,
  PIN_ALL_RGB = 0x90, // not a real pin, more like an optimization here.
};

const std::array<std::pair<std::uint8_t, std::uint32_t>, 18> pin_init = {{
  { START,  INPUT },
  { GUITAR, INPUT },
  { GREEN_1, OUTPUT},
  { RED_1, OUTPUT},
  { BLUE_1, OUTPUT},
  { GREEN_2, OUTPUT},
  { RED_2, OUTPUT},
  { BLUE_2, OUTPUT},
  { GREEN_3, OUTPUT},
  { RED_3, OUTPUT},
  { BLUE_3, OUTPUT},
  { GREEN_4, OUTPUT},
  { RED_4, OUTPUT},
  { BLUE_4, OUTPUT},
  { RED_AUX_1, OUTPUT},
  { RED_AUX_2, OUTPUT},
  { YELLOW_AUX, OUTPUT},
  { POTENTIOMETER, INPUT}
}};

constexpr std::uint8_t resolution = 4; // changes n times over timespan

struct pulse_event {
  std::uint32_t time;
  std::uint16_t duration;
  std::uint8_t pin;

  constexpr pulse_event(std::uint32_t t, std::uint16_t d, std::uint8_t p)
    : time(t), duration(d), pin(p) {}
};

struct rgb_event {
  std::uint32_t time;
  std::uint16_t duration;
  std::uint8_t red, green, blue;

  constexpr rgb_event(std::uint32_t t, std::uint16_t d, std::uint8_t r, std::uint8_t g, std::uint8_t b)
    : time(t), duration(d), red(r), green(g), blue(b) {}
};

struct event_init {
  union {
    pulse_event pulse;
    rgb_event rgb;
  } v;

  std::uint8_t type;

  constexpr event_init(const pulse_event& pulse_) : v{.pulse = pulse_}, type(0) {}
  constexpr event_init(const rgb_event& rgb_) : v{.rgb = rgb_}, type(1) {}
};

struct phys_event {
  std::uint16_t delay;
  std::uint32_t data;
};

// crazy optimization, it used to be a LOT of containers but I had the idea to flatten it.
std::vector<phys_event> queue;

constexpr std::array<event_init,77> event_inits = {
    event_init{pulse_event{0, 130, RED_AUX_1}},
    event_init{pulse_event{130, 130, RED_AUX_2}},
    event_init{pulse_event{260, 130, RED_AUX_1}},
    event_init{pulse_event{390, 130, RED_AUX_2}},
    event_init{pulse_event{520, 130, RED_AUX_1}},
    event_init{pulse_event{650, 130, RED_AUX_2}},
    event_init{pulse_event{780, 130, RED_AUX_1}},
    event_init{pulse_event{910, 130, RED_AUX_2}},
    event_init{pulse_event{1040, 130, RED_AUX_1}},
    event_init{pulse_event{1170, 130, RED_AUX_2}},
    event_init{pulse_event{1300, 130, RED_AUX_1}},
    event_init{pulse_event{1430, 130, RED_AUX_2}},
    event_init{pulse_event{1560, 130, RED_AUX_1}},
    event_init{pulse_event{1690, 130, RED_AUX_2}},
    event_init{pulse_event{1820, 130, RED_AUX_1}},
    event_init{pulse_event{1950, 130, RED_AUX_2}},
    event_init{pulse_event{2080, 130, RED_AUX_1}},
    event_init{pulse_event{2210, 130, RED_AUX_2}},
    event_init{pulse_event{2340, 130, RED_AUX_1}},
    event_init{pulse_event{2470, 130, RED_AUX_2}},
    event_init{pulse_event{2600, 130, RED_AUX_1}},
    event_init{pulse_event{2730, 130, RED_AUX_2}},
    event_init{pulse_event{2860, 130, RED_AUX_1}},
    event_init{pulse_event{2990, 130, RED_AUX_2}},
    event_init{pulse_event{3120, 130, RED_AUX_1}},
    event_init{pulse_event{3250, 130, RED_AUX_2}},
    event_init{pulse_event{3380, 130, RED_AUX_1}},
    event_init{pulse_event{3510, 130, RED_AUX_2}},
    event_init{pulse_event{3640, 130, RED_AUX_1}},
    event_init{pulse_event{3770, 130, RED_AUX_2}},
    event_init{pulse_event{3900, 130, RED_AUX_1}},
    event_init{pulse_event{4030, 130, RED_AUX_2}},
    event_init{pulse_event{4160, 130, RED_AUX_1}},
    event_init{pulse_event{4290, 130, RED_AUX_2}},
    event_init{pulse_event{4420, 130, RED_AUX_1}},
    event_init{pulse_event{4550, 130, RED_AUX_2}},
    event_init{pulse_event{4680, 130, RED_AUX_1}},
    event_init{pulse_event{4810, 130, RED_AUX_2}},
    event_init{pulse_event{4940, 130, RED_AUX_1}},
    event_init{pulse_event{5070, 130, RED_AUX_2}},
    event_init{pulse_event{5200, 130, RED_AUX_1}},
    event_init{pulse_event{5330, 130, RED_AUX_2}},
    event_init{pulse_event{5460, 130, RED_AUX_1}},
    event_init{pulse_event{5590, 130, RED_AUX_2}},
    event_init{pulse_event{5720, 130, RED_AUX_1}},
    event_init{pulse_event{5850, 130, RED_AUX_2}},
    event_init{pulse_event{5980, 130, RED_AUX_1}},
    event_init{pulse_event{6110, 130, RED_AUX_2}},
    event_init{pulse_event{6240, 130, RED_AUX_1}},
    event_init{pulse_event{6370, 130, RED_AUX_2}},
    event_init{pulse_event{6500, 130, RED_AUX_1}},
    event_init{pulse_event{6630, 130, RED_AUX_2}},
    event_init{pulse_event{6760, 130, RED_AUX_1}},
    event_init{pulse_event{6890, 130, RED_AUX_2}},
    event_init{pulse_event{7020, 130, RED_AUX_1}},
    event_init{pulse_event{7150, 130, RED_AUX_2}},
    event_init{pulse_event{7280, 130, RED_AUX_1}},
    event_init{pulse_event{7410, 130, RED_AUX_2}},
    event_init{pulse_event{7540, 130, RED_AUX_1}},
    event_init{pulse_event{7670, 130, RED_AUX_2}},
    event_init{pulse_event{7800, 130, RED_AUX_1}},
    event_init{pulse_event{7930, 130, RED_AUX_2}},
    event_init{pulse_event{8060, 130, RED_AUX_1}},
    event_init{pulse_event{8190, 130, RED_AUX_2}},
    event_init{pulse_event{8320, 130, RED_AUX_1}},
    event_init{pulse_event{8450, 130, RED_AUX_2}},
    event_init{pulse_event{8580, 130, RED_AUX_1}},
    event_init{pulse_event{8710, 130, RED_AUX_2}},
    event_init{pulse_event{8840, 130, RED_AUX_1}},
    event_init{pulse_event{8970, 130, RED_AUX_2}},
    event_init{pulse_event{9100, 130, RED_AUX_1}},
    event_init{pulse_event{9230, 130, RED_AUX_2}},
    event_init{pulse_event{9360, 130, RED_AUX_1}},
    event_init{pulse_event{9490, 130, RED_AUX_2}},
    event_init{pulse_event{9620, 130, RED_AUX_1}},
    event_init{pulse_event{9750, 130, RED_AUX_2}},
    event_init{pulse_event{9880, 130, RED_AUX_1}},
};

#define SET_PIN_COLOR(pin, red, green, blue) (\
((pin & 0xFF) << 24) | ((red & 0xFF) << 16) | ((green & 0xFF) << 8) | (blue & 0xFF))
#define SET_PIN_VALUE(pin, value) SET_PIN_COLOR(pin, value, 0, 0)
#define GET_PIN(data)      ((data >> 24) & 0xFF)
#define GET_RED(data)      ((data >> 16) & 0xFF)
#define GET_VALUE GET_RED
#define GET_GREEN(data)    ((data >> 8) & 0xFF)
#define GET_BLUE(data)     (data & 0xFF)

void add_event(const std::uint32_t data, const std::uint32_t abs_time) {
  std::uint32_t accumulatedTime = 0;
  auto it = queue.begin();

  for (; it != queue.end(); ++it) {
    if (accumulatedTime + it->delay >= abs_time) {
      break;
    }
    accumulatedTime += it->delay;
  }

  const std::uint16_t new_delta = abs_time - accumulatedTime;

  it = queue.insert(it, {new_delta, data});

  if ((it + 1) != queue.end()) {
    (it + 1)->delay -= new_delta;
  }
}

void start_sequence() {
  // iterate over queue with an iterator
  for (
  auto it = queue.begin();
  it != queue.end();
  ++it
  ) {
    if (!digitalRead(GUITAR)) {
      for (const auto& pin : pin_init) {
        if (pin.second== OUTPUT) {
          analogWrite(pin.first, 0);
        }
      }
      break;
    }
    const auto pin = GET_PIN(it->data);
    if (pin == PIN_ALL_RGB) {
      const std::uint8_t red = GET_RED(it->data);
      const std::uint8_t green = GET_GREEN(it->data);
      const std::uint8_t blue = GET_BLUE(it->data);
      // it's horrible but it's fast.
      analogWrite(RED_1, red);
      analogWrite(GREEN_1, green);
      analogWrite(BLUE_1, blue);
      analogWrite(RED_2, red);
      analogWrite(GREEN_2, green);
      analogWrite(BLUE_2, blue);
      analogWrite(RED_3, red);
      analogWrite(GREEN_3, green);
      analogWrite(BLUE_3, blue);
      analogWrite(RED_4, red);
      analogWrite(GREEN_4, green);
      analogWrite(BLUE_4, blue);
    }
    else {
      analogWrite(pin, GET_VALUE(it->data));
    }
    // check if next
    if (it + 1 != queue.end()) {
      delay((it+1)->delay);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  // Initialize the pins
  for (const auto& [pin_number, pin_mode] : pin_init) {
    pinMode(pin_number, pin_mode);
  }

  for (const auto& event : event_inits) {
    switch (event.type) {
      case 0:
        for (int i = 0; i <= event.v.pulse.duration; i+= (event.v.pulse.duration / resolution)) {
          const double mult = static_cast<double>(i) / event.v.pulse.duration;
          add_event(SET_PIN_VALUE(event.v.pulse.pin, static_cast<uint8_t>(mult * 255)), event.v.pulse.time + i);
        }
        add_event(SET_PIN_VALUE(event.v.pulse.pin, 0), event.v.pulse.time + event.v.pulse.duration + 1);
        break;
      case 1:
        for (int i = 0; i <= event.v.rgb.duration; i+= (event.v.rgb.duration / resolution)) {
          const double mult = static_cast<double>(i) / event.v.rgb.duration;
          add_event(SET_PIN_COLOR(PIN_ALL_RGB, static_cast<uint8_t>(mult * event.v.rgb.red), static_cast<uint8_t>(mult * event.v.rgb.green), static_cast<uint8_t>(mult * event.v.rgb.blue)), event.v.rgb.time + i);
        }
      add_event(SET_PIN_COLOR(PIN_ALL_RGB, 0, 0, 0), event.v.rgb.time + event.v.rgb.duration + 1);
        break;
      default:break;
    }
  }
  digitalWrite(2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  if (!analogRead(START)) {
    start_sequence();
  }
}
