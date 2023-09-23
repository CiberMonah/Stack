#include "stack.h"

const int MIN_CAPACITY = 5;
const int POISON = 12321;


error_type stack_ctor(Stack* stk, const char* name, int line, const char* func, const char* file) {
    if(stk == NULL)
        return NULL_PTR_ERR;

    stk->is_exist = 1;
    stk->capacity = MIN_CAPACITY;
    stk->size = 0;

    stk->name = name;
    stk->line = line;
    stk->file_name = file;
    stk->func_name = func;

    stk->data = (Elem_t*)calloc(MIN_CAPACITY, sizeof(Elem_t));
    if(stk->data == NULL)
        return MEM_ALLOC_ERR;

    for(int i = 0; i < stk->capacity; i++)
        stk->data[i] = VOID_ELEM;

    return NO_ERR;
}

error_type stack_dtor(Stack* stk) {
    if(stk->is_exist == 0) return STACK_IS_NOT_EXIST;
    stk->size = POISON;
    stk->capacity = POISON;
    free(stk->data);
    return NO_ERR;
}

error_type stack_push(Stack* stk, Elem_t value) {
    if(stk->is_exist == 0) return STACK_IS_NOT_EXIST;
    stack_resize_capacity(stk);
    stk->data[stk->size] = value;
    stk->size += 1;

    return NO_ERR;
}

error_type stack_pop(Stack* stk, Elem_t* poped) {
    if(stk == NULL) return NULL_PTR_ERR;
    if(stk->is_exist == 0) return STACK_IS_NOT_EXIST;
    if(stk->size == 0)
        return OUT_OF_INDEX_ERR;
    stk->size--;
    *poped = stk->data[(stk->size)];
    stk->data[(stk->size)] = VOID_ELEM;
    if(stack_resize_capacity(stk) == NO_ERR) {
        return NO_ERR;
    }
    return CRITICAL_ERR;
}

error_type stack_dump(Stack* stk, const char* file, const char* func, const int line) {
    printf("Dump called in file - %s function  - %s on line - %d", file, func, line);
    if(stk->is_exist == 0) {
        return STACK_IS_NOT_EXIST;
    } else {
        printf("\nPointer on stack named(%s)- %p\n", stk->name, stk);
        printf("Created in file - %s in function - %s on line - %d\n", stk->file_name, stk->func_name, stk->line);
        printf("Pointer on data - %p\n", stk->data);
        printf("Capacity of stack - %d\n", stk->capacity);
        printf("Cursor on - %d\n", stk->size);
        for(int i = 0; i < stk->capacity; i++) {
            if(stk->data[i] == VOID_ELEM)
                printf("[%d] = (void)\n", i);
            else
                printf("[%d] = %d\n", i, stk->data[i]);
        }
        return NO_ERR;
    }

    assert(0 && "fallthrough");
}

error_type print_error(error_type error) {
    if(error == MEM_ALLOC_ERR) {
        printf("Memory allocation error\n");
        return error;
    } else if(error == NULL_PTR_ERR) {
        printf("Pointer is Null\n");
        return error;
    } else if(error == OUT_OF_INDEX_ERR) {
        printf("Index is out of range\n");
        return error;
    } else if(error == STACK_IS_NOT_EXIST) {
        printf("Stack is not exist\n");
        return error;
    }

    return NO_ERR;
}

error_type put_error(Stack* stk, error_type error) {
    if(stk == NULL)
        return NULL_PTR_ERR;
    stk->errors |= error;
    return NO_ERR;
}

int get_error(Stack* stk) {
    int counter = 0;

    if(stk == NULL) {
        return NULL_PTR_ERR;
    } else if (stk->is_exist == 0) {
        put_error(stk, STACK_IS_NOT_EXIST);
        counter++;
    } else if (stk->capacity < 0 || stk->size < 0 || stk->size > stk->capacity) {
        put_error(stk, STACK_SIZE_ERR);
        counter++;
    } else if (stk->data == NULL) {
        put_error(stk, MEM_ALLOC_ERR);
        counter++;
    }

    return counter;
}

error_type check_canaries(Stack* stk) {
    if(stk->left_canary == LEFT_PARROT && stk->right_canary == RIGHT_PARROT)
        return NO_ERR;

    return STACK_CANARY_ERR;
}

error_type stack_resize_capacity(Stack* stk) {
    if(check_canaries(stk) == STACK_CANARY_ERR) return STACK_CANARY_ERR;

    Elem_t* temp = NULL;

    if ((stk->size == stk->capacity / 2 - 1) && (stk->capacity / 2 >= MIN_CAPACITY)) {
        temp = (Elem_t*)realloc(stk->data, stk -> capacity  / 2 * sizeof(Elem_t));
        if(temp == NULL)
            return MEM_ALLOC_ERR;
        stk->data = temp;
        stk->capacity = stk->capacity /  2;
    } else if(stk->size == stk->capacity - 1) {
        temp = (Elem_t*)realloc(stk->data, stk->capacity * 2 * sizeof(Elem_t));
        if(temp == NULL)
            return MEM_ALLOC_ERR;
        stk->data = temp;
        for(int i = 0; i < stk->size + 2; i++)
            stk->data[stk->size  + i] = VOID_ELEM;
        stk->capacity *= 2;
    }

    return NO_ERR;
}

unsigned long long int hasher (Stack* stk) {
    unsigned long long hash = 0;

    for(unsigned int i = 0; i < sizeof(Stack) - 17; i++) {
        hash += *(int*)(stk + i) % *(int*)(stk + i + 1);
    }
    return hash;
}

