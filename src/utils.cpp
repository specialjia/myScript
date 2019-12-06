
#include "utils.h"


void logInit()
{
	FILE *fp = fopen("./protectedlog.txt", "wt+");
	if (fp == nullptr)
	{
		MessageBox(NULL, _TEXT("create log file failed !"), _TEXT("tip"), 0);
	}
	log_set_fp(fp);
	log_set_quiet(true);

}
bool autoStartWhenPowerOn()
{
	HKEY hKey;
	TCHAR pName[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, pName, MAX_PATH);

	
	LONG lRet = NULL;
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, SELFSTART_REGEDIT_PATH, 0, KEY_ALL_ACCESS, &hKey);

	
	if (lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	lRet = RegSetValueEx(hKey, _TEXT("testProtect"), 0, REG_SZ, (LPBYTE)(LPCTSTR)pName, (lstrlen(pName) + 1) * sizeof(TCHAR));

	
	if (lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	
	RegCloseKey(hKey);
	return TRUE;
}



bool getAllProcesses(vector<PROCESSENTRY32> &myvector)
{
	bool ret = false;
	HANDLE hSnap;
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);
	BOOL bResult = Process32First(hSnap, &pe);
	while (bResult)
	{
		log_trace("processName = %s processID = %d ", pe.szExeFile,pe.th32ProcessID);
		myvector.push_back(pe);
		bResult = Process32Next(hSnap, &pe);
	}

	CloseHandle(hSnap);
	return true;
}

bool findSpecificProcess(TCHAR *processName)
{

	vector<PROCESSENTRY32> vProcesses;
	getAllProcesses(vProcesses);
	vector<PROCESSENTRY32>::iterator it = vProcesses.begin();
	for (; it != vProcesses.end(); it++)
	{
		log_trace("processName = %s ", it->szExeFile);
		if (!_tcscmp(processName, it->szExeFile))
		{
			return true;
		}
	}
	return false;
}


bool IsFileExist(TCHAR *csFile)
{
	DWORD dwAttrib = GetFileAttributes(csFile);
	return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}


int createNewProcess(TCHAR *strPath)
{
	PROCESS_INFORMATION  pro_id;
	::ZeroMemory(&pro_id, sizeof(PROCESS_INFORMATION));
	STARTUPINFO  str_inf;
	::ZeroMemory(&str_inf, sizeof(STARTUPINFO));
	str_inf.cb = sizeof(STARTUPINFO);
	str_inf.dwFlags = STARTF_USESHOWWINDOW;
	str_inf.wShowWindow = SW_SHOW;
	int ret_code = CreateProcess(
		strPath,
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&str_inf,
		&pro_id
		);

	::CloseHandle(pro_id.hThread);
	::CloseHandle(pro_id.hProcess);

	return ret_code;
}


bool inputString(TCHAR *str)
{
	short nKeyR = 0;
	for (int i = 0; i < _tcslen(str); i++)
	{
		if (str[i] >= _TEXT('a') && str[i] <= _TEXT('z'))
		{
			nKeyR = GetKeyState(VK_CAPITAL);
			if (nKeyR)
			{
				PRESS(VK_CAPITAL);
				Sleep(100);
				RELEASE(VK_CAPITAL);
			}
			Sleep(100);
			PRESS(str[i] + 'A' - 'a');
			Sleep(100);
			RELEASE(str[i] + 'A' - 'a');
		}
		if (str[i] >= _TEXT('A') && str[i] <= _TEXT('Z'))
		{
			nKeyR = GetKeyState(VK_CAPITAL);
			if (!nKeyR)
			{
				PRESS(VK_CAPITAL);
				Sleep(100);
				RELEASE(VK_CAPITAL);
			}
			Sleep(100);
			PRESS(str[i]);
			Sleep(100);
			RELEASE(str[i]);
		}
		if (str[i] >= _TEXT('0') && str[i] <= _TEXT('9'))
		{
			Sleep(100);
			PRESS(str[i]);
			Sleep(100);
			RELEASE(str[i]);
		}

	}

	return true;
}


bool selectPart()
{
	int x = 129;
	int y = 139;
	HWND h = FindWindow(_TEXT("#32770"), NULL);
	if (h == NULL)
	{
		cout << "²éÕÒ#32770(¶Ô»°¿ò)Ê§°Ü" << endl;
		return false;
	}
	CRect r1;
	GetWindowRect(h, &r1);

	SetCursorPos(x + r1.left, y + r1.top);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	x = 498;
	y = 171;

	Sleep(2000);
	SetCursorPos(x + r1.left, y + r1.top);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	return true;

}


bool entrySelectPartWind()
{
	int x = 521;
	int y = 688;
	HWND h = FindWindow(NULL, _TEXT("ÓÎÏ·µÇÂ½Æ÷"));
	if (h == NULL)
	{
		log_trace("search game log window failed!");

		return false;
	}
	CRect r1;
	GetWindowRect(h, &r1);
	x += r1.left;
	y += r1.top;
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	return true;
}


bool autoLogIn()
{
	do {
		if (findSpecificProcess(PROCCESS_NAME))
		{
			if (IsFileExist(PROCESS_EXE_PATH))
			{
				if (!createNewProcess(PROCESS_EXE_PATH))
				{
					log_trace("create process failed!");
					return -1;
				}
				Sleep(10000);
				if (!entrySelectPartWind())
				{
					log_trace("entrySelectPartWind failed!");
					return -1;
				}
				Sleep(9000);
				if (!selectPart())
				{
					log_trace("selPart failed!");
					return -1;
				}
				Sleep(2000);
				inputString(ACCOUNT);
				PRESSKEY(VK_TAB);
				inputString(PASSWORD);
				PRESSKEY(VK_TAB);
				Sleep(100);
				PRESSKEY(VK_RETURN);
			}
			else
			{
				log_trace("can not find protected application");
			}
		}
		else
		{
			log_trace("protected application is runing !");
		}
		Sleep(5000);
	} while (true);

	return TRUE;
}

