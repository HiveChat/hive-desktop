#include <stdio.h>
#include <sodium.h>

#define crypto_generichash_HEXBYTES (crypto_generichash_BYTES * 2 + 1)

typedef unsigned char UCHAR;

char* to_hex( char hex[], const UCHAR bin[], size_t length )
{
	int i;
	UCHAR *p0 = (UCHAR *)bin;
	char *p1 = hex;

	for( i = 0; i < length; i++ ) {
		snprintf( p1, 3, "%02x", *p0 );
		p0 += 1;
		p1 += 2;
	}

	return hex;
}

int main()
{
	if (sodium_init() == -1) 
	{
        return 1;
	}

    unsigned char client_publickey[crypto_box_PUBLICKEYBYTES]; 
    unsigned char client_secretkey[crypto_box_SECRETKEYBYTES]; 
    unsigned char server_publickey[crypto_box_PUBLICKEYBYTES]; 
    unsigned char server_secretkey[crypto_box_SECRETKEYBYTES]; 
    unsigned char scalarmult_q_by_client[crypto_scalarmult_BYTES]; 
    unsigned char scalarmult_q_by_server[crypto_scalarmult_BYTES]; 
    unsigned char sharedkey_by_client[crypto_generichash_BYTES]; 
    unsigned char sharedkey_by_server[crypto_generichash_BYTES]; 
    crypto_generichash_state h;

    /* Create client's secret and public keys */
    randombytes_buf(client_secretkey, sizeof client_secretkey);
    crypto_scalarmult_base(client_publickey, client_secretkey);
    /* Create server's secret and public keys */
    randombytes_buf(server_secretkey, sizeof server_secretkey);
    crypto_scalarmult_base(server_publickey, server_secretkey);
      /* The client derives a shared key from its secret key and the server's public key */ /* shared key = h(q ‖ client_publickey ‖ server_publickey) */
	if (crypto_scalarmult(scalarmult_q_by_client, client_secretkey, server_publickey) != 0 )
	{
		/* Error */
	}
	crypto_generichash_init(&h, NULL, 0U, sizeof sharedkey_by_client); 
	crypto_generichash_update(&h, scalarmult_q_by_client, sizeof scalarmult_q_by_client); 
	crypto_generichash_update(&h, client_publickey, sizeof client_publickey); 
	crypto_generichash_update(&h, server_publickey, sizeof server_publickey); 
	crypto_generichash_final(&h, sharedkey_by_client, sizeof sharedkey_by_client);

	/* The server derives a shared key from its secret key and the client's public key */ /* shared key = h(q ‖ client_publickey ‖ server_publickey) */
	if (crypto_scalarmult(scalarmult_q_by_server, server_secretkey, client_publickey) != 0 )
	{
		/* Error */
	}
	crypto_generichash_init(&h, NULL, 0U, sizeof sharedkey_by_server); 
	crypto_generichash_update(&h, scalarmult_q_by_server, sizeof scalarmult_q_by_server); 
	crypto_generichash_update(&h, client_publickey, sizeof client_publickey); 
	crypto_generichash_update(&h, server_publickey, sizeof server_publickey); 
	crypto_generichash_final(&h, sharedkey_by_server, sizeof sharedkey_by_server);
	/* sharedkey_by_client and sharedkey_by_server are identical */

    printf("sodium!\n");

	char client_hex[crypto_generichash_HEXBYTES];
    sodium_bin2hex(&client_hex[0], crypto_generichash_HEXBYTES, &sharedkey_by_client[0], crypto_generichash_BYTES);
    char server_hex[crypto_generichash_HEXBYTES];
    sodium_bin2hex(&server_hex[0], crypto_generichash_HEXBYTES, &sharedkey_by_server[0], crypto_generichash_BYTES);
    printf("Client Shared Key: %s\n", client_hex);
    printf("Server Shared Key: %s\n", server_hex);
    return 0;
}
