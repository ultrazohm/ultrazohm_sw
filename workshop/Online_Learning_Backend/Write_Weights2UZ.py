from importlib.metadata import files
import numbers
import re

from ultrazohm_cli import Acquisition, Client
import numpy as np
from pathlib import Path
import time
path_here = Path(__file__).parent

class ParamRetriever:
    def __init__(self, folder_path):
        self.folder_path = Path(folder_path)
        files_with_0 = []
        numbers = []
        for f in self.folder_path.iterdir():
            if "0" in f.name:
                files_with_0.append(f.name)

            match = re.search(r'\d+', f.name)
            if match:
                numbers.append(int(match.group()))

        has_zero = bool(files_with_0)
        highest_nb = max(numbers, default=None)
        self.nb_layers = highest_nb + has_zero

        if has_zero:
            self.one_base_offset = 0
        else:
            self.one_base_offset = 1

    def retrieve_layer(self,layer_idx):
        flat_weights = np.loadtxt(self.folder_path / f"layer{layer_idx + self.one_base_offset}_weights.csv", delimiter=",")
        bias = np.loadtxt(self.folder_path / f"layer{layer_idx + self.one_base_offset}_bias.csv", delimiter=",")

        return np.concatenate([np.atleast_1d(bias), np.atleast_1d(flat_weights)], dtype=np.float64)
        #return np.concatenate([np.atleast_1d(flat_weights), np.atleast_1d(bias)], dtype=np.float64)

with Acquisition(channel_mapping="my-mapping.json"):
    uz = Client()
    uz.connect("192.168.1.233", 1000)

    uz.set_observable("JSO_DQN_PT1_ACTUAL", 4)

    uz.set_observable("JSO_LAYER_IDX", 5)
    uz.set_observable("JSO_PARAM_IDX", 6)
    uz.set_observable("JSO_PARAM_VALUE", 7)
    uz.set_observable("JSO_ALLOW_UPDATE", 8)

    uz.set_observable("JSO_DQN_PT1_JAVASCOPE_SETPOINT", 9)

    param_retriever = ParamRetriever(path_here / "Overwrite_Weights")

    uz.enable_system()
    uz.enable_control()

    cursor = None

    try:
        while True:

            for _layer_idx in range(3):
                layer_params = param_retriever.retrieve_layer(_layer_idx)

                for _param_idx in range(len(layer_params)):
                    uz.set_variable("layer_idx", _layer_idx)
                    uz.set_variable("param_idx", _param_idx)
                    uz.set_variable("param_value", layer_params[_param_idx])

                    uz.set_variable("allow_update", 1)
                    time.sleep(50e-6)
                    uz.set_variable("allow_update", 0)


            print(np.squeeze(uz.tail(n=1, channels=["JSO_DQN_PT1_ACTUAL"]).to_numpy())[2])

            print()

            request_setpoint = np.random.uniform(low=-1, high=1)
            uz.set_variable("dqn_pt1_javascope_setpoint", request_setpoint)
            print(request_setpoint)

            #page = uz.read_since(
            #    cursor,
            #    channels=["JSO_DQN_PT1_ACTUAL"],
            #    limit=10_000,
            #)
            #cursor = page.cursor
            #print(page.data)


    finally:
        uz.stop()
