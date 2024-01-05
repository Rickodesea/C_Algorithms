//Copyright (C) 2024 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "dynamic_array.h"

//#define DA_TRACE(da, msg, pos) printf("%s (%lld):\n--capacity: %lu\n--length: %lu\n--array: %p\n\n", msg, pos, da->capacity, da->length, da->array)

static inline void da_free(dynamic_array_t* da, void* mem)
{
    if(da->free) da->free(mem);
    else DYNAMIC_ARRAY_DEFAULT_FREE(mem);
}

static inline void* da_malloc(dynamic_array_t* da, size_t size)
{
    if(da->malloc) return da->malloc(size);
    else return DYNAMIC_ARRAY_DEFAULT_MALLOC(size);
}

static inline void* da_realloc(dynamic_array_t* da, void* mem, size_t size)
{
    if(da->realloc) return da->realloc(mem, size);
    else return DYNAMIC_ARRAY_DEFAULT_REALLOC(mem, size);
}

static inline size_t da_get_length_per_alloc(dynamic_array_t* da)
{
    if(da->length_per_alloc) {
        if(da->length_per_alloc >= DYNAMIC_ARRAY_MIN_LENGTH_PER_ALLOC)
            return da->length_per_alloc;
        return DYNAMIC_ARRAY_MIN_LENGTH_PER_ALLOC;
    }
    return DYNAMIC_ARRAY_DEFAULT_LENGTH_PER_ALLOC;
}

static inline void da_resize(dynamic_array_t* da)
{
    da->array = da_realloc(da, da->array, da->capacity * da->mem_size);
    if(da->user_array_var)
    {
        da->user_array_var[0] = da->array;
    }
}

static inline void da_init_capacity(dynamic_array_t* da)
{
    da->capacity = 
        da->length + 
        (da->length % da_get_length_per_alloc(da)) +
        da_get_length_per_alloc(da);
    
    da_resize(da);
}

static inline void da_update_capacity(dynamic_array_t* da)
{
    size_t dif = da->capacity - da->length;
    if(dif <= DYNAMIC_ARRAY_MIN_LENGTH_PER_ALLOC)
    {
        da->capacity += da_get_length_per_alloc(da);
        da_resize(da);
    }
    else
    if(dif >= (da_get_length_per_alloc(da) * 2))
    {
        da->capacity -= da_get_length_per_alloc(da);
        da_resize(da);
    }
    if(da->user_length_var)
    {
        da->user_length_var[0] = da->length;
    }
}

static inline size_t da_get_position(dynamic_array_t* da, long long position)
{
    if(position < 0)
    {
        return (size_t)(da->length + position);
    }
    else
    if(position >= da->length)
    {
        return (size_t)(position % da->length);
    }
    return (size_t)position;
}

static inline void* da_get_item(dynamic_array_t* da, size_t position)
{
    return da->array + (da->mem_size * position);
}

static inline void da_write_item(dynamic_array_t* da, size_t position, void* item)
{
    void* cur_item = da_get_item(da, position);
    memcpy(cur_item, item, da->mem_size);
}

bool dynamic_array_init(dynamic_array_t* da)
{
    assert(da);
    assert(da->mem_size);
    assert((da->length||da->array)?da->length&&da->array:1);

    if(da && da->mem_size && ((da->length||da->array)?da->length&&da->array:1))
    {
        da_init_capacity(da); 

        return true;
    }

    return false;
}

void dynamic_array_fit(dynamic_array_t* da)
{
    da->capacity = da->length;
    da_resize(da);
}

size_t dynamic_array_get_position(dynamic_array_t* da, long long rel_pos)
{
    return da_get_position(da, rel_pos);
}

void* dynamic_array_get_item(dynamic_array_t* da, long long rel_pos, void* ret_item)
{
    if(0 < da->length)
    {
        size_t position = da_get_position(da, rel_pos);
        void* item = da_get_item(da, position);
        if(ret_item) memcpy(ret_item, item, da->mem_size);
        return item;
    }
    return NULL;
}

void dynamic_array_replace_item(dynamic_array_t* da, long long rel_pos, void* item)
{
    if(0 < da->length)
    {
        size_t position = da_get_position(da, rel_pos);
        void* cur_item = da_get_item(da, position);
        memcpy(cur_item, item, da->mem_size);
    }
}

void* dynamic_array_delete_item(dynamic_array_t* da, long long rel_pos, void* ret_item)
{
    if(0 < da->length)
    {
        size_t position = da_get_position(da, rel_pos);
        void* item = da_get_item(da, position);
        if(ret_item) memcpy(ret_item, item, da->mem_size);
        for(size_t i = position; i < da->length - 1; i++)
        {
            void* rem = da_get_item(da, i);
            void* new = da_get_item(da, i + 1);
            memcpy(rem, new, da->mem_size);
        }
        da->length --;
        da_update_capacity(da);
        return item;
    }
    return NULL;
}

void dynamic_array_append_item(dynamic_array_t* da, void* item)
{
    da->length ++;
    da_update_capacity(da);
    da_write_item(da, da->length - 1, item);
}

void dynamic_array_insert_item(dynamic_array_t* da, long long rel_pos, void* item)
{
    if(da->length)
    {
        size_t position = da_get_position(da, rel_pos);
        da->length ++;
        da_update_capacity(da);
        for(size_t i = da->length - 1; i > position; i--)
        {
            void* new = da_get_item(da, i - 1);
            void* rem = da_get_item(da, i);
            memcpy(rem, new, da->mem_size);
        }
        da_write_item(da, position, item);
    }
    else
    {
        dynamic_array_append_item(da, item);
    }
}

