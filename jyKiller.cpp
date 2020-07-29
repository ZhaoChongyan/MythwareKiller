/*
 * This program is created by ZhaoChongyan.
 * This program is used for destroy Jifangguanlizhushou, A useless, disgusting malware software.
 * The malware software is hard-opposing. So I created this program to solve the problem.
 */
#include <cstdlib>
#include <windows.h>
#include <TlHelp32.h>
#include <queue>
using namespace std;

int main(void) {
	HANDLE hSnapshort = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshort == INVALID_HANDLE_VALUE) {
		/*
		 * Cannot creat a HANDLE!!!
		 */
		throw "CreateToolhelp32Snapshot failed!\n";
		return -1;
	}
	queue<HANDLE> proList;
	bool finished = false; 
	do {
		finished = true;
		PROCESSENTRY32 stcProcessInfo;
		stcProcessInfo.dwSize = sizeof(stcProcessInfo);
		BOOL bRet = Process32First(hSnapshort, &stcProcessInfo);
		while(bRet) {
			/*
			 * Add the process to the list.
			 */
			if(!strcmp(stcProcessInfo.szExeFile, "StudentMain.exe")) {
				proList.push(::OpenProcess(PROCESS_TERMINATE, FALSE, stcProcessInfo.th32ProcessID));
			}
			bRet = Process32Next(hSnapshort, &stcProcessInfo);
		}
		while (proList.size()) {
			/*
			 * Abort the process in the list.
			 */
			if (!(::TerminateProcess(proList.front(), 0))) {
				/*
				 * Fail to abort the malware process.
				 */
				finished = false;
			}
			CloseHandle(proList.front());
			proList.pop();
		}
	} while(!finished);
	CloseHandle(hSnapshort);
	return 0;
}
