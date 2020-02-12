prom = prime
obj =	./src/platform/linux_uart.c \
		./src/core/crc.c \
		./src/core/uart.c \
		./src/core/fpa.c \
		./src/core/prime.c \
		./main.c

$(prom): $(obj)
	gcc -o $(prom) $(obj)

%.o: %.c $(deps)
	$(cc) -c $< -o $@

clean:
	rm -rf $(prom)