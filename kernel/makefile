# Nuke built-in rules and variables.
override MAKEFLAGS += -rR

# This is the name that our final kernel executable will have.
# Change as needed.
override KERNEL := nposkrnl.exe

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

# It is suggested to use a custom built cross toolchain to build a kernel.
# We are using the standard "cc" here, it may work by using
# the host system's toolchain, but this is not guaranteed.
override DEFAULT_KCC := clang
$(eval $(call DEFAULT_VAR,KCC,$(DEFAULT_KCC)))

override KCC_IS_CLANG := no
ifeq ($(shell $(KCC) --version 2>&1 | grep -i 'clang' >/dev/null 2>&1 && echo 1),1)
    override KCC_IS_CLANG := yes
endif

# Same thing for "ld" (the linker).
override DEFAULT_KLD := ld.lld
$(eval $(call DEFAULT_VAR,KLD,$(DEFAULT_KLD)))

# User controllable C flags.
override DEFAULT_KCFLAGS := -g -O2 -pipe
$(eval $(call DEFAULT_VAR,KCFLAGS,$(DEFAULT_KCFLAGS)))

# User controllable C preprocessor flags. We set none by default.
override DEFAULT_KCPPFLAGS :=
$(eval $(call DEFAULT_VAR,KCPPFLAGS,$(DEFAULT_KCPPFLAGS)))

ifeq ($(KARCH), x86_64)
    # User controllable nasm flags.
    override DEFAULT_KNASMFLAGS := -F dwarf -g
    $(eval $(call DEFAULT_VAR,KNASMFLAGS,$(DEFAULT_KNASMFLAGS)))
endif

# User controllable linker flags. We set none by default.
override DEFAULT_KLDFLAGS :=
$(eval $(call DEFAULT_VAR,KLDFLAGS,$(DEFAULT_KLDFLAGS)))

# Internal C flags that should not be changed by the user.
override KCFLAGS += \
    -Wall \
    -Wextra \
    -std=gnu11 \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fPIE

# Internal C preprocessor flags that should not be changed by the user.
override KCPPFLAGS := \
    -I src \
    $(KCPPFLAGS) \
    -MMD \
    -MP

ifeq ($(KARCH),x86_64)
    # Internal nasm flags that should not be changed by the user.
    override KNASMFLAGS += \
        -Wall
endif

# Architecture specific internal flags.
ifeq ($(KARCH),x86_64)
    ifeq ($(KCC_IS_CLANG),yes)
        override KCC += \
            -target x86_64-elf
    endif
    override KCFLAGS += \
        -m64 \
        -march=x86-64 \
        -mno-80387 \
        -mno-mmx \
        -mno-sse \
        -mno-sse2 \
        -mno-red-zone
    override KLDFLAGS += \
        -m elf_x86_64
    override KNASMFLAGS += \
        -f elf64

else
    $(error Architecture $(KARCH) not supported)
endif

# Internal linker flags that should not be changed by the user.
override KLDFLAGS += \
    -nostdlib \
    -pie \
    -z text \
    -z max-page-size=0x1000 \
    -T linker-$(KARCH).ld

# Use "find" to glob all *.c, *.S, and *.asm files in the tree and obtain the
# object and header dependency file names.
override CFILES := $(shell cd src && find -L * -type f -name '*.c')
override ASFILES := $(shell cd src && find -L * -type f -name '*.S')
override NASMFILES := $(shell cd src && find -L * -type f -name '*.asm')
override OBJ := $(addprefix obj-$(KARCH)/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o))
override HEADER_DEPS := $(addprefix obj-$(KARCH)/,$(CFILES:.c=.c.d) $(ASFILES:.S=.S.d))

# Default target.
.PHONY: all
all: bin-$(KARCH)/$(KERNEL)

src/limine.h:
	curl -Lo $@ https://github.com/limine-bootloader/limine/raw/trunk/limine.h

# Link rules for the final kernel executable.
# The magic printf/dd command is used to force the final ELF file type to ET_DYN.
# GNU binutils, for silly reasons, forces the ELF type to ET_EXEC even for
# relocatable PIEs, if the base load address is non-0.
# See https://sourceware.org/bugzilla/show_bug.cgi?id=31795 for more information.
bin-$(KARCH)/$(KERNEL): makefile linker-$(KARCH).ld $(OBJ)
	mkdir -p "$$(dirname $@)"
	$(KLD) $(OBJ) $(KLDFLAGS) -o $@
	printf '\003' | dd of=$@ bs=1 count=1 seek=16 conv=notrunc 2>/dev/null

# Include header dependencies.
-include $(HEADER_DEPS)

# Compilation rules for *.c files.
obj-$(KARCH)/%.c.o: src/%.c makefile src/limine.h
	mkdir -p "$$(dirname $@)"
	$(KCC) $(KCFLAGS) $(KCPPFLAGS) -c $< -o $@

# Compilation rules for *.S files.
obj-$(KARCH)/%.S.o: src/%.S makefile
	mkdir -p "$$(dirname $@)"
	$(KCC) $(KCFLAGS) $(KCPPFLAGS) -c $< -o $@

# Compilation rules for *.asm (nasm) files.
obj-$(KARCH)/%.asm.o: src/%.asm makefile
	mkdir -p "$$(dirname $@)"
	nasm $(KNASMFLAGS) $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf bin-$(KARCH) obj-$(KARCH)

.PHONY: distclean
distclean:
	rm -rf bin-* obj-* src/limine.h
