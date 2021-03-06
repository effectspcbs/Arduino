#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>

#include "selector.h"

void Selector::selectorSetup()
{
    pinMode(c_encoderPinA, INPUT);
    pinMode(c_encoderPinB, INPUT);
    pinMode(c_switchPin, INPUT_PULLUP);
    pinMode(c_latchPin, OUTPUT);

    digitalWrite(c_encoderPinA, HIGH);
    digitalWrite(c_encoderPinB, HIGH);
    digitalWrite(c_latchPin, LOW);

    SPI.begin();
    
}

uint8_t Selector::readRotaryState()
{
    m_lastSelectorState = (digitalRead(c_encoderPinB) << 1) | digitalRead(c_encoderPinA);
    m_selectorState = c_encoderStates[m_selectorState & 0xf][m_lastSelectorState];

    return m_selectorState & 0x30;
}

void Selector::selectorMove()
{
    uint8_t state = readRotaryState();

    if (state == 0x10)
    {
        m_counter --;
        if (m_counter == 255)
        {
            m_counter = 7;
        }
        #ifdef DEBUG
            Serial.print("Selector counter : ");
            Serial.println(m_counter);
        #endif

        m_newProgram = true;
    }
    
    if (state == 0x20)
    {
        m_counter ++;
        if(m_counter == 8)
        {
            m_counter = 0;
        }
        #ifdef DEBUG
            Serial.print("Selector counter : ");
            Serial.println(m_counter);
        #endif

        m_newProgram = true;
    }
}

bool Selector::selectorSwitch()
{
    m_switchState = digitalRead(c_switchPin);
    
    if (m_switchState == LOW 
    && m_now - m_lastSwitchTime > c_debounceTime 
    && m_switchState != m_lastSwitchState)
    {
        m_lastSwitchTime = m_now;
        m_lastSwitchState = m_switchState;

        
    #ifdef DEBUG
        Serial.println("Selector switch");
    #endif

        return true;
    }
    else
    {
        m_lastSwitchState = m_switchState;

        return false;
    }    
}

void Selector::switchPresetMode()
{
    m_presetMode = !m_presetMode;

    #ifdef DEBUG
        Serial.print("Preset mode : ");
        Serial.println(m_presetMode);
    #endif
}

void Selector::lightSelectorLed()
{
    if (m_presetMode == 0)
    {
        shiftReg(1 << m_counter);
        shiftReg(0);
    }
    else
    {
        shiftReg(0);
        shiftReg(1 << m_counter);
    }
    
}

void Selector::shiftReg(uint8_t value)
{
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    digitalWrite(c_latchPin, LOW);
    SPI.transfer(value);
    digitalWrite(c_latchPin, HIGH);
    digitalWrite(c_latchPin, LOW);
    SPI.endTransaction();
}

uint8_t Selector::getPresetMode()
{
    return m_presetMode;
}

void Selector::setPresetMode(uint8_t mode)
{
    m_presetMode = mode;
}

uint8_t Selector::getCounter()
{
    return m_counter;
}

void Selector::setCounter(uint8_t counter)
{
    m_counter = counter;
}
