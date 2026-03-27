import base64
import io
import re

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

datasets = {
    'file1': None,
    'file2': None,
}
dataset_filenames = {
    'file1': None,
    'file2': None,
}


def graph_panel(graph_index):
    return html.Div([
        html.H3(f'Graph {graph_index}', style={'margin': '0 0 10px 0'}),
        html.Div([
            dcc.Dropdown(
                id=f'file-selection-{graph_index}',
                clearable=False,
                placeholder='Select file',
                style={'width': '100%', 'margin': '0 0 12px 0'},
            ),
        ], id=f'file-selection-container-{graph_index}', style={'display': 'none'}),
        html.Div([
            dcc.Checklist(
                id=f'overlay-compare-{graph_index}',
                options=[{'label': ' Overlay compare (both files)', 'value': 'overlay'}],
                value=[],
                style={'margin': '0 0 12px 0'},
                inputStyle={'marginRight': '6px'},
            ),
        ], id=f'overlay-compare-container-{graph_index}', style={'display': 'none'}),
        dcc.Checklist(
            id=f'cursor-toggle-{graph_index}',
            options=[{'label': ' Enable cursors', 'value': 'show'}],
            value=[],
            style={'margin': '0 0 12px 0'},
            inputStyle={'marginRight': '6px'},
        ),
        html.Div([
            html.Button(
                'Fit cursor into plot',
                id=f'fit-cursor-button-{graph_index}',
                n_clicks=0,
                style={
                    'backgroundColor': '#f3f4f6',
                    'color': '#222222',
                    'border': '1px solid #c7c9cc',
                    'padding': '8px 16px',
                    'fontSize': '14px',
                    'cursor': 'pointer',
                    'borderRadius': '5px',
                    'marginRight': '16px',
                    'display': 'none',
                },
            ),
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
        dcc.Store(id=f'layout-store-{graph_index}'),
        dcc.Store(id=f'secondary-axis-enabled-{graph_index}', data=False),
        dcc.Dropdown(
            id=f'dropdown-selection-{graph_index}',
            multi=True,
            clearable=False,
            style={'width': '100%', 'margin': '0 0 20px 0'}
        ),
        html.Button(
            'Enable second axis',
            id=f'secondary-axis-toggle-{graph_index}',
            n_clicks=0,
            style={
                'backgroundColor': '#f3f4f6',
                'color': '#222222',
                'border': '1px solid #c7c9cc',
                'padding': '8px 16px',
                'fontSize': '14px',
                'cursor': 'pointer',
                'borderRadius': '5px',
                'marginBottom': '12px',
            },
        ),
        html.Div([
            html.Div('Right axis channels', style={'margin': '0 0 8px 0', 'fontWeight': '600'}),
            dcc.Dropdown(
                id=f'secondary-axis-selection-{graph_index}',
                multi=True,
                clearable=True,
                placeholder='Select channels for right axis',
                style={'width': '100%', 'margin': '0 0 20px 0'}
            ),
        ], id=f'secondary-axis-container-{graph_index}', style={'display': 'none'}),
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
                'display': 'none',
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
        html.Div('Number of plots', style={'marginBottom': '8px', 'fontWeight': '600'}),
        dcc.RadioItems(
            id='plot-count-selector',
            options=[
                {'label': '1 plot', 'value': 1},
                {'label': '2 plots', 'value': 2},
                {'label': '4 plots', 'value': 4},
            ],
            value=1,
            inline=True,
            inputStyle={'marginRight': '6px', 'marginLeft': '14px'},
            labelStyle={'cursor': 'pointer'},
        ),
    ], style={'width': '90%', 'margin': '0 auto 10px auto'}),
    html.Div([
        dcc.Upload(
            id='upload-data',
            multiple=True,
            children=html.Button(
                'Upload up to 2 files',
                style={
                    'background-color': '#4CAF50',
                    'color': 'white',
                    'border': 'none',
                    'padding': '10px 20px',
                    'text-align': 'center',
                    'text-decoration': 'none',
                    'display': 'inline-block',
                    'font-size': '16px',
                    'cursor': 'pointer',
                    'border-radius': '5px',
                }
            ),
            style={'margin': 'auto', 'textAlign': 'center'}
        ),
        html.Button(
            'Clear loaded data',
            id='clear-upload-data',
            n_clicks=0,
            style={
                'backgroundColor': '#f3f4f6',
                'color': '#222222',
                'border': '1px solid #c7c9cc',
                'padding': '10px 20px',
                'fontSize': '16px',
                'cursor': 'pointer',
                'borderRadius': '5px',
                'marginLeft': '12px',
            },
        ),
    ], style={'width': '80%', 'margin': '20px auto', 'display': 'flex', 'justifyContent': 'center', 'alignItems': 'center', 'flexWrap': 'wrap', 'gap': '12px'}),
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
        html.Div(graph_panel(1), id='graph-panel-container-1'),
        html.Div(graph_panel(2), id='graph-panel-container-2'),
        html.Div(graph_panel(3), id='graph-panel-container-3'),
        html.Div(graph_panel(4), id='graph-panel-container-4'),
    ], id='graphs-grid', style={
        'width': '90%',
        'margin': 'auto',
        'display': 'grid',
        'gridTemplateColumns': 'repeat(2, minmax(500px, 1fr))',
        'gap': '20px',
    })
], style={'max-width': '1600px', 'margin': '0 auto', 'padding': '20px'})


@app.callback(
    Output('graph-panel-container-1', 'style'),
    Output('graph-panel-container-2', 'style'),
    Output('graph-panel-container-3', 'style'),
    Output('graph-panel-container-4', 'style'),
    Output('graphs-grid', 'style'),
    Input('plot-count-selector', 'value')
)
def update_plot_layout(plot_count):
    hidden = {'display': 'none'}
    shown = {'display': 'block'}

    styles = {
        1: [shown, hidden, hidden, hidden],
        2: [shown, shown, hidden, hidden],
        4: [shown, shown, shown, shown],
    }.get(plot_count, [shown, shown, shown, shown])

    grid_columns = '1fr' if plot_count == 1 else 'repeat(2, minmax(500px, 1fr))'
    grid_style = {
        'width': '90%',
        'margin': 'auto',
        'display': 'grid',
        'gridTemplateColumns': grid_columns,
        'gap': '20px',
    }

    return styles[0], styles[1], styles[2], styles[3], grid_style


