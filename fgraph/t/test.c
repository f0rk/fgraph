#include <stdio.h>
#include <stdlib.h>
#include "../src/fgraph.h"

int main() {
    fgraph_vec_t *vec = 0, *rvec = 0; long res = 0, i = 0; fgraph_t *graph = 0; unsigned long ures = 0;
    fgraph_edge_weight_t rweight = 0; fgraph_heap_t *heap = 0;
    
    printf("init returned %d\n", fgraph_vec_init(&vec, 4));
    
    printf("set returned %d\n", fgraph_vec_set(&vec, 0, 1));
    printf("set returned %d\n", fgraph_vec_set(&vec, 1, 2));
    printf("set returned %d\n", fgraph_vec_set(&vec, 2, 3));
    printf("set returned %d\n", fgraph_vec_set(&vec, 3, 4));
    
    fgraph_vec_get(&vec, 0, &res);
    printf("vec[0] is %d\n", res);
    
    fgraph_vec_get(&vec, 1, &res);
    printf("vec[1] is %d\n", res);
    
    fgraph_vec_get(&vec, 2, &res);
    printf("vec[2] is %d\n", res);
    
    fgraph_vec_get(&vec, 3, &res);
    printf("vec[3] is %d\n", res);
    
    printf("vec[10] returned %d\n", fgraph_vec_get(&vec, 10, &res));
    
    printf("vec_clear returned %d\n", fgraph_vec_clear(&vec));
    
    res = fgraph_init(&graph, 10, FGRAPH_ODIRECTED|FGRAPH_OWEIGHTED|FGRAPH_ONOSELFL);
    printf("fgraph_init returned %d\n", res);
    
    printf("graph size is %d\n", graph->size);
    
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 0, 1, 10));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 0, 2, 10));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 0, 3, 10));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 0, 4, 10));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 0, 20, 10));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 5, 5, 10));
    
    printf("edge_count_all returned %d\n", fgraph_edge_count_all(&graph, &ures));
    printf("edge_count_all is %d (exp 4)\n", ures);
    
    printf("edge_count(0) returned %d\n", fgraph_edge_count(&graph, 0, &ures));
    printf("edge_count(0) is %d (exp 4)\n", ures);
    
    printf("edge_count(1) returned %d\n", fgraph_edge_count(&graph, 1, &ures));
    printf("edge_count(1) is %d (exp 0)\n", ures);
    
    res = fgraph_clear(&graph);
    printf("fgraph_clear returned %d\n", res);
    
    res = fgraph_init(&graph, 10, FGRAPH_ODIRECTED);
    printf("fgraph_init returned %d\n", res);
    
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 0, 2, 4));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 0, 3, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 1, 3, 6));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 1, 4, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 2, 5, 2));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 3, 4, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 3, 5, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 3, 6, 2));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 4, 7, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 5, 8, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 6, 7, 6));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 6, 9, 2));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 8, 9, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 9, 7, 2));
    
    res = fgraph_sort_topological(&graph, &vec);
    printf("sort_topological returned %d\n", res);
    
    printf("vec[0] returns %d\n", fgraph_vec_get(&vec, 0, &res));
    printf("vec[0] is %d\n", res);
    
    printf("vec[1] returns %d\n", fgraph_vec_get(&vec, 1, &res));
    printf("vec[1] is %d\n", res);
    
    printf("vec[2] returns %d\n", fgraph_vec_get(&vec, 2, &res));
    printf("vec[2] is %d\n", res);
    
    printf("vec[3] returns %d\n", fgraph_vec_get(&vec, 3, &res));
    printf("vec[3] is %d\n", res);
    
    printf("vec[4] returns %d\n", fgraph_vec_get(&vec, 4, &res));
    printf("vec[4] is %d\n", res);
    
    printf("vec[5] returns %d\n", fgraph_vec_get(&vec, 5, &res));
    printf("vec[5] is %d\n", res);
    
    printf("vec[6] returns %d\n", fgraph_vec_get(&vec, 6, &res));
    printf("vec[6] is %d\n", res);
    
    printf("vec[7] returns %d\n", fgraph_vec_get(&vec, 7, &res));
    printf("vec[7] is %d\n", res);
    
    printf("vec[8] returns %d\n", fgraph_vec_get(&vec, 8, &res));
    printf("vec[8] is %d\n", res);
    
    printf("vec[9] returns %d\n", fgraph_vec_get(&vec, 9, &res));
    printf("vec[9] is %d\n", res);
    
    res = fgraph_sp_dag(&graph, 3, 9, &rvec, &rweight);
    printf("sp_dag returns %d\n", res);
    
    printf("sp from 3 to 9 is %d\n", rweight);
    
    res = fgraph_vec_size(&rvec, &ures);
    printf("vec_size returns %d\n", res);
    printf("vec_size is %d\n", ures);
    for(i = 0; i < ures; ++i) {
        fgraph_vec_get(&rvec, i, &res);
        printf("vec[%d] is %d\n", i, res);
    }
    
    printf("vec_clear returns %d\n", fgraph_vec_clear(&vec));
    printf("fgraph_clear returns %d\n", fgraph_clear(&graph));
    
    printf("heap_init returns %d\n", fgraph_heap_init(&heap, 10));
    printf("heap_insert(%d,%d) returns %d\n", 0, 9, fgraph_heap_insert(&heap, 0, 9));
    printf("heap_insert(%d,%d) returns %d\n", 1, 7, fgraph_heap_insert(&heap, 1, 7));
    printf("heap_insert(%d,%d) returns %d\n", 2, 18, fgraph_heap_insert(&heap, 2, 18));
    printf("heap_insert(%d,%d) returns %d\n", 3, 4, fgraph_heap_insert(&heap, 3, 4));
    printf("heap_insert(%d,%d) returns %d\n", 4, 3, fgraph_heap_insert(&heap, 4, 3));
    printf("heap_insert(%d,%d) returns %d\n", 5, -2, fgraph_heap_insert(&heap, 5, -2));
    printf("heap_insert(%d,%d) returns %d\n", 6, 5, fgraph_heap_insert(&heap, 6, 5));
    printf("heap_insert(%d,%d) returns %d\n", 7, 9, fgraph_heap_insert(&heap, 7, 9));
    printf("heap_insert(%d,%d) returns %d\n", 8, -10, fgraph_heap_insert(&heap, 8, -10));
    printf("heap_insert(%d,%d) returns %d\n", 9, 1, fgraph_heap_insert(&heap, 9, 1));
    printf("heap_size returns %d\n", fgraph_heap_size(&heap, &ures));
    printf("heap_size is %d (exp 10)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 8)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 5)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 9)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 4)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 3)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 6)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 1)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 0 or 7)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 7 or 0)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 2)\n", ures);
    
    printf("heap_clear returns %d\n", fgraph_heap_clear(&heap));
    
    printf("heap_init returns %d\n", fgraph_heap_init(&heap, 10));
    printf("heap_insert(%d,%d) returns %d\n", 0, 9, fgraph_heap_insert(&heap, 0, 9));
    printf("heap_insert(%d,%d) returns %d\n", 1, 7, fgraph_heap_insert(&heap, 1, 7));
    printf("heap_insert(%d,%d) returns %d\n", 2, 18, fgraph_heap_insert(&heap, 2, 18));
    printf("heap_insert(%d,%d) returns %d\n", 3, 4, fgraph_heap_insert(&heap, 3, 4));
    printf("heap_insert(%d,%d) returns %d\n", 4, 3, fgraph_heap_insert(&heap, 4, 3));
    printf("heap_insert(%d,%d) returns %d\n", 5, -2, fgraph_heap_insert(&heap, 5, -2));
    printf("heap_insert(%d,%d) returns %d\n", 6, 5, fgraph_heap_insert(&heap, 6, 5));
    printf("heap_insert(%d,%d) returns %d\n", 7, 9, fgraph_heap_insert(&heap, 7, 9));
    printf("heap_insert(%d,%d) returns %d\n", 8, -10, fgraph_heap_insert(&heap, 8, -10));
    printf("heap_insert(%d,%d) returns %d\n", 9, 1, fgraph_heap_insert(&heap, 9, 1));
    printf("heap_size returns %d\n", fgraph_heap_size(&heap, &ures));
    printf("heap_size is %d (exp 10)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 8)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 5)\n", ures);
    
    res = fgraph_heap_decrease(&heap, 7, -2);
    printf("heap_decrease returns %d\n", res);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 7)\n", ures);
    
    res = fgraph_heap_decrease(&heap, 2, 6);
    printf("heap_decrease returns %d\n", res);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 9)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 4)\n", ures);
    
    res = fgraph_heap_decrease(&heap, 0, 8);
    printf("heap_decrease returns %d\n", res);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 3)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 6)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 2)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 1)\n", ures);
    
    res = fgraph_heap_remove(&heap, &ures);
    printf("heap_remove returns %d\n", res);
    printf("heap_remove is %d (exp 0)\n", ures);
    
    printf("heap_clear returns %d\n", fgraph_heap_clear(&heap));
    
    res = fgraph_init(&graph, 10, FGRAPH_ODIRECTED);
    printf("fgraph_init returned %d\n", res);
    
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 0, 2, 4));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 0, 3, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 1, 3, 6));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 1, 4, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 2, 5, 2));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 3, 4, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 3, 5, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 3, 6, 2));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 4, 7, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 5, 8, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 6, 7, 6));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 6, 9, 2));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 8, 9, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 9, 7, 2));
    res = fgraph_sp_dijkstra(&graph, 3, 9, &rvec, &rweight);
    printf("sp_dijkstra returns %d\n", res);
    
    printf("sp from 3 to 9 is %d\n", rweight);
    
    res = fgraph_vec_size(&rvec, &ures);
    printf("vec_size returns %d\n", res);
    printf("vec_size is %d\n", ures);
    for(i = 0; i < ures; ++i) {
        fgraph_vec_get(&rvec, i, &res);
        printf("vec[%d] is %d\n", i, res);
    }
    
    printf("vec_clear returns %d\n", fgraph_vec_clear(&rvec));
    printf("fgraph_clear returns %d\n", fgraph_clear(&graph));
    
    res = fgraph_init(&graph, 10, FGRAPH_ODEFAULT);
    printf("fgraph_init returned %d\n", res);
    
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 0, 2, 4));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 0, 3, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 1, 3, 6));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 1, 4, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 2, 5, 2));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 3, 4, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 3, 5, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 3, 6, 2));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 4, 7, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 5, 8, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 6, 7, 6));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 6, 9, 2));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 8, 9, 1));
    printf("edge_add returned %d\n", fgraph_edge_add(&graph, 9, 7, 2));
    res = fgraph_sp_bfs(&graph, 3, 9, &rvec);
    printf("sp_bfs returns %d\n", res);
    
    res = fgraph_vec_size(&rvec, &ures);
    printf("vec_size returns %d\n", res);
    printf("vec_size is %d\n", ures);
    for(i = 0; i < ures; ++i) {
        fgraph_vec_get(&rvec, i, &res);
        printf("vec[%d] is %d\n", i, res);
    }
    
    printf("vec_clear returns %d\n", fgraph_vec_clear(&rvec));
    printf("fgraph_clear returns %d\n", fgraph_clear(&graph));
    
    return 0;
}
