#include <Arduino.h>

#ifndef HARDWARE_H
#define HARDWARE_H

/**
 * @brief Interface between the program and the hardware
 */
class Hardware
{
    private:
        //Hardware state
        uint8_t m_bypassState = 0;
        uint8_t m_currentProgram = 0;
        uint8_t m_currentPreset = 0;
        uint8_t m_presetMode = 0;
        bool m_presetSaveMode = false;

        // Current effect parameters
        bool m_effectIsDelay = false;
        uint16_t m_effectMinInterval = 0;
        uint16_t m_effectMaxInterval = 0;
        bool m_effectHasTapEnabled = false;
        bool m_effectHasPot0Enabled = false;
        bool m_effectHasPot1Enabled = false;
        bool m_effectHasPot2Enabled = false;
        bool m_effectHasPot3Enabled = false;

        // Stored state
        uint8_t m_tapState = 0;
        uint8_t m_divState = 0;
        uint8_t m_divValue = 0;
        uint16_t m_interval = 0;
        uint16_t m_divInterval = 0;

        // Hardware triggers
        bool m_bypassSwitchPress = false;
        bool m_selectorMove = false;
        bool m_selectorSwitchPress = false;
        bool m_selectorSwitchLongPress = false;
        bool m_selectorSwitchRelease = false;
        bool m_tapSwitchPress = false;
        bool m_tapSwitchLongPress = false;
        bool m_pot0Turned = false;
        bool m_pot1Turned = false;
        bool m_pot2Turned = false;
        bool m_pot3Turned = false;

        // Tap logic
        uint32_t m_firstTapTime = 0;
        uint32_t m_lastTapTime = 0;
        uint8_t m_timesTapped = 0;
        const uint8_t c_maxTaps = 3;
        uint8_t m_tapLedBlinkValue = 0;
        uint8_t m_mappedInterval = 0;
        uint8_t m_mappedDivInterval = 0;

        /**
         * @brief Apply the bypass state
         */
        void turnPedalOnOff();

        /**
         * @brief Calculate the interval
         */
        void calculateInterval();

        /**
         * @brief Calculate the divided interval
         */
        void calculateDivInterval();

        /**
         * @brief Calculate the value of the current interval mapped to 8bits in the relation to the min ad max iterval
         */
        uint8_t getMappedInterval();

        /**
         * @brief Calculate the value of the current divied interval mapped to 8bits in the relation to the min ad max iterval
         */
        uint8_t getMappedDivInterval();

        /**
         * @brief Map the interval to the pot value in relation to the min and max interval
         * 
         * @param value 
         */
        void setIntervalFromPotValue(uint16_t value);

    public:
        /**
         * @brief Setup the hardware devices
         */
        void hardwareSetup();

        /**
         * @brief Initialize the memory and set the midi channel
         */
        void hardwareInitialization();

        /**
         * @brief Restore the last stored pedal state
         */
        void restoreLastState();

        /**
         * @brief Poll the various devices
         */
        void hardwarePoll();

        /**
         * @brief Reset the hardware trigger at the end of a cycle
         */
        void resetTriggers();

        /**
         * @brief Switch the bypass state
         */
        void bypassSwitch();

        /**
         * @brief Change between preset and program mode
         */
        void presetModeSwitch();

        /**
         * @brief Load a program from memory
         */
        void loadProgram();

        /**
         * @brief Load a preset from memory
         */
        void loadPreset();

        /**
         * @brief Save the current state as a preset
         */
        void savePreset();

        /**
         * @brief Tap logic
         */
        void processTap();

        /**
         * @brief Div logic
         */
        void processDiv();

        /**
         * @brief Blink tap led to the interval
         */
        void blinkTapLed();

        /**
         * @brief Pot0 logic
         */
        void processPot0();

        /**
         * @brief Pot1 logic
         */
        void processPot1();

        /**
         * @brief Pot2 logic
         */
        void processPot2();

        /**
         * @brief Pot3 logic
         */
        void processPot3();

        /**
         * @brief Get the Current Program object
         * 
         * @return uint8_t 
         */
        uint8_t getCurrentProgram();

        /**
         * @brief Get the Preset Mode object
         * 
         * @return uint8_t 
         */
        uint8_t getPresetMode();

        /**
         * @brief Get the Bypass Switch Press object
         * 
         * @return true 
         * @return false 
         */
        bool getBypassSwitchPress();

        /**
         * @brief Get the Selector Move object
         * 
         * @return true 
         * @return false 
         */
        bool getSelectorMove();

        /**
         * @brief Get the Selector Switch Press object
         * 
         * @return true 
         * @return false 
         */
        bool getSelectorSwitchPress();

        /**
         * @brief Get the Selector Switch Long Press object
         * 
         * @return true 
         * @return false 
         */
        bool getSelectorSwitchLongPress();

        /**
         * @brief Get the Selector Switch Released object
         * 
         * @return true 
         * @return false 
         */
        bool getSelectorSwitchReleased();

        /**
         * @brief Get the Tap Switch Press object
         * 
         * @return true 
         * @return false 
         */
        bool getTapSwitchPress();

        /**
         * @brief Get the Tap Switch Long Press object
         * 
         * @return true 
         * @return false 
         */
        bool getTapSwitchLongPress();

        /**
         * @brief Get the Bypass State object
         * 
         * @return uint8_t 
         */
        uint8_t getBypassState();

        /**
         * @brief Get the Pot0 Turned object
         * 
         * @return true 
         * @return false 
         */
        bool getPot0Turned();

        /**
         * @brief Get the Pot1 Turned object
         * 
         * @return true 
         * @return false 
         */
        bool getPot1Turned();

        /**
         * @brief Get the Pot2 Turned object
         * 
         * @return true 
         * @return false 
         */
        bool getPot2Turned();

        /**
         * @brief Get the Pot3 Turned object
         * 
         * @return true 
         * @return false 
         */
        bool getPot3Turned();
};

#endif