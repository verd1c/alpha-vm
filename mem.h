#ifndef __MEM__
#define __MEM__

#include <vector>
#include <stack>
#include "vmarg.h"

#define AVM_STACKSIZE   4096
#define AVM_WIPEOUT(m)  memset(&(m), 0, sizeof(m))

namespace AVM_memcell_t {
    enum AVM_memcell_t {
        number_m,
        string_m,
        bool_m,
        table_m,
        userfunc_m,
        libfunc_m,
        nil_m,
        undef_m
    };
}

enum AVM_table;

struct AVM_memcell {
    AVM_memcell_t::AVM_memcell_t type;

    union data {
        double numVal;
        char *strVal;
        unsigned char boolVar;
        struct avm_table *tableVal;
        unsigned funcVal;
        char *libfuncVal;
    };
};

class AVMStack {
public:
    AVM_memcell stack[AVM_STACKSIZE];
    AVMStack();
};

#endif