"""Host training contract checks; no UltraZohm connection required."""
import random

import numpy as np
import polars as pl
import pytest
import torch

from train_pt1_dqn import CHANNELS, make_network, parameters, train, transitions


def batch():
    k = np.arange(3000)
    # Cross both the float32 consecutive-integer limit and a 16-bit limb wrap.
    counter = np.uint64(2**48 + 65500) + k.astype(np.uint64)
    fields = {name: np.zeros(3000, dtype=np.float32) for name in CHANNELS}
    fields.update(actor=np.ones(3000), time=k, episode=k // 500 + 1,
                  episode_k=k % 500, done=(k % 500 == 499),
                  reference=np.ones(3000), reward=-np.ones(3000),
                  epsilon=np.full(3000, np.float32(0.05)))
    fields.update({f"isr_{i}": (counter >> (16*i)) & 65535 for i in range(4)})
    return pl.DataFrame({f"JSO_pt1_{name}": values for name, values in fields.items()})


def test_complete_batch_with_exact_counter_and_terminal_next_observation():
    data = batch().with_columns(pl.when(pl.col("JSO_pt1_done") == 1)
                               .then(0.25).otherwise(0.0).alias("JSO_pt1_next_y"))
    replay = transitions(data, 0.05)
    assert len(replay) == 3000
    np.testing.assert_array_equal(replay[499][3], [0.25, 1.0])
    np.testing.assert_array_equal(replay[500][0], [0.0, 1.0])


@pytest.mark.parametrize("kind", ["missing", "duplicate", "gap", "action", "epsilon", "alignment"])
def test_reject_invalid_data(kind):
    data = batch()
    if kind == "missing":
        data = data.slice(1)
    elif kind == "duplicate":
        data = pl.concat([data.head(2999), data.tail(1), data.tail(1)])
    else:
        column, value = {"gap": ("isr_0", 0), "action": ("action_index", 3),
                         "epsilon": ("epsilon", 0), "alignment": ("next_y", 1)}[kind]
        data = data.with_columns(pl.lit(value).alias(f"JSO_pt1_{column}"))
    with pytest.raises(ValueError):
        transitions(data, 0.05)


def test_export_order_reproduces_pytorch_and_training_updates_weights():
    torch.manual_seed(1)
    network = make_network()
    obs = np.array([[0.3, -0.7]], dtype=np.float32)
    result = obs.copy()
    for i, layer in enumerate(parameters(network)):
        weight = np.asarray(layer["weights"], dtype=np.float32).reshape(result.shape[1], -1)
        result = result @ weight + np.asarray(layer["bias"], dtype=np.float32)
        if i < 2:
            result = np.maximum(result, 0)
    np.testing.assert_allclose(result, network(torch.from_numpy(obs)).detach().numpy(), atol=1e-7)
    target = make_network()
    target.load_state_dict(network.state_dict())
    before = network[0].weight.detach().clone()
    optimizer = torch.optim.Adam(network.parameters(), lr=1e-4)
    updates, loss = train(network, target, optimizer, transitions(batch(), 0.05), random.Random(1), 10, 0)
    assert updates == 10 and np.isfinite(loss)
    assert not torch.equal(before, network[0].weight)
    for a, b in zip(network.parameters(), target.parameters()):
        assert torch.equal(a, b)
