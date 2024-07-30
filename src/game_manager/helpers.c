#include "../logger.h"
#include "helpers.h"
#include "gm.h"

int game_populate_entities(Game* game, int g_cs, int g_ccx, int g_ccy)
{
  game->entities.grid = GRID_create(&game->window->dimensions, g_cs, g_ccx, g_ccy);
  if (game->entities.grid == NULL)
  {
    LOGGERR("GRID_create", 0, "");
    game_depopulate_entities(game);
    return 1;
  }

  return 0;
}

void game_depopulate_entities(Game* game)
{
  GRID_destroy(&game->entities.grid);
}

void game_handle_events(Game* game)
{
  WINDOW_update_events(game->window, &game->events);

  if (game->events.quit || game->events.input.q) game->running = false;
}