@app.callback(
    Output('dropdown-selection-1', 'options'),
    Output('dropdown-selection-1', 'value'),
    Output('dropdown-selection-2', 'options'),
    Output('dropdown-selection-2', 'value'),
    Output('dropdown-selection-3', 'options'),
    Output('dropdown-selection-3', 'value'),
    Output('dropdown-selection-4', 'options'),
    Output('dropdown-selection-4', 'value'),
    Output('secondary-axis-selection-1', 'options'),
    Output('secondary-axis-selection-1', 'value'),
    Output('secondary-axis-selection-2', 'options'),
    Output('secondary-axis-selection-2', 'value'),
    Output('secondary-axis-selection-3', 'options'),
    Output('secondary-axis-selection-3', 'value'),
    Output('secondary-axis-selection-4', 'options'),
    Output('secondary-axis-selection-4', 'value'),
    Output('secondary-axis-enabled-1', 'data', allow_duplicate=True),
    Output('secondary-axis-enabled-2', 'data', allow_duplicate=True),
    Output('secondary-axis-enabled-3', 'data', allow_duplicate=True),
    Output('secondary-axis-enabled-4', 'data', allow_duplicate=True),
    Output('file-selection-1', 'options'),
    Output('file-selection-1', 'value'),
    Output('file-selection-2', 'options'),
    Output('file-selection-2', 'value'),
    Output('file-selection-3', 'options'),
    Output('file-selection-3', 'value'),
    Output('file-selection-4', 'options'),
    Output('file-selection-4', 'value'),
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
            html.Div('Loading file(s), please wait...', style={'color': '#1f5aa6'}),
            '',
        )
    ],
)
def update_options(contents, filenames):
    clear_result = (
        [], [], [], [], [], [], [], [],
        [], [], [], [], [], [], [], [],
        False, False, False, False,
        [], None, [], None, [], None, [], None,
        None, None, None, None,
        None, None, None, None,
        None,
        '',
    )

    if not contents or not filenames:
        reset_datasets()
        return clear_result

    content_list = contents if isinstance(contents, list) else [contents]
    filename_list = filenames if isinstance(filenames, list) else [filenames]

    if len(content_list) != len(filename_list):
        reset_datasets()
        return clear_result[:-1] + (html.Div('Upload payload is inconsistent.', style={'color': '#b00020'}),)

    if len(content_list) > 2:
        reset_datasets()
        return clear_result[:-1] + (html.Div('Please upload at most 2 files.', style={'color': '#b00020'}),)

    loaded = []
    for index, (content, filename) in enumerate(zip(content_list, filename_list), start=1):
        parsed_df, error = parse_uploaded_file(content, filename)
        if error:
            reset_datasets()
            return clear_result[:-1] + (html.Div(error, style={'color': '#b00020'}),)
        loaded.append((f'file{index}', filename, parsed_df))

    reset_datasets()
    for file_key, filename, loaded_df in loaded:
        datasets[file_key] = loaded_df
        dataset_filenames[file_key] = filename

    selectable_columns = sorted({
        col
        for loaded_df in datasets.values() if loaded_df is not None
        for col in loaded_df.columns
        if col != 'time'
    }, key=channel_sort_key)

    dropdown_options = [{'label': col, 'value': col} for col in selectable_columns]
    default_selection = [selectable_columns[0]] if selectable_columns else []

    file_options = []
    if datasets['file1'] is not None:
        file_options.append({'label': f'File 1: {dataset_filenames["file1"]}', 'value': 'file1'})
    if datasets['file2'] is not None:
        file_options.append({'label': f'File 2: {dataset_filenames["file2"]}', 'value': 'file2'})

    default_file_values = ['file1', 'file1', 'file1', 'file1']
    if datasets['file2'] is not None:
        default_file_values = ['file1', 'file2', 'file1', 'file2']

    file_stats = []
    for file_key in ('file1', 'file2'):
        if datasets[file_key] is not None:
            file_stats.append(
                f'{dataset_filenames[file_key]} ({len(datasets[file_key])} rows, {len(datasets[file_key].columns)} columns)'
            )

    status_message = html.Div(
        'Loaded: ' + ' | '.join(file_stats),
        style={'color': '#1f6f43'}
    )

    return (
        dropdown_options,
        default_selection,
        dropdown_options,
        default_selection,
        dropdown_options,
        default_selection,
        dropdown_options,
        default_selection,
        dropdown_options,
        [],
        dropdown_options,
        [],
        dropdown_options,
        [],
        dropdown_options,
        [],
        False,
        False,
        False,
        False,
        file_options,
        default_file_values[0],
        file_options,
        default_file_values[1],
        file_options,
        default_file_values[2],
        file_options,
        default_file_values[3],
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
    Output('upload-data', 'contents', allow_duplicate=True),
    Output('upload-data', 'filename', allow_duplicate=True),
    Output('dropdown-selection-1', 'options', allow_duplicate=True),
    Output('dropdown-selection-1', 'value', allow_duplicate=True),
    Output('dropdown-selection-2', 'options', allow_duplicate=True),
    Output('dropdown-selection-2', 'value', allow_duplicate=True),
    Output('dropdown-selection-3', 'options', allow_duplicate=True),
    Output('dropdown-selection-3', 'value', allow_duplicate=True),
    Output('dropdown-selection-4', 'options', allow_duplicate=True),
    Output('dropdown-selection-4', 'value', allow_duplicate=True),
    Output('secondary-axis-selection-1', 'options', allow_duplicate=True),
    Output('secondary-axis-selection-1', 'value', allow_duplicate=True),
    Output('secondary-axis-selection-2', 'options', allow_duplicate=True),
    Output('secondary-axis-selection-2', 'value', allow_duplicate=True),
    Output('secondary-axis-selection-3', 'options', allow_duplicate=True),
    Output('secondary-axis-selection-3', 'value', allow_duplicate=True),
    Output('secondary-axis-selection-4', 'options', allow_duplicate=True),
    Output('secondary-axis-selection-4', 'value', allow_duplicate=True),
    Output('secondary-axis-enabled-1', 'data', allow_duplicate=True),
    Output('secondary-axis-enabled-2', 'data', allow_duplicate=True),
    Output('secondary-axis-enabled-3', 'data', allow_duplicate=True),
    Output('secondary-axis-enabled-4', 'data', allow_duplicate=True),
    Output('file-selection-1', 'options', allow_duplicate=True),
    Output('file-selection-1', 'value', allow_duplicate=True),
    Output('file-selection-2', 'options', allow_duplicate=True),
    Output('file-selection-2', 'value', allow_duplicate=True),
    Output('file-selection-3', 'options', allow_duplicate=True),
    Output('file-selection-3', 'value', allow_duplicate=True),
    Output('file-selection-4', 'options', allow_duplicate=True),
    Output('file-selection-4', 'value', allow_duplicate=True),
    Output('cursor-store-1', 'data', allow_duplicate=True),
    Output('cursor-store-2', 'data', allow_duplicate=True),
    Output('cursor-store-3', 'data', allow_duplicate=True),
    Output('cursor-store-4', 'data', allow_duplicate=True),
    Output('viewport-store-1', 'data', allow_duplicate=True),
    Output('viewport-store-2', 'data', allow_duplicate=True),
    Output('viewport-store-3', 'data', allow_duplicate=True),
    Output('viewport-store-4', 'data', allow_duplicate=True),
    Output('shared-xaxis-store', 'data', allow_duplicate=True),
    Output('cursor-info-1', 'children', allow_duplicate=True),
    Output('cursor-info-2', 'children', allow_duplicate=True),
    Output('cursor-info-3', 'children', allow_duplicate=True),
    Output('cursor-info-4', 'children', allow_duplicate=True),
    Output('graph-content-1', 'figure', allow_duplicate=True),
    Output('graph-content-2', 'figure', allow_duplicate=True),
    Output('graph-content-3', 'figure', allow_duplicate=True),
    Output('graph-content-4', 'figure', allow_duplicate=True),
    Output('status-message', 'children', allow_duplicate=True),
    Input('clear-upload-data', 'n_clicks'),
    prevent_initial_call=True
)
def clear_loaded_data(n_clicks):
    if not n_clicks:
        return no_update

    reset_datasets()
    empty_figure = create_empty_figure(False)
    reset_values = [
        None,
        None,
        [], [],
        [], [],
        [], [],
        [], [],
        [], [],
        [], [],
        [], [],
        [], [],
        False, False, False, False,
        [], None,
        [], None,
        [], None,
        [], None,
        None, None, None, None,
        None, None, None, None,
        None,
        '', '', '', '',
        empty_figure, empty_figure, empty_figure, empty_figure,
        '',
    ]
    return tuple(reset_values)


@app.callback(
    Output('secondary-axis-enabled-1', 'data'),
    Input('secondary-axis-toggle-1', 'n_clicks'),
    State('secondary-axis-enabled-1', 'data'),
    prevent_initial_call=True
)
def toggle_secondary_axis_1(n_clicks, enabled):
    return toggle_secondary_axis_state(n_clicks, enabled)


@app.callback(
    Output('secondary-axis-enabled-2', 'data'),
    Input('secondary-axis-toggle-2', 'n_clicks'),
    State('secondary-axis-enabled-2', 'data'),
    prevent_initial_call=True
)
def toggle_secondary_axis_2(n_clicks, enabled):
    return toggle_secondary_axis_state(n_clicks, enabled)


@app.callback(
    Output('secondary-axis-enabled-3', 'data'),
    Input('secondary-axis-toggle-3', 'n_clicks'),
    State('secondary-axis-enabled-3', 'data'),
    prevent_initial_call=True
)
def toggle_secondary_axis_3(n_clicks, enabled):
    return toggle_secondary_axis_state(n_clicks, enabled)


@app.callback(
    Output('secondary-axis-enabled-4', 'data'),
    Input('secondary-axis-toggle-4', 'n_clicks'),
    State('secondary-axis-enabled-4', 'data'),
    prevent_initial_call=True
)
def toggle_secondary_axis_4(n_clicks, enabled):
    return toggle_secondary_axis_state(n_clicks, enabled)


@app.callback(
    Output('secondary-axis-container-1', 'style'),
    Output('secondary-axis-toggle-1', 'children'),
    Output('secondary-axis-selection-1', 'value', allow_duplicate=True),
    Input('secondary-axis-enabled-1', 'data'),
    State('secondary-axis-selection-1', 'value'),
    prevent_initial_call=True,
)
def render_secondary_axis_1(enabled, current_value):
    return render_secondary_axis_state(enabled, current_value)


@app.callback(
    Output('secondary-axis-container-2', 'style'),
    Output('secondary-axis-toggle-2', 'children'),
    Output('secondary-axis-selection-2', 'value', allow_duplicate=True),
    Input('secondary-axis-enabled-2', 'data'),
    State('secondary-axis-selection-2', 'value'),
    prevent_initial_call=True,
)
def render_secondary_axis_2(enabled, current_value):
    return render_secondary_axis_state(enabled, current_value)


