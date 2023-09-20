#include "stack.h"

const int min_capacity = 5;

error_type stack_ctor(Stack* stk) {
    if(stk == NULL)
        return null_ptr_err;
    stk->size = 0;
    stk->capacity = min_capacity;
    stk->data = {};

    return no_err;
}

error_type stack_dtor(Stack* stk) {
    stk->size = 999;
    stk->capacity = -1;
    free(stk->data);
    return no_err;
}

error_type stack_push(Stack* stk, Elem_t value) {
    if(stk->size == stk->capacity) { //Add assert and prochaya huinya
        stk->data = (Elem_t*)realloc(stk->data, stk->capacity * 2 * sizeof(Elem_t));
        if(stk->data == NULL)
            return mem_alloc_err;
        stk->capacity *= 2;
        }
    else
        stk->data[(stk->size)++] = value;
    return no_err;
}

error_type stack_pop(Stack* stk) {
    if(stk->size-- == stk->capacity / 2) { //Add assert and prochaya huinya
        stk->data = (Elem_t*)realloc(stk->data, stk -> capacity  / 2 * sizeof(Elem_t));
        stk->capacity = stk->capacity /  2;
        if(stk->data == NULL)
            return mem_alloc_err;
        }
    else
        stk->data[(stk->size)--] = 0;
    return no_err;
}

error_type dump(Stack* stk) {
    printf("Capacity of stack - %d\n", stk->capacity);
    printf("Cursor on - %d\n", stk->size);
    for(int i = 0; i < stk->capacity; i++) {
        printf("[%d] = %d\n", i, stk->data[i]);
    }
    return no_err;
}


