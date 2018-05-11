@ECHO OFF
ECHO Removing temporary files...

if /I "%1"=="all" (
  del /f *.obj server.exe
) ELSE (
  del /f *.obj
)