#pragma once

#include "world.h"

void* world_handle_events(void* vp_world);
void* world_update(void* vp_world);
void  world_render(World* world);
