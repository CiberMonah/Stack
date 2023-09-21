#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Elem_t;

struct Stack {
    Elem_t* data = NULL;
    int size = 0;
    int capacity = 0;
};


enum error_type {
    no_err = 9090,
    mem_alloc_err = 5656,
    null_ptr_err = 7878,
    out_of_index_err = 1212,
};

error_type stack_ctor(Stack* stk);
error_type stack_push(Stack* stk, Elem_t value);
error_type stack_pop(Stack* stk);
error_type stack_dtor(Stack* stk);
error_type dump(Stack* stk);
error_type get_error(error_type error);


#endif // STACK_H_INCLUDED
