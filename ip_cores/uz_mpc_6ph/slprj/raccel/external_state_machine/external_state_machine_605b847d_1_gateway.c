#ifdef MATLAB_MEX_FILE
#include "tmwtypes.h"
#else
#include "rtwtypes.h"
#endif
#include "nesl_rtw.h"
#include "external_state_machine_605b847d_1.h"
#include "external_state_machine_605b847d_1_gateway.h"
void external_state_machine_605b847d_1_gateway ( void ) { NeModelParameters
modelparams = { ( NeSolverType ) 2 , 0.001 , 0 , 0 , 0.001 , 0 , 0 , 0 , 0 ,
( SscLoggingSetting ) 0 , 591307800 , } ; NeSolverParameters solverparams = {
0 , 0 , 1 , 0 , 0 , 0.001 , 1e-06 , 1e-09 , 0 , 0 , 100 , 0 , 1 , 0 , 1e-09 ,
1 , ( NeLocalSolverChoice ) 0 , 1e-06 , 1 , 3 , 2 , 0 , 2 , (
NeLinearAlgebraChoice ) 1 , ( NeEquationFormulationChoice ) 0 , 1024 , 1 ,
0.001 , ( NePartitionStorageMethod ) 0 , 1024 , ( NePartitionMethod ) 1 , } ;
const NeOutputParameters * outputparameters = NULL ; NeDae * dae ; size_t
numOutputs = 0 ; int * rtpDaes = NULL ; { static const NeOutputParameters
outputparameters_init [ ] = { { 0 , 0 , } , { 0 , 1 , } , } ;
outputparameters = outputparameters_init ; numOutputs = sizeof (
outputparameters_init ) / sizeof ( outputparameters_init [ 0 ] ) ; }
external_state_machine_605b847d_1_dae ( & dae , & modelparams , &
solverparams ) ; nesl_register_simulator_group (
"external_state_machine/Subsystem1/Solver Configuration1_1" , 1 , & dae , &
solverparams , & modelparams , numOutputs , outputparameters , 0 , rtpDaes )
; }
