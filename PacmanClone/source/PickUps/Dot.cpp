#include "PacmanCore.h"
#include "Dot.h"
#include "Event\EventBroker.h"

void Dot::OnPickUp()
{
    EventBroker::OnDotEaten.Invoke();
    bIsEnabled = false;
}
