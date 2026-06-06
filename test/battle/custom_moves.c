#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveType(MOVE_ROCK_HEART) == TYPE_ROCK);
    ASSUME(GetMovePower(MOVE_ROCK_HEART) == 80);
    ASSUME(GetMoveAccuracy(MOVE_ROCK_HEART) == 100);
    ASSUME(GetMoveCategory(MOVE_ROCK_HEART) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_ROCK_HEART, MOVE_EFFECT_INFATUATION, 30));

    ASSUME(GetMoveEffect(MOVE_RIPTIDE) == EFFECT_FIXED_PERCENT_DAMAGE);
    ASSUME(GetMoveType(MOVE_RIPTIDE) == TYPE_WATER);
    ASSUME(GetMoveAccuracy(MOVE_RIPTIDE) == 100);
    ASSUME(GetMoveDamagePercentage(MOVE_RIPTIDE) == 50);
    ASSUME(GetMoveCategory(MOVE_RIPTIDE) == DAMAGE_CATEGORY_STATUS);

    ASSUME(IsExplosionMove(MOVE_ARC_FAULT));
    ASSUME(GetMoveType(MOVE_ARC_FAULT) == TYPE_ELECTRIC);
    ASSUME(GetMovePower(MOVE_ARC_FAULT) == 200);
    ASSUME(GetMoveAccuracy(MOVE_ARC_FAULT) == 100);
    ASSUME(GetMoveCategory(MOVE_ARC_FAULT) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(MoveHasAdditionalEffect(MOVE_ARC_FAULT, MOVE_EFFECT_ELECTRIC_TERRAIN));

    ASSUME(GetMoveType(MOVE_GRASSPIERCER) == TYPE_GRASS);
    ASSUME(GetMovePower(MOVE_GRASSPIERCER) == 80);
    ASSUME(GetMoveAccuracy(MOVE_GRASSPIERCER) == 100);
    ASSUME(GetMoveCategory(MOVE_GRASSPIERCER) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_GRASSPIERCER, MOVE_EFFECT_GRASSPIERCER, 50));

    ASSUME(GetMoveEffect(MOVE_PSYCHE_LOCK) == EFFECT_PSYCHE_LOCK);
    ASSUME(GetMoveType(MOVE_PSYCHE_LOCK) == TYPE_PSYCHIC);
    ASSUME(GetMoveAccuracy(MOVE_PSYCHE_LOCK) == 100);
    ASSUME(GetMoveCategory(MOVE_PSYCHE_LOCK) == DAMAGE_CATEGORY_STATUS);
    ASSUME(MoveSetsStrictEscapePrevention(MOVE_PSYCHE_LOCK));

    ASSUME(GetMoveType(MOVE_POISONED_STARS) == TYPE_POISON);
    ASSUME(GetMovePower(MOVE_POISONED_STARS) == 20);
    ASSUME(GetMoveAccuracy(MOVE_POISONED_STARS) == 100);
    ASSUME(GetMoveCategory(MOVE_POISONED_STARS) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(GetMoveStrikeCount(MOVE_POISONED_STARS) == 3);
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_POISONED_STARS, MOVE_EFFECT_POISON, 30));
    ASSUME(MoveIgnoresResistancesIfUserPoison(MOVE_POISONED_STARS));

    ASSUME(GetMoveType(MOVE_MAGMATIC_RAGE) == TYPE_FIRE);
    ASSUME(GetMovePower(MOVE_MAGMATIC_RAGE) == 70);
    ASSUME(GetMoveAccuracy(MOVE_MAGMATIC_RAGE) == 100);
    ASSUME(GetMoveCategory(MOVE_MAGMATIC_RAGE) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_MAGMATIC_RAGE, MOVE_EFFECT_BURN, 10));

    ASSUME(GetMoveType(MOVE_SHALLOW_GRAVE) == TYPE_GROUND);
    ASSUME(GetMovePower(MOVE_SHALLOW_GRAVE) == 120);
    ASSUME(GetMoveAccuracy(MOVE_SHALLOW_GRAVE) == 80);
    ASSUME(GetMoveCategory(MOVE_SHALLOW_GRAVE) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(MoveHasAdditionalEffect(MOVE_SHALLOW_GRAVE, MOVE_EFFECT_WRAP));
    ASSUME_MOVE_EFFECT_STAT_CHANGE(MOVE_SHALLOW_GRAVE, speed: -3);

    ASSUME(GetMoveEffect(MOVE_SINKHOLE) == EFFECT_SINKHOLE);
    ASSUME(GetMoveType(MOVE_SINKHOLE) == TYPE_ROCK);
    ASSUME(GetMoveAccuracy(MOVE_SINKHOLE) == 100);
    ASSUME(GetMoveCategory(MOVE_SINKHOLE) == DAMAGE_CATEGORY_PHYSICAL);

    ASSUME(GetMoveType(MOVE_SUNBLOOM) == TYPE_GRASS);
    ASSUME(GetMovePower(MOVE_SUNBLOOM) == 60);
    ASSUME(GetMoveAccuracy(MOVE_SUNBLOOM) == 100);
    ASSUME(GetMoveCategory(MOVE_SUNBLOOM) == DAMAGE_CATEGORY_SPECIAL);
    ASSUME(MoveHasAdditionalEffectSelf(MOVE_SUNBLOOM, MOVE_EFFECT_SUNBLOOM));

    ASSUME(GetMoveEffect(MOVE_AURA_FARMING) == EFFECT_AURA_FARMING);
    ASSUME(GetMoveType(MOVE_AURA_FARMING) == TYPE_FIGHTING);
    ASSUME(GetMovePower(MOVE_AURA_FARMING) == 1);
    ASSUME(GetMoveAccuracy(MOVE_AURA_FARMING) == 100);
    ASSUME(GetMovePP(MOVE_AURA_FARMING) == 1);
    ASSUME(GetMoveTarget(MOVE_AURA_FARMING) == TARGET_BOTH);
    ASSUME(GetMoveCategory(MOVE_AURA_FARMING) == DAMAGE_CATEGORY_SPECIAL);
    ASSUME(GetMovePriority(MOVE_AURA_FARMING) < 0);

    ASSUME(GetMoveType(MOVE_WAKE_CRASH) == TYPE_WATER);
    ASSUME(GetMovePower(MOVE_WAKE_CRASH) == 120);
    ASSUME(GetMoveAccuracy(MOVE_WAKE_CRASH) == 100);
    ASSUME(GetMoveCategory(MOVE_WAKE_CRASH) == DAMAGE_CATEGORY_PHYSICAL);
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
    ASSUME(GetMoveAccuracy(MOVE_OVEREXPOSURE) == 100);
    ASSUME(GetMoveCategory(MOVE_OVEREXPOSURE) == DAMAGE_CATEGORY_SPECIAL);
    ASSUME(MoveHasAdditionalEffect(MOVE_OVEREXPOSURE, MOVE_EFFECT_OVEREXPOSURE));

    ASSUME(GetMoveType(MOVE_DRY_FULMINATION) == TYPE_ELECTRIC);
    ASSUME(GetMovePower(MOVE_DRY_FULMINATION) == 120);
    ASSUME(GetMoveAccuracy(MOVE_DRY_FULMINATION) == 70);
    ASSUME(GetMoveCategory(MOVE_DRY_FULMINATION) == DAMAGE_CATEGORY_SPECIAL);
    ASSUME(MoveAlwaysHitsInSun(MOVE_DRY_FULMINATION));
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_DRY_FULMINATION, MOVE_EFFECT_BURN, 30));

    ASSUME(GetMoveEffect(MOVE_WINDSTORM) == EFFECT_WEATHER);
    ASSUME(GetMoveType(MOVE_WINDSTORM) == TYPE_FLYING);
    ASSUME(GetMoveCategory(MOVE_WINDSTORM) == DAMAGE_CATEGORY_STATUS);
    ASSUME(GetMoveWeatherType(MOVE_WINDSTORM) == BATTLE_WEATHER_WINDSTORM);

    ASSUME(GetMoveEffect(MOVE_VINSECTICATION) == EFFECT_LAST_RESPECTS);
    ASSUME(GetMoveType(MOVE_VINSECTICATION) == TYPE_BUG);
    ASSUME(GetMovePower(MOVE_VINSECTICATION) == 50);
    ASSUME(GetMoveAccuracy(MOVE_VINSECTICATION) == 100);
    ASSUME(GetMoveCategory(MOVE_VINSECTICATION) == DAMAGE_CATEGORY_PHYSICAL);

    ASSUME(GetMoveEffect(MOVE_FUSSY_FUSS) == EFFECT_FUSSY_FUSS);
    ASSUME(GetMoveType(MOVE_FUSSY_FUSS) == TYPE_NORMAL);
    ASSUME(GetMovePower(MOVE_FUSSY_FUSS) == 75);
    ASSUME(GetMoveAccuracy(MOVE_FUSSY_FUSS) == 100);
    ASSUME(GetMoveCategory(MOVE_FUSSY_FUSS) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME_MOVE_EFFECT_STAT_CHANGE(MOVE_FUSSY_FUSS, attack: -1);

    ASSUME(GetMoveEffect(MOVE_JINX) == EFFECT_FUTURE_SIGHT);
    ASSUME(GetMoveType(MOVE_JINX) == TYPE_GHOST);
    ASSUME(GetMovePower(MOVE_JINX) == 120);
    ASSUME(GetMoveAccuracy(MOVE_JINX) == 100);
    ASSUME(GetMoveCategory(MOVE_JINX) == DAMAGE_CATEGORY_SPECIAL);
    ASSUME(MoveIgnoresProtect(MOVE_JINX));

    ASSUME(GetMoveEffect(MOVE_CRASHING_FIST) == EFFECT_CRASHING_FIST);
    ASSUME(GetMoveType(MOVE_CRASHING_FIST) == TYPE_FIGHTING);
    ASSUME(GetMovePower(MOVE_CRASHING_FIST) == 85);
    ASSUME(GetMoveAccuracy(MOVE_CRASHING_FIST) == 80);
    ASSUME(GetMoveCategory(MOVE_CRASHING_FIST) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(MoveIgnoresProtect(MOVE_CRASHING_FIST));

    ASSUME(GetMoveEffect(MOVE_HYDRAULIC_PRESS) == EFFECT_BODY_PRESS);
    ASSUME(GetMoveType(MOVE_HYDRAULIC_PRESS) == TYPE_STEEL);
    ASSUME(GetMovePower(MOVE_HYDRAULIC_PRESS) == 80);
    ASSUME(GetMoveAccuracy(MOVE_HYDRAULIC_PRESS) == 100);
    ASSUME(GetMoveCategory(MOVE_HYDRAULIC_PRESS) == DAMAGE_CATEGORY_PHYSICAL);

    ASSUME(GetMoveEffect(MOVE_ICE_RINK) == EFFECT_ICE_RINK);
    ASSUME(GetMoveType(MOVE_ICE_RINK) == TYPE_ICE);
    ASSUME(GetMoveCategory(MOVE_ICE_RINK) == DAMAGE_CATEGORY_STATUS);

    ASSUME(GetMoveEffect(MOVE_STORM_SACRIFICE) == EFFECT_STORM_SACRIFICE);
    ASSUME(GetMoveType(MOVE_STORM_SACRIFICE) == TYPE_DRAGON);
    ASSUME(GetMovePower(MOVE_STORM_SACRIFICE) == 95);
    ASSUME(GetMoveAccuracy(MOVE_STORM_SACRIFICE) == 100);
    ASSUME(GetMoveCategory(MOVE_STORM_SACRIFICE) == DAMAGE_CATEGORY_SPECIAL);

    ASSUME(GetMoveEffect(MOVE_MINERAGRAPHY) == EFFECT_MINERAGRAPHY);
    ASSUME(GetMoveType(MOVE_MINERAGRAPHY) == TYPE_ROCK);
    ASSUME(GetMoveCategory(MOVE_MINERAGRAPHY) == DAMAGE_CATEGORY_STATUS);

    ASSUME(GetMoveEffect(MOVE_SURFS_UP) == EFFECT_TWO_TYPED_MOVE);
    ASSUME(GetMoveType(MOVE_SURFS_UP) == TYPE_FIGHTING);
    ASSUME(GetMoveArgType(MOVE_SURFS_UP) == TYPE_WATER);
    ASSUME(GetMovePower(MOVE_SURFS_UP) == 100);
    ASSUME(GetMoveAccuracy(MOVE_SURFS_UP) == 95);
    ASSUME(GetMoveCategory(MOVE_SURFS_UP) == DAMAGE_CATEGORY_PHYSICAL);

    ASSUME(GetMoveType(MOVE_UNDERCURRENT) == TYPE_ELECTRIC);
    ASSUME(GetMovePower(MOVE_UNDERCURRENT) == 70);
    ASSUME(GetMoveAccuracy(MOVE_UNDERCURRENT) == 100);
    ASSUME(GetMoveCategory(MOVE_UNDERCURRENT) == DAMAGE_CATEGORY_SPECIAL);

    ASSUME(GetMoveEffect(MOVE_THIRD_DEGREE) == EFFECT_DOUBLE_POWER_ON_ARG_STATUS);
    ASSUME(GetMoveType(MOVE_THIRD_DEGREE) == TYPE_FIRE);
    ASSUME(GetMovePower(MOVE_THIRD_DEGREE) == 65);
    ASSUME(GetMoveAccuracy(MOVE_THIRD_DEGREE) == 100);
    ASSUME(GetMoveCategory(MOVE_THIRD_DEGREE) == DAMAGE_CATEGORY_SPECIAL);

    ASSUME(GetMoveEffect(MOVE_INVERSION) == EFFECT_INVERSION);
    ASSUME(GetMoveType(MOVE_INVERSION) == TYPE_NORMAL);
    ASSUME(GetMovePP(MOVE_INVERSION) == 1);
    ASSUME(GetMoveCategory(MOVE_INVERSION) == DAMAGE_CATEGORY_STATUS);

    ASSUME(GetMoveEffect(MOVE_WING_SLICER) == EFFECT_WING_SLICER);
    ASSUME(GetMoveType(MOVE_WING_SLICER) == TYPE_FLYING);
    ASSUME(GetMovePower(MOVE_WING_SLICER) == 65);
    ASSUME(GetMoveAccuracy(MOVE_WING_SLICER) == 100);
    ASSUME(GetMoveCategory(MOVE_WING_SLICER) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(GetMoveStrikeCount(MOVE_WING_SLICER) == 2);

    ASSUME(GetMoveType(MOVE_GEMINIC_BLAST) == TYPE_PSYCHIC);
    ASSUME(GetMovePower(MOVE_GEMINIC_BLAST) == 60);
    ASSUME(GetMoveAccuracy(MOVE_GEMINIC_BLAST) == 100);
    ASSUME(GetMoveCategory(MOVE_GEMINIC_BLAST) == DAMAGE_CATEGORY_SPECIAL);
    ASSUME(GetMoveStrikeCount(MOVE_GEMINIC_BLAST) == 2);
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_GEMINIC_BLAST, MOVE_EFFECT_CONFUSION, 30));

    ASSUME(GetMoveEffect(MOVE_SHOWSTOPPER) == EFFECT_SHOWSTOPPER);
    ASSUME(GetMoveType(MOVE_SHOWSTOPPER) == TYPE_WATER);
    ASSUME(GetMoveAccuracy(MOVE_SHOWSTOPPER) == 100);
    ASSUME(GetMoveCategory(MOVE_SHOWSTOPPER) == DAMAGE_CATEGORY_STATUS);

    ASSUME(GetMoveEffect(MOVE_RESEARCH) == EFFECT_RESEARCH);
    ASSUME(GetMoveType(MOVE_RESEARCH) == TYPE_NORMAL);
    ASSUME(GetMoveCategory(MOVE_RESEARCH) == DAMAGE_CATEGORY_STATUS);

    ASSUME(GetMoveEffect(MOVE_CHRYSALIS) == EFFECT_CHRYSALIS);
    ASSUME(GetMoveType(MOVE_CHRYSALIS) == TYPE_BUG);
    ASSUME(GetMoveCategory(MOVE_CHRYSALIS) == DAMAGE_CATEGORY_STATUS);
    ASSUME(GetMoveProtectMethod(MOVE_CHRYSALIS) == PROTECT_CHRYSALIS);

    ASSUME(GetMoveEffect(MOVE_CASTING_CALL) == EFFECT_CASTING_CALL);
    ASSUME(GetMoveType(MOVE_CASTING_CALL) == TYPE_ELECTRIC);
    ASSUME(GetMoveCategory(MOVE_CASTING_CALL) == DAMAGE_CATEGORY_STATUS);

    ASSUME(GetMoveEffect(MOVE_MOUNTING_PRESSURE) == EFFECT_MOUNTING_PRESSURE);
    ASSUME(GetMoveType(MOVE_MOUNTING_PRESSURE) == TYPE_GROUND);
    ASSUME(GetMoveCategory(MOVE_MOUNTING_PRESSURE) == DAMAGE_CATEGORY_STATUS);

    ASSUME(GetMoveEffect(MOVE_JET_STREAM) == EFFECT_JET_STREAM);
    ASSUME(GetMoveType(MOVE_JET_STREAM) == TYPE_FLYING);
    ASSUME(GetMovePower(MOVE_JET_STREAM) == 100);
    ASSUME(GetMoveAccuracy(MOVE_JET_STREAM) == 95);
    ASSUME(GetMoveCategory(MOVE_JET_STREAM) == DAMAGE_CATEGORY_PHYSICAL);

    ASSUME(GetMoveEffect(MOVE_STUNT_DOUBLE) == EFFECT_STUNT_DOUBLE);
    ASSUME(GetMoveType(MOVE_STUNT_DOUBLE) == TYPE_ICE);
    ASSUME(GetMoveCategory(MOVE_STUNT_DOUBLE) == DAMAGE_CATEGORY_STATUS);

    ASSUME(GetMoveType(MOVE_CALAMITY_CLEAVE) == TYPE_DRAGON);
    ASSUME(GetMovePower(MOVE_CALAMITY_CLEAVE) == 130);
    ASSUME(GetMoveAccuracy(MOVE_CALAMITY_CLEAVE) == 100);
    ASSUME(GetMoveCategory(MOVE_CALAMITY_CLEAVE) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(MoveCantBeUsedTwice(MOVE_CALAMITY_CLEAVE));
    ASSUME(IsSlicingMove(MOVE_CALAMITY_CLEAVE));

    ASSUME(GetMoveEffect(MOVE_PSIDEKICK) == EFFECT_PSIDEKICK);
    ASSUME(GetMoveType(MOVE_PSIDEKICK) == TYPE_NORMAL);
    ASSUME(GetMovePower(MOVE_PSIDEKICK) == 60);
    ASSUME(GetMoveAccuracy(MOVE_PSIDEKICK) == 100);
    ASSUME(GetMoveCategory(MOVE_PSIDEKICK) == DAMAGE_CATEGORY_PHYSICAL);

    ASSUME(GetMoveEffect(MOVE_MOSH_PIT) == EFFECT_MOSH_PIT);
    ASSUME(GetMoveType(MOVE_MOSH_PIT) == TYPE_POISON);
    ASSUME(GetMoveAccuracy(MOVE_MOSH_PIT) == 100);
    ASSUME(GetMoveCategory(MOVE_MOSH_PIT) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(MoveHasAdditionalEffectWithChance(MOVE_MOSH_PIT, MOVE_EFFECT_POISON, 10));

    ASSUME(GetMoveEffect(MOVE_SYNCHRONIZED_SWIM) == EFFECT_SYNCHRONIZED_SWIM);
    ASSUME(GetMoveType(MOVE_SYNCHRONIZED_SWIM) == TYPE_WATER);
    ASSUME(GetMovePower(MOVE_SYNCHRONIZED_SWIM) == 70);
    ASSUME(GetMoveAccuracy(MOVE_SYNCHRONIZED_SWIM) == 100);
    ASSUME(GetMoveCategory(MOVE_SYNCHRONIZED_SWIM) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(GetMoveStrikeCount(MOVE_SYNCHRONIZED_SWIM) == 2);
}

SINGLE_BATTLE_TEST("Custom Moves - Rock Heart may infatuate the target")
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

SINGLE_BATTLE_TEST("Custom Moves - Riptide halves the target's current HP")
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

SINGLE_BATTLE_TEST("Custom Moves - Arc Fault makes the user faint and sets Electric Terrain")
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

SINGLE_BATTLE_TEST("Custom Moves - Grasspiercer can badly poison, paralyze, or put the target to sleep")
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

SINGLE_BATTLE_TEST("Custom Moves - Psyche Lock prevents hit-and-switch moves from switching out")
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

SINGLE_BATTLE_TEST("Custom Moves - Psyche Lock prevents Shed Shell switching")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_SHED_SHELL].holdEffect == HOLD_EFFECT_SHED_SHELL);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_SHED_SHELL); Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_PSYCHE_LOCK); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHE_LOCK, player);
        NONE_OF {
            MESSAGE("Wobbuffet, that's enough! Come back!");
            MESSAGE("Wobbuffet, come back!");
            MESSAGE("Wobbuffet, OK! Come back!");
            MESSAGE("Wobbuffet, good! Come back!");
            MESSAGE("Go! Wynaut!");
            MESSAGE("You're in charge, Wynaut!");
            MESSAGE("Go for it, Wynaut!");
            MESSAGE("Your opponent's weak! Get 'em, Wynaut!");
        }
    } THEN {
        enum BattlerId battler = opponent - gBattleMons;
        EXPECT(opponent->volatiles.strictEscapePrevention);
        EXPECT(!CanBattlerEscape(battler));
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Poisoned Stars hits 3 times and can poison on each hit")
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

SINGLE_BATTLE_TEST("Custom Moves - Poisoned Stars ignores Poison resistance when used by a Poison-type Pokemon", s16 damage)
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

SINGLE_BATTLE_TEST("Custom Moves - Magmatic Rage is super effective against Rock and Ground types")
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

SINGLE_BATTLE_TEST("Custom Moves - Shallow Grave traps the target and lowers Speed by 3 stages")
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

SINGLE_BATTLE_TEST("Custom Moves - Sinkhole deals less damage to airborne targets and more damage during Gravity", s16 damage)
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

SINGLE_BATTLE_TEST("Custom Moves - Sunbloom sets sunlight for 5 turns or 8 turns if it KOs")
{
    u32 hp, remainingDuration;
    PARAMETRIZE { hp = 999; remainingDuration = 4; }
    PARAMETRIZE { hp = 1; remainingDuration = 8; }
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

SINGLE_BATTLE_TEST("Custom Moves - Sunbloom does not reset existing sunlight")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(999); MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_SUNNY_DAY); }
        TURN { MOVE(player, MOVE_SUNBLOOM); }
    } THEN {
        EXPECT(gBattleWeather & B_WEATHER_SUN_NORMAL);
        EXPECT_EQ(gBattleStruct->weatherDuration, 3);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Sunbloom is stronger in sunlight", s16 damage)
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

SINGLE_BATTLE_TEST("Custom Moves - Aura Farming reflects damage received before moving")
{
    s16 receivedDamage;
    s16 reflectedDamage;

    GIVEN {
        ASSUME(GetMoveCategory(MOVE_POUND) == DAMAGE_CATEGORY_PHYSICAL);
        PLAYER(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_AURA_FARMING); MOVE(opponent, MOVE_POUND); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, opponent);
        HP_BAR(player, captureDamage: &receivedDamage);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AURA_FARMING, player);
        HP_BAR(opponent, captureDamage: &reflectedDamage);
    } THEN {
        EXPECT_MUL_EQ(receivedDamage, Q_4_12(2.0), reflectedDamage);
    }
}

