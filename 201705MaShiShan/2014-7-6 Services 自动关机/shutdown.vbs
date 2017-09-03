wscript.sleep 1000
dim Obj
set Obj = createobject("wscript.shell")
Obj.exec "shutdown -s -t 0"