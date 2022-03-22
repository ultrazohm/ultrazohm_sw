.. _uz_PID_new_ID_state:

==============================
Guide to create a new ID-state
==============================

The current ``ID-states`` carry a wide range of identification methods. 
However, if a new identification method is supposed to be implemented, this guide will assist in creating a new ``ID-state``.
Before starting the procedure of creating a new state, it is advised to read up about the general concept and layout of the ParmeterID in :ref:`uz_ParameterID`, :ref:`uz_PID_setup`, :ref:`uz_ParameterID_Data_structs` and :ref:`uz_PID_new_control_algorithm`.

General information
===================

* To ensure proper independence of the stateflows from the sampleTime, try to make if-statements with a counter value in relation to the sampleTime. (instead of ``==20000`` write ``==uint32(2/GlobalConfig.sampleTimeISR)`` @10kHz).
* Avoid i.e. ``after(1.0,sec)`` state transition conditions. Create custom counter values for i.e. 1 second delays. Otherwise the transition won't scale with different sample times.
* A three-phase testbench setup with a PMSM, inverter, load machine and physical couplings is included in the subsystem ``Hardware``. This can be used to test the new stateflow. 
* To signal which state is currently active, each state in one ``ID-state`` has a unique ``activeState`` value. Each ``ID-state`` follows the naming scheme of ``Yxx``, where ``Y`` is the decimal for the state, and ``xx`` the decimals for the substates (i.e. 621). 


Changes in the Simulation model
===============================

#. Create a new empty stateflow.
#. Add the necessary inputs. These most likely include :ref:`uz_Global_config_struct`, :ref:`uz_Control_flags_struct` and :ref:`uz_Actual_values_struct`.
#. If applicable, add the :ref:`uz_Controller_parameters_struct` bus as output with the name.
#. Select the appropriate bus types for the inputs and output. I.e. for the ControlFlags bus
  
    .. image:: ../images/assign_bus.png

#. Give the state an appropriate name in the scheme of ``StateID`` i.e. ``ElectricalID``.
#. To clean up the signalflow, ``Go-to`` and ``From`` blocks are used. Copy the three appropriate input ``From``-blocks from another state and connect them.
#. Copy the ``Go-to`` from another state, change its name according to the state name ``stateID_FOC_output`` and adjust its color accordingly. This type of output block has different shades of blue.
#. Add acknowledgement-flags as outputs of the state.
  
   * If the state is designed as an OfflineID-state, add two outputs with the names ``enteredStateID`` and ``finishedStateID``.
   * If it is designed as an OnlineID-state, the output ``enteredStateID`` is sufficient. 

#. Copy the appropriate ``Go-to`` blocks from another state and adjust the names and colors.

    .. image:: ../images/output_inputs1.png


#. The ParameterID is shipped with a ``.mat`` file which includes all necessary busses. Open it with the bus-editor.

   .. note::

      Stick to the data types ``boolean``, ``single`` and if necessary ``uint32``. Do not use ``double``, since the UltraZohm has no dedicated hardware for FP64 calculations. 
  
   * Add a new bus for the state-specific configuration values ``uz_PID_StateIDConfig_t`` and add all config values to this bus.
   * Add a new bus for the state-specific output/identification-values ``uz_PID_StateID_output_t`` and add all necessary values.
   * Open the ``uz_PID_GlobalConfig_t`` bus and add a new member with the name ``StateID``.
   * Open the ``uz_PID_ControlFlags_t`` bus and add a new member with the name ``startStateID``. If its an Online-state, add ``enableStateID``.

      .. image:: ../images/Bus_editor.png

   * Save the file by overwriting the old one. 

#. Add ``uz_PID_StateIDConfig_t`` as input and ``uz_PID_StateID_output_t`` as output to the new stateflow.
#. Select as type the newly created busses. 
#. Add the ``From`` block for the individual config bus in the appropriate color.

    .. image:: ../images/inputs_outputs2.png

#. Add the config setup ,similar to the other states, for this state in the subsystem called ``config`` at the top of the ParameterID. Don't forget to add the new entry to the ``GlobalConfig`` as well.

    .. image:: ../images/config_buscreator.png

#. Add the ``Go-to`` block subsystem to the appropriate output of the subsystem to connect to the already existing ``From`` block.
#. Add the corresponding ``From`` blocks for ``enteredStateID`` and ``finishedStateID`` to the ControlState as an input and adjust the colors.

    .. image:: ../images/ControlState_changes.png

