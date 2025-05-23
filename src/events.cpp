#include "events.h"
#include <RE/U/UI.h>

namespace Events
{
    void AddListeners(RE::UI* ui)
    {
        ui->GetEventSource<RE::MenuOpenCloseEvent>()->AddEventSink(&g_menuOpenCloseEventHandler);
    }
}
