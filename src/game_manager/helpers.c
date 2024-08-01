#include <SDL2/SDL_keycode.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include "../file_manager/file_manager.h"
#include "../logger.h"
#include "helpers.h"
#include "gm.h"

int game_populate_entities(Game* game, STTiconf* conf)
{
  game->entities.grid = GRID_create(&game->window->dimensions, conf->grid_cell_size, conf->grid_cell_count_x, conf->grid_cell_count_y);
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

  int hud_status = HUD_init(&game->entities.hud, game->entities.grid->cell_size, conf->p_high_score);
  if (hud_status != 0)
  {
    LOGGERR("HUD_init", 0, "");
    game_depopulate_entities(game);
    return 1;
  }

  hud_status = HUD_update_score_board(&game->entities.hud, game->window->renderer, game->entities.grid, 0);
  if (hud_status != 0)
  {
    LOGGERR("HUD_update_score_board", 0, "");
    game_depopulate_entities(game);
    return 1;
  }

  return 0;
}

void game_depopulate_entities(Game* game)
{
  HUD_deinit(&game->entities.hud);
  NAKE_free(&game->entities.nake);
  GRID_destroy(&game->entities.grid);
}

void game_handle_events(Game* game)
{
  if (game->events.quit || game->events.key == SDLK_q) game->running = false;

  if (game->events.window_resize)
  {
    GRID_align_center(game->entities.grid, &game->window->dimensions);
    NAKE_counter_offset(game->entities.nake, &game->entities.grid->offset);
    APPLE_counter_offset(&game->entities.apple, &game->entities.grid->offset);
    HUD_counter_offset(&game->entities.hud, &game->entities.grid->offset);
    game->events.window_resize = false;
  }
}

void game_update(Game* game)
{
  NAKE_update(game->entities.nake, game->entities.grid, game->events.key);
  FEAST feast = NAKE_eat_apple(game->entities.nake, &game->entities.apple);
  if (feast == ATE)
  {
    APPLE_set_rand_position(&game->entities.apple, game->entities.grid);
    int hud_status = HUD_update_score_board(&game->entities.hud, game->window->renderer, game->entities.grid, game->entities.nake->tail_len);
    if (hud_status != 0) game->interrupt = true;
  }
  else if (feast == ERROR) game->interrupt = true;
}

int game_save(STTiconf* conf)
{
  char data_str[32] = "";
  int status = sprintf(data_str, "%04X%04X%04X%04X%04X\n", conf->grid_cell_size, conf->grid_cell_count_x, conf->grid_cell_count_y, conf->update_interval, conf->p_high_score);
  if (status < 0)
  {
    LOGGERR("sprintf", errno, strerror(errno));
    return 1;
  }

  size_t data_str_len = strlen(data_str);
  status = FM_write(GAME_SAVE_FILE_PATH, data_str, data_str_len, sizeof(char));
  if (status != 0)
  {
    LOGGERR("FM_write", status, "unknown");
    return 1;
  }

  return 0;
}
