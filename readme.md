# BMP to RGB565
This is a BMP 24bit to RGB 565 (16bit) Converter for Embedding.

## Clone & Compile

```
git clone --recursive https://github.com/liyanboy74/bmp24-to-rgb565.git
cd bmp24-to-rgb565
mkdir build && cd build
cmake ..
make
```

## Usage
```
Bmp24ToRgb565 [FileName] [y/n:Optional SwapBytes]
```
For help use`--help` or `-h`


## Example
In Windows CMD:
```
Bmp24ToRgb565.exe img
```
Or simply **double click** `Bmp24ToRgb565.exe` for run ,it will ask for `.bmp` file Name.


## Output
The output file `Name.h` have below content:
```c
#ifndef __name_h__
#define __name_h__
const uint16_t name[X*Y]={.....................};
#endif
```
Include `Name.h` in your project and use it.

## Note
Windows bash script `.bat` for multiple convert:
 ```
 for /l %%x in (1, 1, 100) do (
   Bmp24ToRgb565.exe img%%x
)
 ```
