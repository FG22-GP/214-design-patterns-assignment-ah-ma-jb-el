#include "PacmanCore.h"
#include "Cookie.h"
#include "Event\EventBroker.h"

void Cookie::OnPickUp()
{
    EventBroker::OnCookieEaten.Invoke();
    bIsEnabled = false;
}
