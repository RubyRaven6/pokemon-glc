#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveType(MOVE_ROCK_HEART) == TYPE_ROCK);
    ASSUME(GetMovePower(MOVE_ROCK_HEART) == 80);
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_ROCK_HEART, MOVE_EFFECT_INFATUATION, 30));

    ASSUME(GetMoveEffect(MOVE_RIPTIDE) == EFFECT_FIXED_PERCENT_DAMAGE);
    ASSUME(GetMoveDamagePercentage(MOVE_RIPTIDE) == 50);
    ASSUME(GetMoveCategory(MOVE_RIPTIDE) == DAMAGE_CATEGORY_STATUS);

    ASSUME(IsExplosionMove(MOVE_ARC_FAULT));
    ASSUME(MoveHasAdditionalEffect(MOVE_ARC_FAULT, MOVE_EFFECT_ELECTRIC_TERRAIN));

    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_GRASSPIERCER, MOVE_EFFECT_GRASSPIERCER, 50));
    ASSUME(GetMoveEffect(MOVE_PSYCHE_LOCK) == EFFECT_PSYCHE_LOCK);
    ASSUME(MoveSetsStrictEscapePrevention(MOVE_PSYCHE_LOCK));

    ASSUME(GetMoveStrikeCount(MOVE_POISONED_STARS) == 3);
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_POISONED_STARS, MOVE_EFFECT_POISON, 30));
    ASSUME(MoveIgnoresResistancesIfUserPoison(MOVE_POISONED_STARS));

    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_MAGMATIC_RAGE, MOVE_EFFECT_BURN, 10));
    ASSUME(MoveHasAdditionalEffect(MOVE_SHALLOW_GRAVE, MOVE_EFFECT_WRAP));
    ASSUME_MOVE_EFFECT_STAT_CHANGE(MOVE_SHALLOW_GRAVE, speed: -3);

    ASSUME(GetMoveEffect(MOVE_SINKHOLE) == EFFECT_SINKHOLE);
    ASSUME(GetMoveType(MOVE_SINKHOLE) == TYPE_ROCK);
    ASSUME(GetMoveCategory(MOVE_SINKHOLE) == DAMAGE_CATEGORY_PHYSICAL);

    ASSUME(GetMoveType(MOVE_SUNBLOOM) == TYPE_GRASS);
    ASSUME(GetMovePower(MOVE_SUNBLOOM) == 60);
    ASSUME(GetMoveCategory(MOVE_SUNBLOOM) == DAMAGE_CATEGORY_SPECIAL);
    ASSUME(MoveHasAdditionalEffect(MOVE_SUNBLOOM, MOVE_EFFECT_SUNBLOOM));

    ASSUME(GetMoveEffect(MOVE_AURA_FARMING) == EFFECT_AURA_FARMING);
    ASSUME(GetMoveType(MOVE_AURA_FARMING) == TYPE_FIGHTING);
    ASSUME(GetMovePower(MOVE_AURA_FARMING) == 75);
    ASSUME(GetMoveCategory(MOVE_AURA_FARMING) == DAMAGE_CATEGORY_SPECIAL);
    ASSUME(GetMovePriority(MOVE_AURA_FARMING) < 0);

    ASSUME(GetMoveType(MOVE_WAKE_CRASH) == TYPE_WATER);
    ASSUME(GetMovePower(MOVE_WAKE_CRASH) == 120);
    ASSUME(GetMovePriority(MOVE_WAKE_CRASH) == 1);
    ASSUME(GetMoveRecoil(MOVE_WAKE_CRASH) == 20);

    ASSUME(GetMoveEffect(MOVE_RAZZLE_DAZZLE) == EFFECT_RAZZLE_DAZZLE);
    ASSUME(GetMoveType(MOVE_RAZZLE_DAZZLE) == TYPE_GHOST);
    ASSUME(GetMovePower(MOVE_RAZZLE_DAZZLE) == 75);
    ASSUME(GetMoveCategory(MOVE_RAZZLE_DAZZLE) == DAMAGE_CATEGORY_SPECIAL);

    ASSUME(GetMoveEffect(MOVE_STEELSURGE) == EFFECT_STEELSURGE);
    ASSUME(GetMoveType(MOVE_STEELSURGE) == TYPE_STEEL);
    ASSUME(GetMoveCategory(MOVE_STEELSURGE) == DAMAGE_CATEGORY_STATUS);

    ASSUME(GetMoveType(MOVE_OVEREXPOSURE) == TYPE_ICE);
    ASSUME(GetMovePower(MOVE_OVEREXPOSURE) == 65);
    ASSUME(MoveHasAdditionalEffect(MOVE_OVEREXPOSURE, MOVE_EFFECT_OVEREXPOSURE));

    ASSUME(GetMoveType(MOVE_DRY_FULMINATION) == TYPE_ELECTRIC);
    ASSUME(GetMovePower(MOVE_DRY_FULMINATION) == 120);
    ASSUME(GetMoveAccuracy(MOVE_DRY_FULMINATION) == 70);
    ASSUME(GetMoveCategory(MOVE_DRY_FULMINATION) == DAMAGE_CATEGORY_SPECIAL);
    ASSUME(MoveAlwaysHitsInSun(MOVE_DRY_FULMINATION));
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_DRY_FULMINATION, MOVE_EFFECT_BURN, 30));
}

