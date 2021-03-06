#include <Arduino.h>

#ifndef FV1_H
#define FV1_H

class FV1
{
    private:
        const uint8_t c_pot0Pin = 14; // PWM pin connected to the P0 input, to be set
        const uint8_t c_pot1Pin = 13; // PWM pin connected to the P1 input, to be set
        const uint8_t c_pot2Pin = 12; // PWM pin connected to the P2 input, to be set

        const uint8_t c_s0Pin = 16; // pin connected to the S0 input
        const uint8_t c_s1Pin = 17; // pin connected to the S1 input
        const uint8_t c_s2Pin = 18; // pin connected to the S2 input

    public:
        /**
         * @brief Setup the µC's pins
         * 
         */
        void FV1Setup();

        /**
         * @brief Sends program changes to the FV1's S0/1/2 inputs
         * 
         * @param program 
         */
        void sendProgramChange(uint8_t program);

        /**
         * @brief Sends a PWM pulse to the FV1's P0 input
         * 
         * @param value 
         */
        void sendPot0Value(int value);

        /**
         * @brief Sends a PWM pulse to the FV1's P1 input
         * 
         * @param value 
         */
        void sendPot1Value(int value);

        /**
         * @brief Sends a PWM pulse to the FV1's P2 input
         * 
         * @param value 
         */
        void sendPot2Value(int value);
};

#endif