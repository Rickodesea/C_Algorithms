//Copyright (C) 2024 Alrick Grandison, Algodal™

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

///The dynamic array data type.
typedef struct dynamic_array_t dynamic_array_t; 

/// The dynamic array data type.
/// All dynamic array function requires a pointer to this data.
struct dynamic_array_t
{
    /// The current length of the array.
    size_t length;

    /// The current heap allocated array pointer value.
    void*  array;

    /// The constant size of an individual item in the array.
    /// This is the only required input.  It is required at initialization.
    /// Once it is set, it MUST NOT change!
    size_t mem_size;

    // OPTIONAL

    void(*free)(void*); ///< An alternative free
    void*(*malloc)(size_t); ///< An alternative malloc
    void*(*realloc)(void*,size_t); ///< An alternative realloc

    /// If provided, keeps the variable updated 
    /// with the latest value of @ref array.
    void** user_array_var;

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

/// @brief Sets up the internal structures based on the input.
///        This function call is required once and before all other functions.
/// @return Whether or not the dynamic array was initialized successfully.
bool dynamic_array_init(dynamic_array_t* da);

/// Checks if the dynamic array is empty.
bool dynamic_array_empty(dynamic_array_t* da);

size_t dynamic_array_length(dynamic_array_t* da);

void* dynamic_array_array(dynamic_array_t* da);

void dynamic_array_fit(dynamic_array_t* da);

size_t dynamic_array_resolve_position(dynamic_array_t* da, long long rel_pos);

void* dynamic_array_get_item(dynamic_array_t* da, long long rel_pos, void* ret_item);

void dynamic_array_append_item(dynamic_array_t* da, void* item);

void dynamic_array_insert_item(dynamic_array_t* da, long long rel_pos, void* item);

void* dynamic_array_delete_item(dynamic_array_t* da, long long rel_pos, void* ret_item);

#ifdef __cplusplus
}
#endif

#endif //DYNAMIC_ARRAY_H










