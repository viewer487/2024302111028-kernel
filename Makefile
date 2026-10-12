CC   = riscv64-unknown-elf-gcc
LD   = riscv64-unknown-elf-ld
CFLAGS = -Wall -Werror -O -std=gnu99 -mcmodel=medany -ffreestanding \
         -nostdlib -fno-common -ggdb -march=rv64gc -fno-stack-protector -fno-pie
QEMU = qemu-system-riscv64

SRCS = $(wildcard kernel/*.c) $(wildcard kernel/*.S)
OBJS = $(patsubst %.c,%.o,$(filter %.c,$(SRCS))) \
	$(patsubst %.S,%.o,$(filter %.S,$(SRCS)))

kernel/kernel: $(OBJS) kernel/kernel.ld
	$(LD) -T kernel/kernel.ld -o $@ $(OBJS)

%.o: %.c kernel/riscv.h kernel/course_sid.h
	$(CC) $(CFLAGS) -Ikernel -c -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -Ikernel -c -o $@ $<

qemu: kernel/kernel
	$(QEMU) -machine virt -bios none -kernel kernel/kernel -nographic

clean:
	rm -f kernel/*.o kernel/kernel
