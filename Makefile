build:
	cc main.c -o tool
run:
	./tool examples/example.c
clean:
	rm tool
	rm exec-hot-reload
