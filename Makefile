##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [2.29.2] date: [Fri Oct 26 17:24:51 CEST 2018]
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = MiniMouse

BOARD_MURATA      = 1
RELAY             = 1
BOARD_WITH_SENSOR = 1
BOARD_L4          = 0
RADIO_SX1276      = 1
RADIO_SX1272      = 0
RADIO_SX126x      = 0
DEVICE_UNDER_TEST = 1
RADIO_WITH_TCX0   = 1
####################SX126x_BOARD
# building variablesSX126x_BOARD
######################################
# debug build?
DEBUG = 1C_SOURCES
# optimization
OPT = -Os -g


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
CPP_SOURCES =  \
UserCode/appli.cpp\
UserCode/main.cpp \
radio/sx1272/sx1272.cpp\
radio/SX1276Lib/sx1276/sx1276.cpp\
radio/SX126X/SX126x.cpp\
MinimouseSrc/LoRaMacCryptoMiniMouse.cpp\
MinimouseSrc/LoraWanProcess.cpp\
MiniMouse/MacLayer.cpp\
MiniMouse/MiniMouseAes.cpp\
MiniMouse/MiniMouseCmac.cpp\
MiniMouse/PhyLayer.cpp\
MiniMouse/RadioIsrRoutine.cpp\
MiniMouse/Regions.cpp\
MiniMouse/RegionUS.cpp\
MiniMouse/utilities.cpp\
RadioPlaner/RadioPlaner.cpp
ifeq ($(RADIO_SX1276), 1)
    CPP_SOURCES +=  \
    PointToPoint/PointToPointReceiver.cpp\
    PointToPoint/PointToPointTransmitter.cpp\
    UserCode/MainPtpRxTx.cpp 
endif
ifeq ($(BOARD_MURATA), 0)
    CPP_SOURCES +=  \
    McuApi/STM32/SrcStm32/stm32l4xx_it.cpp \
    McuApi/STM32/SrcStm32/stm32l4xx_hal_msp.cpp\
	McuApi/ClassSTM32L4.cpp 
else
    CPP_SOURCES +=  \
    McuApi/STM32/SrcStm32/stm32l0xx_it.cpp \
    McuApi/STM32/SrcStm32/stm32l0xx_hal_msp.cpp\
	McuApi/ClassSTM32L072.cpp  
endif

ifeq ($(BOARD_MURATA), 0)
C_SOURCES = \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_lptim.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_wwdg.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c \
McuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c \
McuApi/STM32/SrcStm32/system_stm32l4xx.c
else
C_SOURCES = \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_i2c_ex.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_lptim.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rtc.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rtc_ex.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_spi.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_tim_ex.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_uart_ex.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_wwdg.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_rcc_ex.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ex.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_flash_ramfunc.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_gpio.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_dma.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_pwr_ex.c \
McuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_cortex.c \
McuApi/STM32/SrcStm32/system_stm32l0xx.c
endif

# ASM sources
ifeq ($(BOARD_MURATA), 0)
    ASM_SOURCES =  \
    McuApi/STM32/startup_stm32l476xx.s
else
    ASM_SOURCES =  \
    McuApi/STM32/startup_stm32l072xx.s
endif

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)g++
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
CPP = $(PREFIX)g++
AS = $(PREFIX)g++ -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
ifeq ($(BOARD_MURATA), 0)
    CPU = -mcpu=cortex-m4
else
    CPU = -mcpu=cortex-m0plus
endif
# fpu
ifeq ($(BOARD_MURATA), 0)
    FPU = -mfpu=fpv4-sp-d16
endif
# float-abi
ifeq ($(BOARD_MURATA), 0)
    FLOAT-ABI = -mfloat-abi=hard
endif
# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
ifeq ($(BOARD_MURATA), 0)
    C_DEFS =  \
    -DUSE_HAL_DRIVER \
    -DSTM32L476xx
else
    C_DEFS =  \
    -DUSE_HAL_DRIVER \
    -DMURATA_BOARD \
    -DSTM32L072xx
endif
ifeq ($(DEVICE_UNDER_TEST), 1)
    C_DEFS += -DDEVICE_UNDER_TEST  
endif
ifeq ($(RADIO_SX1276), 1)
    C_DEFS += -DSX1276_BOARD  
endif
ifeq ($(RADIO_SX1272), 1)
    C_DEFS += -DSX1272_BOARD  
endif
ifeq ($(RADIO_SX126x), 1)
    C_DEFS += -DSX126x_BOARD  
endif
ifeq ($(RELAY), 1)
    C_DEFS += -DRELAY
endif
ifeq ($(RADIO_WITH_TCX0), 1)
   C_DEFS += -DRADIO_WITH_TCX0
endif
ifeq ($(BOARD_WITH_SENSOR), 1)
    C_DEFS += -DBOARD_WITH_SENSOR
endif
ifeq ($(BOARD_L4), 1)
    C_DEFS += -DBOARD_L4  
endif
    c_DEFS += -DDEBUG_ARRAY
# AS includes
AS_INCLUDES = 

# C includesOBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))
ifeq ($(BOARD_MURATA), 0)
C_INCLUDES =  \
-IMcuApi/STM32/IncStm32 \
-IMcuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Inc \
-IMcuApi/STM32/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy \
-IMcuApi/STM32/Drivers/CMSIS/Device/ST/STM32L4xx/Include \
-IMcuApi/STM32/Drivers/CMSIS/Include \
-IUserCode \
-IMcuApi\
-IMinimouseSrc\
-Iradio/sx1272\
-Iradio/SX1276Lib/registers\
-Iradio/SX1276Lib/sx1276\
-Iradio/SX126X\
-IPointToPoint\
-IRadioPlaner
else
C_INCLUDES =  \
-IMcuApi/STM32/IncStm32 \
-IMcuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Inc \
-IMcuApi/STM32/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy \
-IMcuApi/STM32/Drivers/CMSIS/Device/ST/STM32L0xx/Include \
-IMcuApi/STM32/Drivers/CMSIS/Include \
-IUserCode \
-IMcuApi\
-IMinimouseSrc\
-Iradio/sx1272\
-Iradio/SX1276Lib/registers\
-Iradio/SX1276Lib/sx1276\
-Iradio/SX126X\
-IPointToPoint\
-IRadioPlaner
endif
# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections  -fno-exceptions
CPPFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -fno-rtti -fno-exceptions -std=c++11 
ifeq ($(DEBUG), 1)
#-gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
ifeq ($(BOARD_MURATA), 0)
LDSCRIPT = McuApi/STM32/STM32L476RGTx_FLASH.ld
else
LDSCRIPT = McuApi/STM32/STM32L072CZYx_FLASH.ld
endif
# libraries
LIBS =   -lstdc++ -lsupc++ -lm -lc -lnosys


LIBDIR = 
LDFLAGS = $(MCU) --specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR) 
	$(CPP) -c $(CPPFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

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

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***