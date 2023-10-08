#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void) {
    int iter = 0;
    Stack stk = {};
    STK_CTOR(&stk);
    printf("To stop session press s\n");

    while (getchar() != 's') {
        iter++;
        getchar();
        Elem_t poped = VOID_ELEM;
        printf("type 1 to push elem\ntype 2 to pop stack\ntype 3 to break stack\n");
        switch(getchar()) {
        case '1':
            printf("Print element to push:\n");
            Elem_t a;
            scanf("%d", &a);
            stack_push(&stk, a);
            break;
        case '2':
            stack_pop(&stk, &poped) ;
            printf("\nPoped element - %d\n", poped);
            break;
        case '3':
            execution(&stk);
            break;
        default: printf("Wrong key...\n");
        }
        getchar();
        print_stack(&stk);
    }
    if(iter == 0) return 0;
    put_error(&stk, stack_dtor(&stk));
    if(stack_verificator(&stk) != 0) {
        if(check_error(&stk) == 1) {
            STK_DUMP(&stk);
            return 1;
        }
    }
    return 0;
}
