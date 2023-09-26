#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void) {

    Stack stk;
    STK_CTOR(&stk);
    printf("To stop session press s\n");
    while (getchar() != 's') {
        getchar();
        Elem_t poped = VOID_ELEM;
        printf("type 1 to push elem\ntype 2 to pop stack\n");
        switch(getchar()) {
        case'1':
            printf("Print element to push:\n");
            Elem_t a;
            scanf("%d", &a);
            put_error(&stk, stack_push(&stk, a));
            break;
        case'2':
            stack_pop(&stk, &poped) ;
            printf("\nPoped element - %d\n", poped);
            break;
        default: printf("Wrong key...\n");
        }
        //STK_DUMP(&stk);
        getchar();
        printf("Stack:\n");
        print_stack(&stk);

    }
    put_error(&stk, stack_dtor(&stk));
    if(stack_verificator(&stk) != 0) {
        if(check_error(&stk) == 1) {
            STK_DUMP(&stk);
            abort();
        }
    }
    return 0;
}
