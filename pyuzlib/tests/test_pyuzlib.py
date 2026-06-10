import pyuzlib


def test_pyuzlib_has_version():
    assert pyuzlib.__version__


def test_pyuzlib_exposes_docs_pmsm_helpers():
    assert pyuzlib.docs.pmsm.plot_flux_map