@app.callback(
    Output('secondary-axis-container-3', 'style'),
    Output('secondary-axis-toggle-3', 'children'),
    Output('secondary-axis-selection-3', 'value', allow_duplicate=True),
    Input('secondary-axis-enabled-3', 'data'),
    State('secondary-axis-selection-3', 'value'),
    prevent_initial_call=True,
)
def render_secondary_axis_3(enabled, current_value):
    return render_secondary_axis_state(enabled, current_value)


@app.callback(
    Output('secondary-axis-container-4', 'style'),
    Output('secondary-axis-toggle-4', 'children'),
    Output('secondary-axis-selection-4', 'value', allow_duplicate=True),
    Input('secondary-axis-enabled-4', 'data'),
    State('secondary-axis-selection-4', 'value'),
    prevent_initial_call=True,
)
def render_secondary_axis_4(enabled, current_value):
    return render_secondary_axis_state(enabled, current_value)


@app.callback(
    Output('file-selection-container-1', 'style'),
    Output('overlay-compare-container-1', 'style'),
    Output('overlay-compare-1', 'value'),
    Input('file-selection-1', 'options'),
    State('overlay-compare-1', 'value'),
)
def render_compare_controls_1(file_options, overlay_value):
    return render_compare_controls_state(file_options, overlay_value)


@app.callback(
    Output('file-selection-container-2', 'style'),
    Output('overlay-compare-container-2', 'style'),
    Output('overlay-compare-2', 'value'),
    Input('file-selection-2', 'options'),
    State('overlay-compare-2', 'value'),
)
def render_compare_controls_2(file_options, overlay_value):
    return render_compare_controls_state(file_options, overlay_value)


@app.callback(
    Output('file-selection-container-3', 'style'),
    Output('overlay-compare-container-3', 'style'),
    Output('overlay-compare-3', 'value'),
    Input('file-selection-3', 'options'),
    State('overlay-compare-3', 'value'),
)
def render_compare_controls_3(file_options, overlay_value):
    return render_compare_controls_state(file_options, overlay_value)


@app.callback(
    Output('file-selection-container-4', 'style'),
    Output('overlay-compare-container-4', 'style'),
    Output('overlay-compare-4', 'value'),
    Input('file-selection-4', 'options'),
    State('overlay-compare-4', 'value'),
)
def render_compare_controls_4(file_options, overlay_value):
    return render_compare_controls_state(file_options, overlay_value)


@app.callback(
    Output('fit-cursor-button-1', 'style'),
    Output('cursor-info-1', 'style'),
    Input('cursor-toggle-1', 'value'),
    Input('file-selection-1', 'value'),
)
def render_cursor_controls_1(cursor_toggle, selected_file):
    return render_cursor_controls_state(cursor_toggle, selected_file)


@app.callback(
    Output('fit-cursor-button-2', 'style'),
    Output('cursor-info-2', 'style'),
    Input('cursor-toggle-2', 'value'),
    Input('file-selection-2', 'value'),
)
def render_cursor_controls_2(cursor_toggle, selected_file):
    return render_cursor_controls_state(cursor_toggle, selected_file)


@app.callback(
    Output('fit-cursor-button-3', 'style'),
    Output('cursor-info-3', 'style'),
    Input('cursor-toggle-3', 'value'),
    Input('file-selection-3', 'value'),
)
def render_cursor_controls_3(cursor_toggle, selected_file):
    return render_cursor_controls_state(cursor_toggle, selected_file)


@app.callback(
    Output('fit-cursor-button-4', 'style'),
    Output('cursor-info-4', 'style'),
    Input('cursor-toggle-4', 'value'),
    Input('file-selection-4', 'value'),
)
def render_cursor_controls_4(cursor_toggle, selected_file):
    return render_cursor_controls_state(cursor_toggle, selected_file)


@app.callback(
    Output('graph-content-1', 'figure'),
    Input('dropdown-selection-1', 'value'),
    Input('cursor-toggle-1', 'value'),
    Input('cursor-store-1', 'data'),
    Input('file-selection-1', 'value'),
    Input('overlay-compare-1', 'value'),
    Input('secondary-axis-selection-1', 'value'),
    State('viewport-store-1', 'data'),
    State('layout-store-1', 'data'),
    State('time-axis-lock-toggle', 'value'),
    State('shared-xaxis-store', 'data'),
    prevent_initial_call=True
)
def update_graph_1(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value, viewport_data, layout_data, time_axis_lock, shared_xaxis_data):
    return update_graph_common(
        'graph-content-1',
        value,
        cursor_toggle,
        cursor_positions,
        selected_file,
        overlay_compare,
        secondary_axis_value,
        viewport_data,
        layout_data,
        time_axis_lock,
        shared_xaxis_data,
    )


@app.callback(
    Output('graph-content-2', 'figure'),
    Input('dropdown-selection-2', 'value'),
    Input('cursor-toggle-2', 'value'),
    Input('cursor-store-2', 'data'),
    Input('file-selection-2', 'value'),
    Input('overlay-compare-2', 'value'),
    Input('secondary-axis-selection-2', 'value'),
    State('viewport-store-2', 'data'),
    State('layout-store-2', 'data'),
    State('time-axis-lock-toggle', 'value'),
    State('shared-xaxis-store', 'data'),
    prevent_initial_call=True
)
def update_graph_2(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value, viewport_data, layout_data, time_axis_lock, shared_xaxis_data):
    return update_graph_common(
        'graph-content-2',
        value,
        cursor_toggle,
        cursor_positions,
        selected_file,
        overlay_compare,
        secondary_axis_value,
        viewport_data,
        layout_data,
        time_axis_lock,
        shared_xaxis_data,
    )


@app.callback(
    Output('graph-content-3', 'figure'),
    Input('dropdown-selection-3', 'value'),
    Input('cursor-toggle-3', 'value'),
    Input('cursor-store-3', 'data'),
    Input('file-selection-3', 'value'),
    Input('overlay-compare-3', 'value'),
    Input('secondary-axis-selection-3', 'value'),
    State('viewport-store-3', 'data'),
    State('layout-store-3', 'data'),
    State('time-axis-lock-toggle', 'value'),
    State('shared-xaxis-store', 'data'),
    prevent_initial_call=True
)
def update_graph_3(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value, viewport_data, layout_data, time_axis_lock, shared_xaxis_data):
    return update_graph_common(
        'graph-content-3',
        value,
        cursor_toggle,
        cursor_positions,
        selected_file,
        overlay_compare,
        secondary_axis_value,
        viewport_data,
        layout_data,
        time_axis_lock,
        shared_xaxis_data,
    )


@app.callback(
    Output('graph-content-4', 'figure'),
    Input('dropdown-selection-4', 'value'),
    Input('cursor-toggle-4', 'value'),
    Input('cursor-store-4', 'data'),
    Input('file-selection-4', 'value'),
    Input('overlay-compare-4', 'value'),
    Input('secondary-axis-selection-4', 'value'),
    State('viewport-store-4', 'data'),
    State('layout-store-4', 'data'),
    State('time-axis-lock-toggle', 'value'),
    State('shared-xaxis-store', 'data'),
    prevent_initial_call=True
)
def update_graph_4(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value, viewport_data, layout_data, time_axis_lock, shared_xaxis_data):
    return update_graph_common(
        'graph-content-4',
        value,
        cursor_toggle,
        cursor_positions,
        selected_file,
        overlay_compare,
        secondary_axis_value,
        viewport_data,
        layout_data,
        time_axis_lock,
        shared_xaxis_data,
    )


def update_graph_common(
    graph_id,
    value,
    cursor_toggle,
    cursor_positions,
    selected_file,
    overlay_compare,
    secondary_axis_value,
    viewport_data,
    layout_data,
    time_axis_lock,
    shared_xaxis_data,
):
    triggered_id = callback_context.triggered_id
    if triggered_id == graph_id.replace('graph-content', 'cursor-store'):
        return patch_cursor_shapes(cursor_toggle, cursor_positions, selected_file)

    return build_figure(
        graph_id,
        value,
        cursor_toggle,
        cursor_positions,
        selected_file,
        overlay_compare,
        secondary_axis_value,
        viewport_data,
        layout_data,
        time_axis_lock,
        shared_xaxis_data,
    )


