#include <tap.h>
#include "fgraph.h"

int main() {
    fgraph_vec_t *vec = 0;
    fgraph_return_t res = 0;
    unsigned long ulval = 0;
    long lval = 0;
    
    tap_plan(15);
    
    res = fgraph_vec_init(&vec, 10);
    tap_ok(res == FGRAPH_SUCCESS, "vec inited ok");
    tap_ok(vec != 0, "vec not null");
    
    res = fgraph_vec_size(&vec, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "size retrieved ok");
    tap_ok(ulval == 10, "vec is of size 10");
    
    res = fgraph_vec_set(&vec, 0, 12);
    tap_ok(res == FGRAPH_SUCCESS, "vec set ok");
    
    res = fgraph_vec_get(&vec, 0, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "vec get ok");
    tap_ok(lval == 12, "vec[0] is 12");
    
    res = fgraph_vec_clear(&vec);
    tap_ok(res == FGRAPH_SUCCESS, "vec cleared ok");
    tap_ok(vec == 0, "vec set to null");
    
    res = fgraph_vec_init_set(&vec, 10, -2);
    tap_ok(res == FGRAPH_SUCCESS, "vec inited and set ok");
    tap_ok(vec != 0, "vec not null");
    
    res = fgraph_vec_get(&vec, 2, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "vec get ok");
    tap_ok(lval == -2, "vec[2] is -2");
    
    res = fgraph_vec_clear(&vec);
    tap_ok(res == FGRAPH_SUCCESS, "vec cleared ok");
    tap_ok(vec == 0, "vec set to null");
    
    return tap_status();
}
