#pragma once

#include "gm.h"
#include "states.h"

int  game_populate_entities(Game* game, STTiconf* conf);
void game_depopulate_entities(Game* game);
void game_handle_window_events(Game* game);
void game_update(Game* game);
int  game_save(STTiconf* conf);