DOUBLE_BATTLE_TEST("Custom Moves - Aura Farming hits both opponents for twice the total damage received")
{
    s16 receivedDamage[2];
    s16 reflectedDamage[2];

    GIVEN {
        ASSUME(GetMoveCategory(MOVE_POUND) == DAMAGE_CATEGORY_PHYSICAL);
        ASSUME(GetMoveCategory(MOVE_WATER_GUN) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_WOBBUFFET) { Speed(1); HP(999); MaxHP(999); }
        PLAYER(SPECIES_WYNAUT) { Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_WYNAUT) { Speed(90); }
    } WHEN {
        TURN {
            MOVE(playerLeft, MOVE_AURA_FARMING);
            MOVE(playerRight, MOVE_CELEBRATE);
            MOVE(opponentLeft, MOVE_POUND, target: playerLeft);
            MOVE(opponentRight, MOVE_WATER_GUN, target: playerLeft);
        }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, opponentLeft);
        HP_BAR(playerLeft, captureDamage: &receivedDamage[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponentRight);
        HP_BAR(playerLeft, captureDamage: &receivedDamage[1]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AURA_FARMING, playerLeft);
        HP_BAR(opponentLeft, captureDamage: &reflectedDamage[0]);
        HP_BAR(opponentRight, captureDamage: &reflectedDamage[1]);
    } THEN {
        EXPECT_EQ(reflectedDamage[0], (receivedDamage[0] + receivedDamage[1]) * 2);
        EXPECT_EQ(reflectedDamage[1], (receivedDamage[0] + receivedDamage[1]) * 2);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Aura Farming survives lethal damage until it reflects")
{
    GIVEN {
        ASSUME(GetMovePower(MOVE_HYPER_BEAM) > 100);
        PLAYER(SPECIES_WOBBUFFET) { Speed(1); HP(10); MaxHP(10); Defense(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Attack(255); }
    } WHEN {
        TURN { MOVE(player, MOVE_AURA_FARMING); MOVE(opponent, MOVE_HYPER_BEAM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_BEAM, opponent);
        HP_BAR(player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AURA_FARMING, player);
        HP_BAR(opponent);
        HP_BAR(player);
        MESSAGE("Wobbuffet fainted!");
    } THEN {
        EXPECT_EQ(player->hp, 0);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Wake Crash applies 20 percent recoil")
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

SINGLE_BATTLE_TEST("Custom Moves - Razzle Dazzle doubles on consecutive use up to 300 BP")
{
    s16 damage[4];
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { SpAttack(50); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(9999); MaxHP(9999); SpDefense(50); }
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

SINGLE_BATTLE_TEST("Custom Moves - Steelsurge sets sharp steel on the opposing side")
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

SINGLE_BATTLE_TEST("Custom Moves - Overexposure makes its target weak to Ice for the rest of battle")
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

SINGLE_BATTLE_TEST("Custom Moves - Dry Fulmination cannot miss in sun and may burn")
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

SINGLE_BATTLE_TEST("Custom Moves - Windstorm sets windstorm for 5 turns")
{
    enum Item item;

    PARAMETRIZE { item = ITEM_NONE; }
    PARAMETRIZE { item = ITEM_DAMP_ROCK; }
    PARAMETRIZE { item = ITEM_HEAT_ROCK; }
    PARAMETRIZE { item = ITEM_SMOOTH_ROCK; }
    PARAMETRIZE { item = ITEM_ICY_ROCK; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(item); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WINDSTORM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WINDSTORM, player);
        MESSAGE("A windstorm kicked up!");
        MESSAGE("The windstorm is raging.");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_TAILWIND);
        NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STRONG_WINDS);
    } THEN {
        EXPECT(gBattleWeather & B_WEATHER_WINDSTORM);
        EXPECT(!(gBattleWeather & B_WEATHER_STRONG_WINDS));
        EXPECT_EQ(gBattleStruct->weatherDuration, 4);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Windstorm can be replaced by other weather")
{
    enum Move move;
    u32 expectedWeather;

    PARAMETRIZE { move = MOVE_RAIN_DANCE; expectedWeather = B_WEATHER_RAIN_NORMAL; }
    PARAMETRIZE { move = MOVE_SUNNY_DAY; expectedWeather = B_WEATHER_SUN_NORMAL; }
    PARAMETRIZE { move = MOVE_SANDSTORM; expectedWeather = B_WEATHER_SANDSTORM; }
    PARAMETRIZE { move = MOVE_SNOWSCAPE; expectedWeather = B_WEATHER_SNOW; }
    GIVEN {
        ASSUME(GetMoveEffect(move) == EFFECT_WEATHER);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WINDSTORM); }
        TURN { MOVE(player, move); }
    } THEN {
        EXPECT(gBattleWeather & expectedWeather);
        EXPECT_EQ(gBattleStruct->weatherDuration, 4);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Windstorm boosts Flying-type attacks", s16 damage)
{
    u32 setupMove;
    PARAMETRIZE { setupMove = MOVE_CELEBRATE; }
    PARAMETRIZE { setupMove = MOVE_WINDSTORM; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, setupMove); }
        TURN { MOVE(player, MOVE_GUST, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GUST, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Windstorm removes Flying-type weaknesses", s16 damage)
{
    u32 setupMove;
    PARAMETRIZE { setupMove = MOVE_CELEBRATE; }
    PARAMETRIZE { setupMove = MOVE_WINDSTORM; }
    GIVEN {
        ASSUME(GetMoveType(MOVE_THUNDER_SHOCK) == TYPE_ELECTRIC);
        ASSUME(GetSpeciesType(SPECIES_PIDGEY, 1) == TYPE_FLYING);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY);
    } WHEN {
        TURN { MOVE(player, setupMove); }
        TURN { MOVE(player, MOVE_THUNDER_SHOCK); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THUNDER_SHOCK, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Vinsectication gains power for fainted party members", s16 damage)
{
    u32 j, faintCount;
    PARAMETRIZE { faintCount = 0; }
    PARAMETRIZE { faintCount = 1; }
    GIVEN {
        PLAYER(SPECIES_HITMONLEE);
        PLAYER(SPECIES_GEODUDE);
        OPPONENT(SPECIES_TAUROS) { Item(ITEM_LEPPA_BERRY); Moves(MOVE_RECYCLE, MOVE_NONE, MOVE_NONE, MOVE_NONE); }
    } WHEN {
        for (j = 0; j < faintCount; j++)
        {
            TURN { MOVE(opponent, MOVE_RECYCLE); SWITCH(player, 1); }
            TURN { MOVE(opponent, MOVE_RECYCLE); MOVE(player, MOVE_MEMENTO); SEND_OUT(player, 0); }
            TURN { MOVE(opponent, MOVE_RECYCLE); USE_ITEM(player, ITEM_REVIVE, partyIndex: 1); }
        }
        TURN { MOVE(opponent, MOVE_RECYCLE); MOVE(player, MOVE_VINSECTICATION, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_VINSECTICATION, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Fussy Fuss doubles when the user is below half HP and lowers Attack", s16 damage)
{
    u32 hp;
    PARAMETRIZE { hp = 200; }
    PARAMETRIZE { hp = 100; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(hp); MaxHP(200); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FUSSY_FUSS, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FUSSY_FUSS, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_ATK], DEFAULT_STAT_STAGE - 1);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Jinx hits the switched-in Pokemon two turns later")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_JINX); }
        TURN { SWITCH(opponent, 1); }
        TURN {}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_JINX, player);
        MESSAGE("The opposing Wynaut took the Jinx attack!");
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Jinx ignores Wonder Guard")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SQUIRTLE) { Ability(ABILITY_WONDER_GUARD); }
    } WHEN {
        TURN { MOVE(player, MOVE_JINX); }
        TURN {}
        TURN {}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_JINX, player);
        MESSAGE("The opposing Squirtle took the Jinx attack!");
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Jinx ignores Protect and Endure")
{
    enum Move defensiveMove;
    PARAMETRIZE { defensiveMove = MOVE_PROTECT; }
    PARAMETRIZE { defensiveMove = MOVE_ENDURE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(400); Moves(defensiveMove); }
    } WHEN {
        TURN { MOVE(player, MOVE_JINX); }
        TURN {}
        TURN { MOVE(opponent, defensiveMove); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_JINX, player);
        MESSAGE("The opposing Wobbuffet took the Jinx attack!");
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(opponent->hp, 0);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Crashing Fist damages protected targets for one-third damage", s16 damage)
{
    u32 protectMove;
    PARAMETRIZE { protectMove = MOVE_CELEBRATE; }
    PARAMETRIZE { protectMove = MOVE_PROTECT; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Attack(200); }
        OPPONENT(SPECIES_WOBBUFFET) { Defense(100); }
    } WHEN {
        TURN { MOVE(opponent, protectMove); MOVE(player, MOVE_CRASHING_FIST, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CRASHING_FIST, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[0].damage, results[1].damage);
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(3.0), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Hydraulic Press uses the user's Defense", s16 damage)
{
    u32 def, atk;
    PARAMETRIZE { def = 100; atk = 200; }
    PARAMETRIZE { def = 200; atk = 100; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Attack(atk); Defense(def); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HYDRAULIC_PRESS, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYDRAULIC_PRESS, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Ice Rink makes grounded non-Ice switch-ins move last for one turn")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(50); }
        OPPONENT(SPECIES_RATTATA) { Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_ICE_RINK); }
        TURN { MOVE(player, MOVE_CELEBRATE); SWITCH(opponent, 1); }
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ICE_RINK, player);
        MESSAGE("The opposing Rattata slid on the ice!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player);
    } THEN {
        EXPECT(!opponent->volatiles.iceRink);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Ice Rink is removed by grounded Fire-type switch-ins")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_CHARMANDER);
    } WHEN {
        TURN { MOVE(player, MOVE_ICE_RINK); }
        TURN { MOVE(player, MOVE_CELEBRATE); SWITCH(opponent, 1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ICE_RINK, player);
        MESSAGE("The ice around the opposing team melted away!");
    } THEN {
        EXPECT(!IsHazardOnSide(B_SIDE_OPPONENT, HAZARDS_ICE_RINK));
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Storm Sacrifice sets rain when it knocks out the target")
{
    u32 hp;
    PARAMETRIZE { hp = 999; }
    PARAMETRIZE { hp = 1; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(hp); MaxHP(999); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        if (hp == 1) {
            TURN { MOVE(player, MOVE_STORM_SACRIFICE); SEND_OUT(opponent, 1); }
        } else {
            TURN { MOVE(player, MOVE_STORM_SACRIFICE); }
        }
    } THEN {
        if (hp == 1)
            EXPECT(gBattleWeather & B_WEATHER_RAIN_NORMAL);
        else
            EXPECT(!(gBattleWeather & B_WEATHER_RAIN));
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Mineragraphy raises the user's two lowest stats by three stages")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_MINERAGRAPHY); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 3);
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 3);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Surf's Up deals Fighting and Water type damage", s16 damage)
{
    enum Move move;
    PARAMETRIZE { move = MOVE_BRICK_BREAK; }
    PARAMETRIZE { move = MOVE_SURFS_UP; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Attack(200); }
        OPPONENT(SPECIES_NUMEL) { Defense(100); }
    } WHEN {
        TURN { MOVE(player, move, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Undercurrent is super effective against Ground")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_DIGLETT);
    } WHEN {
        TURN { MOVE(player, MOVE_UNDERCURRENT); }
    } SCENE {
        HP_BAR(opponent);
        MESSAGE("It's super effective!");
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Third Degree doubles in power against burned targets", s16 damage)
{
    bool32 burned;
    PARAMETRIZE { burned = FALSE; }
    PARAMETRIZE { burned = TRUE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { SpAttack(200); }
        OPPONENT(SPECIES_WOBBUFFET) { SpDefense(100); if (burned) Status1(STATUS1_BURN); }
    } WHEN {
        TURN { MOVE(player, MOVE_THIRD_DEGREE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Inversion toggles inverse type matchups")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_VAPOREON) { Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_INVERSION); }
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        MESSAGE("Type matchups were inverted!");
        HP_BAR(opponent);
        MESSAGE("It's super effective!");
    } THEN {
        EXPECT(IsTypeChartInverted());
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Inversion restores the normal type chart when used again")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_INVERSION); }
    } WHEN {
        TURN { MOVE(player, MOVE_INVERSION); MOVE(opponent, MOVE_INVERSION); }
    } SCENE {
        MESSAGE("Type matchups were inverted!");
        MESSAGE("Type matchups returned to normal!");
    } THEN {
        EXPECT(!IsTypeChartInverted());
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Wing Slicer only hits twice if the user acts before opposing foes", s16 damage)
{
    u32 playerSpeed, opponentSpeed;
    PARAMETRIZE { playerSpeed = 200; opponentSpeed = 100; }
    PARAMETRIZE { playerSpeed = 100; opponentSpeed = 200; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(playerSpeed); Attack(200); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(opponentSpeed); Defense(100); Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_WING_SLICER, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        results[i].damage = opponent->maxHP - opponent->hp;
    } FINALLY {
        EXPECT_GT(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Geminic Blast may confuse on either hit")
{
    PASSES_RANDOMLY(30, 100, RNG_SECONDARY_EFFECT);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_GEMINIC_BLAST); }
    } SCENE {
        HP_BAR(opponent);
        HP_BAR(opponent);
    } THEN {
        u32 confusionTurns = opponent->volatiles.confusionTurns;
        EXPECT_GT(confusionTurns, 0);
    }
}

DOUBLE_BATTLE_TEST("Custom Moves - Showstopper redirects attacks and lowers two random stats")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_WYNAUT) { Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SHOWSTOPPER); MOVE(opponentLeft, MOVE_TACKLE, target: playerRight); MOVE(playerRight, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SHOWSTOPPER, playerLeft);
        MESSAGE("Wobbuffet became the center of attention!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, opponentLeft);
        HP_BAR(playerLeft);
    } THEN {
        u32 loweredStats = 0;
        for (enum Stat stat = STAT_ATK; stat < NUM_BATTLE_STATS; stat++)
        {
            if (opponentLeft->statStages[stat] < DEFAULT_STAT_STAGE)
                loweredStats++;
        }
        EXPECT_EQ(loweredStats, 2);
    }
}

AI_SINGLE_BATTLE_TEST("Custom Moves - AI values Rock Heart's infatuation chance")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY);
        PLAYER(SPECIES_NIDOQUEEN);
        OPPONENT(SPECIES_NIDOKING) { Moves(MOVE_ROCK_HEART, MOVE_CELEBRATE); }
    } WHEN {
        TURN { SCORE_GT_VAL(opponent, MOVE_ROCK_HEART, AI_SCORE_DEFAULT); }
    }
}

AI_SINGLE_BATTLE_TEST("Custom Moves - AI values Grasspiercer's random status chance")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_GRASSPIERCER, MOVE_CELEBRATE); }
    } WHEN {
        TURN { SCORE_GT_VAL(opponent, MOVE_GRASSPIERCER, AI_SCORE_DEFAULT); }
    }
}

AI_DOUBLE_BATTLE_TEST("Custom Moves - AI scores Sunbloom as sun setup for its ally")
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

AI_SINGLE_BATTLE_TEST("Custom Moves - AI scores Steelsurge as a hazard")
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

AI_SINGLE_BATTLE_TEST("Custom Moves - AI scores Overexposure as Ice support")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_OVEREXPOSURE, MOVE_AURORA_BEAM); }
    } WHEN {
        TURN { SCORE_GT(opponent, MOVE_OVEREXPOSURE, MOVE_AURORA_BEAM); }
    }
}

AI_SINGLE_BATTLE_TEST("Custom Moves - AI scores Windstorm as Flying support")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_POWERFUL_STATUS);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_WINDSTORM, MOVE_GUST); }
    } WHEN {
        TURN { SCORE_GT(opponent, MOVE_WINDSTORM, MOVE_GUST); }
    }
}

AI_SINGLE_BATTLE_TEST("Custom Moves - AI scores Ice Rink as a hazard")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_POWERFUL_STATUS);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_ICE_RINK, MOVE_CELEBRATE); }
    } WHEN {
        TURN { EXPECT_MOVE(opponent, MOVE_ICE_RINK); }
    }
}

AI_SINGLE_BATTLE_TEST("Custom Moves - AI scores Mineragraphy as setup")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_POWERFUL_STATUS);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_MINERAGRAPHY, MOVE_CELEBRATE); }
    } WHEN {
        TURN { SCORE_GT(opponent, MOVE_MINERAGRAPHY, MOVE_CELEBRATE); }
    }
}

