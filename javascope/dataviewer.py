import base64
import io

from dash import Dash, html, dcc, Output, Input, State, Patch, callback_context, no_update
import plotly.graph_objects as go
import pandas as pd
from plotly_resampler import FigureResampler

app = Dash(__name__)
figures = {
    'graph-content-1': FigureResampler(),
    'graph-content-2': FigureResampler(),
    'graph-content-3': FigureResampler(),
    'graph-content-4': FigureResampler(),
}
df = None


def graph_panel(graph_index):
    return html.Div([
        html.H3(f'Graph {graph_index}', style={'margin': '0 0 10px 0'}),
        dcc.Checklist(
            id=f'cursor-toggle-{graph_index}',
            options=[{'label': ' Enable cursors', 'value': 'show'}],
            value=[],
            style={'margin': '0 0 12px 0'},
            inputStyle={'marginRight': '6px'},
        ),
        html.Div([
            html.Button(
                'Export data',
                id=f'export-button-{graph_index}',
                n_clicks=0,
                style={
                    'backgroundColor': '#4CAF50',
                    'color': 'white',
                    'border': 'none',
                    'padding': '8px 16px',
                    'fontSize': '14px',
                    'cursor': 'pointer',
                    'borderRadius': '5px',
                    'marginRight': '16px',
                },
            ),
            dcc.Checklist(
                id=f'export-relative-time-{graph_index}',
                options=[{'label': ' start time at 0', 'value': 'relative'}],
                value=[],
                style={'display': 'inline-block'},
                inputStyle={'marginRight': '6px'},
            ),
        ], style={'margin': '0 0 12px 0', 'display': 'flex', 'alignItems': 'center', 'flexWrap': 'wrap'}),
        dcc.Store(id=f'cursor-store-{graph_index}'),
        dcc.Store(id=f'viewport-store-{graph_index}'),
        dcc.Dropdown(
            id=f'dropdown-selection-{graph_index}',
            multi=True,
            clearable=False,
            style={'width': '100%', 'margin': '0 0 20px 0'}
        ),
        dcc.Graph(
            id=f'graph-content-{graph_index}',
            style={'width': '100%', 'height': '450px'},
            config={'editable': True, 'edits': {'shapePosition': True}}
        ),
        html.Div(
            id=f'cursor-info-{graph_index}',
            style={
                'marginTop': '10px',
                'fontFamily': 'monospace',
                'fontSize': '14px',
                'whiteSpace': 'pre-wrap',
            }
        ),
        dcc.Store(id=f'export-payload-{graph_index}'),
        dcc.ConfirmDialog(
            id=f'export-warning-{graph_index}',
            message='Enable cursors first!',
        ),
        html.Div(id=f'export-save-trigger-{graph_index}', style={'display': 'none'}),
    ], style={
        'backgroundColor': '#ffffff',
        'padding': '16px',
        'border': '1px solid #d9d9d9',
        'borderRadius': '8px',
        'boxShadow': '0 1px 4px rgba(0, 0, 0, 0.08)',
    })

app.layout = html.Div([
    html.H1(children='UltraZohm Data Viewer', style={'textAlign': 'center'}),
    html.Div([
        dcc.Upload(
            id='upload-data',
            children=html.Button('Upload File', style={'background-color': '#4CAF50', 'color': 'white', 'border': 'none', 'padding': '10px 20px', 'text-align': 'center', 'text-decoration': 'none', 'display': 'inline-block', 'font-size': '16px', 'cursor': 'pointer', 'border-radius': '5px'}),
            style={'margin': 'auto', 'textAlign': 'center'}
        ),
    ], style={'width': '80%', 'margin': '20px auto'}),
    html.Div([
        dcc.Checklist(
            id='time-axis-lock-toggle',
            options=[{'label': ' Lock time axis across all graphs', 'value': 'lock'}],
            value=[],
            style={'width': '90%', 'margin': '0 auto 10px auto'},
            inputStyle={'marginRight': '6px'},
        ),
        dcc.Store(id='shared-xaxis-store'),
    ]),
    dcc.Loading(
        html.Div(id='status-message', style={'width': '90%', 'margin': '0 auto 20px auto'}),
        type='circle',
        color='#4CAF50'
    ),
    html.Div([
        graph_panel(1),
        graph_panel(2),
        graph_panel(3),
        graph_panel(4),
    ], style={
        'width': '90%',
        'margin': 'auto',
        'display': 'grid',
        'gridTemplateColumns': 'repeat(auto-fit, minmax(500px, 1fr))',
        'gap': '20px',
    })
], style={'max-width': '1600px', 'margin': '0 auto', 'padding': '20px'})

