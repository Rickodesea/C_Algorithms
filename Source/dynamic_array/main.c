//Copyright (C) 2024 Alrick Grandison, Algodal™

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"

int main()
{
    int count = 10;
    int* array = malloc(sizeof(int) * count);
    for(int i = 0; i < count; i++) {
        array[i] = rand();
        printf("adding...%d\n", array[i]);
    }

    //input
    dynamic_array_t darray = {};
    darray.mem_size = sizeof(int);
    darray.array  = array; //set the current array but will be updated by darray
    darray.length = count; //set the current length but will be updated by darray
    darray.user_array_var = (void**)&array; //ask darray to update the variable `array` with the latest pointer of the array
    
    dynamic_array_init(&darray); //this sets up the internal structures based on the input

    while(darray.length > 0)
    {
        int* item_a; //one way of getting the same item
        int  item_b; //another way to get the same item
        item_a = dynamic_array_get_item(&darray, 0, &item_b);
        printf("deleting...%d", *item_a);
        int item_c = 0;
        dynamic_array_delete_item(&darray, 0, &item_c);
        printf("...deleted...%d\n", item_c);
    }

    while(darray.length < 10)
    {
        int item = rand();
        dynamic_array_append_item(&darray, &item);
        printf("adding...%d\n", item);
    }

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    int item_insert;
    printf("goto absolute position %d and insert item(s)\n", 5);
    item_insert = rand();
    dynamic_array_insert_item(&darray, 5, &item_insert);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    printf("goto absolute position %d and insert item(s)\n", 7);
    item_insert = rand();
    dynamic_array_insert_item(&darray, 7, &item_insert);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    printf("goto absolute position %d and insert item(s)\n", 8);
    item_insert = rand();
    dynamic_array_insert_item(&darray, 8, &item_insert);
    item_insert = rand();
    dynamic_array_insert_item(&darray, 8, &item_insert);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    printf("goto absolute position %d and insert item(s)\n", 0);
    item_insert = rand();
    dynamic_array_insert_item(&darray, 0, &item_insert);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    item_insert = rand();
    printf("goto absolute position %lu and insert %d\n", dynamic_array_get_position(&darray, -1), item_insert);
    dynamic_array_insert_item(&darray, -1, &item_insert);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    printf("goto absolute position %d and delete item(s)\n", 4);
    dynamic_array_delete_item(&darray, 4, NULL);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    printf("goto absolute position %d and delete item(s)\n", 3);
    dynamic_array_delete_item(&darray, 3, NULL);
    dynamic_array_delete_item(&darray, 3, NULL);
    dynamic_array_delete_item(&darray, 3, NULL);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    printf("goto absolute position %lu and delete an item(s)\n", dynamic_array_get_position(&darray, -1));
    dynamic_array_delete_item(&darray, -1, NULL);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    item_insert = rand();
    printf("goto absolute position %u and replace with %d\n", 5, item_insert);
    dynamic_array_replace_item(&darray, 5, &item_insert);

    item_insert = rand();
    printf("goto absolute position %u and replace with %d\n", 2, item_insert);
    dynamic_array_replace_item(&darray, 2, &item_insert);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }
}










