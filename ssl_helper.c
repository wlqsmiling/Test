/*
 * @Author: liqunwu
 * @Date: 2023-11-09 15:26:56
 * @Description: 
 * Copyright (c) 2023 by zhejianglab, All Rights Reserved.
 */
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

// Function to save the private key to a character array
    int save_private_key_to_array(EC_KEY *key_pair, unsigned char **priv_key_data, size_t *priv_key_len)
    {
        BIO *bio = BIO_new(BIO_s_mem());
        if (bio == NULL)
        {
            printf("Failed to create BIO for private key.\n");
            return 0;
        }

        if (PEM_write_bio_ECPrivateKey(bio, key_pair, NULL, NULL, 0, NULL, NULL) != 1)
        {
            printf("Failed to write private key to BIO.\n");
            BIO_free_all(bio);
            return 0;
        }

        // Determine the length of the private key data
        *priv_key_len = BIO_pending(bio);

        // Allocate memory for the private key data
        *priv_key_data = (unsigned char *)malloc(*priv_key_len);
        if (*priv_key_data == NULL)
        {
            printf("Failed to allocate memory for private key data.\n");
            BIO_free_all(bio);
            return 0;
        }

        // Read the private key data into the character array
        if (BIO_read(bio, *priv_key_data, *priv_key_len) != (int)*priv_key_len)
        {
            printf("Failed to read private key data.\n");
            free(*priv_key_data);
            BIO_free_all(bio);
            return 0;
        }

        BIO_free_all(bio);

        return 1;
    }

    // Function to save the public key to a character array
    int save_public_key_to_array(EC_KEY *key_pair, unsigned char **pub_key_data, size_t *pub_key_len)
    {
        BIO *bio = BIO_new(BIO_s_mem());
        if (bio == NULL)
        {
            printf("Failed to create BIO for public key.\n");
            return 0;
        }

        if (PEM_write_bio_EC_PUBKEY(bio, key_pair) != 1)
        {
            printf("Failed to write public key to BIO.\n");
            BIO_free_all(bio);
            return 0;
        }

        // Determine the length of the public key data
        *pub_key_len = BIO_pending(bio);

        // Allocate memory for the public key data
        *pub_key_data = (unsigned char *)malloc(*pub_key_len);
        if (*pub_key_data == NULL)
        {
            printf("Failed to allocate memory for public key data.\n");
            BIO_free_all(bio);
            return 0;
        }

        // Read the public key data into the character array
        if (BIO_read(bio, *pub_key_data, *pub_key_len) != (int)*pub_key_len)
        {
            printf("Failed to read public key data.\n");
            free(*pub_key_data);
            BIO_free_all(bio);
            return 0;
        }

        BIO_free_all(bio);

        return 1;
    }

EC_KEY* char_to_ec_key(const char* ec_key_str, int is_private_key) {
    if (!ec_key_str) {
        fprintf(stderr, "Invalid EC_KEY string.\n");
        return NULL;
    }

    BIO* bio_mem = BIO_new_mem_buf(ec_key_str, -1);
    if (!bio_mem) {
        fprintf(stderr, "Failed to create BIO.\n");
        return NULL;
    }

    EC_KEY* ec_key;
    if (is_private_key) {
        ec_key = PEM_read_bio_ECPrivateKey(bio_mem, NULL, NULL, NULL);
    } else {
        ec_key = PEM_read_bio_EC_PUBKEY(bio_mem, NULL, NULL, NULL);
    }

    if (!ec_key) {
        fprintf(stderr, "Failed to read EC_KEY from BIO.\n");
        BIO_free(bio_mem);
        return NULL;
    }

    BIO_free(bio_mem);

    return ec_key;
}

