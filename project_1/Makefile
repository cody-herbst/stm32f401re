
# arm variables
CC := gcc
UTIL := objcopy

# mcpu and macro names
MCPU := cortex-m4
MACRO := STM32F401xE

# important directories
LINKERDIR := linkers
SRCDIR := src
BINDIR := bin
INCLUDEDIR := include
LIBDIR := lib
ASMB := asmb
CONFIGDIR := config

# important files
OPENOCD_CONFIG_FILE := $(CONFIGDIR)/st_nucleo_f4.cfg
OPENOCD_LOG := .openocd.log
FLASHLINKER := $(LINKERDIR)/STM32F401CE_FLASH.ld

# source and object files wildcards
C_FILES := $(wildcard $(SRCDIR)/*.c)
OBJ_FILES := $(addprefix $(BINDIR)/,$(notdir $(C_FILES:.c=.o)))

# flags
LD_FLAGS := -mcpu=$(MCPU) -mlittle-endian -mthumb -D$(MACRO) -T$(FLASHLINKER) -Wl,--gc-sections
CC_FLAGS := -Wall -mcpu=$(MCPU) -mlittle-endian -mthumb -I$(INCLUDEDIR)/ -D$(MACRO)
UTIL_FLAGS := -Oihex

###############################################################################################################################
# builds all of the necessary files

build: $(BINDIR)/ $(BINDIR)/main.hex

$(BINDIR)/main.hex: $(BINDIR)/main.elf
	arm-none-eabi-$(UTIL) $(UTIL_FLAGS) $< $@

$(BINDIR)/main.elf: $(OBJ_FILES) 
	arm-none-eabi-$(CC) $(CC_FLAGS) -c $(ASMB)/startup_stm32f401xe.s -o $(BINDIR)/startup.o
	arm-none-eabi-$(CC) $(LD_FLAGS) $^ $(BINDIR)/startup.o -o $@ 

$(BINDIR)/%.o: $(SRCDIR)/%.c
	arm-none-eabi-$(CC) $(CC_FLAGS) -c $< -o $@

$(BINDIR)/:
	mkdir $(BINDIR)/

################################################################################################################################
# cleans the project

clean:
	rm -r $(BINDIR)/*.*
	rm -r $(OPENOCD_LOG)


################################################################################################################################
# openocd commands

flash: $(BINDIR)/ build
	openocd -f $(OPENOCD_CONFIG_FILE) -l $(OPENOCD_LOG) -c "init" -c "reset halt" -c "flash write_image erase $(BINDIR)/main.hex" -c "reset run" -c "exit"

debug: $(BINDIR)/ build
	openocd -f $(OPENOCD_CONFIG_FILE) -l $(OPENOCD_LOG)