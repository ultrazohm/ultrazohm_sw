.. _uz_HarmonicCurrentInjection:

========================
HarmonicCurrentInjection
========================

Toolbox for the implementation of parallel control loops to control user-defined current harmonics.
The user can chose between the following two control schemes:

.. tikz:: HarmonicCurrentInjection schematic
  :align: center

  \usetikzlibrary{arrows.meta, calc, positioning, shapes}
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%% FOC %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	% Define Blocks
	\tikzstyle{PMSM} = [circle, draw, fill=red!30, text width=1.4cm, text centered, minimum height=1.4cm]
	\tikzstyle{PI} = [rectangle, draw, fill=blue!30, text width=0.6cm, text centered, minimum height=0.6cm]
	\tikzstyle{DQ} = [rectangle, draw, fill=green!30, minimum width=1.2cm, text centered, minimum height=1.6cm]
	\tikzstyle{SVM} = [rectangle, draw, fill=orange!30, text width=1.6cm, text centered, minimum height=1.6cm]
	\tikzstyle{Add} = [circle, draw, minimum size=1cm, scale=0.2]
	\tikzstyle{Connection} = [ellipse, draw, minimum height=0.5cm, minimum width=0.7cm, fill=gray!30, scale=0.3]
		
	% Blocks
	\node[PI] (PI1) {PI};
	\node[PI, yshift=-1cm] (PI2) {PI};
	\node[DQ, xshift=3cm, yshift=-0.5cm] (DQ1) {};
	\draw (DQ1.south west) -- (DQ1.north east);
	\node[above of = DQ1, xshift=-0.3cm, yshift=-0.45cm] () {dq};
	\node[below of = DQ1, xshift=0.14cm, yshift=0.38cm] () {UVW};
	\node[SVM, xshift=5.5cm, yshift=-0.5cm] (SVM) {PWM\\ \& \\ Inverter};
	\node[PMSM, xshift=9.2cm, yshift=-0.5cm] (PMSM) {Motor};
	\node[DQ, xshift=3cm, yshift=-3.5cm] (DQ2) {};
	\draw (DQ2.south west) -- (DQ2.north east);
	\node[above of = DQ2, xshift=-0.3cm, yshift=-0.45cm] () {dq};
	\node[below of = DQ2, xshift=0.14cm, yshift=0.38cm] () {UVW};
	\node[xshift=-3cm, yshift=0cm] (Startd) {$I_{d,ref}$};
	\node[xshift=-3cm, yshift=-1cm] (Startq) {$I_{q,ref}$};
	\node[Add, xshift=-6cm, yshift=0cm, label={[xshift=0.2cm, yshift=-0.5cm]-}] (Add1) {};
	\node[Add, xshift=-9cm, yshift=-5cm, label={[xshift=0.2cm, yshift=-0.5cm]-}] (Add2) {};
	
	% Connections
	\draw[->, line width=1pt] (Startd.east) -- (Add1.west);
	\draw[->, line width=1pt] (Add1.east) -- (PI1.west);
	\draw[->, line width=1pt] (Startq.east) -- (Add2.west);
	\draw[->, line width=1pt] (Add2.east) -- (PI2.west);
	\draw[->, line width=1pt] ([yshift=0.5cm]DQ1.east) -- ([yshift=0.5cm]SVM.west);
	\draw[->, line width=1pt] ([yshift=0cm]DQ1.east) -- ([yshift=0cm]SVM.west);
	\draw[->, line width=1pt] ([yshift=-0.5cm]DQ1.east) -- ([yshift=-0.5cm]SVM.west);
	\draw[line width=1pt] ([yshift=0.5cm]SVM.east) -- ([xshift=0.16cm, yshift=0.5cm]PMSM.west);
	\draw[line width=1pt] ([yshift=0cm]SVM.east) -- ([yshift=0cm]PMSM.west);
	\draw[line width=1pt] ([yshift=-0.5cm]SVM.east) -- ([xshift=0.16cm, yshift=-0.5cm]PMSM.west);
	\draw[->, line width=1pt] ([xshift=0.5cm, yshift=0.5cm]SVM.east) -- ++(0,-3) -- ([yshift=0.5cm]DQ2.east);
	\node[Connection, xshift=0.5cm/0.3, yshift=0.5cm/0.3] (Con1) at (SVM.east) {};
	\draw[->, line width=1pt] ([xshift=1cm, yshift=0cm]SVM.east) -- ++(0,-3) -- ([yshift=0cm]DQ2.east);
	\node[Connection, xshift=1cm/0.3, yshift=0cm/0.3] (Con2) at (SVM.east) {};
	\draw[->, line width=1pt] ([xshift=1.5cm, yshift=-0.5cm]SVM.east) -- ++(0,-3) -- ([yshift=-0.5cm]DQ2.east);
	\node[Connection, xshift=1.5cm/0.3, yshift=-0.5cm/0.3] (Con3) at (SVM.east) {};
	\draw[->, line width=1pt] ([yshift=0.3cm]DQ2.west) -- ++(-3.6,0) -- (Add1.south);
	\draw[->, line width=1pt] ([yshift=-0.3cm]DQ2.west) -- ++(-4.2,0) -- (Add2.south);
	\draw[->, line width=1pt] (PMSM.south) -- ([yshift=-1.5cm]PMSM.center) -- ([yshift=-1.5cm]DQ1.center) -- (DQ1.south);
	\draw[->, line width=1pt] ([yshift=-1.5cm]DQ1.center) -- (DQ2.north);
	
	% Labels
	\node[left=of DQ2, xshift=0.5cm, yshift=0.5cm] (Id) {$I_d$};
	\node[left=of DQ2, xshift=0.5cm, yshift=-0.1cm] (Iq) {$I_q$};
	\node[right=of DQ2, xshift=-0.5cm, yshift=0.7cm] (Ia) {$I_U$};
	\node[right=of DQ2, xshift=-0.5cm, yshift=0.2cm] (Ib) {$I_V$};
	\node[right=of DQ2, xshift=-0.5cm, yshift=-0.3cm] (Ic) {$I_W$};
	\node[left=of DQ1, xshift=0.85cm, yshift=0.75cm] (Ud) {$U_d$};
	\node[left=of DQ1, xshift=0.85cm, yshift=-0.25cm] (Uq) {$U_q$};
	\node[right=of DQ1, xshift=-1cm, yshift=0.7cm] (Ua) {$U_U$};
	\node[right=of DQ1, xshift=-1cm, yshift=0.2cm] (Ub) {$U_V$};
	\node[right=of DQ1, xshift=-1cm, yshift=-0.3cm] (Uc) {$U_W$};
	\node[left=of DQ2, xshift=0.5cm, yshift=0.5cm] (Id) {$I_d$};
	\node[left=of DQ2, xshift=0.5cm, yshift=-0.1cm] (Iq) {$I_q$};
	\node[below=of PMSM, xshift=-5cm, yshift=0.9cm] (thetael) {$\theta_{el}$};
	
	%%%%%%%%%%%%%%%%%%%%%%%%%%%%% HCI %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	% Define Blocks
	\tikzstyle{BP} = [draw, rectangle, minimum width=1.2cm, minimum height=1.6cm, fill=yellow!50, path picture={\draw[line width=0.8pt] (-0.45,0.65) -- (-0.45,-0.65) -- (0.45,-0.65); \draw[line width=0.8pt] (-0.45,-0.65) to[out=5, in=255] (-0.06,0.15) to[out= 75, in=200] (0,0.25) to[out=-20, in=105] (0.06,0.15) to[out=-75, in=175] (0.45,-0.65);}]
	\tikzstyle{LP} = [draw, rectangle, minimum width=1.2cm, minimum height=1.6cm, fill=yellow!50, path picture={\draw[line width=0.8pt] (-0.45,0.65) -- (-0.45,-0.65) -- (0.45,-0.65); \draw[line width=0.8pt] (-0.45,0.0) -- (-0.25,0.0) to[out=0, in=130] (0.45,-0.65);}]
	
	% Blocks
	\node[BP, xshift=-1.45cm, yshift=-7cm] (BP1) {};
	\node[DQ, xshift=0.8cm, yshift=-7cm] (DQ3) {};
	\draw (DQ3.south west) -- (DQ3.north east);
	\node[above of = DQ3, xshift=-0.14cm, yshift=-0.4cm] () {UVW};
	\node[below of = DQ3, xshift=0.3cm, yshift=0.45cm] () {dqn};
	\node[LP, xshift=3cm, yshift=-7cm] (LP1) {};
	\node[Add, xshift=4.8cm/0.2, yshift=-6.5cm/0.2] (Add3) {};
	\node[Add, xshift=4.8cm/0.2, yshift=-7.5cm/0.2] (Add4) {};
	\node[PI, xshift=5.7cm, yshift=-6.5cm] (PI3) {PI};
	\node[PI, xshift=5.7cm, yshift=-7.5cm] (PI4) {PI};
	\node[DQ, xshift=7.7cm, yshift=-7cm] (DQ5) {};
	\draw (DQ5.south west) -- (DQ5.north east);
	\node[above of = DQ5, xshift=-0.2cm, yshift=-0.45cm] () {dqn};
	\node[below of = DQ5, xshift=0.3cm, yshift=0.45cm] () {dq};
	\node[Add, xshift=1.5cm/0.2, yshift=0cm/0.2] (Add9) {};
	\node[Add, xshift=1.0cm/0.2, yshift=-1cm/0.2] (Add10) {};
	
	% Connections
	\node[Connection, xshift=3.32cm/0.3, yshift=0.5cm/0.3] (Con4) at (DQ2.east) {};
	\draw[->, line width=1pt] (Con4) -- ++(0,-1.7) -- ++(-10.4,0) -- ++(0,-1.8) -- ([yshift=0.5cm]BP1.west);
	\node[Connection, xshift=3.82cm/0.3, yshift=0cm/0.3] (Con5) at (DQ2.east) {};
	\draw[->, line width=1pt] (Con5) -- ++(0,-1.4) -- ++(-10.4,0) -- ++(0,-2.1) -- ([yshift=-0cm]BP1.west);
	\node[Connection, xshift=4.32cm/0.3, yshift=-0.5cm/0.3] (Con6) at (DQ2.east) {};
	\draw[->, line width=1pt] (Con6) -- ++(0,-1.1) -- ++(-10.4,0) -- ++(0,-2.4) -- ([yshift=-0.5cm]BP1.west);
	\draw[->, line width=1pt] ([yshift=0.5cm]BP1.east) -- ([yshift=0.5cm]DQ3.west);
	\draw[->, line width=1pt] ([yshift=0cm]BP1.east) -- ([yshift=0cm]DQ3.west);
	\draw[->, line width=1pt] ([yshift=-0.5cm]BP1.east) -- ([yshift=-0.5cm]DQ3.west);
	\draw[->, line width=1pt] ([yshift=0.5cm]DQ3.east) -- ([yshift=0.5cm]LP1.west);
	\draw[->, line width=1pt] ([yshift=-0.5cm]DQ3.east) -- ([yshift=-0.5cm]LP1.west);
	\draw[->, line width=1pt] ([yshift=0.5cm]LP1.east) -- (Add3.west);
	\draw[->, line width=1pt] ([yshift=-0.5cm]LP1.east) -- (Add4.west);
	\draw[->, line width=1pt] (Add3.east) -- (PI3.west);
	\draw[->, line width=1pt] (Add4.east) -- (PI4.west);
	\draw[->, line width=1pt] (PI3.east) -- ([yshift=0.5cm]DQ5.west);
	\draw[->, line width=1pt] (PI4.east) -- ([yshift=-0.5cm]DQ5.west);
	\draw[->, line width=1pt] ([yshift=0.5cm]DQ5.east) -- ++(1.9,0) -- ++(0,7.1) -- ++(-8.7,0) -- (Add9.north);
	\draw[->, line width=1pt] ([yshift=-0.5cm]DQ5.east) -- ++(2.1,0) -- ++(0,8.3) -- ++(-9.4,0) -- (Add10.north);
	\draw[->, line width=1pt] (PI1.east) -- (Add9.west);
	\draw[->, line width=1pt] (PI2.east) -- (Add10.west);
	\draw[->, line width=1pt] (Add9.east) -- ([yshift=0.5cm]DQ1.west);
	\draw[->, line width=1pt] (Add10.east) -- ([yshift=-0.5cm]DQ1.west);
	\draw[->, line width=1pt] ([yshift=0.4cm]Add3.north) -- (Add3.north);
	\draw[->, line width=1pt] ([yshift=0.4cm]Add4.north) -- (Add4.north);
	\node[Connection, below=of PMSM, yshift=0.43cm/0.3] (Con10) {};
	\draw[->, line width=1pt] (Con10) -- ++(0,-3.6) -- ++(-8.4,0) -- (DQ3.north);
	\draw[->, line width=1pt] ([yshift=0.6cm]DQ5.north) -- (DQ5.north);
	
	% Labels
	\node[right=of BP1, xshift=-1.05cm, yshift=0.7cm] (Ia5) {$I_{U,n}$};
	\node[right=of BP1, xshift=-1.05cm, yshift=0.2cm] (Ib5) {$I_{V,n}$};
	\node[right=of BP1, xshift=-1.05cm, yshift=-0.3cm] (Ic5) {$I_{W,n}$};
	\node[right=of DQ3, xshift=-1cm, yshift=0.7cm] (Id5) {$I_{dn}$};
	\node[right=of DQ3, xshift=-1cm, yshift=-0.3cm] (Iq5) {$I_{qn}$};
	\node[above=of Add3, xshift=-0.6cm, yshift=-1cm] (Id5ref) {$I_{dn,ref}$};
	\node[above=of Add4, xshift=-0.6cm, yshift=-1cm] (Id5ref) {$I_{qn,ref}$};
	\node[right=of PI3, xshift=-1cm, yshift=0.2cm] (Ud5) {$U_{dn}$};
	\node[right=of PI4, xshift=-1cm, yshift=0.2cm] (Uq5) {$U_{qn}$};
	\node[above=of LP1, xshift=1.6cm, yshift=-0.5cm] (thetael2) {$\theta_{el}$};
  \end{tikzpicture}

  \begin{tikzpicture}
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%% FOC %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	% Define Blocks
	\tikzstyle{PMSM} = [circle, draw, fill=red!30, text width=1.4cm, text centered, minimum height=1.4cm]
	\tikzstyle{PI} = [rectangle, draw, fill=blue!30, text width=0.6cm, text centered, minimum height=0.6cm]
	\tikzstyle{DQ} = [rectangle, draw, fill=green!30, minimum width=1.2cm, text centered, minimum height=1.6cm]
	\tikzstyle{SVM} = [rectangle, draw, fill=orange!30, text width=1.6cm, text centered, minimum height=1.6cm]
	\tikzstyle{Add} = [circle, draw, minimum size=1cm, scale=0.2]
	\tikzstyle{Connection} = [ellipse, draw, minimum height=0.5cm, minimum width=0.7cm, fill=gray!30, scale=0.3]
		
	% Blocks
	\node[PI] (PI1) {PI};
	\node[PI, yshift=-1cm] (PI2) {PI};
	\node[DQ, xshift=3cm, yshift=-0.5cm] (DQ1) {};
	\draw (DQ1.south west) -- (DQ1.north east);
	\node[above of = DQ1, xshift=-0.3cm, yshift=-0.45cm] () {dq};
	\node[below of = DQ1, xshift=0.14cm, yshift=0.38cm] () {UVW};
	\node[SVM, xshift=5.5cm, yshift=-0.5cm] (SVM) {PWM\\ \& \\ Inverter};
	\node[PMSM, xshift=9.2cm, yshift=-0.5cm] (PMSM) {Motor};
	\node[DQ, xshift=3cm, yshift=-3.5cm] (DQ2) {};
	\draw (DQ2.south west) -- (DQ2.north east);
	\node[above of = DQ2, xshift=-0.3cm, yshift=-0.45cm] () {dq};
	\node[below of = DQ2, xshift=0.14cm, yshift=0.38cm] () {UVW};
	\node[xshift=-3cm, yshift=0cm] (Startd) {$I_{d,ref}$};
	\node[xshift=-3cm, yshift=-1cm] (Startq) {$I_{q,ref}$};
	\node[Add, xshift=-6cm, yshift=0cm, label={[xshift=0.2cm, yshift=-0.5cm]-}] (Add1) {};
	\node[Add, xshift=-9cm, yshift=-5cm, label={[xshift=0.2cm, yshift=-0.5cm]-}] (Add2) {};
	
	% Connections
	\draw[->, line width=1pt] (Startd.east) -- (Add1.west);
	\draw[->, line width=1pt] (Add1.east) -- (PI1.west);
	\draw[->, line width=1pt] (Startq.east) -- (Add2.west);
	\draw[->, line width=1pt] (Add2.east) -- (PI2.west);
	\draw[->, line width=1pt] ([yshift=0.5cm]DQ1.east) -- ([yshift=0.5cm]SVM.west);
	\draw[->, line width=1pt] ([yshift=0cm]DQ1.east) -- ([yshift=0cm]SVM.west);
	\draw[->, line width=1pt] ([yshift=-0.5cm]DQ1.east) -- ([yshift=-0.5cm]SVM.west);
	\draw[line width=1pt] ([yshift=0.5cm]SVM.east) -- ([xshift=0.16cm, yshift=0.5cm]PMSM.west);
	\draw[line width=1pt] ([yshift=0cm]SVM.east) -- ([yshift=0cm]PMSM.west);
	\draw[line width=1pt] ([yshift=-0.5cm]SVM.east) -- ([xshift=0.16cm, yshift=-0.5cm]PMSM.west);
	\draw[->, line width=1pt] ([xshift=0.5cm, yshift=0.5cm]SVM.east) -- ++(0,-3) -- ([yshift=0.5cm]DQ2.east);
	\node[Connection, xshift=0.5cm/0.3, yshift=0.5cm/0.3] (Con1) at (SVM.east) {};
	\draw[->, line width=1pt] ([xshift=1cm, yshift=0cm]SVM.east) -- ++(0,-3) -- ([yshift=0cm]DQ2.east);
	\node[Connection, xshift=1cm/0.3, yshift=0cm/0.3] (Con2) at (SVM.east) {};
	\draw[->, line width=1pt] ([xshift=1.5cm, yshift=-0.5cm]SVM.east) -- ++(0,-3) -- ([yshift=-0.5cm]DQ2.east);
	\node[Connection, xshift=1.5cm/0.3, yshift=-0.5cm/0.3] (Con3) at (SVM.east) {};
	\draw[->, line width=1pt] ([yshift=0.3cm]DQ2.west) -- ++(-3.6,0) -- (Add1.south);
	\draw[->, line width=1pt] ([yshift=-0.3cm]DQ2.west) -- ++(-4.2,0) -- (Add2.south);
	\draw[->, line width=1pt] (PMSM.south) -- ([yshift=-1.5cm]PMSM.center) -- ([yshift=-1.5cm]DQ1.center) -- (DQ1.south);
	\draw[->, line width=1pt] ([yshift=-1.5cm]DQ1.center) -- (DQ2.north);
	
	% Labels
	\node[left=of DQ2, xshift=0.5cm, yshift=0.5cm] (Id) {$I_d$};
	\node[left=of DQ2, xshift=0.5cm, yshift=-0.1cm] (Iq) {$I_q$};
	\node[right=of DQ2, xshift=-0.5cm, yshift=0.7cm] (Ia) {$I_U$};
	\node[right=of DQ2, xshift=-0.5cm, yshift=0.2cm] (Ib) {$I_V$};
	\node[right=of DQ2, xshift=-0.5cm, yshift=-0.3cm] (Ic) {$I_W$};
	\node[left=of DQ1, xshift=0.85cm, yshift=0.75cm] (Ud) {$U_d$};
	\node[left=of DQ1, xshift=0.85cm, yshift=-0.25cm] (Uq) {$U_q$};
	\node[right=of DQ1, xshift=-1cm, yshift=0.7cm] (Ua) {$U_U$};
	\node[right=of DQ1, xshift=-1cm, yshift=0.2cm] (Ub) {$U_V$};
	\node[right=of DQ1, xshift=-1cm, yshift=-0.3cm] (Uc) {$U_W$};
	\node[left=of DQ2, xshift=0.5cm, yshift=0.5cm] (Id) {$I_d$};
	\node[left=of DQ2, xshift=0.5cm, yshift=-0.1cm] (Iq) {$I_q$};
	\node[below=of PMSM, xshift=-5cm, yshift=0.9cm] (thetael) {$\theta_{el}$};
	
	%%%%%%%%%%%%%%%%%%%%%%%%%%%%% HCI %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	% Define Blocks
	\tikzstyle{BP} = [draw, rectangle, minimum width=1.2cm, minimum height=1.6cm, fill=yellow!50, path picture={\draw[line width=0.8pt] (-0.45,0.65) -- (-0.45,-0.65) -- (0.45,-0.65); \draw[line width=0.8pt] (-0.45,-0.65) to[out=5, in=255] (-0.06,0.15) to[out= 75, in=200] (0,0.25) to[out=-20, in=105] (0.06,0.15) to[out=-75, in=175] (0.45,-0.65);}]
	\tikzstyle{LP} = [draw, rectangle, minimum width=1.2cm, minimum height=1.6cm, fill=yellow!50, path picture={\draw[line width=0.8pt] (-0.45,0.65) -- (-0.45,-0.65) -- (0.45,-0.65); \draw[line width=0.8pt] (-0.45,0.0) -- (-0.25,0.0) to[out=0, in=130] (0.45,-0.65);}]
	
	% Blocks
	\node[BP, xshift=-1.8cm, yshift=-6cm] (BP1) {};
	\node[DQ, xshift=0.8cm, yshift=-6cm] (DQ3) {};
	\draw (DQ3.south west) -- (DQ3.north east);
	\node[above of = DQ3, xshift=-0.24cm, yshift=-0.45cm] () {dq};
	\node[below of = DQ3, xshift=0.2cm, yshift=0.45cm] () {dqn};
	\node[LP, xshift=3cm, yshift=-6cm] (LP1) {};
	\node[Add, xshift=4.8cm/0.2, yshift=-5.5cm/0.2] (Add3) {};
	\node[Add, xshift=4.8cm/0.2, yshift=-6.5cm/0.2] (Add4) {};
	\node[PI, xshift=5.7cm, yshift=-5.5cm] (PI3) {PI};
	\node[PI, xshift=5.7cm, yshift=-6.5cm] (PI4) {PI};
	\node[DQ, xshift=7.7cm, yshift=-6cm] (DQ5) {};
	\draw (DQ5.south west) -- (DQ5.north east);
	\node[above of = DQ5, xshift=-0.2cm, yshift=-0.45cm] () {dqn};
	\node[below of = DQ5, xshift=0.3cm, yshift=0.45cm] () {dq};
	\node[Add, xshift=1.5cm/0.2, yshift=0cm/0.2] (Add9) {};
	\node[Add, xshift=1.0cm/0.2, yshift=-1cm/0.2] (Add10) {};
	
	% Connections
	\node[Connection, xshift=-3.6cm/0.3, yshift=0.3cm/0.3] (Con4) at (DQ2.west) {};
	\draw[->, line width=1pt] (Con4) -- ++(0,-1.2) -- ++(-1.8,0) -- ++(0,-1.1) -- ([yshift=0.5cm]BP1.west);
	\node[Connection, xshift=-4.2cm/0.3, yshift=-0.3cm/0.3] (Con6) at (DQ2.west) {};
	\draw[->, line width=1pt] (Con6) -- ++(-1.6,0) -- ++(0,-2.7) -- ([yshift=-0.5cm]BP1.west);
	\draw[->, line width=1pt] ([yshift=0.5cm]BP1.east) -- ([yshift=0.5cm]DQ3.west);
	\draw[->, line width=1pt] ([yshift=-0.5cm]BP1.east) -- ([yshift=-0.5cm]DQ3.west);
	\draw[->, line width=1pt] ([yshift=0.5cm]DQ3.east) -- ([yshift=0.5cm]LP1.west);
	\draw[->, line width=1pt] ([yshift=-0.5cm]DQ3.east) -- ([yshift=-0.5cm]LP1.west);
	\draw[->, line width=1pt] ([yshift=0.5cm]LP1.east) -- (Add3.west);
	\draw[->, line width=1pt] ([yshift=-0.5cm]LP1.east) -- (Add4.west);
	\draw[->, line width=1pt] (Add3.east) -- (PI3.west);
	\draw[->, line width=1pt] (Add4.east) -- (PI4.west);
	\draw[->, line width=1pt] (PI3.east) -- ([yshift=0.5cm]DQ5.west);
	\draw[->, line width=1pt] (PI4.east) -- ([yshift=-0.5cm]DQ5.west);
	\draw[->, line width=1pt] ([yshift=0.5cm]DQ5.east) -- ++(1.9,0) -- ++(0,6.1) -- ++(-8.7,0) -- (Add9.north);
	\draw[->, line width=1pt] ([yshift=-0.5cm]DQ5.east) -- ++(2.1,0) -- ++(0,7.3) -- ++(-9.4,0) -- (Add10.north);
	\draw[->, line width=1pt] (PI1.east) -- (Add9.west);
	\draw[->, line width=1pt] (PI2.east) -- (Add10.west);
	\draw[->, line width=1pt] (Add9.east) -- ([yshift=0.5cm]DQ1.west);
	\draw[->, line width=1pt] (Add10.east) -- ([yshift=-0.5cm]DQ1.west);
	\draw[->, line width=1pt] ([yshift=0.4cm]Add3.north) -- (Add3.north);
	\draw[->, line width=1pt] ([yshift=0.4cm]Add4.north) -- (Add4.north);
	\node[Connection, below=of PMSM, yshift=0.43cm/0.3] (Con10) {};
	\draw[->, line width=1pt] (Con10) -- ++(0,-2.6) -- ++(-8.4,0) -- (DQ3.north);
	\draw[->, line width=1pt] ([yshift=0.6cm]DQ5.north) -- (DQ5.north);
		
	% Labels
	\node[right=of BP1, xshift=-1.05cm, yshift=0.7cm] (Ia5) {$I_{d,n-1}$};
	\node[right=of BP1, xshift=-1.05cm, yshift=-0.3cm] (Ic5) {$I_{q,n-1}$};
	\node[right=of DQ3, xshift=-1cm, yshift=0.7cm] (Id5) {$I_{dn}$};
	\node[right=of DQ3, xshift=-1cm, yshift=-0.3cm] (Iq5) {$I_{qn}$};
	\node[above=of Add3, xshift=-0.6cm, yshift=-1cm] (Id5ref) {$I_{dn,ref}$};
	\node[above=of Add4, xshift=-0.6cm, yshift=-1cm] (Id5ref) {$I_{qn,ref}$};
	\node[right=of PI3, xshift=-1cm, yshift=0.2cm] (Ud5) {$U_{dn}$};
	\node[right=of PI4, xshift=-1cm, yshift=0.2cm] (Uq5) {$U_{qn}$};
	\node[above=of LP1, xshift=1.6cm, yshift=-0.5cm] (thetael2) {$\theta_{el}$};
  \end{tikzpicture}