@app.callback(
    Output('dropdown-selection-1', 'options'),
    Output('dropdown-selection-1', 'value'),
    Output('dropdown-selection-2', 'options'),
    Output('dropdown-selection-2', 'value'),
    Output('dropdown-selection-3', 'options'),
    Output('dropdown-selection-3', 'value'),
    Output('dropdown-selection-4', 'options'),
    Output('dropdown-selection-4', 'value'),
    Output('cursor-store-1', 'data', allow_duplicate=True),
    Output('cursor-store-2', 'data', allow_duplicate=True),
    Output('cursor-store-3', 'data', allow_duplicate=True),
    Output('cursor-store-4', 'data', allow_duplicate=True),
    Output('viewport-store-1', 'data', allow_duplicate=True),
    Output('viewport-store-2', 'data', allow_duplicate=True),
    Output('viewport-store-3', 'data', allow_duplicate=True),
    Output('viewport-store-4', 'data', allow_duplicate=True),
    Output('shared-xaxis-store', 'data'),
    Output('status-message', 'children'),
    Input('upload-data', 'contents'),
    Input('upload-data', 'filename'),
    prevent_initial_call=True,
    running=[
        (
            Output('status-message', 'children'),
            html.Div('Loading file, please wait...', style={'color': '#1f5aa6'}),
            '',
        )
    ],
)
def update_options(contents, filename):
    global df

    if not contents or not filename:
        return [], [], [], [], [], [], [], [], None, None, None, None, None, None, None, None, None, ''

    df, error = parse_uploaded_file(contents, filename)
    if error:
        return [], [], [], [], [], [], [], [], None, None, None, None, None, None, None, None, None, html.Div(error, style={'color': '#b00020'})

    selectable_columns = [col for col in df.columns if col != 'time']
    dropdown_options = [{'label': col, 'value': col} for col in selectable_columns]
    default_selection = [selectable_columns[0]] if selectable_columns else []
    status_message = html.Div(
        f'Loaded {filename} with {len(df)} rows and {len(df.columns)} columns.',
        style={'color': '#1f6f43'}
    )
    return (
        dropdown_options,
        default_selection,
        dropdown_options,
        [],
        dropdown_options,
        [],
        dropdown_options,
        [],
        None,
        None,
        None,
        None,
        None,
        None,
        None,
        None,
        None,
        status_message,
    )

@app.callback(
    Output('graph-content-1', 'figure'),
    Input('dropdown-selection-1', 'value'),
    Input('cursor-toggle-1', 'value'),
    Input('cursor-store-1', 'data'),
    State('viewport-store-1', 'data'),
    State('time-axis-lock-toggle', 'value'),
    State('shared-xaxis-store', 'data'),
    prevent_initial_call=True
)
def update_graph_1(value, cursor_toggle, cursor_positions, viewport_data, time_axis_lock, shared_xaxis_data):
    return update_graph_common('graph-content-1', value, cursor_toggle, cursor_positions, viewport_data, time_axis_lock, shared_xaxis_data)


@app.callback(
    Output('graph-content-2', 'figure'),
    Input('dropdown-selection-2', 'value'),
    Input('cursor-toggle-2', 'value'),
    Input('cursor-store-2', 'data'),
    State('viewport-store-2', 'data'),
    State('time-axis-lock-toggle', 'value'),
    State('shared-xaxis-store', 'data'),
    prevent_initial_call=True
)
def update_graph_2(value, cursor_toggle, cursor_positions, viewport_data, time_axis_lock, shared_xaxis_data):
    return update_graph_common('graph-content-2', value, cursor_toggle, cursor_positions, viewport_data, time_axis_lock, shared_xaxis_data)


