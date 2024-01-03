//Copyright (C) 2024 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "dynamic_array.h"

dynamic_array_t dynamic_array_initialize(
    void**  heap_array_variable_ptr,
    size_t array_length_per_item,
    size_t uniform_item_size,
    bool   loopback_search_method,
    void(*free_func)(void*),
    void*(*malloc_func)(size_t),
    void*(*realloc_func)(void*,size_t)
){
    dynamic_array_t darray = {}; //zeros the struct
    darray.array_ptr = heap_array_variable_ptr; //pointer to user's variable that contains the array
    darray.array = *darray.array_ptr; //actual array pointer
    darray.length = array_length_per_item;
    darray.mem_size = uniform_item_size;
    darray.loopback = loopback_search_method;
    darray.free = (free_func)?free_func:free;
    darray.malloc = (malloc_func)?malloc_func:malloc;
    darray.realloc = (realloc_func)?realloc_func:realloc;
    return darray;
}

bool dynamic_array_is_item_available(dynamic_array_t* darray)
{
    return darray->length > 0 && darray->position < darray->length;
}

static size_t get_position(dynamic_array_t* darray, int location)
{
    long long new_position = (long long)darray->position + location;

    if(new_position >= darray->length)
    {
        if(darray->loopback)
        {
            return new_position % darray->length;
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
    else
    if(new_position < 0)
    {
        if(darray->loopback)
        {
            if(darray->length)
            {
                return darray->length + new_position;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    return (size_t)new_position;
}

void* dynamic_array_get_item(dynamic_array_t* darray, int location, void* ret_item)
{
    const size_t index = get_position(darray, location);
    void* item = darray->array + (index * darray->mem_size);
    if(ret_item) memcpy(ret_item, item, darray->mem_size);
    return item;
}

void dynamic_array_delete_item(dynamic_array_t* darray, int location, void* ret_deleted)
{
    //save the position to be deleted
    size_t previous_position = darray->position;
    size_t delete_position = get_position(darray, location);
    
    //optionally save the deleted item
    if(ret_deleted)
    {
        void* deleted_item = dynamic_array_get_item(darray, location, NULL);
        memcpy(ret_deleted, deleted_item, darray->mem_size);
    }
    
    //loop through all positions and update the items
    for(size_t i = delete_position; i < darray->length - 1; i++)
    {
        darray->position = i;
        void* current_item = dynamic_array_get_item(darray, 0, NULL);
        void* next_item    = dynamic_array_get_item(darray, 0 + 1, NULL);
        memcpy(current_item, next_item, darray->mem_size);
    }
    
    //reset the current position
    darray->position = previous_position;

    //reduce array
    if(darray->length)
    {
        darray->length --;
        if(darray->length)
        {
            assert(darray->realloc);
            darray->array = darray->realloc(darray->array, darray->mem_size * darray->length);
            darray->array_ptr[0] = darray->array; //update user's variable with new address
        }
        else
        {
            assert(darray->free);
            darray->free(darray->array);
            darray->array_ptr[0] = 0; //update user's variable with new address
        }
    }
}

size_t dynamic_array_append_item(dynamic_array_t* darray, void* item)
{
    //extend the array
    darray->length ++;
    darray->array = darray->realloc(darray->array, darray->mem_size * darray->length);
    darray->array_ptr[0] = darray->array;
    //add item to position
    memcpy(darray->array + (darray->mem_size * (darray->length - 1)), item, darray->mem_size);
    return darray->length - 1;
}

size_t dynamic_array_insert_item(dynamic_array_t* darray, int location, void* item)
{
    //extend the array
    darray->length ++;
    darray->array = darray->realloc(darray->array, darray->mem_size * darray->length);
    darray->array_ptr[0] = darray->array;

    //save the current position
    size_t previous_position = darray->position;

    //get the insert position
    size_t insert_position = get_position(darray, location);

    //loop through all positions and update the items
    for(size_t i = darray->length - 1; i > insert_position; i--)
    {
        darray->position = i;
        void* current_item = dynamic_array_get_item(darray, 0, NULL);
        void* next_item    = dynamic_array_get_item(darray, -1, NULL);
        memcpy(current_item, next_item, darray->mem_size);
    }

    //add new item
    memcpy(darray->array + (darray->mem_size * insert_position), item, darray->mem_size);
    
    //reset position
    darray->position = previous_position;

    //return position item was inserted in
    return insert_position;
}

size_t dynamic_array_set_position(dynamic_array_t* darray, size_t absolute_position)
{
    darray->position = absolute_position;
    darray->position = get_position(darray, 0);
    return darray->position;
}