Setup
=====

.. _uz_HarmonicCurrentInjection_config:

Configuration
-------------

In order to configure the CurrentControl, multiple configuration structs have to be initialized.

.. doxygenenum:: uz_HarmonicCurrentInjection_mode_select

.. doxygenstruct:: uz_HarmonicCurrentInjection_config
  :members:

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example to initialize the configuration struct

  #include "uz/uz_HarmonicCurrentInjection/uz_HarmonicCurrentInjection.h"
  int main(void) {
    struct uz_PI_Controller_config config_id = {
      .Kp = 10.0f,
      .Ki = 10.0f,
      .samplingTime_sec = 0.00005f
    };
    struct uz_PI_Controller_config config_iq = {
      .Kp = 10.0f,
      .Ki = 10.0f,
      .samplingTime_sec = 0.00005f
    };
    struct uz_CurrentControl_config CurrentController_config = {
      .decoupling_select = no_decoupling,
      .config_PMSM = config_PMSM,
      .config_id = config_id,
      .config_iq = config_iq,
      .max_modulation_index = 1.0f / sqrtf(3.0f)
    struct uz_IIR_Filter_config Bandpass_abc_config = {
      .selection = BandPass_second_order,
      .pass_frequency_Hz = 300.0f,
      .damping = 0.05f,
      .sample_frequency_Hz = 1000.0f
    };
    struct uz_IIR_Filter_config Bandpass_dq_config = {
      .selection = BandPass_second_order,
      .pass_frequency_Hz = 360.0f,
      .damping = 0.05f,
      .sample_frequency_Hz = 1000.0f
    };
    struct uz_IIR_Filter_config Lowpass_dq_config = {
      .selection = LowPass_first_order,
      .cutoff_frequency_Hz = 60.0f,
      .sample_frequency_Hz = 1000.0f,
    };
    struct uz_HarmonicCurrentInjection_config HCI_config = {
      .order_harmonic = -5.0f,
      .selection = abc_to_dq,
      .config_currentController = CurrentController_config,
      .config_bandpass_abc = Bandpass_abc_config,
      .config_bandpass_dq = Bandpass_dq_config,
      .config_lowpass_dq = Lowpass_dq_config
    };
  }

Description
^^^^^^^^^^^

With these config structs one can customize the HarmonicCurrentInjection and the included CurrentControl and IIR Filters. 
It is possible to choose the between the shown control schemes by using the selection option. 
The cutoff_frequency_Hz, pass_frequency_Hz and damping can be set to suitable values or to arbitrary values and set afterwards via the set functions shown below.
It is recommended to deactivate the decoupling option of the CurrentControl.

.. _uz_HarmonicCurrentInjection_init:

Init function
-------------

.. doxygentypedef:: uz_HarmonicCurrentInjection_t
.. doxygenfunction:: uz_HarmonicCurrentInjection_init

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to init a HarmonicCurrentInjection instance. ``config_HarmonicCurrentInjection`` according to configuration section.

  int main(void) {
     uz_HarmonicCurrentInjection_t* HCI_instance = uz_HarmonicCurrentInjection_init(HCI_config);
  }

Description
^^^^^^^^^^^

Allocates the memory for the HarmonicCurrentInjection instance and the included CurrentControl and IIR Filter instances. 
Furthermore the input values of the configuration structs are asserted. 

.. _uz_HarmonicCurrentInjection_sample:

Sample function
---------------

.. doxygenfunction:: uz_HarmonicCurrentInjection_sample

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate the HarmonicCurrentInjection output. HarmonicCurrentInjection-Instance via init-function.

  int main(void) {
    float V_dc_volts = 24.0f;
    float omega_el_rad_per_sec = 125.1f;
    float theta_el_rad = 1.2f;
    struct uz_3ph_dq_t i_abc_actual_Ampere = {.a = 1.0f, .b = -0.5f, .c = -0.5f};
    struct uz_3ph_dq_t i_ref_harmonic_Ampere = {.d = 1.0f, .q = 2.0f, .zero = 0.0f};
    uz_3ph_dq_t v_dq_Volts = uz_HarmonicCurrentInjection_sample(HCI_instance, i_ref_harmonic_Ampere, i_abc_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, theta_el_rad);
  }

Description
^^^^^^^^^^^

Calculates one sample of the CurrentControl.

.. warning::

  The sample function has to be called with the same sample time as specified in the ``samplingTime_sec`` member of the :ref:`PI-Controller configuration struct <uz_piController_config>` and the :ref:`IIR filter configuration struct <uz_IIR_Filter>`.

.. _uz_HarmonicCurrentInjection_set_filters:

Set filters function
--------------------

.. doxygenfunction:: uz_HarmonicCurrentInjection_set_filters_abc

.. doxygenfunction:: uz_HarmonicCurrentInjection_set_filters_dq

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to update the filters of a HarmonicCurrentInjection-Instance.

  int main(void) {
    float omega_el_rad_per_sec = 60.0f;
    uz_HarmonicCurrentInjection_set_filters_abc(HCI_instance, omega_el_rad_per_sec);
    uz_HarmonicCurrentInjection_set_filters_dq(HCI_instance, omega_el_rad_per_sec);
  }

Description
^^^^^^^^^^^

Updates the filters of a HarmonicCurrentInjection-Instance according to a given electrical rotational speed.

.. note::

  Either the ``uz_HarmonicCurrentInjection_set_filters_abc`` function or the ``uz_HarmonicCurrentInjection_set_filters_dq`` function has to be called depending on the control scheme chosen in the mode selection.