AI_SINGLE_BATTLE_TEST("Custom Moves - AI uses Inversion as soon as possible")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_POWERFUL_STATUS);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_INVERSION, MOVE_PSYCHIC); }
    } WHEN {
        TURN { EXPECT_MOVE(opponent, MOVE_INVERSION); }
    }
}

AI_SINGLE_BATTLE_TEST("Custom Moves - AI does not use Inversion while type matchups are already inverted")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_POWERFUL_STATUS);
        FLAG_SET(B_FLAG_INVERSE_BATTLE);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_INVERSION, MOVE_PSYCHIC); }
    } WHEN {
        TURN { SCORE_GT(opponent, MOVE_PSYCHIC, MOVE_INVERSION); }
    }
}

AI_DOUBLE_BATTLE_TEST("Custom Moves - AI scores Showstopper as redirection support")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_DOUBLE_BATTLE | AI_FLAG_POWERFUL_STATUS);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_SHOWSTOPPER, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WYNAUT) { Moves(MOVE_TACKLE); }
    } WHEN {
        TURN { SCORE_GT(opponentLeft, MOVE_SHOWSTOPPER, MOVE_CELEBRATE, target: playerLeft); }
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Research raises offenses if the user is not attacked")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(5); }
    } WHEN {
        TURN { MOVE(player, MOVE_RESEARCH); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 2);
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 2);
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Research raises defenses if the user is attacked")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(5); }
    } WHEN {
        TURN { MOVE(player, MOVE_RESEARCH); MOVE(opponent, MOVE_SCRATCH); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 2);
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 2);
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Chrysalis protects and heals if hit")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(200); HP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CHRYSALIS); MOVE(opponent, MOVE_SCRATCH); }
    } THEN {
        EXPECT_EQ(player->hp, 150);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Casting Call switches out and charges the replacement")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_CASTING_CALL); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CASTING_CALL); SEND_OUT(player, 1); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("Wynaut was charged with power!");
    } THEN {
        EXPECT_EQ(player->species, SPECIES_WYNAUT);
        EXPECT(player->volatiles.chargeTimer > 0);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Orbital Pull charges then boosts offenses and sets gravity")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MOUNTING_PRESSURE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { SKIP_TURN(player); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 2);
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 2);
        EXPECT(gFieldStatuses & STATUS_FIELD_GRAVITY);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Jet Stream grants Wind Rider after attacking until end of turn")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(10); Ability(ABILITY_NONE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(5); }
    } WHEN {
        TURN { MOVE(player, MOVE_JET_STREAM); MOVE(opponent, MOVE_GUST); }
    } THEN {
        EXPECT(!player->volatiles.jetStreamWindRider);
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Stunt Double bursts when its substitute is broken")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(200); HP(200); Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(200); HP(200); Speed(5); Attack(500); }
    } WHEN {
        TURN { MOVE(player, MOVE_STUNT_DOUBLE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_SCRATCH); }
    } THEN {
        EXPECT_EQ(opponent->hp, 163);
        EXPECT(opponent->status1 & STATUS1_FROSTBITE);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Calamity Cleave cannot be used twice in a row")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_CALAMITY_CLEAVE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CALAMITY_CLEAVE); }
        TURN { FORCED_MOVE(player); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CALAMITY_CLEAVE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STRUGGLE, player);
    }
}

