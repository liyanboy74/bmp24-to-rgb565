# 24-bit BMP to 16-bit RGB565 Converter         



**Compile:**

```
gcc main.c -o Bmp24ToRgb565
```

**Usage:**

```
Bmp24ToRgb565 [FileName] [y/n:Optional SwapBytes]
```


**Example:**

*In Windows CMD*
```
Bmp24ToRgb565.exe img y
```
Or **simply double click** `Bmp24ToRgb565.exe` for run ,it will ask for `.bmp` file Name.

**Output:**

The output file `Name.h` have below content:
```c
#ifndef __name_h__
#define __name_h__
const uint16_t name[X*Y]={.....................};
#endif
```

include `Name.h` in your project and use it.
