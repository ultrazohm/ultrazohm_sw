/*
 * Project Wizard generated file.
 *
 * This file is fully owned by Project Wizard code generation.
 * Manual changes may be overwritten the next time software files are generated.
 */

#pragma once

struct _DS_Data_;

typedef struct {
{{ field_declarations }}
} project_wizard_visualization_data_t;

extern project_wizard_visualization_data_t project_wizard_visualization_data;

void project_wizard_visualization_update(struct _DS_Data_* data);
