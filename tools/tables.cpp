#include "../tools.h"
#include "../mem.h"
#include "assert.h"
#include <cstring>
#include <iostream>

AVM_table *tables::new_table(void)
{

    AVM_table *t = (AVM_table *)malloc(sizeof(AVM_table));
    AVM_WIPEOUT(*t);

    t->ref_counter = t->total = 0;
    tables::init_table_buckets(t->numIndexed);
    tables::init_table_buckets(t->strIndexed);

    return t;
}

void tables::init_table_buckets(AVM_table_bucket **p)
{

    unsigned int i = 0;

    for (i = 0; i < AVM_TABLE_HASHSIZE; ++i)
    {
        p[i] = (AVM_table_bucket *)0;
    }
}

void refcounter_increase(AVM_table *t)
{

    ++t->ref_counter;
}

AVM_memcell *tablegetelem(AVM_table *table, AVM_memcell *index)
{

    assert(table);

    int indexOfTable;

    if (index->type == AVM_memcell_t::string_m)
    {

        indexOfTable = (int)strlen(index->data.strVal) % AVM_TABLE_HASHSIZE;

        if (table->strIndexed[indexOfTable] != NULL)
        {
            AVM_table_bucket *tmp = table->strIndexed[indexOfTable];
            while (tmp != NULL)
            {
                if (strcmp(tmp->key.data.strVal, index->data.strVal) == 0)
                    return &tmp->value;

                tmp = tmp->next;
            }
        }
    }
    else if (index->type == AVM_memcell_t::number_m)
    {

        indexOfTable = (int)index->data.numVal % AVM_TABLE_HASHSIZE;

        if (table->numIndexed[indexOfTable] != NULL)
        {
            AVM_table_bucket *tmp = table->numIndexed[indexOfTable];
            while (tmp != NULL)
            {
                if (tmp->key.data.numVal == index->data.numVal)
                    return &tmp->value;

                tmp = tmp->next;
            }
        }
    }
    return NULL;
}

void tablesetelem(AVM_table *table, AVM_memcell *index, AVM_memcell *value)
{

    assert(table);

    int tindex;

    AVM_memcell *elem = tablegetelem(table, index);

    if (index->type == AVM_memcell_t::string_m)
    {

        tindex = (int)strlen(index->data.strVal) % AVM_TABLE_HASHSIZE;
        if (elem != NULL)
        {
            mem::assign(elem, value);
            return;
        }

        if (table->strIndexed[tindex] == NULL)
        {

            table->strIndexed[tindex] = (AVM_table_bucket *)malloc(sizeof(AVM_table_bucket));

            AVM_table_bucket *new_b = (AVM_table_bucket *)malloc(sizeof(AVM_table_bucket));
            new_b->key = *index;

            if (value->type == AVM_memcell_t::table_m)
            {
                refcounter_increase(value->data.tableVal);
            }

            new_b->value = *value;
            table->strIndexed[tindex] = new_b;
            table->strIndexed[tindex]->next = NULL;
            table->total++;

            return;
        }

        AVM_table_bucket *tmp = table->strIndexed[tindex];
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }

        AVM_table_bucket *new_b = (AVM_table_bucket *)malloc(sizeof(AVM_table_bucket));
        new_b->key = *index;

        if (value->type == AVM_memcell_t::table_m)
        {
            refcounter_increase(value->data.tableVal);
        }

        new_b->value = *value;
        tmp->next = new_b;
        new_b->next = NULL;
        table->total++;
    }
    else if (index->type == AVM_memcell_t::number_m)
    {

        tindex = (int)index->data.numVal % AVM_TABLE_HASHSIZE;

        if (elem != NULL)
        {
            mem::assign(elem, value);
            return;
        }

        if (table->numIndexed[tindex] == NULL)
        {

            table->numIndexed[tindex] = (AVM_table_bucket *)malloc(sizeof(AVM_table_bucket));

            AVM_table_bucket *new_b = (AVM_table_bucket *)malloc(sizeof(AVM_table_bucket));
            new_b->key.data.numVal = index->data.numVal;

            if (value->type == AVM_memcell_t::table_m)
            {
                refcounter_increase(value->data.tableVal);
            }

            new_b->value = *value;

            table->numIndexed[tindex] = new_b;

            table->numIndexed[tindex]->next = NULL;
            table->total++;

            return;
        }

        AVM_table_bucket *tmp = table->numIndexed[tindex];
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }

        AVM_table_bucket *new_b = (AVM_table_bucket *)malloc(sizeof(AVM_table_bucket));
        new_b->key = *index;

        if (value->type == AVM_memcell_t::table_m)
        {
            refcounter_increase(value->data.tableVal);
        }

        new_b->value = *value;
        tmp->next = new_b;
        new_b->next = NULL;
        table->total++;
    }
}