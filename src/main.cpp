
#include "keybd.h"
#include "utils.h"
#include "stdafx.h"

//hide dos window
//#pragma comment(linker,"/subsystem:\"windows\"  /entry:\"mainCRTStartup\"" ) 

int _tmain()
{
	logInit();	
	if (!autoStartWhenPowerOn())
	{
		log_trace("auto Start failed !");		
		return -1;
	}
	autoLogIn();
	return 0;

}