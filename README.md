# stm32l475-cxx

This repository shows how to develop a C++ application layer based on a FreeRTOS and ST HAL, C code base. All the code is designed to be build and flash on the [B-L475E-IOT01A2](https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) evaluation board.

## Build

The following content explains how to build the application, which is based on CMake.
The following Software are mandatory:
 - CMake
 - make
 - GNU GCC ARM toolchain

### From VS code

To build the project into VS Code the [CMake extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) is mandatory.

When the CMake extension is install, follow the next step:
 1. Select your kit : `Ctrl + Shift + P` → then type `CMake: Select a Kit` and select the right toolchain.
 2. On the CMale Extension menu click on `…` and then `Clean Reconfigure All Project`.
 3. On the CMale Extension click on the `Build All Project` icon.
 4. You should see the following logs on the output console.

 ```
 …
[build] [ 95%] Building C object CMakeFiles/stm32l475_cpp.elf.dir/freertos/FreeRTOS-Kernel/list.c.o
[build] [ 95%] Building C object CMakeFiles/stm32l475_cpp.elf.dir/freertos/FreeRTOS-Kernel/queue.c.o
[build] [ 96%] Building C object CMakeFiles/stm32l475_cpp.elf.dir/freertos/FreeRTOS-Kernel/stream_buffer.c.o
[build] [ 98%] Building C object CMakeFiles/stm32l475_cpp.elf.dir/freertos/FreeRTOS-Kernel/tasks.c.o
[build] [ 98%] Building CXX object CMakeFiles/stm32l475_cpp.elf.dir/main/src/main.cpp.o
[build] [ 99%] Building C object CMakeFiles/stm32l475_cpp.elf.dir/freertos/FreeRTOS-Kernel/timers.c.o
[build] [100%] Linking CXX executable stm32l475_cpp.elf
[build] Invoking: Unsigned Hex file creation
[build] Invoking: Unsigned Hex file creation
[build] [100%] Built target stm32l475_cpp.elf
[driver] Build completed: 00:00:02.769
[build] Build finished with exit code 0
 ```

### From the terminal

Open the termial at the root repository's folder then type:

```Shell
cmake -B build
```

Then:

```Shell
make -C build -j10
```
