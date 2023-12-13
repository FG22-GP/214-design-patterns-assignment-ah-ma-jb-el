#pragma once

#include "PacmanCore.h"
#include "Event.h"

class EventBroker
{
	//See IPickup.h & .cpp for example usage of events.
	//Use lambda functions, save callback to call RemoveListener with

public:
	static Event<> OnDotEaten;
	static Event<> OnCookieEaten;
	static Event<> OnFruitEaten;
};