#include "../execute.h"
#include "mem.h"
#include "vm.h"
#include <assert.h>

typedef char *(*tostring_func_t)(AVM_memcell *);

extern char *number_tostring(AVM_memcell *);
extern char *string_tostring(AVM_memcell *);
extern char *bool_tostring(AVM_memcell *);
extern char *table_tostring(AVM_memcell *);
extern char *userfunc_tostring(AVM_memcell *);
extern char *libfunc_tostring(AVM_memcell *);
extern char *nil_tostring(AVM_memcell *);
extern char *undef_tostring(AVM_memcell *);

tostring_func_t tostringFuncs[] = {
	number_tostring,
	string_tostring,
	bool_tostring,
	table_tostring,
	userfunc_tostring,
	libfunc_tostring, 
	nil_tostring,
	undef_tostring
};



char *avm_tostring(AVM_memcell *m)
{
	assert(m->type >= 0 && m->type <= AVM_memcell_t::undef_m);

	//tostringFuncs to idio me to_string??
	return (*tostringFuncs[m->type])(m);
}


void Execute::newtable(VM *vm, Instruction *instr)
{
	AVM_memcell *lv = vm->translate_operand(&instr->result, (AVM_memcell *)0);
	assert(lv && (&vm->stack.stack[AVM_STACKSIZE - 1] >= lv && lv > &vm->stack[vm->top] || lv == &vm->retval));

	memclear::clcell(lv);

	lv->type = AVM_memcell_t::table_m;
	lv->data.tableVal = avm_tablenew();
	avm_tableincrefcounter(lv->data.tableVal);
}

void Execute::tablegetelem(VM *vm, Instruction *instr)
{
	AVM_memcell *lv = vm->translate_operand(&instr->result, (AVM_memcell *)0);
	AVM_memcell *t = vm->translate_operand(&instr->arg1, (AVM_memcell *)0);
	AVM_memcell *i = vm->translate_operand(&instr->arg2, &vm->ax);

	assert(lv && (&vm->stack.stack[AVM_STACKSIZE - 1] >= lv && lv > &vm->stack.stack[vm->top] || lv == &vm->retval));
	assert(t && (&vm->stack.stack[AVM_STACKSIZE-1] >= t && t > &vm->stack.stack[vm->top]);
	assert(i);

	memclear::clcell(lv);
	lv->type = AVM_memcell_t::nil_m;

	if(t->type != AVM_memcell_t::ta)
		printf("Illegal use of type %s as table!\n", typeStrings[t->type]);
	else {
		AVM_memcell *content = avm_tablegetelem(t->data.tableVal, i);
		if (content)
			mem::assign(lv, content);
		else
		{
			char *ts = avm_tostring(t);
			char *is = avm_tostring(i);
			printf("%s[%s] not found!\n", ts, is);
			free(ts);
			free(is);
		}
	}
}

void Execute::tablesetelem(VM *vm, Instruction *instr)
{
	AVM_memcell *t = vm->translate_operand(&instr->result, (AVM_memcell *)0);
	AVM_memcell *i = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *c = vm->translate_operand(&instr->arg2, &vm->bx);

	assert(t && &vm->stack.stack[AVM_STACKSIZE - 1] >= t && &vm->stack.stack[vm->top]);
	assert(i && c);

	if (t->type != AVM_memcell_t::table_m)
		printf("Illegal use of type %s as table!\n", typeStrings[t->type]);
	else
		avm_tablesetelem(t->data.tableVal, i, c);
}