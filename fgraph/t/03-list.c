#include <tap.h>
#include "fgraph.h"
#include <stdio.h>

int main() {
    fgraph_list_t *list = 0;
    fgraph_return_t res = 0;
    unsigned long ulval = 0;
    long lval = 0;
    
    tap_plan(46);
    
    res = fgraph_list_init(&list);
    tap_ok(res == FGRAPH_SUCCESS, "list inited ok");
    tap_ok(list != 0, "list not null");
    
    res = fgraph_list_init(&list);
    tap_ok(res == FGRAPH_EINITED, "list already inited");
    
    res = fgraph_list_add(&list, 10);
    tap_ok(res == FGRAPH_SUCCESS, "10 added ok");
    
    res = fgraph_list_add(&list, 2);
    tap_ok(res == FGRAPH_SUCCESS, "2 added ok");
    
    res = fgraph_list_add(&list, -3);
    tap_ok(res == FGRAPH_SUCCESS, "-3 added ok");
    
    res = fgraph_list_size(&list, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "got list size ok");
    tap_ok(ulval == 3, "list size is 3");
    
    res = fgraph_list_get(&list, 1, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "got list idx 0 ok");
    tap_ok(lval == 2, "lval is 2");
    
    res = fgraph_list_get(&list, 4, &lval);
    tap_ok(res != FGRAPH_SUCCESS, "no such idx: 4");
    
    lval = 0;
    res = fgraph_list_remove(&list, 1, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "removed elem at idx 1 ok");
    tap_ok(lval == 2, "lval is 2");
    
    res = fgraph_list_size(&list, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "got list size ok");
    tap_ok(ulval == 2, "list size is 2");
    
    res = fgraph_list_add(&list, 4);
    tap_ok(res == FGRAPH_SUCCESS, "4 added ok");
    
    res = fgraph_list_add(&list, 5);
    tap_ok(res == FGRAPH_SUCCESS, "5 added ok");
    
    res = fgraph_list_size(&list, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "got list size ok");
    tap_ok(ulval == 4, "list size is 4");
    
    res = fgraph_list_set(&list, 1, -100);
    tap_ok(res == FGRAPH_SUCCESS, "set list idx 1 to -100");
    
    res = fgraph_list_get(&list, 1, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "got elem at idx 1 ok");
    tap_ok(lval == -100, "lval is -100");
    
    res = fgraph_list_size(&list, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "got list size ok");
    tap_ok(ulval == 4, "list size is 4");
    
    res = fgraph_list_clear(&list);
    tap_ok(res == FGRAPH_SUCCESS, "list cleared ok");
    tap_ok(list == 0, "list is null");
    
    res = fgraph_list_add(&list, 2);
    tap_ok(res == FGRAPH_ENULL, "list is null");
    
    res = fgraph_list_get(&list, 2, &lval);
    tap_ok(res == FGRAPH_ENULL, "list is null");
    
    res = fgraph_list_remove(&list, 2, &lval);
    tap_ok(res == FGRAPH_ENULL, "list is null");
    
    res = fgraph_list_set(&list, 2, 2);
    tap_ok(res == FGRAPH_ENULL, "list is null");
    
    res = fgraph_list_size(&list, &ulval);
    tap_ok(res == FGRAPH_ENULL, "list is null");
    
    res = fgraph_list_clear(&list);
    tap_ok(res == FGRAPH_ENULL, "list is null");
    
    res = fgraph_list_init(&list);
    tap_ok(res == FGRAPH_SUCCESS, "list inited ok");
    
    res = fgraph_list_add(&list, 1);
    tap_ok(res == FGRAPH_SUCCESS, "added ok");
    
    res = fgraph_list_add(&list, 2);
    tap_ok(res == FGRAPH_SUCCESS, "added ok");
    
    res = fgraph_list_add(&list, 3);
    tap_ok(res == FGRAPH_SUCCESS, "added ok");
    
    res = fgraph_list_add(&list, 4);
    tap_ok(res == FGRAPH_SUCCESS, "added ok");
    
    res = fgraph_list_remove(&list, 0, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "value removed ok");
    tap_ok(lval == 1, "removed elem is 1");
    
    res = fgraph_list_remove(&list, 0, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "value removed ok");
    tap_ok(lval == 2, "removed elem is 2");
    
    res = fgraph_list_remove(&list, 0, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "value removed ok");
    tap_ok(lval == 3, "removed elem is 3");
    
    res = fgraph_list_remove(&list, 0, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "value removed ok");
    tap_ok(lval == 4, "removed elem is 4");
    
    res = fgraph_list_remove(&list, 0, &lval);
    tap_ok(res == FGRAPH_EBOUNDS, "no elem at 0");
    
    return tap_status();
}
