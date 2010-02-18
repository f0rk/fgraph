#include <stdlib.h>
#include <stdio.h>
#include "fgraph.h"

/* initialization and destruction */
long fgraph_init(fgraph_t **graph, unsigned long size, fgraph_bitmask_t options) {
    return 0;
}

long fgraph_clear(fgraph_t **graph) {
    return 0;
}

/* vectors */
long fgraph_vec_init(fgraph_vec_t **vec, unsigned long size) {
    long i;
    
    *vec = (fgraph_vec_t*)malloc(sizeof(fgraph_vec_t));
    if(*vec == 0) { //no memory
        return FGRAPH_ENOMEM;
    }
    
    (*vec)->arr = (long*)malloc(sizeof(long)*size);
    if((*vec)->arr == 0) { //no memory
        return FGRAPH_ENOMEM;
    }
    
    for(i = 0; i < size; ++i) {
        (*vec)->arr[i] = 0; //default to 0
    }
    
    (*vec)->size = size;
    return FGRAPH_SUCCESS;
}

long fgraph_vec_clear(fgraph_vec_t **vec) {
    if(*vec == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if((*vec)->arr == 0) {
        return FGRAPH_ENULL;
    }
    
    free((*vec)->arr);
    (*vec)->size = 0;
    free(*vec);
    return FGRAPH_SUCCESS;
}

long fgraph_vec_get(fgraph_vec_t **vec, unsigned long index, long *rvalue) {
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

long fgraph_vec_set(fgraph_vec_t **vec, unsigned long index, long value) {
    long *t; long i;
    
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

/* edge operations */
long fgraph_edge_add(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_edge_weight_t weight) {
    return 0;
}

/* shortest path operations */
long fgraph_sp_dag(fgraph_t **graph, fgraph_vec_t **rvec, fgraph_edge_weight_t *rweight, unsigned long from, unsigned long to) {
    return 0;
}

/* sort operations */
long fgraph_sort_topological(fgraph_t **graph, fgraph_vec_t **rvec) {
    return 0;
}