def build_figure(
    graph_id,
    value,
    cursor_toggle,
    cursor_positions,
    selected_file,
    overlay_compare,
    secondary_axis_value,
    viewport_data,
    layout_data,
    time_axis_lock,
    shared_xaxis_data,
):
    base_file_key = get_selected_file_key(selected_file)
    active_df = get_selected_dataset(base_file_key)
    fig = figures[graph_id]
    cursor_enabled = 'show' in (cursor_toggle or [])
    overlay_enabled = 'overlay' in (overlay_compare or [])
    secondary_axis_channels = set(secondary_axis_value or [])

    empty_figure = create_empty_figure(bool(secondary_axis_channels))

    if active_df is None:
        return empty_figure

    fig.replace(go.Figure())
    if not value:
        return empty_figure

    if 'time' not in active_df.columns:
        empty_figure.update_layout(title='Selected file must contain a "time" column for plotting.')
        return empty_figure

    base_label = dataset_filenames.get(base_file_key) or base_file_key
    compare_file_key = get_compare_file_key(base_file_key) if overlay_enabled else None
    compare_df = get_selected_dataset(compare_file_key) if compare_file_key else None
    compare_label = dataset_filenames.get(compare_file_key) if compare_file_key else None
    selected_channels = get_displayed_channels(value, secondary_axis_value, active_df.columns)

    if overlay_enabled and compare_df is None:
        empty_figure.update_layout(title='Overlay compare needs 2 uploaded files.')
        return empty_figure

    for col in selected_channels:
        if col in active_df.columns:
            base_name = f'{col} ({base_label})' if overlay_enabled else col
            trace_kwargs = {}
            if col in secondary_axis_channels:
                trace_kwargs['yaxis'] = 'y2'
            base_x, base_y = get_trace_xy(active_df, col)
            if base_x is not None and base_y is not None:
                fig.add_trace(go.Scattergl(name=base_name, x=base_x, y=base_y, **trace_kwargs))
        if overlay_enabled and compare_df is not None and col in compare_df.columns and 'time' in compare_df.columns:
            trace_kwargs = {'line': {'dash': 'dot'}}
            if col in secondary_axis_channels:
                trace_kwargs['yaxis'] = 'y2'
            compare_x, compare_y = get_trace_xy(compare_df, col)
            if compare_x is not None and compare_y is not None:
                fig.add_trace(
                    go.Scattergl(
                        name=f'{col} ({compare_label})',
                        x=compare_x,
                        y=compare_y,
                        **trace_kwargs,
                    )
                )

    if cursor_enabled:
        cursor_x1, cursor_x2 = get_cursor_positions(cursor_positions, active_df)
        fig.update_layout(shapes=build_cursor_shapes(cursor_x1, cursor_x2))

    fig.update_layout(
        template='simple_white',
        hovermode='closest',
        xaxis=dict(showgrid=True, title='time'),
        yaxis=dict(showgrid=True),
        yaxis2=dict(
            showgrid=False,
            overlaying='y',
            side='right',
            showticklabels=bool(secondary_axis_channels),
            visible=bool(secondary_axis_channels),
        ),
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
    apply_layout_metadata(fig, layout_data)
    preserve_axis_ranges(fig, viewport_data)
    if 'lock' in (time_axis_lock or []):
        apply_shared_xaxis(fig, shared_xaxis_data)

    return fig


def create_empty_figure(show_secondary_axis=False):
    empty_figure = go.Figure()
    empty_figure.update_layout(
        template='simple_white',
        hovermode='closest',
        xaxis=dict(showgrid=True, title='time'),
        yaxis=dict(showgrid=True),
        yaxis2=dict(
            showgrid=False,
            overlaying='y',
            side='right',
            showticklabels=show_secondary_axis,
            visible=show_secondary_axis,
        ),
        legend=dict(
            orientation='h',
            yanchor='top',
            y=-0.2,
            xanchor='left',
            x=0,
        ),
        margin=dict(l=60, r=20, t=40, b=110),
    )
    return empty_figure


def patch_cursor_shapes(cursor_toggle, cursor_positions, selected_file):
    active_df = get_selected_dataset(selected_file)

    patched_figure = Patch()
    if 'show' not in (cursor_toggle or []):
        patched_figure['layout']['shapes'] = []
        return patched_figure

    if active_df is None or 'time' not in active_df.columns:
        patched_figure['layout']['shapes'] = []
        return patched_figure

    cursor_x1, cursor_x2 = get_cursor_positions(cursor_positions, active_df)
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
            'layer': 'above',
            'line': {'color': '#ff0000', 'width': 5},
        },
        {
            'type': 'line',
            'xref': 'x',
            'yref': 'paper',
            'x0': cursor_x2,
            'x1': cursor_x2,
            'y0': 0,
            'y1': 1,
            'layer': 'above',
            'line': {'color': '#0057ff', 'width': 5},
        },
    ]


for graph_id, figure in figures.items():
    figure.register_update_graph_callback(app=app, graph_id=graph_id)


EXPORT_CLIENTSIDE_FUNCTION = """
function(payload) {
  if (!payload) {
    return window.dash_clientside.no_update;
  }

  function ensureCsvExtension(filename) {
    if (!filename) {
      return "export.csv";
    }
    return filename.toLowerCase().endsWith(".csv") ? filename : filename + ".csv";
  }

  var files = Array.isArray(payload.files) ? payload.files : [payload];

  for (var i = 0; i < files.length; i++) {
    var filePayload = files[i];
    var suggestedName = filePayload.filename || "export.csv";
    var enteredName = window.prompt("Enter export filename", suggestedName);
    if (enteredName === null) {
      return window.dash_clientside.no_update;
    }

    var finalName = ensureCsvExtension((enteredName || "").trim() || suggestedName);
    var blob = new Blob([filePayload.content], {
      type: filePayload.mime_type || "text/csv"
    });

    var url = URL.createObjectURL(blob);
    var anchor = document.createElement("a");
    anchor.href = url;
    anchor.download = finalName;
    document.body.appendChild(anchor);
    anchor.click();
    anchor.remove();
    setTimeout(function(currentUrl) {
      URL.revokeObjectURL(currentUrl);
    }, 0, url);
  }

  return window.dash_clientside.no_update;
}
"""

app.clientside_callback(
    EXPORT_CLIENTSIDE_FUNCTION,
    Output('export-save-trigger-1', 'children'),
    Input('export-payload-1', 'data'),
    prevent_initial_call=True,
)

app.clientside_callback(
    EXPORT_CLIENTSIDE_FUNCTION,
    Output('export-save-trigger-2', 'children'),
    Input('export-payload-2', 'data'),
    prevent_initial_call=True,
)

app.clientside_callback(
    EXPORT_CLIENTSIDE_FUNCTION,
    Output('export-save-trigger-3', 'children'),
    Input('export-payload-3', 'data'),
    prevent_initial_call=True,
)

app.clientside_callback(
    EXPORT_CLIENTSIDE_FUNCTION,
    Output('export-save-trigger-4', 'children'),
    Input('export-payload-4', 'data'),
    prevent_initial_call=True,
)


@app.callback(
    Output('cursor-store-1', 'data'),
    Input('graph-content-1', 'relayoutData'),
    State('cursor-store-1', 'data'),
    State('file-selection-1', 'value'),
    State('cursor-toggle-1', 'value'),
    prevent_initial_call=True
)
def update_cursor_store_1(relayout_data, cursor_positions, selected_file, cursor_toggle):
    return extract_cursor_positions(relayout_data, cursor_positions, selected_file, cursor_toggle)


@app.callback(
    Output('cursor-store-2', 'data'),
    Input('graph-content-2', 'relayoutData'),
    State('cursor-store-2', 'data'),
    State('file-selection-2', 'value'),
    State('cursor-toggle-2', 'value'),
    prevent_initial_call=True
)
def update_cursor_store_2(relayout_data, cursor_positions, selected_file, cursor_toggle):
    return extract_cursor_positions(relayout_data, cursor_positions, selected_file, cursor_toggle)


@app.callback(
    Output('cursor-store-3', 'data'),
    Input('graph-content-3', 'relayoutData'),
    State('cursor-store-3', 'data'),
    State('file-selection-3', 'value'),
    State('cursor-toggle-3', 'value'),
    prevent_initial_call=True
)
def update_cursor_store_3(relayout_data, cursor_positions, selected_file, cursor_toggle):
    return extract_cursor_positions(relayout_data, cursor_positions, selected_file, cursor_toggle)


@app.callback(
    Output('cursor-store-4', 'data'),
    Input('graph-content-4', 'relayoutData'),
    State('cursor-store-4', 'data'),
    State('file-selection-4', 'value'),
    State('cursor-toggle-4', 'value'),
    prevent_initial_call=True
)
def update_cursor_store_4(relayout_data, cursor_positions, selected_file, cursor_toggle):
    return extract_cursor_positions(relayout_data, cursor_positions, selected_file, cursor_toggle)


