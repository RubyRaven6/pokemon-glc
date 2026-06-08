#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "event_scripts.h"
#include "pokemon.h"
#include "party_menu.h"
#include "tournament_logic.h"
#include "tournament_opponent.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/opponents.h"

struct Roster
{
    enum OpponentID opponentId;
    u16 flag;
};

static const struct Roster sKantoGymLeaderRoster[] =
{
    { OPPONENT_BROCK,           FLAG_KANTO_LEADER_BROCK },
    { OPPONENT_MISTY,           FLAG_KANTO_LEADER_MISTY },
    { OPPONENT_LT_SURGE,        FLAG_KANTO_LEADER_LT_SURGE },
    { OPPONENT_ERIKA,           FLAG_KANTO_LEADER_ERIKA },
    { OPPONENT_SABRINA,         FLAG_KANTO_LEADER_SABRINA },
    { OPPONENT_KOGA_AND_JANINE, FLAG_KANTO_LEADER_KOGA_JANINE },
    { OPPONENT_BLAINE,          FLAG_KANTO_LEADER_BLAINE },
    { OPPONENT_GIOVANNI,        FLAG_KANTO_LEADER_GIOVANNI },
};

static const struct Roster sJohtoGymLeaderRoster[] =
{
    { OPPONENT_FALKNER, FLAG_JOHTO_LEADER_FALKNER },
    { OPPONENT_BUGSY,   FLAG_JOHTO_LEADER_BUGSY },
    { OPPONENT_WHITNEY, FLAG_JOHTO_LEADER_WHITNEY },
    { OPPONENT_MORTY,   FLAG_JOHTO_LEADER_MORTY },
    { OPPONENT_CHUCK,   FLAG_JOHTO_LEADER_CHUCK },
    { OPPONENT_JASMINE, FLAG_JOHTO_LEADER_JASMINE },
    { OPPONENT_PRYCE,   FLAG_JOHTO_LEADER_PRYCE },
    { OPPONENT_CLAIR,   FLAG_JOHTO_LEADER_CLAIR },
};

static const struct Roster sHoennGymLeaderRoster[] =
{
    { OPPONENT_ROXANNE,       FLAG_HOENN_LEADER_ROXANNE },
    { OPPONENT_BRAWLY,        FLAG_HOENN_LEADER_BRAWLY },
    { OPPONENT_WATTSON,       FLAG_HOENN_LEADER_WATTSON },
    { OPPONENT_FLANNERY_NUTS, FLAG_HOENN_LEADER_FLANNERY },
    { OPPONENT_NORMAN,        FLAG_HOENN_LEADER_NORMAN },
    { OPPONENT_WINONA,        FLAG_HOENN_LEADER_WINONA },
    { OPPONENT_TATE_AND_LIZA, FLAG_HOENN_LEADER_TATE_AND_LIZA },
    { OPPONENT_JUAN,          FLAG_HOENN_LEADER_JUAN },
};

static const struct Roster sSinnohGymLeaderRoster[] =
{
    { OPPONENT_ROARK,        FLAG_SINNOH_LEADER_ROARK },
    { OPPONENT_GARDENIA,     FLAG_SINNOH_LEADER_GARDENIA },
    { OPPONENT_MAYLENE,      FLAG_SINNOH_LEADER_MAYLENE },
    { OPPONENT_CRASHER_WAKE, FLAG_SINNOH_LEADER_CRASHERWAKE },
    { OPPONENT_FANTINA,      FLAG_SINNOH_LEADER_FANTINA },
    { OPPONENT_BYRON,        FLAG_SINNOH_LEADER_BYRON },
    { OPPONENT_CANDICE_NUTS, FLAG_SINNOH_LEADER_CANDICE },
    { OPPONENT_VOLKNER,      FLAG_SINNOH_LEADER_VOLKNER },
};

