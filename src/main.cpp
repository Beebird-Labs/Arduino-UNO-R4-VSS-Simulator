#include <Arduino.h>

// Phase-Continuous VSS Simulator
// Target: Arduino Uno R4
// Output: Pin 7 (Update to your wiring)

const int VSS_PIN = 7;
const float HZ_PER_MPH = 1.139f;
const float MAX_MPH = 120.0f;
const int MIN_LOOP_MS = 15000;
const int MAX_LOOP_MS = 45000;

// State tracking for the sweep
float current_mph = 0.0f;
unsigned long cycle_start_ms = 0;
long current_duration_ms = 30000;
bool sweeping_up = true;

// State tracking for the phase-continuous wave
uint32_t last_toggle_us = 0;
bool pin_state = false;

void setup()
{
  pinMode(VSS_PIN, OUTPUT);
  Serial.begin(115200);

  // Seed random from a floating analog pin
  randomSeed(analogRead(A0));

  cycle_start_ms = millis();

  // A full cycle is Up + Down. Divide duration by 2 for one leg.
  current_duration_ms = random(MIN_LOOP_MS, MAX_LOOP_MS + 1) / 2;

  Serial.println("Phase-Continuous VSS Simulator Started");
}

void loop()
{
  unsigned long now_ms = millis();
  unsigned long elapsed_ms = now_ms - cycle_start_ms;

  // ---------------------------------------------------------
  // 1. Manage the Ramp State (No Delays)
  // ---------------------------------------------------------
  if (elapsed_ms >= current_duration_ms)
  {
    cycle_start_ms = now_ms;
    elapsed_ms = 0;
    sweeping_up = !sweeping_up;

    // Pick a new random duration for the next cycle ONLY when we hit 0 MPH
    if (sweeping_up)
    {
      long full_cycle = random(MIN_LOOP_MS, MAX_LOOP_MS + 1);
      current_duration_ms = full_cycle / 2;
      Serial.print("New Cycle Duration: ");
      Serial.print(full_cycle / 1000);
      Serial.println("s");
    }
  }

  // Calculate the target speed natively as a float
  float progress = (float)elapsed_ms / (float)current_duration_ms;
  if (sweeping_up)
  {
    current_mph = progress * MAX_MPH;
  }
  else
  {
    current_mph = MAX_MPH - (progress * MAX_MPH);
  }

  // ---------------------------------------------------------
  // 2. Generate the Waveform (Phase-Continuous)
  // ---------------------------------------------------------
  if (current_mph > 0.5f)
  {
    // Calculate how many microseconds a half-wave should last
    float current_hz = current_mph * HZ_PER_MPH;
    uint32_t half_period_us = (uint32_t)(1000000.0f / (current_hz * 2.0f));

    uint32_t now_us = micros();

    // If enough time has passed, toggle the pin
    if (now_us - last_toggle_us >= half_period_us)
    {
      last_toggle_us = now_us;
      pin_state = !pin_state;
      digitalWrite(VSS_PIN, pin_state ? HIGH : LOW);
    }
  }
  else
  {
    // Complete stop
    digitalWrite(VSS_PIN, LOW);
    pin_state = false;
    last_toggle_us = micros(); // Keep the timer "primed" for a clean launch
  }
}