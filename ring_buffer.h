
#ifndef __RING_BUFFER__
#define __RING_BUFFER__

#include "app_error.h"

#define BFR_SUCCESS 0
#define BFR_ERROR 1

typedef struct{
    float latitude;
    float longitude;
}geo_coordinates;

typedef  struct{
    int queue_pos_no;
    int sensor_value1;
    int sensor_value2;
    int sensor_value3;
    uint8_t sensor_value4;
    geo_coordinates *lat_lng;
}storage_structure;

typedef struct{
    bool is_full;
    uint16_t head;
    uint16_t tail;
    storage_structure * packets_ptr;
    uint16_t total_slots;
}ring_buffer_t;

ring_buffer_t * init_cbuffer(int length);

ret_code_t add_item(ring_buffer_t *, storage_structure *);

bool is_buffer_full(ring_buffer_t *);

bool is_buffer_empty(ring_buffer_t *);

ret_code_t uninit_cbuffer(ring_buffer_t *);

storage_structure * read_head_item(ring_buffer_t *);

storage_structure * read_tail_item(ring_buffer_t *);

ret_code_t remove_head_item(ring_buffer_t *);

ret_code_t remove_tail_item(ring_buffer_t *);

ret_code_t reset_cbuffer(ring_buffer_t *);

int get_queue_capacity(ring_buffer_t *);

#endif
