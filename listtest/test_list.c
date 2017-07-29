#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minunit.h"
#include "list.h"

int testdata[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
list* l;

void test_list_check(int listdata[], size_t listlen) {
    listitem* itm = l->head;
    for(int i = 0; i < listlen; i++) {
        mu_assert_int_eq(listdata[i], *(int*)itm->data);
        itm = itm->next;
    }
}

void suite_setup() {
    l = NULL;
}

void suite_teardown() {
    list_destroy(l);
}

void test_setup() {

}

void test_teardown() {

}

MU_TEST(test_list_create) {
    l = list_create();
    mu_check(l != NULL);

}

MU_TEST(test_list_append) {
    mu_assert_int_eq(0, list_append_data(l, (void*)&testdata[0]));
    mu_assert_int_eq(0, list_append_data(l, (void*)&testdata[1]));
    mu_assert_int_eq(0, list_append_data(l, (void*)&testdata[2]));
    mu_assert_int_eq(3, l->numitems);
    int listdata1[3] = {1, 2, 3};
    test_list_check(listdata1, 3);
}

MU_TEST(test_list_prepend) {
    mu_assert_int_eq(0, list_prepend_data(l, (void*)&testdata[3]));
    mu_assert_int_eq(4, l->numitems);
    int listdata2[4] = {4, 1, 2, 3};
    test_list_check(listdata2, 4);
}

MU_TEST(test_list_remove) {
    mu_assert_int_eq(0, list_remove_data(l, (void*)&testdata[1], sizeof(int)));
    mu_assert_int_eq(3, l->numitems);
    int listdata3[3] = {4, 1, 3};
    test_list_check(listdata3, 3);
}

MU_TEST(test_list_insert) {
    mu_assert_int_eq(0, list_insert_data(l, l->head, (void*)&testdata[4]));
    mu_assert_int_eq(4, l->numitems);
    int listdata4[4] = {4, 5, 1, 3};
    test_list_check(listdata4, 4);
}

MU_TEST_SUITE(list_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    suite_setup();
    MU_RUN_TEST(test_list_create);
    MU_RUN_TEST(test_list_append);
    MU_RUN_TEST(test_list_prepend);
    MU_RUN_TEST(test_list_remove);
    MU_RUN_TEST(test_list_insert);
    suite_teardown();
}

int main(int argc, char **argv) {
    MU_RUN_SUITE(list_suite);
    MU_REPORT();

    return minunit_fail;
}