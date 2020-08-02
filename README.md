# APT-POC
This is a simple APT POC program written in C programming for red team activities , this program collects all the keystrokes and record them one file per application window and sends mail with these data at random time. All payloads are totally encrypted, it bypassed most of antivirus vendors at the time of writing . the program has the following features </br></br>
1- simple anti sand boxing and anti-debugging techniques</br>
2- Payload encryption</br>
3- Key-logging</br>
4- In-memory Powershell execution</br> 
5- Persistence</br> 
and much more</br>

<B>Requirements</B></br>

1- Build Tools for Visual Studio 2019 https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019</br>
2- Python 2.7  https://www.python.org/download/releases/2.7/</br>

<B>Progam building steps</B></br>

1- Modify mail.ps1 with sender email credentials and to mail(If Gmail will be used as sender turn on Less secure app access setting)</br>
2- Excute encodemail.ps1</br>
3 - Modify the variable ps_payload in prog.cpp with the encoded Powershell payload from the last step</br>
4- Execute compile.bat</br> 
5- Execute  decrypt.py prog.exe</br>
6- Copy the payload and modify the variable exe_payload in Dropper.cpp</br>
7- Execute compile.bat again , the resulting file is Dropper.exe</br>
<B>TO DO</B></br>
1- Add C2C support</br> 
2- Dynamic in-memory encrypted payload/binary files execution from the C2C</br>


