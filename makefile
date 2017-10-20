PROJECT_NAME	:= ay_player

#**********************************************************************
# Параметры сборки проекта.
#**********************************************************************
FREE_RTOS_OPTIMIZATION			:= -g3 -Og
USER_CODE_OPTIMIZATION			:= -g3 -Og
MICRO_SD_DRIVER_OPTIMIZATION		:= -g3 -Og
FAT_FS_OPTIMIZATION			:= -g3 -Og

LD_FILES = -T stm32f1_low_driver/CMSIS/device/gcc/linker/STM32F103XB_FLASH.ld
MK_FLAGS		:= -mcpu=cortex-m3 -mthumb -mfloat-abi=soft 

C_FLAGS			:= $(MK_FLAGS) 
# Все предупреждения == ошибки.
C_FLAGS			+= -Werror
# Выдавать предупреждения (ошибки) о сомнительных констукциях.
C_FLAGS			+= -Wall
# Выдавать предупреждение (ошибку) о любых сомнительных действиях.
C_FLAGS			+= -Wextra 
C_FLAGS			+= -std=c99 
# Если переменная объявлена как enum, то она должна иметь возможность
# хранить в себе всевозможные состояния этого enum-а (а не только текущее).
C_FLAGS			+= -fshort-enums
# Развертывание циклов.
C_FLAGS			+= -funroll-loops

C_FAT_FS_FLAGS		:= $(MK_FLAGS) -std=gnu89

CPP_FLAGS		:= $(MK_FLAGS)     
CPP_FLAGS		+= -Werror -Wall -Wextra
CPP_FLAGS		+= -std=c++1z
CPP_FLAGS		+= -funroll-loops

LDFLAGS			:= $(MK_FLAGS)
LDFLAGS			+= $(LD_FILES)
# Размещает каждую функцию в отдельной секции.
LDFLAGS			+= -ffunction-sections -fdata-sections
# Убираем неиспользуемые функции из .elf.
LDFLAGS			+= -Wl,--gc-sections 

# Формируем map файл.
#LDFLAGS			+= -Wl,-Map="build/$(PROJECT_NAME).map"

#**********************************************************************
# Параметры toolchain-а.
#**********************************************************************
TOOLCHAIN_PATH	= arm-none-eabi

CC	= $(TOOLCHAIN_PATH)-gcc
CPP	= $(TOOLCHAIN_PATH)-g++
CCDEP	= $(TOOLCHAIN_PATH)-gcc
LD	= $(TOOLCHAIN_PATH)-g++
AR	= $(TOOLCHAIN_PATH)-ar
AS	= $(TOOLCHAIN_PATH)-gcc
OBJCOPY	= $(TOOLCHAIN_PATH)-objcopy
OBJDUMP	= $(TOOLCHAIN_PATH)-objdump
GDB	= $(TOOLCHAIN_PATH)-gdb
SIZE	= $(TOOLCHAIN_PATH)-size

