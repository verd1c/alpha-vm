#ifndef __STRUCTS__
#define __STRUCTS__

#define AVM_STACKSIZE   4096
#define AVM_TABLE_HASHSIZE 211

class Table;

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
union data_t {
    double numVal;
    char *strVal;
    unsigned char boolVar;
    Table *tableVal;
    unsigned funcVal;
    char *libfuncVal;
};

struct AVM_memcell {
    AVM_memcell_t::AVM_memcell_t type;

    data_t data;
};

struct bucket {
    AVM_memcell key;
    AVM_memcell value;
    struct bucket *next;
};


class Table {
public:
    unsigned ref_counter;
    unsigned total;

    /* indexes */
    bucket *str_indexed[AVM_TABLE_HASHSIZE];
    bucket *num_indexed[AVM_TABLE_HASHSIZE];

    Table();

    void initBuckets(bucket **t);
    void destroyBuckets(bucket **t);

    AVM_memcell *getElem(AVM_memcell *key);
    void setElem(AVM_memcell *key, AVM_memcell *value);

    void incRefCounter();
    void decRefCounter();
    void destroy();
    bucket **getTable(AVM_memcell *key);

    /* hashing */
    unsigned hash(AVM_memcell *key);
};

class AVMStack {
public:
    AVM_memcell stack[AVM_STACKSIZE];
    AVMStack();
};

#endif