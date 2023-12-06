#include "PacmanCore.h"
#include "AIState_Base.h"

void AIState_Base::SetMachine(std::shared_ptr<StateMachine_Component> machine)
{
    StateMachine = machine;
}
