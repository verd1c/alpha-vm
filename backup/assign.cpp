#include "../execute.h"
#include "../mem.h"
#include "../vm.h"
#include <assert.h>


void mem::assign (AVM_memcell *lv, AVM_memcell *rv);

void Execute::assign(VM *vm, Instruction *instr) {
	AVM_memcell* lv = vm->translate_operand(&instr->result, (AVM_memcell*)0 );
	AVM_memcell* rv = vm->translate_operand(&instr->arg1, &vm->ax);

	assert(lv && (&vm->stack[AVM_STACKSIZE-1]>= lv && lv> &vm->stack[0]));
	assert(rv);
	mem::assign(lv,rv);
}