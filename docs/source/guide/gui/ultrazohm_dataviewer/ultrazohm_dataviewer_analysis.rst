Analysis mode
=============

Use analysis mode for CSV/Parquet recordings, including JavaScope logs and completed CLI recordings.
No acquisition service, firmware checkout or device is required.

1. Start the viewer and choose **Navigation → Open file(s)…**, or run ``ultrazohm-dataviewer gui measurement.parquet``.
2. Expand the recording and drag signals into Plots.
   Select a grid and zoom to the interval of interest.
   The default Polars + Lazy mode reads windows from disk; use Parquet for repeated access to large recordings.
3. Drag a signal into FFT or Histogram, select the time window and press **Compute**.
   Nodes provide filters, math and chained transforms.
4. Export a plot or analysis result to CSV.
   Exports use original samples rather than display downsampling.
   Wait for completion in the Application log.
5. Save the analysis with **Save state**, or ``viewer.save_session("analysis.json")``.
   Reopen with ``ultrazohm-dataviewer gui analysis.json``.
   Keep referenced recordings available: session JSON stores references and settings, not measurement arrays.

Files with a single ``time`` or ``frequency`` column select their axis automatically.
Otherwise select the axis column and its domain when prompted.
FFT and FIR filters require uniformly spaced time data; imported spectra cannot be processed as time data.
Live snapshots and other memory-only recordings must be exported before saving a reloadable session.
Exporting does not attach the saved file to the existing snapshot.
Open the exported file, recreate plot assignments and node sources using that recording, then remove the memory-only snapshot before saving the session.
Node outputs derived from reloadable recordings are restored through their saved graph and do not require separate exports.

See :doc:`ultrazohm_dataviewer_usage` for the full panel and method reference, :doc:`ultrazohm_dataviewer_library` for headless numerical analysis, and :doc:`ultrazohm_dataviewer_workflows` for Python automation.
