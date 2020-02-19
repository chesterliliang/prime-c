prom = prime
obj =	./src/platform/x_uart.c \
		./src/crc.c \
		./src/comm/uart.c \
		./src/comm/io.c \
		./src/fpa.c \
		./src/prime.c \
		./main.c

$(prom): $(obj)
	gcc -o $(prom) $(obj)

%.o: %.c $(deps)
	$(cc) -c $< -o $@

clean:
	rm -rf $(prom)