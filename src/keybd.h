#ifndef __KEYBD__H__
#define __KEYBD__H__
// for testing
#include "stdafx.h"

#define PRESSKEY(x)   press_key(x)

#define PRESS(x) press(x); log_trace("Press %d ",x);
#define RELEASE(x) release(x); log_trace("Release %d ",x);
BYTE scan_code(DWORD pKey);
void press(DWORD pKey);
void release(DWORD pKey);
void press_key(DWORD pKey);


#endif