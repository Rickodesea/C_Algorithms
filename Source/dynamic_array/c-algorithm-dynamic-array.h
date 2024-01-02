//Copyright (C) 2024 Alrick Grandison, Algodal™

#ifndef C_ALGORITHM_DYNAMIC_ARRAY_H
#define C_ALGORITHM_DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
/// @brief Core Structure
struct dynamic_array_t
{
    size_t index; ///<internal iterator
    short  dir; ///<internal search direction
    void*  array; ///< internal array (must be heap allocated to use add and delete functions...for set or get functions, stack arrays can be used as well)
    void** array_ptr; ///< Holds the address of the variable that contains the heap array
    size_t length; ///<length of the array interms of items
    size_t mem_size; ///< the size of an item.  All items must be equal in size.
    bool   loopback; ///< when travelling the array, (true) loop to the other end when reach the end or the beginning of the array or (false) clamp to the last or first item.
};

typedef struct dynamic_array_t dynamic_array_t;

dynamic_array_t dynamic_array_initialize(
    void**  heap_array_variable,
    size_t array_length_per_item,
    size_t uniform_item_size,
    bool   loopback_search_method
);

bool dynamic_array_current_available(dynamic_array_t* darray);

void* dynamic_array_get_current(dynamic_array_t* darray, void* ret_item);
void* dynamic_array_get_next(dynamic_array_t* darray, void* ret_item);

void dynamic_array_delete_current(dynamic_array_t* darray);



#ifdef __cplusplus
}
#endif

#endif //C_ALGORITHM_DYNAMIC_ARRAY_H










