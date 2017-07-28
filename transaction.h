/**
 * @file transactions.h
 * @author Frank Boerman
 * @brief Headerfile for the transaction library
 *
 *
 * Describes the functions of the transaction library as well as the transaction data struct
 */

#ifndef _TRANSACTION_H
#define _TRANSACTION_H

#include <stdio.h>
#include <string.h>
#include <sodium.h> 
#include "keypair.h"

#define TRANSACTION_SIGN_LEN 112

typedef struct _transaction {
    unsigned char buyerpk[crypto_sign_PUBLICKEYBYTES];
    unsigned char sellerpk[crypto_sign_PUBLICKEYBYTES];
    long int timestamp;
    char bought[16];
    char sold[16];
    int ammount_bought;
    int ammount_sold;
    unsigned char buyer_sig[crypto_sign_BYTES + TRANSACTION_SIGN_LEN];
    unsigned char seller_sig[crypto_sign_BYTES + TRANSACTION_SIGN_LEN];
}transaction;

/*
* @brief Creates an empty transaction
*
* This function creates an empty transaction initialized with all zeros
* returns NULL if malloc fails and a pointer to the new struct otherwise
*
* @return pointer to new struct or NULL on failure
*/
transaction* transaction_create_empty();

/**
* @brief destroy the transaction
*
* Frees the memory used for the transaction
*
* @param ta pointer to transaction struct to be destroyed
*/
void transaction_destroy(transaction* ta);

/**
 * @brief signs the given transaction
 *
 * This function signs a given prefilled transaction and fills in the signature on the correct field
 * @param ta the transaction to be signed
 * @param kp the keypair to use to sign
 * @param type 0 for buyer 1 for seller
 * @return 0 if all succesfull 1 otherwise
*/
int transaction_sign(transaction* ta, keypair* kp, int type);

/**
 * @brief verifies the signature on a transaction
 *
 * This function verifies the signature on a transaction of a given transaction.
 * @param ta the transaction to be verified
 * @param type 0 for buyer 1 for seller
 * @return 0 if verification is succesfull 1 otherwise
 **/
 int transaction_verify(transaction* ta, int type);

/**
 * @brief shortcut to full verification of transaction
 *
 * this function calls the transaction_verify twice, once for buyer and once for seller, to fully verify the transaction
 * @param ta the transaction to be verified
 * @return 0 if verification is succesfull 1 otherwise
 */
 int transaction_verify_full(transaction* ta);

 /**
  * @brief equality check for two given transactions
  *
  * this function checks if two given transactions are equal. It only checks the parts which are signed, so not the signatures itself
  * @param ta1 transaction 1 to be checked with transaction 2
  * @param ta2 transaction 2 to be checked with transaction 1
  * @return 0 on success and 1 otherwise
  */
int transaction_checkequal(transaction* ta1, transaction* ta2);

/**
  * @brief give string representation of the transaction core
  *
  * this function converts a given transaction to a string representation. It only handles the core, without the signatures
  * it gives 7 lines of 16 hexes 
  * @param ta the transaction to represent
  * @return string of the transaction
  */
 char* transaction_getstring_core(transaction* ta);

 /**
  * @brief give string representation of the transaction
  *
  * this function converts a given transaction to a string representation. It handles the full struct including signatures
  * it gives 29 lines of 16 hexes 
  * @param ta the transaction to represent
  * @return string of the transaction
  */
 char* transaction_getstring_full(transaction* ta);

 /**
  * @brief load transaction core from string
  *
  * this function constructs a transaction struct from a string produced by the getstring function. It only handles the core, without the signatures.
  * it returns the build transaction struct pointer or NULL on failure
  * @param string containing the transaction
  * @return pointer to the build struct or NULL on failure
  */
transaction* transaction_loadstring_core(char* str);

 /**
 * @brief load transaction from string
 *
 * this function constructs a transaction struct from a string produced by the getstring function. It handles the full struct including signatures
 * it returns the build transaction struct pointer or NULL on failure
 * @param string containing the transaction
 * @return pointer to the build struct or NULL on failure
 */
transaction* transaction_loadstring_full(char* str);

#endif