#include <stdio.h>
#include <windows.h>
#include <TlHelp32.h>
#include <stdlib.h>

int Kill_Pro(TCHAR Kill_Name[]) {
	HANDLE hSnapshort=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hSnapshort==INVALID_HANDLE_VALUE) {
		printf("CreateToolhelp32Snapshot failed!\n");
		return -1;
	}
	PROCESSENTRY32 stcProcessInfo;
	stcProcessInfo.dwSize=sizeof(stcProcessInfo);
	BOOL bRet=Process32First(hSnapshort,&stcProcessInfo);
	while(bRet) {
		if(!strcmp(stcProcessInfo.szExeFile,Kill_Name)) {
			HANDLE hProcess=::OpenProcess(PROCESS_TERMINATE,FALSE,stcProcessInfo.th32ProcessID);
			::TerminateProcess(hProcess,0);
			CloseHandle(hProcess);
		}
		bRet=Process32Next(hSnapshort,&stcProcessInfo);
	}
	CloseHandle(hSnapshort);
	return 0;
}

int Check_Pro(TCHAR Check_Name[]) {
	HANDLE hSnapshort=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hSnapshort==INVALID_HANDLE_VALUE) {
		printf("CreateToolhelp32Snapshot failed!\n");
		return -1;
	}
	PROCESSENTRY32 stcProcessInfo;
	stcProcessInfo.dwSize=sizeof(stcProcessInfo);
	BOOL bRet=Process32First(hSnapshort,&stcProcessInfo);
	while(bRet) {
		if(!strcmp(stcProcessInfo.szExeFile,Check_Name))
			return 1;
		bRet=Process32Next(hSnapshort,&stcProcessInfo);
	}
	CloseHandle(hSnapshort);
	return 0;
}

int main(void) {
	puts("Killing jy");
	while(Check_Pro("StudentMain.exe")) {
		Kill_Pro("StudentMain.exe");
	}
	puts("jfglzs has been killed!");
	return 0;
}
