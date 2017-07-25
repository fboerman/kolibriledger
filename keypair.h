#ifndef _KEYPAIR_H
#define _KEYPAIR_H

#include <stdio.h>
#include <string.h>
#include <sodium.h>

// Struct to hold a Ed25519 public/private keypair for signing and verifying
typedef struct _keypair {
    unsigned char pk[crypto_sign_PUBLICKEYBYTES];
    unsigned char sk[crypto_sign_SECRETKEYBYTES];
} keypair;

/**
 * @brief Generate a new keypair struct
 *
 * Allocates a new struct and generates a new edEd25519 public/private keypair.
 * Returns NULL if malloc fails
 *
 * @return pointer to the newly allocated struct
 */
keypair* keypair_generate();

/**
* @brief Save keypair to file
* 
* Saves a given keypair to file with given name. Extensions are automatically appended.
* 
* @param name name of the file to be saved
* @param kp pointer to keypair struct to be saved
* @return integer, 0 if saved succesfully, 1 if encountered error
*/
int keypair_save(const char* name, keypair* kp);

/**
* @brief Load keypair from file
* 
* Loads a keypair from file with given name. Extensions are automatically appended.
* Returns NULL if malloc fails
*
* @param name name of the file to be loaded
* @return pointer to allocated keypair struct
*/
keypair* keypair_load(const char* name);

/**
* @brief destroy the keypair
*
* Frees the memory used for the keypair
*
* @param kp pointer to keypair struct to be destroyed
*/
void keypair_destroy(keypair* kp);

#endif