#define DEBUG 1

#include <Arduino.h>

#include "bypass.h"

void Bypass::bypassSetup()
{
    pinMode(m_relayPin, OUTPUT);
    pinMode(m_okPin, OUTPUT),

    digitalWrite(m_okPin, LOW);
    digitalWrite(m_relayPin, LOW);
}

void Bypass::BypassSwitch(uint8_t state)
{
    digitalWrite(m_okPin, HIGH);                // OK on
    delay(10);                                  // 5~10 ms depending on the OK
    digitalWrite(m_relayPin, state);              // Relay switch
    delay(10);                                  // 5~10 ms depending on the relay
    digitalWrite(m_okPin, LOW);                 // OK off
}
