#include "uz_PushButton_facade.h"

static uz_PushButton PBEnableSystem;
static uz_PushButton PBEnableControl;
static uz_PushButton PBStop;

void uz_PushButton_facade_init(uz_PushButtonFacadeCfg cfg){
	uz_PushBotton_init(&PBEnableSystem,(cfg.EnableSystem) );
	uz_PushBotton_init(&PBEnableControl,(cfg.EnableControl) );
	uz_PushBotton_init(&PBStop,(cfg.Stop) );
}

_Bool uz_GetPushButtonStop(){
	_Bool Value;
	Value=PBStop.GetValue(&PBStop);
	return (Value);
};

_Bool uz_GetPushButtonEnableSystem(){
	_Bool Value;
	Value=PBEnableSystem.GetValue(&PBEnableSystem);
	return (Value);
};

_Bool uz_GetPushButtonEnableControl(){
	_Bool Value;
	Value=PBEnableControl.GetValue(&PBEnableControl);
	return (Value);
};