DOUBLE_BATTLE_TEST("Custom Moves - Psidekick doubles in power if an ally uses a Psychic move")
{
    u16 hpWithPsychic = 0;
    u16 hpWithoutPsychic = 0;

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Attack(100); Speed(10); }
        PLAYER(SPECIES_WYNAUT) { Speed(5); }
        OPPONENT(SPECIES_WOBBUFFET) { Defense(100); HP(400); MaxHP(400); Speed(4); }
        OPPONENT(SPECIES_WYNAUT) { Speed(3); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_PSIDEKICK, target: opponentLeft); MOVE(playerRight, MOVE_CONFUSION, target: opponentRight); }
    } THEN {
        hpWithPsychic = opponentLeft->hp;
    } GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Attack(100); Speed(10); }
        PLAYER(SPECIES_WYNAUT) { Speed(5); }
        OPPONENT(SPECIES_WOBBUFFET) { Defense(100); HP(400); MaxHP(400); Speed(4); }
        OPPONENT(SPECIES_WYNAUT) { Speed(3); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_PSIDEKICK, target: opponentLeft); MOVE(playerRight, MOVE_TACKLE, target: opponentRight); }
    } THEN {
        hpWithoutPsychic = opponentLeft->hp;
        EXPECT_GT(hpWithoutPsychic, hpWithPsychic);
    }
}

SINGLE_BATTLE_TEST("Custom Moves - Mosh Pit hits once for each healthy party member")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Attack(100); }
        PLAYER(SPECIES_WYNAUT);
        PLAYER(SPECIES_ABRA);
        OPPONENT(SPECIES_WOBBUFFET) { Defense(100); HP(400); MaxHP(400); }
    } WHEN {
        TURN { MOVE(player, MOVE_MOSH_PIT); }
    } SCENE {
        MESSAGE("The Pokémon was hit 3 time(s)!");
    }
}

DOUBLE_BATTLE_TEST("Custom Moves - Synchroswim is repeated by the user's ally with the ally's stats")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Attack(50); Speed(20); }
        PLAYER(SPECIES_WYNAUT) { Attack(300); Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Defense(100); HP(400); MaxHP(400); Speed(4); }
        OPPONENT(SPECIES_WYNAUT) { Speed(3); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SYNCHRONIZED_SWIM, target: opponentLeft); MOVE(playerRight, MOVE_CELEBRATE); MOVE(opponentLeft, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SYNCHRONIZED_SWIM, playerLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SYNCHRONIZED_SWIM, playerRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerRight);
    } THEN {
        EXPECT_LT(opponentLeft->hp, 300);
    }
}