@app.callback(
    Output('viewport-store-1', 'data'),
    Input('graph-content-1', 'relayoutData'),
    State('viewport-store-1', 'data'),
    prevent_initial_call=True
)
def update_viewport_store_1(relayout_data, viewport_data):
    return extract_viewport_data(relayout_data, viewport_data)


@app.callback(
    Output('layout-store-1', 'data'),
    Input('graph-content-1', 'relayoutData'),
    State('layout-store-1', 'data'),
    prevent_initial_call=True
)
def update_layout_store_1(relayout_data, layout_data):
    return extract_layout_metadata(relayout_data, layout_data)


@app.callback(
    Output('viewport-store-2', 'data'),
    Input('graph-content-2', 'relayoutData'),
    State('viewport-store-2', 'data'),
    prevent_initial_call=True
)
def update_viewport_store_2(relayout_data, viewport_data):
    return extract_viewport_data(relayout_data, viewport_data)


@app.callback(
    Output('layout-store-2', 'data'),
    Input('graph-content-2', 'relayoutData'),
    State('layout-store-2', 'data'),
    prevent_initial_call=True
)
def update_layout_store_2(relayout_data, layout_data):
    return extract_layout_metadata(relayout_data, layout_data)


@app.callback(
    Output('viewport-store-3', 'data'),
    Input('graph-content-3', 'relayoutData'),
    State('viewport-store-3', 'data'),
    prevent_initial_call=True
)
def update_viewport_store_3(relayout_data, viewport_data):
    return extract_viewport_data(relayout_data, viewport_data)


@app.callback(
    Output('layout-store-3', 'data'),
    Input('graph-content-3', 'relayoutData'),
    State('layout-store-3', 'data'),
    prevent_initial_call=True
)
def update_layout_store_3(relayout_data, layout_data):
    return extract_layout_metadata(relayout_data, layout_data)


@app.callback(
    Output('viewport-store-4', 'data'),
    Input('graph-content-4', 'relayoutData'),
    State('viewport-store-4', 'data'),
    prevent_initial_call=True
)
def update_viewport_store_4(relayout_data, viewport_data):
    return extract_viewport_data(relayout_data, viewport_data)


@app.callback(
    Output('layout-store-4', 'data'),
    Input('graph-content-4', 'relayoutData'),
    State('layout-store-4', 'data'),
    prevent_initial_call=True
)
def update_layout_store_4(relayout_data, layout_data):
    return extract_layout_metadata(relayout_data, layout_data)


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
    Input('file-selection-1', 'value'),
    Input('overlay-compare-1', 'value'),
    Input('secondary-axis-selection-1', 'value'),
    prevent_initial_call=True
)
def update_cursor_info_1(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value):
    return build_cursor_info(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value)


@app.callback(
    Output('cursor-info-2', 'children'),
    Input('dropdown-selection-2', 'value'),
    Input('cursor-toggle-2', 'value'),
    Input('cursor-store-2', 'data'),
    Input('file-selection-2', 'value'),
    Input('overlay-compare-2', 'value'),
    Input('secondary-axis-selection-2', 'value'),
    prevent_initial_call=True
)
def update_cursor_info_2(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value):
    return build_cursor_info(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value)


@app.callback(
    Output('cursor-info-3', 'children'),
    Input('dropdown-selection-3', 'value'),
    Input('cursor-toggle-3', 'value'),
    Input('cursor-store-3', 'data'),
    Input('file-selection-3', 'value'),
    Input('overlay-compare-3', 'value'),
    Input('secondary-axis-selection-3', 'value'),
    prevent_initial_call=True
)
def update_cursor_info_3(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value):
    return build_cursor_info(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value)


@app.callback(
    Output('cursor-info-4', 'children'),
    Input('dropdown-selection-4', 'value'),
    Input('cursor-toggle-4', 'value'),
    Input('cursor-store-4', 'data'),
    Input('file-selection-4', 'value'),
    Input('overlay-compare-4', 'value'),
    Input('secondary-axis-selection-4', 'value'),
    prevent_initial_call=True
)
def update_cursor_info_4(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value):
    return build_cursor_info(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value)


@app.callback(
    Output('graph-content-1', 'figure', allow_duplicate=True),
    Output('viewport-store-1', 'data', allow_duplicate=True),
    Output('shared-xaxis-store', 'data', allow_duplicate=True),
    Input('fit-cursor-button-1', 'n_clicks'),
    State('cursor-toggle-1', 'value'),
    State('cursor-store-1', 'data'),
    State('file-selection-1', 'value'),
    State('time-axis-lock-toggle', 'value'),
    prevent_initial_call=True,
)
def fit_cursor_into_plot_1(n_clicks, cursor_toggle, cursor_positions, selected_file, time_axis_lock):
    return fit_cursor_into_plot(n_clicks, cursor_toggle, cursor_positions, selected_file, time_axis_lock)


@app.callback(
    Output('graph-content-2', 'figure', allow_duplicate=True),
    Output('viewport-store-2', 'data', allow_duplicate=True),
    Output('shared-xaxis-store', 'data', allow_duplicate=True),
    Input('fit-cursor-button-2', 'n_clicks'),
    State('cursor-toggle-2', 'value'),
    State('cursor-store-2', 'data'),
    State('file-selection-2', 'value'),
    State('time-axis-lock-toggle', 'value'),
    prevent_initial_call=True,
)
def fit_cursor_into_plot_2(n_clicks, cursor_toggle, cursor_positions, selected_file, time_axis_lock):
    return fit_cursor_into_plot(n_clicks, cursor_toggle, cursor_positions, selected_file, time_axis_lock)


@app.callback(
    Output('graph-content-3', 'figure', allow_duplicate=True),
    Output('viewport-store-3', 'data', allow_duplicate=True),
    Output('shared-xaxis-store', 'data', allow_duplicate=True),
    Input('fit-cursor-button-3', 'n_clicks'),
    State('cursor-toggle-3', 'value'),
    State('cursor-store-3', 'data'),
    State('file-selection-3', 'value'),
    State('time-axis-lock-toggle', 'value'),
    prevent_initial_call=True,
)
def fit_cursor_into_plot_3(n_clicks, cursor_toggle, cursor_positions, selected_file, time_axis_lock):
    return fit_cursor_into_plot(n_clicks, cursor_toggle, cursor_positions, selected_file, time_axis_lock)


@app.callback(
    Output('graph-content-4', 'figure', allow_duplicate=True),
    Output('viewport-store-4', 'data', allow_duplicate=True),
    Output('shared-xaxis-store', 'data', allow_duplicate=True),
    Input('fit-cursor-button-4', 'n_clicks'),
    State('cursor-toggle-4', 'value'),
    State('cursor-store-4', 'data'),
    State('file-selection-4', 'value'),
    State('time-axis-lock-toggle', 'value'),
    prevent_initial_call=True,
)
def fit_cursor_into_plot_4(n_clicks, cursor_toggle, cursor_positions, selected_file, time_axis_lock):
    return fit_cursor_into_plot(n_clicks, cursor_toggle, cursor_positions, selected_file, time_axis_lock)


@app.callback(
    Output('export-payload-1', 'data'),
    Output('export-warning-1', 'displayed'),
    Output('export-warning-1', 'message'),
    Input('export-button-1', 'n_clicks'),
    State('dropdown-selection-1', 'value'),
    State('cursor-toggle-1', 'value'),
    State('cursor-store-1', 'data'),
    State('export-relative-time-1', 'value'),
    State('file-selection-1', 'value'),
    State('overlay-compare-1', 'value'),
    State('secondary-axis-selection-1', 'value'),
    State('graph-content-1', 'figure'),
    prevent_initial_call=True
)
def export_data_1(n_clicks, value, cursor_toggle, cursor_positions, relative_time, selected_file, overlay_compare, secondary_axis_value, figure_state):
    return export_plot_data(n_clicks, value, cursor_toggle, cursor_positions, relative_time, 1, selected_file, overlay_compare, secondary_axis_value, figure_state)


@app.callback(
    Output('export-payload-2', 'data'),
    Output('export-warning-2', 'displayed'),
    Output('export-warning-2', 'message'),
    Input('export-button-2', 'n_clicks'),
    State('dropdown-selection-2', 'value'),
    State('cursor-toggle-2', 'value'),
    State('cursor-store-2', 'data'),
    State('export-relative-time-2', 'value'),
    State('file-selection-2', 'value'),
    State('overlay-compare-2', 'value'),
    State('secondary-axis-selection-2', 'value'),
    State('graph-content-2', 'figure'),
    prevent_initial_call=True
)
def export_data_2(n_clicks, value, cursor_toggle, cursor_positions, relative_time, selected_file, overlay_compare, secondary_axis_value, figure_state):
    return export_plot_data(n_clicks, value, cursor_toggle, cursor_positions, relative_time, 2, selected_file, overlay_compare, secondary_axis_value, figure_state)


