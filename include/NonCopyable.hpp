#ifndef __NONCOPY__

#define __NONCOPY__

#include <iostream>

class NonCopyable
{
    public:
        NonCopyable() =                                 default;

        // deleting all copy/move ctrs and operators (no semantics)
        NonCopyable(const NonCopyable &) =              delete;
        NonCopyable(NonCopyable &&) =                   delete;
        
        NonCopyable& operator =(const NonCopyable &) =  delete;
        NonCopyable& operator ==(NonCopyable&&) =       delete;
};

#endif