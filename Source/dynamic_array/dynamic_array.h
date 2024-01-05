//Copyright (C) 2024 Alrick Grandison, Algodal™

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

///The dynamic array type.
typedef struct dynamic_array_t dynamic_array_t; 

/// The dynamic array structure.
struct dynamic_array_t
{
    /// The current length of the array.
    /// The value is updated regularly.
    size_t length;

    /// The current heap allocated array pointer value.
    /// The pointer is updated regularly.
    void*  array;

    /// The constant size of an individual item in the array.
    /// This is the only required input and is required at initialization.
    size_t mem_size;

    // OPTIONAL

    void(*free)(void*); ///< An alternative free
    void*(*malloc)(size_t); ///< An alternative malloc
    void*(*realloc)(void*,size_t); ///< An alternative realloc

    /// If provided, keeps the variable updated 
    /// with the latest value of @ref array.
    void**  user_array_var;

    /// If provided, keeps the variable updated 
    /// with the latest value of @ref length.
    size_t* user_length_var;

    /// How much item slots to append per allocation.  
    /// The default is 8.
    unsigned int length_per_alloc;

    // INTERNAL

    /// The actual amount of item slots created.
    size_t capacity;
};

#define DYNAMIC_ARRAY_DEFAULT_LENGTH_PER_ALLOC 8
#define DYNAMIC_ARRAY_DEFAULT_FREE free
#define DYNAMIC_ARRAY_DEFAULT_MALLOC malloc
#define DYNAMIC_ARRAY_DEFAULT_REALLOC realloc

#define DYNAMIC_ARRAY_MIN_LENGTH_PER_ALLOC 2

/// @brief Sets up the dynamic array for use.
///        Dynamic array is not valid until this function is called.
///        This function is required to be called again if @ref dynamic_array_fit 
///        was called.
/// @return Success of initialization
bool dynamic_array_init(dynamic_array_t* da);

/// Resize the dynamic array to fit the length.
/// Best used when returning the array back to the application.
/// If you call this function, before calling any other function
/// you should call @ref dynamic_array_init again
void dynamic_array_fit(dynamic_array_t* da);

/// Gets the absolute position used to access the item.
/// @param rel_pos A relative positive or negative function.
///                If positive then it is treated as the absolute position
///                unless it is larger than the length then it is mapped back
///                within the array length.
///                If the value is negative then it is treated as a reverse position.
size_t dynamic_array_get_position(dynamic_array_t* da, long long rel_pos);

/// Gets the item at the specified position.
/// @param ret_item (Optional) Receives the selected item
/// @return returns the selected item
void* dynamic_array_get_item(dynamic_array_t* da, long long rel_pos, void* ret_item);

/// Adds an item to the end of the dynamic array
/// @param item item to add
void dynamic_array_append_item(dynamic_array_t* da, void* item);

/// Inserts an item at the specified position of the dynamic array.
/// @param item item to insert
void dynamic_array_insert_item(dynamic_array_t* da, long long rel_pos, void* item);

/// Deletes an item at the specified position of the dynamic array
/// @param item item to delete
void* dynamic_array_delete_item(dynamic_array_t* da, long long rel_pos, void* ret_item);

/// Replaces the item at the specified position of the dynamic array
/// @param item item to replace
void dynamic_array_replace_item(dynamic_array_t* da, long long rel_pos, void* item);

#ifdef __cplusplus
}
#endif

#endif //DYNAMIC_ARRAY_H










