"""Final evaluation contract checks, without hardware or a GUI."""

import subprocess
from types import SimpleNamespace
from unittest.mock import MagicMock, patch

import polars as pl
import pytest
from test_train_pt1_dqn import batch
from train_pt1_live import (
    collect_replay,
    continuous_recording,
    evaluate_final,
    open_viewer,
    run_training,
)


@patch("train_pt1_live.time.sleep")
@patch("train_pt1_live.collect_replay")
@patch("train_pt1_dqn.train", side_effect=AssertionError("Evaluation must not train"))
def test_evaluation_records_greedy_rollout_and_metrics(train, collect, sleep, tmp_path):
    data = batch().with_columns(pl.lit(0.0).alias("JSO_pt1_epsilon"))
    collect.return_value = data, {
        "recording": "all.recording.json",
        "start": 6000,
        "stop": 9000,
    }
    uz = MagicMock()
    summary = evaluate_final(
        uz, tmp_path, {"number": 1, "handle": "all.recording.json"}
    )
    uz.set_variable.assert_called_once_with("DQN-Epsilon", 0.0)
    train.assert_not_called()
    assert summary["transitions"] == 3000
    assert len(summary["episodes"]) == 6
    assert summary["episodes"][0]["rmse"] == 1.0
    assert summary["episodes"][0]["return"] == -500.0
    assert summary["start"] == 6000
    assert summary["stop"] == 9000
    assert not (tmp_path / "evaluation.parquet").exists()
    assert (tmp_path / "evaluation.json").is_file()


@patch("train_pt1_live.time.sleep")
@patch("train_pt1_live.collect_replay")
def test_evaluation_rejects_exploration(collect, sleep, tmp_path):
    collect.return_value = batch(), "bad.recording.json"
    with pytest.raises(ValueError, match="Epsilon"):
        evaluate_final(
            MagicMock(), tmp_path, {"number": 1, "handle": "all.recording.json"}
        )
    assert not (tmp_path / "evaluation.parquet").exists()


def test_collector_reads_only_new_round_without_restarting_log():
    uz = MagicMock()
    uz.status.return_value = {
        "state": {"connected": True},
        "logging": {"fast": {"phase": "recording"}},
    }
    uz.data_info.side_effect = [{"stop": 9000}, {"stop": 10500}, {"stop": 12000}]
    data = batch().drop("JSO_pt1_time", "JSO_pt1_done")
    uz.read_range.side_effect = [data.head(1500), data.tail(1500)]
    result, segment = collect_replay(uz, {"number": 1, "handle": "all.recording.json"})
    assert result.height == 3000
    assert result["JSO_pt1_time"].to_list() == list(range(3000))
    assert result["JSO_pt1_done"].sum() == 6
    assert segment["start"] == 9000 and segment["stop"] == 12000
    assert uz.read_range.call_args_list[0].args == (9000, 10500)
    uz.start_logging.assert_not_called()
    uz.stop_logging.assert_not_called()
    uz.stop.assert_called_once()


@patch("update_parameters_prototype.time.sleep")
@patch("update_parameters_prototype.wait_feedback")
@patch("update_parameters_prototype.feedback")
def test_uploader_preserves_fixed_channels(feedback, wait, sleep):
    from train_pt1_dqn import make_network, parameters
    from update_parameters_prototype import network_info, uz_nn_update_weights

    feedback.return_value = {
        "active": 1,
        "received": 0,
        "error": 0,
        "target": 1,
        "expected": 1251,
    }
    uz = MagicMock()
    uz_nn_update_weights(
        uz,
        parameters(make_network()),
        network_info("dqn"),
        command_interval=0.0002,
        assign_feedback=False,
    )
    uz.set_observable.assert_not_called()
    uz.start_logging.assert_not_called()
    uz.stop_logging.assert_not_called()
    assert wait.call_count == 41  # 40 count checks and final completion.


def test_incomplete_replay_stops_and_session_finalizes(tmp_path):
    uz = MagicMock()
    uz.recordings.return_value = [{"stream": "fast", "recording": 1}]
    uz.data_info.return_value = {"stop": 100}
    uz.status.side_effect = [
        {"logging": {"fast": {"phase": "recording", "handle": "all.recording.json"}}},
        {"state": {"connected": False}},
        {"logging": {"fast": {"phase": "complete"}}},
    ]
    with pytest.raises(RuntimeError, match="disconnected"), continuous_recording(
        uz, tmp_path
    ) as recording:
        collect_replay(uz, recording)
    uz.start_logging.assert_called_once()
    uz.stop_logging.assert_called_once()


@patch("train_pt1_live.time.sleep")
@patch("train_pt1_live.configure_viewer")
@patch("train_pt1_live.upload_network")
@patch("train_pt1_live.collect_replay")
def test_training_and_evaluation_share_one_recording(
    collect, upload, configure, sleep, tmp_path
):
    args = SimpleNamespace(rounds=2, seed=1, gradient_steps=1, output=tmp_path)
    uz, viewer, process = MagicMock(), MagicMock(), MagicMock()
    process.poll.return_value = None
    uz.recordings.return_value = [{"stream": "fast", "recording": 1}]
    uz.data_info.return_value = {"stop": 0}
    uz.status.return_value = {
        "logging": {"fast": {"phase": "complete", "handle": "all.recording.json"}}
    }
    collect.side_effect = [
        (
            batch().with_columns(
                pl.lit(epsilon, dtype=pl.Float32).alias("JSO_pt1_epsilon")
            ),
            {
                "recording": "all.recording.json",
                "start": i * 3000,
                "stop": (i + 1) * 3000,
            },
        )
        for i, epsilon in enumerate([1.0, 0.05, 0.0])
    ]
    run_training(args, uz, viewer, process)
    uz.start_logging.assert_called_once()
    uz.stop_logging.assert_called_once()
    configure.assert_called_once()
    assert uz.set_observable.call_count == 19
    assert upload.call_count == 3
    assert collect.call_count == 3
    viewer.live_follow.assert_not_called()
    assert (tmp_path / "evaluation.json").exists()
    assert len((tmp_path / "progress.jsonl").read_text().splitlines()) == 2


@pytest.mark.parametrize("failure_stage", ["startup", "attach", "training"])
def test_viewer_cleanup_on_failure(tmp_path, failure_stage):
    args = SimpleNamespace(
        output=tmp_path, viewer_endpoint="127.0.0.1:19741", endpoint="127.0.0.1:19740"
    )
    with patch("train_pt1_live.subprocess.Popen") as launch, patch(
        "train_pt1_live.wait_for_viewer"
    ) as ready, patch("train_pt1_live.attach_viewer") as attach, patch(
        "ultrazohm_dataviewer.Client"
    ) as client:
        process = launch.return_value
        process.poll.return_value = None
        process.wait.side_effect = [subprocess.TimeoutExpired("viewer", 5), 0]
        if failure_stage == "startup":
            ready.side_effect = RuntimeError("startup failed")
        elif failure_stage == "attach":
            attach.side_effect = RuntimeError("attach failed")
        with pytest.raises(RuntimeError, match=failure_stage), open_viewer(
            args, []
        ) as (viewer, running):
            assert running is process
            raise RuntimeError("training failed")
        process.terminate.assert_called_once()
        process.kill.assert_called_once()
        assert process.wait.call_count == 2
        if failure_stage != "startup":
            client.return_value.__exit__.assert_called_once()
