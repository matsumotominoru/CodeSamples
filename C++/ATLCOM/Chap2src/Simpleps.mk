
Simpleps.dll: dlldata.obj Simple_p.obj Simple_i.obj
	link /dll /out:Simpleps.dll /def:Simpleps.def /entry:DllMain dlldata.obj Simple_p.obj Simple_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Simpleps.dll
	@del Simpleps.lib
	@del Simpleps.exp
	@del dlldata.obj
	@del Simple_p.obj
	@del Simple_i.obj
