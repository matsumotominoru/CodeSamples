
BUObjectps.dll: dlldata.obj BUObject_p.obj BUObject_i.obj
	link /dll /out:BUObjectps.dll /def:BUObjectps.def /entry:DllMain dlldata.obj BUObject_p.obj BUObject_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del BUObjectps.dll
	@del BUObjectps.lib
	@del BUObjectps.exp
	@del dlldata.obj
	@del BUObject_p.obj
	@del BUObject_i.obj
