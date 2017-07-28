#include <string.h>
#include <sodium.h>

#include "keypair.h"
#include "transaction.h"
#include "../minunit.h"

int tests_run = 0;

keypair *kpbuyer, *kpseller;
transaction* ta;

void suite_setup() {
    kpbuyer = NULL;
    kpseller = NULL;
    ta = NULL;
}

void suite_teardown() {
    keypair_destroy(kpbuyer);
    keypair_destroy(kpseller);
    transaction_destroy(ta);
}

void test_setup() {

}

void test_teardown() {

}

MU_TEST(test_sodium_init) {
    mu_check(sodium_init() != -1);
}

MU_TEST(test_transaction_generate) {
    kpbuyer = keypair_generate();
    mu_check(kpbuyer != NULL);
    kpseller = keypair_generate();
    mu_check(kpseller != NULL);
    ta = transaction_create_empty();
    mu_check(ta != NULL);
    
    //fill transaction with some data
    memcpy(ta->buyerpk, kpbuyer->pk, crypto_sign_PUBLICKEYBYTES);
    memcpy(ta->sellerpk, kpseller->pk, crypto_sign_PUBLICKEYBYTES);
    ta->timestamp = (unsigned long int)time(NULL);
    memcpy(ta->bought, "grain", 5);
    memcpy(ta->sold, "cash", 4);
    ta->ammount_bought = 5;
    ta->ammount_sold = 10;

    //test if verification fails
    mu_check(transaction_verify(ta, 0) != 0);
    mu_check(transaction_verify(ta, 1) != 0);
}

MU_TEST(test_transaction_sign_and_verify) {
    mu_assert_int_eq(0, transaction_sign(ta, kpbuyer, 0));
    mu_assert_int_eq(0, transaction_sign(ta, kpseller, 1));
    mu_assert_int_eq(0, transaction_verify(ta, 0));
    mu_assert_int_eq(0, transaction_verify(ta, 1));
}

MU_TEST(test_transaction_corrupt) {
    ta->ammount_sold++;
    mu_assert_int_eq(1, transaction_verify(ta, 0));
    mu_assert_int_eq(1, transaction_verify(ta, 1));

    ta->ammount_sold = 10;
    mu_assert_int_eq(transaction_verify_full(ta), 0);
}

MU_TEST(test_transaction_sig_corrupt) {
    ta->buyer_sig[3] = '0';
    ta->seller_sig[7] = '0';
    mu_assert_int_eq(1, transaction_verify(ta, 0));
    mu_assert_int_eq(1, transaction_verify(ta, 1));
}

MU_TEST(test_transaction_save_and_load_string) {
    char* str_core = transaction_getstring_core(ta);
    char* str_full = transaction_getstring_full(ta);
    
    mu_check(str_core != NULL);
    mu_check(str_full != NULL);
    
    transaction* ta1 = transaction_loadstring_core(str_core);
    transaction* ta2 = transaction_loadstring_full(str_full);

    mu_assert_int_eq(0, transaction_checkequal(ta1, ta2));
    mu_assert_int_eq(0, transaction_checkequal(ta1, ta));
    mu_assert_int_eq(0, transaction_verify_full(ta2));

    free(str_core);
    free(str_full);
}

MU_TEST_SUITE(transaction_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    suite_setup();
    MU_RUN_TEST(test_sodium_init);
    MU_RUN_TEST(test_transaction_generate);
    MU_RUN_TEST(test_transaction_sign_and_verify);
    MU_RUN_TEST(test_transaction_save_and_load_string);
    MU_RUN_TEST(test_transaction_corrupt);
    MU_RUN_TEST(test_transaction_sig_corrupt);
    suite_teardown();
}

int main(int argc, char **argv) {
    MU_RUN_SUITE(transaction_suite);
    MU_REPORT();

    return minunit_fail;
}