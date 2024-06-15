#include <argp.h>
#include <stdlib.h>
#include <time.h>

#include "libs/logger.h"
#include "libs/world/world.h"
#include "nconf.h"

#define DEFAULT_WINDOW_TITLE  "nake"
#define DEFAULT_WINDOW_WIDTH  640
#define DEFAULT_WINDOW_HEIGHT 480
#define DEFAULT_WINDOW_FPS    10
#define DEFAULT_WINDOW_EFPS   24

#define DEFAULT_GRID_CELLSIZE 8
#define DEFAULT_GRID_MX       4
#define DEFAULT_GRID_MY       8

const char* argp_program_version = "0.0.0";

static char doc[]      = "simple snake game made with SDL2";
static char args_doc[] = "all the arguments are optional";

static struct argp_option options[] = {
  { "width",    'w', "width",     OPTION_ARG_OPTIONAL,                                         "window width" },
  { "height",   'h', "height",    OPTION_ARG_OPTIONAL,                                        "window height" },
  { "speed",    's', "speed",     OPTION_ARG_OPTIONAL, "fps snake update effectivly changing the snake speed" },
  { "cell",     'c', "cell_size", OPTION_ARG_OPTIONAL,                                       "grid cell size" },
  { "margin_l", 'l', "ml",        OPTION_ARG_OPTIONAL,                                    "grid margin right" },
  { "margin_b", 'b', "mb",        OPTION_ARG_OPTIONAL,                                   "grid margin bottom" },
  { 0 }
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  NConf* conf = (NConf*) state->input;

  switch (key)
  {
    case 'w':
    conf->width     = arg ? atoi(arg) : DEFAULT_WINDOW_WIDTH;
    break;

    case 'h':
    conf->height    = arg ? atoi(arg) : DEFAULT_WINDOW_HEIGHT;
    break;

    case 's':
    conf->speed     = arg ? atoi(arg) : DEFAULT_WINDOW_FPS;
    break;

    case 'c':
    conf->cell_size = arg ? atoi(arg) : DEFAULT_GRID_CELLSIZE;
    break;

    case 'l':
    conf->ml        = arg ? atoi(arg) : DEFAULT_GRID_MX;
    break;

    case 'b':
    conf->mb        = arg ? atoi(arg) : DEFAULT_GRID_MY;
    break;

    default:
    return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char** argv)
{
  srand(time(NULL));

  NConf conf = {
    DEFAULT_WINDOW_WIDTH,
    DEFAULT_WINDOW_HEIGHT,
    DEFAULT_WINDOW_FPS,
    DEFAULT_GRID_CELLSIZE,
    DEFAULT_GRID_MX,
    DEFAULT_GRID_MY
  };

  argp_parse(&argp, argc, argv, 0, 0, &conf);

  World* world = WORLD_form(DEFAULT_WINDOW_TITLE, conf.width, conf.height, conf.speed, DEFAULT_WINDOW_EFPS, conf.cell_size, conf.ml, conf.mb);
  if (world == NULL)
  {
    LOGG("WORLD_init faild");
    return EXIT_FAILURE;
  }

  WORLD_evolve(world);
  WORLD_destroy(world);

  return EXIT_SUCCESS;
}
