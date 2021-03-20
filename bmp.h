/*
 * bmp.h
 *
 *  Created on: 2019. febr. 17.
 *      Author: Benjami
 */

#ifndef __BMP_H_
#define __BMP_H_

typedef struct __attribute__((packed)) tagBITMAPFILEHEADER {
  uint16_t   bfType;        //bitmap id
  uint32_t   bfSize;        //The size of the BMP file in bytes 
  uint16_t   bfReserved1;
  uint16_t   bfReserved2;
  uint32_t   bfOffBits;
} BITMAPFILEHEADER; // size is 14 bytes

typedef struct __attribute__((packed)) tagBITMAPINFOHEADER {
  uint32_t  biSize;           //the size of this header, in bytes (40) 
  uint32_t  biWidth;          //the bitmap width in pixels (signed integer) 
  uint32_t  biHeight;         //the bitmap height in pixels (signed integer) 
  uint16_t  biPlanes;         //the number of color planes (must be 1) 
  uint16_t  biBitCount;       //the number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 and 32. 
  uint32_t  biCompression;
  uint32_t  biSizeImage;      //the image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps. 
  uint32_t  biXPelsPerMeter;  //the horizontal resolution of the image
  uint32_t  biYPelsPerMeter;  //the vertical resolution of the image
  uint32_t  biClrUsed;
  uint32_t  biClrImportant;
} BITMAPINFOHEADER; // size is 40 bytes

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);

#endif /* __BMP_H_ */
