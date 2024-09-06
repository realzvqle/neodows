# Nuke built-in rules and variables.
override MAKEFLAGS += -rR

# Convenience macro to reliably declare user overridable variables.
define DEFAULT_VAR =
    ifeq ($(origin $1),default)
        override $(1) := $(2)
    endif
    ifeq ($(origin $1),undefined)
        override $(1) := $(2)
    endif
endef

# Target architecture to build for. Default to x86_64.
override DEFAULT_KARCH := x86_64
$(eval $(call DEFAULT_VAR,KARCH,$(DEFAULT_KARCH)))

override IMAGE_NAME := nightpane-$(KARCH)

.PHONY: all
all: $(IMAGE_NAME).iso

.PHONY: all-hdd
all-hdd: $(IMAGE_NAME).hdd

.PHONY: run
run: run-$(KARCH)

.PHONY: run-hdd
run-hdd: run-hdd-$(KARCH)

.PHONY: run-x86_64
run-x86_64: ovmf $(IMAGE_NAME).iso
	qemu-system-x86_64 -cdrom nightpane-x86_64.iso -boot d -d int,cpu_reset -audiodev pa,id=speaker -machine pcspk-audiodev=speaker

run-debug: ovmf $(IMAGE_NAME).hdd
	qemu-system-x86_64 -cdrom nightpane-x86_64.iso -boot d -d int,cpu_reset -s -S -audiodev pa,id=speaker -machine pcspk-audiodev=speaker
	gdb target remote :1234

.PHONY: run-hdd-x86_64
run-hdd-x86_64: ovmf $(IMAGE_NAME).hdd
	qemu-system-x86_64 -hda $(IMAGE_NAME).hdd -m 2048 -audiodev pa,id=speaker -machine pcspk-audiodev=speaker



.PHONY: ovmf
ovmf: ovmf-$(KARCH)

ovmf-x86_64:
	mkdir -p ovmf-x86_64
	cd ovmf-x86_64 && curl -o OVMF.fd https://retrage.github.io/edk2-nightly/bin/RELEASEX64_OVMF.fd


limine/limine:
	rm -rf limine
	git clone https://github.com/limine-bootloader/limine.git --branch=v7.x-binary --depth=1
	$(MAKE) -C limine

.PHONY: kernel
kernel:
	$(MAKE) -C kernel

$(IMAGE_NAME).iso: limine/limine kernel
	rm -rf iso_root
	mkdir -p iso_root/nightpane/system
	mkdir -p iso_root/boot
	cp -v kernel/bin-$(KARCH)/nposkrnl.exe iso_root/nightpane/system
	mkdir -p iso_root/boot/limine
	cp -v limine.cfg iso_root/boot/limine/
	mkdir -p iso_root/EFI/BOOT
ifeq ($(KARCH),x86_64)
	cp -v limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/boot/limine/
	cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
	cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/
	xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o $(IMAGE_NAME).iso

endif
	rm -rf iso_root

$(IMAGE_NAME).hdd: limine/limine kernel
	rm -f $(IMAGE_NAME).hdd
	dd if=/dev/zero bs=1M count=0 seek=64 of=$(IMAGE_NAME).hdd
	sgdisk $(IMAGE_NAME).hdd -n 1:2048 -t 1:ef00

ifeq ($(KARCH),x86_64)
	./limine/limine bios-install $(IMAGE_NAME).hdd

endif
	mformat -i $(IMAGE_NAME).hdd@@1M
	mmd -i $(IMAGE_NAME).hdd@@1M ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine ::/nightpane ::/nightpane/system
	mcopy -i $(IMAGE_NAME).hdd@@1M kernel/bin-$(KARCH)/nposkrnl.exe ::/nightpane/system
	mcopy -i $(IMAGE_NAME).hdd@@1M limine.cfg ::/boot/limine
ifeq ($(KARCH),x86_64)
	mcopy -i $(IMAGE_NAME).hdd@@1M limine/limine-bios.sys ::/boot/limine
	mcopy -i $(IMAGE_NAME).hdd@@1M limine/BOOTX64.EFI ::/EFI/BOOT
	mcopy -i $(IMAGE_NAME).hdd@@1M limine/BOOTIA32.EFI ::/EFI/BOOT

endif

.PHONY: clean
clean:
	rm -rf iso_root *.iso *.hdd
	$(MAKE) -C kernel clean

.PHONY: distclean
distclean: clean
	rm -rf limine ovmf*
	$(MAKE) -C kernel distclean
