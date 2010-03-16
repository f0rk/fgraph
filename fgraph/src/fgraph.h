#include <limits.h>

/* option constants */
enum fgraph_option_t {
    FGRAPH_ODEFAULT    = 1, //use the default settings, probably unweighted, undirected
    FGRAPH_OWEIGHTED   = 2, //weighted graph
    FGRAPH_ODIRECTED   = 8, //directed graph
    FGRAPH_ODENSE      = 16, //dense graph
    FGRAPH_ONOSELFL    = 32, //no self loops
    FGRAPH_ONOPARALLEL = 64 //no parallel edges
};

typedef enum fgraph_option_t fgraph_option_t;

enum fgraph_return_t {
    /* success constants */
    FGRAPH_SUCCESS     = 0,

    /* error constants */
    FGRAPH_ENOMEM      = 1, //no memory
    FGRAPH_ENOVTX      = 2, //no such vertex exists
    FGRAPH_EBOUNDS     = 4, //out of bounds
    FGRAPH_ENOEDGE     = 8, //no such edge exists
    FGRAPH_EUNSUP      = 16, //unsupported operation
    FGRAPH_EILLOPT     = 32, //illegal option configuration passed
    FGRAPH_ENULL       = 64, //got a null pointer expecting not null
    FGRAPH_ESELFL      = 128, //attempted addition of a self loop
    FGRAPH_EINITED     = 256, //this data structure has already been initialized
    FGRAPH_EPARALLEL   = 512, //parallel edge not allowed
    FGRAPH_ENOTADAG    = 1024, //graph wasn't a dag
    FGRAPH_EUNKNOWN    = 2048, //don't know what caused the error
    FGRAPH_ENOPATH     = 4096, //no path between vertexes
    FGRAPH_EEXISTS     = 8192, //element exists and may not be updated
    FGRAPH_EEMPTY      = 16384, //empty data structure
    FGRAPH_EORDER      = 32768, //violation of some ordering constraint (e.g. >)
    FGRAPH_ESIGN       = 65536 //bad sign, ie a negative number where not expected
};

typedef enum fgraph_return_t fgraph_return_t;

/* fgraph types */
typedef long fgraph_edge_weight_t;
#define FGRAPH_EDGE_WEIGHT_MAX LONG_MAX
#define FGRAPH_EDGE_WEIGHT_MIN LONG_MIN

struct fgraph_edge_t {
    struct fgraph_edge_t *next;
    unsigned long oid; //id of the other vertex
    fgraph_edge_weight_t weight; 
};

typedef struct fgraph_edge_t fgraph_edge_t;

struct fgraph_t {
    fgraph_option_t options;
    unsigned long size;
    unsigned long ecnt;
    fgraph_edge_t **vtx_to_edge;
};

typedef struct fgraph_t fgraph_t;

struct fgraph_vector_t {
    long *arr;
    unsigned long size;
};

typedef struct fgraph_vector_t fgraph_vec_t;

struct fgraph_node_t {
    struct fgraph_node_t *next;
    struct fgraph_node_t *prev;
    long val;
};

typedef struct fgraph_node_t fgraph_node_t;

struct fgraph_stack_t {
    fgraph_node_t *top;
    unsigned long size;
};

typedef struct fgraph_stack_t fgraph_stack_t;

struct fgraph_list_t {
    fgraph_node_t *head;
    fgraph_node_t *tail;
    unsigned long size;
};

typedef struct fgraph_list_t fgraph_list_t;

struct fgraph_heap_t {
    unsigned long n, size;
    long *pq, *qp;
    fgraph_edge_weight_t *pri;
};

typedef struct fgraph_heap_t fgraph_heap_t;

/* initialization and destruction */
fgraph_return_t fgraph_init(fgraph_t **graph, unsigned long size, fgraph_option_t options);
fgraph_return_t fgraph_clear(fgraph_t **graph);