static const struct Roster sUnovaGymLeaderRoster[] =
{
    { OPPONENT_LENORA,  FLAG_UNOVA_LEADER_LENORA },
    { OPPONENT_BURGH,   FLAG_UNOVA_LEADER_BURGH },
    { OPPONENT_ELESA,   FLAG_UNOVA_LEADER_ELESA },
    { OPPONENT_CLAY,    FLAG_UNOVA_LEADER_CLAY },
    { OPPONENT_SKYLA,   FLAG_UNOVA_LEADER_SKYLA },
    { OPPONENT_BRYCEN,  FLAG_UNOVA_LEADER_BRYCEN },
    { OPPONENT_DRAYDEN, FLAG_UNOVA_LEADER_DRAYDEN },
    { OPPONENT_CHEREN,  FLAG_UNOVA_LEADER_CHEREN },
    { OPPONENT_ROXIE,   FLAG_UNOVA_LEADER_ROXIE },
    { OPPONENT_MARLON,  FLAG_UNOVA_LEADER_MARLON },
};

#define ROSTER(_roster, _flag)     \
{                                  \
    .roster = _roster,             \
    .count = ARRAY_COUNT(_roster), \
    .flag = _flag,                 \
}
static const struct RosterData
{
    const struct Roster *roster;
    u32 count;
    u16 flag;
}
sGymLeaderRosters[] =
{
    [ROSTER_GEN1_GYM_LEADERS] = ROSTER(sKantoGymLeaderRoster,  FLAG_COMPLETED_ROSTER_KANTO),
    [ROSTER_GEN2_GYM_LEADERS] = ROSTER(sJohtoGymLeaderRoster,  FLAG_COMPLETED_ROSTER_JOHTO),
    [ROSTER_GEN3_GYM_LEADERS] = ROSTER(sHoennGymLeaderRoster,  FLAG_COMPLETED_ROSTER_HOENN),
    [ROSTER_GEN4_GYM_LEADERS] = ROSTER(sSinnohGymLeaderRoster, FLAG_COMPLETED_ROSTER_SINNOH),
    [ROSTER_GEN5_GYM_LEADERS] = ROSTER(sUnovaGymLeaderRoster,  FLAG_COMPLETED_ROSTER_UNOVA),
};

const u16 gTechniqueFlagUnlocks[] =
{
    [ITEM_TM01] = FLAG_KANTO_LEADER_BROCK,
    [ITEM_TM02] = FLAG_KANTO_LEADER_MISTY,
    [ITEM_TM03] = FLAG_KANTO_LEADER_LT_SURGE,
    [ITEM_TM04] = FLAG_KANTO_LEADER_ERIKA,
    [ITEM_TM05] = FLAG_KANTO_LEADER_SABRINA,
    [ITEM_TM06] = FLAG_KANTO_LEADER_KOGA_JANINE,
    [ITEM_TM07] = FLAG_KANTO_LEADER_BLAINE,
    [ITEM_TM08] = FLAG_KANTO_LEADER_GIOVANNI,
    [ITEM_TM09] = FLAG_JOHTO_LEADER_FALKNER,
    [ITEM_TM10] = FLAG_JOHTO_LEADER_BUGSY,
    [ITEM_TM11] = FLAG_JOHTO_LEADER_WHITNEY,
    [ITEM_TM12] = FLAG_JOHTO_LEADER_MORTY,
    [ITEM_TM13] = FLAG_JOHTO_LEADER_CHUCK,
    [ITEM_TM14] = FLAG_JOHTO_LEADER_JASMINE,
    [ITEM_TM15] = FLAG_JOHTO_LEADER_PRYCE,
    [ITEM_TM16] = FLAG_JOHTO_LEADER_CLAIR,
    [ITEM_TM17] = FLAG_HOENN_LEADER_ROXANNE,
    [ITEM_TM18] = FLAG_HOENN_LEADER_BRAWLY,
    [ITEM_TM19] = FLAG_HOENN_LEADER_WATTSON,
    [ITEM_TM20] = FLAG_HOENN_LEADER_FLANNERY,
    [ITEM_TM21] = FLAG_HOENN_LEADER_NORMAN,
    [ITEM_TM22] = FLAG_HOENN_LEADER_WINONA,
    [ITEM_TM23] = FLAG_HOENN_LEADER_TATE_AND_LIZA,
    [ITEM_TM24] = FLAG_HOENN_LEADER_JUAN,
    [ITEM_TM25] = FLAG_SINNOH_LEADER_ROARK,
    [ITEM_TM26] = FLAG_SINNOH_LEADER_GARDENIA,
    [ITEM_TM27] = FLAG_SINNOH_LEADER_MAYLENE,
    [ITEM_TM28] = FLAG_SINNOH_LEADER_CRASHERWAKE,
    [ITEM_TM29] = FLAG_SINNOH_LEADER_FANTINA,
    [ITEM_TM30] = FLAG_SINNOH_LEADER_BYRON,
    [ITEM_TM31] = FLAG_SINNOH_LEADER_CANDICE,
    [ITEM_TM32] = FLAG_SINNOH_LEADER_VOLKNER,
    [ITEM_TM33] = FLAG_UNOVA_LEADER_LENORA,
    [ITEM_TM34] = FLAG_UNOVA_LEADER_BURGH,
    [ITEM_TM35] = FLAG_UNOVA_LEADER_ELESA,
    [ITEM_TM36] = FLAG_UNOVA_LEADER_CLAY,
    [ITEM_TM37] = FLAG_UNOVA_LEADER_SKYLA,
    [ITEM_TM38] = FLAG_UNOVA_LEADER_BRYCEN,
    [ITEM_TM39] = FLAG_UNOVA_LEADER_DRAYDEN,
    [ITEM_TM40] = FLAG_UNOVA_LEADER_CHEREN,
    [ITEM_TM41] = FLAG_UNOVA_LEADER_ROXIE,
    [ITEM_TM42] = FLAG_UNOVA_LEADER_MARLON,
};

