#!/usr/bin/env python3
import sys
import subprocess

# STM32F411CEU6
TOTAL_FLASH = 512 * 1024  # 512 KB
TOTAL_RAM = 128 * 1024   # 128 KB
ELF_FILE = sys.argv[1]
SIZE_TOOL = 'arm-none-eabi-size'
try:
    result = subprocess.check_output([SIZE_TOOL, ELF_FILE]).decode('utf-8')
except FileNotFoundError:
    print(f"Error: '{SIZE_TOOL}' not found. ARM toolchain is in PATH?")
    sys.exit(1)
except subprocess.CalledProcessError as e:
    print(f"Błąd podczas uruchamiania size tool: {e}")
    sys.exit(1)

# Parsowanie wyniku
lines = result.strip().split('\n')
if len(lines) < 2:
    print(f"Błąd: Nieoczekiwany format wyjścia z size tool:\n{result}")
    sys.exit(1)

# Druga linia zawiera dane w formacie:
#   text	   data	    bss	    dec	    hex	filename
try:
    parts = lines[1].split()
    text = int(parts[0])
    data = int(parts[1])
    bss = int(parts[2])
except (IndexError, ValueError):
    print(f"Błąd: Nie można sparsować wyniku z size tool:\n{result}")
    sys.exit(1)

# Obliczenia:
# FLASH = kod (.text) + dane zainicjalizowane (.data)
# RAM   = dane zainicjalizowane (.data) + dane niezainicjalizowane (.bss)
flash_used = text + data
ram_used = data + bss
flash_percent = (flash_used / TOTAL_FLASH) * 100
ram_percent = (ram_used / TOTAL_RAM) * 100

# Generowanie raportu
report = f"""
+-----------------------------------------------------------------+
|                        MEMORY USAGE REPORT                     |
+-----------------------------------------------------------------+
| MCU: STM32F411CEU6 ({TOTAL_FLASH // 1024} KB Flash, {TOTAL_RAM // 1024} KB RAM)
| fILE: {ELF_FILE.split('/')[-1]}
+-----------------------------------------------------------------+
| MEMORY |      USED             |   FREE     |   USED TOTAL |
|--------|----------------------- |-----------------|-----------------|
| FLASH  | {flash_used:>10d}    B | {TOTAL_FLASH:>10d} B |      {flash_percent:6.2f} % |
| RAM    | {ram_used:>10d}      B | {TOTAL_RAM:>10d} B |      {ram_percent:6.2f} % |
+-----------------------------------------------------------------+
"""

print(report)

# Meson/Ninja wymaga, aby `custom_target` tworzył plik wyjściowy.
# Możemy zapisać raport również do pliku tekstowego.
if len(sys.argv) > 2:
    output_file = sys.argv[2]
    with open(output_file, 'w') as f:
        f.write(report)