@app.callback(
    Output('export-payload-3', 'data'),
    Output('export-warning-3', 'displayed'),
    Output('export-warning-3', 'message'),
    Input('export-button-3', 'n_clicks'),
    State('dropdown-selection-3', 'value'),
    State('cursor-toggle-3', 'value'),
    State('cursor-store-3', 'data'),
    State('export-relative-time-3', 'value'),
    State('file-selection-3', 'value'),
    State('overlay-compare-3', 'value'),
    State('secondary-axis-selection-3', 'value'),
    State('graph-content-3', 'figure'),
    prevent_initial_call=True
)
def export_data_3(n_clicks, value, cursor_toggle, cursor_positions, relative_time, selected_file, overlay_compare, secondary_axis_value, figure_state):
    return export_plot_data(n_clicks, value, cursor_toggle, cursor_positions, relative_time, 3, selected_file, overlay_compare, secondary_axis_value, figure_state)


@app.callback(
    Output('export-payload-4', 'data'),
    Output('export-warning-4', 'displayed'),
    Output('export-warning-4', 'message'),
    Input('export-button-4', 'n_clicks'),
    State('dropdown-selection-4', 'value'),
    State('cursor-toggle-4', 'value'),
    State('cursor-store-4', 'data'),
    State('export-relative-time-4', 'value'),
    State('file-selection-4', 'value'),
    State('overlay-compare-4', 'value'),
    State('secondary-axis-selection-4', 'value'),
    State('graph-content-4', 'figure'),
    prevent_initial_call=True
)
def export_data_4(n_clicks, value, cursor_toggle, cursor_positions, relative_time, selected_file, overlay_compare, secondary_axis_value, figure_state):
    return export_plot_data(n_clicks, value, cursor_toggle, cursor_positions, relative_time, 4, selected_file, overlay_compare, secondary_axis_value, figure_state)


def extract_cursor_positions(relayout_data, cursor_positions, selected_file, cursor_toggle):
    active_df = get_selected_dataset(selected_file)
    if (
        not relayout_data
        or 'show' not in (cursor_toggle or [])
        or active_df is None
        or 'time' not in active_df.columns
    ):
        return no_update

    current_positions = get_cursor_positions(cursor_positions, active_df)
    if current_positions == (None, None):
        return no_update

    updated_positions = list(current_positions)
    found_cursor_update = False

    for index in range(2):
        x0_key = f'shapes[{index}].x0'
        x1_key = f'shapes[{index}].x1'
        if x0_key in relayout_data:
            updated_positions[index] = snap_cursor_to_time(relayout_data[x0_key], active_df)
            found_cursor_update = True
        elif x1_key in relayout_data:
            updated_positions[index] = snap_cursor_to_time(relayout_data[x1_key], active_df)
            found_cursor_update = True

    if 'shapes' in relayout_data and len(relayout_data['shapes']) >= 2:
        updated_positions = [
            snap_cursor_to_time(relayout_data['shapes'][0].get('x0', updated_positions[0]), active_df),
            snap_cursor_to_time(relayout_data['shapes'][1].get('x0', updated_positions[1]), active_df),
        ]
        found_cursor_update = True

    if not found_cursor_update:
        viewport_positions = cursor_positions_for_viewport(relayout_data, active_df)
        if viewport_positions is None or tuple(viewport_positions) == tuple(current_positions):
            return no_update
        return viewport_positions

    return updated_positions


def cursor_positions_for_viewport(relayout_data, active_df):
    if relayout_data.get('xaxis.autorange'):
        return default_cursor_positions(active_df)

    if 'xaxis.range[0]' in relayout_data and 'xaxis.range[1]' in relayout_data:
        range_start = relayout_data['xaxis.range[0]']
        range_stop = relayout_data['xaxis.range[1]']
    elif 'xaxis.range' in relayout_data and len(relayout_data['xaxis.range']) >= 2:
        range_start = relayout_data['xaxis.range'][0]
        range_stop = relayout_data['xaxis.range'][1]
    else:
        return None

    if range_start is None or range_stop is None:
        return None

    visible_start = snap_cursor_to_time(min(range_start, range_stop), active_df)
    visible_stop = snap_cursor_to_time(max(range_start, range_stop), active_df)
    if visible_start is None or visible_stop is None:
        return None

    span = visible_stop - visible_start
    return [
        snap_cursor_to_time(visible_start + 0.25 * span, active_df),
        snap_cursor_to_time(visible_start + 0.75 * span, active_df),
    ]


def build_cursor_info(value, cursor_toggle, cursor_positions, selected_file, overlay_compare, secondary_axis_value):
    base_file_key = get_selected_file_key(selected_file)
    active_df = datasets.get(base_file_key)
    overlay_enabled = 'overlay' in (overlay_compare or [])
    secondary_axis_channels = set(secondary_axis_value or [])

    if active_df is None or 'show' not in (cursor_toggle or []):
        return ''

    if 'time' not in active_df.columns:
        return 'Cursors require a "time" column.'

    selected_channels = get_displayed_channels(value, secondary_axis_value, active_df.columns)
    if not selected_channels:
        return 'Select at least one channel to show cursor values.'

    cursor_x1, cursor_x2 = get_cursor_positions(cursor_positions, active_df)
    index_1 = nearest_time_index(cursor_x1, active_df)
    index_2 = nearest_time_index(cursor_x2, active_df)
    time_1 = active_df["time"].iloc[index_1]
    time_2 = active_df["time"].iloc[index_2]
    start_time, end_time = sorted((time_1, time_2))

    lines = [
        f'Cursor A: x={format_value(time_1)}',
        f'Cursor B: x={format_value(time_2)}',
        f'Start time: {format_value(start_time)}',
        f'End time: {format_value(end_time)}',
        f'Delta X: {format_value(time_2 - time_1)}',
    ]

    compare_file_key = get_compare_file_key(base_file_key) if overlay_enabled else None
    compare_df = datasets.get(compare_file_key) if compare_file_key else None
    base_label = dataset_filenames.get(base_file_key) or base_file_key
    compare_label = dataset_filenames.get(compare_file_key) if compare_file_key else None

    if overlay_enabled:
        lines.append(f'Base file: {base_label}')
        if compare_df is None:
            lines.append('Overlay compare needs 2 uploaded files.')

    for col in selected_channels:
        y1 = active_df[col].iloc[index_1]
        y2 = active_df[col].iloc[index_2]
        if overlay_enabled:
            lines.append(
                f'{col} [{axis_label(col, secondary_axis_channels)}] ({base_label}): A={format_value(y1)}, B={format_value(y2)}, Delta={format_value(y2 - y1)}'
            )
        else:
            lines.append(
                f'{col} [{axis_label(col, secondary_axis_channels)}]: A={format_value(y1)}, B={format_value(y2)}, Delta={format_value(y2 - y1)}'
            )

        if overlay_enabled and compare_df is not None and col in compare_df.columns and 'time' in compare_df.columns:
            compare_index_1 = nearest_time_index(cursor_x1, compare_df)
            compare_index_2 = nearest_time_index(cursor_x2, compare_df)
            compare_y1 = compare_df[col].iloc[compare_index_1]
            compare_y2 = compare_df[col].iloc[compare_index_2]
            lines.append(
                f'{col} [{axis_label(col, secondary_axis_channels)}] ({compare_label}): A={format_value(compare_y1)}, B={format_value(compare_y2)}, Delta={format_value(compare_y2 - compare_y1)}'
            )

    return '\n'.join(lines)


def get_cursor_positions(cursor_positions, active_df):
    if cursor_positions and len(cursor_positions) == 2:
        return cursor_positions[0], cursor_positions[1]

    return default_cursor_positions(active_df)


def default_cursor_positions(active_df):
    if active_df is None or 'time' not in active_df.columns or active_df.empty:
        return None, None

    time_series = active_df['time']
    start = time_series.iloc[0]
    stop = time_series.iloc[-1]
    span = stop - start
    return start + 0.25 * span, start + 0.75 * span


def nearest_time_index(cursor_x, active_df):
    return (active_df['time'] - cursor_x).abs().idxmin()


def snap_cursor_to_time(cursor_x, active_df):
    if cursor_x is None:
        return None
    return active_df['time'].iloc[nearest_time_index(cursor_x, active_df)]


def format_value(value):
    if isinstance(value, float):
        return f'{value:.6g}'
    return str(value)


