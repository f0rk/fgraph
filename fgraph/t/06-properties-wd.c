#include <tap.h>
#include "fgraph.h"

/* weighted + directed */

int main() {
    fgraph_t *graph = 0;
    fgraph_return_t res = 0;
    fgraph_edge_weight_t wval = 0, *pwval = 0;
    fgraph_option_t oval = 0, *poval = 0;
    unsigned long ulval = 0, *pulval = 0;
    int ival = 0, *pival = 0;
    
    tap_plan(50);
    
    res = fgraph_init(&graph, 8, FGRAPH_OWEIGHTED|FGRAPH_ODIRECTED);
    tap_ok(res == FGRAPH_SUCCESS, "inited ok");
    tap_ok(graph != 0, "graph not null");
    
    res = fgraph_size(&graph, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "got graph size ok");
    tap_ok(ulval == 8, "graph size is 8");
    
    res = fgraph_size(&graph, pulval);
    tap_ok(res == FGRAPH_ENULL, "pulval is null");
    
    res = fgraph_options(&graph, &oval);
    tap_ok(res == FGRAPH_SUCCESS, "got graph options ok");
    tap_ok(oval == (FGRAPH_OWEIGHTED|FGRAPH_ODIRECTED), "options ok");
    
    res = fgraph_options(&graph, poval);
    tap_ok(res == FGRAPH_ENULL, "poval is null");
    
    res = fgraph_edge_add(&graph, 0, 1, 8);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 0, 2, 2);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 1, 5, 7);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 1, 2, 3);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 2, 4, 1);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 2, 3, 5);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 3, 6, 3);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 3, 7, 1);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 4, 5, 2);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 4, 6, 6);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 5, 7, 4);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 6, 7, 2);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_count_all(&graph, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "got count ok");
    tap_ok(ulval == 12, "edge count is 12");
    
    res = fgraph_edge_count_all(&graph, pulval);
    tap_ok(res == FGRAPH_ENULL, "pulval is null");
    
    res = fgraph_edge_count(&graph, 0, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "got count ok");
    tap_ok(ulval == 2, "edge count is 2");
    
    res = fgraph_edge_count(&graph, 0, pulval);
    tap_ok(res == FGRAPH_ENULL, "pulval is null");
    
    res = fgraph_edge_count(&graph, 5, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "got count ok");
    tap_ok(ulval == 1, "edge count is 1");
    
    res = fgraph_edge_count(&graph, 20, &ulval);
    tap_ok(res == FGRAPH_ENOVTX, "no such vertex");
    
    res = fgraph_edge_get_weight(&graph, 5, 7, &wval);
    tap_ok(res == FGRAPH_SUCCESS, "got weight ok");
    tap_ok(wval == 4, "weight is 4");
    
    res = fgraph_edge_get_weight(&graph, 5, 7, pwval);
    tap_ok(res == FGRAPH_ENULL, "pwval is null");
    
    res = fgraph_edge_get_weight(&graph, 7, 5, &wval);
    tap_ok(res == FGRAPH_ENOEDGE, "no such edge");
    
    res = fgraph_edge_get_weight(&graph, 4, 6, &wval);
    tap_ok(res == FGRAPH_SUCCESS, "got weight ok");
    tap_ok(wval == 6, "weight is 6");
    
    res = fgraph_edge_set_weight(&graph, 4, 6, 10);
    tap_ok(res == FGRAPH_SUCCESS, "set weight ok");
    
    res = fgraph_edge_set_weight(&graph, 6, 4, 10);
    tap_ok(res == FGRAPH_ENOEDGE, "no such edge");
    
    res = fgraph_edge_get_weight(&graph, 4, 6, &wval);
    tap_ok(res == FGRAPH_SUCCESS, "got weight ok");
    tap_ok(wval == 10, "weight is 10");
    
    res = fgraph_edge_exists(&graph, 2, 4, &ival);
    tap_ok(res == FGRAPH_SUCCESS, "checked for edge ok");
    tap_ok(ival, "edge exists");
    
    res = fgraph_edge_exists(&graph, 2, 4, pival);
    tap_ok(res == FGRAPH_ENULL, "pival is null");
    
    res = fgraph_edge_exists(&graph, 4, 2, &ival);
    tap_ok(res == FGRAPH_SUCCESS, "checked for edge ok");
    tap_ok(!ival, "no such edge");
    
    res = fgraph_edge_remove(&graph, 2, 4);
    tap_ok(res == FGRAPH_SUCCESS, "removed edge ok");
    
    res = fgraph_edge_remove(&graph, 4, 2);
    tap_ok(res == FGRAPH_ENOEDGE, "no such edge");
    
    res = fgraph_edge_get_weight(&graph, 2, 4, &wval);
    tap_ok(res == FGRAPH_ENOEDGE, "no such edge");
    
    res = fgraph_edge_set_weight(&graph, 2, 4, 10);
    tap_ok(res == FGRAPH_ENOEDGE, "no such edge");
    
    res = fgraph_edge_exists(&graph, 2, 4, &ival);
    tap_ok(res == FGRAPH_SUCCESS, "checked for edge ok");
    tap_ok(!ival, "edge does not exist");
    
    return tap_status();
}