@app.callback(
    Output('graph-content-3', 'figure'),
    Input('dropdown-selection-3', 'value'),
    Input('cursor-toggle-3', 'value'),
    Input('cursor-store-3', 'data'),
    State('viewport-store-3', 'data'),
    State('time-axis-lock-toggle', 'value'),
    State('shared-xaxis-store', 'data'),
    prevent_initial_call=True
)
def update_graph_3(value, cursor_toggle, cursor_positions, viewport_data, time_axis_lock, shared_xaxis_data):
    return update_graph_common('graph-content-3', value, cursor_toggle, cursor_positions, viewport_data, time_axis_lock, shared_xaxis_data)


@app.callback(
    Output('graph-content-4', 'figure'),
    Input('dropdown-selection-4', 'value'),
    Input('cursor-toggle-4', 'value'),
    Input('cursor-store-4', 'data'),
    State('viewport-store-4', 'data'),
    State('time-axis-lock-toggle', 'value'),
    State('shared-xaxis-store', 'data'),
    prevent_initial_call=True
)
def update_graph_4(value, cursor_toggle, cursor_positions, viewport_data, time_axis_lock, shared_xaxis_data):
    return update_graph_common('graph-content-4', value, cursor_toggle, cursor_positions, viewport_data, time_axis_lock, shared_xaxis_data)


def update_graph_common(graph_id, value, cursor_toggle, cursor_positions, viewport_data, time_axis_lock, shared_xaxis_data):
    triggered_id = callback_context.triggered_id
    if triggered_id == graph_id.replace('graph-content', 'cursor-store'):
        return patch_cursor_shapes(cursor_toggle, cursor_positions)

    return build_figure(graph_id, value, cursor_toggle, cursor_positions, viewport_data, time_axis_lock, shared_xaxis_data)


def build_figure(graph_id, value, cursor_toggle, cursor_positions, viewport_data, time_axis_lock, shared_xaxis_data):
    global df
    fig = figures[graph_id]
    cursor_enabled = 'show' in (cursor_toggle or [])

    empty_figure = go.Figure()
    empty_figure.update_layout(
        template="simple_white",
        hovermode='closest',
        xaxis=dict(showgrid=True, title='time'),
        yaxis=dict(showgrid=True),
        legend=dict(
            orientation='h',
            yanchor='top',
            y=-0.2,
            xanchor='left',
            x=0,
        ),
        margin=dict(l=60, r=20, t=40, b=110),
    )

    if df is None:
        return empty_figure

    fig.replace(go.Figure())
    if not value:
        return empty_figure

    if 'time' not in df.columns:
        empty_figure.update_layout(title='The uploaded file must contain a "time" column for plotting.')
        return empty_figure

    for col in value:
        if col not in df.columns:
            continue
        fig.add_trace(go.Scattergl(name=col, x=df['time'], y=df[col]))

    if cursor_enabled:
        cursor_x1, cursor_x2 = get_cursor_positions(cursor_positions)
        fig.update_layout(shapes=build_cursor_shapes(cursor_x1, cursor_x2))

    fig.update_layout(
        template="simple_white",
        hovermode='closest',
        xaxis=dict(showgrid=True, title='time'),
        yaxis=dict(showgrid=True),
        showlegend=True,
        legend=dict(
            orientation='h',
            yanchor='top',
            y=-0.2,
            xanchor='left',
            x=0,
        ),
        margin=dict(l=60, r=20, t=40, b=110),
    )
    preserve_axis_ranges(fig, viewport_data)
    if 'lock' in (time_axis_lock or []):
        apply_shared_xaxis(fig, shared_xaxis_data)

    return fig


def patch_cursor_shapes(cursor_toggle, cursor_positions):
    patched_figure = Patch()
    if 'show' not in (cursor_toggle or []):
        patched_figure['layout']['shapes'] = []
        return patched_figure

    cursor_x1, cursor_x2 = get_cursor_positions(cursor_positions)
    if cursor_x1 is None or cursor_x2 is None:
        patched_figure['layout']['shapes'] = []
        return patched_figure

    patched_figure['layout']['shapes'] = build_cursor_shapes(cursor_x1, cursor_x2)
    return patched_figure


