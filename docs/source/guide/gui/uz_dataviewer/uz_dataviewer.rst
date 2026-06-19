.. _uz_dataviewer:

========================
UltraZohm Data Viewer
========================

``uz_dataviewer`` is a ImGui/ImPlot desktop and web application for inspecting the ``Log_*.csv`` / ``.parquet`` logs that JavaScope records.
It does not talk to hardware — it reads files only — and is built to make multi-gigabyte logs fast and interactive.

These pages cover how to use the viewer, how it is built and packaged, how to drive its data/analysis core as a headless Python library, how to extend it with node plugins, and the design notes / roadmap behind it.

.. toctree::
   :maxdepth: 1
   :caption: User documentation

   usage
   build
   library
   plugins

.. toctree::
   :maxdepth: 1
   :caption: Design & internals

   architecture
   native_vs_web
   dataviewer_v_javascope

.. toctree::
   :maxdepth: 1
   :caption: Roadmap & proposals

   roadmap
   nodes_future_ideas
   remote_data
   web_large_logs