def export_plot_data(n_clicks, value, cursor_toggle, cursor_positions, relative_time, graph_index, selected_file, overlay_compare, secondary_axis_value, figure_state=None):
    selected_file_key = get_selected_file_key(selected_file)
    active_df = datasets.get(selected_file_key)
    overlay_enabled = 'overlay' in (overlay_compare or [])

    if not n_clicks or active_df is None or 'time' not in active_df.columns:
        return no_update, False, 'Enable cursors first!'

    if 'show' not in (cursor_toggle or []):
        return no_update, True, 'Enable cursors first!'

    selected_channels = get_displayed_channels(value, secondary_axis_value, active_df.columns)
    if not selected_channels:
        return no_update, True, 'Select at least one channel to export.'

    cursor_x1, cursor_x2 = get_cursor_positions(cursor_positions, active_df)
    if cursor_x1 is None or cursor_x2 is None:
        return no_update, True, 'Enable cursors first!'

    start_time, stop_time = sorted((cursor_x1, cursor_x2))
    export_df = active_df.loc[
        (active_df['time'] >= start_time) & (active_df['time'] <= stop_time),
        ['time', *selected_channels],
    ].copy()
    if export_df is None:
        return no_update, True, 'No data points found between the cursors.'
    if export_df.empty:
        return no_update, True, 'No data points found between the cursors.'

    if 'relative' in (relative_time or []):
        export_df['time'] = export_df['time'] - export_df['time'].iloc[0]

    export_df['time'] = export_df['time'].round(12)
    compare_file_key = get_compare_file_key(selected_file_key) if overlay_enabled else None
    metadata_prefix = build_log_metadata_prefix(figure_state, selected_file_key, compare_file_key)

    filename_suffix = build_export_timestamp_suffix(start_time, stop_time, 'relative' in (relative_time or []))
    file_suffix = selected_file_key if selected_file_key in {'file1', 'file2'} else 'file1'
    export_name = get_export_name(figure_state, f'graph_{graph_index}_{file_suffix}')
    export_files = [{
        'content': metadata_prefix + export_df.to_csv(index=False),
        'filename': f'{export_name}_{filename_suffix}.csv',
        'mime_type': 'text/csv',
        'request_id': f'{graph_index}_{n_clicks}_base',
    }]

    if overlay_enabled:
        compare_df = datasets.get(compare_file_key) if compare_file_key else None
        if compare_df is None or 'time' not in compare_df.columns:
            return no_update, True, 'Overlay export needs 2 uploaded files.'

        compare_export_df = compare_df.loc[
            (compare_df['time'] >= start_time) & (compare_df['time'] <= stop_time),
            ['time', *selected_channels],
        ].copy()
        if compare_export_df is not None and not compare_export_df.empty:
            if 'relative' in (relative_time or []):
                compare_export_df['time'] = compare_export_df['time'] - compare_export_df['time'].iloc[0]
            compare_export_df['time'] = compare_export_df['time'].round(12)
            compare_file_suffix = compare_file_key if compare_file_key in {'file1', 'file2'} else 'file1'
            compare_export_name = get_export_name(figure_state, f'graph_{graph_index}_{compare_file_suffix}', compare_file_suffix)
            export_files.append({
                'content': metadata_prefix + compare_export_df.to_csv(index=False),
                'filename': f'{compare_export_name}_{filename_suffix}.csv',
                'mime_type': 'text/csv',
                'request_id': f'{graph_index}_{n_clicks}_{compare_file_suffix}',
            })

    export_payload = export_files[0] if len(export_files) == 1 else {'files': export_files, 'request_id': f'{graph_index}_{n_clicks}_multi'}
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

    if viewport_data.get('yaxis2.autorange'):
        fig.update_layout(yaxis2=dict(autorange=True))
    elif 'yaxis2.range[0]' in viewport_data and 'yaxis2.range[1]' in viewport_data:
        fig.update_layout(yaxis2=dict(range=[viewport_data['yaxis2.range[0]'], viewport_data['yaxis2.range[1]']]))


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

    if 'shapes' in relayout_data or any(key.startswith('shapes[') for key in relayout_data):
        return no_update

    updated_viewport = dict(viewport_data or {})
    found_viewport_update = False
    range_updated = False

    for key in (
        'xaxis.range[0]',
        'xaxis.range[1]',
        'yaxis.range[0]',
        'yaxis.range[1]',
        'yaxis2.range[0]',
        'yaxis2.range[1]',
    ):
        if key in relayout_data:
            updated_viewport[key] = relayout_data[key]
            found_viewport_update = True
            range_updated = True

    if range_updated:
        updated_viewport['xaxis.autorange'] = False
        updated_viewport['yaxis.autorange'] = False
        if 'yaxis2.range[0]' in updated_viewport and 'yaxis2.range[1]' in updated_viewport:
            updated_viewport['yaxis2.autorange'] = False

    for key in ('xaxis.autorange', 'yaxis.autorange', 'yaxis2.autorange'):
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


def extract_layout_metadata(relayout_data, layout_data):
    if not relayout_data:
        return no_update

    updated_layout = dict(layout_data or {})
    found_layout_update = False
    for key in ('title.text', 'title.subtitle.text', 'xaxis.title.text', 'yaxis.title.text', 'yaxis2.title.text'):
        if key in relayout_data:
            updated_layout[key] = relayout_data[key]
            found_layout_update = True

    if not found_layout_update:
        return no_update

    return updated_layout


def apply_layout_metadata(fig, layout_data):
    if not layout_data:
        return

    if 'title.text' in layout_data:
        title_layout = {'text': layout_data['title.text']}
        if 'title.subtitle.text' in layout_data:
            title_layout['subtitle'] = {'text': layout_data['title.subtitle.text']}
        fig.update_layout(title=title_layout)
    elif 'title.subtitle.text' in layout_data:
        fig.update_layout(title={'subtitle': {'text': layout_data['title.subtitle.text']}})
    if 'xaxis.title.text' in layout_data:
        fig.update_xaxes(title=layout_data['xaxis.title.text'])
    if 'yaxis.title.text' in layout_data:
        fig.update_yaxes(title=layout_data['yaxis.title.text'])
    if 'yaxis2.title.text' in layout_data:
        fig.update_layout(yaxis2=dict(title=layout_data['yaxis2.title.text']))


def get_export_name(figure_state, fallback_name, compare_suffix=None):
    title_text = extract_figure_title(figure_state)
    if title_text:
        sanitized_title = sanitize_filename_part(title_text)
        if sanitized_title:
            if compare_suffix:
                return f'{sanitized_title}_{compare_suffix}'
            return sanitized_title
    return fallback_name


def build_log_metadata_prefix(figure_state, selected_file_key=None, compare_file_key=None):
    title_text, subtitle_text = extract_figure_title_parts(figure_state)
    metadata_lines = []
    original_logfile = dataset_filenames.get(selected_file_key) if selected_file_key else None
    compare_logfile = dataset_filenames.get(compare_file_key) if compare_file_key else None
    if title_text or subtitle_text or original_logfile or compare_logfile:
        metadata_lines.append('# Export metadata')
    if title_text:
        metadata_lines.append(f'# Title: {title_text}')
    if subtitle_text:
        metadata_lines.append(f'# Subtitle: {subtitle_text}')
    if original_logfile:
        metadata_lines.append(f'# Original log file: {original_logfile}')
    if compare_logfile:
        metadata_lines.append(f'# Compare log file: {compare_logfile}')
    if not metadata_lines:
        return ''
    return '\n'.join(metadata_lines) + '\n#\n'


def build_export_timestamp_suffix(start_time, stop_time, relative_time_enabled):
    if relative_time_enabled:
        return f't_{sanitize_filename_part(format_timestamp_for_filename(stop_time - start_time))}'
    return (
        f't_{sanitize_filename_part(format_timestamp_for_filename(start_time))}'
        f'_to_{sanitize_filename_part(format_timestamp_for_filename(stop_time))}'
    )


def format_timestamp_for_filename(value):
    if isinstance(value, pd.Timestamp):
        return value.strftime('%Y%m%d_%H%M%S_%f').rstrip('0').rstrip('_')
    if hasattr(value, 'isoformat'):
        try:
            return value.isoformat()
        except TypeError:
            pass
    if isinstance(value, float):
        return f'{value:.6g}'
    return str(value)


def extract_figure_title(figure_state):
    title_text, _ = extract_figure_title_parts(figure_state)
    return title_text


