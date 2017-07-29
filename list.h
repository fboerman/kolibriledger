#ifndef _LIST_H
#define _LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _listitem listitem;

typedef struct _listitem {
    listitem* prev;
    listitem* next;
    void* data;
}listitem;

typedef struct _list {
    listitem* head;
    int numitems;
}list;

list* list_create();

int list_append_data(list* l, void* data);

int list_prepend_data(list* l, void* data);

int list_insert_data(list* l, listitem* itm, void* data);

listitem* list_get_item(list* l, void* data, size_t datalen);

int list_remove_item(list* l, listitem* itm);

int list_remove_data(list* l, void* data, size_t datalen);

int list_destroy(list* l);

#endif