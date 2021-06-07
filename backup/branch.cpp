#include "../execute.h"
#include <assert.h>
#include "mem.h"

void Execute::jeq(VM *vm, Instruction *instr)
{

	assert(instr->result.type == label_a);

	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	unsigned char result = 0;

	if (rv1->type == AVM_memcell_t::undef_m || rv2->type == AVM_memcell_t::undef_m)
	{
		printf("'undef' involved in equality\n");
		vm->exec_finished = 1;
	}
	else if (rv1->type == AVM_memcell_t::nil_m || rv2->type == AVM_memcell_t::nil_m)
	{
		result = (rv1->type == AVM_memcell_t::nil_m) && (rv2->type == AVM_memcell_t::nil_m);
	}
	else if (rv1->type == AVM_memcell_t::bool_m || rv2->type == AVM_memcell_t::bool_m)
	{
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	}
	else if (rv1->type != rv2->type)
	{
		printf("Equality check between different types is illegal\n");
		vm->exec_finished = 1;
	}
	else
	{

		if (rv1->type == AVM_memcell_t::number_m)
		{
			result = rv1->data.numVal == rv2->data.numVal;
		}
		else if (rv1->type == AVM_memcell_t::string_m)
		{
			result = !strcmp(rv1->data.strVal, rv2->data.strVal);
		}
		else
		{
			result = (avm_tobool(rv1) == avm_tobool(rv2));
		}
	}

	if (!vm->exec_finished && result)
		vm->pc = instr->result.val;
}

void Execute::jne(VM *vm, Instruction *instr)
{
	assert(instr->result.type == label_a);

	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	unsigned char result = 0;

	if (rv1->type == AVM_memcell_t::undef_m || rv2->type == AVM_memcell_t::undef_m)
	{
		printf("'undef' involved in equality\n");
		vm->exec_finished = 1;
	}
	else if (rv1->type == AVM_memcell_t::nil_m || rv2->type == AVM_memcell_t::nil_m)
	{
		result = (rv1->type == AVM_memcell_t::nil_m) && (rv2->type == AVM_memcell_t::nil_m);
	}
	else if (rv1->type == AVM_memcell_t::bool_m || rv2->type == AVM_memcell_t::bool_m)
	{
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	}
	else if (rv1->type != rv2->type)
	{
		printf("Equality check between different types is illegal\n");
		vm->exec_finished = 1;
	}
	else
	{

		if (rv1->type == AVM_memcell_t::number_m)
		{
			result = rv1->data.numVal == rv2->data.numVal;
		}
		else if (rv1->type == AVM_memcell_t::string_m)
		{
			result = !strcmp(rv1->data.strVal, rv2->data.strVal);
		}
		else
		{
			result = (avm_tobool(rv1) == avm_tobool(rv2));
		}
	}

	if (!vm->exec_finished && !result)
		vm->pc = instr->result.val;
}

void Execute::jle(VM *vm, Instruction *instr)
{
	assert(instr->result.type == label_a);

	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	unsigned char result = 0;

	if (rv1->type == AVM_memcell_t::undef_m || rv2->type == AVM_memcell_t::undef_m)
	{
		printf("'undef' involved in equality\n");
		vm->exec_finished = 1;
	}
	else if (rv1->type == AVM_memcell_t::nil_m || rv2->type == AVM_memcell_t::nil_m)
	{
		result = (rv1->type == AVM_memcell_t::nil_m) && (rv2->type == AVM_memcell_t::nil_m);
	}
	else if (rv1->type == AVM_memcell_t::bool_m || rv2->type == AVM_memcell_t::bool_m)
	{
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	}
	else if (rv1->type != rv2->type)
	{
		printf("Equality check between different types is illegal\n");
		vm->exec_finished = 1;
	}
	else
	{

		if (rv1->type == AVM_memcell_t::number_m)
		{
			printf("Error:Not an arithmetic constant!\n");
		}
		else if (rv1->type == AVM_memcell_t::string_m)
		{
			printf("Error:Not an arithmetic constant!\n");
		}
		else
		{
			result = (rv1->data.numVal <= rv2->data.numVal);
		}
	}

	if (!vm->exec_finished && result)
		vm->pc = instr->result.val;
}