def build_cursor_shapes(cursor_x1, cursor_x2):
    return [
        {
            'type': 'line',
            'xref': 'x',
            'yref': 'paper',
            'x0': cursor_x1,
            'x1': cursor_x1,
            'y0': 0,
            'y1': 1,
            'line': {'color': '#d62728', 'width': 2},
        },
        {
            'type': 'line',
            'xref': 'x',
            'yref': 'paper',
            'x0': cursor_x2,
            'x1': cursor_x2,
            'y0': 0,
            'y1': 1,
            'line': {'color': '#1f77b4', 'width': 2},
        },
    ]


for graph_id, figure in figures.items():
    figure.register_update_graph_callback(app=app, graph_id=graph_id)


app.clientside_callback(
    "function(payload) { return window.dash_clientside.dataviewer.save_export(payload); }",
    Output('export-save-trigger-1', 'children'),
    Input('export-payload-1', 'data'),
    prevent_initial_call=True,
)

app.clientside_callback(
    "function(payload) { return window.dash_clientside.dataviewer.save_export(payload); }",
    Output('export-save-trigger-2', 'children'),
    Input('export-payload-2', 'data'),
    prevent_initial_call=True,
)

app.clientside_callback(
    "function(payload) { return window.dash_clientside.dataviewer.save_export(payload); }",
    Output('export-save-trigger-3', 'children'),
    Input('export-payload-3', 'data'),
    prevent_initial_call=True,
)

app.clientside_callback(
    "function(payload) { return window.dash_clientside.dataviewer.save_export(payload); }",
    Output('export-save-trigger-4', 'children'),
    Input('export-payload-4', 'data'),
    prevent_initial_call=True,
)


@app.callback(
    Output('cursor-store-1', 'data'),
    Input('graph-content-1', 'relayoutData'),
    State('cursor-store-1', 'data'),
    prevent_initial_call=True
)
def update_cursor_store_1(relayout_data, cursor_positions):
    return extract_cursor_positions(relayout_data, cursor_positions)


@app.callback(
    Output('cursor-store-2', 'data'),
    Input('graph-content-2', 'relayoutData'),
    State('cursor-store-2', 'data'),
    prevent_initial_call=True
)
def update_cursor_store_2(relayout_data, cursor_positions):
    return extract_cursor_positions(relayout_data, cursor_positions)


@app.callback(
    Output('cursor-store-3', 'data'),
    Input('graph-content-3', 'relayoutData'),
    State('cursor-store-3', 'data'),
    prevent_initial_call=True
)
def update_cursor_store_3(relayout_data, cursor_positions):
    return extract_cursor_positions(relayout_data, cursor_positions)


@app.callback(
    Output('cursor-store-4', 'data'),
    Input('graph-content-4', 'relayoutData'),
    State('cursor-store-4', 'data'),
    prevent_initial_call=True
)
def update_cursor_store_4(relayout_data, cursor_positions):
    return extract_cursor_positions(relayout_data, cursor_positions)


@app.callback(
    Output('viewport-store-1', 'data'),
    Input('graph-content-1', 'relayoutData'),
    State('viewport-store-1', 'data'),
    prevent_initial_call=True
)
def update_viewport_store_1(relayout_data, viewport_data):
    return extract_viewport_data(relayout_data, viewport_data)


@app.callback(
    Output('viewport-store-2', 'data'),
    Input('graph-content-2', 'relayoutData'),
    State('viewport-store-2', 'data'),
    prevent_initial_call=True
)
def update_viewport_store_2(relayout_data, viewport_data):
    return extract_viewport_data(relayout_data, viewport_data)


@app.callback(
    Output('viewport-store-3', 'data'),
    Input('graph-content-3', 'relayoutData'),
    State('viewport-store-3', 'data'),
    prevent_initial_call=True
)
def update_viewport_store_3(relayout_data, viewport_data):
    return extract_viewport_data(relayout_data, viewport_data)


