#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main()
{
	LPTCH pEv = GetEnvironmentStrings();
	LPTSTR szEnvs;
	
	for (szEnvs = (LPTSTR)pEv; *szEnvs;) {
		wprintf(_T("%s\n"), szEnvs);
		while (*szEnvs++);
	}

	FreeEnvironmentStrings(pEv);
	system("pause");
	return 0;
}