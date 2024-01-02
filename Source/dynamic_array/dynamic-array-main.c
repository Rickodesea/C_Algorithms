//Copyright (C) 2024 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c-algorithm-dynamic-array.h"

int main()
{
    int count = 10;
    int* array = malloc(sizeof(int) * count);
    for(int i = 0; i < count; i++) {
        array[i] = rand();
        printf("adding...%d\n", array[i]);
    }

    dynamic_array_t darray = dynamic_array_initialize(
        (void**)&array,
        count,
        sizeof(int),
        true
    );
    
    while(dynamic_array_current_available(&darray))
    {
        int* item_a; //one way of getting the same item
        int  item_b; //another way to get the same item
        item_a = dynamic_array_get_current(&darray, &item_b);
        printf("deleting...%d\n", *item_a);
        dynamic_array_delete_current(&darray);
    }
}










