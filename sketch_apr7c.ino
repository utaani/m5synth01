/**
 * @file piano.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief Unit Synth Piano Example
 * @version 0.2
 * @date 2024-04-07
 *
 *
 * @Hardwares: M5Core + Unit Synth
 * @Platform Version: Arduino M5Stack Board Manager v2.1.0
 * @Dependent Library:
 * M5UnitSynth: https://github.com/m5stack/M5Unit-Synth
 */

#include "M5NanoC6.h"
#include "M5UnitSynth.h"

M5UnitSynth synth;
char codefg = 'C';
unsigned long lastc;


void setup() {
    Serial.begin(115200);
    Serial.println("Unit Synth Piano");
    synth.begin(&Serial1, UNIT_SYNTH_BAUD, 1, 2);
    synth.setInstrument(0, 0, GrandPiano_1);  // synth piano 1
    pinMode(GPIO_NUM_9, INPUT);  // Btn

}

void loop() {
  static int8_t oldBtn = HIGH;
  int8_t btnState = digitalRead(GPIO_NUM_9);

  if (oldBtn != btnState) {
    oldBtn = btnState;
    if (btnState) {
      // LOW -> HIGH
      synth.setAllNotesOff(0);
    } else {
      // HIGH -> LOW
      if (codefg == 'C') {
        // play C
        synth.setNoteOn(0, 60, 127);
        synth.setNoteOn(0, 64, 127);
        synth.setNoteOn(0, 67, 127);
        lastc = millis();
        codefg = 'G';
      }
      else if (codefg == 'G') {
        if (millis() - lastc >= 5000) {
          // play C
          synth.setNoteOn(0, 60, 127);
          synth.setNoteOn(0, 64, 127);
          synth.setNoteOn(0, 67, 127);
          lastc = millis();
          codefg = 'G';
        }
        else {
          // play G
          synth.setNoteOn(0, 59, 127);
          synth.setNoteOn(0, 62, 127);
          synth.setNoteOn(0, 67, 127);
          codefg = 'C';
        }
      }
      else {
        synth.setAllNotesOff(0);
      }

    }
  }
  delay(1);
}