from pathlib import Path

import numpy as np
import torch.nn as nn


def export_to_uz_nn(trained_actor, export_dir="workshop/exported_paras"):
    """Export a trained SB3 DQN Q-network to uz_nn-compatible CSV files.

    DQN does not have an actor network. Pass either the trained DQN model,
    model.q_net, or the q_net Sequential module. The exported weights are
    transposed from PyTorch's out_features x in_features layout to uz_nn's
    number_of_inputs x number_of_neurons layout.
    """

    export_path = Path(export_dir)
    export_path.mkdir(parents=True, exist_ok=True)

    linear_layers = _get_linear_layers(trained_actor)
    if len(linear_layers) < 2:
        raise ValueError("Expected at least one hidden layer and one output layer")

    for layer_number, layer in enumerate(linear_layers, start=1):
        weights = layer.weight.detach().cpu().numpy().astype(np.float32)
        bias = _get_bias(layer)

        uz_weights = weights.T.reshape(-1)

        _write_csv_row(export_path / f"layer{layer_number}_weights.csv", uz_weights)
        _write_csv_row(export_path / f"layer{layer_number}_bias.csv", bias)


def _get_linear_layers(trained_actor):
    network = _get_network_module(trained_actor)
    linear_layers = [
        module for module in network.modules() if isinstance(module, nn.Linear)
    ]

    if not linear_layers:
        raise ValueError("No torch.nn.Linear layers found for export")

    return linear_layers


def _get_network_module(trained_actor):
    if hasattr(trained_actor, "q_net"):
        return _get_network_module(trained_actor.q_net)

    if isinstance(trained_actor, nn.Module):
        return trained_actor

    raise TypeError("Expected a DQN model, QNetwork, or torch.nn.Module")


def _get_bias(layer):
    if layer.bias is None:
        return np.zeros(layer.out_features, dtype=np.float32)

    return layer.bias.detach().cpu().numpy().astype(np.float32)


def _write_csv_row(path, values):
    values = np.asarray(values, dtype=np.float32).reshape(1, -1)
    np.savetxt(path, values, delimiter=",", fmt="%.9g")
