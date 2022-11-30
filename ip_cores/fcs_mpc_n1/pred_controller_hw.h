/******************************************************************************
 *
 * pred_controller_hw_definitions.h
 *
 * Copyright (C) 2020 Institute EAL, TU München, All rights reserved.
 *
 *  Created on: 29.04.2020
 *      Author: Eyke Liegmann (EL)
 *
******************************************************************************/
#pragma once

#define Nh		1	// prediction horizon
#define Nin		3	// number of inputs, size of U
#define Nout	2	// number of outputs, size of Y
#define Nx		2	// number of states, size of X
#define Nopt    (Nh*Nin)	// size of the optimal solution
#define Nref 	(1*Nout) 	// horizon of reference vector reference, the IP core might be designed for longer horizons

#define Nsw_combs 8 // 2^3 - number of switching candidates

#define BITS_NinNh 2	// how many bits are necessary to count to Nin*Nh = ceiling(log2(Nin*Nh)), 4bits works up to Nh=5




// VISUAL_STUDIO is defined in VS project as pre-processor definition
#ifdef VISUAL_STUDIO
	#define PRAGMA_SUB(x)	__pragma (#x)
#else
	#define PRAGMA_SUB(x) _Pragma (#x)
#endif
#define DO_PRAGMA(x)	PRAGMA_SUB(x)

