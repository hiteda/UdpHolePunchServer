REM windows_compile.bat
REM Requires Visual Studio 2013

SET CC="C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\cl"
SET CFLAGS="/EHsc /W4"
CALL "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"
%CC% %CFLAGS% src\Main.cpp src\Server.cpp src\ServerSocket.cpp src\ClientMap.cpp /link /out:server.exe