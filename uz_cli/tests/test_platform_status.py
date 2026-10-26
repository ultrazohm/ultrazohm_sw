"""Compile the real Baremetal status helper without Xilinx hardware dependencies."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


@unittest.skipUnless(shutil.which("cc"), "host C compiler required")
class PlatformStatusTest(unittest.TestCase):
    def test_state_transitions_preserve_all_lower_bits(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "status.c"
            binary = Path(directory) / "status"
            source.write_text('''
#include <assert.h>
#include "javascope_status.h"
int main(void) {
    const platform_state_t states[] = {idle_state, running_state, control_state, error_state};
    const uint32_t expected[] = {0x00000000U, 0x40000000U, 0x80000000U, 0xC0000000U};
    const uint32_t feedback[] = {0U, 1U, 15U, 0x3FFFFFFFU};
    for (unsigned before = 0; before < 4; ++before) {
        for (unsigned after = 0; after < 4; ++after) {
            for (unsigned i = 0; i < 4; ++i) {
                uint32_t status = expected[before] | feedback[i];
                uint32_t updated = javascope_status_with_platform_state(status, states[after]);
                assert(updated == (expected[after] | feedback[i]));
            }
        }
    }
    const uint32_t flags[] = {
        JAVASCOPE_STATUS_LED_READY, JAVASCOPE_STATUS_LED_RUNNING,
        JAVASCOPE_STATUS_LED_ERROR, JAVASCOPE_STATUS_LED_USER,
        JAVASCOPE_STATUS_BUTTON_1, JAVASCOPE_STATUS_BUTTON_2,
        JAVASCOPE_STATUS_BUTTON_3, JAVASCOPE_STATUS_BUTTON_4,
        JAVASCOPE_STATUS_BUTTON_5, JAVASCOPE_STATUS_BUTTON_6,
        JAVASCOPE_STATUS_BUTTON_7, JAVASCOPE_STATUS_BUTTON_8,
        JAVASCOPE_STATUS_LOGGING_TRIGGER
    };
    const uint32_t words[] = {0U, 0xFFFFFFFFU, 0xAAAAAAAAU, 0x55555555U};
    for (unsigned bit = 0; bit < sizeof(flags) / sizeof(flags[0]); ++bit) {
        assert(flags[bit] == (UINT32_C(1) << bit));
        for (unsigned i = 0; i < sizeof(words) / sizeof(words[0]); ++i) {
            uint32_t status = words[i];
            javascope_status_set_flag(&status, flags[bit], true);
            assert(status == (words[i] | flags[bit]));
            javascope_status_set_flag(&status, flags[bit], true);
            assert(status == (words[i] | flags[bit]));
            javascope_status_set_flag(&status, flags[bit], false);
            assert(status == (words[i] & ~flags[bit]));
            javascope_status_set_flag(&status, flags[bit], false);
            assert(status == (words[i] & ~flags[bit]));
        }
    }
    return 0;
}
''')
            subprocess.run(["cc", "-std=c99", "-Wall", "-Wextra", "-Werror",
                            "-I", str(ROOT / "vitis/software/Baremetal/src/include"),
                            str(source), "-o", str(binary)], check=True)
            subprocess.run([str(binary)], check=True)
