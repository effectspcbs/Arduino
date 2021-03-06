#define DEBUG 1

#include <Arduino.h>

#include "bypass.h"

void Bypass::bypassSetup()
{
    pinMode(c_relayPin, OUTPUT);
    pinMode(c_okPin, OUTPUT),
    pinMode(c_switchPin, INPUT_PULLUP);

    digitalWrite(c_okPin, LOW);
    digitalWrite(c_relayPin, m_bypassState);
}

bool Bypass::bypassPressed()
{
    m_now = millis();

    if (m_now - m_lastPressTime > c_debounceTime) // Debounce
    {
        m_lastPressTime = m_now;   
        return true;
    }
    else
    {
        return false;
    }
    
}

void Bypass::switchRelay()
{
    m_bypassState = !m_bypassState;

    digitalWrite(c_okPin, HIGH);                // OK on
    delay(10);                                  // 5~10 ms depending on the OK
    digitalWrite(c_relayPin, m_bypassState);    // Relay switch
    delay(10);                                  // 5~10 ms depending on the relay
    digitalWrite(c_okPin, LOW);                 // OK off

    #ifdef DEBUG
        Serial.print("Bypass : ");
        Serial.println(m_bypassState);
    #endif
}

uint8_t Bypass::getBypassState()
{
    return m_bypassState;
}

void Bypass::setBypassState(uint8_t state)
{
    m_bypassState = state;
}