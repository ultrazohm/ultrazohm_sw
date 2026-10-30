"""Missing numeric CSV values shared by native and generated browser loaders."""
from itertools import product

# Preserve Arrow's established spellings and the browser's case-insensitive ones.
NULL_VALUES = sorted({
    "", "#N/A", "#N/A N/A", "#NA", "-1.#IND", "-1.#QNAN", "-NaN", "-nan",
    "1.#IND", "1.#QNAN", "N/A", "n/a",
} | {"".join(letters) for token in ("na", "nan", "null")
     for letters in product(*[(c.lower(), c.upper()) for c in token])})
