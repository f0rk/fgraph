#include <fgraph.h>
#include <stdio.h>

int main() {
    fgraph_t *graph = 0;
    fgraph_vec_t *vec = 0;
    fgraph_edge_weight_t weight = 0;
    fgraph_return_t res = 0;
    unsigned long i = 0, len = 0;
    long val = 0;
    
    /*
     * Create a graph with 8 vertices that is both
     * weighted and directed. Note that vertex indexing
     * starts at 0, so that you may address the vertices
     * as 0 through 7.
     */
    res = fgraph_init(&graph, 8, FGRAPH_OWEIGHTED|FGRAPH_ODIRECTED);
    if(res != FGRAPH_SUCCESS) {
        return 1; /* couldn't create our graph */
    }
    
    /*
     * Add some edges. See simple.png and simple.dot for
     * what this graph looks like.
     */
    fgraph_edge_add(&graph, 0, 1, 8);
    fgraph_edge_add(&graph, 0, 2, 2);
    fgraph_edge_add(&graph, 1, 5, 7);
    fgraph_edge_add(&graph, 1, 2, 3);
    fgraph_edge_add(&graph, 2, 4, 1);
    fgraph_edge_add(&graph, 2, 3, 5);
    fgraph_edge_add(&graph, 3, 6, 3);
    fgraph_edge_add(&graph, 3, 7, 1);
    fgraph_edge_add(&graph, 4, 5, 2);
    fgraph_edge_add(&graph, 4, 6, 6);
    fgraph_edge_add(&graph, 5, 7, 4);
    fgraph_edge_add(&graph, 6, 7, 2);
    
    /*
     * Find the shortest path from 0 to 7. no need to
     * initialize our result vector, it will be done for
     * us. The total weight of the path will be stored in
     * weight.
     */
    res = fgraph_sp_dag(&graph, 0, 7, &vec, &weight);
    if(res != FGRAPH_SUCCESS) {
        return 1; /* couldn't find a path */
    }
    
    /*
     * Print out the shortest path from 0 to 7, then
     * print the weight of that path. See simplesp.dot
     * and simplesp.png for a visualization of the
     * resulting shortest path.
     */
    fgraph_vec_length(&vec, &len);
    for(i = 0; i < len; ++i) {
        fgraph_vec_get(&vec, i, &val);
        printf("%d -> ", val);
    }
    fgraph_vec_get(&vec, len, &val);
    printf("%d\n", val);
    
    printf("%d\n", weight);
    
    return 0;
}
