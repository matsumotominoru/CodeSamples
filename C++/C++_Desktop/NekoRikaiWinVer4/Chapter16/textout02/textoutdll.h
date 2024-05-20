// textoutdll.h

#ifdef __cplusplus
    #define EXPORT extern "C" __declspec(dllexport)
#else
    #define EXPORT __declspec(dllexport)
#endif

EXPORT BOOL MyTextOut(HDC, int, int, LPCTSTR);
