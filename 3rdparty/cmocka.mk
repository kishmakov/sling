CMOCKA_LIB = libcmocka.so

cmocka: compile-cmocka link-cmocka

compile-cmocka:
	$(CC) -DCMOCKA_EXPORTS -DHAVE_CONFIG_H=1  -std=gnu99 -pedantic -pedantic-errors -Wall -Wextra -Wshadow -Wmissing-prototypes -Wdeclaration-after-statement -Wunused -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute -Wundef -fPIC -fstack-protector -D_GNU_SOURCE -D_LARGEFILE64_SOURCE -g -Iinclude -c $(3RD_DIR)/cmocka.c -o $(OBJ_DIR)/cmocka.o

link-cmocka:
	$(CC) -fPIC -std=gnu99 -pedantic -pedantic-errors -Wall -Wextra -Wshadow -Wmissing-prototypes -Wdeclaration-after-statement -Wunused -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute -Wundef -fPIC -fstack-protector -D_GNU_SOURCE -D_LARGEFILE64_SOURCE -g -shared -Wl,-soname,$(CMOCKA_LIB) -o $(LIB_DIR)/$(CMOCKA_LIB) $(OBJ_DIR)/cmocka.o -lrt
