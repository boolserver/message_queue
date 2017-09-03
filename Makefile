.PHONY: all

all:
	rm -f msg_queue.out
	gcc server_for_frontend_backend.c msg_queue.c -o msg_queue.out -lrt

run: 
	./msg_queue.out
