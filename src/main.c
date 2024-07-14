#include <argp.h>
#include <stdlib.h>
#include <time.h>

#include "logger.h"
#include "nconf.h"
#include "world/world.h"

#define DEFAULT_WINDOW_TITLE  "nake"
#define DEFAULT_WINDOW_FPS    10

#define DEFAULT_GRID_CELLSIZE 8
#define DEFAULT_GRID_CCC      64
#define DEFAULT_GRID_RCC      32

const char* argp_program_version = "1.5.5";

static char doc[]      = "simple snake game made with SDL2";

static struct argp_option options[] = {
  { "cell_size", 's', "CELL_SIZE",  OPTION_ARG_OPTIONAL,      "grid cell size", 1 },
  {       "col", 'c',       "COL",  OPTION_ARG_OPTIONAL, "grid col cell count", 1 },
  {       "row", 'r',       "ROW",  OPTION_ARG_OPTIONAL, "grid row cell count", 1 },
  {       "fps", 'f',       "FPS",  OPTION_ARG_OPTIONAL, "fps game is updated", 2 },
  { 0 }
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  NConf* conf = (NConf*) state->input;

  switch (key)
  {
    case 's':
    conf->cell_size      = arg ? atoi(arg) : DEFAULT_GRID_CELLSIZE;
    break;

    case 'c':
    conf->g_c_cell_count = arg ? atoi(arg) : DEFAULT_GRID_CCC;
    break;

    case 'r':
    conf->g_r_cell_count = arg ? atoi(arg) : DEFAULT_GRID_RCC;
    break;

    case 'f':
    conf->fps            = arg ? atoi(arg) : DEFAULT_WINDOW_FPS;
    break;

    default:
    return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

static struct argp argp = { options, parse_opt, NULL, doc, NULL, NULL, NULL };

int main(int argc, char** argv)
{
  srand(time(NULL));

  NConf conf = {
    DEFAULT_GRID_CELLSIZE,
    DEFAULT_GRID_CCC,
    DEFAULT_GRID_RCC,
    DEFAULT_WINDOW_FPS
  };

  argp_parse(&argp, argc, argv, 0, NULL, &conf);

  World* world = WORLD_form(DEFAULT_WINDOW_TITLE, conf.cell_size, conf.g_c_cell_count, conf.g_r_cell_count, conf.fps);
  if (world == NULL)
  {
    LOGG("WORLD_init faild");
    return EXIT_FAILURE;
  }

  WORLD_evolve(world);
  WORLD_destroy(world);

  return EXIT_SUCCESS;
}
