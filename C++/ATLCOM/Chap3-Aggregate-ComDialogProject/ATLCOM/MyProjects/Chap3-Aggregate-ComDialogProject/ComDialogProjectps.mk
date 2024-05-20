
ComDialogProjectps.dll: dlldata.obj ComDialogProject_p.obj ComDialogProject_i.obj
	link /dll /out:ComDialogProjectps.dll /def:ComDialogProjectps.def /entry:DllMain dlldata.obj ComDialogProject_p.obj ComDialogProject_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ComDialogProjectps.dll
	@del ComDialogProjectps.lib
	@del ComDialogProjectps.exp
	@del dlldata.obj
	@del ComDialogProject_p.obj
	@del ComDialogProject_i.obj
