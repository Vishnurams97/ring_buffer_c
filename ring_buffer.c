
#include "ring_buffer.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

ring_buffer_t * init_cbuffer(int length){
    ring_buffer_t * p_buffer_t;
    p_buffer_t->head = 0;
    p_buffer_t->tail = 0;
    p_buffer_t->total_slots = length - 1;
    p_buffer_t->is_full = false;
    p_buffer_t->packets_ptr = (storage_structure *)calloc(length, sizeof(storage_structure));
    return p_buffer_t;
}

bool is_buffer_full(ring_buffer_t * p_buffer_t){
    return p_buffer_t->is_full;
}

bool is_buffer_empty(ring_buffer_t * p_buffer_t){
    return  ((p_buffer_t->is_full==false) && (p_buffer_t->head==p_buffer_t->tail));
}

ret_code_t uninit_cbuffer(ring_buffer_t * p_buffer_t){
    free(p_buffer_t);
    return BFR_SUCCESS;
}

ret_code_t write_item(ring_buffer_t * p_buffer_t, storage_structure * p_data_t){
    memcpy(&p_buffer_t->packets_ptr[p_buffer_t->head], p_data_t, sizeof(storage_structure));
    p_buffer_t->head = (p_buffer_t->head + 1) % p_buffer_t->total_slots;
    if(!is_buffer_full(p_buffer_t)){
        if(p_buffer_t->head == p_buffer_t->tail){
            p_buffer_t->is_full = true;
        }
    }
    if(is_buffer_full(p_buffer_t)){
        p_buffer_t->tail = p_buffer_t->head;
    }
    return BFR_SUCCESS;
}

storage_structure * read_head_item(ring_buffer_t * p_buffer_t){
    return  &(p_buffer_t->packets_ptr[p_buffer_t->head - 1]);
}

storage_structure * read_tail_item(ring_buffer_t * p_buffer_t){
    return  &(p_buffer_t->packets_ptr[p_buffer_t->tail]);
}

ret_code_t remove_head_item(ring_buffer_t * p_buffer_t){
    if(is_buffer_empty(p_buffer_t)){
        return  BFR_SUCCESS;
    }
    else{
        if(is_buffer_full(p_buffer_t)){
            p_buffer_t->is_full = false;
            p_buffer_t->head-=1;
        }   
        else{
            p_buffer_t->head-=1;
        }
    }
}

ret_code_t remove_tail_item(ring_buffer_t * p_buffer_t){
    if(is_buffer_empty(p_buffer_t)){
        return  BFR_SUCCESS;
    }
    else{
        if(is_buffer_full(p_buffer_t)){
            p_buffer_t->is_full = false;
            p_buffer_t->tail = (p_buffer_t->tail + 1) % p_buffer_t->total_slots;
        }   
        else{
            p_buffer_t->tail = (p_buffer_t->tail + 1) % p_buffer_t->total_slots;
        }
    }
}

ret_code_t reset_cbuffer(ring_buffer_t * p_buffer_t){
    p_buffer_t->head = 0;
    p_buffer_t->tail = 0;
    p_buffer_t->total_slots = 0;
    p_buffer_t->is_full = false;
    free(p_buffer_t->packets_ptr); 
}

int get_queue_capacity(ring_buffer_t * p_buffer_t){
    return p_buffer_t->total_slots;
}
