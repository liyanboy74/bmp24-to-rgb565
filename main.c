/*
 By Liyanboy74
 https://github.com/liyanboy74
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "bmp.h"

char ask_SwapBytes='N';

typedef struct{
    uint8_t B,G,R;
}Color_S;

static void SwapBytes(uint16_t *color) {
    uint8_t temp = *color >> 8;
    *color = (*color << 8) | temp;
}

uint16_t Convert_Color_To16(Color_S Color)
{
    uint16_t CC=0;

	CC|=(((int)round((Color.B*(float)0.1215686)))&0x1f)<<0 ;//B5
	CC|=(((int)round((Color.G*(float)0.2470588)))&0x3f)<<5 ;//G6
	CC|=(((int)round((Color.R*(float)0.1215686)))&0x1f)<<11;//R5

	//CC=(((Color.R & 0xF8) << 8) | ((Color.G & 0xFC) << 3) | ((Color.B & 0xF8) >> 3));

	if(ask_SwapBytes=='y' || ask_SwapBytes=='Y')
    {
        SwapBytes(&CC);
    }

	return CC;
}

int main(int argc, char** argv)
{
    int i,j,k;
    FILE *out;
    unsigned char *BMP_Data,*Buffer,Trash[4];
    unsigned char Name[64],FileName[64],SaveName[64],HeaderName[64];

    BITMAPINFOHEADER BMP_Header;
    uint16_t BMP_WidthByteSize,BMP_Width,BMP_Hight;

    if(argc>1)
    {
        if(strcmp("--help",argv[1])==0 ||strcmp("-h",argv[1])==0 || strcmp("-H",argv[1])==0)
        {
            printf("BMP24 to RGB565 Converter\r\n");
            printf("More info: https://github.com/liyanboy74\r\n");
            printf("-------------------------------------------\r\n");
            printf("Argv[1]:\tEnter .bmp File Name\r\n");
            printf("Argv[2]:\tOptional SwapBytes (y/n)\r\n");
            printf("-------------------------------------------");
            return 0;
        }
        else
        {
            strcpy(Name,argv[1]);
            if(argc>2)
            {
                ask_SwapBytes=*argv[2];
            }
        }
    }
    else
    {
    	printf("BMP24 to RGB565 Converter\r\n");
    	printf("Run by Arg --help for Help\r\n");
        printf("Enter .bmp File Name:");
        scanf("%s",Name);
        getchar();
        printf("Are you want to Swap Bytes?(y/n)\r\n");
        ask_SwapBytes=getchar();
    }

    if(ask_SwapBytes=='y'||ask_SwapBytes=='Y')
        printf("Swap Bytes ENABLE\r\n");
    else  printf("Swap Bytes Disable\r\n");

    printf("RUN\r\n");

    sprintf(FileName,"%s.bmp",Name);
    sprintf(SaveName,"%s.h",Name);
    sprintf(HeaderName,"__%s_h__",Name);

    BMP_Data=LoadBitmapFile(FileName,&BMP_Header);

    if(BMP_Data==NULL)
    {
        printf("ERROR: Can't Open %s\r\n",FileName);
        return 1;
    }

    out=fopen(SaveName,"w");

    BMP_Width=BMP_Header.biWidth;
    BMP_Hight=BMP_Header.biHeight;

    printf("Size = %d X %d\r\n",BMP_Width,BMP_Hight);
    fprintf(out,"#ifndef %s\n#define %s\nconst uint16_t %s[%d*%d]={\n",HeaderName,HeaderName,Name,BMP_Width,BMP_Hight);

    BMP_WidthByteSize=BMP_Width*3;

    Buffer=(unsigned char *)calloc(BMP_WidthByteSize,sizeof(unsigned char));

    for(j=1;j<=BMP_Hight;j++)
	{
        memcpy(Buffer,&BMP_Data[j*((-1*BMP_WidthByteSize)-(BMP_Width%4))+ BMP_Header.biSizeImage],BMP_WidthByteSize);

		for(i=0;i<BMP_WidthByteSize;i+=3)
		{
            uint16_t Color=0;
			Color_S RColor;

			RColor.R=Buffer[i];
			RColor.G=Buffer[i+1];
			RColor.B=Buffer[i+2];

			Color=Convert_Color_To16(RColor);
			fprintf(out,"0x%04x",Color);

			if(j==BMP_Hight)
            {
                if(i!=(BMP_WidthByteSize-3)) fprintf(out," ,");
            }
            else fprintf(out," ,");

			if(k>=16)
            {
                k=0;
                fprintf(out,"\n");
            }
            else k++;
		}
	}

    fprintf(out,"};\n#endif\n");
    free(Buffer);
    free(BMP_Data);
    printf("Output Saved as %s\r\n",SaveName);
    printf("End\r\n");
    fclose(out);
    return 0;
}
