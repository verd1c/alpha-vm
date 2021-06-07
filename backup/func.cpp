#include "../execute.h"
#include "mem.h"
#include "vm.h"
#include <assert.h>
//==================
#define AVM_NUMACTUALS OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1

unsigned totalActuals;
extern userfunc* avm_getfuncinfo(unsigned address);


unsigned avm_get_envvalue(VM *vm, unsigned i){
	assert((&vm->stack.stack[i].type) == (AVM_memcell_t::number_m));
	unsigned val = (unsigned)vm->stack.stack[i].data.numVal;
	assert((&vm->stack.stack[i].data.numVal) == ((double)VMArg::val));
	
	return val;
}

void Execute::call(VM *vm, Instruction *instr) {
	// fill
}

void Execute::pusharg(VM *vm, Instruction *instr) {
	// fill
}

void Execute::funcenter(VM *vm, Instruction *instr) {
	AVM_memcell *func= vm->translate_operand(&instr->result, &vm->ax);
	assert(func);
	assert(vm->pc == func->data.funcVal);

	totalActuals = 0;
	userfunc *funcInfo = avm_getfuncinfo(vm->pc);
	vm->topsp = vm->top;
	vm->top = vm->top - funcInfo->local_size;
}

void Execute::funcexit(VM *vm, Instruction *instr) {
	unsigned oldTop = vm->top;
	vm->top = avm_get_envvalue(vm, vm->topsp + AVM_SAVEDTOP_OFFSET);
	vm->pc = avm_get_envvalue(vm, vm->topsp + AVM_SAVEDPC_OFFSET);
	vm->topsp = avm_get_envvalue(vm, vm->topsp + AVM_SAVEDTOPSP_OFFSET);

	while (++oldTop <= vm->top)
		memclear::clcell(&vm->stack.stack[oldTop]);
}

