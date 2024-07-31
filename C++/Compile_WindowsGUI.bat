rem At CodeSamples\C++\C++_Desktop\StdWinAPI32\5.MessageBox\StdWinAPI32_5_MessageBox
cl.exe /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" StdWinAPI32_5_MessageBox.cpp /link user32.lib kernel32.lib

rem At CodeSamples\C++\C++_Desktop\NekoRikaiWinVer4\Chapter10\dialog01
rc.exe /v Resource.rc
rem This requires rc file encoded in cp932 (SJIS). Also requires system locale on the control panel set to cp932 (Japanese)?
rc.exe /v /l1041 /c932 dialog01.rc
cl.exe /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" dialog01.cpp Resource.res /link user32.lib kernel32.lib Gdi32.lib
