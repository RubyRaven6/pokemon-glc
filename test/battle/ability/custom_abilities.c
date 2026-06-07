#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Mettle raises Sp. Attack by one stage after directly causing a Pokemon to faint")
{
    GIVEN {
        ASSUME(GetMoveTarget(MOVE_DISCHARGE) == TARGET_FOES_AND_ALLY);
        PLAYER(SPECIES_PYROAR) { Ability(ABILITY_METTLE); }
        PLAYER(SPECIES_SNORUNT) { HP(1); }
        OPPONENT(SPECIES_GLALIE) { HP(1); }
        OPPONENT(SPECIES_ABRA) { HP(1); }
        OPPONENT(SPECIES_ABRA);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_DISCHARGE); SEND_OUT(opponentLeft, 2); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DISCHARGE, playerLeft);
        MESSAGE("The opposing Glalie fainted!");
        MESSAGE("Snorunt fainted!");
        MESSAGE("The opposing Abra fainted!");
        ABILITY_POPUP(playerLeft, ABILITY_METTLE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
        MESSAGE("Pyroar's Sp. Atk rose drastically!");
    } THEN {
        EXPECT_EQ(playerLeft->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 3);
    }
}