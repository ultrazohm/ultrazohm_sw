from __future__ import annotations

from dataclasses import dataclass

from ..models import VisualizationSignal


@dataclass(frozen=True)
class SoftwareVisualizationFragments:
    generated_file_context: dict[str, str]
    javascope_observable_enums: list[str]
    javascope_observable_pointers: list[str]
    javascope_slowdata_enums: list[str]
    javascope_slowdata_pointers: list[str]


def normalize_visualization_routes(visualization_signals: object) -> dict[str, str]:
    if visualization_signals is None:
        return {}
    if isinstance(visualization_signals, dict):
        routes: dict[str, str] = {}
        for signal_id, route in visualization_signals.items():
            normalized_route = str(route).strip().lower()
            if normalized_route in {"javascope", "slow_data", "both"}:
                routes[str(signal_id)] = normalized_route
        return routes
    return {str(signal_id): "javascope" for signal_id in visualization_signals}


def build_software_visualization_fragments(
    available_signals: list[VisualizationSignal],
    selected_routes: dict[str, str],
) -> SoftwareVisualizationFragments:
    selected_javascope_signals = [
        signal
        for signal in available_signals
        if selected_routes.get(signal.signal_id) in {"javascope", "both"}
    ]
    selected_slowdata_signals = [
        signal
        for signal in available_signals
        if selected_routes.get(signal.signal_id) in {"slow_data", "both"}
    ]
    routed_signals = list(
        {signal.signal_id: signal for signal in selected_javascope_signals + selected_slowdata_signals}.values()
    )
    field_declarations = [
        f"    float {signal.field_name};" for signal in routed_signals
    ] or ["    float unused;"]
    update_assignments = [
        f"    project_wizard_visualization_data.{signal.field_name} = {signal.float_expression};"
        for signal in routed_signals
    ]
    return SoftwareVisualizationFragments(
        generated_file_context={
            "field_declarations": "\n".join(field_declarations),
            "update_assignments": "\n".join(update_assignments),
        },
        javascope_observable_enums=[f"\t{signal.enum_name}," for signal in selected_javascope_signals],
        javascope_observable_pointers=[
            f"\tjs_ch_observable[{signal.enum_name}] = &project_wizard_visualization_data.{signal.field_name};"
            for signal in selected_javascope_signals
        ],
        javascope_slowdata_enums=[
            f"\tJSSD_FLOAT_{signal.enum_name.removeprefix('JSO_')}," for signal in selected_slowdata_signals
        ],
        javascope_slowdata_pointers=[
            f"\tjs_slowDataArray[JSSD_FLOAT_{signal.enum_name.removeprefix('JSO_')}] = &project_wizard_visualization_data.{signal.field_name};"
            for signal in selected_slowdata_signals
        ],
    )
