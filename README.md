# APT-POC

This is a simple APT POC program written in C programming for red team activities , this program records all the keystrokes and record them one file per application window. the program picks a random time to send mail with these data . All payloads are totally encrypted.This program isn't detected by most of antivirus vendors at the time of writing .<i>this program is for educational purpose only and the author is not liable for any kind misuse</i>.The program has the following features </br></br>
1- Simple anti sand boxing and anti-debugging techniques</br>
2- Payload encryption</br>
3- Key-logging</br>
4- In-memory Powershell execution</br> 
5- Persistence</br>
6- Hide TaskManager(needs Administrative privileges) and Process Hacker</br>
And much more</br>

<B>Requirements</B></br>

1- Build Tools for Visual Studio 2019 https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019</br>
2- Python 2.7  https://www.python.org/download/releases/2.7/</br>

<B>Program building steps</B></br>

1- Modify mail.ps1 with sender email credentials and TO email(If Gmail will be used as sender turn on Less secure app access setting)</br>
2- Excute encodemail.ps1</br>
3- Modify the variable ps_payload in prog.cpp with the encoded Powershell payload from the last step</br>
4- Execute compile.bat</br> 
5- Execute  decrypt.py prog.exe</br>
6- Copy the payload and modify the variable exe_payload in Dropper.cpp</br>
7- Execute compile.bat again , the resulting file is Dropper.exe</br>

<B>TO DO</B></br>

1- Add C2 support</br> 
2- Dynamic in-memory encrypted payload/binary files execution from the C2 server</br>


