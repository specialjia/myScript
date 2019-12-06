
#ifndef __H__UTILS__H__
#define __H__UTILS__H__


#include "stdafx.h"

void logInit();
bool autoStartWhenPowerOn();  
bool findSpecificProcess(TCHAR *processName);
bool IsFileExist(TCHAR *csFile);
int createNewProcess(TCHAR *strPath);
bool inputString(TCHAR *str);
bool selectPart();
bool entrySelectPartWind();
bool autoLogIn();



bool getAllProcesses(vector<PROCESSENTRY32> &myvector);

#endif