#pragma once

#include "core/state.hpp"

namespace uz {

// Runs the GLFW/ImGui main loop until the window closes.  Returns the exit code.
int run_app(ScopeAppState& state, bool connect_on_start);

}  // namespace uz
