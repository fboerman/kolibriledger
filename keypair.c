#include "keypair.h"

keypair* keypair_generate() {
    keypair* kp = (keypair*)malloc(sizeof(keypair));
    if(kp == NULL) {
        return NULL;
    }
    crypto_sign_keypair(kp->pk, kp->sk);
    return kp;
}

int keypair_save(const char* name, keypair* kp) {
    char* fnamepriv = (char*)malloc((strlen(name) + 4) * sizeof(char));
    char* fnamepub = (char*)malloc((strlen(name) + 3) * sizeof(char));
    
    sprintf(fnamepriv, "%s.priv", name);
    sprintf(fnamepub, "%s.pub", name);

    FILE* f = fopen(fnamepriv, "w");
    
    if(f == NULL) {
        return 1;
    }

    for(int i = 0; i < crypto_sign_SECRETKEYBYTES; i++)
    {
        fprintf(f, "%02x ", kp->sk[i]);
    }

    if(fclose(f) != 0) {
        return 1;
    }

    f = fopen(fnamepub, "w");

    if(f == NULL) {
        return 1;
    }

    for(int i = 0; i < crypto_sign_PUBLICKEYBYTES; i++) {
        fprintf(f, "%02x ", kp->pk[i]);
    }

    if(fclose(f) != 0) {
        return 1;
    }

    return 0;
}

keypair* keypair_load(const char* name) {
    char* fnamepriv = (char*)malloc((strlen(name) + 4) * sizeof(char));
    char* fnamepub = (char*)malloc((strlen(name) + 3) * sizeof(char));
    keypair* kp = (keypair*)malloc(sizeof(keypair));
    
    if(kp == NULL) {
        return NULL;
    }
    memset(&(kp->sk), 0, crypto_sign_SECRETKEYBYTES);
    memset(&(kp->pk), 0, crypto_sign_PUBLICKEYBYTES);

    sprintf(fnamepriv, "%s.priv", name);
    sprintf(fnamepub, "%s.pub", name);

    FILE* fpub = fopen(fnamepub, "r");

    if(fpub == NULL) {
        return NULL;
    }

    for(int i = 0; i < crypto_sign_PUBLICKEYBYTES; i++) {
        fscanf(fpub, "%02x", (unsigned int*)&(kp->pk[i]));
    }

    fclose(fpub);

    FILE* fpriv = fopen(fnamepriv, "r");
    
    if(fpriv == NULL) {
        return NULL;
    }

    for(int i = 0; i < crypto_sign_SECRETKEYBYTES; i++)
    {
        fscanf(fpriv, "%02x", (unsigned int*)&(kp->sk[i]));
    }

    fclose(fpriv);

    return kp;
}


void keypair_destroy(keypair* kp) {
    free(kp);
}
