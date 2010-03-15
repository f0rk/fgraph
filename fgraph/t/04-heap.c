#include <tap.h>
#include "fgraph.h"

int main() {
    fgraph_heap_t *heap = 0;
    fgraph_return_t res = 0;
    unsigned long ulval = 0;
    long lval = 0;
    
    tap_plan(17);
    
    res = fgraph_heap_init(&heap, 10);
    tap_ok(res == FGRAPH_SUCCESS, "heap inited ok");
    
    res = fgraph_heap_insert(&heap, 0, 10);
    tap_ok(res == FGRAPH_SUCCESS, "value added ok");
    
    res = fgraph_heap_insert(&heap, 20, 3);
    tap_ok(res == FGRAPH_EBOUNDS, "value not added, out of bounds");
    
    res = fgraph_heap_size(&heap, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "heap size returned ok");
    tap_ok(ulval == 1, "heap size is 1");
    
    res = fgraph_heap_insert(&heap, 1, 8);
    tap_ok(res == FGRAPH_SUCCESS, "value added ok");
    
    res = fgraph_heap_insert(&heap, 2, 6);
    tap_ok(res == FGRAPH_SUCCESS, "value added ok");
    
    res = fgraph_heap_insert(&heap, 3, 20);
    tap_ok(res == FGRAPH_SUCCESS, "value added ok");
    
    res = fgraph_heap_remove(&heap, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "value removed ok");
    tap_ok(ulval == 2, "min-key is 2");
    
    res = fgraph_heap_decrease(&heap, 3, 4);
    tap_ok(res == FGRAPH_SUCCESS, "key decreased ok");
    
    res = fgraph_heap_remove(&heap, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "value removed ok");
    tap_ok(ulval == 3, "min-key is 3");
    
    res = fgraph_heap_size(&heap, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "size returned ok");
    tap_ok(ulval == 2, "size is 2");
    
    res = fgraph_heap_clear(&heap);
    tap_ok(res == FGRAPH_SUCCESS, "heap cleared ok");
    tap_ok(heap == 0, "heap is null");
    
    return tap_status();
}