@app.callback(
    Output('viewport-store-4', 'data'),
    Input('graph-content-4', 'relayoutData'),
    State('viewport-store-4', 'data'),
    prevent_initial_call=True
)
def update_viewport_store_4(relayout_data, viewport_data):
    return extract_viewport_data(relayout_data, viewport_data)


@app.callback(
    Output('shared-xaxis-store', 'data', allow_duplicate=True),
    Input('time-axis-lock-toggle', 'value'),
    Input('graph-content-1', 'relayoutData'),
    Input('graph-content-2', 'relayoutData'),
    Input('graph-content-3', 'relayoutData'),
    Input('graph-content-4', 'relayoutData'),
    State('shared-xaxis-store', 'data'),
    prevent_initial_call=True
)
def update_shared_xaxis_store(time_axis_lock, relayout_1, relayout_2, relayout_3, relayout_4, current_shared_xaxis):
    if 'lock' not in (time_axis_lock or []):
        return None

    trigger = callback_context.triggered_id
    relayout_map = {
        'graph-content-1': relayout_1,
        'graph-content-2': relayout_2,
        'graph-content-3': relayout_3,
        'graph-content-4': relayout_4,
    }
    relayout_data = relayout_map.get(trigger)
    if not relayout_data:
        return no_update

    shared_xaxis_data = extract_xaxis_data(relayout_data)
    if not shared_xaxis_data:
        return no_update

    if shared_xaxis_data == (current_shared_xaxis or {}):
        return no_update

    return shared_xaxis_data


@app.callback(
    Output('graph-content-1', 'figure', allow_duplicate=True),
    Output('graph-content-2', 'figure', allow_duplicate=True),
    Output('graph-content-3', 'figure', allow_duplicate=True),
    Output('graph-content-4', 'figure', allow_duplicate=True),
    Input('shared-xaxis-store', 'data'),
    Input('time-axis-lock-toggle', 'value'),
    prevent_initial_call=True
)
def sync_time_axis(shared_xaxis_data, time_axis_lock):
    if 'lock' not in (time_axis_lock or []) or not shared_xaxis_data:
        return no_update, no_update, no_update, no_update

    patch = build_shared_xaxis_patch(shared_xaxis_data)
    if not patch:
        return no_update, no_update, no_update, no_update

    return patch, patch, patch, patch


@app.callback(
    Output('cursor-info-1', 'children'),
    Input('dropdown-selection-1', 'value'),
    Input('cursor-toggle-1', 'value'),
    Input('cursor-store-1', 'data'),
    prevent_initial_call=True
)
def update_cursor_info_1(value, cursor_toggle, cursor_positions):
    return build_cursor_info(value, cursor_toggle, cursor_positions)


@app.callback(
    Output('cursor-info-2', 'children'),
    Input('dropdown-selection-2', 'value'),
    Input('cursor-toggle-2', 'value'),
    Input('cursor-store-2', 'data'),
    prevent_initial_call=True
)
def update_cursor_info_2(value, cursor_toggle, cursor_positions):
    return build_cursor_info(value, cursor_toggle, cursor_positions)


@app.callback(
    Output('cursor-info-3', 'children'),
    Input('dropdown-selection-3', 'value'),
    Input('cursor-toggle-3', 'value'),
    Input('cursor-store-3', 'data'),
    prevent_initial_call=True
)
def update_cursor_info_3(value, cursor_toggle, cursor_positions):
    return build_cursor_info(value, cursor_toggle, cursor_positions)


@app.callback(
    Output('cursor-info-4', 'children'),
    Input('dropdown-selection-4', 'value'),
    Input('cursor-toggle-4', 'value'),
    Input('cursor-store-4', 'data'),
    prevent_initial_call=True
)
def update_cursor_info_4(value, cursor_toggle, cursor_positions):
    return build_cursor_info(value, cursor_toggle, cursor_positions)


