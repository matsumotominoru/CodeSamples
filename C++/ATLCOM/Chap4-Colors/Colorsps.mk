
Colorsps.dll: dlldata.obj Colors_p.obj Colors_i.obj
	link /dll /out:Colorsps.dll /def:Colorsps.def /entry:DllMain dlldata.obj Colors_p.obj Colors_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Colorsps.dll
	@del Colorsps.lib
	@del Colorsps.exp
	@del dlldata.obj
	@del Colors_p.obj
	@del Colors_i.obj
