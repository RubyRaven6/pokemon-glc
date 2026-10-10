#ifndef GUARD_BATTLE_SWITCH_IN
#define GUARD_BATTLE_SWITCH_IN

#include "constants/battle_switch_in.h"

bool32 DoSwitchInEvents(void);
bool32 TryHazardsOnSwitchIn(enum BattlerId battler, enum Ability ability, enum HoldEffect holdEffect, enum Hazards hazardType);

#endif // GUARD_BATTLE_SWITCH_IN