@app.callback(
    Output('export-payload-1', 'data'),
    Output('export-warning-1', 'displayed'),
    Output('export-warning-1', 'message'),
    Input('export-button-1', 'n_clicks'),
    State('dropdown-selection-1', 'value'),
    State('cursor-toggle-1', 'value'),
    State('cursor-store-1', 'data'),
    State('export-relative-time-1', 'value'),
    prevent_initial_call=True
)
def export_data_1(n_clicks, value, cursor_toggle, cursor_positions, relative_time):
    return export_plot_data(n_clicks, value, cursor_toggle, cursor_positions, relative_time, 1)


@app.callback(
    Output('export-payload-2', 'data'),
    Output('export-warning-2', 'displayed'),
    Output('export-warning-2', 'message'),
    Input('export-button-2', 'n_clicks'),
    State('dropdown-selection-2', 'value'),
    State('cursor-toggle-2', 'value'),
    State('cursor-store-2', 'data'),
    State('export-relative-time-2', 'value'),
    prevent_initial_call=True
)
def export_data_2(n_clicks, value, cursor_toggle, cursor_positions, relative_time):
    return export_plot_data(n_clicks, value, cursor_toggle, cursor_positions, relative_time, 2)


@app.callback(
    Output('export-payload-3', 'data'),
    Output('export-warning-3', 'displayed'),
    Output('export-warning-3', 'message'),
    Input('export-button-3', 'n_clicks'),
    State('dropdown-selection-3', 'value'),
    State('cursor-toggle-3', 'value'),
    State('cursor-store-3', 'data'),
    State('export-relative-time-3', 'value'),
    prevent_initial_call=True
)
def export_data_3(n_clicks, value, cursor_toggle, cursor_positions, relative_time):
    return export_plot_data(n_clicks, value, cursor_toggle, cursor_positions, relative_time, 3)


@app.callback(
    Output('export-payload-4', 'data'),
    Output('export-warning-4', 'displayed'),
    Output('export-warning-4', 'message'),
    Input('export-button-4', 'n_clicks'),
    State('dropdown-selection-4', 'value'),
    State('cursor-toggle-4', 'value'),
    State('cursor-store-4', 'data'),
    State('export-relative-time-4', 'value'),
    prevent_initial_call=True
)
def export_data_4(n_clicks, value, cursor_toggle, cursor_positions, relative_time):
    return export_plot_data(n_clicks, value, cursor_toggle, cursor_positions, relative_time, 4)


def extract_cursor_positions(relayout_data, cursor_positions):
    if not relayout_data or df is None or 'time' not in df.columns:
        return no_update

    current_positions = get_cursor_positions(cursor_positions)
    if current_positions == (None, None):
        return no_update

    updated_positions = list(current_positions)
    found_cursor_update = False

    for index in range(2):
        x0_key = f'shapes[{index}].x0'
        x1_key = f'shapes[{index}].x1'
        if x0_key in relayout_data:
            updated_positions[index] = snap_cursor_to_time(relayout_data[x0_key])
            found_cursor_update = True
        elif x1_key in relayout_data:
            updated_positions[index] = snap_cursor_to_time(relayout_data[x1_key])
            found_cursor_update = True

    if 'shapes' in relayout_data and len(relayout_data['shapes']) >= 2:
        updated_positions = [
            snap_cursor_to_time(relayout_data['shapes'][0].get('x0', updated_positions[0])),
            snap_cursor_to_time(relayout_data['shapes'][1].get('x0', updated_positions[1])),
        ]
        found_cursor_update = True

    if not found_cursor_update:
        return no_update

    return updated_positions


def build_cursor_info(value, cursor_toggle, cursor_positions):
    global df

    if df is None or 'show' not in (cursor_toggle or []):
        return ''

    if 'time' not in df.columns:
        return 'Cursors require a "time" column.'

    selected_channels = [col for col in (value or []) if col in df.columns]
    if not selected_channels:
        return 'Select at least one channel to show cursor values.'

    cursor_x1, cursor_x2 = get_cursor_positions(cursor_positions)
    index_1 = nearest_time_index(cursor_x1)
    index_2 = nearest_time_index(cursor_x2)

    lines = [
        f'Cursor A: x={format_value(df["time"].iloc[index_1])}',
        f'Cursor B: x={format_value(df["time"].iloc[index_2])}',
        f'Delta X: {format_value(df["time"].iloc[index_2] - df["time"].iloc[index_1])}',
    ]

    for col in selected_channels:
        y1 = df[col].iloc[index_1]
        y2 = df[col].iloc[index_2]
        lines.append(
            f'{col}: A={format_value(y1)}, B={format_value(y2)}, Delta={format_value(y2 - y1)}'
        )

    return '\n'.join(lines)


