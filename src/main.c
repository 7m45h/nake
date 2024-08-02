#include <argp.h>
#include <stdlib.h>
#include <time.h>

#include "game_manager/gm.h"
#include "game_manager/states.h"
#include "logger.h"

#define WINDOW_TITLE "nake"

#define DEFAULT_GRID_CELL_SIZE     8
#define DEFAULT_GRID_CELL_COUNT_X 64
#define DEFAULT_GRID_CELL_COUNT_Y 32
#define DEFAULT_UPDATE_INTERVAL   10

const char* argp_program_version    = "3.0.1";
static char doc[]                   = "simple snake game made with SDL2 and written in C";
static struct argp_option options[] = {
  { "cell_size",       's',       "CELL_SIZE",  OPTION_ARG_OPTIONAL,             "grid cell size", 1 },
  { "cell_count_x",    'x',    "CELL_COUNT_X",  OPTION_ARG_OPTIONAL, "grid cell count x / column", 1 },
  { "cell_count_y",    'y',    "CELL_COUNT_Y",  OPTION_ARG_OPTIONAL,    "grid cell count y / row", 1 },
  { "update_interval", 'i', "UPDATE_INTERVAL",  OPTION_ARG_OPTIONAL,       "how fast the nake is", 2 },
  { 0 }
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  STTiconf* conf = state->input;

  switch (key)
  {
    case 's':
    conf->grid_cell_size    = arg ? atoi(arg) : DEFAULT_GRID_CELL_SIZE;
    break;

    case 'x':
    conf->grid_cell_count_x = arg ? atoi(arg) : DEFAULT_GRID_CELL_COUNT_X;
    break;

    case 'y':
    conf->grid_cell_count_y = arg ? atoi(arg) : DEFAULT_GRID_CELL_COUNT_Y;
    break;

    case 'i':
    conf->update_interval   = arg ? atoi(arg) : DEFAULT_UPDATE_INTERVAL;
    break;

    default:
    return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

static struct argp parser = { options, parse_opt, NULL, doc, NULL, NULL, NULL };

int main(int argc, char** argv)
{
  Game* game = NULL;

  {
    STTiconf conf = {
      DEFAULT_GRID_CELL_SIZE,
      DEFAULT_GRID_CELL_COUNT_X,
      DEFAULT_GRID_CELL_COUNT_Y,
      DEFAULT_UPDATE_INTERVAL,
      0
    };

    int status = GAME_load(&conf);
    if (status != 0)
    {
      LOGGPERR("GAME_load");
    }

    argp_parse(&parser, argc, argv, 0, NULL, &conf);

    game = GAME_create(WINDOW_TITLE, &conf);
  }

  if (game == NULL)
  {
    LOGGERR("GAME_create", 0, "");
    return EXIT_FAILURE;
  }

  GAME_run(game);
  GAME_destroy(&game);

  return EXIT_SUCCESS;
}
