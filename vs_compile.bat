@ECHO OFF
REM vs_compile.bat
REM Requires Visual Studio 2013 or 2015

SET ERRNO=0

IF EXIST "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\cl" (
  SET CC="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\cl"
  SET VARS="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
  ECHO Compiling with Visual Studio 2015
) ELSE IF EXIST "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\cl" (
  SET CC="C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\cl"
  SET VARS="C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"
  ECHO Compiling with Visual Studio 2013
) ELSE (
  ECHO Installation of Visual Studio 2013 or higher required.
  SET ERRNO=1
  CALL :ERR_EXIT
)
SET CFLAGS="/EHsc /W4"
CALL %VARS%
%CC% %CFLAGS% src\Main.cpp src\Server.cpp src\windows\ServerSocket.cpp src\ClientMap.cpp /link /out:server.exe
CALL :EOF

:ERR_EXIT
EXIT /B %ERRNO%

:EOF
CALL clean.bat