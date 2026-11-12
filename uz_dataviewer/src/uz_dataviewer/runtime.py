"""Runtime capabilities without importing the GUI or browser bridge."""
import sys

IS_WEB = sys.platform == "emscripten"
