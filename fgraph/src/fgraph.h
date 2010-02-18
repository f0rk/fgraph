/* option constants */
#define FGRAPH_ODEFAULT 0; //use the default settings, probably unweighted, undirected
#define FGRAPH_OWEIGHTED 1; //weighted graph
#define FGRAPH_OUNWEIGHTED 2; //unweighted graph
#define FGRAPH_ODIRECTED 4; //directed graph
#define FGRAPH_OUNDIRECTED 8; //undirected graph
#define FGRAPH_OSPARSE 16; //sparse graph
#define FGRAPH_ODENSE 32; //dense graph

/* success constants */
#define FGRAPH_SUCCESS 0;

/* warning constants */
#define FGRAPH_WUNWEIGHTED 1; //graph is unweighted
#define FGRAPH_WRESIZE 2; //resizing a vector

/* error constants */
#define FGRAPH_ENOMEM 4; //no memory
#define FGRAPH_ENOVTX 8; //no such vertex exists
#define FGRAPH_EBOUNDS 16; //out of bounds
#define FGRAPH_ENOEDGE 32; //no such edge exists
#define FGRAPH_EUNSUP 64; //unsupported operation
#define FGRAPH_EILLOPT 128; //illegal option configuration passed
#define FGRAPH_ENULL 256; //got a null pointer expecting not null

/* fgraph types */
typedef unsigned long long fgraph_bitmask_t;
typedef long fgraph_edge_weight_t;

struct edge {
    struct edge *next;
    struct edge *prev;
    unsigned long oid; //id of the other vertex
    fgraph_edge_weight_t weight; 
};

typedef struct edge fgraph_edge_t;

struct graph {
    fgraph_bitmask_t options;
    unsigned long size;
    fgraph_edge_t *vtx_to_edge[];
};

typedef struct graph fgraph_t;

struct vector {
    long *arr;
    unsigned long size;
};

typedef struct vector fgraph_vec_t;

/* initialization and destruction */
long fgraph_init(fgraph_t **graph, unsigned long size, fgraph_bitmask_t options);
long fgraph_clear(fgraph_t **graph);

/* vectors */
long fgraph_vec_init(fgraph_vec_t **vec, unsigned long size);
long fgraph_vec_clear(fgraph_vec_t **vec);
long fgraph_vec_get(fgraph_vec_t **vec, unsigned long index, long *rvalue);
long fgraph_vec_set(fgraph_vec_t **vec, unsigned long index, long value);

/* edge operations */
long fgraph_edge_add(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_edge_weight_t weight);

/* shortest path operations */
long fgraph_sp_dag(fgraph_t **graph, fgraph_vec_t **rvec, fgraph_edge_weight_t *rweight, unsigned long from, unsigned long to);

/* sort operations */
long fgraph_sort_topological(fgraph_t **graph, fgraph_vec_t **rvec);
