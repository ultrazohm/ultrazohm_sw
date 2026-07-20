================================
Ordering adapter cards at JLCPCB
================================

Ensure that

- your edge connectors are placed correctly relative to the board outline

  - see `Issue #61: Board Outline on M1 misalignment in y-axis by 0.046 mm with respect to edge connector X1 <https://bitbucket.org/ultrazohm/uz_a_ltc2311-16/issues/61/>`_ (A cards) and
  - `Issue #9: Board Outline misaligned with respect to edge connector X1 <https://bitbucket.org/ultrazohm/uz_d_template/issues/9/>`_ (D cards) for details, and that

- both symbol and footprint are synchronized to the UZ library (see Warning in :ref:`mech_layers`).

Then, select "45°" as the "Beveling" option during the JLC order process.