SINGLE_BATTLE_TEST("Rock Heart may infatuate the target")
{
    PASSES_RANDOMLY(30, 100, RNG_SECONDARY_EFFECT);
    GIVEN {
        PLAYER(SPECIES_NIDOQUEEN);
        OPPONENT(SPECIES_NIDOKING);
    } WHEN {
        TURN { MOVE(player, MOVE_ROCK_HEART); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROCK_HEART, player);
        HP_BAR(opponent);
        MESSAGE("The opposing Nidoking fell in love!");
    } THEN {
        EXPECT(opponent->volatiles.infatuation);
    }
}

SINGLE_BATTLE_TEST("Riptide halves the target's current HP")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(200); HP(150); }
    } WHEN {
        TURN { MOVE(player, MOVE_RIPTIDE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_RIPTIDE, player);
        HP_BAR(opponent, damage: 75);
    } THEN {
        EXPECT_EQ(opponent->hp, 75);
    }
}

SINGLE_BATTLE_TEST("Arc Fault makes the user faint and sets Electric Terrain")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ARC_FAULT); }
    } THEN {
        EXPECT_EQ(player->hp, 0);
        EXPECT(gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN);
    }
}

SINGLE_BATTLE_TEST("Grasspiercer can badly poison, paralyze, or put the target to sleep")
{
    u8 statusAnim;
    u32 rng;
    PARAMETRIZE { statusAnim = B_ANIM_STATUS_PSN; rng = MOVE_EFFECT_TOXIC; }
    PARAMETRIZE { statusAnim = B_ANIM_STATUS_PRZ; rng = MOVE_EFFECT_PARALYSIS; }
    PARAMETRIZE { statusAnim = B_ANIM_STATUS_SLP; rng = MOVE_EFFECT_SLEEP; }
    PASSES_RANDOMLY(50, 100, RNG_SECONDARY_EFFECT);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_GRASSPIERCER, WITH_RNG(RNG_DIRE_CLAW, rng)); }
        TURN {}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GRASSPIERCER, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_STATUS, statusAnim, opponent);
    }
}

SINGLE_BATTLE_TEST("Psyche Lock prevents hit-and-switch moves from switching out")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_U_TURN, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_PSYCHE_LOCK); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_U_TURN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHE_LOCK, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_U_TURN, opponent);
        NONE_OF {
            MESSAGE("The opposing Wobbuffet went back to 2!");
            MESSAGE("2 sent out Wynaut!");
        }
    } THEN {
        EXPECT(opponent->volatiles.escapePrevention);
        EXPECT(opponent->volatiles.strictEscapePrevention);
    }
}

SINGLE_BATTLE_TEST("Psyche Lock prevents Shed Shell switching")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_SHED_SHELL].holdEffect == HOLD_EFFECT_SHED_SHELL);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_SHED_SHELL); Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_PSYCHE_LOCK); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); SWITCH(opponent, 1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHE_LOCK, player);
        NONE_OF {
            SWITCH_OUT_MESSAGE("Wobbuffet");
            SEND_IN_MESSAGE("Wynaut");
        }
    } THEN {
        EXPECT(opponent->volatiles.strictEscapePrevention);
    }
}

SINGLE_BATTLE_TEST("Poisoned Stars hits 3 times and can poison on each hit")
{
    PASSES_RANDOMLY(30, 100, RNG_SECONDARY_EFFECT);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_POISONED_STARS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POISONED_STARS, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POISONED_STARS, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POISONED_STARS, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, opponent);
    }
}

