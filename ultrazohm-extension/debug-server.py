"""Run Vitis hw_server in a VS Code task, retaining the configured environment."""
import subprocess
import sys

if __name__ == '__main__':
    sys.exit(subprocess.call([sys.argv[1], '-s', 'tcp:127.0.0.1:3121']))
