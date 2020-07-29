
/*******************************************************************************
* image
* filename: unsaved
* name: arrow
*
* preset name: Monochrome
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: no
* conversion type: Monochrome, Diffuse Dither 128
* bits per pixel: 1
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: no
*******************************************************************************/

/*
 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     } tImage;
*/
#include <stdint.h>
#include "resources.h"


static const uint8_t image_data_arrow[16] = {
    0x80, 
    0xc0, 
    0xe0, 
    0xf0, 
    0xf8, 
    0xfc, 
    0xfe, 
    0xff, 
    0xff, 
    0xfe, 
    0xfc, 
    0xf8, 
    0xf0, 
    0xe0, 
    0xc0, 
    0x80
};
const tImage arrow = { image_data_arrow, 8, 16};

