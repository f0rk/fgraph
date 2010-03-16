#include <tap.h>
#include "fgraph.h"

int main() {
    fgraph_stack_t *stack = 0;
    fgraph_return_t res = 0;
    unsigned long ulval = 0, *pulval = 0;
    long lval = 0, *plval = 0;
    
    tap_plan(32);
    
    res = fgraph_stack_init(&stack);
    tap_ok(res == FGRAPH_SUCCESS, "inited ok");
    
    res = fgraph_stack_push(&stack, 30);
    tap_ok(res == FGRAPH_SUCCESS, "pushed ok");
    
    res = fgraph_stack_push(&stack, -20);
    tap_ok(res == FGRAPH_SUCCESS, "pushed ok");
    
    res = fgraph_stack_push(&stack, 10);
    tap_ok(res == FGRAPH_SUCCESS, "pushed ok");
    
    res = fgraph_stack_size(&stack, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "returned size ok");
    tap_ok(ulval == 3, "size is 3");
    
    res = fgraph_stack_pop(&stack, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "popped ok");
    tap_ok(lval == 10, "10 was popped");
    
    res = fgraph_stack_pop(&stack, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "popped ok");
    tap_ok(lval == -20, "-20 was popped");
    
    res = fgraph_stack_pop(&stack, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "popped ok");
    tap_ok(lval == 30, "30 was popped");
    
    res = fgraph_stack_pop(&stack, &lval);
    tap_ok(res == FGRAPH_EEMPTY, "stack is empty");
    
    res = fgraph_stack_clear(&stack);
    tap_ok(res == FGRAPH_SUCCESS, "stack cleared ok");
    tap_ok(stack == 0, "stack is null");
    
    res = fgraph_stack_push(&stack, 50);
    tap_ok(res == FGRAPH_ENULL, "stack is null");
    
    res = fgraph_stack_pop(&stack, &lval);
    tap_ok(res == FGRAPH_ENULL, "stack is null");
    
    res = fgraph_stack_size(&stack, &ulval);
    tap_ok(res == FGRAPH_ENULL, "stack is null");
    
    res = fgraph_stack_init(&stack);
    tap_ok(res == FGRAPH_SUCCESS, "inited ok");
    
    res = fgraph_stack_push(&stack, 1);
    tap_ok(res == FGRAPH_SUCCESS, "pushed ok");
    
    res = fgraph_stack_push(&stack, 2);
    tap_ok(res == FGRAPH_SUCCESS, "pushed ok");
    
    res = fgraph_stack_push(&stack, 3);
    tap_ok(res == FGRAPH_SUCCESS, "pushed ok");
    
    res = fgraph_stack_size(&stack, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "returned size ok");
    tap_ok(ulval == 3, "size is 3");
    
    res = fgraph_stack_pop(&stack, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "popped ok");
    tap_ok(lval == 3, "3 was popped");
    
    res = fgraph_stack_size(&stack, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "returned size ok");
    tap_ok(ulval == 2, "size is 2");
    
    res = fgraph_stack_pop(&stack, plval);
    tap_ok(res == FGRAPH_ENULL, "lval is null");
    
    res = fgraph_stack_size(&stack, pulval);
    tap_ok(res == FGRAPH_ENULL, "ulval is null");
    
    res = fgraph_stack_clear(&stack);
    tap_ok(res == FGRAPH_SUCCESS, "stack cleared ok");
    tap_ok(stack == 0, "stack is null");
    
    return tap_status();
}
