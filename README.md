sudo apt-get install openocd clang-format


meson setup build --cross-file cross_file.txt

meson compile -C build

meson compile -C build format-app 

ninja -C build flash