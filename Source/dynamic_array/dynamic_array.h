//Copyright (C) 2024 Alrick Grandison, Algodal™

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
/// @brief Core Structure
struct dynamic_array_t
{
    size_t position; ///< READONLY internal iterator.  All array item access are relative to this value.
    void*  array; ///< READONLY internal array (must be heap allocated to use add and delete functions...for set or get functions, stack arrays can be used as well)
    void** array_ptr; ///< READONLY Holds the address of the variable that contains the heap array
    size_t length; ///< READONLY length of the array interms of items
    size_t mem_size; ///<  READONLY the size of an item.  All items must be equal in size.
    bool   loopback; ///<  READONLY when travelling the array, (true) loop to the other end when reach the end or the beginning of the array or (false) clamp to the last or first item.
    void(*free)(void*); ///< OPTIONAL function to add your own free
    void*(*malloc)(size_t); ///< OPTIONAL function to add your own malloc
    void*(*realloc)(void*,size_t); ///< OPTIONAL function to add your own realloc
};

typedef struct dynamic_array_t dynamic_array_t;

/// @brief Sets up the dynamic array structure.
/// @param heap_array_variable_ptr ///< pointer to the variable that contains the array
/// @param array_length_per_item ///< the number of items currently in the array
/// @param uniform_item_size ///< the size of an item
/// @param loopback_search_method ///< whether or not loop method is to be use when requested index goes beyond the array length
/// @param free_func ///< optional function to add your own free
/// @param malloc_func ///< optional function to add your own malloc
/// @param realloc_func ///< optional function to add your own malloc
/// @return 
dynamic_array_t dynamic_array_initialize(
    void**  heap_array_variable_ptr,
    size_t array_length_per_item,
    size_t uniform_item_size,
    bool   loopback_search_method,
    void(*free_func)(void*),
    void*(*malloc_func)(size_t),
    void*(*realloc_func)(void*,size_t)
);

/// @brief Does the array has any items
bool dynamic_array_is_item_available(dynamic_array_t* darray);

/// @brief Gets an item from the array relative to the current position of the dynamic array structure
/// @param darray 
/// @param location OPTIONAL Relative to the current position of the dynamic array structure.
///                 Can be positive (next), negative (previous) or 0 (current).  0 is the default.
/// @param ret_item The item returned.
/// @return The item returned.
void* dynamic_array_get_item(dynamic_array_t* darray, int location, void* ret_item);

/// @brief Removes an item from the array relative to the current position of the dynamic array structure.
///        The array is shrunk and if it is empty, the array is freed.
/// @param darray 
/// @param location OPTIONAL Relative to the current position of the dynamic array structure.
///                 Can be positive (next), negative (previous) or 0 (current). 0 is the default.
/// @param ret_deleted Optionally the returned deleted item.  The item is not processed in any way by this function.
///         It's the user's responsibility to clean it up.
void dynamic_array_delete_item(dynamic_array_t* darray, int location, void* ret_deleted);


size_t dynamic_array_append_item(dynamic_array_t* darray, void* item);

size_t dynamic_array_insert_item(dynamic_array_t* darray, int location, void* item);

size_t dynamic_array_set_position(dynamic_array_t* darray, size_t absolute_position);


#ifdef __cplusplus
}
#endif

#endif //DYNAMIC_ARRAY_H