#. Inside the ControlState create a new variable called ``finishedStateID_loc``.
#. Initialize it in the ``InitParams`` function similar to the other variables.
#. Add the passthrough of the ``StateID``-member of the GlobalConfig at the entry of the Superstate.

   * For OfflineID states
   
      * copy the three substates from another ``ID-state`` and adjust the variables.
   
         .. image:: ../images/ControlState_changes2.png

      * Open the ``decideIDstates`` function and adjust the code appropriately.

      .. code-block:: matlab
        :linenos:
        :caption: Addition to the decideIDstates function
    
        if(GlobalConfig_in.StateID==0)
            finishedStateID_loc=uint16(1);
        elseif(finishedStateID==1)
            finishedStateID_loc=uint16(2);    
        end
        %Determine path through the StateID-Stateflows
        if(GlobalConfig_in.StateID==1 && enteredStateID==0 && finishedElectricalID_loc~=0....
         && finishedTwoMassID_loc~=0 && finishedFrictionID_loc~=0 && finished FluxMapID_loc~=0 && finishedStateID_loc~=2 && finishedStateID==0)
               ControlFlags.transNr=uint16(5);
               finishedStateID_loc = uint16(0);
        end
        //Add the new stateID to the latest if-statement
        if(finishedElectricalID_loc~=0 && finishedTwoMassID_loc~=0 && ....
          finishedFrictionID_loc~=0 && finishedFluxMapID_loc~=0 && finishedStateID_loc ~=0)
            ControlFlags.finished_all_Offline_states = boolean(1);
        end
   * For OnlineID state
      
      * If its an OnlineID state, just add another if-else statement to the decideMotorID state
      
      .. code-block:: matlab
         :linenos:
         :caption: Addition to the decideIDstates function
    
         if(ControlFlags.finished_all_Offline_states == 1 && GlobalConfig_in.StateID==1 && enteredStateID==0)
            ControlFlags.enableStateID=boolean(1);
         elseif (ControlFlags.finished_all_Offline_states == 1 && GlobalConfig_in.StateID==0 && enteredStateID==1)
            ControlFlags.enableStateID=boolean(0);
         end

#. Add a superstate to the new state-flow.
#. Add a empty state next to the ``super state``. This will work as the ``idle state``.
#. Copy the transitions between the ``idle state`` and the ``super state`` from a different ``ID-state`` and adjust them according to the new state name. OfflineID and OnlineID states do have different transition conditions, so be wary, from which state you copy these.
#. Copy the ``initParams`` and the ``reset_FOC_output`` (if the struct :ref:`uz_Controller_parameters_struct` is used) and adjust them accordingly.
#. Now you can create substates in the ``super state`` and fill them with functionality/code.

   .. image:: ../images/stateID.png

#. If the :ref:`uz_Controller_parameters_struct` is used, add its corresponding ``From`` block to the FOC subsystem and adjust the code inside the function ``Busselector`` accordingly.
#. Add a new switch for the new stateflow to the already existing ones. 

    
Changes in the UltraZohm software
=================================

After code generating the stateflow the following changes have to be made in the UltraZohm software repository. 

#. Create a new subfolder in the ``Baremetal/src/uz/uz_ParameterID`` folder with the appropriate name.
#. Copy the code generated .h and .c file into this folder and rename them to ``StateID_codegen.c/h``.
#. Add the following changes to the .h file.

   .. code-block:: c
         :linenos:
         :caption: Changes made to the codegenerated header file

         #include "../../uz_global_configuration.h"
         #include "../uz_ParameterID_data.h"
         #if UZ_PARAMETERID_MAX_INSTANCES > 0U
         #include "../rtwtypes.h"

         //generated code

         #endif

#. Copy the individual structs (``uz_PID_StateIDConfig_t`` and ``uz_PID_StateID_output_t``) from the codegenerated header file ``StateID_codegen.h``. 
#. Paste them into the ``uz_ParameterID_data.h`` file, add doxygen comments and remove them from ``StateID_codegen.h``.
#. Compare the global structs (:ref:`uz_Actual_values_struct` , :ref:`uz_Global_config_struct` , :ref:`uz_Control_flags_struct` , :ref:`uz_Controller_parameters_struct`) in the codegenerated header file with the ones in the ``uz_ParameterID_data.h`` file and add the missing struct members to ``uz_ParameterID_data.h``. 
#. Remove the declaration of these global structs in the ``StateID_codegen.h`` file.
#. Add the following changes to the .c file

   .. code-block:: c
         :linenos:
         :caption: Changes made to the codegenerated source file

         #include "StateID_codegen.h"
         #if UZ_PARAMETERID_MAX_INSTANCES > 0U

         //generated code

         #endif

