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

    dynamic_array_t darray = dynamic_array_initialize(
        (void**)&array,
        count,
        sizeof(int),
        true,
        NULL, //default standard free
        NULL, //default standard malloc
        NULL  //default standard realloc
    );
    
    while(dynamic_array_is_item_available(&darray))
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
    dynamic_array_set_position(&darray, 5);
    printf("goto absolute position %d and insert item(s)\n", 5);
    item_insert = rand();
    dynamic_array_insert_item(&darray, 0, &item_insert);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    dynamic_array_set_position(&darray, 7);
    printf("goto absolute position %d and insert item(s)\n", 7);
    item_insert = rand();
    dynamic_array_insert_item(&darray, 0, &item_insert);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    dynamic_array_set_position(&darray, 8);
    printf("goto absolute position %d and insert item(s)\n", 8);
    item_insert = rand();
    dynamic_array_insert_item(&darray, 0, &item_insert);
    item_insert = rand();
    dynamic_array_insert_item(&darray, 0, &item_insert);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    dynamic_array_set_position(&darray, 0);
    printf("goto absolute position %d and insert item(s)\n", 0);
    item_insert = rand();
    dynamic_array_insert_item(&darray, 0, &item_insert);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    dynamic_array_set_position(&darray, darray.length - 1);
    printf("goto absolute position %lu and insert item(s)\n", darray.length - 1);
    item_insert = rand();
    dynamic_array_insert_item(&darray, 0, &item_insert);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    dynamic_array_set_position(&darray, 4);
    printf("goto absolute position %d and delete item(s)\n", 4);
    dynamic_array_delete_item(&darray, 0, NULL);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    dynamic_array_set_position(&darray, 3);
    printf("goto absolute position %d and delete item(s)\n", 3);
    dynamic_array_delete_item(&darray, 0, NULL);
    dynamic_array_delete_item(&darray, 0, NULL);
    dynamic_array_delete_item(&darray, 0, NULL);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    dynamic_array_set_position(&darray, 8);
    printf("goto absolute position %d and delete an item at relative %d positions\n", 8, -3);
    dynamic_array_delete_item(&darray, -3, NULL);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }

    dynamic_array_set_position(&darray, 1);
    printf("goto absolute position %d and delete an item at relative %d positions\n", 1, +2);
    dynamic_array_delete_item(&darray, +2, NULL);

    printf("updated array:\n");
    for(int i = 0; i < darray.length; i++)
    {
        printf("%2d# item %d\n", i, array[i]);
    }
}










