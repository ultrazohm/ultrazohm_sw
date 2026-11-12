"""Shared session lifecycle and GUI command handling."""


class SessionPanel:
    def _sync_session(self, state) -> bool:
        """Discard view-owned state before consuming a replacement session.

        Called before rendering or populating caches. A fresh panel needs no reset.
        """
        previous = getattr(self, "_session_token", None)
        changed = previous is not None and previous is not state.session_token
        if changed:
            self.__init__()
        self._session_token = state.session_token
        return changed

    def _emit(self, state, name: str, *args) -> bool:
        """Execute a GUI command; report errors and return explicit success."""
        try:
            state.commands.execute(state, name, list(args))
        except Exception as exc:  # GUI boundary: keep the application running
            state.console.error(str(exc))
            return False
        return True
