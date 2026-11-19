"""Allow `python -m ultrazohm_cli` as well as the installed console command."""

from .cli import main

raise SystemExit(main())
