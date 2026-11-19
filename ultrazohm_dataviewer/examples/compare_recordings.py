"""Compare matching channels from two recordings in an existing viewer.

Run from a terminal or the Python panel; UZ_DATAVIEWER_ENDPOINT selects the viewer.
"""
import argparse
from ultrazohm_dataviewer import Client


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('first')
    parser.add_argument('second')
    parser.add_argument('--endpoint')
    parser.add_argument('--session', default='comparison.json')
    args = parser.parse_args()
    with Client(args.endpoint) as viewer:
        viewer.clear_session()
        runs = [viewer.load(args.first), viewer.load(args.second)]
        viewer.set_grid(3, 2)
        viewer.link_x(True)
        for plot, signal in enumerate(['y', 'reference', 'action_value', 'reward', 'action_index'], 1):
            for run in runs:
                viewer.add_signal(plot, run, signal)
        for run in runs:
            for signal in ['q_action_minus_1', 'q_action_0', 'q_action_plus_1']:
                viewer.add_signal(6, run, signal)
        viewer.save_session(args.session)


if __name__ == '__main__':
    main()
