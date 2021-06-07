#include "mem.h"
#include <assert.h>

AVMStack::AVMStack()
{
	for (unsigned i = 0; i < AVM_STACKSIZE; i++)
	{
		AVM_WIPEOUT(this->stack[i]);
		this->stack[i].type = AVM_memcell_t::undef_m;
	}
}

tobool_func_t toboolFuncs[] ={
	number_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool
};

memclear::func_t memclear::funcs[] = {
	0,
	memclear::clstring,
	0,
	memclear::cltable,
	0,
	0,
	0,
	0};

void memclear::clstring(AVM_memcell *mc)
{
	free(mc->data.strVal);
}

void memclear::cltable(AVM_memcell *mc)
{
}

void memclear::clcell(AVM_memcell *mc)
{
	if (mc->type != AVM_memcell_t::undef_m)
	{
		memclear::func_t f = memclear::funcs[mc->type];
		if (f)
			(*f)(mc);
		mc->type = AVM_memcell_t::undef_m;
	}
}

void mem::assign(AVM_memcell *lv, AVM_memcell *rv)
{
	if (lv == rv)
		return;

	if (lv->type == AVM_memcell_t::table_m &&
		rv->type == AVM_memcell_t::table_m &&
		lv->data.tableVal == rv->data.tableVal)
	{
		return;
	}

	if (rv->type == AVM_memcell_t::undef_m)
		printf("BUGGAROO\n");

	memclear::clcell(lv);

	memcpy(lv, rv, sizeof(AVM_memcell));

	if (lv->type == AVM_memcell_t::string_m)
	{
		lv->data.strVal = strdup(rv->data.strVal);
	}
}

void avm_tableIncRefCounter(avm_table* t){
	++t->refCounter;
}


unsigned char number_tobool (AVM_memcell* m) {
	return m->data.numVal !=0; 
}

unsigned char string_tobool (AVM_memcell* m) {	
	return m->data.strVal[0] !=0; 
}

unsigned char bool_tobool (AVM_memcell* m) {
	return m->data.boolVar !=0; 
}

unsigned char table_tobool (AVM_memcell* m) {	
	return 1; 
}

unsigned char userfunc_tobool (AVM_memcell* m) {
	return 1; 
}

unsigned char libfunc_tobool (AVM_memcell* m) {
	return 1; 
}

unsigned char nil_tobool (AVM_memcell* m) {	
	return 0; 
}
	
unsigned char undef_tobool (AVM_memcell* m) {
	return 0; 
}

unsigned char avm_tobool(AVM_memcell* m){
	assert(m->type >=0 && m->type < AVM_memcell_t::undef_m);
	return (*toboolFuncs[m->type])(m);
}