specifyDate="2014-7-6"
strAppCommandLineA = "relay.vbs"  
strAppCommandLineB = "shutdown.vbs"     
Set objShell = CreateObject("Wscript.Shell") 
If CDate(year(Now)&"-"&Month(Now)&"-"&day(Now)) > CDate(specifyDate)  Then
	strCommandLine = strAppCommandLineB    
Else
	strCommandLine = strAppCommandLineA     
End If
objShell.Run(strCommandLine) 
Set objShell =Nothing