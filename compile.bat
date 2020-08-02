@ECHO OFF


cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /TcDropper.cpp /link /OUT:Dropper.exe /SUBSYSTEM:CONSOLE /MACHINE:x64
cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tcprog.cpp /link /OUT:prog.exe /SUBSYSTEM:CONSOLE /MACHINE:x64
signtool sign /v /f MySPC.pfx  /t http://timestamp.verisign.com/scripts/timstamp.dll prog.exe
signtool sign /v /f MySPC.pfx  /t http://timestamp.verisign.com/scripts/timstamp.dll dropper.exe