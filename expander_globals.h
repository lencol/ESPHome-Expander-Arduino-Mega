#pragma once

// Krok 1: wymuś kompilację klas APE przed includowaniem arduino_port_expander.h
#define APE_BINARY_OUTPUT
#define APE_BINARY_SENSOR

// Krok 2: includuj plik z definicją ArduinoPortExpander
#include "arduino_port_expander.h"

// Krok 3: globalny wskaźnik - typ jest już znany
ArduinoPortExpander *global_expander = nullptr;

// WAŻNE: Arduino ma delay(10000) w setup() - czeka 10 sekund przed startem.
// Domyślny timeout w ArduinoPortExpander to tylko 5 sekund - ESP odpuszcza
// zanim Arduino w ogóle wystartuje! Wydłużamy timeout do 15 sekund.
// Nadpisujemy metodę setup() przez dziedziczenie.
class ArduinoPortExpanderPatched : public ArduinoPortExpander {
public:
  ArduinoPortExpanderPatched(I2CBus *bus, uint8_t address, bool vref_default = false)
    : ArduinoPortExpander(bus, address, vref_default) {}
  void setup() override {
    this->configure_timeout_ = millis() + 15000; // 15s zamiast 5s
  }
};
