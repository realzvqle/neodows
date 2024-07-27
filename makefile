


all:
	nasm -f bin src/boot.asm -o boot.bin
	dd if=boot.bin of=disk.img bs=512 count=1
	qemu-system-x86_64 -drive format=raw,file=disk.img