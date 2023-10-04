function RTW_SidParentMap() {
    this.sidParentMap = new Array();
    this.sidParentMap["uz_mpc_3ph:2858"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2859"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2860"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2861"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2876"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2877"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2878"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2879"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2890"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2892"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2899"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2900"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2901"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2902"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2903"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2908"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2909"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2917"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2918"] = "uz_mpc_3ph:2857";
    this.sidParentMap["uz_mpc_3ph:2926"] = "uz_mpc_3ph:2857";
    this.getParentSid = function(sid) { return this.sidParentMap[sid];}
}
    RTW_SidParentMap.instance = new RTW_SidParentMap();
