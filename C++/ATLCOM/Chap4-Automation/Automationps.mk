
Automationps.dll: dlldata.obj Automation_p.obj Automation_i.obj
	link /dll /out:Automationps.dll /def:Automationps.def /entry:DllMain dlldata.obj Automation_p.obj Automation_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Automationps.dll
	@del Automationps.lib
	@del Automationps.exp
	@del dlldata.obj
	@del Automation_p.obj
	@del Automation_i.obj