def get_cursor_positions(cursor_positions):
    if cursor_positions and len(cursor_positions) == 2:
        return cursor_positions[0], cursor_positions[1]

    return default_cursor_positions()


def default_cursor_positions():
    if df is None or 'time' not in df.columns or df.empty:
        return None, None

    time_series = df['time']
    start = time_series.iloc[0]
    stop = time_series.iloc[-1]
    span = stop - start
    return start + 0.25 * span, start + 0.75 * span


def nearest_time_index(cursor_x):
    return (df['time'] - cursor_x).abs().idxmin()


def snap_cursor_to_time(cursor_x):
    if cursor_x is None:
        return None
    return df['time'].iloc[nearest_time_index(cursor_x)]


def format_value(value):
    if isinstance(value, float):
        return f'{value:.6g}'
    return str(value)


def export_plot_data(n_clicks, value, cursor_toggle, cursor_positions, relative_time, graph_index):
    global df

    if not n_clicks or df is None or 'time' not in df.columns:
        return no_update, False, 'Enable cursors first!'

    if 'show' not in (cursor_toggle or []):
        return no_update, True, 'Enable cursors first!'

    selected_channels = [col for col in (value or []) if col in df.columns]
    if not selected_channels:
        return no_update, True, 'Select at least one channel to export.'

    cursor_x1, cursor_x2 = get_cursor_positions(cursor_positions)
    if cursor_x1 is None or cursor_x2 is None:
        return no_update, True, 'Enable cursors first!'

    start_time, stop_time = sorted((cursor_x1, cursor_x2))
    export_df = df.loc[(df['time'] >= start_time) & (df['time'] <= stop_time), ['time', *selected_channels]].copy()
    if export_df.empty:
        return no_update, True, 'No data points found between the cursors.'

    if 'relative' in (relative_time or []):
        export_df['time'] = export_df['time'] - export_df['time'].iloc[0]

    export_df['time'] = export_df['time'].round(12)

    filename_suffix = 'relative' if 'relative' in (relative_time or []) else 'absolute'
    default_filename = f'graph_{graph_index}_cursor_export_{filename_suffix}.csv'
    export_payload = {
        'content': export_df.to_csv(index=False),
        'filename': default_filename,
        'mime_type': 'text/csv',
    }
    return export_payload, False, 'Enable cursors first!'


def preserve_axis_ranges(fig, viewport_data):
    if not viewport_data:
        return

    if viewport_data.get('xaxis.autorange'):
        fig.update_xaxes(autorange=True)
    elif 'xaxis.range[0]' in viewport_data and 'xaxis.range[1]' in viewport_data:
        fig.update_xaxes(range=[viewport_data['xaxis.range[0]'], viewport_data['xaxis.range[1]']])

    if viewport_data.get('yaxis.autorange'):
        fig.update_yaxes(autorange=True)
    elif 'yaxis.range[0]' in viewport_data and 'yaxis.range[1]' in viewport_data:
        fig.update_yaxes(range=[viewport_data['yaxis.range[0]'], viewport_data['yaxis.range[1]']])


def apply_shared_xaxis(fig, shared_xaxis_data):
    if not shared_xaxis_data:
        return

    if shared_xaxis_data.get('xaxis.autorange'):
        fig.update_xaxes(autorange=True)
    elif 'xaxis.range[0]' in shared_xaxis_data and 'xaxis.range[1]' in shared_xaxis_data:
        fig.update_xaxes(range=[shared_xaxis_data['xaxis.range[0]'], shared_xaxis_data['xaxis.range[1]']])


