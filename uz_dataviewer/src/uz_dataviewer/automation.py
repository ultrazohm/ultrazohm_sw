"""Replay GUI commands on the UI thread, yielding while exports are pending."""
from dataclasses import dataclass
from concurrent.futures import Future


@dataclass
class Replay:
    commands: object
    path: str
    count: int = 0
    waiting: Future | None = None


def start(state, commands, path):
    if state.services.replay is not None:
        raise ValueError('An automation script is already running')
    if state.services.exports:
        raise ValueError('Wait for the current export before starting automation')
    state.services.replay = Replay(iter(commands), path)


def poll(state):
    replay = state.services.replay
    if replay is None:
        return
    try:
        if replay.waiting is not None:
            if not replay.waiting.done():
                return
            # Export failures abort replay; dependent commands must not run.
            replay.waiting.result()
            replay.waiting = None
        # One command per frame keeps controls responsive between operations.
        command = next(replay.commands, None)
        if command is None:
            state.services.replay = None
            state.console.ok(f'Ran {replay.count} command(s) from {replay.path}')
            return
        name, args = command
        state.commands.execute(state, name, args)
        replay.count += 1
        if state.services.exports:
            replay.waiting = state.services.exports[-1][0]
    except Exception as exc:
        state.services.replay = None
        state.console.error(f'Automation stopped: {exc}')
