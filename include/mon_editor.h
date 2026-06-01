#ifndef MON_EDITOR_H
#define MON_EDITOR_H

#include "gba/types.h"
#include "main.h"

/*
 * Entry tasks for the different versions of the UI. In `start_menu.c', we'll launch a task using one of
 * these functions. You can change which is used to change which menu is launched.
 */

void Task_OpenPokemonEditor(u8 taskId);

#endif