int sign_data(const unsigned char* data, size_t data_len, EC_KEY* ec_key, unsigned char* signature, size_t* signature_len) {
    
    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
    if (!md_ctx) {
        fprintf(stderr, "Failed to create EVP_MD_CTX object.\n");
        EC_KEY_free(ec_key);
    }

    EVP_PKEY* evp_key = EVP_PKEY_new();
    if (!evp_key) {
        fprintf(stderr, "Failed to create EVP_PKEY object.\n");
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    if (EVP_PKEY_set1_EC_KEY(evp_key, ec_key) != 1) {
        fprintf(stderr, "Failed to set EC key in EVP_PKEY object.\n");
        EVP_PKEY_free(evp_key);
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    if (EVP_DigestSignInit(md_ctx, NULL, EVP_sha256(), NULL, evp_key) != 1) {
        fprintf(stderr, "Failed to initialize EVP_MD_CTX for signing.\n");
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    if (EVP_DigestSign(md_ctx, NULL, signature_len, data, data_len) != 1) {
        fprintf(stderr, "Failed to determine signature length.\n");
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    // signature = (unsigned char*)malloc(*signature_len);
    if (!signature) {
        fprintf(stderr, "Failed to allocate memory for the signature.\n");
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    if (EVP_DigestSign(md_ctx,signature, signature_len, data, data_len) != 1) {
        fprintf(stderr, "Failed to sign the data.\n");
        free(signature);
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    EVP_MD_CTX_free(md_ctx);

    printf("Signature: ");
    // print_hex(signature, signature_len);

    EC_KEY_free(ec_key);
}

int verify_data(const unsigned char* data, size_t data_len, EC_KEY* ec_key, unsigned char* signature, size_t signature_len) {
// Verify the signature
    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
    if (!md_ctx) {
        fprintf(stderr, "Failed to create EVP_MD_CTX object.\n");
        EC_KEY_free(ec_key);
        return 1;
    }

// Create an EVP_PKEY object and assign the EC key
    EVP_PKEY* evp_key = EVP_PKEY_new();
    if (!evp_key) {
        fprintf(stderr, "Failed to create EVP_PKEY object.\n");
        EC_KEY_free(ec_key);
        return 1;
    }

    if (EVP_PKEY_assign_EC_KEY(evp_key, ec_key) != 1) {
        fprintf(stderr, "Failed to assign EC key to EVP_PKEY object.\n");
        EVP_PKEY_free(evp_key);
        return 1;
    }

    if (EVP_DigestVerifyInit(md_ctx, NULL, EVP_sha256(), NULL, evp_key) != 1) {
        fprintf(stderr, "Failed to initialize EVP_MD_CTX for verification.\n");
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
        return 1;
    }

    if (EVP_DigestVerify(md_ctx, signature, signature_len, data, data_len) != 1) {
        fprintf(stderr, "Verification failed: Invalid signature.\n");
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
        return 1;
    }

    EVP_MD_CTX_free(md_ctx);

    printf("Verification succeeded: Valid signature.\n");

    // Clean up
    EC_KEY_free(ec_key);

    return 0;
}


TEST(svssoft, signature2)
{
     // Generate the EC key pair
    EC_KEY* ec_key = EC_KEY_new_by_curve_name(NID_secp256k1);
    if (!ec_key) {
        fprintf(stderr, "Failed to generate EC key pair.\n");
    }

    if (EC_KEY_generate_key(ec_key) != 1) {
        fprintf(stderr, "Failed to generate EC key pair.\n");
        EC_KEY_free(ec_key);
    }

    // Extract the private key
    const BIGNUM* private_key_bn = EC_KEY_get0_private_key(ec_key);
    if (!private_key_bn) {
        fprintf(stderr, "Failed to extract private key from EC key.\n");
        EC_KEY_free(ec_key);
    }

    // Convert the private key to a hexadecimal string
    unsigned char private_key_bytes[32];  // Assuming 256-bit private key (32 bytes)
    int private_key_len = BN_bn2bin(private_key_bn, private_key_bytes);
    if (private_key_len != 32) {
        fprintf(stderr, "Unexpected private key length.\n");
        EC_KEY_free(ec_key);
    }

    printf("Private key: ");
    // print_hex(private_key_bytes, private_key_len);

    // Example data to sign and verify
    const unsigned char data[] = "Hello, World!";
    size_t data_len = strlen((const char*)data);

    // Sign the data using the EC key
    unsigned char* signature;
    size_t signature_len;
    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
    if (!md_ctx) {
        fprintf(stderr, "Failed to create EVP_MD_CTX object.\n");
        EC_KEY_free(ec_key);
    }

    EVP_PKEY* evp_key = EVP_PKEY_new();
    if (!evp_key) {
        fprintf(stderr, "Failed to create EVP_PKEY object.\n");
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    if (EVP_PKEY_set1_EC_KEY(evp_key, ec_key) != 1) {
        fprintf(stderr, "Failed to set EC key in EVP_PKEY object.\n");
        EVP_PKEY_free(evp_key);
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    if (EVP_DigestSignInit(md_ctx, NULL, EVP_sha256(), NULL, evp_key) != 1) {
        fprintf(stderr, "Failed to initialize EVP_MD_CTX for signing.\n");
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    if (EVP_DigestSign(md_ctx, NULL, &signature_len, data, data_len) != 1) {
        fprintf(stderr, "Failed to determine signature length.\n");
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    signature = (unsigned char*)malloc(signature_len);
    if (!signature) {
        fprintf(stderr, "Failed to allocate memory for the signature.\n");
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    if (EVP_DigestSign(md_ctx, signature, &signature_len, data, data_len) != 1) {
        fprintf(stderr, "Failed to sign the data.\n");
        free(signature);
        EVP_MD_CTX_free(md_ctx);
        EC_KEY_free(ec_key);
    }

    EVP_MD_CTX_free(md_ctx);

    printf("Signature: ");
    // print_hex(signature, signature_len);

    // Clean up
    free(signature);
    EC_KEY_free(ec_key);

}