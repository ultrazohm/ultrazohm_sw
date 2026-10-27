"""Allow `python -m ultrazohm` as well as the installed console command."""
from .cli import main

raise SystemExit(main())
