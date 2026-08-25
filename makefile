GCC=gcc
LIB=includes

all: program run clean

program: ./main.c ./$(LIB)/socket_utils.c ./$(LIB)/commands/commans_handler.c ./$(LIB)/data_structs/hash_table.c ./$(LIB)/data_structs/linked_list.
	$(GCC) $^ -o $@

run: ./program
	./$^

clean: ./program
	rm $^