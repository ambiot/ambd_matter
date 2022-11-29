include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES	                              #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/application/matter/mbedtls
MATTER = $(CHIPDIR)/third_party/mbedtls/repo/library


vpath %.c $(DIR) $(shell find $(DIR) -type d) $(MATTER) $(shell find $(MATTER) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#
CSRC = $(DIR)/net_sockets.c		\
       $(MATTER)/aes.c			\
       $(MATTER)/aesni.c			\
	   $(MATTER)/arc4.c			\
       $(MATTER)/aria.c		\
	   $(MATTER)/asn1parse.c		\
	   $(MATTER)/asn1write.c		\
	   $(MATTER)/base64.c		\
	   $(MATTER)/bignum.c		\
	   $(MATTER)/blowfish.c		\
       $(MATTER)/camellia.c		\
       $(MATTER)/ccm.c			\
	   $(MATTER)/certs.c			\
	   $(MATTER)/chacha20.c			\
	   $(MATTER)/chachapoly.c			\
       $(MATTER)/cipher.c			\
       $(MATTER)/cipher_wrap.c		\
       $(MATTER)/cmac.c			\
	   $(MATTER)/constant_time.c          \
       $(MATTER)/ctr_drbg.c		\
       $(MATTER)/debug.c			\
       $(MATTER)/des.c			\
       $(MATTER)/dhm.c			\
       $(MATTER)/ecdh.c			\
	   $(MATTER)/ecdsa.c			\
       $(MATTER)/ecjpake.c			\
       $(MATTER)/ecp.c			\
       $(MATTER)/ecp_curves.c			\
	   $(MATTER)/entropy.c			\
	   $(MATTER)/entropy_poll.c			\
       $(MATTER)/error.c			\
       $(MATTER)/gcm.c			\
       $(MATTER)/havege.c			\
       $(MATTER)/hkdf.c			\
       $(MATTER)/hmac_drbg.c			\
	   $(MATTER)/md2.c			\
	   $(MATTER)/md4.c			\
	   $(MATTER)/md5.c			\
	   $(MATTER)/md.c			\
       $(MATTER)/memory_buffer_alloc.c	\
       $(MATTER)/nist_kw.c		\
       $(MATTER)/oid.c		\
       $(MATTER)/padlock.c		\
       $(MATTER)/pem.c		\
	   $(MATTER)/pk.c		\
       $(MATTER)/pkcs11.c		\
       $(MATTER)/pkcs12.c		\
       $(MATTER)/pkcs5.c			\
       $(MATTER)/pkparse.c		\
       $(MATTER)/pk_wrap.c		\
       $(MATTER)/pkwrite.c		\
       $(MATTER)/platform.c		\
       $(MATTER)/platform_util.c	\
       $(MATTER)/poly1305.c	\
       $(MATTER)/ripemd160.c	\
       $(MATTER)/rsa.c	\
       $(MATTER)/rsa_internal.c	\
       $(MATTER)/sha1.c			\
	   $(MATTER)/sha256.c		\
	   $(MATTER)/sha512.c		\
       $(MATTER)/ssl_cache.c		\
       $(MATTER)/ssl_ciphersuites.c	\
       $(MATTER)/ssl_cli.c		\
       $(MATTER)/ssl_cookie.c		\
	   $(MATTER)/ssl_msg.c		\
       $(MATTER)/ssl_srv.c   		\
       $(MATTER)/ssl_ticket.c		\
       $(MATTER)/ssl_tls.c		\
       $(MATTER)/threading.c		\
       $(MATTER)/timing.c			\
       $(MATTER)/version.c		\
       $(MATTER)/version_features.c	\
       $(MATTER)/x509.c			\
       $(MATTER)/x509_create.c		\
       $(MATTER)/x509_crl.c		\
       $(MATTER)/x509_crt.c		\
       $(MATTER)/x509_csr.c		\
       $(MATTER)/x509write_crt.c		\
       $(MATTER)/x509write_csr.c		\
       $(MATTER)/xtea.c		\

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
