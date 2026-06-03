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
