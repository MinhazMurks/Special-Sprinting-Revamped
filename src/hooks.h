#pragma once
namespace Hooks
{
    inline bool isSprintDown;

    class SprintHook
    {
    public:
        static void Hook()
        {

            REL::Relocation<std::uintptr_t> sprintVTable(RE::VTABLE_SprintHandler[0]);
            sprintVTable.write_vfunc(0x4, ProcessButton);
        }

    private:
        static void ProcessButton(RE::SprintHandler* a_this, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data);
    };

    class MovementHook
    {
    public:
        static void Hook()
        {
            REL::Relocation<std::uintptr_t> MovementHandlerVtbl{ RE::VTABLE_MovementHandler[0] };
            _ProcessThumbstick = MovementHandlerVtbl.write_vfunc(0x2, ProcessThumbstick);
            _ProcessButton = MovementHandlerVtbl.write_vfunc(0x4, ProcessButton);
        }

    private:
        static void ProcessThumbstick(RE::MovementHandler* a_this, RE::ThumbstickEvent* a_event, RE::PlayerControlsData* a_data);
        static void ProcessButton(RE::MovementHandler* a_this, RE::ButtonEvent* a_event, RE::PlayerControlsData* a_data);

        static inline REL::Relocation<decltype(ProcessThumbstick)> _ProcessThumbstick;
        static inline REL::Relocation<decltype(ProcessButton)> _ProcessButton;
    };

    void Install();
}