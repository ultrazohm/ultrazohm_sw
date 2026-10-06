// Windows GUI-subsystem entry point (no console window behind the scope).
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int uz_scopec_main(int argc, char** argv);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    return uz_scopec_main(__argc, __argv);
}
#endif
