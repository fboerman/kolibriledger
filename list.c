#include "list.h"

list* list_create() {
    list* l = (list*)malloc(sizeof(list));
    if(l == NULL) {
        return NULL;
    }
    l->head = NULL;
    l->numitems = 0;
    return l;
}

int list_append_data(list* l, void* data) {
    listitem* itm = (listitem*)malloc(sizeof(listitem));
    
    if(itm == NULL) {
        return 1;
    }

    itm->data = data;

    if(l->head == NULL) {
        itm->next = itm->prev = itm;
        l->head = itm;
        l->numitems = 1;
    } else {
        itm->prev = l->head->prev;
        itm->next = l->head;
        l->head->prev->next = itm;
        l->head->prev = itm;

        l->numitems++;
    }

    return 0;
}

int list_prepend_data(list* l, void* data) {
    listitem* itm = (listitem*)malloc(sizeof(listitem));
    
    if(itm == NULL) {
        return 1;
    }

    itm->data = data;

    if(l->head == NULL) {
        itm->next = itm->prev = itm;
        l->head = itm;
        l->numitems = 1;
    } else {
        l->head->prev->next = itm;
        itm->prev = l->head->prev;
        l->head->prev = itm;
        itm->next = l->head;
        l->head = itm;
        l->numitems++;
    }   

    return 0;
    
}

int list_insert_data(list* l, listitem* itm, void* data) {
    listitem* itmnew = (listitem*)malloc(sizeof(listitem));
    
    if(itmnew == NULL) {
        return 1;
    }

    itmnew->data = data;
    itmnew->prev = itm;
    itmnew->next = itm->next;

    itm->next->prev = itmnew;
    itm->next = itmnew;

    l->numitems++;

    return 0;
    
}

listitem* list_get_item(list* l, void* data, size_t datalen) {
    listitem* itm = l->head;

    do {
        if(memcmp(itm->data, data, datalen) == 0) {
            return itm;
        }
        itm = itm->next;
    }while(itm != l->head);

    return NULL;
}

int list_remove_item(list* l, listitem* itm) {
    if(l->head == itm) {
        l->head = NULL;
        l->numitems = 0;
        l->numitems = 0;
        free(itm);
        return 0;
    } else {
        itm->prev->next = itm->next;
        itm->next->prev = itm->prev;
        free(itm);
        l->numitems--;
        return 0;
    }
}

int list_remove_data(list* l, void* data, size_t datalen) {
    listitem* itm = list_get_item(l, data, datalen);
    if(itm == NULL) {
        return 1;
    }
    return list_remove_item(l, itm);
}

int list_destroy(list* l) {
    listitem* itm = l->head;
    listitem* itmnext = l->head;

    for(int i = 0; i < l->numitems; i++) {
        itmnext = itm->next;
        free(itm);
        itm = itmnext;
    }
    free(l);
    return 0;
}