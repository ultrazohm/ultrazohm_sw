import pytest

from pyuzlib._generated_artifacts import check_generated_artifacts


EXPECTED = "operating_point,i_d_A,L_dd_H\n0,1.0,0.002404291148878756\n1,2.0,0.0\n"


def check(tmp_path, actual, *, tolerant=True, suffix=".csv"):
    path = tmp_path / f"artifact{suffix}"
    path.write_text(actual, encoding="utf-8")
    before = path.read_bytes()
    result = check_generated_artifacts(
        {path: EXPECTED}, regenerate_args=["generate"],
        numeric_csv_columns=frozenset({"L_dd_H"}) if tolerant else frozenset(),
    )
    assert path.read_bytes() == before
    return result


def test_tolerates_observed_ci_roundoff_and_near_zero_noise(tmp_path):
    actual = EXPECTED.replace("0.002404291148878756", "0.002404291148878763")
    actual = actual.replace("2.0,0.0", "2.0,1e-16")
    assert check(tmp_path, actual) == 0
    assert check(tmp_path, actual, tolerant=False) == 1
    assert check(tmp_path, actual, suffix=".h") == 1


@pytest.mark.parametrize("actual", [
    EXPECTED.replace("0.002404291148878756", "0.0024043"),
    EXPECTED.replace("2.0,0.0", "2.0,1e-10"),
    EXPECTED.replace("0,1.0,", "0,1.000000000000001,"),
    EXPECTED.replace("0,1.0,", "2,1.0,"),
    EXPECTED.replace("L_dd_H", "L_qq_H"),
    EXPECTED.replace("1,2.0,0.0\n", ""),
    EXPECTED + "2,3.0,0.0\n",
    EXPECTED.replace("1,2.0,0.0", "1,2.0"),
    EXPECTED.replace("1,2.0,0.0", "1,2.0,0.0,0.0"),
    EXPECTED.replace("2.0,0.0", "2.0,nan"),
    EXPECTED.replace("2.0,0.0", "2.0,inf"),
    EXPECTED.replace("2.0,0.0", "2.0,invalid"),
])
def test_rejects_real_changes_and_malformed_data(tmp_path, actual):
    assert check(tmp_path, actual) == 1
