
EventWatcherps.dll: dlldata.obj EventWatcher_p.obj EventWatcher_i.obj
	link /dll /out:EventWatcherps.dll /def:EventWatcherps.def /entry:DllMain dlldata.obj EventWatcher_p.obj EventWatcher_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EventWatcherps.dll
	@del EventWatcherps.lib
	@del EventWatcherps.exp
	@del dlldata.obj
	@del EventWatcher_p.obj
	@del EventWatcher_i.obj
