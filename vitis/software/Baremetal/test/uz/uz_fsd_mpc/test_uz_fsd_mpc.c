#ifdef TEST
#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_fsd_mpc.h"
#include "uz_fsd_mpc_fixture.h"
#include <math.h>
#include <stddef.h>

TEST_SOURCE_FILE("src/uz/uz_fsd_mpc/uz_fsd_mpc_math.c")
TEST_SOURCE_FILE("src/uz/uz_fsd_mpc/uz_fsd_mpc_solver.c")

void setUp(void) {}
void tearDown(void) {}

static void compare_command(const struct uz_fsd_mpc_command *actual,
	int32_t path, const float expected[4]) {
	TEST_ASSERT_EQUAL_INT32(path, actual->path);
	for (int32_t j = 0; j < 4; ++j) {
		TEST_ASSERT_FLOAT_WITHIN(5.0e-7f, expected[j], actual->x_half[j]);
	}
}

void test_frozen_simplex_vectors_and_state_chronology(void) {
	for (int32_t record = 0; record < 9; ++record) {
		const struct fsd_fixture *fixture = &fsd_fixture[record];
		const struct uz_fsd_mpc_input *first = &fixture->step[0].input;
		struct uz_fsd_mpc_output preload;
		uz_fsd_mpc_t *self = uz_fsd_mpc_init(fixture->config, first, &preload);
		TEST_ASSERT_NOT_NULL(self);
		TEST_ASSERT_EQUAL_INT(UZ_FSD_MPC_OK, preload.status);
		compare_command(&preload.calculated,
			fixture->preload_path, fixture->preload_x);
		for (int32_t index = 0; index < 6; ++index) {
			const struct fsd_expected_step *expected = &fixture->step[index];
			struct uz_fsd_mpc_output output;
			struct uz_fsd_mpc_diagnostics diagnostics;
			struct uz_fsd_mpc_schedule schedule;
			TEST_ASSERT_EQUAL_INT(UZ_FSD_MPC_OK, uz_fsd_mpc_step(self,
				&expected->input, &output, &diagnostics));
			TEST_ASSERT_EQUAL_UINT32((uint32_t)(index + 1), output.update_count);
			compare_command(&output.applied, expected->applied_path,
				expected->applied_x);
			compare_command(&output.calculated, expected->calculated_path,
				expected->calculated_x);
			for (int32_t axis = 0; axis < 2; ++axis) {
				TEST_ASSERT_FLOAT_WITHIN(2.0e-6f, expected->measured[axis],
					output.measured_dq_a[axis]);
				TEST_ASSERT_FLOAT_WITHIN(2.0e-6f, expected->predicted[axis],
					output.predicted_start_dq_a[axis]);
			}
			TEST_ASSERT_FLOAT_WITHIN(2.0e-7f, expected->theta_prediction,
				output.theta_prediction_rad);
			TEST_ASSERT_FLOAT_WITHIN(2.0e-7f, expected->theta_optimization,
				output.theta_optimization_rad);
			const float duties[3] = {output.duty_a, output.duty_b, output.duty_c};
			for (int32_t phase = 0; phase < 3; ++phase) {
				TEST_ASSERT_TRUE(isfinite(duties[phase]));
				TEST_ASSERT_TRUE(duties[phase] >= 0.0f && duties[phase] <= 1.0f);
				TEST_ASSERT_FLOAT_WITHIN(3.0e-7f, expected->duty[phase], duties[phase]);
			}
			TEST_ASSERT_EQUAL_INT(UZ_FSD_MPC_OK, uz_fsd_mpc_schedule(
				&output.calculated, fixture->config.period_s, &schedule));
			TEST_ASSERT_EQUAL_INT32(expected->schedule_count, schedule.count);
			for (int32_t event = 0; event < schedule.count; ++event) {
				TEST_ASSERT_EQUAL_INT32(expected->states[event], schedule.states[event]);
				TEST_ASSERT_FLOAT_WITHIN(3.0e-11f, expected->dwell_s[event],
					schedule.dwell_s[event]);
			}
			if (record == 0 && index == 0) {
				int32_t candidate = output.calculated.path;
				TEST_ASSERT_EQUAL_INT32(6, diagnostics.candidate_count);
				for (int32_t i = 0; i < 4; ++i) {
					TEST_ASSERT_FLOAT_WITHIN(5.0e-3f, fsd_qp_f[i],
						diagnostics.f[candidate][i]);
					for (int32_t j = 0; j < 4; ++j) {
						TEST_ASSERT_FLOAT_WITHIN(5.0e-3f, fsd_qp_h[i][j],
							diagnostics.h[candidate][i][j]);
					}
				}
				TEST_ASSERT_FLOAT_WITHIN(6.0e-3f, fsd_qp_cost,
					diagnostics.cost_a2[candidate]);
			}
		}
		struct uz_fsd_mpc_output reset;
		TEST_ASSERT_EQUAL_INT(UZ_FSD_MPC_OK, uz_fsd_mpc_reset(self, first, &reset));
		TEST_ASSERT_EQUAL_UINT32(0U, reset.update_count);
		compare_command(&reset.calculated,
			fixture->preload_path, fixture->preload_x);
	}
}

