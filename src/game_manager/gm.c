#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include "../file_manager/file_manager.h"
#include "../logger.h"
#include "gm.h"
#include "helpers.h"
#include "states.h"

#define SAVE_HEX_STR_LEN   45
#define BASE_OF_HEX        16
#define ONE_SEC_IN_MILI  1000.0f

int GAME_load(STTiconf* conf)
{
  size_t hex_str_len = 0;
  char* hex_str      = FM_read(GAME_SAVE_FILE_PATH, &hex_str_len, sizeof(char), true);
  if (hex_str == NULL)
  {
    LOGGPERR("FM_read");
    return 1;
  }

  if (hex_str_len != SAVE_HEX_STR_LEN)
  {
    LOGG("save file length not match | expected: %02d got: %02ld", SAVE_HEX_STR_LEN, hex_str_len);
    free(hex_str);
    return 1;
  }

  char* next_hex          = NULL;
  conf->grid_cell_size    = (int) strtol(hex_str,  &next_hex, BASE_OF_HEX);
  conf->grid_cell_count_x = (int) strtol(next_hex, &next_hex, BASE_OF_HEX);
  conf->grid_cell_count_y = (int) strtol(next_hex, &next_hex, BASE_OF_HEX);
  conf->update_interval   = (int) strtol(next_hex, &next_hex, BASE_OF_HEX);
  conf->p_high_score      = (int) strtol(next_hex, &next_hex, BASE_OF_HEX);

  free(hex_str);

  return 0;
}

Game* GAME_create(const char* title, STTiconf* conf)
{
  Game* game = calloc(1, sizeof(Game));
  if (game == NULL)
  {
    LOGGERR("malloc", errno, strerror(errno));
    return NULL;
  }

  game->window = WINDOW_create(title);
  if (game->window == NULL)
  {
    LOGGPERR("WINDOW_create");
    GAME_destroy(&game);
    return NULL; 
  }

  int entity_status = game_populate_entities(game, conf);
  if (entity_status != 0)
  {
    LOGGPERR("game_populate_entities");
    GAME_destroy(&game);
    return NULL;
  }

  game->running             = false;
  game->interrupt           = false;
  game->event_poll_interval = ONE_SEC_IN_MILI / game->window->refresh_rate;
  game->update_interval     = ONE_SEC_IN_MILI / conf->update_interval;

  return game;
}

void GAME_run(Game* game)
{
  game->running = true;

  Uint64 frame_start_time = 0;
  Uint64 frame_duration   = 0;
  Uint64 event_ticker     = game->event_poll_interval;
  Uint64 update_ticker    = game->update_interval;
  while (game->running)
  {
    frame_start_time = SDL_GetTicks64();

    if (event_ticker >= game->event_poll_interval)
    {
      event_ticker = 0;
      WINDOW_update_events(game->window, &game->events);
      game_handle_events(game);
    }
    else event_ticker += frame_duration;

    if (update_ticker >= game->update_interval)
    {
      update_ticker = 0;
      game_update(game);
      if (game->interrupt) break;
    }
    else update_ticker += frame_duration;

    WINDOW_update_screen(game->window, &game->entities);

    frame_duration = SDL_GetTicks64() - frame_start_time;
  }

  if (game->interrupt)
  {
    LOGG("game loop interrupted!");
  }
  else
  {
    STTiconf conf = {
      game->entities.grid->cell_size,
      game->entities.grid->cell_count.x,
      game->entities.grid->cell_count.y,
      ONE_SEC_IN_MILI / game->update_interval,
      game->entities.hud->score_board.high_score
    };

    int status = game_save(&conf);
    if (status != 0)
    {
      LOGGPERR("game_save");
    }
  }
}

void GAME_destroy(Game** game)
{
  if (game != NULL && *game != NULL)
  {
    game_depopulate_entities(*game);
    WINDOW_destroy(&(*game)->window);

    free(*game);
    *game = NULL;
  }
}
