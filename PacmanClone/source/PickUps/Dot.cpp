#include "PacmanCore.h"
#include "Dot.h"
#include "Event\EventBroker.h"

int Dot::TotalDots = 0;

void Dot::OnPickUp()
{
    EventBroker::OnDotEaten.Invoke();
    bIsEnabled = false;
}