#. Add a new .h and .c file with the names ``uz_PID_StateID.c/h``.
#. Add the license header to the files.
#. Add the following code to the .h and .c file and adjust the names of the structs and functions accordingly.

   .. code-block:: c
         :linenos:
         :caption: Code for the new .h file

         #include "../../uz_global_configuration.h"
         #if UZ_PARAMETERID_MAX_INSTANCES > 0U
         #include <stdbool.h>
         #include "../../uz_HAL.h"
         #include "StateID_codegen.h"

         /**
         * @brief Object definition for uz_PID_StateID_t
         * 
         */
         typedef struct uz_PID_StateID_t{
	         ExtY_StateID_t output;
	         ExtU_StateID_t input;
	         DW_StateID_t rtDW; /* Observable states */
	         RT_MODEL_StateID_t modelData;
	         RT_MODEL_StateID_t *PtrToModelData;
         } uz_PID_StateID_t;
         
         /**
         * @brief Initializes the uz_PID_StateID_t object
         * 
         * @return uz_PID_StateID_t* pointer to object
         */
         uz_PID_StateID_t* uz_StateID_init(void);

         /**
         * @brief steps the StateID state once
         * 
         * @param self pointer to uz_PID_StateID_t* object
         */
         void uz_StateID_step(uz_PID_StateID_t *self);

         #endif

   .. code-block:: c
         :linenos:
         :caption: Code for the new .c file

         #include "../../uz_global_configuration.h"
         #if UZ_PARAMETERID_MAX_INSTANCES > 0U
         #include "uz_PID_StateID.h"

         static uint32_t instances_counter_PID_StateID = 0;

         static uz_PID_StateID_t instances_PID_StateID[UZ_PARAMETERID_MAX_INSTANCES] = { 0 };

         static uz_PID_StateID_t* uz_PID_StateID_allocation(void);

         static uz_PID_StateID_t* uz_PID_StateID_allocation(void) {
	         uz_assert(instances_counter_PID_StateID < UZ_PARAMETERID_MAX_INSTANCES);
	         uz_PID_ControlState_t* self = &instances_PID_StateID[instances_counter_PID_StateID];
	         instances_counter_PID_StateID++;
	         return (self);
         }

         uz_PID_StateID_t* uz_StateID_init(void) {
	         uz_PID_StateID_t* self = uz_PID_StateID_allocation();
	         self->PtrToModelData = &self->modelData;
	         self->PtrToModelData->dwork = &self->rtDW;
	         self->PtrToModelData->inputs = &self->input;
	         self->PtrToModelData->outputs = &self->output;
	         StateID_initialize(self->PtrToModelData);
	         return (self);
         }

         void uz_StateID_step(uz_PID_StateID_t *self) {
	         uz_assert_not_NULL(self);
	         StateID_step(self->PtrToModelData);
         }
         #endif


#. Include the ``uz_PID_StateID.h`` file to the ``uz_ParameterID.h`` file.
#. Add the new ``uz_PID_StateIDConfig_t`` and ``uz_PID_StateID_output_t`` to the :ref:`uz_ParameterID_Data_struct` in the ``uz_ParameterID_data.h`` file. Add the output struct as a pointer, similarly to the other output structs. 
#. Add default values for the config struct to the ``uz_ParameterID_initialize_data_structs`` function (like for the other states). Assign the address of the output struct here as well. 
#. Add the new state to the ``uz_ParameterID_t`` declaration and ``uz_ParameterID_init`` function.
#. Add a new static step function to the ``uz_ParameterID.c`` file, which wraps the assignment of inputs & outputs and step-function call.

   .. code-block:: c
         :linenos:
         :caption: Template code for static step function

         static void uz_PID_StateID_step(uz_ParameterID_t* self, uz_ParameterID_Data_t* Data) {
            //Update State-Inputs
            self->StateID->input.ActualValues = Data->ActualValues;
            self->StateID->input.StateIDConfig = Data->StateID_Config;
            self->StateID->input.GlobalConfig_out = self->ControlState->output.GlobalConfig_out;
            self->StateID->input.ControlFlags = self->ControlState->output.ControlFlags;

            //Step the function
            uz_StateID_step(self->StateID);

            //Update Control-State-inputs
            self->ControlState->input.enteredStateID = self->StateID->output.enteredStateID;
            self->ControlState->input.finishedStateID = self->StateID->output.finishedStateID;
         }

#. Add the step function to the ``uz_ParameterID_step`` function and change the names accordingly.

   * If it is designed as an Offline-state, use the following template. Adjust the transition number ``x`` accordingly. Add the new transition number to the switch-case accordingly.

      .. code-block:: c
         :linenos:
         :caption: Code for ``uz_ParameterID_step`` function for Offline-state. 

         //StateID
         if (self->ControlState->output.ControlFlags.transNr == xU || self->ControlState->output.GlobalConfig_out.Reset == true) {
            uz_PID_StateID_step(self, Data);
         } else if (self->ControlState->output.GlobalConfig_out.StateID == false && self->StateID->output.enteredStateID == true) {
            uz_PID_StateID_step(self, Data);
         }

         //
         switch (self->ControlState->output.ControlFlags.transNr) {

         ....
         //other cases
         ....
         case xU:
            Data->Controller_Parameters = self->StateID->output.StateID_FOC_output;
            break;
         .... 
         //Rest of code

   * If it is designed as an Online-state, use the following template:

      .. code-block:: c
         :linenos:
         :caption: Code for ``uz_ParameterID_step`` function for Online-state. 

         //StateID
         if (self->ControlState->output.ControlFlags.enableStateID == true || self->ControlState->output.GlobalConfig_out.Reset == true) {
            uz_PID_StateID_step(self, Data);
         }

#. All necessary changes are now done. Depending on your setup, respectively the purpose of the new ``ID-state``, it may be feasible to adjust the ``uz_ParameterID_Controller`` and ``uz_ParameterID_generate_DutyCycle`` functions. Otherwise write new functions for this.