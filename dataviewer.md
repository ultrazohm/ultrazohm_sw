# Build imgui dataviewer

> In javascope, there is a python based dataviewer (dataviewer.py) that uses plotly. I want a dataviewer with the same functions but using [pthom/imgui_bundle](https://github.com/pthom/imgui_bundle) instead.
> The core functionality is to read log files generated from the javascope (in javascope directory). The log files are either .csv or parquet, both has to work. Note that the files can be quite large (>1 GB of data), so downsampling is probably required to see long data logs. Check what is currently used for downsampling and if this can be used with imgui_bundle or not.
> Visually, I want changes compared to the existing dataviewer.py. I want a 3-layout version with navigation left, main view right and console on the bottom (similar to vscode layout).
> In the navigation left, I want to see all data that I loaded (multiple data files have to be able to load) and then activate only the ones I want to use. I want to be able to "click open" the run and then see what signals were logged (similar to Matlab data viewer). I want to be able to create multiple sub plots and then drag and drop the signals I want to see "into" the plot. The plot grid should be run-time settable (e.g., 1x2, 1x1, 2x2) and the type of the plot should be changeable. At a later state, I want, for example, to plot a time signal and have a second window display the FFT of the signal where I can select what part of the original signal should be used for the FFT.
> Think about the problem and present your plan, then implement the plan without checking back
>
> - Create a new repo level directory "uz_dataviewer"
> - In the directory, start a new python project that implements the dataviewer functionality using imgui_bundle
> - make sure that there is a clean structure and the resulting dataviewer can be compiled to native apps for windows, unix (ubuntu), and web (see imgui_bundle docs)
> - Clean build flow is essential