/* vectors */
fgraph_return_t fgraph_vec_init(fgraph_vec_t **vec, unsigned long size);
fgraph_return_t fgraph_vec_init_set(fgraph_vec_t **vec, unsigned long size, long value);
fgraph_return_t fgraph_vec_clear(fgraph_vec_t **vec);
fgraph_return_t fgraph_vec_get(fgraph_vec_t **vec, unsigned long index, long *rvalue);
fgraph_return_t fgraph_vec_set(fgraph_vec_t **vec, unsigned long index, long value);
fgraph_return_t fgraph_vec_size(fgraph_vec_t **vec, unsigned long *rvalue);

/* stacks */
fgraph_return_t fgraph_stack_init(fgraph_stack_t **stack);
fgraph_return_t fgraph_stack_clear(fgraph_stack_t **stack);
fgraph_return_t fgraph_stack_push(fgraph_stack_t **stack, long value);
fgraph_return_t fgraph_stack_pop(fgraph_stack_t **stack, long *rvalue);
fgraph_return_t fgraph_stack_size(fgraph_stack_t **stack, unsigned long *rvalue);

/* lists */
fgraph_return_t fgraph_list_init(fgraph_list_t **list);
fgraph_return_t fgraph_list_clear(fgraph_list_t **list);
fgraph_return_t fgraph_list_add(fgraph_list_t **list, long value);
fgraph_return_t fgraph_list_remove(fgraph_list_t **list, unsigned long idx, long *rvalue);
fgraph_return_t fgraph_list_get(fgraph_list_t **list, unsigned long idx, long *rvalue);
fgraph_return_t fgraph_list_set(fgraph_list_t **list, unsigned long idx, long value);
fgraph_return_t fgraph_list_size(fgraph_list_t **list, unsigned long *rvalue);

/* heaps */
fgraph_return_t fgraph_heap_init(fgraph_heap_t **heap, unsigned long max);
fgraph_return_t fgraph_heap_clear(fgraph_heap_t **heap);
fgraph_return_t fgraph_heap_insert(fgraph_heap_t **heap, unsigned long key, fgraph_edge_weight_t value);
fgraph_return_t fgraph_heap_remove(fgraph_heap_t **heap, unsigned long *rkey);
fgraph_return_t fgraph_heap_decrease(fgraph_heap_t **heap, unsigned long key, fgraph_edge_weight_t value);
fgraph_return_t fgraph_heap_size(fgraph_heap_t **heap, unsigned long *rsize);
fgraph_return_t fgraph_heap_max(fgraph_heap_t **heap, unsigned long *rmax);
fgraph_return_t fgraph_heap_swim(fgraph_heap_t **heap, unsigned long i);
fgraph_return_t fgraph_heap_sink(fgraph_heap_t **heap, unsigned long i);
fgraph_return_t fgraph_heap_more(fgraph_heap_t **heap, unsigned long i, unsigned long j, int *rbool);
fgraph_return_t fgraph_heap_swap(fgraph_heap_t **heap, unsigned long i, unsigned long j);

/* edge operations */
fgraph_return_t fgraph_edge_add(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_edge_weight_t weight);
fgraph_return_t fgraph_edge_count_all(fgraph_t **graph, unsigned long *rvalue);
fgraph_return_t fgraph_edge_count(fgraph_t **graph, unsigned long vtx, unsigned long *rvalue);

/* shortest path operations */
fgraph_return_t fgraph_sp_dag(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_vec_t **rvec, fgraph_edge_weight_t *rweight);
fgraph_return_t fgraph_sp_dijkstra(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_vec_t **rvec, fgraph_edge_weight_t *rweight);
fgraph_return_t fgraph_sp_bfs(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_vec_t **rvec);

/* sort operations */
fgraph_return_t fgraph_sort_topological(fgraph_t **graph, fgraph_vec_t **rvec);

/* coloring operations */
fgraph_return_t fgraph_color_is_kcolorable_bf(fgraph_t **graph, long ncolors, int *rbool);
fgraph_return_t fgraph_color_is_kcolorable(fgraph_t **graph, long ncolors, int *rbool);
fgraph_return_t fgraph_color_kcoloring_bf(fgraph_t **graph, long ncolors, fgraph_vec_t **rvec);
fgraph_return_t fgraph_color_kcoloring(fgraph_t **graph, long ncolors, fgraph_vec_t **rvec);
