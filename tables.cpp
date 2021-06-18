#include "structs.h"
#include "mem.h"
#include <assert.h>

#define HASH_MULTIPLIER 65599

Table::Table() {
    this->ref_counter = 0;

    initBuckets(str_indexed);
    initBuckets(num_indexed);
}

void Table::initBuckets(bucket **t) {
    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; i++) {
        t[i] = (bucket *)0;
    }
}

void Table::destroyBuckets(bucket **t) {
    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; i++, ++t) {
        for (bucket *b = *t; b;) {
            bucket *del = b;
            b = b->next;
            memclear::clcell(&del->key);
            memclear::clcell(&del->value);
            free(del);
        }
        t[i] = (bucket *)0;
    }
}

void Table::incRefCounter() {
    ++this->ref_counter;
}

void Table::decRefCounter() {
    if (!--this->ref_counter)
        this->destroy();
}

void Table::destroy() {
    this->destroyBuckets(this->str_indexed);
    this->destroyBuckets(this->num_indexed);
}

unsigned Table::hash(AVM_memcell *key) {
    size_t i;
    unsigned int sum = 0;
    char *str;

    using namespace AVM_memcell_t;
    switch (key->type) {
    case number_m:

        sum = key->data.numVal * HASH_MULTIPLIER;

        break;
    case string_m:
        str = key->data.strVal;

        for (i = 0; i < strlen(str); i++) {
            sum = sum * HASH_MULTIPLIER + str[i];
        }
        break;
    default:
        assert(0);
    }


    return sum % AVM_TABLE_HASHSIZE;
}

bucket **Table::getTable(AVM_memcell *key) {
    using namespace AVM_memcell_t;

    switch (key->type) {
    case number_m:
        return this->num_indexed;
        break;
    case string_m:
        return this->str_indexed;
        break;
    default:
        assert(0);
    }
    return (bucket **)0;
}

bool keycmp(AVM_memcell *key1, AVM_memcell *key2) {
    using namespace AVM_memcell_t;

    switch (key1->type) {
    case number_m:
        if (key1->data.numVal == key2->data.numVal)
            return true;
        else
            return false;
        break;
    case string_m:
        if (strcmp(key1->data.strVal, key2->data.strVal) == 0)
            return true;
        else
            return false;
        break;
    default:
        assert(0);
    }
    return false;
}

AVM_memcell *Table::getElem(AVM_memcell *key) {
    bucket **table;
    int h;

    table = this->getTable(key);

    h = this->hash(key);

    bucket *iter = table[h];

    while (iter) {

        if (keycmp(&iter->key, key)) {
            return &iter->value;
        }

        iter = iter->next;
    }

    return 0;
}

void Table::setElem(AVM_memcell *key, AVM_memcell *value) {
    bucket **table;
    bucket *newnode;
    int h;

    table = this->getTable(key);

    h = this->hash(key);

    bucket *iter = table[h];

    if (!iter) {
        table[h] = (bucket *)malloc(sizeof(bucket));
        memcpy(&table[h]->key, key, sizeof(bucket));
        memcpy(&table[h]->value, value, sizeof(bucket));
        table[h]->next = (bucket *)0;
        return;
    }

    while (iter->next) {
        iter = iter->next;
    }

    iter->next = (bucket *)malloc(sizeof(bucket));
    iter->next->key = *key;
    iter->next->value = *value;
    iter->next->next = (bucket *)0;

    return;
}