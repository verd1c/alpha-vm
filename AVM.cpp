// AVM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <fstream>
#include <iostream>
#include "vm.h"
#include "vmarg.h"

VM *debug;

int main()
{
    VM vm = VM();
    debug = &vm;
    vm.parse("target.abc");
    while (!vm.exec_finished) {
        vm.execute_cycle();
    }
    return 1;
}