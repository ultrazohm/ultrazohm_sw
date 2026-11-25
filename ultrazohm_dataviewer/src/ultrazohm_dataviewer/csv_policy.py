"""Spellings of missing numeric CSV values."""

from itertools import product

# Common spellings (as established by Arrow) plus case-insensitive na/nan/null.
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
