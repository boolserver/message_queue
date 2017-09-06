.PHONY: all

all:
	rm -f msg_queue.out
	gcc server_for_frontend_backend.c msg_queue.c -o msg_queue.out -lrt

run: 
	./msg_queue.out

run_test:
	rm -f test_msg_queue.out
	gcc test_msg_queue.c msg_queue.c -lrt -luuid -o test_msg_queue.out
	./test_msg_queue.out
