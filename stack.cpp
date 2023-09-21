#include "stack.h"

const int min_capacity = 5;
const int void_elem = 78787;

error_type stack_ctor(Stack* stk) {
    if(stk == NULL)
        return null_ptr_err;
    stk->size = 0;
    stk->capacity = min_capacity;
    stk->data = (Elem_t*)calloc(min_capacity, sizeof(Elem_t));
    if(stk->data == NULL) return mem_alloc_err;
    for(int i = 0; i < stk->capacity; i++)
        stk->data[i] = void_elem;
    return no_err;
}

error_type stack_dtor(Stack* stk) {
    if(stk == NULL || stk->capacity < 0 || stk->size < 0) return stack_is_not_exist;
    stk->size = -1;
    stk->capacity = -1;
    free(stk->data);
    return no_err;
}

error_type stack_push(Stack* stk, Elem_t value) {
    if(stk->size < 0 || stk->capacity < 0) return stack_is_not_exist;
    if(stk->size == stk->capacity - 1) {
        stk->data = (Elem_t*)realloc(stk->data, stk->capacity * 2 * sizeof(Elem_t));
        for(int i = 0; i < stk->size + 2; i++)
            stk->data[stk->size  + i] = void_elem;
        if(stk->data == NULL)
            return mem_alloc_err;
        stk->capacity *= 2;
        stk->data[(stk->size)] = value;
        stk->size += 1;
        return no_err;
    } else {
        stk->data[stk->size] = value;
        stk->size++;
        return no_err;
    }
}

error_type stack_pop(Stack* stk) {
    if(stk == NULL) return null_ptr_err;
    if(stk->capacity < 0 || stk->size < 0 || stk->data == NULL) return stack_is_not_exist;
    if(stk->size == 0)
        return out_of_index_err;
    if(stk->size-- == stk->capacity / 2) {
        stk->data = (Elem_t*)realloc(stk->data, stk -> capacity  / 2 * sizeof(Elem_t));
        stk->capacity = stk->capacity /  2;
        if(stk->data == NULL)
            return mem_alloc_err;
        stk->data[(stk->size)] = void_elem;
        }
    else
        stk->data[(stk->size)] = void_elem;
    return no_err;
}

error_type dump(Stack* stk) {
    if(stk->capacity < 0 || stk->size < 0 || stk->data == NULL) {
        return stack_is_not_exist;
    } else {
        printf("\nPointer on stack - %p\n", stk);
        printf("Pointer on data - %p\n", stk->data);
        printf("Capacity of stack - %d\n", stk->capacity);
        printf("Cursor on - %d\n", stk->size);
        for(int i = 0; i < stk->capacity; i++) {
            if(stk->data[i] == void_elem)
                printf("[%d] = (void)\n", i);
            else
                printf("[%d] = %d\n", i, stk->data[i]);
        }
    return no_err;
    }
}

error_type get_error(error_type error) {
    if(error == mem_alloc_err) printf("Memory allocation error\n");
    else if(error == null_ptr_err) printf("Pointer is Null\n");
    else if(error == out_of_index_err) printf("Index is out of range\n");
    else if(error == stack_is_not_exist) printf("Stack is not exist\n");
    return no_err;
}
