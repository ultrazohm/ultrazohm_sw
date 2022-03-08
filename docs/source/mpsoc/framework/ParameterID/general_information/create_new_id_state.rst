.. _uz_PID_new_ID_state:

==============================
Guide to create a new ID-state
==============================

The current ``ID-states`` carry a wide range of identification methods. 
However, if a new identification method is supposed to be implemented, this guide will assist in creating a new ``ID-state``.
Before starting the procedure of creating a new state, it is advised to read up about the general concept and layout of the ParmeterID in :ref:`uz_PID_general_information`, :ref:`uz_ParameterID_Data_structs` and :ref:`uz_PID_new_control_algorithm`.

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

#. Add the config setup ,similar to the other states, for this state in the subsystem called ``config`` at the top of the ParameterID.

    .. image:: ../images/config_buscreator.png

#. Add the ``Go-to`` block subsystem to the appropriate output of the subsystem to connect to the already existing ``From`` block.
#. Add the corresponding ``From`` blocks for ``enteredStateID`` and ``finishedStateID`` to the ControlState as an input and adjust the colors.

    .. image:: ../images/ControlState_changes.png

#. Inside the ControlState create a new variable called ``finishedStateID_loc``.
#. Initialize it in the ``InitParams`` function similar to the other variables.
#. Add the passthrough of the ``StateID``-member of the GlobalConfig at the entry of the Superstate.

   * For OfflineID states
   
      * copy the three substates from another ``ID-state`` and adjust the variables.
      * If its an OnlineID state, just add another if-else statement to the decideMotorID state, similar to the OnlineID 
   
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

    