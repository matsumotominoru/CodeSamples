
Propertiesps.dll: dlldata.obj Properties_p.obj Properties_i.obj
	link /dll /out:Propertiesps.dll /def:Propertiesps.def /entry:DllMain dlldata.obj Properties_p.obj Properties_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Propertiesps.dll
	@del Propertiesps.lib
	@del Propertiesps.exp
	@del dlldata.obj
	@del Properties_p.obj
	@del Properties_i.obj
