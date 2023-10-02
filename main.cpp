#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// static void check_sizes()
// {
//     printf("%u\n", sizeof(unsigned long));
//     printf("%u\n", sizeof(Elem_t*));
//     printf("%u\n", sizeof(int));
//     printf("%u\n", sizeof(int));
//     printf("%u\n", sizeof(bool));
//     printf("%u\n", sizeof(int));
//     printf("%u\n", sizeof(int));
//     printf("%u\n", sizeof(const char*));
//     printf("%u\n", sizeof(const char*));
//     printf("%u\n", sizeof(const char*));
//     printf("%u\n", sizeof(unsigned long));
//     printf("%u\n", sizeof(void (*)(void*)));
//     printf("%u\n", sizeof(unsigned long));
// }

int main(void) {
    //check_sizes();
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
            printf("%s:Hash: %lu\n", __PRETTY_FUNCTION__, stk.hash);
            printf("%s:Hasher: %lu\n", __PRETTY_FUNCTION__, hasher(&stk));
            Elem_t a;
            scanf("%d", &a);
            printf("%s:Hash: %lu\n", __PRETTY_FUNCTION__, stk.hash);
            printf("%s:Hasher: %lu\n", __PRETTY_FUNCTION__, hasher(&stk));
            printf("dfjsclkjflskd");
            stack_push(&stk, a);
            break;
        case '2':
            //stack_pop(nullptr, &poped);
            stack_pop(&stk, &poped) ;
            printf("\nPoped element - %d\n", poped);
            break;
        case '3':
            // stk.left_canary ++;          // to test left canarie
            // stk.hash = hasher(&stk);
            // stk.right_canary ++;          // to test right canarie
            // stk.hash = hasher(&stk);
                        //with right hash program detects error
            execution(&stk);      // Hash is more valuable detecting error than check_canarioes,
            stk.hash = hasher(&stk);            // So if canaries are different and hash is not right it is hash error
            break;                              // But if hash is right -- it s canarie error
        default: printf("Wrong key...\n");
        }
        //STK_DUMP(&stk);
        getchar();
        //printf("Stack:\n");
        print_stack(&stk);
    }
    if(iter == 0) return 0; //if first chois was finish programm
    put_error(&stk, stack_dtor(&stk));
    if(stack_verificator(&stk) != 0) {
        if(check_error(&stk) == 1) {
            STK_DUMP(&stk);
            abort();
        }
    }
    return 0;
}
