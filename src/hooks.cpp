#include "hooks.h"

#include "settings.h"

namespace Hooks
{
	static bool isSprintDown = false;

	void FlashHudMenuMeter(std::uint32_t a_meter)
	{
		using func_t = decltype(&FlashHudMenuMeter);
		REL::Relocation<func_t> func(REL::ID{ 52845 });
		return func(a_meter);
	}

	void SetSprintForPlayer(RE::PlayerCharacter* player, bool valueToSet)
	{
		if (player->GetPlayerRuntimeData().playerFlags.isSprinting != valueToSet)
		{
			player->GetPlayerRuntimeData().playerFlags.isSprinting = valueToSet;
		}
	}

	void SprintHook::ProcessButton(RE::SprintHandler* a_this, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data)
	{
		RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
		const float stamina = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kStamina);

		if (a_event->IsDown())
		{
			if (stamina > 0.0f)
			{
				isSprintDown = !isSprintDown;
				SetSprintForPlayer(player, isSprintDown);
			}
			else if (stamina == 0.0f)
			{
				// Out of stamina, flash stamina meter
				FlashHudMenuMeter(26);
				SetSprintForPlayer(player, false);
			}
		}
	}

	void MovementHook::ProcessThumbstick(RE::MovementHandler* a_this, RE::ThumbstickEvent* a_event, RE::PlayerControlsData* a_data)
	{
		RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
		const float sumStickValue = abs(a_event->xValue) + abs(a_event->yValue);
		const float stamina = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kStamina);

		if (isSprintDown)
		{
			if (stamina > 0.0f)
			{
				if (sumStickValue > 0.9f && Settings::variableMoveSpeed)
				{
					// If not sprinting, start sprinting
					SetSprintForPlayer(player, true);
				}
				else if (sumStickValue > 0.0 && Settings::variableMoveSpeed)
				{
					SetSprintForPlayer(player, false);
				} else if (sumStickValue <= 0.0f)
				{
					if (!Settings::fullToggleMode)
					{
						isSprintDown = false;
					}

					SetSprintForPlayer(player, false);
				}
			} else
			{
				// Out of stamina, flash stamina meter
				FlashHudMenuMeter(26);
				isSprintDown = false;

				SetSprintForPlayer(player, false);
			}
		}

		// call original function so other plugins can hook this vfunc properly
		_ProcessThumbstick(a_this, a_event, a_data);
	}

	void Install()
	{
		SKSE::log::info("Hooking Movement and Sprint");

		SprintHook::Hook();
		MovementHook::Hook();

		// Force sprint state to sync in every frame
		REL::safe_write(REL::ID{ 40760 }.address() + 0x159, std::uint16_t(0x9090));

		// Skip HUD meter flashing when out of stamina - we handle it ourselves
		REL::safe_write(REL::ID{ 42350 }.address() + 0x350, std::uint8_t(0xEB));

		SKSE::log::info("Hooks Installed");
	}
}
