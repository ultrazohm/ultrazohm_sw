# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'UltraZohm'
copyright = '2024, UltraZohm Community'
author = 'UltraZohm Community'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    "sphinxcontrib.mermaid",
    "sphinxcontrib.yt",
    "sphinx_issues",
    "sphinx_copybutton",
    "sphinxcontrib.tikz",
    "sphinx.ext.mathjax",
    "breathe",
    "sphinx_plotly_directive",
    "matplotlib.sphinxext.plot_directive",
    "sphinx_design",
    "sphinx_sitemap"
]
templates_path = ['_templates']
exclude_patterns = []
html_favicon = "favicon.svg"

tikz_proc_suite = "GhostScript"
breathe_projects = {"doxygen_baremetal_r5": "../doxygen_output/xml"}
breathe_default_project = "doxygen_baremetal_r5"
breathe_domain_by_extension = {
    "h": "c",
}

issues_uri = "https://bitbucket.org/ultrazohm/ultrazohm_sw/issues/{issue}"
issues_pr_uri = "https://bitbucket.org/ultrazohm/ultrazohm_sw/pull-requests/{pr}"
issues_commit_uri = "https://bitbucket.org/ultrazohm/ultrazohm_sw/commits/{commit}"

latex_engine = "lualatex"

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'pydata_sphinx_theme'
html_theme_options = {
    "navigation_with_keys":"True"
}

# html_static_path = ['_static']

html_context = {
    "display_bitbucket": True,  # Integrate Bitbucket
    "bitbucket_user": "ultrazohm",  # Username
    "bitbucket_repo": "ultrazohm_sw",  # Repo name
    "bitbucket_version": "main",  # Version
    "conf_py_path": "/docs/source/",  # Path in the checkout to the docs root
}


# enables numbered figures
numfig = True
# For numbering equations directly with sphinx
# https://stackoverflow.com/questions/50631942/how-does-equation-numbering-work-for-sphinx
math_numfig = True
numfig_secnum_depth = 2
math_eqref_format = "Eq.{number}"

# For Mathjax rendering instead of picture, according to
mathjax_config = {
    "TeX": {"equationNumbers": {"autoNumber": "AMS", "useLabelIds": True}},
}
mathjax_path = (
    "https://cdn.jsdelivr.net/npm/mathjax@2/MathJax.js?config=TeX-AMS-MML_HTMLorMML"
)

# https://github.com/michaeljones/breathe/issues/696
nitpick_ignore = [
    ("c:identifier", "int32_t"),
    ("c:identifier", "uint32_t"),
    ("c:identifier", "int16_t"),
    ("c:identifier", "uint16_t"),
    ("c:identifier", "size_t"),
    ("c:identifier", "uintptr_t"),
    ("c:identifier", "bool"),
]

tikz_latex_preamble = "\\newcommand\Foo[1]{Z}" # https://github.com/sphinx-contrib/tikz/issues/19

# For sphinx-sitemap: https://sphinx-sitemap.readthedocs.io/en/latest/getting-started.html
html_baseurl = 'https://docs.ultrazohm.com/'
html_extra_path = ['robots.txt']