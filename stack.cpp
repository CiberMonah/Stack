#include "stack.h"

const int min_capacity = 5;


error_type stack_ctor(Stack* stk, const char* name, int line, const char* func, const char* file) {
    if(stk == NULL)
        return null_ptr_err;

    stk->is_exist = 1;
    stk->capacity = min_capacity;
    stk->size = 0;

    stk->name = name;
    stk->line = line;
    stk->file_name = file;
    stk->func_name = func;

    stk->data = (Elem_t*)calloc(min_capacity, sizeof(Elem_t));
    if(stk->data == NULL)
        return mem_alloc_err;

    for(int i = 0; i < stk->capacity; i++)
        stk->data[i] = void_elem;

    return no_err;
}

error_type stack_dtor(Stack* stk) {
    if(stk->is_exist == 0) return stack_is_not_exist;
    stk->size = -1;
    stk->capacity = -1;
    free(stk->data);
    return no_err;
}

error_type stack_push(Stack* stk, Elem_t value) {
    if(stk->is_exist == 0) return stack_is_not_exist;
    stack_resize_capacity(stk);
    stk->data[stk->size] = value;
    stk->size += 1;

    return no_err;
}

error_type stack_pop(Stack* stk, Elem_t* poped) {
    if(stk == NULL) return null_ptr_err;
    if(stk->is_exist == 0) return stack_is_not_exist;
    if(stk->size == 0)
        return out_of_index_err;
    stk->size--;
    *poped = stk->data[(stk->size)];
    stk->data[(stk->size)] = void_elem;
    if(stack_resize_capacity(stk) == no_err) {
        return no_err;
    }
    return critical_err;
}

error_type stack_dump(Stack* stk, const char* file, const char* func, const int line) {
    printf("Dump called in file - %s function  - %s on line - %d", file, func, line);
    if(stk->is_exist == 0) {
        return stack_is_not_exist;
    } else {
        printf("\nPointer on stack named(%s)- %p\n", stk->name, stk);
        printf("Created in file - %s in function - %s on line - %d\n", stk->file_name, stk->func_name, stk->line);
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

    assert(0 && "fallthrough");
}

error_type get_error(error_type error) {
    if(error == mem_alloc_err) {
        printf("Memory allocation error\n");
        return mem_alloc_err;
    } else if(error == null_ptr_err) {
        printf("Pointer is Null\n");
        return null_ptr_err;
    } else if(error == out_of_index_err) {
        printf("Index is out of range\n");
        return out_of_index_err;
    } else if(error == stack_is_not_exist) {
        printf("Stack is not exist\n");
        return stack_is_not_exist;
    }

    return no_err;
}

error_type put_error(error_type error, Stack* stk) {
    if(stk == NULL)
        return null_ptr_err;
    stk->errors |= error;
    return no_err;
}

error_type check_cannaries(Stack* stk) {
    if(stk->left_canary == left_parrot && stk->right_canary == right_parrot)
        return no_err;

    return stack_canary_err;
}

error_type stack_resize_capacity(Stack* stk) {
    Elem_t* temp = NULL;

    if ((stk->size == stk->capacity / 2 - 1) && (stk->capacity / 2 >= min_capacity)) {
        temp = (Elem_t*)realloc(stk->data, stk -> capacity  / 2 * sizeof(Elem_t));
        if(temp == NULL)
            return mem_alloc_err;
        stk->data = temp;
        stk->capacity = stk->capacity /  2;
    } else if(stk->size == stk->capacity - 1) {
        temp = (Elem_t*)realloc(stk->data, stk->capacity * 2 * sizeof(Elem_t));
        if(temp == NULL)
            return mem_alloc_err;
        stk->data = temp;
        for(int i = 0; i < stk->size + 2; i++)
            stk->data[stk->size  + i] = void_elem;
        stk->capacity *= 2;
    }
    return no_err;
}
