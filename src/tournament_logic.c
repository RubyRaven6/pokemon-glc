#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "event_scripts.h"
#include "pokemon.h"
#include "party_menu.h"
#include "tournament_logic.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/opponents.h"

static const u32 sKantoGymLeaderRoster[] = {
    TRAINER_LEADER_BROCK,
    TRAINER_LEADER_MISTY,
    TRAINER_LEADER_LT_SURGE,
    TRAINER_LEADER_ERIKA,
    TRAINER_LEADER_SABRINA,
    TRAINER_LEADER_KOGA_AND_JANINE,
    TRAINER_LEADER_BLAINE,
    TRAINER_LEADER_GIOVANNI,
};

static const u16 sKantoGymLeaderFlags[] = {
    FLAG_KANTO_LEADER_BROCK,
    FLAG_KANTO_LEADER_MISTY,
    FLAG_KANTO_LEADER_LT_SURGE,
    FLAG_KANTO_LEADER_ERIKA,
    FLAG_KANTO_LEADER_SABRINA,
    FLAG_KANTO_LEADER_KOGA_JANINE,
    FLAG_KANTO_LEADER_BLAINE,
    FLAG_KANTO_LEADER_GIOVANNI
};

static const u32 sJohtoGymLeaderRoster[] = {
    TRAINER_LEADER_FALKNER,
    TRAINER_LEADER_BUGSY,
    TRAINER_LEADER_WHITNEY,
    TRAINER_LEADER_MORTY,
    TRAINER_LEADER_CHUCK,
    TRAINER_LEADER_JASMINE,
    TRAINER_LEADER_PRYCE,
    TRAINER_LEADER_CLAIR,
};

static const u16 sJohtoGymLeaderFlags[] = {
    FLAG_JOHTO_LEADER_FALKNER,
    FLAG_JOHTO_LEADER_BUGSY,
    FLAG_JOHTO_LEADER_WHITNEY,
    FLAG_JOHTO_LEADER_MORTY,
    FLAG_JOHTO_LEADER_CHUCK,
    FLAG_JOHTO_LEADER_JASMINE,
    FLAG_JOHTO_LEADER_PRYCE,
    FLAG_JOHTO_LEADER_CLAIR
};

static const u32 sHoennGymLeaderRoster[] = {
    TRAINER_LEADER_ROXANNE,
    TRAINER_LEADER_BRAWLY,
    TRAINER_LEADER_WATTSON,
    TRAINER_LEADER_FLANNERY,
    TRAINER_LEADER_NORMAN,
    TRAINER_LEADER_WINONA,
    TRAINER_LEADER_TATE_AND_LIZA,
    TRAINER_LEADER_JUAN,
};

static const u16 sHoennGymLeaderFlags[] = {
    FLAG_HOENN_LEADER_ROXANNE,
    FLAG_HOENN_LEADER_BRAWLY,
    FLAG_HOENN_LEADER_WATTSON,
    FLAG_HOENN_LEADER_FLANNERY,
    FLAG_HOENN_LEADER_NORMAN,
    FLAG_HOENN_LEADER_WINONA,
    FLAG_HOENN_LEADER_TATE_AND_LIZA,
    FLAG_HOENN_LEADER_JUAN
};

static const u32 sSinnohGymLeaderRoster[] = {
    TRAINER_LEADER_ROARK,
    TRAINER_LEADER_GARDENIA,
    TRAINER_LEADER_MAYLENE,
    TRAINER_LEADER_CRASHER_WAKE,
    TRAINER_LEADER_FANTINA,
    TRAINER_LEADER_BYRON,
    TRAINER_LEADER_CANDICE_NUTS,
    TRAINER_LEADER_VOLKNER
};

static const u16 sSinnohGymLeaderFlags[] = {
    FLAG_SINNOH_LEADER_ROARK,
    FLAG_SINNOH_LEADER_GARDENIA,
    FLAG_SINNOH_LEADER_MAYLENE,
    FLAG_SINNOH_LEADER_CRASHERWAKE,
    FLAG_SINNOH_LEADER_FANTINA,
    FLAG_SINNOH_LEADER_BYRON,
    FLAG_SINNOH_LEADER_CANDICE,
    FLAG_SINNOH_LEADER_VOLKNER
};

static const u32 sUnovaGymLeaderRoster[] = {
    TRAINER_LEADER_LENORA,
    TRAINER_LEADER_BURGH,
    TRAINER_LEADER_ELESA,
    TRAINER_LEADER_CLAY,
    TRAINER_LEADER_SKYLA,
    TRAINER_LEADER_BRYCEN,
    TRAINER_LEADER_DRAYDEN,
    TRAINER_LEADER_CHEREN,
    TRAINER_LEADER_ROXIE,
    TRAINER_LEADER_MARLON
};

