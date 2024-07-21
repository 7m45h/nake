#pragma once

#include "../nconf.h"
#include "../world/world.h"

int SLM_save_state(World* world);
int SLM_load_state(World* world);
int SLM_save_nconf(NConf* nconf);
int SLM_load_nconf(NConf* nconf);
