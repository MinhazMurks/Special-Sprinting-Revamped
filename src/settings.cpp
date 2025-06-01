#include "settings.h"
#include <SKSE/Logger.h>

#include "hooks.h"
#include "SimpleIni.h"


namespace Settings
{
    void LoadSettings()
    {
        constexpr auto path = L"Data/SKSE/Plugins/Special-Sprinting-Revamped/Settings.ini";
        std::wstring ws(path);
        std::string str(ws.begin(), ws.end());

        CSimpleIniA ini;
        ini.SetUnicode();
        SI_Error error = ini.LoadFile(path);

        SKSE::log::info("Loading settings from {}: {}", str, error);

        if (error < 0)
        {
            SKSE::log::error("Failed to load settings file!");
            fullToggleModeEnabled = true;
            variableMoveSpeedEnabled = true;
            return;
        }

        toggleEnabled = ini.GetBoolValue("ToggleOptions", "ToggleEnabled", true);
        fullToggleModeEnabled = ini.GetBoolValue("ToggleOptions", "FullToggleModeEnabled", true);
        sprintAvailableInitially = ini.GetBoolValue("ToggleOptions", "SprintAvailableInitially", false);

        variableMoveSpeedEnabled = ini.GetBoolValue("VariableSpeedOptions", "VariableMoveSpeedEnabled", true);
        sprintActivationThreshold = ini.GetDoubleValue("VariableSpeedOptions", "SprintActivationThreshold", 0.9);

        sprintActivationThreshold = std::max(0.1, sprintActivationThreshold);
        sprintActivationThreshold = std::min(1.2, sprintActivationThreshold);

        Hooks::isSprintDown = sprintAvailableInitially;

        SKSE::log::info("FullToggleModeEnabled: {}", fullToggleModeEnabled);
        SKSE::log::info("VariableMoveSpeedEnabled: {}", variableMoveSpeedEnabled);

        SKSE::log::info("Settings loaded!");
    }
}
