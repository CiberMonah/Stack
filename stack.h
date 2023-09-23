#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define STK_DUMP(stk) ({                                                \
    stack_dump((stk), __FILE__, __PRETTY_FUNCTION__, __LINE__);         \
    })

#define STK_CTOR(stk) ({                                                \
    stack_ctor((stk), #stk, __LINE__, __PRETTY_FUNCTION__, __FILE__);   \
    })

typedef int Elem_t;
const unsigned long long left_parrot = 12250030;  //Does not include the digits 0 or 1 in the octal notation of the number
const unsigned long long right_parrot = 4831533;  //Does not include the digits 0 or 1 in the octal notation of the number
const Elem_t void_elem = 78787;

struct Stack {
    unsigned long long left_canary = left_parrot;
    Elem_t* data = NULL;
    int size = 0;
    int capacity = 0;
    int line = 0;
    const char* file_name = NULL;
    const char* func_name = NULL;
    const char* name = NULL;
    bool is_exist = 0;
    int errors = 1 << 0;
    unsigned long long right_canary = right_parrot;
};


enum error_type {
    no_err = 1 << 0,

    mem_alloc_err = 1 << 1,
    null_ptr_err = 1 << 2,
    out_of_index_err = 1 << 3,
    stack_is_not_exist = 1 << 4,
    critical_err = 1 << 5,
    stack_canary_err = 1 << 6
};

error_type stack_ctor(Stack* stk, const char* name, int line, const char* func, const char* file);
error_type stack_pop(Stack* stk, Elem_t* poped);
error_type stack_dtor(Stack* stk);
error_type stack_dump(Stack* stk, const char* file, const char* func, const int line);
error_type get_error(error_type error);
error_type stack_push(Stack* stk, Elem_t value);
error_type check_cannaries(Stack* stk);
error_type stack_resize_capacity(Stack* stk);
error_type put_error(error_type error, Stack* stk);


#endif // STACK_H_INCLUDED
