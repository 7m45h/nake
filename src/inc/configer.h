#pragma once

typedef struct
{
  int      window_w;
  int      window_h;
  int     cell_size;
  int grid_margin_x;
  int grid_margin_y;
} NConf;

NConf NCONF_get_config(int argc, char** argv);
