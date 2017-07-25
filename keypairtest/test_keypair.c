#include <string.h>
#include <sodium.h>

#include "keypair.h"
#include "minunit.h"

int tests_run = 0;

keypair* kp1, * kp2;

void suite_setup() {
    kp1 = NULL;
    kp2 = NULL;
}

void suite_teardown() {
    keypair_destroy(kp1);
    keypair_destroy(kp2);
}

void test_setup() {

}

void test_teardown() {

}

MU_TEST(test_sodium_init) {
    mu_check(sodium_init() != -1);
}

MU_TEST(test_keypair_generate) {
    kp1 = keypair_generate();
    mu_check(kp1 != NULL);
}

MU_TEST(test_keypair_save) {
    int returncode = keypair_save("testkey", kp1);
    mu_check(returncode == 0);
}

MU_TEST(test_keypair_load) {
    kp2 = keypair_load("testkey");
    mu_check(kp2 != NULL);
}

MU_TEST(test_keypair_identical) {
    int cmpsk = strncmp((const char*)(kp1->sk), (const char*)(kp2->sk), crypto_sign_SECRETKEYBYTES);
    int cmppk = strncmp((const char*)(kp1->pk), (const char*)(kp2->pk), crypto_sign_PUBLICKEYBYTES);
    mu_assert_int_eq(0, cmpsk);
    mu_assert_int_eq(0, cmppk);
}

MU_TEST_SUITE(keypair_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    suite_setup();
    MU_RUN_TEST(test_sodium_init);
    MU_RUN_TEST(test_keypair_generate);
    MU_RUN_TEST(test_keypair_save);
    MU_RUN_TEST(test_keypair_load);
    MU_RUN_TEST(test_keypair_identical);
    suite_teardown();
}

int main(int argc, char **argv) {
    MU_RUN_SUITE(keypair_suite);
    MU_REPORT();

    return minunit_fail;
}