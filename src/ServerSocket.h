// Retrieves the correct OS-dependent header

#if defined (_WIN32)
  #include "windows/ServerSocket.h"
#elif defined (__linux__) || defined (__unix__) || defined (__posix__)
  #include "posix/ServerSocket.h"
#endif