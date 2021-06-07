#include "../execute.h"
#include "../mem.h"
#include "../vm.h"
#include <assert.h>

arithmetic_func_t arithmeticFuncs[] = {
	add_impl,
	sub_impl,
	mul_impl,
	div_impl,
	mod_impl,
	minus_impl
	};

void Execute::add(VM *vm, Instruction *instr)
{
	AVM_memcell *lv = vm->translate_operand(&instr->result, (AVM_memcell *)0);
	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	assert(lv && ((&vm->stack.stack[AVM_STACKSIZE] >= lv && &vm->stack.stack[0] < lv) || lv == &vm->retval));
	assert(rv1 && rv2);

	if (rv1->type != AVM_memcell_t::number_m || rv2->type != AVM_memcell_t::number_m)
	{
		printf("not a number arithmetic!\n");
		vm->exec_finished = 1;
	}
	else
	{
		arithmetic_func_t op = arithmeticFuncs[0];
		memclear::clcell(lv);
		lv->type = AVM_memcell_t::number_m;
		lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
	}
}

void Execute::sub(VM *vm, Instruction *instr)
{
	AVM_memcell *lv = vm->translate_operand(&instr->result, (AVM_memcell *)0);
	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	assert(lv && ((&vm->stack.stack[AVM_STACKSIZE] >= lv && &vm->stack.stack[0] < lv) || lv == &vm->retval));
	assert(rv1 && rv2);

	if (rv1->type != AVM_memcell_t::number_m || rv2->type != AVM_memcell_t::number_m)
	{
		printf("not a number arithmetic!\n");
		vm->exec_finished = 1;
	}
	else
	{
		arithmetic_func_t op = arithmeticFuncs[1];
		memclear::clcell(lv);
		lv->type = AVM_memcell_t::number_m;
		lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
	}
}

void Execute::mul(VM *vm, Instruction *instr)
{
	AVM_memcell *lv = vm->translate_operand(&instr->result, (AVM_memcell *)0);
	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	assert(lv && ((&vm->stack.stack[AVM_STACKSIZE] >= lv && &vm->stack.stack[0] < lv) || lv == &vm->retval));
	assert(rv1 && rv2);

	if (rv1->type != AVM_memcell_t::number_m || rv2->type != AVM_memcell_t::number_m)
	{
		printf("not a number arithmetic!\n");
		vm->exec_finished = 1;
	}
	else
	{
		arithmetic_func_t op = arithmeticFuncs[2];
		memclear::clcell(lv);
		lv->type = AVM_memcell_t::number_m;
		lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
	}
}

void Execute::div(VM *vm, Instruction *instr)
{
	AVM_memcell *lv = vm->translate_operand(&instr->result, (AVM_memcell *)0);
	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	assert(lv && ((&vm->stack.stack[AVM_STACKSIZE] >= lv && &vm->stack.stack[0] < lv) || lv == &vm->retval));
	assert(rv1 && rv2);

	if (rv1->type != AVM_memcell_t::number_m || rv2->type != AVM_memcell_t::number_m)
	{
		printf("not a number arithmetic!\n");
		vm->exec_finished = 1;
	}
	else
	{
		arithmetic_func_t op = arithmeticFuncs[3];
		memclear::clcell(lv);
		lv->type = AVM_memcell_t::number_m;
		lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
	}
}

void Execute::mod(VM *vm, Instruction *instr)
{
	AVM_memcell *lv = vm->translate_operand(&instr->result, (AVM_memcell *)0);
	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	assert(lv && ((&vm->stack.stack[AVM_STACKSIZE] >= lv && &vm->stack.stack[0] < lv) || lv == &vm->retval));
	assert(rv1 && rv2);

	if (rv1->type != AVM_memcell_t::number_m || rv2->type != AVM_memcell_t::number_m)
	{
		printf("not a number arithmetic!\n");
		vm->exec_finished = 1;
	}
	else
	{
		arithmetic_func_t op = arithmeticFuncs[4];
		memclear::clcell(lv);
		lv->type = AVM_memcell_t::number_m;
		lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
	}
}

void Execute::minus(VM *vm, Instruction *instr)
{
	AVM_memcell *lv = vm->translate_operand(&instr->result, (AVM_memcell *)0);
	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	assert(lv && ((&vm->stack.stack[AVM_STACKSIZE] >= lv && &vm->stack.stack[0] < lv) || lv == &vm->retval));
	assert(rv1 && rv2);

	if (rv1->type != AVM_memcell_t::number_m || rv2->type != AVM_memcell_t::number_m)
	{
		printf("not a number arithmetic!\n");
		vm->exec_finished = 1;
	}
	else
	{
		arithmetic_func_t op = arithmeticFuncs[5];
		memclear::clcell(lv);
		lv->type = AVM_memcell_t::number_m;
		lv->data.numVal = (*op)(rv1->data.numVal,-1);
	}
}

double add_impl(double x, double y)
{
	return x + y;
}

double sub_impl(double x, double y)
{
	return x - y;
}

double mul_impl(double x, double y)
{
	return x * y;
}

double div_impl(double x, double y)
{
	if (y == 0)
	{
		printf("Error:Division with zero attempted.\n");
	}
	return x / y;
}

double mod_impl(double x, double y)
{
	if (y == 0)
	{
		printf("Error:Division with zero attempted.\n");
	}
	return ((unsigned)x) % ((unsigned)y);
}

double minus_impl(double x,double y)
{
	if (x == 0)
	{
		printf("Error:Cannot uminus zero.\n");
	}
	return (x *y);
}