SINGLE_BATTLE_TEST("Poisoned Stars ignores Poison resistance when used by a Poison-type Pokemon", s16 damage)
{
    u32 species;
    PARAMETRIZE { species = SPECIES_WOBBUFFET; }
    PARAMETRIZE { species = SPECIES_NIDOKING; }
    GIVEN {
        ASSUME(GetSpeciesType(SPECIES_WOBBUFFET, 0) != TYPE_POISON && GetSpeciesType(SPECIES_WOBBUFFET, 1) != TYPE_POISON);
        ASSUME(GetSpeciesType(SPECIES_NIDOKING, 0) == TYPE_POISON || GetSpeciesType(SPECIES_NIDOKING, 1) == TYPE_POISON);
        ASSUME(GetSpeciesType(SPECIES_ARBOK, 0) == TYPE_POISON || GetSpeciesType(SPECIES_ARBOK, 1) == TYPE_POISON);
        PLAYER(species) { Attack(100); }
        OPPONENT(SPECIES_ARBOK) { Defense(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_POISONED_STARS, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POISONED_STARS, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage * 2);
    }
}

SINGLE_BATTLE_TEST("Magmatic Rage is super effective against Rock and Ground types")
{
    u32 species;
    PARAMETRIZE { species = SPECIES_NOSEPASS; }
    PARAMETRIZE { species = SPECIES_SANDSHREW; }
    GIVEN {
        ASSUME(GetSpeciesType(SPECIES_NOSEPASS, 0) == TYPE_ROCK || GetSpeciesType(SPECIES_NOSEPASS, 1) == TYPE_ROCK);
        ASSUME(GetSpeciesType(SPECIES_SANDSHREW, 0) == TYPE_GROUND || GetSpeciesType(SPECIES_SANDSHREW, 1) == TYPE_GROUND);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(species);
    } WHEN {
        TURN { MOVE(player, MOVE_MAGMATIC_RAGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MAGMATIC_RAGE, player);
        MESSAGE("It's super effective!");
    }
}

SINGLE_BATTLE_TEST("Shallow Grave traps the target and lowers Speed by 3 stages")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SHALLOW_GRAVE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SHALLOW_GRAVE, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
    } THEN {
        EXPECT(opponent->volatiles.wrapped);
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 3);
    }
}

SINGLE_BATTLE_TEST("Sinkhole deals less damage to airborne targets and more damage during Gravity", s16 damage)
{
    u32 setupMove, item;
    PARAMETRIZE { setupMove = MOVE_CELEBRATE; item = ITEM_NONE; }
    PARAMETRIZE { setupMove = MOVE_CELEBRATE; item = ITEM_AIR_BALLOON; }
    PARAMETRIZE { setupMove = MOVE_GRAVITY; item = ITEM_NONE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Item(item); }
    } WHEN {
        TURN { MOVE(player, setupMove); }
        TURN { MOVE(player, MOVE_SINKHOLE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SINKHOLE, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_LT(results[1].damage, results[0].damage);
        EXPECT_GT(results[2].damage, results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Sunbloom sets sunlight for 5 turns or 8 turns if it KOs")
{
    u32 hp, remainingDuration;
    PARAMETRIZE { hp = 999; remainingDuration = 4; }
    PARAMETRIZE { hp = 1; remainingDuration = 7; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(hp); MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_SUNBLOOM); }
    } THEN {
        EXPECT(gBattleWeather & B_WEATHER_SUN_NORMAL);
        EXPECT_EQ(gBattleStruct->weatherDuration, remainingDuration);
    }
}

SINGLE_BATTLE_TEST("Sunbloom does not reset existing sunlight")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_SUNNY_DAY); }
        TURN { MOVE(player, MOVE_SUNBLOOM); }
    } THEN {
        EXPECT(gBattleWeather & B_WEATHER_SUN_NORMAL);
        EXPECT_EQ(gBattleStruct->weatherDuration, 3);
    }
}

