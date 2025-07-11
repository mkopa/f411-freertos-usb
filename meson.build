# meson.build

project('f411-freertos-usb', 'c', 'cpp',
        meson_version: '>=1.4.0',
        default_options: ['c_std=c11', 'cpp_std=c++17', 'warning_level=2'])

executable_name = meson.project_name() + '.elf'

# --- Args ---
c_defines = [
  '-DUSE_HAL_DRIVER',
  '-DSTM32F411xE',
]
add_project_arguments(c_defines, language: 'c')

# --- Headers ---
inc_dirs = include_directories(
  'App/Inc',
  'Core/Inc',
  'Drivers/STM32F4xx_HAL_Driver/Inc',
  'Drivers/STM32F4xx_HAL_Driver/Inc/Legacy',
  'Drivers/CMSIS/Device/ST/STM32F4xx/Include',
  'Drivers/CMSIS/Include',
  'Middlewares/Third_Party/FreeRTOS/Source/include',
  'Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2',
  'Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F',
  'USB_DEVICE/App',
  'USB_DEVICE/Target',
  'Middlewares/ST/STM32_USB_Device_Library/Core/Inc',
  'Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc',
  

)

# --- Sources ---
c_sources = files(
  'App/Src/app.c',
  'App/Src/circ_buffer.c',
  'Core/Src/main.c',
  'Core/Src/gpio.c',
  'Core/Src/i2c.c',
  'Core/Src/rtc.c',
  'Core/Src/spi.c',
  'Core/Src/usart.c',
  'Core/Src/stm32f4xx_it.c',
  'Core/Src/stm32f4xx_hal_msp.c',
  'Core/Src/system_stm32f4xx.c',
  'Core/Src/sysmem.c',
  'Core/Src/syscalls.c',
  'Core/Src/freertos.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c',
  'Middlewares/Third_Party/FreeRTOS/Source/croutine.c',
  'Middlewares/Third_Party/FreeRTOS/Source/event_groups.c',
  'Middlewares/Third_Party/FreeRTOS/Source/list.c',
  'Middlewares/Third_Party/FreeRTOS/Source/queue.c',
  'Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c',
  'Middlewares/Third_Party/FreeRTOS/Source/tasks.c',
  'Middlewares/Third_Party/FreeRTOS/Source/timers.c',
  'Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c',
  'Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c',
  'Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c',
  'USB_DEVICE/App/usb_device.c',
  'USB_DEVICE/App/usbd_desc.c',
  'USB_DEVICE/App/usbd_cdc_if.c',
  'USB_DEVICE/Target/usbd_conf.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c',
  'Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c',
  'Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c',
  'Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c',
  'Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c',
  'Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c'
)

asm_sources = files('startup_stm32f411xe.s')

# --- Linker ---
linker_script = files('STM32F411XX_FLASH.ld')
link_args = [
  '-Wl,-Map=' + meson.project_build_root() / executable_name + '.map,--cref',
  '-Wl,--gc-sections',
  '-T', linker_script[0].full_path(),
  '-lc', '-lm', '-lnosys'
]

# --- (.elf) ---
executable_elf = executable(
  executable_name,
  c_sources,
  asm_sources,
  include_directories: inc_dirs,
  link_args: link_args,
  link_depends: linker_script,
  install: false
)

# --- (.hex, .bin, size) ---
objcopy = find_program('arm-none-eabi-objcopy', required: true)
size_tool = find_program('arm-none-eabi-size', required: true)

custom_target(executable_name + '.hex',
  command: [objcopy, '-O', 'ihex', '@INPUT@', '@OUTPUT@'],
  input: executable_elf,
  output: executable_name + '.hex',
  build_by_default: true
)

custom_target(executable_name + '.bin',
  command: [objcopy, '-O', 'binary', '@INPUT@', '@OUTPUT@'],
  input: executable_elf,
  output: executable_name + '.bin',
  build_by_default: true
)

size_script = find_program('print_size.py')

custom_target(
  'size_report',
  command: [size_script, '@INPUT@', '@OUTPUT@'],
  input: executable_elf,
  output: 'size_report.txt',
  build_by_default: true,
  console: true
)

run_target('size',
  command: [size_tool, executable_elf]
)

# --- (flash) ---
openocd = find_program('openocd', required: false)
if openocd.found()
  run_target('flash',
    command: [
      openocd,
      '-f', meson.project_source_root() / 'openocd.cfg',
      '-c', 'program @0@ verify reset exit'.format(executable_elf.full_path())
    ],
    depends: executable_elf
  )
endif

# --- Linter/Formatter ---
clang_format = find_program('clang-format', required: false)
if clang_format.found()
  files_to_format = files(
    'App/Inc/app.h',
    'App/Inc/circ_buffer.h',
    'App/Src/app.c',
    'App/Src/circ_buffer.c'
  )
  run_target('format-app',
    command: [clang_format, '-i', files_to_format]
  )
endif