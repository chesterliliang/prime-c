cc = gcc
prom = test
deps = src/BHZ1Finger.h
obj =	../../platform/linux_uart.o \
		../../platform/bios_serial.o \
		../../core/crc.o \
		../../core/uart.o \
		../../core/fpa.o \
		../../core/prime.o \
		BHZ1Finger.o \
		test.o


$(prom): $(obj)
	$(cc) -o $(prom) $(obj)

%.o: %.c $(deps)
	$(cc) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)
