#pragma once

namespace Settings
{
    inline bool toggleEnabled;
    inline bool fullToggleModeEnabled;
    inline bool sprintAvailableInitially;

    inline bool variableMoveSpeedEnabled;
    inline double sprintActivationThreshold;

    void LoadSettings();
}