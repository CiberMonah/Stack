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
const unsigned long LEFT_PARROT = 12250030;  //Does not include the digits 0 or 1 in the octal notation of the number
const unsigned long RIGHT_PARROT = 4831533;  //Does not include the digits 0 or 1 in the octal notation of the number
const Elem_t VOID_ELEM = 78787;

struct Stack {
    unsigned long left_canary = LEFT_PARROT;

    Elem_t* data = NULL;
    int size = 0;
    int capacity = 0;
    bool is_exist = 0;
    int errors = 1 << 0;

    int line = 0;
    const char* name = NULL;
    const char* file_name = NULL;
    const char* func_name = NULL;

    unsigned long hash = 0;
    unsigned long right_canary = RIGHT_PARROT;
};


enum error_type {
    NO_ERR = 1 << 0,

    MEM_ALLOC_ERR = 1 << 1,
    NULL_PTR_ERR= 1 << 2,
    OUT_OF_INDEX_ERR = 1 << 3,
    STACK_IS_NOT_EXIST = 1 << 4,
    CRITICAL_ERR = 1 << 5,
    STACK_CANARY_ERR = 1 << 6,
    STACK_SIZE_ERR = 1 << 7,
    STACK_HASH_ERR = 1 << 8
};

error_type stack_ctor(Stack* stk, const char* name, int line, const char* func, const char* file);
error_type stack_pop(Stack* stk, Elem_t* poped);
error_type stack_dtor(Stack* stk);
error_type stack_dump(Stack* stk, const char* file, const char* func, const int line);
error_type print_error(error_type error);
error_type stack_push(Stack* stk, Elem_t value);
error_type check_canaries(Stack* stk);
error_type stack_resize_capacity(Stack* stk);
error_type put_error(Stack* stk, error_type error);
int get_error(Stack* stk);
unsigned long hasher (Stack* stk);
error_type hash_checker(Stack* stk);


#endif // STACK_H_INCLUDED
