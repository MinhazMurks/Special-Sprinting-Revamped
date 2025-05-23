#pragma once

#include <cstdint>
#include <RE/B/BSTEvent.h>
#include <RE/M/MenuOpenCloseEvent.h>
#include <RE/P/PlayerCharacter.h>
#include <RE/U/UI.h>

namespace Events
{

    void FlashHudMenuMeter(std::uint32_t a_meter);

    class MenuOpenCloseEventHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
    {
    public:
        RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_dispatcher) override
        {
            RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();

            if (a_event && a_event->opening && a_event->menuName != "LootMenu" && player->GetPlayerRuntimeData().playerFlags.isSprinting)
            {
                // Menu was opened, stop sprinting
                player->GetPlayerRuntimeData().playerFlags.isSprinting = false;
            }

            return RE::BSEventNotifyControl::kContinue;
        }
    };

    inline MenuOpenCloseEventHandler g_menuOpenCloseEventHandler;

    void AddListeners(RE::UI* ui);
}
