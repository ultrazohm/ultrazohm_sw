SLStudio.Utils.RemoveHighlighting(get_param('ADC_RAW_TO_VALUE', 'handle'));
SLStudio.Utils.RemoveHighlighting(get_param('gm_ADC_RAW_TO_VALUE', 'handle'));
annotate_port('gm_ADC_RAW_TO_VALUE/ADC_RAW_TO_VALUE/ProductConv', 0, 1, '');
annotate_port('gm_ADC_RAW_TO_VALUE/ADC_RAW_TO_VALUE/PipelineRegister', 1, 1, '');
annotate_port('gm_ADC_RAW_TO_VALUE/ADC_RAW_TO_VALUE/HwModeRegister', 0, 1, '');
