#pragma once

#include <stdbool.h>

#include "world.h"

bool  world_init(World* world);
void* world_handle_events(void* vp_world);
void* world_update(void* vp_world);
void  world_render(World* world);
void  world_deinit(World* world);
