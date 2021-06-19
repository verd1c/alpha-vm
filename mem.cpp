#include "mem.h"
#include "execute.h"
#include "tools.h"

AVMStack::AVMStack() {
	for (unsigned i = 0; i < AVM_STACKSIZE; i++) {
		AVM_WIPEOUT(this->stack[i]);
		this->stack[i].type = AVM_memcell_t::undef_m;
	}
}

memclear::func_t memclear::funcs[] = {
		0,
		memclear::clstring,
		0,
		memclear::cltable,
		0,
		0,
		0,
		0
};

void memclear::clstring(AVM_memcell *mc) {
	free(mc->data.strVal);
}

void memclear::cltable(AVM_memcell *mc) {

}

void memclear::clcell(AVM_memcell *mc) {
	if (mc->type != AVM_memcell_t::undef_m) {
		memclear::func_t f = memclear::funcs[mc->type];
		if (f)
			(*f)(mc);
		mc->type = AVM_memcell_t::undef_m;
	}
}

void mem::assign(AVM_memcell *lv, AVM_memcell *rv) {
	if (lv == rv)
		return;

	if (lv->type == AVM_memcell_t::table_m &&
		rv->type == AVM_memcell_t::table_m &&
		lv->data.tableVal == rv->data.tableVal) {
		return;
	}

	if (rv->type == AVM_memcell_t::undef_m)
		printf("BUGGAROO\n");

	memclear::clcell(lv);

	memcpy(lv, rv, sizeof(AVM_memcell));

	if (lv->type == AVM_memcell_t::string_m) {
		lv->data.strVal = strdup(rv->data.strVal);
	}
}

userfunc *mem::getfuncinfo(VM *vm, unsigned i) {
	for (int j = 0; j < vm->userfuncs.size(); j++) {
		if (vm->userfuncs.at(j).address == i) return &vm->userfuncs.at(j);
	}
}

void mem::dec_top(VM *vm) {
	if (!vm->top) {
		vm->exec_finished = true;
	}
	else {
		vm->top--;
	}
}

unsigned mem::get_envvalue(VM *vm, unsigned i) {
	unsigned val = (unsigned)vm->stack.stack[i].data.numVal;
	return val;
}

void mem::push_envvalue(VM *vm, unsigned val) {
	vm->stack.stack[vm->top].type = AVM_memcell_t::number_m;
	vm->stack.stack[vm->top].data.numVal = val;
	mem::dec_top(vm);
}

void mem::call_save_environment(VM *vm) {
	mem::push_envvalue(vm, vm->totalActuals);
	mem::push_envvalue(vm, vm->pc + 1);
	mem::push_envvalue(vm, vm->top + vm->totalActuals + 2);
	mem::push_envvalue(vm, vm->topsp);
}

unsigned mem::totalactuals(VM *vm) {
	return mem::get_envvalue(vm, vm->topsp+ AVM_NUMACTUALS_OFFSET);
}

AVM_memcell *mem::getactual(VM *vm, unsigned i) {
	return &vm->stack.stack[vm->topsp + AVM_STACKENV_SIZE + 1 + i];
}

typedef void (*library_func_t)(VM *vm);

char *strr(AVM_memcell *mc) {
	return mc->data.strVal;
}

void libfunc_print (VM *vm) {
	unsigned n = mem::totalactuals(vm);
	for (unsigned i = 0; i < n; i++) {
		char *str = tostring::avm_tostring(vm, mem::getactual(vm, i));
		printf("%s", str);
	}
}

void libfunc_objecttotalmembers(VM *vm) {
	int size = 0;
	unsigned n = mem::totalactuals(vm);
	if (n != 1)
		printf("wat\n");

	AVM_memcell *arg = mem::getactual(vm, 0);

	if (arg->type != AVM_memcell_t::table_m) {
		printf("Wasn't table\n");
	}

	for (int i = 0; i < AVM_TABLE_HASHSIZE; i++) {
		if (arg->data.tableVal->str_indexed[i])
			size++;
		if (arg->data.tableVal->num_indexed[i])
			size++;
		if (arg->data.tableVal->tab_indexed[i])
			size++;
	}

	vm->retval.type = AVM_memcell_t::number_m;
	vm->retval.data.numVal = size;
	return;
}

library_func_t avm_getlibraryfunc(VM *vm, char *id) {
	if (strcmp(id, "print") == 0) {
		return libfunc_print;
	}
	else if (strcmp(id, "objecttotalmembers") == 0) {
		return libfunc_objecttotalmembers;
	}
	else {
		return 0;
	}
}

void mem::calllibfunc(VM *vm, char *id) {
	library_func_t f = avm_getlibraryfunc(vm, id);
	if (!f) {
		vm->exec_finished = true;
	}
	else {
		vm->topsp = vm->top;
		vm->totalActuals = 0;
		(*f)(vm);
		if (!vm->exec_finished) {
			Execute::funcexit(vm, nullptr);
		}
	}
}