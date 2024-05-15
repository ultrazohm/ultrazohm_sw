function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["cosf"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["fabsf"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["impl_modul_mpc.c:GradProj"] = {file: "C:\\GIT\\UltraZohm\\software\\ultrazohm_sw_3ph_impl_mod_ps\\vitis\\software\\Baremetal\\src\\Codegen\\impl_modul_mpc_ert_rtw\\impl_modul_mpc.c",
	stack: 3,
	stackTotal: 4};
	 this.metricsArray.fcn["impl_modul_mpc.c:P_omega"] = {file: "C:\\GIT\\UltraZohm\\software\\ultrazohm_sw_3ph_impl_mod_ps\\vitis\\software\\Baremetal\\src\\Codegen\\impl_modul_mpc_ert_rtw\\impl_modul_mpc.c",
	stack: 1,
	stackTotal: 1};
	 this.metricsArray.fcn["impl_modul_mpc.c:detect_unsuited_sequence_1"] = {file: "C:\\GIT\\UltraZohm\\software\\ultrazohm_sw_3ph_impl_mod_ps\\vitis\\software\\Baremetal\\src\\Codegen\\impl_modul_mpc_ert_rtw\\impl_modul_mpc.c",
	stack: 24,
	stackTotal: 24};
	 this.metricsArray.fcn["impl_modul_mpc.c:formulate_qp_1"] = {file: "C:\\GIT\\UltraZohm\\software\\ultrazohm_sw_3ph_impl_mod_ps\\vitis\\software\\Baremetal\\src\\Codegen\\impl_modul_mpc_ert_rtw\\impl_modul_mpc.c",
	stack: 48,
	stackTotal: 48};
	 this.metricsArray.fcn["impl_modul_mpc.c:state_space_mdl_1"] = {file: "C:\\GIT\\UltraZohm\\software\\ultrazohm_sw_3ph_impl_mod_ps\\vitis\\software\\Baremetal\\src\\Codegen\\impl_modul_mpc_ert_rtw\\impl_modul_mpc.c",
	stack: 52,
	stackTotal: 52};
	 this.metricsArray.fcn["impl_modul_mpc_initialize"] = {file: "C:\\GIT\\UltraZohm\\software\\ultrazohm_sw_3ph_impl_mod_ps\\vitis\\software\\Baremetal\\src\\Codegen\\impl_modul_mpc_ert_rtw\\impl_modul_mpc.c",
	stack: 12,
	stackTotal: 12};
	 this.metricsArray.fcn["impl_modul_mpc_step"] = {file: "C:\\GIT\\UltraZohm\\software\\ultrazohm_sw_3ph_impl_mod_ps\\vitis\\software\\Baremetal\\src\\Codegen\\impl_modul_mpc_ert_rtw\\impl_modul_mpc.c",
	stack: 18,
	stackTotal: 70};
	 this.metricsArray.fcn["memset"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\string.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["sinf"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data; }; 
	 this.codeMetricsSummary = '<a href="impl_modul_mpc_metrics.html">Global Memory: 0(bytes) Maximum Stack: 52(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