SINGLE_BATTLE_TEST("Sunbloom is stronger in sunlight", s16 damage)
{
    u32 setupMove;
    PARAMETRIZE { setupMove = MOVE_CELEBRATE; }
    PARAMETRIZE { setupMove = MOVE_SUNNY_DAY; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, setupMove); }
        TURN { MOVE(player, MOVE_SUNBLOOM, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUNBLOOM, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Aura Farming gains power for attacks received before moving", s16 damage)
{
    u32 opponentMove;
    PARAMETRIZE { opponentMove = MOVE_CELEBRATE; }
    PARAMETRIZE { opponentMove = MOVE_SCRATCH; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(opponentMove); }
    } WHEN {
        TURN { MOVE(player, MOVE_AURA_FARMING, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); MOVE(opponent, opponentMove); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AURA_FARMING, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Wake Crash applies 20 percent recoil")
{
    s16 damage;
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_WAKE_CRASH, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WAKE_CRASH, player);
        HP_BAR(opponent, captureDamage: &damage);
        HP_BAR(player);
    } THEN {
        EXPECT_EQ(player->maxHP - player->hp, damage * 20 / 100);
    }
}

SINGLE_BATTLE_TEST("Razzle Dazzle doubles on consecutive use up to 300 BP")
{
    s16 damage[4];
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { SpAttack(50); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(999); MaxHP(999); SpDefense(50); }
    } WHEN {
        TURN { MOVE(player, MOVE_RAZZLE_DAZZLE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
        TURN { MOVE(player, MOVE_RAZZLE_DAZZLE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
        TURN { MOVE(player, MOVE_RAZZLE_DAZZLE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
        TURN { MOVE(player, MOVE_RAZZLE_DAZZLE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_RAZZLE_DAZZLE, player);
        HP_BAR(opponent, captureDamage: &damage[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_RAZZLE_DAZZLE, player);
        HP_BAR(opponent, captureDamage: &damage[1]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_RAZZLE_DAZZLE, player);
        HP_BAR(opponent, captureDamage: &damage[2]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_RAZZLE_DAZZLE, player);
        HP_BAR(opponent, captureDamage: &damage[3]);
    } THEN {
        EXPECT_GT(damage[1], damage[0]);
        EXPECT_GT(damage[2], damage[1]);
        EXPECT_EQ(damage[3], damage[2]);
    }
}

SINGLE_BATTLE_TEST("Steelsurge sets sharp steel on the opposing side")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_STEELSURGE); }
    } THEN {
        EXPECT(IsHazardOnSide(B_SIDE_OPPONENT, HAZARDS_STEELSURGE));
    }
}

SINGLE_BATTLE_TEST("Overexposure makes its target weak to Ice for the rest of battle")
{
    s16 damage[2];
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_ICE_BEAM, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
        TURN { MOVE(player, MOVE_OVEREXPOSURE); }
        TURN { MOVE(player, MOVE_CELEBRATE); SWITCH(opponent, 1); }
        TURN { MOVE(player, MOVE_CELEBRATE); SWITCH(opponent, 0); }
        TURN { MOVE(player, MOVE_ICE_BEAM, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ICE_BEAM, player);
        HP_BAR(opponent, captureDamage: &damage[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_OVEREXPOSURE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ICE_BEAM, player);
        HP_BAR(opponent, captureDamage: &damage[1]);
    } THEN {
        EXPECT_MUL_EQ(damage[0], Q_4_12(2.0), damage[1]);
    }
}

SINGLE_BATTLE_TEST("Dry Fulmination cannot miss in sun and may burn")
{
    PASSES_RANDOMLY(100, 100, RNG_ACCURACY);
    PASSES_RANDOMLY(30, 100, RNG_SECONDARY_EFFECT);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SUNNY_DAY); }
        TURN { MOVE(player, MOVE_DRY_FULMINATION); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRY_FULMINATION, player);
        NONE_OF { MESSAGE("The opposing Wobbuffet avoided the attack!"); }
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_BRN, opponent);
    } THEN {
        EXPECT(opponent->status1 & STATUS1_BURN);
    }
}

AI_SINGLE_BATTLE_TEST("AI values Rock Heart's infatuation chance")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY);
        PLAYER(SPECIES_NIDOQUEEN);
        OPPONENT(SPECIES_NIDOKING) { Moves(MOVE_ROCK_HEART, MOVE_CELEBRATE); }
    } WHEN {
        TURN { SCORE_GT_VAL(opponent, MOVE_ROCK_HEART, AI_SCORE_DEFAULT); }
    }
}

AI_SINGLE_BATTLE_TEST("AI values Grasspiercer's random status chance")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_GRASSPIERCER, MOVE_CELEBRATE); }
    } WHEN {
        TURN { SCORE_GT_VAL(opponent, MOVE_GRASSPIERCER, AI_SCORE_DEFAULT); }
    }
}

AI_DOUBLE_BATTLE_TEST("AI scores Sunbloom as sun setup for its ally")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_DOUBLE_BATTLE);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_SUNBLOOM, MOVE_MAGICAL_LEAF); }
        OPPONENT(SPECIES_EXEGGUTOR) { Ability(ABILITY_CHLOROPHYLL); Moves(MOVE_SOLAR_BEAM); }
    } WHEN {
        TURN { SCORE_GT(opponentLeft, MOVE_SUNBLOOM, MOVE_MAGICAL_LEAF, target: playerLeft); }
    }
}

AI_SINGLE_BATTLE_TEST("AI scores Steelsurge as a hazard")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_POWERFUL_STATUS);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_STEELSURGE, MOVE_CELEBRATE); }
    } WHEN {
        TURN { EXPECT_MOVE(opponent, MOVE_STEELSURGE); }
    }
}

AI_SINGLE_BATTLE_TEST("AI scores Overexposure as Ice support")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_OVEREXPOSURE, MOVE_AURORA_BEAM); }
    } WHEN {
        TURN { SCORE_GT(opponent, MOVE_OVEREXPOSURE, MOVE_AURORA_BEAM); }
    }
}
