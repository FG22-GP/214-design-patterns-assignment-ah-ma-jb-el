#pragma once

#include "PacmanCore.h"
#include "Event.h"

class EventBroker
{
public:
	static Event<> OnDotEaten;
	static Event<> OnCookieEaten;
	static Event<> OnFruitEaten;
};