#pragma once

#include <stdbool.h>

#include "world.h"

bool world_init(World* world);
void world_handle_events(World* world);
void world_update(World* world);
void world_render(World* world);
void world_deinit(World* world);
