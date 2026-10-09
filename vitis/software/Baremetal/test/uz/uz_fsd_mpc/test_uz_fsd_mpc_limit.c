#ifdef TEST
#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_fsd_mpc.h"
#include "uz_global_configuration.h"

TEST_SOURCE_FILE("src/uz/uz_fsd_mpc/uz_fsd_mpc_math.c")
TEST_SOURCE_FILE("src/uz/uz_fsd_mpc/uz_fsd_mpc_solver.c")

void setUp(void) {}
void tearDown(void) {}

void test_static_instance_pool_has_a_hard_limit(void) {
	struct uz_fsd_mpc_config config = {
		.resistance_ohm = 0.51f, .inductance_d_h = 0.002f,
		.inductance_q_h = 0.002f, .flux_pm_wb = 0.042f,
		.period_s = 0.0001f, .lambda = 10.0f,
		.coordinates = UZ_FSD_MPC_SI,
		.selector = UZ_FSD_MPC_DEADBEAT,
		.modulation = UZ_FSD_MPC_SVM,
		.solver = UZ_FSD_MPC_SIMPLEX_FACE
	};
	struct uz_fsd_mpc_input input = {
		.ia = 0.0f, .ib = 0.0f, .ic = 0.0f,
		.theta_e = 0.0f, .omega_e = 335.1032f,
		.v_dc = 48.0f, .id_ref = 0.0f, .iq_ref = 11.313708f
	};
	struct uz_fsd_mpc_output preload;
	for (uint32_t index = 0U; index < UZ_FSD_MPC_MAX_INSTANCES; ++index) {
		TEST_ASSERT_NOT_NULL(uz_fsd_mpc_init(config, &input, &preload));
		TEST_ASSERT_EQUAL_INT(UZ_FSD_MPC_OK, preload.status);
	}
	TEST_ASSERT_FAIL_ASSERT(uz_fsd_mpc_init(config, &input, &preload));
}
#endif
