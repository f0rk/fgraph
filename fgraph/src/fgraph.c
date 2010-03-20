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

/* basic graph information */
fgraph_return_t fgraph_size(fgraph_t **graph, unsigned long *rvalue) {
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) {
        return FGRAPH_ENULL;
    }
    
    *rvalue = (*graph)->size;
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_options(fgraph_t **graph, fgraph_option_t *rvalue) {
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) {
        return FGRAPH_ENULL;
    }
    
    *rvalue = (*graph)->options;
    
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
        free(*vec);
        *vec = 0;
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

fgraph_return_t fgraph_vec_length(fgraph_vec_t **vec, unsigned long *rvalue) {
    if(*vec == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if((*vec)->arr == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) { //null pointer
        return FGRAPH_ENULL;
    }
    
    *rvalue = (*vec)->size - 1;
    return FGRAPH_SUCCESS;
}

/* stacks */
fgraph_return_t fgraph_stack_init(fgraph_stack_t **stack) {
    if((*stack) != 0) {
        return FGRAPH_EINITED;
    }
    
    *stack = (fgraph_stack_t*)malloc(sizeof(fgraph_stack_t));
    if((*stack) == 0) {
        return FGRAPH_ENOMEM;
    }
    
    (*stack)->top = 0;
    (*stack)->size = 0;
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_stack_clear(fgraph_stack_t **stack) {
    fgraph_node_t *n = 0, *t = 0;
    
    if((*stack) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*stack)->top != 0) {
        for(n = (*stack)->top; n != 0; n = t) { //walk down the stack
            t = n->prev;
            free(n);
        }
        (*stack)->top = 0;
        (*stack)->size = 0;
    }
    
    free(*stack);
    *stack = 0;
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_stack_push(fgraph_stack_t **stack, long value) {
    fgraph_node_t *nn = 0;
    
    if((*stack) == 0) {
        return FGRAPH_ENULL;
    }
    
    nn = (fgraph_node_t*)malloc(sizeof(fgraph_node_t));
    if(nn == 0) {
        return FGRAPH_ENOMEM;
    }
    
    nn->prev = 0;
    nn->next = 0;
    nn->val = value;
    
    (*stack)->size++;
    
    if((*stack)->top == 0) {
        (*stack)->top = nn;
        (*stack)->size = 1;
        return FGRAPH_SUCCESS;
    }
    
    nn->prev = (*stack)->top;
    (*stack)->top->next = nn;
    (*stack)->top = nn;
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_stack_pop(fgraph_stack_t **stack, long *rvalue) {
    if((*stack) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*stack)->top == 0) {
        return FGRAPH_EEMPTY;
    }
    
    *rvalue = (*stack)->top->val;
    
    if((*stack)->top->prev != 0) {
        (*stack)->top = (*stack)->top->prev;
        (*stack)->top->next->prev = 0;
        free((*stack)->top->next);
        (*stack)->top->next = 0;
        (*stack)->size--;
        return FGRAPH_SUCCESS;
    }
    
    free((*stack)->top);
    (*stack)->top = 0;
    (*stack)->size = 0;
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_stack_size(fgraph_stack_t **stack, unsigned long *rvalue) {
    if((*stack) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) {
        return FGRAPH_ENULL;
    }
    
    *rvalue = (*stack)->size;
    
    return FGRAPH_SUCCESS;
}

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
    *list = 0;
    
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
    fgraph_node_t *n = 0;
    unsigned long i = 0;
    
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

/* heap operations */
fgraph_return_t fgraph_heap_init(fgraph_heap_t **heap, unsigned long size) {
    unsigned long i = 0;
    
    if((*heap) != 0) {
        return FGRAPH_EINITED;
    }
    
    *heap = (fgraph_heap_t*)malloc(sizeof(fgraph_heap_t));
    if((*heap) == 0) {
        return FGRAPH_ENOMEM;
    }
    
    (*heap)->pq = 0;
    (*heap)->qp = 0;
    (*heap)->pri = 0;
    
    (*heap)->pq = (long*)malloc(sizeof(long)*size);
    if((*heap)->pq == 0) {
        free(*heap);
        return FGRAPH_ENOMEM;
    }
    
    (*heap)->qp = (long*)malloc(sizeof(long)*size);
    if((*heap)->qp == 0) {
        free((*heap)->pq);
        free(*heap);
        return FGRAPH_ENOMEM;
    }
    
    (*heap)->pri = (fgraph_edge_weight_t*)malloc(sizeof(fgraph_edge_weight_t)*size);
    if((*heap)->pri == 0) {
        free((*heap)->pq);
        free((*heap)->qp);
        free(*heap);
        return FGRAPH_ENOMEM;
    }
    
    (*heap)->size = size;
    (*heap)->n = 0;
    
    for(i = 0; i < (*heap)->size; ++i) {
        (*heap)->qp[i] = -1;
        (*heap)->pri[i] = FGRAPH_EDGE_WEIGHT_MIN;
    }
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_heap_clear(fgraph_heap_t **heap) {
    if((*heap) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*heap)->pq == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*heap)->qp == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*heap)->pri == 0) {
        return FGRAPH_ENULL;
    }
    
    free((*heap)->pq);
    (*heap)->pq = 0;
    
    free((*heap)->qp);
    (*heap)->qp = 0;
    
    free((*heap)->pri);
    (*heap)->pri = 0;
    
    (*heap)->size = 0;
    (*heap)->n = 0;
    
    free(*heap);
    *heap = 0;
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_heap_insert(fgraph_heap_t **heap, unsigned long key, fgraph_edge_weight_t value) {
    long r = 0;
    
    if((*heap) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*heap)->size <= key) {
        return FGRAPH_EBOUNDS;
    }
    
    if((*heap)->pri[key] != FGRAPH_EDGE_WEIGHT_MIN) {
        return FGRAPH_EEXISTS;
    }
    
    ++((*heap)->n);
    (*heap)->qp[key] = (*heap)->n;
    (*heap)->pq[(*heap)->n] = key;
    (*heap)->pri[key] = value;
    r = fgraph_heap_swim(heap, (*heap)->n);
    if(r != FGRAPH_SUCCESS) {
        return r; //should never happen
    }
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_heap_remove(fgraph_heap_t **heap, unsigned long *rkey) {
    long r = 0;
    
    if((*heap) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rkey == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*heap)->n == 0) {
        *rkey = 0;
        return FGRAPH_EEMPTY;
    }
    
    *rkey = (*heap)->pq[1];
    (*heap)->qp[*rkey] = -1;
    r = fgraph_heap_swap(heap, 1, ((*heap)->n)--);
    if(r != FGRAPH_SUCCESS) {
        return r; //should never happen
    }
    r = fgraph_heap_sink(heap, 1);
    if(r != FGRAPH_SUCCESS) {
        return r; //should never happen
    }
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_heap_decrease(fgraph_heap_t **heap, unsigned long key, fgraph_edge_weight_t value) {
    long r = 0;
    
    if((*heap) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*heap)->size <= key) {
        return FGRAPH_EBOUNDS;
    }
    
    if((*heap)->pri[key] < value) {
        return FGRAPH_EORDER;
    }
    
    (*heap)->pri[key] = value;
    r = fgraph_heap_swim(heap, (*heap)->qp[key]);
    if(r != FGRAPH_SUCCESS) {
        return r; //should never happen
    }
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_heap_size(fgraph_heap_t **heap, unsigned long *rsize) {
    if((*heap) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rsize == 0) {
        return FGRAPH_ENULL;
    }
    
    *rsize = (*heap)->n;
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_heap_max(fgraph_heap_t **heap, unsigned long *rmax) {
    if((*heap) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rmax == 0) {
        return FGRAPH_ENULL;
    }
    
    *rmax = (*heap)->size - 1;
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_heap_swim(fgraph_heap_t **heap, unsigned long i) {
    long r = 0; int b = 0;
    
    if((*heap) == 0) {
        return FGRAPH_ENULL;
    }
    
    while(i > 1) {
        r = fgraph_heap_more(heap, i/2, i, &b);
        if(r != FGRAPH_SUCCESS) {
            return r; //should never happen
        }
        
        if(b == 0) {
            break;
        }
        
        r = fgraph_heap_swap(heap, i, i/2);
        if(r != FGRAPH_SUCCESS) {
            return r; //should never happen
        }
        
        i /= 2;
    }
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_heap_sink(fgraph_heap_t **heap, unsigned long i) {
    unsigned long j = 0; int b = 0; long r = 0;
    
    if((*heap) == 0) {
        return FGRAPH_ENULL;
    }
    
    while(2*i <= (*heap)->n) {
        j = 2*i;
        
        r = fgraph_heap_more(heap, j, j+1, &b);
        if(r != FGRAPH_SUCCESS) {
            return r; //should never happen
        }
        
        if(j < (*heap)->n && b != 0) {
            j++;
        }
        
        r = fgraph_heap_more(heap, i, j, &b);
        if(r != FGRAPH_SUCCESS) {
            return r; //should never happen
        }
        
        if(b == 0) {
            break;
        }
        
        r = fgraph_heap_swap(heap, i, j);
        if(r != FGRAPH_SUCCESS) {
            return r; //should never happen
        }
        
        i = j;
    }
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_heap_more(fgraph_heap_t **heap, unsigned long i, unsigned long j, int *rbool) {
    if((*heap) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rbool == 0) {
        return FGRAPH_ENULL;
    }
    
    *rbool = ((*heap)->pri[(*heap)->pq[i]]) > ((*heap)->pri[(*heap)->pq[j]]);
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_heap_swap(fgraph_heap_t **heap, unsigned long i, unsigned long j) {
    if((*heap) == 0) {
        return FGRAPH_ENULL;
    }
    
    long swap = (*heap)->pq[i];
    (*heap)->pq[i] = (*heap)->pq[j];
    (*heap)->pq[j] = swap;
    (*heap)->qp[(*heap)->pq[i]] = i;
    (*heap)->qp[(*heap)->pq[j]] = j;
    
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
        ne = 0;
        ne = (fgraph_edge_t*)malloc(sizeof(fgraph_edge_t));
        if(ne == 0) {
            return FGRAPH_ENOMEM;
        }
        ne->oid = from;
        ne->weight = weight;
        ne->next = 0;
        
        if((*graph)->vtx_to_edge[to] != 0) {
            ne->next = (*graph)->vtx_to_edge[to];
        }
        (*graph)->vtx_to_edge[to] = ne;

        ++((*graph)->ecnt);
    }
    
    return FGRAPH_SUCCESS;
}

fgraph_return_t fgraph_edge_remove(fgraph_t **graph, unsigned long from, unsigned long to) {
    fgraph_edge_t *e = 0, *t = 0;
    
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*graph)->vtx_to_edge == 0) {
        return FGRAPH_ENULL;
    }
    
    if(from >= (*graph)->size || to >= (*graph)->size) {
        return FGRAPH_ENOVTX;
    }
    
    if(!(((*graph)->options & FGRAPH_ODIRECTED) == FGRAPH_ODIRECTED)) { //not directed, remove the edge in the other direction
        for(e = (*graph)->vtx_to_edge[to]; e != 0; e = e->next) {
            if(e->oid == from) { //gotcha
                if(t == 0) {
                    t = e;
                    (*graph)->vtx_to_edge[to] = e->next;
                    e->next = 0;
                    free(e);
                    break;
                }
                
                t->next = e->next;
                e->next = 0;
                free(e);
                break;
            }
            t = e;
        }
    }
    
    for(e = (*graph)->vtx_to_edge[from]; e != 0; e = e->next) {
        if(e->oid == to) { //gotcha
            if(t == 0) {
                t = e;
                (*graph)->vtx_to_edge[from] = e->next;
                e->next = 0;
                free(e);
                return FGRAPH_SUCCESS;
            }
            
            t->next = e->next;
            e->next = 0;
            free(e);
            return FGRAPH_SUCCESS;
        }
        t = e;
    }
    
    return FGRAPH_ENOEDGE;
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
    fgraph_edge_t *e = 0;
    
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

fgraph_return_t fgraph_edge_get_weight(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_edge_weight_t *rvalue) {
    fgraph_edge_t *e = 0;
    
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*graph)->vtx_to_edge == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rvalue == 0) {
        return FGRAPH_ENULL;
    }
    
    if(from >= (*graph)->size || to >= (*graph)->size) {
        return FGRAPH_ENOEDGE;
    }
    
    //see if the edge exists
    for(e = (*graph)->vtx_to_edge[from]; e != 0; e = e->next) {
        if(e->oid == to) { //found it
            *rvalue = e->weight;
            return FGRAPH_SUCCESS;
        }
    }
    
    return FGRAPH_ENOEDGE;
}

fgraph_return_t fgraph_edge_set_weight(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_edge_weight_t weight) {
    fgraph_edge_t *e = 0;
    
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*graph)->vtx_to_edge == 0) {
        return FGRAPH_ENULL;
    }
    
    if(from >= (*graph)->size || to >= (*graph)->size) {
        return FGRAPH_ENOEDGE;
    }
    
    if(!(((*graph)->options & FGRAPH_ODIRECTED) == FGRAPH_ODIRECTED)) { //undirected, set the other edge
        for(e = (*graph)->vtx_to_edge[to]; e != 0; e = e->next) {
            if(e->oid == from) { //found it
                e->weight = weight;
                break;
            }
        }
    }
    
    //see if the edge exists
    for(e = (*graph)->vtx_to_edge[from]; e != 0; e = e->next) {
        if(e->oid == to) { //found it
            e->weight = weight;
            return FGRAPH_SUCCESS;
        }
    }
    
    return FGRAPH_ENOEDGE;
}

fgraph_return_t fgraph_edge_exists(fgraph_t **graph, unsigned long from, unsigned long to, int *rbool) {
    fgraph_edge_t *e = 0;
    
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if((*graph)->vtx_to_edge == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rbool == 0) {
        return FGRAPH_ENULL;
    }
    
    if(from >= (*graph)->size || to >= (*graph)->size) {
        return FGRAPH_ENOEDGE;
    }
    
    *rbool = 0;
    
    //see if the edge exists
    for(e = (*graph)->vtx_to_edge[from]; e != 0; e = e->next) {
        if(e->oid == to) { //found it
            *rbool = 1;
            return FGRAPH_SUCCESS;
        }
    }
    
    return FGRAPH_SUCCESS;
}

/* shortest path operations */
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
    
    if(rweight == 0) {
        return FGRAPH_ENULL;
    }
    
    if(!(((*graph)->options & FGRAPH_ODIRECTED) == FGRAPH_ODIRECTED)) {
        return FGRAPH_ENOTADAG; //actually it could be a dag, but you shouldn't be this stupid
    }
    
    if(from >= (*graph)->size || to >= (*graph)->size) {
        return FGRAPH_EBOUNDS;
    }
    
    if(from == to) {
        return FGRAPH_ENOPATH; //actually there could be a path, but you shouldn't be this stupid
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
            if(((*graph)->options & FGRAPH_OWEIGHTED) == FGRAPH_OWEIGHTED) {
                if(d[v] + e->weight < d[e->oid]) {
                    d[e->oid] = d[v] + e->weight;
                    p[e->oid] = v;
                }
            } else {
                if(d[v] + 1 < d[e->oid]) {
                    d[e->oid] = d[v] + 1;
                    p[e->oid] = v;
                }
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

fgraph_return_t fgraph_sp_dijkstra(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_vec_t **rvec, fgraph_edge_weight_t *rweight) {
    unsigned long *p = 0, i = 0, v = 0, *parentv = 0;
    fgraph_heap_t *pq = 0;
    fgraph_edge_t *e = 0;
    long r = 0, si = 0, sv = 0;
    fgraph_edge_weight_t *parentw = 0;
    fgraph_list_t *path = 0;
    
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(rweight == 0) {
        return FGRAPH_ENULL;
    }
    
    if(from >= (*graph)->size || to >= (*graph)->size) {
        return FGRAPH_EBOUNDS;
    }
    
    if(!(((*graph)->options & FGRAPH_OWEIGHTED) == FGRAPH_OWEIGHTED)) {
        *rweight = 0; //no concept
        return fgraph_sp_bfs(graph, from, to, rvec);
    }
    
    p = (unsigned long*)malloc(sizeof(unsigned long)*((*graph)->size));
    if(p == 0) {
        return FGRAPH_ENOMEM;
    }
    
    parentv = (unsigned long*)malloc(sizeof(unsigned long)*((*graph)->size));
    if(parentv == 0) {
        free(p);
        return FGRAPH_ENOMEM;
    }
    
    parentw = (fgraph_edge_weight_t*)malloc(sizeof(fgraph_edge_weight_t)*((*graph)->size));
    if(parentw == 0) {
        free(p);
        free(parentv);
        return FGRAPH_ENOMEM;
    }
    
    r = fgraph_heap_init(&pq, (*graph)->size);
    if(r != FGRAPH_SUCCESS) {
        free(p);
        free(parentv);
        free(parentw);
        return r;
    }
    
    for(i = 0; i < (*graph)->size; ++i) {
        p[i] = ULONG_MAX;
    }
    
    p[from] = 0;
    r = fgraph_heap_insert(&pq, from, 0);
    if(r != FGRAPH_SUCCESS) {
        free(p);
        free(parentv);
        free(parentw);
        fgraph_heap_clear(&pq);
        return r; //should never happen
    }
    
    while(pq->n != 0) {
        r = fgraph_heap_remove(&pq, &v);
        if(r != FGRAPH_SUCCESS) {
            free(p);
            free(parentv);
            free(parentw);
            fgraph_heap_clear(&pq);
            return r; //should never happen
        }
        
        if(v == to) {
            //set up us the path
            r = fgraph_list_init(&path);
            if(r != FGRAPH_SUCCESS) {
                free(p);
                free(parentv);
                free(parentw);
                fgraph_heap_clear(&pq);
                return r;
            }
            
            *rweight = 0;
            sv = v;
            while(sv >= 0) {
                r = fgraph_list_add(&path, sv);
                if(r != FGRAPH_SUCCESS) {
                    free(p);
                    free(parentv);
                    free(parentw);
                    fgraph_heap_clear(&pq);
                    fgraph_list_clear(&path);
                    return r;
                }
                
                if(sv == from) {
                    break;
                }
                
                *rweight += parentw[sv];
                sv = parentv[sv];
            }
            
            if((*rvec) != 0) {
                r = fgraph_vec_clear(rvec);
                if(r != FGRAPH_SUCCESS) {
                    free(p);
                    free(parentv);
                    free(parentw);
                    fgraph_heap_clear(&pq);
                    fgraph_list_clear(&path);
                    return r; //should never happen
                }
            }
            
            r = fgraph_vec_init(rvec, path->size);
            if(r != FGRAPH_SUCCESS) {
                free(p);
                free(parentv);
                free(parentw);
                fgraph_heap_clear(&pq);
                fgraph_list_clear(&path);
                return r;
            }
            
            for(si = path->size - 1; si > -1; --si) {
                r = fgraph_list_remove(&path, 0, &sv);
                if(r != FGRAPH_SUCCESS) {
                    free(p);
                    free(parentv);
                    free(parentw);
                    fgraph_heap_clear(&pq);
                    fgraph_list_clear(&path);
                    return r; //should never happen
                }
                
                r = fgraph_vec_set(rvec, si, sv);
                if(r != FGRAPH_SUCCESS) {
                    free(p);
                    free(parentv);
                    free(parentw);
                    fgraph_heap_clear(&pq);
                    fgraph_list_clear(&path);
                    return r; //should never happen
                }
            }
            
            free(p);
            free(parentv);
            free(parentw);
            fgraph_heap_clear(&pq);
            fgraph_list_clear(&path);
            
            return FGRAPH_SUCCESS;
        }
        
        for(e = (*graph)->vtx_to_edge[v]; e != 0; e = e->next) {
            if(e->weight < 0) {
                free(p);
                free(parentv);
                free(parentw);
                fgraph_heap_clear(&pq);
                return FGRAPH_ESIGN;
            }
            
            if(p[e->oid] == ULONG_MAX) {
                r = fgraph_heap_insert(&pq, e->oid, FGRAPH_EDGE_WEIGHT_MAX);
                if(r != FGRAPH_SUCCESS) {
                    free(p);
                    free(parentv);
                    free(parentw);
                    fgraph_heap_clear(&pq);
                    return r; //should never happen
                }
            }
            
            if(p[v] + e->weight < p[e->oid]) {
                p[e->oid] = p[v] + e->weight;
                r = fgraph_heap_decrease(&pq, e->oid, p[e->oid]);
                if(r != FGRAPH_SUCCESS) {
                    free(p);
                    free(parentv);
                    free(parentw);
                    fgraph_heap_clear(&pq);
                    return r; //should never happen
                }
                parentv[e->oid] = v;
                parentw[e->oid] = e->weight;
            }
        }
    }
    
    //pq empty before reaching to, i.e., no path
    free(p);
    free(parentv);
    free(parentw);
    fgraph_heap_clear(&pq);
    
    return FGRAPH_ENOPATH;
}

fgraph_return_t fgraph_sp_bfs(fgraph_t **graph, unsigned long from, unsigned long to, fgraph_vec_t **rvec) {
    unsigned long *p = 0;
    short *visited = 0;
    fgraph_list_t *queue = 0, *path = 0;
    long i = 0, r = 0, v = 0;
    fgraph_edge_t *e = 0;
    
    if((*graph) == 0) {
        return FGRAPH_ENULL;
    }
    
    if(from >= (*graph)->size || to >= (*graph)->size) {
        return FGRAPH_EBOUNDS;
    }
    
    p = (unsigned long*)malloc(sizeof(unsigned long)*((*graph)->size));
    if(p == 0) {
        return FGRAPH_ENOMEM;
    }
    
    for(i = 0; i < (*graph)->size; ++i) {
        p[i] = -1;
    }
    
    visited = (short*)malloc(sizeof(short)*((*graph)->size));
    if(visited == 0) {
        free(p);
        return FGRAPH_ENOMEM;
    }
    
    for(i = 0; i < (*graph)->size; ++i) {
        visited[i] = 0;
    }
    
    r = fgraph_list_init(&queue);
    if(r != FGRAPH_SUCCESS) {
        free(p);
        free(visited);
        return r;
    }
    
    r = fgraph_list_add(&queue, from);
    if(r != FGRAPH_SUCCESS) {
        free(p);
        free(visited);
        fgraph_list_clear(&queue);
        return r;
    }
    
    while(queue->size != 0) {
        r = fgraph_list_remove(&queue, 0, &v);
        if(r != FGRAPH_SUCCESS) {
            free(p);
            free(visited);
            fgraph_list_clear(&queue);
            return r; //should never happen
        }
        
        if(v == to) {
            //set up us the path
            r = fgraph_list_init(&path);
            if(r != FGRAPH_SUCCESS) {
                free(p);
                free(visited);
                fgraph_list_clear(&queue);
                return r; 
            }
            
            while(v > -1) {
                r = fgraph_list_add(&path, v);
                if(r != FGRAPH_SUCCESS) {
                    free(p);
                    free(visited);
                    fgraph_list_clear(&queue);
                    fgraph_list_clear(&path);
                    return r;
                }
                
                if(v == from) {
                    break;
                }
                
                v = p[v];
            }
            
            if((*rvec) != 0) {
                r = fgraph_vec_clear(rvec);
                if(r != FGRAPH_SUCCESS) {
                    free(p);
                    free(visited);
                    fgraph_list_clear(&queue);
                    fgraph_list_clear(&path);
                    return r; //should never happen
                }
            }
            
            r = fgraph_vec_init(rvec, path->size);
            if(r != FGRAPH_SUCCESS) {
                free(p);
                free(visited);
                fgraph_list_clear(&queue);
                fgraph_list_clear(&path);
                return r;
            }
            
            for(i = path->size - 1; i > -1; --i) {
                r = fgraph_list_remove(&path, 0, &v);
                if(r != FGRAPH_SUCCESS) {
                    free(p);
                    free(visited);
                    fgraph_list_clear(&queue);
                    fgraph_list_clear(&path);
                    return r; //should never happen
                }
                
                r = fgraph_vec_set(rvec, i, v);
                if(r != FGRAPH_SUCCESS) {
                    free(p);
                    free(visited);
                    fgraph_list_clear(&queue);
                    fgraph_list_clear(&path);
                    return r; //should never happen
                }
            }
            
            free(p);
            free(visited);
            fgraph_list_clear(&queue);
            fgraph_list_clear(&path);
            
            return FGRAPH_SUCCESS;
        }
        
        for(e = (*graph)->vtx_to_edge[v]; e != 0; e = e->next) {
            if(visited[e->oid] == 0) {
                p[e->oid] = v;
                r = fgraph_list_add(&queue, e->oid);
                if(r != FGRAPH_SUCCESS) {
                    free(p);
                    free(visited);
                    fgraph_list_clear(&queue);
                    return r;
                }
                visited[e->oid] = 1;
            }
        }
    }
    
    free(p);
    free(visited);
    fgraph_list_clear(&queue);
    
    return FGRAPH_ENOPATH;
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
fgraph_return_t fgraph_color_is_kcolorable_bf(fgraph_t **graph, long ncolors, int *rbool) {
    return FGRAPH_EUNSUP; //TODO: Implement
}

fgraph_return_t fgraph_color_is_kcolorable(fgraph_t **graph, long ncolors, int *rbool) {
    return FGRAPH_EUNSUP; //TODO: Implement
}

fgraph_return_t fgraph_color_kcoloring_bf(fgraph_t **graph, long ncolors, fgraph_vec_t **rvec) {
    return FGRAPH_EUNSUP; //TODO: Implement
}

fgraph_return_t fgraph_color_kcoloring(fgraph_t **graph, long ncolors, fgraph_vec_t **rvec) {
    return FGRAPH_EUNSUP; //TODO: Implement
}
