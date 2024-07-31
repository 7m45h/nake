#include <SDL2/SDL_keycode.h>
#include <stdbool.h>
#include <time.h>

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

  game->entities.nake = NAKE_create(game->entities.grid);
  if (game->entities.nake == NULL)
  {
    LOGGERR("NAKE_create", 0, "");
    game_depopulate_entities(game);
    return 1;
  }

  APPLE_init(&game->entities.apple, game->entities.grid);

  return 0;
}

void game_depopulate_entities(Game* game)
{
  NAKE_free(&game->entities.nake);
  GRID_destroy(&game->entities.grid);
}

void game_handle_events(Game* game)
{
  if (game->events.quit || game->events.key == SDLK_q) game->running = false;

  if (game->events.window_resize)
  {
    GRID_align_center(game->entities.grid, &game->window->dimensions);
    NAKE_counter_offset(game->entities.nake, game->entities.grid);
    APPLE_counter_offset(&game->entities.apple, &game->entities.grid->offset);
    game->events.window_resize = false;
  }
}

void game_update(Game* game)
{
  NAKE_update(game->entities.nake, game->entities.grid, game->events.key);
  FEAST feast = NAKE_eat_apple(game->entities.nake, &game->entities.apple);
  if (feast == ATE)
    APPLE_set_rand_position(&game->entities.apple, game->entities.grid);
  else if (feast == ERROR)
    game->interrupt = true;
}
