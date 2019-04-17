
for /L %%n in (1,1,66) do (
	start /d "C:\Users\PhungVanHoang\source\repos\tryDDoS\Debug" tryDDoS.exe
	)	

IF %ERRORLEVEL% NEQ 0 (
  ECHO %ERRORLEVEL%
)

EXIT