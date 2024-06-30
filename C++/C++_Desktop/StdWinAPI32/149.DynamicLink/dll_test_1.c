#include <windows.h>

#define PRC_ATT TEXT("DLL が読み込まれました")
#define PRC_DET TEXT("DLL が解放されました")
#define TRD_ATT TEXT("既存プロセスが新しいスレッドを作成しています")
#define TRD_DET TEXT("既存のスレッドが終了しようとしています")

#define TITLE TEXT("Kitty on your lap")

int WINAPI DllEntryPoint(HINSTANCE hInstance , DWORD fdwReason , PVOID pvReserved) {
    switch(fdwReason) {
    case DLL_PROCESS_ATTACH:
        MessageBox(NULL , PRC_ATT , TITLE , MB_OK);
        break;
    case DLL_PROCESS_DETACH:
        MessageBox(NULL , PRC_DET , TITLE , MB_OK);
        break;
    case DLL_THREAD_ATTACH:
        MessageBox(NULL , TRD_ATT , TITLE , MB_OK);
        break;
    case DLL_THREAD_DETACH:
        MessageBox(NULL , TRD_DET , TITLE , MB_OK);
    }
    return TRUE;
}
