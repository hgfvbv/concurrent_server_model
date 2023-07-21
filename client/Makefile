OBJS := client.o main.o sem.o shm.o shmfifo.o msg.o
CC := gcc

client:$(OBJS)
	@$(CC) $^ -o $@ -lpthread
	@echo "Done"
%.o:%.c
	@$(CC) -c $< -o $@
clean:
	@rm *.o client
	@echo "Clear"
