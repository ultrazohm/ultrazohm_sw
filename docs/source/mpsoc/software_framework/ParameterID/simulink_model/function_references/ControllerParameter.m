function [FOC_out_new] = ControllerParameter(FOC_out_old,bandwidthCurrentControl,PMSM_config,damping,psiOverJ)
    FOC_out_new = FOC_out_old;
    FOC_out_new.Kp_id_out = single(PMSM_config.Ld_Henry * bandwidthCurrentControl);
    FOC_out_new.Kp_iq_out = single(PMSM_config.Lq_Henry * bandwidthCurrentControl);
    FOC_out_new.Ki_id_out = single(PMSM_config.R_ph_Ohm * bandwidthCurrentControl);
    FOC_out_new.Ki_iq_out = single(FOC_out_new.Ki_id_out);
    FOC_out_new.Kp_n_out = single(FOC_out_new.Ki_iq_out/(PMSM_config.Lq_Henry*damping*PMSM_config.polePairs*3.0/2.0*psiOverJ));
    FOC_out_new.Ki_n_out = single((FOC_out_new.Ki_iq_out)^2 / ((PMSM_config.Lq_Henry)^2 * damping^3 * PMSM_config.polePairs*3.0/2.0*psiOverJ));
end