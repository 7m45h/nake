#pragma once

#include "gm.h"
#include "states.h"

int  game_populate_entities(Game* game, int g_cs, int g_ccx, int g_ccy);
void game_depopulate_entities(Game* game);
void game_handle_events(Game* game);
