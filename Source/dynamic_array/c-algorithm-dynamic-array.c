//Copyright (C) 2024 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "c-algorithm-dynamic-array.h"

dynamic_array_t dynamic_array_initialize(
    void**  heap_array_variable,
    size_t array_length_per_item,
    size_t uniform_item_size,
    bool   loopback_search_method
){
    dynamic_array_t darray = {};
    darray.array_ptr = heap_array_variable; //pointer to user's variable that contains the array
    darray.array = *darray.array_ptr; //actual array pointer
    darray.length = array_length_per_item;
    darray.mem_size = uniform_item_size;
    darray.loopback = loopback_search_method;
    return darray;
}

bool dynamic_array_current_available(dynamic_array_t* darray)
{
    return darray->length > 0 && darray->index < darray->length;
}

void* dynamic_array_get_current(dynamic_array_t* darray, void* ret_item)
{
    void* item = darray->array + (darray->index * darray->mem_size);
    if(ret_item) memcpy(ret_item, item, darray->mem_size);
    return item;
}

static size_t next_index(dynamic_array_t* darray)
{
    size_t next = darray->index + 1;

    if(next >= darray->length)
    {
        if(darray->loopback)
        {
            return next % darray->length;
        }
        else
        {
            if(darray->length)
            {
                return darray->length - 1;
            }
            return 0;
        }
    }
    return next;
}

void* dynamic_array_get_next(dynamic_array_t* darray, void* ret_item)
{
    void* item = darray->array + (next_index(darray) * darray->mem_size);
    if(ret_item) memcpy(ret_item, item, darray->mem_size);
    return item;
}

void dynamic_array_delete_current(dynamic_array_t* darray)
{
    //save the current position
    size_t index_before_delete = darray->index;
    
    //loop through all positions and update the items
    for(size_t i = darray->index; i < darray->length - 1; i++)
    {
        darray->index = i;
        void* current_item = dynamic_array_get_current(darray, NULL);
        void* next_item    = dynamic_array_get_next(darray, NULL);
        memcpy(current_item, next_item, darray->mem_size);
    }
    //reset the current position
    darray->index = index_before_delete;
    //reduce array
    if(darray->length)
    {
        darray->length --;
        if(darray->length)
        {
            darray->array = realloc(darray->array, darray->mem_size * darray->length);
            darray->array_ptr = darray->array; //update user's variable with new address
        }
        else
        {
            free(darray->array);
            darray->array_ptr = 0; //update user's variable with new address
        }
    }
}





