#include "events.h"
#include "hooks.h"
#include "log.h"
#include "settings.h"

void OnDataLoaded()
{
	RE::UI* ui = RE::UI::GetSingleton();
	Events::AddListeners(ui);
	Settings::LoadSettings();
	Hooks::Install();
	SKSE::log::info("Menu open/close event handler subscribed.");
}

void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kPostLoad:
		break;
	case SKSE::MessagingInterface::kPostPostLoad:
		break;
	case SKSE::MessagingInterface::kPreLoadGame:
		break;
	case SKSE::MessagingInterface::kPostLoadGame:
		break;
	case SKSE::MessagingInterface::kSaveGame:
		break;
	case SKSE::MessagingInterface::kDeleteGame:
		break;
	case SKSE::MessagingInterface::kInputLoaded:;
		break;
	case SKSE::MessagingInterface::kNewGame:
		break;
	case SKSE::MessagingInterface::kDataLoaded:
		SKSE::log::info("Data loaded!");
		OnDataLoaded();
		break;
	}
}

SKSEPluginLoad(const SKSE::LoadInterface *skse) {

    SKSE::Init(skse);
	SetupLog();

    auto messaging = SKSE::GetMessagingInterface();
	if (!messaging->RegisterListener("SKSE", MessageHandler)) {
		return false;
	}
	
    return true;
}