static const u16 sUnovaGymLeaderFlags[] = {
    FLAG_UNOVA_LEADER_LENORA,
    FLAG_UNOVA_LEADER_BURGH,
    FLAG_UNOVA_LEADER_ELESA,
    FLAG_UNOVA_LEADER_CLAY,
    FLAG_UNOVA_LEADER_SKYLA,
    FLAG_UNOVA_LEADER_BRYCEN,
    FLAG_UNOVA_LEADER_DRAYDEN,
    FLAG_UNOVA_LEADER_CHEREN,
    FLAG_UNOVA_LEADER_ROXIE,
    FLAG_UNOVA_LEADER_MARLON
};

static const u16 sRosterCompletionFlags[] = {
    0,
    FLAG_COMPLETED_ROSTER_KANTO,
    FLAG_COMPLETED_ROSTER_JOHTO,
    FLAG_COMPLETED_ROSTER_HOENN,
    FLAG_COMPLETED_ROSTER_SINNOH,
    FLAG_COMPLETED_ROSTER_UNOVA
};

static const struct RosterStruct {
  const u32 *roster;
  const u16* leaderFlags;
  u32 rosterCount;
} sGymLeaderRosters[] = {
    [1] = { sKantoGymLeaderRoster, sKantoGymLeaderFlags, ARRAY_COUNT(sKantoGymLeaderRoster) },
    [2] = { sJohtoGymLeaderRoster, sJohtoGymLeaderFlags, ARRAY_COUNT(sJohtoGymLeaderRoster) },
    [3] = { sHoennGymLeaderRoster, sHoennGymLeaderFlags, ARRAY_COUNT(sHoennGymLeaderRoster) },
    [4] = { sSinnohGymLeaderRoster, sSinnohGymLeaderFlags, ARRAY_COUNT(sSinnohGymLeaderRoster) },
    [5] = { sUnovaGymLeaderRoster, sUnovaGymLeaderFlags, ARRAY_COUNT(sUnovaGymLeaderRoster) }
};

static const u8 *sPWTBattleScripts[] =
{
    /* KANTO LEADERS */
    [TRAINER_LEADER_BROCK]           = EventScript_PWTBattleBrock,
    [TRAINER_LEADER_MISTY]           = EventScript_PWTBattleMisty,
    [TRAINER_LEADER_LT_SURGE]        = EventScript_PWTBattleLtSurge,
    [TRAINER_LEADER_ERIKA]           = EventScript_PWTBattleErika,
    [TRAINER_LEADER_KOGA_AND_JANINE] = EventScript_PWTBattleKogaJanine,
    [TRAINER_LEADER_SABRINA]         = EventScript_PWTBattleSabrina,
    [TRAINER_LEADER_BLAINE]          = EventScript_PWTBattleBlaine,
    [TRAINER_LEADER_GIOVANNI]        = EventScript_PWTBattleGiovanni,

    /* JOHTO LEADERS */
    [TRAINER_LEADER_FALKNER]         = EventScript_PWTBattleFalkner,
    [TRAINER_LEADER_BUGSY]           = EventScript_PWTBattleBugsy,
    [TRAINER_LEADER_WHITNEY]         = EventScript_PWTBattleWhitney,
    [TRAINER_LEADER_MORTY]           = EventScript_PWTBattleMorty,
    [TRAINER_LEADER_CHUCK]           = EventScript_PWTBattleChuck,
    [TRAINER_LEADER_JASMINE]         = EventScript_PWTBattleJasmine,
    [TRAINER_LEADER_PRYCE]           = EventScript_PWTBattlePryce,
    [TRAINER_LEADER_CLAIR]           = EventScript_PWTBattleClair,

    /*HOENN LEADERS*/
    [TRAINER_LEADER_ROXANNE]         = EventScript_PWTBattleRoxanne,
    [TRAINER_LEADER_BRAWLY]          = EventScript_PWTBattleBrawly,
    [TRAINER_LEADER_WATTSON]         = EventScript_PWTBattleWattson,
    [TRAINER_LEADER_FLANNERY]        = EventScript_PWTBattleFlannery,
    [TRAINER_LEADER_NORMAN]          = EventScript_PWTBattleNorman,
    [TRAINER_LEADER_WINONA]          = EventScript_PWTBattleWinona,
    [TRAINER_LEADER_TATE_AND_LIZA]   = EventScript_PWTBattleTateAndLiza,
    [TRAINER_LEADER_JUAN]            = EventScript_PWTBattleJuan,

    /*SINNOH LEADERS*/
    [TRAINER_LEADER_ROARK]           = EventScript_PWTBattleRoark,
    [TRAINER_LEADER_GARDENIA]        = EventScript_PWTBattleGardenia,
    [TRAINER_LEADER_MAYLENE]         = EventScript_PWTBattleMaylene,
    [TRAINER_LEADER_CRASHER_WAKE]    = EventScript_PWTBattleCrasherWake,
    [TRAINER_LEADER_FANTINA]         = EventScript_PWTBattleFantina,
    [TRAINER_LEADER_BYRON]           = EventScript_PWTBattleByron,
    [TRAINER_LEADER_CANDICE_NUTS]    = EventScript_PWTBattleCandice,
    [TRAINER_LEADER_VOLKNER]         = EventScript_PWTBattleVolkner,

    /*UNOVA LEADERS*/
    [TRAINER_LEADER_LENORA]         = EventScript_PWTBattleLenora,
    [TRAINER_LEADER_BURGH]          = EventScript_PWTBattleBurgh,
    [TRAINER_LEADER_ELESA]          = EventScript_PWTBattleElesa,
    [TRAINER_LEADER_CLAY]           = EventScript_PWTBattleClay,
    [TRAINER_LEADER_SKYLA]          = EventScript_PWTBattleSkyla,
    [TRAINER_LEADER_BRYCEN]         = EventScript_PWTBattleBrycen,
    [TRAINER_LEADER_DRAYDEN]        = EventScript_PWTBattleDrayden,
    [TRAINER_LEADER_CHEREN]         = EventScript_PWTBattleCheren,
    [TRAINER_LEADER_ROXIE]          = EventScript_PWTBattleRoxie,
    [TRAINER_LEADER_MARLON] = EventScript_PWTBattleMarlon,
};

