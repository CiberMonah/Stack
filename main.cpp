#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void) {

    Stack stk;
    STK_CTOR(&stk);
    printf("To stop session press s\n");
    while (getchar() != 's') {
        //stack_dtor(&stk); //use to brake program, and it will detect it:)
        getchar();
        Elem_t poped = void_elem;
        printf("type 1 to push elem\ntype 2 to pop stack\n");
        switch(getchar()) {
        case'1':
            printf("Print element to push:\n");
            Elem_t a;
            scanf("%d", &a);
            get_error(stack_push(&stk, a));
            break;
        case'2':
            if(get_error(stack_pop(&stk, &poped)) == no_err)
                printf("\nPoped element - %d\n", poped);

            break;
        default: printf("Wrong key...\n");
        }
        STK_DUMP(&stk);
        getchar();

    }
    get_error(stack_dtor(&stk));
    return 0;
}
