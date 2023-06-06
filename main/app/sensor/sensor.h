#pragma once

#include "stdbool.h"

void load_cell_2_init();
void load_cell_2_enable();
void load_cell_2_disable();
bool load_cell_2_is_enabled();
void load_cell_2_set_tara();
void load_cell_2_clear_tara();
float load_cell_2_get_real();
float load_cell_2_get_raw();
float load_cell_2_get_rawps();
float load_cell_2_get_realps();