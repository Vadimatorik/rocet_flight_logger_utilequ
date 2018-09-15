CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)

# Toolchain settings
SET(TOOLCHAIN_BIN_PATH /opt/arm/gcc-arm-none-eabi-7-2018-q2-update/bin)
SET(CMAKE_C_COMPILER_WORKS 1)
SET(CMAKE_CXX_COMPILER_WORKS 1)
SET(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_PATH}/arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_PATH}/arm-none-eabi-g++)
SET(ARM_SIZE "${TOOLCHAIN_BIN_PATH}/arm-none-eabi-size")
SET(ARM_OBJDUMP "${TOOLCHAIN_BIN_PATH}/arm-none-eabi-objdump")

# Compiler settings & flags
SET(OPTIMIZATION_DEBUG_FLAGS "-O0 -g3")
SET(COMMON_FLAGS "-mcpu=cortex-m3 -mthumb -mthumb-interwork -mfloat-abi=soft")

SET(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} ${OPTIMIZATION_DEBUG_FLAGS} -std=gnu99 -fshort-enums")
SET(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} ${OPTIMIZATION_DEBUG_FLAGS} -Wall -Werror -Wextra -std=c++14 -fno-exceptions \
        -fshort-enums -ffunction-sections -fdata-sections")

# Linker settings
SET(LD_FILE "${CMAKE_CURRENT_SOURCE_DIR}/submodule/module_stm32f1_low_level/LD/STM32F103XB_FLASH.ld")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-fmessage-length=0 -nostartfiles -Xlinker -gc-sections \
        -specs=nosys.specs -specs=nano.specs -fno-exceptions -Wl,--undefined=uxTopUsedPriority -ffunction-sections \
        -Wl,--gc-sections -T ${LD_FILE}")

PROJECT(rocket_logger C CXX ASM)
SET(CMAKE_CXX_STANDARD 14)

#SET(CMAKE_VERBOSE_MAKEFILE on)

add_definitions(-D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\))

INCLUDE_DIRECTORIES(
        ${CMAKE_SOURCE_DIR}/cfg
        ${CMAKE_SOURCE_DIR}/user_code
        ${CMAKE_SOURCE_DIR}/user_code/mk_hardware
        )

# Submodule headers
INCLUDE_DIRECTORIES(
        ${CMAKE_SOURCE_DIR}/submodule/module_freertos_for_stm32f1
        ${CMAKE_SOURCE_DIR}/submodule/module_freertos_for_stm32f1/include
        ${CMAKE_SOURCE_DIR}/submodule/module_mc_hardware_interfaces
        ${CMAKE_SOURCE_DIR}/submodule/module_mc_hardware_interfaces_implementation_for_stm32/inc
        ${CMAKE_SOURCE_DIR}/submodule/module_sensor/mpu6050
        ${CMAKE_SOURCE_DIR}/submodule/module_stm32f1_low_level/CMSIS/device/Include
        ${CMAKE_SOURCE_DIR}/submodule/module_stm32f1_low_level/CMSIS/Include
        ${CMAKE_SOURCE_DIR}/submodule/module_stm32f1_low_level/HAL/Inc
        ${CMAKE_SOURCE_DIR}/submodule/module_stm32f1_low_level/HAL/Inc/Legacy
        ${CMAKE_SOURCE_DIR}/submodule/module_system_dummy
)

FILE(GLOB_RECURSE USER_SRC "user_code/*.*")
FILE(GLOB_RECURSE MODULES_SRC "submodule/*.cpp" "submodule/*.c")
SET(STARTUP_FILE "./submodule/module_stm32f1_low_level/startupe/startup_stm32f103xb.s")

ADD_EXECUTABLE(${PROJECT_NAME}.elf ${MODULES_SRC} ${STARTUP_FILE} ${USER_SRC} ${LD_FILE})

SET(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
SET(ASM_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.asm)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${BIN_FILE}")

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMENT "Invoking: Cross ARM GNU Print Size"
        COMMAND ${ARM_SIZE} ${PROJECT_NAME}.elf)