void test_invalid_config_asserts_and_generated_backend_is_explicit(void) {
	struct uz_fsd_mpc_output preload;
	struct uz_fsd_mpc_config config = fsd_fixture[0].config;
	const struct uz_fsd_mpc_input *first = &fsd_fixture[0].step[0].input;
	config.period_s = 0.0f;
	TEST_ASSERT_FAIL_ASSERT(uz_fsd_mpc_init(config, first, &preload));
	config = fsd_fixture[0].config;
	config.solver = UZ_FSD_MPC_GENERATED_ACTIVE_SET;
	TEST_ASSERT_FAIL_ASSERT(uz_fsd_mpc_init(config, first, &preload));
	config = fsd_fixture[6].config;
	config.selector = UZ_FSD_MPC_DEADBEAT;
	TEST_ASSERT_FAIL_ASSERT(uz_fsd_mpc_init(config, first, &preload));
}

void test_fault_latch_invalid_duties_and_reset(void) {
	struct uz_fsd_mpc_output preload, output;
	const struct fsd_fixture *fixture = &fsd_fixture[0];
	struct uz_fsd_mpc_input invalid = fixture->step[0].input;
	uz_fsd_mpc_t *self = uz_fsd_mpc_init(fixture->config,
		&fixture->step[0].input, &preload);
	invalid.v_dc = NAN;
	TEST_ASSERT_EQUAL_INT(UZ_FSD_MPC_INPUT_INVALID,
		uz_fsd_mpc_step(self, &invalid, &output, NULL));
	TEST_ASSERT_TRUE(isnan(output.duty_a));
	TEST_ASSERT_TRUE(isnan(output.duty_b));
	TEST_ASSERT_TRUE(isnan(output.duty_c));
	TEST_ASSERT_EQUAL_INT(UZ_FSD_MPC_FAULTED,
		uz_fsd_mpc_step(self, &fixture->step[0].input, &output, NULL));
	TEST_ASSERT_EQUAL_INT(UZ_FSD_MPC_OK,
		uz_fsd_mpc_reset(self, &fixture->step[0].input, &preload));
	TEST_ASSERT_EQUAL_INT(UZ_FSD_MPC_OK,
		uz_fsd_mpc_step(self, &fixture->step[0].input, &output, NULL));
	invalid = fixture->step[0].input;
	invalid.v_dc = 3.0e38f;
	TEST_ASSERT_NOT_EQUAL(UZ_FSD_MPC_OK,
		uz_fsd_mpc_step(self, &invalid, &output, NULL));
	TEST_ASSERT_TRUE(isnan(output.duty_a));
}
#endif
