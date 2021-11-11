#pragma once

typedef struct uz_simscapeExample uz_simscapeExample;
typedef struct uz_simscapeExample *uz_simscapeExample_handle;

uz_simscapeExample_handle uz_simscapeExample_init(uz_simscapeExample_handle self);
void uz_simscapeExample_step_model_once(uz_simscapeExample_handle self);