static const u32 sLeaderSignatureTechs[] =
{
    MOVE_ROCK_HEART,
    MOVE_RIPTIDE,
    MOVE_ARC_FAULT,
    MOVE_GRASSPIERCER,
    MOVE_PSYCHE_LOCK,
    MOVE_POISONED_STARS,
    MOVE_MAGMATIC_RAGE,
    MOVE_SHALLOW_GRAVE,
    MOVE_WINDSTORM,
    MOVE_VINSECTICATION,
    MOVE_FUSSY_FUSS,
    MOVE_JINX,
    MOVE_CRASHING_FIST,
    MOVE_HYDRAULIC_PRESS,
    MOVE_ICE_RINK,
    MOVE_STORM_SACRIFICE,
    MOVE_MINERAGRAPHY,
    MOVE_SURFS_UP,
    MOVE_UNDERCURRENT,
    MOVE_THIRD_DEGREE,
    MOVE_INVERSION,
    MOVE_WING_SLICER,
    MOVE_GEMINIC_BLAST,
    MOVE_SHOWSTOPPER,
    MOVE_SINKHOLE,
    MOVE_SUNBLOOM,
    MOVE_AURA_FARMING,
    MOVE_WAKE_CRASH,
    MOVE_RAZZLE_DAZZLE,
    MOVE_STEELSURGE,
    MOVE_OVEREXPOSURE,
    MOVE_DRY_FULMINATION,
    MOVE_RESEARCH,
    MOVE_CHRYSALIS,
    MOVE_CASTING_CALL,
    MOVE_ORBITAL_PULL,
    MOVE_JET_STREAM,
    MOVE_STUNT_DOUBLE,
    MOVE_CALAMITY_CLEAVE,
    MOVE_PSIDEKICK,
    MOVE_MOSH_PIT,
    MOVE_SYNCHROSWIM,
};

void ChooseRandomGymLeader(void)
{
    enum TrainerRoster gen = VarGet(VAR_GENERATION_CTL);

    u32 countUndefeated = 0;
    u32 leader1 = 0;
    u32 leader2 = 0;
    u32 leader3 = 0;

    for (u32 i = 0; i < sGymLeaderRosters[gen].count; i++)
    {
        if(!FlagGet(sGymLeaderRosters[gen].roster[i].flag))
            countUndefeated++;
    }
    
    u32 n = RandomUniform(RNG_NONE, 0, countUndefeated - 1);

    for (u32 i = 0; i < sGymLeaderRosters[gen].count; i++)
    {
        if (!FlagGet(sGymLeaderRosters[gen].roster[i].flag))
        {
            if (n == 0)
            {
                leader3 = i;
                break;
            }
            n--;
        }
    }
    
    do { leader1 = RandomUniform(RNG_NONE, 0, sGymLeaderRosters[gen].count - 1); } while (leader1 == leader3);

    do { leader2 = RandomUniform(RNG_NONE, 0, sGymLeaderRosters[gen].count - 1); } while (leader2 == leader3 || leader2 == leader1);

    VarSet(VAR_GYM_LEADER_1, sGymLeaderRosters[gen].roster[leader1].opponentId);
    VarSet(VAR_GYM_LEADER_2, sGymLeaderRosters[gen].roster[leader2].opponentId);
    VarSet(VAR_GYM_LEADER_3, sGymLeaderRosters[gen].roster[leader3].opponentId);
};

