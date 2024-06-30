#ifdef __cplusplus
#define DLL_EXPORT extern "C" __declspec (dllexport)
#else 
#define DLL_EXPORT __declspec (dllexport)
#endif

DLL_EXPORT BOOL CALLBACK GetCenter(LPRECT , LPRECT);
