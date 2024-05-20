
URLTreeps.dll: dlldata.obj URLTree_p.obj URLTree_i.obj
	link /dll /out:URLTreeps.dll /def:URLTreeps.def /entry:DllMain dlldata.obj URLTree_p.obj URLTree_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del URLTreeps.dll
	@del URLTreeps.lib
	@del URLTreeps.exp
	@del dlldata.obj
	@del URLTree_p.obj
	@del URLTree_i.obj
