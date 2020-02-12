prom = gcc
obj =	./src/platform/linux_uart.o \
		./src/core/crc.o \
		./src/core/uart.o \
		./src/core/fpa.o \
		./src/core/prime.o \
		./main.o

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)

%.o: %.c $(deps)
	$(cc) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)