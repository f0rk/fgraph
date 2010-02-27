#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "fgraph.h"

/* initialization and destruction */
fgraph_return_t fgraph_init(fgraph_t **graph, unsigned long size, fgraph_option_t options) {
    long i = 0;
    
    if((*graph) != 0) {
        return FGRAPH_EINITED;
    }
    
    *graph = (fgraph_t*)malloc(sizeof(fgraph_t));
    if((*graph) == 0) {
        return FGRAPH_ENOMEM;
    }
    
    (*graph)->vtx_to_edge = (fgraph_edge_t**)malloc(sizeof(fgraph_edge_t)*size);
    if((*graph)->vtx_to_edge == 0) {
        return FGRAPH_ENOMEM;
    }
    
    //make sure all null
    for(i = 0; i < size; ++i) {
        (*graph)->vtx_to_edge[i] = 0;
    }
    
    (*graph)->options = options;
    (*graph)->size = size;
    (*graph)->ecnt = 0;
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_clear(fgraph_t **graph) {
    long i = 0;
    fgraph_edge_t *e = 0, *t = 0;
    
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*graph)->vtx_to_edge == 0) {
        return FGRAPH_ENULL;
    }
    
    for(i = 0; i < (*graph)->size; ++i) {
        if((*graph)->vtx_to_edge[i] != 0) {
            //walk the edge list
            for(e = (*graph)->vtx_to_edge[i]; e != 0; e = t) {
                t = e->next;
                free(e);
            }
            (*graph)->vtx_to_edge[i] = 0;
        }
    }
    
    free((*(*graph)->vtx_to_edge));
    (*graph)->vtx_to_edge = 0;
    
    (*graph)->options = 0;
    (*graph)->size = 0;
    (*graph)->ecnt = 0;
    
    free(*graph);
    *graph = 0;
    
    return FGRAPH_SUCCESS;
}

/* vectors */
fgraph_return_t fgraph_vec_init(fgraph_vec_t **vec, unsigned long size) {
    return fgraph_vec_init_set(vec, size, 0);
}

