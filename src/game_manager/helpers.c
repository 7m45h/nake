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
    LOGGPERR("GRID_create");
    game_depopulate_entities(game);
    return 1;
  }

  game->entities.nake = NAKE_create(game->entities.grid);
  if (game->entities.nake == NULL)
  {
    LOGGPERR("NAKE_create");
    game_depopulate_entities(game);
    return 1;
  }

  APPLE_init(&game->entities.apple, game->entities.grid);

  game->entities.hud = HUD_init(conf->p_high_score);
  if (game->entities.hud == NULL)
  {
    LOGGPERR("HUD_init");
    game_depopulate_entities(game);
    return 1;
  }

  int hud_status = HUD_update_score_board_score(game->entities.hud, game->window->renderer, game->entities.grid, 0);
  if (hud_status != 0)
  {
    LOGGPERR("HUD_update_score_board_score");
    game_depopulate_entities(game);
    return 1;
  }

  hud_status = HUD_update_score_board_hscore(game->entities.hud, game->window->renderer, game->entities.grid, conf->p_high_score);
  if (hud_status != 0)
  {
    LOGGPERR("HUD_update_score_board_hscore");
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

void game_handle_window_events(Game* game)
{
  while (SDL_PollEvent(&game->window->event))
  {
    switch (game->window->event.type)
    {
      case SDL_QUIT:
      game->running = false;
      break;

      case SDL_KEYDOWN:
      switch (game->window->event.key.keysym.sym)
      {
        case SDLK_q:
        game->running = false;
        break;

        case SDLK_f:
        int status = WINDOW_toggle_fullscreen(game->window);
        if (status != 0)
        {
          LOGGPERR("WINDOW_toggle_fullscreen");
          game->interrupt = true;
        }
        break;

        default:
        game->current_key = game->window->event.key.keysym.sym;
        break;
      }
      break;

      case SDL_WINDOWEVENT:
      switch (game->window->event.window.event)
      {
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        game->window->dimensions.x     = game->window->event.window.data1;
        game->window->dimensions.y     = game->window->event.window.data2;

        GRID_align_center(game->entities.grid, &game->window->dimensions);
        NAKE_counter_offset(game->entities.nake, &game->entities.grid->offset);
        APPLE_counter_offset(&game->entities.apple, &game->entities.grid->offset);
        HUD_counter_offset(game->entities.hud, &game->entities.grid->offset);
        break;
      }
      break;
    }
  }
}

void game_update(Game* game)
{
  NAKE_update(game->entities.nake, game->entities.grid, game->current_key);
  FEAST feast = NAKE_eat_apple(game->entities.nake, &game->entities.apple);
  if (feast == ATE)
  {
    APPLE_set_rand_position(&game->entities.apple, game->entities.grid);
    int hud_status = HUD_update_score_board_score(game->entities.hud, game->window->renderer, game->entities.grid, game->entities.nake->tail_len);
    if (hud_status != 0) game->interrupt = true;
    else if ((int) game->entities.nake->tail_len > game->entities.hud->score_board.high_score)
    {
      hud_status = HUD_update_score_board_hscore(game->entities.hud, game->window->renderer, game->entities.grid, game->entities.nake->tail_len);
      if (hud_status != 0) game->interrupt = true;
    }
  }
  else if (feast == ERROR) game->interrupt = true;
}

int game_save(STTiconf* conf)
{
  char data_str[48] = "";
  int status = sprintf(data_str, "%08X %08X %08X %08X %08X\n", conf->grid_cell_size, conf->grid_cell_count_x, conf->grid_cell_count_y, conf->update_interval, conf->p_high_score);
  if (status < 0)
  {
    LOGGERR("sprintf", errno, strerror(errno));
    return 1;
  }

  size_t data_str_len = strlen(data_str);
  status = FM_write(GAME_SAVE_FILE_PATH, data_str, data_str_len, sizeof(char));
  if (status != 0)
  {
    LOGGPERR("FM_write");
    return 1;
  }

  return 0;
}
