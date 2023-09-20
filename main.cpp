#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void) {
    Stack stk;
    stack_ctor(&stk);

    stack_push(&stk, 5);
    dump(&stk);
    stack_dtor(&stk);

    /*printf("To stop session press s\n");
    while (getchar() == 's') {
        getchar();
        Stack stk = {};
        stack_ctor(&stk);
        printf("type 1 to push elem\ntype 2 to pop stack\ntype 3 to print info\n");

        switch(getchar()) {
        case'1':
            printf("Print element to push:\n");
            Elem_t a;
            scanf("%d", &a);
            stack_push(&stk, a);
            //break;
        case'2':
            if(stack_pop(&stk) == no_err)
                printf("Pop succesfuly");
            else
                printf("Pop wasnt succesfully");
            break;
        case'3':
            dump(&stk);
            break;
        default:
            printf("sosi hui");
            //getchar();
        }
        getchar();

    }
    return 0;*/
}
