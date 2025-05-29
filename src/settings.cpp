#include "settings.h"
#include <SKSE/Logger.h>
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
            fullToggleMode = true;
            variableMoveSpeed = true;
            return;
        }

        fullToggleMode = ini.GetBoolValue("General", "FullToggleMode", true);
        variableMoveSpeed = ini.GetBoolValue("General", "VariableMoveSpeed", true);

        SKSE::log::info("FullToggleMode: {}", fullToggleMode);
        SKSE::log::info("VariableMoveSpeed: {}", variableMoveSpeed);

        SKSE::log::info("Settings loaded!");
    }
}
