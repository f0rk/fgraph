#include <tap.h>
#include "fgraph.h"

int main() {
    fgraph_t *graph = 0;
    fgraph_return_t res = 0;
    
    tap_plan(12);
    
    res = fgraph_init(&graph, 10, FGRAPH_ODEFAULT);
    tap_ok(res == FGRAPH_SUCCESS, "graph inited ok");
    tap_ok(graph != 0, "graph not null");
    
    res = fgraph_init(&graph, 10, FGRAPH_ODEFAULT);
    tap_ok(res == FGRAPH_EINITED, "graph already inited");
    
    res = fgraph_clear(&graph);
    tap_ok(res == FGRAPH_SUCCESS, "graph cleared ok");
    tap_ok(graph == 0, "graph is null");
    
    res = fgraph_clear(&graph);
    tap_ok(res == FGRAPH_ENULL, "graph is null");
    
    res = fgraph_init(&graph, 10, FGRAPH_ODEFAULT);
    tap_ok(res == FGRAPH_SUCCESS, "graph inited ok");
    tap_ok(graph != 0, "graph not null");
    
    res = fgraph_init(&graph, 10, FGRAPH_ODEFAULT);
    tap_ok(res == FGRAPH_EINITED, "graph already inited");
    
    res = fgraph_clear(&graph);
    tap_ok(res == FGRAPH_SUCCESS, "graph cleared ok");
    tap_ok(graph == 0, "graph is null");
    
    res = fgraph_clear(&graph);
    tap_ok(res == FGRAPH_ENULL, "graph is null");
    
    return tap_status();
}
