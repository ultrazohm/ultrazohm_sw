.. _hil:

====================
Hardware in the Loop
====================


.. tikz:: Plant model in PS, Control algorithm in PL
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(mpsoc) {MPSoC};
  \node[name=ps, below = 0.1cm of mpsoc] {PS};
  \node[block,name=plant, below = 0.2cm of ps,drop shadow] {Plant model};
  \node[block,name=controller, below of=plant,drop shadow] {Controller};
  \node[name=pl, below = 0.1cm of controller] {PL};
  \begin{scope}[on background layer]
    \node[draw,fill=blue!10,rounded corners,fit=(mpsoc) (pl),inner sep=5pt,minimum width=3.5cm] {};
    \node[draw,fill=yellow!20,rounded corners,fit=(pl) (controller),inner sep=5pt,minimum width=2.5cm] {};
    \node[draw,fill=green!10,rounded corners,fit=(ps) (plant),inner sep=5pt,minimum width=2.5cm] {};
  \end{scope}
  \draw[->] ([xshift=-0.3cm]controller.north) -- ([xshift=-0.3cm]plant.south);
  \draw[<-] ([xshift=0.3cm]controller.north) -- ([xshift=0.3cm]plant.south);
  \end{tikzpicture}

.. tikz:: Plant in PS, Control algorithm in PL
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(mpsoc) {MPSoC};
  \node[name=ps, below = 0.1cm of mpsoc] {PS};
  \node[block,name=plant, below = 0.2cm of ps,drop shadow] {Controller};
  \node[block,name=controller, below of=plant,drop shadow] {Plant model};
  \node[name=pl, below = 0.1cm of controller] {PL};
  \begin{scope}[on background layer]
    \node[draw,fill=blue!10,rounded corners,fit=(mpsoc) (pl),inner sep=5pt,minimum width=3.5cm] {};
    \node[draw,fill=yellow!20,rounded corners,fit=(pl) (controller),inner sep=5pt,minimum width=2.5cm] {};
    \node[draw,fill=green!10,rounded corners,fit=(ps) (plant),inner sep=5pt,minimum width=2.5cm] {};
  \end{scope}
  \draw[->] ([xshift=-0.3cm]controller.north) -- ([xshift=-0.3cm]plant.south);
  \draw[<-] ([xshift=0.3cm]controller.north) -- ([xshift=0.3cm]plant.south);
  \end{tikzpicture}


.. tikz:: Control algorithm in PS and PL, Plant model in PL
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows

  \begin{tikzpicture}[auto, node distance=2.5cm,>=latex']
  \tikzstyle{block} = [draw, fill=black!10, rectangle, rounded corners, minimum height=3em, minimum width=3em]
  \node(mpsoc) {MPSoC};
  \node[name=ps, below = 0.1cm of mpsoc] {PS};
  \node[block,name=controller_ps, below = 0.2cm of ps,drop shadow] {Controller};
  \node[block,name=controller, below = 1cm of controller_ps,drop shadow] {Controller};
  \node[block,name=plant_pl, right of=controller,drop shadow] {Plant};
  \node[name=pl, below = 0.1cm of controller] {PL};
  \begin{scope}[on background layer]
    \node[draw,fill=blue!10,rounded corners,fit=(mpsoc) (pl) (plant_pl),inner sep=5pt,minimum width=5.5cm] {};
    \node[draw,fill=yellow!20,rounded corners,fit=(pl) (controller) (plant_pl),inner sep=5pt,minimum width=2.5cm] {};
    \node[draw,fill=green!10,rounded corners,fit=(ps) (controller_ps),inner sep=5pt,minimum width=2.5cm] {};
  \end{scope}
  \draw[->] ([xshift=-0.3cm]controller.north) -- ([xshift=-0.3cm]controller_ps.south);
  \draw[<-] ([xshift=0.3cm]controller.north) -- ([xshift=0.3cm]controller_ps.south);
  \draw[->] ([yshift=-0.2cm]controller.east) -- ([yshift=-0.2cm]plant_pl.west);
  \draw[<-] ([yshift=0.2cm]controller.east) -- ([yshift=0.2cm]plant_pl.west);
  \draw[->] ([xshift=-0.2cm]plant_pl.north) |- ([yshift=-0.2cm]controller_ps.east);
  \draw[<-] ([xshift=0.2cm]plant_pl.north) |- ([yshift=0.2cm]controller_ps.east);
  \end{tikzpicture}