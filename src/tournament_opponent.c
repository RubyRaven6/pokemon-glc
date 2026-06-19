#include "global.h"
#include "event_data.h"
#include "event_scripts.h"
#include "tournament_opponent.h"
#include "tournament_logic.h"
#include "constants/event_objects.h"

#define OPPONENT_GFX(graphicsId, ...) { graphicsId, DEFAULT(NUM_OBJ_EVENT_GFX, __VA_ARGS__) }

const struct TournamentOpponent gTournamentOpponents[OPPONENT_COUNT] =
{
    [OPPONENT_NONE] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
    },
    // Gen 1
    [OPPONENT_BROCK] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_ROXANNE),
        .script = EventScript_PWTBattleBrock,
    },
    [OPPONENT_MISTY] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_AQUA_MEMBER_F),
        .script = EventScript_PWTBattleMisty,
    },
    [OPPONENT_LT_SURGE] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_WATTSON),
        .script = EventScript_PWTBattleLtSurge,
    },
    [OPPONENT_ERIKA] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_ANABEL),
        .script = EventScript_PWTBattleErika,
    },
    [OPPONENT_SABRINA] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_HEX_MANIAC),
        .script = EventScript_PWTBattleSabrina,
    },
    [OPPONENT_KOGA_AND_JANINE] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_EXPERT_M, OBJ_EVENT_GFX_EXPERT_F),
        .script = EventScript_PWTBattleKogaJanine,
    },
    [OPPONENT_BLAINE] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_MAGMA_MEMBER_M),
        .script = EventScript_PWTBattleBlaine,
    },
    [OPPONENT_GIOVANNI] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_ARCHIE),
        .script = EventScript_PWTBattleGiovanni,
    },
    // Gen2
    [OPPONENT_FALKNER] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleFalkner,
    },
    [OPPONENT_BUGSY] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleBugsy,
    },
    [OPPONENT_WHITNEY] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleWhitney,
    },
    [OPPONENT_MORTY] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleMorty,
    },
    [OPPONENT_CHUCK] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleChuck,
    },
    [OPPONENT_JASMINE] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleJasmine,
    },
    [OPPONENT_PRYCE] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattlePryce,
    },
    [OPPONENT_CLAIR] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleClair,
    },
    // Gen 3
    [OPPONENT_ROXANNE] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_ROXANNE),
        .script = EventScript_PWTBattleRoxanne,
    },
    [OPPONENT_BRAWLY] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRAWLY),
        .script = EventScript_PWTBattleBrawly,
    },
    [OPPONENT_WATTSON] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_WATTSON),
        .script = EventScript_PWTBattleWattson,
    },
    [OPPONENT_FLANNERY_NUTS] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_FLANNERY),
        .script = EventScript_PWTBattleFlannery,
    },
    [OPPONENT_NORMAN] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_NORMAN),
        .script = EventScript_PWTBattleNorman,
    },
    [OPPONENT_WINONA] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_WINONA),
        .script = EventScript_PWTBattleWinona,
    },
    [OPPONENT_TATE_AND_LIZA] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_TATE, OBJ_EVENT_GFX_LIZA),
        .script = EventScript_PWTBattleTateAndLiza,
    },
    [OPPONENT_JUAN] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_JUAN), // 🐎
        .script = EventScript_PWTBattleJuan,
    },
    // Gen 4
    [OPPONENT_ROARK] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleRoark,
    },
    [OPPONENT_GARDENIA] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleGardenia,
    },
    [OPPONENT_MAYLENE] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleMaylene,
    },
    [OPPONENT_CRASHER_WAKE] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleCrasherWake,
    },
    [OPPONENT_FANTINA] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleFantina,
    },
    [OPPONENT_BYRON] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleByron,
    },
    [OPPONENT_CANDICE_NUTS] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleCandice,
    },
    [OPPONENT_VOLKNER] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleVolkner,
    },
    // Gen 5
    [OPPONENT_LENORA] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleLenora,
    },
    [OPPONENT_BURGH] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleBurgh,
    },
    [OPPONENT_ELESA] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleElesa,
    },
    [OPPONENT_CLAY] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleClay,
    },
    [OPPONENT_SKYLA] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleSkyla,
    },
    [OPPONENT_BRYCEN] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleBrycen,
    },
    [OPPONENT_DRAYDEN] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleDrayden,
    },
    [OPPONENT_CHEREN] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleCheren, 
    },
    [OPPONENT_ROXIE] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleRoxie,
    },
    [OPPONENT_MARLON] =
    {
        .graphicsId = OPPONENT_GFX(OBJ_EVENT_GFX_BRENDAN_NORMAL),
        .script = EventScript_PWTBattleMarlon,
    },
};

bool32 IsOpponentADuo(enum OpponentID opponentId)
{
    const struct TournamentOpponent *opponent = &gTournamentOpponents[opponentId];

    if (opponent->graphicsId[1] >= NUM_OBJ_EVENT_GFX)
        return FALSE;
    
    return TRUE;
}
