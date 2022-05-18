#include "uz_PushButton_facade.h"

static uz_PushButton PBEnableSystem;
static uz_PushButton PBEnableControl;
static uz_PushButton PBStop;

void uz_PushButton_facade_init(uz_PushButtonFacadeCfg cfg)
{
	uz_PushBotton_init(&PBEnableSystem, (cfg.EnableSystem));
	uz_PushBotton_init(&PBEnableControl, (cfg.EnableControl));
	uz_PushBotton_init(&PBStop, (cfg.Stop));
}

_Bool uz_GetPushButtonStop()
{
	return (uz_PushButton_GetValue(&PBStop));
}

_Bool uz_GetPushButtonEnableSystem()
{
	return (uz_PushButton_GetValue(&PBEnableSystem));
}

_Bool uz_GetPushButtonEnableControl()
{
	return uz_PushButton_GetValue(&PBEnableControl);
}
