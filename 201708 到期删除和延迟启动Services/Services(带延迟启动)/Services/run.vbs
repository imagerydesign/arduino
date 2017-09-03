specifyDate="2017-10-16"
strAppCommandLineA = "C:\Services\relay.vbs"  
strAppCommandLineB = "C:\Services\del.bat"     
Set objShell = CreateObject("Wscript.Shell") 
If CDate(year(Now)&"-"&Month(Now)&"-"&day(Now)) > CDate(specifyDate)  Then
	strCommandLine = strAppCommandLineB    
Else
	strCommandLine = strAppCommandLineA     
End If
objShell.Run(strCommandLine) 
Set objShell =Nothing