
EventCtrlps.dll: dlldata.obj EventCtrl_p.obj EventCtrl_i.obj
	link /dll /out:EventCtrlps.dll /def:EventCtrlps.def /entry:DllMain dlldata.obj EventCtrl_p.obj EventCtrl_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EventCtrlps.dll
	@del EventCtrlps.lib
	@del EventCtrlps.exp
	@del dlldata.obj
	@del EventCtrl_p.obj
	@del EventCtrl_i.obj
