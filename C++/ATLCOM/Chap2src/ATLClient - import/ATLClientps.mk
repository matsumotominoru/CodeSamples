
ATLClientps.dll: dlldata.obj ATLClient_p.obj ATLClient_i.obj
	link /dll /out:ATLClientps.dll /def:ATLClientps.def /entry:DllMain dlldata.obj ATLClient_p.obj ATLClient_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ATLClientps.dll
	@del ATLClientps.lib
	@del ATLClientps.exp
	@del dlldata.obj
	@del ATLClient_p.obj
	@del ATLClient_i.obj
