#include "PacmanCore.h"
#include "EventBroker.h"

Event<> EventBroker::OnDotEaten;
Event<> EventBroker::OnCookieEaten;
Event<> EventBroker::OnFruitEaten;