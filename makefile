.PHONY: build-kernel

build-kernel:
	cd kernel && make

build-loader:
	cd boot && make

all:
	@if [ ! -d bin ]; then \
		mkdir -p bin; \
	fi
	make build-loader
	make build-kernel
	aarch64-none-elf-ld -nostdlib -Tlinker.ld boot.o obj/*.o -o bin/nposkrnl.exe


clean:
	cd kernel && make clean
	cd boot && make clean
	rm -rf bin
run:
	make all
	qemu-system-aarch64 -machine virt -cpu cortex-a76 -kernel bin/nposkrnl.exe -device virtio-gpu-pci -display sdl -serial mon:stdio