def extract_xaxis_data(relayout_data):
    if not relayout_data:
        return None

    # Ignore shape drag events to avoid syncing x-axis while moving cursors.
    if 'shapes' in relayout_data or any(key.startswith('shapes[') for key in relayout_data):
        return None

    shared_xaxis_data = {}

    if 'xaxis.range[0]' in relayout_data and 'xaxis.range[1]' in relayout_data:
        shared_xaxis_data['xaxis.range[0]'] = relayout_data['xaxis.range[0]']
        shared_xaxis_data['xaxis.range[1]'] = relayout_data['xaxis.range[1]']
        shared_xaxis_data['xaxis.autorange'] = False
        return shared_xaxis_data

    if 'xaxis.autorange' in relayout_data:
        shared_xaxis_data['xaxis.autorange'] = relayout_data['xaxis.autorange']
        return shared_xaxis_data

    return None


def build_shared_xaxis_patch(shared_xaxis_data):
    if not shared_xaxis_data:
        return None

    patched_figure = Patch()

    if shared_xaxis_data.get('xaxis.autorange'):
        patched_figure['layout']['xaxis']['autorange'] = True
    elif 'xaxis.range[0]' in shared_xaxis_data and 'xaxis.range[1]' in shared_xaxis_data:
        patched_figure['layout']['xaxis']['autorange'] = False
        patched_figure['layout']['xaxis']['range'] = [
            shared_xaxis_data['xaxis.range[0]'],
            shared_xaxis_data['xaxis.range[1]'],
        ]
    else:
        return None

    return patched_figure


def extract_viewport_data(relayout_data, viewport_data):
    if not relayout_data:
        return no_update

    # Ignore relayout events that are caused by dragging cursor shapes.
    # Those events may contain incidental axis information, but they should
    # not overwrite the user's actual viewport.
    if 'shapes' in relayout_data or any(key.startswith('shapes[') for key in relayout_data):
        return no_update

    updated_viewport = dict(viewport_data or {})
    found_viewport_update = False
    range_updated = False

    for key in ('xaxis.range[0]', 'xaxis.range[1]', 'yaxis.range[0]', 'yaxis.range[1]'):
        if key in relayout_data:
            updated_viewport[key] = relayout_data[key]
            found_viewport_update = True
            range_updated = True

    if range_updated:
        updated_viewport['xaxis.autorange'] = False
        updated_viewport['yaxis.autorange'] = False

    for key in ('xaxis.autorange', 'yaxis.autorange'):
        if key in relayout_data:
            updated_viewport[key] = relayout_data[key]
            found_viewport_update = True
            if relayout_data[key]:
                range0 = key.replace('.autorange', '.range[0]')
                range1 = key.replace('.autorange', '.range[1]')
                updated_viewport.pop(range0, None)
                updated_viewport.pop(range1, None)

    if not found_viewport_update:
        return no_update

    return updated_viewport


def parse_uploaded_file(contents, filename):
    filetype = get_file_extension(filename)
    if filetype not in {'csv', 'parquet'}:
        return None, f'Unsupported file type "{filetype}". Please upload a .csv or .parquet file.'

    try:
        _, content_string = contents.split(',', 1)
        decoded = base64.b64decode(content_string)
    except (ValueError, TypeError, base64.binascii.Error):
        return None, 'The uploaded file could not be decoded.'

    try:
        if filetype == 'parquet':
            df = pd.read_parquet(io.BytesIO(decoded))
        else:
            df = pd.read_csv(io.StringIO(decoded.decode('utf-8')), sep=';')
    except UnicodeDecodeError:
        return None, 'The CSV file must be UTF-8 encoded.'
    except Exception as exc:
        return None, f'Failed to read "{filename}": {exc}'

    if df.empty:
        return None, f'"{filename}" does not contain any rows.'

    if len(df.columns) == 0:
        return None, f'"{filename}" does not contain any columns.'

    return df, None


def get_file_extension(filename):
    parts = filename.split('.')
    if len(parts) == 1:
        return None

    return parts[-1].lower()

if __name__ == '__main__':
    app.run(debug=True,port=8080)