void Script_goto_pwt_battle_script(struct ScriptContext *ctx)
{
    enum OpponentID opponentId = VarGet(ScriptReadHalfword(ctx));

    Script_RequestEffects(SCREFF_V1);

    ScriptCall(ctx, gTournamentOpponents[opponentId].script);
}

void SetCompleteRosterFlag(void)
{
    u32 countDefeated = 0;
    enum TrainerRoster gen = VarGet(VAR_GENERATION_CTL);

    for (u32 i = 0; i < sGymLeaderRosters[gen].count; i++)
    {
        if (FlagGet(sGymLeaderRosters[gen].roster[i].flag))
            countDefeated++;
    }

    if(countDefeated == sGymLeaderRosters[gen].count)
        FlagSet(sGymLeaderRosters[gen].flag);
}

bool8 ScrCmd_checkdefeatedleaders(struct ScriptContext *ctx)
{
    u32 countDefeated = 0;
    enum TrainerRoster kanto = ROSTER_GEN1_GYM_LEADERS;

    for (u32 i = 0; i < sGymLeaderRosters[kanto].count; i++)
    {
        if(FlagGet(sGymLeaderRosters[kanto].roster[i].flag))
            countDefeated++;
    }

    if (countDefeated >= 1)
        gSpecialVar_Result = TRUE;
    else
        gSpecialVar_Result = FALSE;
    
    return FALSE;
}

u32 CheckPartyForTech(void)
{
    u32 counter = 0;

    for (u32 j = 0; j < gPartiesCount[B_TRAINER_PLAYER]; j++)
        for (u32 i = 0; i < ARRAY_COUNT(sLeaderSignatureTechs); i++)
            if(MonKnowsMove(&gParties[B_TRAINER_PLAYER][j], sLeaderSignatureTechs[i]))
                counter++;
    
    return counter;
}

void Debug_SetAllFlagsForGymLeaders(void)
{
    for (u32 i = ITEM_TM01; i < ARRAY_COUNT(gTechniqueFlagUnlocks); i++)
    {
        if(!FlagGet(gTechniqueFlagUnlocks[i]))
            FlagSet(gTechniqueFlagUnlocks[i]);
    }
}

void CheckForOpponentDuo(void)
{
    enum OpponentID opponentId = GetCurrentOpponent();
    
    if (IsOpponentADuo(opponentId))
        gSpecialVar_Result = TRUE;
    else
        gSpecialVar_Result = FALSE;
}

enum OpponentID GetCurrentOpponent(void)
{
    switch (VarGet(VAR_GYM_LEADER_BATTLE_COUNT))
    {
        case 1: return VarGet(VAR_GYM_LEADER_1);
        case 2: return VarGet(VAR_GYM_LEADER_2);
        case 3: return VarGet(VAR_GYM_LEADER_3);
    }

    return OPPONENT_NONE;
}

void SetupOpponentGfxId(void)
{
    enum OpponentID opponentId = GetCurrentOpponent();

    Script_RequestEffects(SCREFF_V1);

    if (IsOpponentADuo(opponentId) == TRUE)
    {
        VarSet(VAR_OBJ_GFX_ID_0, gTournamentOpponents[opponentId].graphicsId[0]);
        VarSet(VAR_OBJ_GFX_ID_1, gTournamentOpponents[opponentId].graphicsId[1]);
    }
    else
    {
        VarSet(VAR_OBJ_GFX_ID_0, gTournamentOpponents[opponentId].graphicsId[0]);
    }
}
