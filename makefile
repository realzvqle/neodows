


all:
	nasm -f bin src/boot.asm -o boot.bin
	nasm -f bin src/kernel.asm -o kernel.bin
	dd if=boot.bin of=neodows.img bs=512 count=1
	dd if=kernel.bin of=neodows.img bs=512 count=1 conv=notrunc


	qemu-system-x86_64 -drive format=raw,file=neodows.img -d int