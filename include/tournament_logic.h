#ifndef GUARD_TOURNAMENT_LOGIC_H
#define GUARD_TOURNAMENT_LOGIC_H

#include "tournament_opponent.h"

enum TrainerRoaster
{
    ROSTER_GEN1_GYM_LEADERS = 1,
    ROSTER_GEN2_GYM_LEADERS,
    ROSTER_GEN3_GYM_LEADERS,
    ROSTER_GEN4_GYM_LEADERS,
    ROSTER_GEN5_GYM_LEADERS,
};

void ChooseRandomGymLeader(void);
void SetCompleteRosterFlag(void);
void CheckForOpponentDuo(void);
void SetupOpponentGfxId(void);
u32 CheckPartyForTech(void);

enum OpponentID GetCurrentOpponent(void);

extern const u16 gTechniqueFlagUnlocks[];

#endif //GUARD_TOURNAMENT_LOGIC_H
