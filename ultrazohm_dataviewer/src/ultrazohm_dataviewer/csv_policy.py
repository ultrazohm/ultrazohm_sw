"""Spellings of missing numeric CSV values, shared by both loader backends."""

from itertools import product

# Arrow's established spellings plus case-insensitive na/nan/null.
NULL_VALUES = sorted(
    {
        "",
        "#N/A",
        "#N/A N/A",
        "#NA",
        "-1.#IND",
        "-1.#QNAN",
        "-NaN",
        "-nan",
        "1.#IND",
        "1.#QNAN",
        "N/A",
        "n/a",
    }
    | {
        "".join(letters)
        for token in ("na", "nan", "null")
        for letters in product(*[(c.lower(), c.upper()) for c in token])
    }
)