fgraph_return_t fgraph_vec_init_set(fgraph_vec_t **vec, unsigned long size, long value) {
    long i = 0;
    
    if((*vec) != 0) {
        return FGRAPH_EINITED;
    }
    
    *vec = (fgraph_vec_t*)malloc(sizeof(fgraph_vec_t));
    if(*vec == 0) { //no memory
        return FGRAPH_ENOMEM;
    }
    
    (*vec)->arr = (long*)malloc(sizeof(long)*size);
    if((*vec)->arr == 0) { //no memory
        return FGRAPH_ENOMEM;
    }
    
    for(i = 0; i < size; ++i) {
        (*vec)->arr[i] = value; //default to value
    }
    
    (*vec)->size = size;
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_vec_clear(fgraph_vec_t **vec) {
    if(*vec == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if((*vec)->arr == 0) {
        return FGRAPH_ENULL;
    }
    
    free((*vec)->arr);
    (*vec)->arr = 0;
    
    (*vec)->size = 0;
    
    free(*vec);
    *vec = 0;
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_vec_get(fgraph_vec_t **vec, unsigned long index, long *rvalue) {
    if(*vec == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if((*vec)->arr == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if(index >= (*vec)->size) {
        return FGRAPH_EBOUNDS;
    }
    
    *rvalue = (*vec)->arr[index];
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_vec_set(fgraph_vec_t **vec, unsigned long index, long value) {
    long *t = 0;
    long i = 0;
    
    if(*vec == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if((*vec)->arr == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if(index >= (*vec)->size) { //reallocate
        t = (long*)malloc(sizeof(long)*(*vec)->size*2);
        if(t == 0) { //no memory
            return FGRAPH_ENOMEM;
        }
        for(i = 0; i < (*vec)->size; ++i) {
            t[i] = (*vec)->arr[i];
        }
        for(; i < (*vec)->size*2; ++i) {
            t[i] = 0; //zero out the rest of the array
        }
        free((*vec)->arr);
        (*vec)->arr = t;
        (*vec)->size *= 2;
    }
    
    (*vec)->arr[index] = value;
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_vec_size(fgraph_vec_t **vec, unsigned long *rvalue) {
    if(*vec == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if((*vec)->arr == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    *rvalue = (*vec)->size;
    return FGRAPH_SUCCESS;
}

/* stack operations */
//TODO

/* list operations */
fgraph_return_t fgraph_list_init(fgraph_list_t **list) {
    if((*list) != 0) {
        return FGRAPH_EINITED;
    }
    
    *list = (fgraph_list_t*)malloc(sizeof(fgraph_list_t));
    if((*list) == 0) {
        return FGRAPH_ENOMEM;
    }
    
    (*list)->head = 0;
    (*list)->tail = 0;
    (*list)->size = 0;
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_list_clear(fgraph_list_t **list) {
    fgraph_node_t *n = 0, *t = 0;
    
    if((*list) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*list)->head != 0) {
        for(n = (*list)->head; n != 0; n = t) {
            t = n->next;
            free(n);
        }
        (*list)->head = 0;
        (*list)->tail = 0;
        (*list)->size = 0;
    }
    
    free(*list);
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_list_add(fgraph_list_t **list, long value) {
    fgraph_node_t *nn = 0;
    
    if((*list) == 0) {
        return FGRAPH_ENULL;
    }
    
    nn = (fgraph_node_t*)malloc(sizeof(fgraph_node_t));
    if(nn == 0) {
        return FGRAPH_ENOMEM;
    }
    
    nn->next = 0;
    nn->prev = 0;
    nn->val = value;
    
    if((*list)->head == 0) {
        (*list)->head = nn;
        (*list)->tail = nn;
        (*list)->size = 1;
        return FGRAPH_SUCCESS;
    }
    
    (*list)->tail->next = nn;
    nn->prev = (*list)->tail;
    (*list)->tail = nn;
    ++((*list)->size);
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_list_remove(fgraph_list_t **list, unsigned long idx, long *rvalue) {
    fgraph_node_t *n = 0;
    unsigned long i = 0;
    
    if((*list) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) {
        return FGRAPH_ENULL;
    }
    
    if(idx >= (*list)->size) {
        return FGRAPH_EBOUNDS;
    }
    
    i = 0;
    for(n = (*list)->head; n != 0; n = n->next) {
        if(i == idx) {
            *rvalue = n->val;
            
            if(n != (*list)->head) { //not the head
                n->prev->next = n->next;
            } else {
                (*list)->head = n->next;
                if((*list)->head != 0) {
                    (*list)->head->prev = 0;
                }
            }
            
            if(n != (*list)->tail) { //not the tail
                n->next->prev = n->prev;
            } else {
                (*list)->tail = n->prev;
                if((*list)->tail != 0) {
                    (*list)->tail->next = 0;
                }
            }
            
            n->next = 0;
            n->prev = 0;
            
            free(n);
            --((*list)->size);
            
            if((*list)->size == 0) {
                (*list)->head = 0;
                (*list)->tail = 0;
            }
            
            return FGRAPH_SUCCESS;
        }
        ++i;
    }
    
    return FGRAPH_EUNKNOWN; //should NEVER get here
}

fgraph_return_t fgraph_list_get(fgraph_list_t **list, unsigned long idx, long *rvalue) {
    fgraph_node_t *n = 0;
    unsigned long i = 0;
    
    if((*list) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) {
        return FGRAPH_ENULL;
    }
    
    if(idx >= (*list)->size) {
        return FGRAPH_EBOUNDS;
    }
    
    for(n = (*list)->head; n != 0; n = n->next) {
        if(i == idx) {
            *rvalue = n->val;
            return FGRAPH_SUCCESS;
        }
        ++i;
    }
    
    return FGRAPH_EUNKNOWN;
}

fgraph_return_t fgraph_list_set(fgraph_list_t **list, unsigned long idx, long value) {
    fgraph_node_t *n; unsigned long i;
    
    if((*list) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(idx >= (*list)->size) {
        return FGRAPH_EBOUNDS;
    }
    
    for(n = (*list)->head; n != 0; n = n->next) {
        if(i == idx) {
            n->val = value;
            return FGRAPH_SUCCESS;
        }
        ++i;
    }
    
    return FGRAPH_EUNKNOWN;
}

fgraph_return_t fgraph_list_size(fgraph_list_t **list, unsigned long *rvalue) {
    if((*list) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) {
        return FGRAPH_ENULL;
    }
    
    *rvalue = (*list)->size;
    
    return FGRAPH_SUCCESS;
}

/* edge operations */
fgraph_return_t fgraph_edge_add(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_edge_weight_t weight) {
    fgraph_edge_t *ne = 0;
    
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*graph)->vtx_to_edge == 0) {
        return FGRAPH_ENULL;
    }
    
    if(from >= (*graph)->size || to >= (*graph)->size) {
        return FGRAPH_ENOVTX;
    }
    
    if((from == to) && (((*graph)->options & FGRAPH_ONOSELFL) == FGRAPH_ONOSELFL)) {
        return FGRAPH_ESELFL;
    }
    
    ne = (fgraph_edge_t*)malloc(sizeof(fgraph_edge_t));
    if(ne == 0) {
        return FGRAPH_ENOMEM;
    }
    ne->oid = to;
    ne->weight = weight;
    ne->next = 0;
    
    if((*graph)->vtx_to_edge[from] != 0) {
        ne->next = (*graph)->vtx_to_edge[from];
    }
    (*graph)->vtx_to_edge[from] = ne;
    
    ++((*graph)->ecnt);
    
    if(!(((*graph)->options & FGRAPH_ODIRECTED) == FGRAPH_ODIRECTED)) { //not directed, add the edge in the other direction
        ne = (fgraph_edge_t*)malloc(sizeof(fgraph_edge_t));
        if(ne == 0) {
            return FGRAPH_ENOMEM;
        }
        ne->oid = from;
        ne->weight = weight;
        
        if((*graph)->vtx_to_edge[to] != 0) {
            ne->next = (*graph)->vtx_to_edge[to];
        }
        (*graph)->vtx_to_edge[to] = ne;

        ++((*graph)->ecnt);
    }
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_edge_count_all(fgraph_t **graph, unsigned long *rvalue) {
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    *rvalue = (*graph)->ecnt;
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_edge_count(fgraph_t **graph, unsigned long vtx, unsigned long *rvalue) {
    fgraph_edge_t *e;
    
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*graph)->vtx_to_edge == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if(vtx >= (*graph)->size) {
        return FGRAPH_ENOVTX;
    }
    
    *rvalue = 0;
    if((*graph)->vtx_to_edge[vtx] != 0) {
        //walk the edge list
        for(e = (*graph)->vtx_to_edge[vtx]; e != 0; e = e->next) {
            ++(*rvalue);
        }
    }
    
    return FGRAPH_SUCCESS;
}

/* shortest path operations */
//rvec will contain the nodes along the shortest path
fgraph_return_t fgraph_sp_dag(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_vec_t **rvec, fgraph_edge_weight_t *rweight) {
    fgraph_vec_t *st = 0;
    long r = 0, v = 0, *p = 0, j = 0;
    unsigned long i = 0;
    fgraph_edge_weight_t *d = 0;
    fgraph_edge_t *e = 0;
    fgraph_list_t *sp = 0;
    
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*graph)->vtx_to_edge == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rweight == 0) {
        return FGRAPH_ENULL;
    }
    
    if(from >= (*graph)->size || to >= (*graph)->size) {
        return FGRAPH_EBOUNDS;
    }
    
    if(!(((*graph)->options & FGRAPH_OWEIGHTED) == FGRAPH_OWEIGHTED)) { //use BFS, when implemented
        //TODO: Implement fgraph_sp_bfs
    }
    
    r = fgraph_vec_init_set(&st, (*graph)->size, -1);
    if(r != FGRAPH_SUCCESS) {
        return r;
    }
    
    r = fgraph_sort_topological(graph, &st);
    if(r != FGRAPH_SUCCESS) {
        fgraph_vec_clear(&st);
        return r;
    }
    
    d = (fgraph_edge_weight_t*)malloc(sizeof(fgraph_edge_weight_t)*((*graph)->size));
    if(d == 0) {
        fgraph_vec_clear(&st);
        return FGRAPH_ENOMEM;
    }
    
    for(i = 0; i < (*graph)->size; ++i) {
        d[i] = FGRAPH_EDGE_WEIGHT_MAX;
    }
    
    d[from] = 0;
    
    p = (long*)malloc(sizeof(long)*((*graph)->size));
    if(p == 0) {
        fgraph_vec_clear(&st);
        free(d);
        return FGRAPH_ENOMEM;
    }
    
    for(i = 0; i < (*graph)->size; ++i) {
        p[i] = -1;
    }
    
    //find from
    for(i = 0; i < (*graph)->size; ++i) {
        r = fgraph_vec_get(&st, i, &v);
        if(r != FGRAPH_SUCCESS) {
            fgraph_vec_clear(&st);
            free(d);
            free(p);
            return FGRAPH_EUNKNOWN; //should never happen
        }
        
        if(v == to) {
            fgraph_vec_clear(&st);
            free(d);
            free(p);
            return FGRAPH_ENOPATH;
        }
        
        if(v == from) {
            break;
        }
    }
    
    if(i == (*graph)->size) {
        fgraph_vec_clear(&st);
        free(d);
        free(p);
        return FGRAPH_EUNKNOWN; //should never happen
    }
    
    for(; i < (*graph)->size; ++i) {
        r = fgraph_vec_get(&st, i, &v);
        if(r != FGRAPH_SUCCESS) {
            fgraph_vec_clear(&st);
            free(d);
            free(p);
            return FGRAPH_EUNKNOWN; //should never happen
        }
        
        if(v == to) {
            break;
        }
        
        //process each edge out of v
        for(e = (*graph)->vtx_to_edge[v]; e != 0; e = e->next) {
            if(d[v] + e->weight < d[e->oid]) {
                d[e->oid] = d[v] + e->weight;
                p[e->oid] = v;
            }
        }
    }
    
    if(d[to] == FGRAPH_EDGE_WEIGHT_MAX) {
        fgraph_vec_clear(&st);
        free(d);
        free(p);
        return FGRAPH_ENOPATH;
    }
    
    r = fgraph_list_init(&sp);
    if(r != FGRAPH_SUCCESS) {
        fgraph_vec_clear(&st);
        free(d);
        free(p);
        return r;
    }
    
    for(v = to; v > -1;) {
        r = fgraph_list_add(&sp, v);
        if(r != FGRAPH_SUCCESS) {
            fgraph_vec_clear(&st);
            fgraph_list_clear(&sp);
            free(d);
            free(p);
            return FGRAPH_EUNKNOWN;
        }
        v = p[v];
    }
    
    if((*rvec) != 0) {
        r = fgraph_vec_clear(rvec);
        if(r != FGRAPH_SUCCESS) {
            fgraph_vec_clear(&st);
            fgraph_list_clear(&sp);
            free(d);
            free(p);
            return FGRAPH_EUNKNOWN;
        }
    }
    
    r = fgraph_vec_init(rvec, sp->size);
    if(r != FGRAPH_SUCCESS) {
        fgraph_vec_clear(&st);
        fgraph_list_clear(&sp);
        free(d);
        free(p);
        return r;
    }
    
    for(j = sp->size - 1; j > -1; --j) {
        r = fgraph_list_remove(&sp, 0, &v);
        if(r != FGRAPH_SUCCESS) {
            fgraph_vec_clear(&st);
            fgraph_list_clear(&sp);
            free(d);
            free(p);
            return FGRAPH_EUNKNOWN;
        }
        r = fgraph_vec_set(rvec, j, v);
        if(r != FGRAPH_SUCCESS) {
            fgraph_vec_clear(&st);
            fgraph_list_clear(&sp);
            free(d);
            free(p);
            return FGRAPH_EUNKNOWN;
        }
    }
    
    *rweight = d[to];
    
    fgraph_vec_clear(&st);
    fgraph_list_clear(&sp);
    free(d);
    free(p);
    
    return FGRAPH_SUCCESS;
}

/* sort operations */
fgraph_return_t fgraph_sort_topological(fgraph_t **graph, fgraph_vec_t **rvec) {
    fgraph_list_t *k = 0;
    unsigned long r = 0, j = 0, o = 0;
    fgraph_edge_t *e = 0;
    unsigned long *i = 0;
    long v = 0;
    
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*graph)->vtx_to_edge == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*rvec) == 0) {
        r = fgraph_vec_init(rvec, (*graph)->size);
        if(r != FGRAPH_SUCCESS) {
            return r;
        }
    }
    
    if((*rvec)->size != (*graph)->size) {
        r = fgraph_vec_clear(rvec);
        if(r != FGRAPH_SUCCESS) {
            return r;
        }
        r = fgraph_vec_init(rvec, (*graph)->size);
        if(r != FGRAPH_SUCCESS) {
            return r;
        }
    }
    
    for(j = 0; j < (*rvec)->size; ++j) {
        fgraph_vec_set(rvec, j, -1);
    }
    
    r = fgraph_list_init(&k);
    if(r != FGRAPH_SUCCESS) {
        return r;
    }
    
    i = (unsigned long*)malloc(sizeof(unsigned long)*((*graph)->size));
    if(i == 0) {
        fgraph_list_clear(&k);
        return FGRAPH_ENOMEM;
    }
    for(j = 0; j < (*graph)->size; ++j) {
        i[j] = 0;
    }
    
    for(j = 0; j < (*graph)->size; ++j) {
        if((*graph)->vtx_to_edge[j] != 0) {
            for(e = (*graph)->vtx_to_edge[j]; e != 0; e = e->next) {
                ++i[e->oid];
            }
        }
    }
    
    for(j = 0; j < (*graph)->size; ++j) {
        if(i[j] == 0) {
            fgraph_list_add(&k, j);
        }
    }
    
    if(k->size == 0) {
        free(i);
        fgraph_list_clear(&k);
        return FGRAPH_ENOTADAG;
    }
    
    o = 0;
    while(k->size > 0) {
        r = fgraph_list_remove(&k, 0, &v);
        if(r == FGRAPH_EBOUNDS) {
            break;    
        }
        
        if(r != FGRAPH_SUCCESS) {
            free(i);
            fgraph_list_clear(&k);
            return FGRAPH_EUNKNOWN; //should never happen
        }
        if(v >= (*graph)->size) {
            free(i);
            fgraph_list_clear(&k);
            return FGRAPH_EUNKNOWN; //should never happen
        }
        
        r = fgraph_vec_set(rvec, o, v);
        if(r != FGRAPH_SUCCESS) {
            free(i);
            fgraph_list_clear(&k);
            return FGRAPH_EUNKNOWN; //should never happen
        }
        ++o;
        
        for(e = (*graph)->vtx_to_edge[v]; e != 0; e = e->next) {
            --i[e->oid];
            if(i[e->oid] == 0) {
                r = fgraph_list_add(&k, e->oid);
                if(r != FGRAPH_SUCCESS) {
                    free(i);
                    fgraph_list_clear(&k);
                    if(r == FGRAPH_ENOMEM) {
                        return FGRAPH_ENOMEM;
                    }
                    return FGRAPH_EUNKNOWN; //should never happen
                }
            }
        }
    }
    
    if(o != (*graph)->size) { //k empty before all vtx in rvec, i.e. not a dag
        free(i);
        fgraph_list_clear(&k);
        return FGRAPH_ENOTADAG;
    }
    
    free(i);
    fgraph_list_clear(&k);
    
    return FGRAPH_SUCCESS;
}

/* coloring operations */
//TODO
