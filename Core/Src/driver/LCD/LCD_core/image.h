/*
 * image.h
 *
 *  Created on: 31 ����. 2019 �.
 *      Author: tabur
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdint.h>

typedef struct _tImage
{
  uint16_t 					xSize;
  uint16_t 					ySize;
  uint16_t 					bytesPerLine;
  uint8_t					bitsPerPixel;
  const unsigned char* 		pData;
} sImage;

#define GUI_BITMAP			sImage
#define GUI_CONST_STORAGE	const

//extern GUI_CONST_STORAGE GUI_BITMAP bmSTLogo;
//extern GUI_CONST_STORAGE GUI_BITMAP bmpocLogo;
extern GUI_CONST_STORAGE GUI_BITMAP bmtemplate_B;

#endif /* IMAGE_H_ */
