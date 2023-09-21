#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void) {

    Stack stk = {};
    if(stack_ctor(&stk) == no_err) {
        printf("Stack created\n");
    } else {
        printf("Stack wasnt created!\n");
        return 1;
    }
    printf("To stop session press s\n");
    while (getchar() != 's') {
        getchar();
        printf("type 1 to push elem\ntype 2 to pop stack\ntype 3 to print info\n");
        switch(getchar()) {
        case'1':
            printf("Print element to push:\n");
            Elem_t a;
            scanf("%d", &a);
            get_error(stack_push(&stk, a));
            break;
        case'2':
            get_error(stack_pop(&stk));
            break;
        default:
            printf("sosi hui");
            //getchar();
        }
        dump(&stk);
        getchar();

    }
    get_error(stack_dtor(&stk));
    return 0;
}
