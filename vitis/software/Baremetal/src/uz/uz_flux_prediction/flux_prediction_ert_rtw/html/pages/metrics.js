function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["flux_prediction_initialize"] = {file: "C:\\Users\\Philipp\\uz_temp\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\uz\\uz_flux_prediction\\flux_prediction_ert_rtw\\flux_prediction.c",
	stack: 12,
	stackTotal: 12};
	 this.metricsArray.fcn["flux_prediction_step"] = {file: "C:\\Users\\Philipp\\uz_temp\\ultrazohm_sw\\vitis\\software\\Baremetal\\src\\uz\\uz_flux_prediction\\flux_prediction_ert_rtw\\flux_prediction.c",
	stack: 12,
	stackTotal: 12};
	 this.metricsArray.fcn["memset"] = {file: "C:\\Program Files\\MATLAB\\R2023b\\polyspace\\verifier\\cxx\\include\\include-libc\\string.h",
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
	 this.codeMetricsSummary = '<a href="javascript:void(0)" onclick="return postParentWindowMessage({message:\'gotoReportPage\', pageName:\'flux_prediction_metrics\'});">Global Memory: 0(bytes) Maximum Stack: 12(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
