OBJS := main.o sem.o server.o shm.o shmfifo.o thread_pool.o hashmap.o msg.o
CC := gcc

server:$(OBJS)
	@$(CC) $^ -o $@ -lpthread
	@echo "Done"
%.o:%.c
	@$(CC) -c $< -o $@
clean:
	@rm *.o server
	@echo "Clear"
