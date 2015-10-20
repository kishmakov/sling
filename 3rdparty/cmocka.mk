CMOCKA_LIB = libcmocka.so

cmocka: compile-cmocka link-cmocka

compile-cmocka:
	$(CC) -DCMOCKA_EXPORTS -DHAVE_CONFIG_H=1 $(CFLAGS) -fstack-protector -D_GNU_SOURCE -D_LARGEFILE64_SOURCE -c $(3RD_DIR)/cmocka.c -o $(OBJ_DIR)/cmocka.o

link-cmocka:
	$(CC) $(LFLAGS) -fstack-protector -D_GNU_SOURCE -D_LARGEFILE64_SOURCE -g -shared -Wl,-soname,$(CMOCKA_LIB) -o $(LIB_DIR)/$(CMOCKA_LIB) $(OBJ_DIR)/cmocka.o -lrt
