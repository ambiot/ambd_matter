include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
MATTER_MBEDTLS_DIR = $(BASEDIR)/component/common/network/ssl/mbedtls-matter/library

vpath %.c $(MATTER_MBEDTLS_DIR) $(shell find $(MATTER_MBEDTLS_DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(MATTER_MBEDTLS_DIR)/aes.c			\
       $(MATTER_MBEDTLS_DIR)/aesni.c			\
	   $(MATTER_MBEDTLS_DIR)/arc4.c			\
       $(MATTER_MBEDTLS_DIR)/aria.c		\
	   $(MATTER_MBEDTLS_DIR)/asn1parse.c		\
	   $(MATTER_MBEDTLS_DIR)/asn1write.c		\
	   $(MATTER_MBEDTLS_DIR)/base64.c		\
	   $(MATTER_MBEDTLS_DIR)/bignum.c		\
	   $(MATTER_MBEDTLS_DIR)/blowfish.c		\
       $(MATTER_MBEDTLS_DIR)/camellia.c		\
       $(MATTER_MBEDTLS_DIR)/ccm.c			\
	   $(MATTER_MBEDTLS_DIR)/certs.c			\
	   $(MATTER_MBEDTLS_DIR)/chacha20.c			\
	   $(MATTER_MBEDTLS_DIR)/chachapoly.c			\
       $(MATTER_MBEDTLS_DIR)/cipher.c			\
       $(MATTER_MBEDTLS_DIR)/cipher_wrap.c		\
       $(MATTER_MBEDTLS_DIR)/cmac.c			\
	   $(MATTER_MBEDTLS_DIR)/constant_time.c          \
       $(MATTER_MBEDTLS_DIR)/ctr_drbg.c		\
       $(MATTER_MBEDTLS_DIR)/debug.c			\
       $(MATTER_MBEDTLS_DIR)/des.c			\
       $(MATTER_MBEDTLS_DIR)/dhm.c			\
       $(MATTER_MBEDTLS_DIR)/ecdh.c			\
	   $(MATTER_MBEDTLS_DIR)/ecdsa.c			\
       $(MATTER_MBEDTLS_DIR)/ecjpake.c			\
       $(MATTER_MBEDTLS_DIR)/ecp.c			\
       $(MATTER_MBEDTLS_DIR)/ecp_curves.c			\
	   $(MATTER_MBEDTLS_DIR)/entropy.c			\
	   $(MATTER_MBEDTLS_DIR)/entropy_poll.c			\
       $(MATTER_MBEDTLS_DIR)/error.c			\
       $(MATTER_MBEDTLS_DIR)/gcm.c			\
       $(MATTER_MBEDTLS_DIR)/havege.c			\
       $(MATTER_MBEDTLS_DIR)/hkdf.c			\
       $(MATTER_MBEDTLS_DIR)/hmac_drbg.c			\
	   $(MATTER_MBEDTLS_DIR)/md2.c			\
	   $(MATTER_MBEDTLS_DIR)/md4.c			\
	   $(MATTER_MBEDTLS_DIR)/md5.c			\
	   $(MATTER_MBEDTLS_DIR)/md.c			\
       $(MATTER_MBEDTLS_DIR)/memory_buffer_alloc.c	\
       $(MATTER_MBEDTLS_DIR)/nist_kw.c		\
       $(MATTER_MBEDTLS_DIR)/oid.c		\
       $(MATTER_MBEDTLS_DIR)/padlock.c		\
       $(MATTER_MBEDTLS_DIR)/pem.c		\
	   $(MATTER_MBEDTLS_DIR)/pk.c		\
       $(MATTER_MBEDTLS_DIR)/pkcs11.c		\
       $(MATTER_MBEDTLS_DIR)/pkcs12.c		\
       $(MATTER_MBEDTLS_DIR)/pkcs5.c			\
       $(MATTER_MBEDTLS_DIR)/pkparse.c		\
       $(MATTER_MBEDTLS_DIR)/pk_wrap.c		\
       $(MATTER_MBEDTLS_DIR)/pkwrite.c		\
       $(MATTER_MBEDTLS_DIR)/platform.c		\
       $(MATTER_MBEDTLS_DIR)/platform_util.c	\
       $(MATTER_MBEDTLS_DIR)/poly1305.c	\
       $(MATTER_MBEDTLS_DIR)/ripemd160.c	\
       $(MATTER_MBEDTLS_DIR)/rsa.c	\
       $(MATTER_MBEDTLS_DIR)/rsa_internal.c	\
       $(MATTER_MBEDTLS_DIR)/sha1.c			\
	   $(MATTER_MBEDTLS_DIR)/sha256.c		\
	   $(MATTER_MBEDTLS_DIR)/sha512.c		\
       $(MATTER_MBEDTLS_DIR)/ssl_cache.c		\
       $(MATTER_MBEDTLS_DIR)/ssl_ciphersuites.c	\
       $(MATTER_MBEDTLS_DIR)/ssl_cli.c		\
       $(MATTER_MBEDTLS_DIR)/ssl_cookie.c		\
	   $(MATTER_MBEDTLS_DIR)/ssl_msg.c		\
       $(MATTER_MBEDTLS_DIR)/ssl_srv.c   		\
       $(MATTER_MBEDTLS_DIR)/ssl_ticket.c		\
       $(MATTER_MBEDTLS_DIR)/ssl_tls.c		\
       $(MATTER_MBEDTLS_DIR)/threading.c		\
       $(MATTER_MBEDTLS_DIR)/timing.c			\
       $(MATTER_MBEDTLS_DIR)/version.c		\
       $(MATTER_MBEDTLS_DIR)/version_features.c	\
       $(MATTER_MBEDTLS_DIR)/x509.c			\
       $(MATTER_MBEDTLS_DIR)/x509_create.c		\
       $(MATTER_MBEDTLS_DIR)/x509_crl.c		\
       $(MATTER_MBEDTLS_DIR)/x509_crt.c		\
       $(MATTER_MBEDTLS_DIR)/x509_csr.c		\
       $(MATTER_MBEDTLS_DIR)/x509write_crt.c		\
       $(MATTER_MBEDTLS_DIR)/x509write_csr.c		\
       $(MATTER_MBEDTLS_DIR)/xtea.c		\

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)


#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS


#*****************************************************************************#
#              GENERATE OBJECT FILE
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.d

-include $(DEPS)