void Execute::jge(VM *vm, Instruction *instr)
{
	assert(instr->result.type == label_a);

	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	unsigned char result = 0;

	if (rv1->type == AVM_memcell_t::undef_m || rv2->type == AVM_memcell_t::undef_m)
	{
		printf("'undef' involved in equality\n");
		vm->exec_finished = 1;
	}
	else if (rv1->type == AVM_memcell_t::nil_m || rv2->type == AVM_memcell_t::nil_m)
	{
		result = (rv1->type == AVM_memcell_t::nil_m) && (rv2->type == AVM_memcell_t::nil_m);
	}
	else if (rv1->type == AVM_memcell_t::bool_m || rv2->type == AVM_memcell_t::bool_m)
	{
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	}
	else if (rv1->type != rv2->type)
	{
		printf("Equality check between different types is illegal\n");
		vm->exec_finished = 1;
	}
	else
	{

		if (rv1->type == AVM_memcell_t::number_m)
		{
			printf("Error:Not an arithmetic constant!\n");
		}
		else if (rv1->type == AVM_memcell_t::string_m)
		{
			printf("Error:Not an arithmetic constant!\n");
		}
		else
		{
			result = (rv1->data.numVal >= rv2->data.numVal);
		}
	}

	if (!vm->exec_finished && result)
		vm->pc = instr->result.val;
}

void Execute::jlt(VM *vm, Instruction *instr)
{
	assert(instr->result.type == label_a);

	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	unsigned char result = 0;

	if (rv1->type == AVM_memcell_t::undef_m || rv2->type == AVM_memcell_t::undef_m)
	{
		printf("'undef' involved in equality\n");
		vm->exec_finished = 1;
	}
	else if (rv1->type == AVM_memcell_t::nil_m || rv2->type == AVM_memcell_t::nil_m)
	{
		result = (rv1->type == AVM_memcell_t::nil_m) && (rv2->type == AVM_memcell_t::nil_m);
	}
	else if (rv1->type == AVM_memcell_t::bool_m || rv2->type == AVM_memcell_t::bool_m)
	{
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	}
	else if (rv1->type != rv2->type)
	{
		printf("Equality check between different types is illegal\n");
		vm->exec_finished = 1;
	}
	else
	{

		if (rv1->type == AVM_memcell_t::number_m)
		{
			printf("Error:Not an arithmetic constant!\n");
		}
		else if (rv1->type == AVM_memcell_t::string_m)
		{
			printf("Error:Not an arithmetic constant!\n");
		}
		else
		{
			result = (rv1->data.numVal < rv2->data.numVal);
		}
	}

	if (!vm->exec_finished && result)
		vm->pc = instr->result.val;
}

void Execute::jgt(VM *vm, Instruction *instr)
{
	assert(instr->result.type == label_a);

	AVM_memcell *rv1 = vm->translate_operand(&instr->arg1, &vm->ax);
	AVM_memcell *rv2 = vm->translate_operand(&instr->arg2, &vm->bx);

	unsigned char result = 0;

	if (rv1->type == AVM_memcell_t::undef_m || rv2->type == AVM_memcell_t::undef_m)
	{
		printf("'undef' involved in equality\n");
		vm->exec_finished = 1;
	}
	else if (rv1->type == AVM_memcell_t::nil_m || rv2->type == AVM_memcell_t::nil_m)
	{
		result = (rv1->type == AVM_memcell_t::nil_m) && (rv2->type == AVM_memcell_t::nil_m);
	}
	else if (rv1->type == AVM_memcell_t::bool_m || rv2->type == AVM_memcell_t::bool_m)
	{
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	}
	else if (rv1->type != rv2->type)
	{
		printf("Equality check between different types is illegal\n");
		vm->exec_finished = 1;
	}
	else
	{

		if (rv1->type == AVM_memcell_t::number_m)
		{
			printf("Error:Not an arithmetic constant!\n");
		}
		else if (rv1->type == AVM_memcell_t::string_m)
		{
			printf("Error:Not an arithmetic constant!\n");
		}
		else
		{
			result = (rv1->data.numVal > rv2->data.numVal);
		}
	}

	if (!vm->exec_finished && result)
		vm->pc = instr->result.val;
}

void Execute::jump(VM *vm, Instruction *instr)
{
	assert(instr->result.type == label_a);

	if (!vm->exec_finished)
		vm->pc = instr->result.val;
}