def extract_figure_title_parts(figure_state):
    if not isinstance(figure_state, dict):
        return None, None

    layout = figure_state.get('layout')
    if not isinstance(layout, dict):
        return None, None

    title = layout.get('title')
    if isinstance(title, dict):
        title_value = title.get('text')
        subtitle_value = None
        subtitle = title.get('subtitle')
        if isinstance(subtitle, dict):
            subtitle_value = subtitle.get('text')
        elif isinstance(subtitle, str):
            subtitle_value = subtitle
    elif isinstance(title, str):
        title_value = title
        subtitle_value = None
    else:
        title_value = None
        subtitle_value = None

    if not title_value and not subtitle_value:
        return None, None

    split_title = re.split(r'<br\s*/?>', str(title_value), maxsplit=1, flags=re.IGNORECASE) if title_value else []
    main_title = strip_html_tags(split_title[0]).strip() if split_title else None
    subtitle_text = strip_html_tags(subtitle_value).strip() if subtitle_value else None
    if not subtitle_text and len(split_title) > 1:
        subtitle_text = strip_html_tags(split_title[1]).strip()
    subtitle_text = re.sub(r'^\s*Subtitle:\s*', '', subtitle_text, flags=re.IGNORECASE) if subtitle_text else None
    subtitle_text = subtitle_text or None

    return main_title or None, subtitle_text


def strip_html_tags(value):
    return re.sub(r'<[^>]+>', '', value or '')


def sanitize_filename_part(value):
    if value is None:
        return None

    sanitized = re.sub(r'\s+', '_', str(value).strip())
    sanitized = re.sub(r'[^A-Za-z0-9._-]', '_', sanitized)
    sanitized = re.sub(r'_+', '_', sanitized).strip('._-')
    return sanitized or None


def get_displayed_channels(primary_value, secondary_axis_value, available_columns):
    ordered_channels = []
    for col in (primary_value or []) + (secondary_axis_value or []):
        if col in available_columns and col not in ordered_channels and col != 'time':
            ordered_channels.append(col)
    return ordered_channels


def axis_label(col, secondary_axis_channels):
    return 'Y2' if col in secondary_axis_channels else 'Y1'


def toggle_secondary_axis_state(n_clicks, enabled):
    if not n_clicks:
        return enabled
    return not bool(enabled)


def render_secondary_axis_state(enabled, current_value):
    if enabled:
        return {'display': 'block'}, 'Disable second axis', current_value or []
    return {'display': 'none'}, 'Enable second axis', []


def render_compare_controls_state(file_options, overlay_value):
    has_multiple_files = len(file_options or []) > 1
    visible_style = {'display': 'block'}
    hidden_style = {'display': 'none'}
    if has_multiple_files:
        return visible_style, visible_style, overlay_value or []
    return hidden_style, hidden_style, []


def render_cursor_controls_state(cursor_toggle, selected_file):
    active_df = get_selected_dataset(selected_file)
    cursor_enabled = (
        'show' in (cursor_toggle or [])
        and active_df is not None
        and 'time' in active_df.columns
        and not active_df.empty
    )

    button_style = {
        'backgroundColor': '#f3f4f6',
        'color': '#222222',
        'border': '1px solid #c7c9cc',
        'padding': '8px 16px',
        'fontSize': '14px',
        'cursor': 'pointer',
        'borderRadius': '5px',
        'marginRight': '16px',
        'display': 'inline-block' if cursor_enabled else 'none',
    }
    info_style = {
        'marginTop': '10px',
        'fontFamily': 'monospace',
        'fontSize': '14px',
        'whiteSpace': 'pre-wrap',
        'display': 'block' if cursor_enabled else 'none',
    }
    return button_style, info_style


def fit_cursor_into_plot(n_clicks, cursor_toggle, cursor_positions, selected_file, time_axis_lock):
    active_df = get_selected_dataset(selected_file)
    if (
        not n_clicks
        or 'show' not in (cursor_toggle or [])
        or active_df is None
        or 'time' not in active_df.columns
        or active_df.empty
    ):
        return no_update, no_update, no_update

    cursor_x1, cursor_x2 = get_cursor_positions(cursor_positions, active_df)
    if cursor_x1 is None or cursor_x2 is None:
        return no_update, no_update, no_update

    start_time, stop_time = sorted((cursor_x1, cursor_x2))
    span = stop_time - start_time
    padding = span * 0.05 if span else default_cursor_padding(active_df)
    viewport_data = {
        'xaxis.range[0]': start_time - padding,
        'xaxis.range[1]': stop_time + padding,
        'xaxis.autorange': False,
    }

    patch = Patch()
    patch['layout']['xaxis']['autorange'] = False
    patch['layout']['xaxis']['range'] = [
        viewport_data['xaxis.range[0]'],
        viewport_data['xaxis.range[1]'],
    ]

    shared_xaxis_data = viewport_data if 'lock' in (time_axis_lock or []) else no_update
    return patch, viewport_data, shared_xaxis_data


def default_cursor_padding(active_df):
    if active_df is None or 'time' not in active_df.columns or active_df.empty:
        return 0

    time_series = active_df['time']
    span = time_series.iloc[-1] - time_series.iloc[0]
    if span:
        return span * 0.02

    if len(time_series) > 1:
        step = abs(time_series.iloc[1] - time_series.iloc[0])
        if step:
            return step

    return 1


def channel_sort_key(channel_name):
    match = re.fullmatch(r'([A-Za-z_]+)(\d+)', channel_name)
    if match:
        prefix, number = match.groups()
        return (prefix.lower(), int(number), channel_name.lower())
    return (channel_name.lower(), -1, channel_name.lower())


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
            loaded_df = pd.read_parquet(io.BytesIO(decoded))
        else:
            loaded_df = pd.read_csv(io.StringIO(decoded.decode('utf-8')), sep=';')
    except UnicodeDecodeError:
        return None, 'The CSV file must be UTF-8 encoded.'
    except Exception as exc:
        return None, f'Failed to read "{filename}": {exc}'

    if loaded_df.empty:
        return None, f'"{filename}" does not contain any rows.'

    if len(loaded_df.columns) == 0:
        return None, f'"{filename}" does not contain any columns.'

    loaded_df = normalize_time_dataframe(loaded_df)

    return loaded_df, None


def get_file_extension(filename):
    parts = filename.split('.')
    if len(parts) == 1:
        return None

    return parts[-1].lower()


def reset_datasets():
    datasets['file1'] = None
    datasets['file2'] = None
    dataset_filenames['file1'] = None
    dataset_filenames['file2'] = None


def get_selected_dataset(selected_file):
    selected_key = get_selected_file_key(selected_file)
    if selected_key is None:
        return None
    return datasets[selected_key]


def get_selected_file_key(selected_file):
    if selected_file in datasets and datasets[selected_file] is not None:
        return selected_file

    for file_key in ('file1', 'file2'):
        if datasets[file_key] is not None:
            return file_key

    return None


def get_compare_file_key(base_file_key):
    if base_file_key == 'file1' and datasets['file2'] is not None:
        return 'file2'
    if base_file_key == 'file2' and datasets['file1'] is not None:
        return 'file1'
    return None


def normalize_time_dataframe(dataframe):
    if dataframe is None or 'time' not in dataframe.columns:
        return dataframe

    time_series = dataframe['time']
    if (
        time_series.notna().all()
        and (pd.api.types.is_numeric_dtype(time_series) or pd.api.types.is_datetime64_any_dtype(time_series))
        and time_series.is_monotonic_increasing
    ):
        return dataframe.reset_index(drop=True) if not dataframe.index.equals(pd.RangeIndex(len(dataframe))) else dataframe

    normalized_df = dataframe.copy()
    time_series = normalized_df['time']

    numeric_time = pd.to_numeric(time_series, errors='coerce')
    if numeric_time.notna().all():
        normalized_time = numeric_time
    else:
        datetime_time = pd.to_datetime(time_series, errors='coerce')
        if datetime_time.notna().all():
            normalized_time = datetime_time
        else:
            normalized_time = time_series

    normalized_df['time'] = normalized_time
    normalized_df = normalized_df.loc[normalized_df['time'].notna()].copy()
    if normalized_df.empty:
        return normalized_df

    normalized_df = normalized_df.sort_values(by='time', kind='stable').reset_index(drop=True)
    return normalized_df


def get_trace_xy(dataframe, column_name):
    if dataframe is None or 'time' not in dataframe.columns or column_name not in dataframe.columns:
        return None, None

    if dataframe.empty:
        return None, None

    valid_rows = dataframe['time'].notna()
    if not valid_rows.all():
        trace_x = dataframe.loc[valid_rows, 'time']
        trace_y = dataframe.loc[valid_rows, column_name]
        if trace_x.empty:
            return None, None
        return trace_x, trace_y

    trace_x = dataframe['time']
    trace_y = dataframe[column_name]
    if trace_x.empty:
        return None, None

    return trace_x, trace_y


if __name__ == '__main__':
    app.run(debug=True, port=8080)
