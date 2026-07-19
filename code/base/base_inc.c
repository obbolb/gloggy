#include "base.c"

#if OS_LINUX == 1
#include "base_linux.c"
#else
#error "os not supported yet"
#endif
