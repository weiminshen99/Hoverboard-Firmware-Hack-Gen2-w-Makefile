
# ---------------------------------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
# 	2022-3-18  - improvements for general use by weiminshen99@gmail.com
#	2017-02-10 - Several enhancements + project update mode
#   	2015-07-22 - first version
# ----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
#
# NOTE: $(EXAMPLE_DIR)/main.c is copied to build/, so please type make twice.
#
# -----------------------------------------------------------------------------


######################################
# target
######################################
TARGET = example

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization for size
OPT = -Os

#######################################
# paths
#######################################

EXAMPLE_DIR = Examples/USART/DMA_transmitter\&receiver
#EXAMPLE_DIR = Examples/USART/Printf

# Build path
BUILD_DIR = build

#######################################

# AS includes
AS_INCLUDES =

# C includes
C_INCLUDES =  \
-IInc \
-IFirmware/CMSIS/GD/GD32F1x0/Include/ \
-IFirmware/CMSIS/ \
-IUtilities \
-I$(DRIVERS_DIR)/Include/ \
-I$(EXAMPLE_DIR)

######################################
# source
######################################
DRIVERS_DIR = Firmware/GD32F1x0_standard_peripheral

# C sources
C_SOURCES =  \
Firmware/CMSIS/GD/GD32F1x0/Source/system_gd32f1x0.c \
$(DRIVERS_DIR)/Source/gd32f1x0_adc.c \
$(DRIVERS_DIR)/Source/gd32f1x0_can.c \
$(DRIVERS_DIR)/Source/gd32f1x0_cec.c \
$(DRIVERS_DIR)/Source/gd32f1x0_cmp.c \
$(DRIVERS_DIR)/Source/gd32f1x0_crc.c \
$(DRIVERS_DIR)/Source/gd32f1x0_dac.c \
$(DRIVERS_DIR)/Source/gd32f1x0_dbg.c \
$(DRIVERS_DIR)/Source/gd32f1x0_dma.c \
$(DRIVERS_DIR)/Source/gd32f1x0_exti.c \
$(DRIVERS_DIR)/Source/gd32f1x0_fmc.c \
$(DRIVERS_DIR)/Source/gd32f1x0_fwdgt.c \
$(DRIVERS_DIR)/Source/gd32f1x0_gpio.c \
$(DRIVERS_DIR)/Source/gd32f1x0_i2c.c \
$(DRIVERS_DIR)/Source/gd32f1x0_ivref.c \
$(DRIVERS_DIR)/Source/gd32f1x0_misc.c \
$(DRIVERS_DIR)/Source/gd32f1x0_opa.c \
$(DRIVERS_DIR)/Source/gd32f1x0_pmu.c \
$(DRIVERS_DIR)/Source/gd32f1x0_rcu.c \
$(DRIVERS_DIR)/Source/gd32f1x0_rtc.c \
$(DRIVERS_DIR)/Source/gd32f1x0_slcd.c \
$(DRIVERS_DIR)/Source/gd32f1x0_spi.c \
$(DRIVERS_DIR)/Source/gd32f1x0_syscfg.c \
$(DRIVERS_DIR)/Source/gd32f1x0_timer.c \
$(DRIVERS_DIR)/Source/gd32f1x0_tsi.c \
$(DRIVERS_DIR)/Source/gd32f1x0_usart.c \
$(DRIVERS_DIR)/Source/gd32f1x0_wwdgt.c \
Utilities/gd32f1x0r_eval.c \
main.c

# $(EXAMPLE_DIR)/main.c needs to be copied to build/, and type make twice.

# ASM sources
ASM_SOURCES =  \
startup_gd32f1x0.s


#######################################
# binaries
#######################################
GCC_PATH = /Applications/ARM_11.2/bin/
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
GDB = $(GCC_PATH)/$(PREFIX)gdb
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
GDB= $(PREFIX)gdb
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_STDPERIPH_DRIVER \
-DGD32F130_150

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = GD32F130C6T_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@
#	cp $(EXAMPLE_DIR)/main.c $@

#######################################
# read, write, clean, and gdb
#######################################

clean:
	-rm -fR $(BUILD_DIR)

read:
	st-flash read firmware.bin 0x08000000 0x40000

flash:	$(BUILD_DIR)/$(TARGET).bin
	st-flash --reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000

gdb:	$(BUILD_DIR)/$(TARGET).elf
#	st-util -p 4242 & // you may type this once
	$(GDB) --eval-command="target extended-remote :4242" $(BUILD_DIR)/$(TARGET).elf

##############################################################################################
# unlock both stm32 and gd32! the command may hang, but ctrl_C out and then you can read/flash
##############################################################################################

unlock:
	openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg -c init -c "reset halt" -c "stm32f1x unlock 0"

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