#**********************************************************************
# Конфигурация проекта пользователя.
#**********************************************************************
# Все файлы из папки cfg в каталоге проекта.
USER_CFG_H_FILE		:= $(wildcard cfg/*.h)
USER_CFG_DIR		:= cfg
USER_CFG_PATH		:= -I$(USER_CFG_DIR)

#**********************************************************************
# Интерфейсы микроконтроллера.
#**********************************************************************
# Все файлы из папки cfg в каталоге проекта.
MK_INTER_H_FILE		:= $(wildcard mk_hardware_interfaces/*.h)
MK_INTER_DIR		:= mk_hardware_interfaces
MK_INTER_PATH		:= -I$(MK_INTER_DIR)
	
#**********************************************************************
# Для сборки FreeRTOS.
#**********************************************************************
# Собираем все необходимые .h файлы FreeRTOS.
# FreeRTOS.h должен обязательно идти первым! 
FREE_RTOS_H_FILE	:= FreeRTOS_for_stm32f1/FreeRTOS.h
FREE_RTOS_H_FILE	+= $(wildcard FreeRTOS_for_stm32f1/include/*.h)

# Директории, в которых лежат файлы FreeRTOS.
FREE_RTOS_DIR		:= FreeRTOS_for_stm32f1
FREE_RTOS_DIR		+= FreeRTOS_for_stm32f1/include

# Подставляем перед каждым путем директории префикс -I.
FREE_RTOS_PATH		:= $(addprefix -I, $(FREE_RTOS_DIR))

# Получаем список .c файлов ( путь + файл.c ).
FREE_RTOS_C_FILE	:= $(wildcard FreeRTOS_for_stm32f1/*.c)

# Получаем список .o файлов ( путь + файл.o ).
# Сначала прибавляем префикс ( чтобы все .o лежали в отдельной директории
# с сохранением иерархии.
FREE_RTOS_OBJ_FILE	:= $(addprefix build/obj/, $(FREE_RTOS_C_FILE))
# Затем меняем у всех .c на .o.
FREE_RTOS_OBJ_FILE	:= $(patsubst %.c, %.o, $(FREE_RTOS_OBJ_FILE))

FREE_RTOS_INCLUDE_FILE	:= -include"./FreeRTOS_for_stm32f1/include/StackMacros.h"
# Сборка FreeRTOS.
# $< - текущий .c файл (зависемость).
# $@ - текущая цель (создаваемый .o файл).
# $(dir путь) - создает папки для того, чтобы путь файла существовал.
build/obj/FreeRTOS_for_stm32f1/%.o:	FreeRTOS_for_stm32f1/%.c 
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(FREE_RTOS_PATH) $(USER_CFG_PATH) $(FREE_RTOS_INCLUDE_FILE) -c $< -o $@

	
#**********************************************************************
# Для сборки FatFS.
#**********************************************************************
FAT_FS_H_FILE	:= $(shell find module_fat_fs_by_chan/ -maxdepth 3 -type f -name "*.h" )
FAT_FS_CPP_FILE	:= $(shell find module_fat_fs_by_chan/ -maxdepth 3 -type f -name "*.c" )
FAT_FS_DIR	:= $(shell find module_fat_fs_by_chan/ -maxdepth 3 -type d -name "*" )
FAT_FS_PATH	:= $(addprefix -I, $(FAT_FS_DIR))
FAT_FS_OBJ_FILE	:= $(addprefix build/obj/, $(FAT_FS_CPP_FILE))
FAT_FS_OBJ_FILE	:= $(patsubst %.c, %.o, $(FAT_FS_OBJ_FILE))
build/obj/module_fat_fs_by_chan/%.o:	module_fat_fs_by_chan/%.c $(USER_CFG_H_FILE)
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(C_FAT_FS_FLAGS) $(FAT_FS_PATH) $(USER_CFG_PATH) $(FAT_FS_OPTIMIZATION) -c $< -o $@


#**********************************************************************
# Драйвер SD карты (micro_sd_driver_by_vadimatorik).
#**********************************************************************
MICRO_SD_DRIVER_H_FILE		:= $(shell find micro_sd_driver_by_vadimatorik/ -maxdepth 3 -type f -name "*.h" )
MICRO_SD_DRIVER_CPP_FILE	:= $(shell find micro_sd_driver_by_vadimatorik/ -maxdepth 3 -type f -name "*.cpp" )
MICRO_SD_DRIVER_DIR		:= $(shell find micro_sd_driver_by_vadimatorik/ -maxdepth 3 -type d -name "*" )
MICRO_SD_DRIVER_PATH		:= $(addprefix -I, $(MICRO_SD_DRIVER_DIR))
MICRO_SD_DRIVER_OBJ_FILE	:= $(addprefix build/obj/, $(MICRO_SD_DRIVER_CPP_FILE))
MICRO_SD_DRIVER_OBJ_FILE	:= $(patsubst %.cpp, %.o, $(MICRO_SD_DRIVER_OBJ_FILE))
build/obj/micro_sd_driver_by_vadimatorik/%.o:	micro_sd_driver_by_vadimatorik/%.cpp
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(MK_INTER_PATH) $(MICRO_SD_DRIVER_PATH) $(USER_CFG_PATH) $(STM32_F2_API_PATH) $(FREE_RTOS_PATH)  $(MICRO_SD_DRIVER_OPTIMIZATION) -c $< -o $@
	
#**********************************************************************
# Сборка кода пользователя.
# Весь код пользователя должен быть в корневой папке.
#**********************************************************************
USER_H_FILE		:= $(shell find user_code/ -maxdepth 5 -type f -name "*.h" )
USER_CPP_FILE		:= $(shell find user_code/ -maxdepth 5 -type f -name "*.cpp" )
USER_C_FILE		:= $(shell find user_code/ -maxdepth 5 -type f -name "*.c" )
USER_DIR		:= $(shell find user_code/ -maxdepth 5 -type d -name "*" )
USER_PATH		:= $(addprefix -I, $(USER_DIR))
USER_OBJ_FILE		:= $(addprefix build/obj/, $(USER_CPP_FILE))
USER_OBJ_FILE		+= $(addprefix build/obj/, $(USER_C_FILE))
USER_OBJ_FILE		:= $(patsubst %.cpp, %.o, $(USER_OBJ_FILE))
USER_OBJ_FILE		:= $(patsubst %.c, %.o, $(USER_OBJ_FILE))

build/obj/%.o:	%.c	
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) 				\
	$(USER_PATH) 					\
	$(FAT_FS_PATH) 					\
	$(MK_INTER_PATH)  				\
	$(STM32_F2_API_PATH) 				\
	$(USER_CFG_PATH) 				\
	$(FREE_RTOS_PATH) 				\
	$(MICRO_SD_DRIVER_PATH) 			\
	$(USER_CODE_OPTIMIZATION)			\
	-c $< -o $@
	
build/obj/%.o:	%.cpp	
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) 				\
	$(USER_PATH) 					\
	$(FAT_FS_PATH) 					\
	$(MK_INTER_PATH)  				\
	$(USER_CFG_PATH) 				\
	$(FREE_RTOS_PATH) 				\
	$(MICRO_SD_DRIVER_PATH) 			\
	$(USER_CODE_OPTIMIZATION)			\
	-c $< -o $@



#**********************************************************************
# Компановка проекта.
#**********************************************************************
PROJECT_OBJ_FILE	:= 	$(FAT_FS_OBJ_FILE) 				\
				$(FREE_RTOS_OBJ_FILE) 				\
				$(USER_OBJ_FILE)				\
				$(MICRO_SD_DRIVER_OBJ_FILE) 			
				
build/$(PROJECT_NAME).elf:	$(PROJECT_OBJ_FILE)
	@$(LD) $(LDFLAGS) $(PROJECT_OBJ_FILE)  -o build/$(PROJECT_NAME).elf
	@echo ' '
	@echo 'Finished building target: $@'
	@echo ' '

$(PROJECT_NAME).siz:	build/$(PROJECT_NAME).elf
	@echo 'Print Size:'
	@arm-none-eabi-size --format=berkeley "build/$(PROJECT_NAME).elf"
	@echo ' '

all:	$(PROJECT_NAME).siz
#@$(OBJDUMP) -D build/$(PROJECT_NAME).elf > build/$(PROJECT_NAME).asm
#@$(OBJCOPY) build/$(PROJECT_NAME).elf build/$(PROJECT_NAME).bin -O binary
	
clean:	
	@rm -R ./build
	@echo 'Project cline!'
	@echo ' '
