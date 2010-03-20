#include <tap.h>
#include "fgraph.h"

int main() {
    fgraph_t *graph = 0;
    fgraph_return_t res = 0;
    fgraph_edge_weight_t wval = 0, *pwval = 0;
    fgraph_vec_t *rvec = 0;
    long lval = 0;
    unsigned long ulval = 0;
    
    tap_plan(107);
    
    /* weighted */
    res = fgraph_init(&graph, 8, FGRAPH_ODIRECTED|FGRAPH_OWEIGHTED);
    tap_ok(res == FGRAPH_SUCCESS, "graph inited ok");
    tap_ok(graph != 0, "graph not null");
    
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
    
    res = fgraph_sp_dag(&graph, 0, 7, &rvec, &wval);
    tap_ok(res == FGRAPH_SUCCESS, "found shortest path ok");
    tap_ok(rvec != 0, "rvec properly populated");
    tap_ok(wval == 8, "path weight is 8");
    
    res = fgraph_vec_size(&rvec, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "got path size ok");
    tap_ok(ulval == 4, "path is of length 4");
    
    res = fgraph_vec_get(&rvec, 0, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "got rvec[0] ok");
    tap_ok(lval == 0, "rvec[0] == 0");
    
    res = fgraph_vec_get(&rvec, 1, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "got rvec[1] ok");
    tap_ok(lval == 2, "rvec[1] == 2");
    
    res = fgraph_vec_get(&rvec, 2, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "got rvec[2] ok");
    tap_ok(lval == 3, "rvec[2] == 3");
    
    res = fgraph_vec_get(&rvec, 3, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "got rvec[3] ok");
    tap_ok(lval == 7, "rvec[3] == 7");
    
    res = fgraph_vec_clear(&rvec);
    tap_ok(res == FGRAPH_SUCCESS, "rvec cleared ok");
    tap_ok(rvec == 0, "rvec is null");
    
    res = fgraph_sp_dag(&graph, 0, 7, &rvec, pwval);
    tap_ok(res == FGRAPH_ENULL, "pwval is null");
    
    res = fgraph_clear(&graph);
    tap_ok(res == FGRAPH_SUCCESS, "graph cleared ok");
    tap_ok(graph == 0, "graph is null");
    
    res = fgraph_sp_dag(&graph, 0, 7, &rvec, &wval);
    tap_ok(res == FGRAPH_ENULL, "graph is null");
    
    /* unweighted */
    res = fgraph_init(&graph, 8, FGRAPH_ODIRECTED);
    tap_ok(res == FGRAPH_SUCCESS, "graph inited ok");
    tap_ok(graph != 0, "graph not null");
    
    res = fgraph_edge_add(&graph, 0, 1, 8);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 0, 2, 2);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 1, 2, 3);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 1, 5, 7);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 2, 4, 1);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 2, 3, 5);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 3, 6, 3);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 4, 5, 2);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 4, 6, 6);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 5, 7, 4);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_edge_add(&graph, 6, 7, 2);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    res = fgraph_sp_dag(&graph, 0, 7, &rvec, &wval);
    tap_ok(res == FGRAPH_SUCCESS, "found shortest path ok");
    tap_ok(rvec != 0, "rvec properly populated");
    
    res = fgraph_vec_size(&rvec, &ulval);
    tap_ok(res == FGRAPH_SUCCESS, "got path size ok");
    tap_ok(ulval == 4, "path is of length 4");
    
    res = fgraph_vec_get(&rvec, 0, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "got rvec[0] ok");
    tap_ok(lval == 0, "rvec[0] == 0");
    
    res = fgraph_vec_get(&rvec, 1, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "got rvec[1] ok");
    tap_ok(lval == 1, "rvec[1] == 1");
    
    res = fgraph_vec_get(&rvec, 2, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "got rvec[2] ok");
    tap_ok(lval == 5, "rvec[2] == 5");
    
    res = fgraph_vec_get(&rvec, 3, &lval);
    tap_ok(res == FGRAPH_SUCCESS, "got rvec[3] ok");
    tap_ok(lval == 7, "rvec[3] == 7");
    
    res = fgraph_vec_clear(&rvec);
    tap_ok(res == FGRAPH_SUCCESS, "rvec cleared ok");
    tap_ok(rvec == 0, "rvec is null");
    
    res = fgraph_clear(&graph);
    tap_ok(res == FGRAPH_SUCCESS, "graph cleared ok");
    tap_ok(graph == 0, "graph is null");
    
    /* not a DAG undirected */
    res = fgraph_init(&graph, 8, FGRAPH_ODEFAULT);
    tap_ok(res == FGRAPH_SUCCESS, "graph inited ok");
    tap_ok(graph != 0, "graph not null");
    
    wval = 0;
    res = fgraph_sp_dag(&graph, 0, 7, &rvec, &wval);
    tap_ok(res == FGRAPH_ENOTADAG, "not a dag");
    tap_ok(rvec == 0, "rvec not inited");
    tap_ok(wval == 0, "wval not set");
    
    res = fgraph_clear(&graph);
    tap_ok(res == FGRAPH_SUCCESS, "graph cleared ok");
    tap_ok(graph == 0, "graph is null");
    
    /* not a DAG directed */
    res = fgraph_init(&graph, 8, FGRAPH_ODIRECTED|FGRAPH_OWEIGHTED);
    tap_ok(res == FGRAPH_SUCCESS, "graph inited ok");
    tap_ok(graph != 0, "graph not null");
    
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
    
    res = fgraph_edge_add(&graph, 3, 0, 0);
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
    
    wval = 0;
    res = fgraph_sp_dag(&graph, 0, 7, &rvec, &wval);
    tap_ok(res == FGRAPH_ENOTADAG, "not a dag");
    tap_ok(rvec == 0, "rvec not inited");
    tap_ok(wval == 0, "wval unset");
    
    res = fgraph_clear(&graph);
    tap_ok(res == FGRAPH_SUCCESS, "graph cleared ok");
    tap_ok(graph == 0, "graph is null");
    
    /* no path */
    res = fgraph_init(&graph, 8, FGRAPH_ODIRECTED|FGRAPH_OWEIGHTED);
    tap_ok(res == FGRAPH_SUCCESS, "graph inited ok");
    tap_ok(graph != 0, "graph not null");
    
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
    
    res = fgraph_edge_add(&graph, 6, 7, 2);
    tap_ok(res == FGRAPH_SUCCESS, "edge added ok");
    
    wval = 0;
    res = fgraph_sp_dag(&graph, 7, 0, &rvec, &wval);
    tap_ok(res == FGRAPH_ENOPATH, "no path");
    tap_ok(rvec == 0, "rvec not inited");
    tap_ok(wval == 0, "wval unset");
    
    res = fgraph_clear(&graph);
    tap_ok(res == FGRAPH_SUCCESS, "graph cleared ok");
    tap_ok(graph == 0, "graph is null");
    
    return tap_status();
}
