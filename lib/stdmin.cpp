#include <stdlib.h>

#ifdef _MSC_VER
#  define NEWDEL_CALL __cdecl
#else
#  define NEWDEL_CALL
#endif

extern "C" void __cdecl __gxx_personality_v0 ( void ) {
}

namespace __cxxabiv1 {
    class __class_type_info {
        virtual void dummy();
    };
    void __class_type_info::dummy() { }  // causes the vtable to get created here
};

extern "C" void __cxa_pure_virtual ()
{
    abort();
}

inline void* NEWDEL_CALL operator new (size_t n, void* ptr) {return ptr;}

void* NEWDEL_CALL operator new (size_t size)
{
    return malloc(size);
}

void* NEWDEL_CALL operator new [] (size_t size)
{
    return malloc(size);
}

void NEWDEL_CALL operator delete (void *p)
{
    if (p)
        free(p);
}

void NEWDEL_CALL operator delete [] (void *p)
{
    if (p)
        free(p);
}

void NEWDEL_CALL operator delete (void *p, size_t)
{
    if (p)
        free(p);
}


