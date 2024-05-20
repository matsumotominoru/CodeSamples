
MsgMapsps.dll: dlldata.obj MsgMaps_p.obj MsgMaps_i.obj
	link /dll /out:MsgMapsps.dll /def:MsgMapsps.def /entry:DllMain dlldata.obj MsgMaps_p.obj MsgMaps_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del MsgMapsps.dll
	@del MsgMapsps.lib
	@del MsgMapsps.exp
	@del dlldata.obj
	@del MsgMaps_p.obj
	@del MsgMaps_i.obj
