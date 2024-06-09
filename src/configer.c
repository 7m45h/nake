#include <argp.h>
#include <stdlib.h>

#include "inc/configer.h"

#define DEFAULT_WINDOW_W 640
#define DEFAULT_WINDOW_H 480

#define DEFAULT_CELL_SIZE     8
#define DEFAULT_GRID_MARGIN_X 4
#define DEFAULT_GRID_MARGIN_Y 8

static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
  NConf* config = state->input;

  switch (key)
  {
     case 'w':
     config->window_w = arg ? atoi(arg) : DEFAULT_WINDOW_W;
     break;

     case 'h':
     config->window_h = arg ? atoi(arg) : DEFAULT_WINDOW_H;
     break;

     case 'c':
     config->cell_size = arg ? atoi(arg) : DEFAULT_CELL_SIZE;
     break;

    case 'x':
    config->grid_margin_x = arg ? atoi(arg) : DEFAULT_GRID_MARGIN_X;
    break;

    case 'y':
    config->grid_margin_y = arg ? atoi(arg) : DEFAULT_GRID_MARGIN_Y;
    break;

    default:
    return ARGP_ERR_UNKNOWN;
  }

   return 0;
}

NConf NCONF_get_config(int argc, char** argv)
{
  const char* argp_program_version = "0.0.0";

  static char doc[]      = "simple nake game in C";

  static struct argp_option options[] = {
    {"window_w",  'w',  "width", OPTION_ARG_OPTIONAL,  "define window width"},
    {"window_h",  'h', "height", OPTION_ARG_OPTIONAL, "define window height"},
    {"cell_size", 'c',     "cs", OPTION_ARG_OPTIONAL,     "define cell size"},
    {"margin_x",  'x',     "mx", OPTION_ARG_OPTIONAL, "define grid margin x"},
    {"margin_y",  'y',     "my", OPTION_ARG_OPTIONAL, "define grid margin y"},
    { 0 },
  };

  static struct argp argp = { options, parse_opt, NULL, doc };

  NConf config = { DEFAULT_WINDOW_W, DEFAULT_WINDOW_H, DEFAULT_CELL_SIZE, DEFAULT_GRID_MARGIN_X, DEFAULT_GRID_MARGIN_Y };

  argp_parse (&argp, argc, argv, 0, 0, &config);

  return config;
}