const u16 gTechniqueFlagUnlocks[] = {
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

static const u32 sLeaderSignatureTechs[] = {
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
    MOVE_MOUNTING_PRESSURE,
    MOVE_JET_STREAM,
    MOVE_STUNT_DOUBLE,
    MOVE_CALAMITY_CLEAVE,
    MOVE_PSIDEKICK,
    MOVE_MOSH_PIT,
    MOVE_SYNCHRONIZED_SWIM,
};

void ChooseRandomGymLeader(void) {
    u32 countUndefeated = 0;
    u32 gen = VarGet(VAR_GENERATION_CTL);
    u32 leader1 = 0;
    u32 leader2 = 0;
    u32 leader3 = 0;

    for (u32 i = 0; i < sGymLeaderRosters[gen].rosterCount; i++)
    {
        if(!FlagGet(sGymLeaderRosters[gen].leaderFlags[i]))
            countUndefeated++;
    }
    
    u32 n = RandomUniform(RNG_NONE, 0, countUndefeated - 1);

    for (u32 i = 0; i < sGymLeaderRosters[gen].rosterCount; i++)
    {
        if (!FlagGet(sGymLeaderRosters[gen].leaderFlags[i]))
        {
            if (n == 0)
            {
                leader3 = i;
                break;
            }
            n--;
        }
    }
    
    do { leader1 = RandomUniform(RNG_NONE, 0, sGymLeaderRosters[gen].rosterCount - 1); } while (leader1 == leader3);

    do { leader2 = RandomUniform(RNG_NONE, 0, sGymLeaderRosters[gen].rosterCount - 1); } while (leader2 == leader3 || leader2 == leader1);

    VarSet(VAR_GYM_LEADER_1, sGymLeaderRosters[gen].roster[leader1]);
    VarSet(VAR_GYM_LEADER_2, sGymLeaderRosters[gen].roster[leader2]);
    VarSet(VAR_GYM_LEADER_3, sGymLeaderRosters[gen].roster[leader3]);
};

void Script_goto_pwt_battle_script(struct ScriptContext *ctx)
{
    u16 trainerId = VarGet(ScriptReadHalfword(ctx));

    Script_RequestEffects(SCREFF_V1);

    ScriptCall(ctx, sPWTBattleScripts[trainerId]);
}

void SetCompleteRosterFlag(void) {
    u32 countDefeated = 0;
    u32 gen = VarGet(VAR_GENERATION_CTL);

    for (u32 i = 0; i < sGymLeaderRosters[gen].rosterCount; i++)
    {
        if(FlagGet(sGymLeaderRosters[gen].leaderFlags[i]))
            countDefeated++;
    }

    if(countDefeated == sGymLeaderRosters[gen].rosterCount)
        FlagSet(sRosterCompletionFlags[gen]);
}

bool8 ScrCmd_checkdefeatedleaders(struct ScriptContext *ctx) {
    u32 countDefeated = 0;
    u32 kanto = 1;

    for (u32 i = 0; i < sGymLeaderRosters[kanto].rosterCount; i++)
    {
        if(FlagGet(sGymLeaderRosters[kanto].leaderFlags[i]))
            countDefeated++;
    }

    if(countDefeated >=1)
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