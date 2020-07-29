#include "datatypes.h"
#include "oled.h"
#include "resources.h"
#include <string.h>

void graphics_draw_bitmap_mono(int const x, int const y, const tImage *image)
{
    int x0, y0, i, bit_count, byte_count;
    char cur_value;

    x0 = 0;
    y0 = 0;
    bit_count = 8;
    byte_count = 0;

    //assumes image is stored as a stream of bits
    for (i = 0; i < (image->height * image->width); i++)
    {
        if (bit_count == 8)
        {
            cur_value = image->data[byte_count++];
            bit_count = 0;
        }

        if (cur_value & 0x80)
        {
            oled_put_pixel(x0 + x, y0 + y);
        }

        cur_value <<= 1;

        x0++;
        bit_count++;

        if (x0 == image->width)
        {
            y0++;
            x0 = 0;
            bit_count = 8;
        }

    }
}

static tChar *find_char_by_code(int const code, const tFont *font)
{
    /* all fonts start with 0x20, which is space */
    if ((code - 0x20) >= font->length)
    {
        return &(font->chars[0x7E - 0x20]);
    }

    return &(font->chars[code - 0x20]);
}

void graphics_put_text(const char *str, int const x, int const y, const tFont *font)
{
    int len = strlen(str);
    int index = 0;
    int code = 0;
    int x1 = x;
    int y1 = y;

    code = str[index];
    tChar *ch = find_char_by_code(code, font);

    while (index < len)
    {

        graphics_draw_bitmap_mono(x1, y1, ch->image);

        x1 += ch->image->width;

        index++;

        code = str[index];
        ch = find_char_by_code(code, font);

        if ((x1 + ch->image->width) >= 128)
        {
            /* wrap */
            x1 = x;
            y1 += ch->image->height;

            if (y1 >= 128)
            {
                /* not enough room */
                return;
            }
        }

    }
}

static uint32_t string_length_pixels(char const * const string, const tFont *font)
{
	int len = 0;
	int px = 0;
	int index = 0;
	int code;

	len = strlen(string);

	while (index < len)
	{
		code = string[index];
		tChar *ch = find_char_by_code(code, font);
		px += ch->image->width;
		index++;
	}

	return px;
}

void graphics_draw_menu(char const * const * const items, uint8_t const count, char const * const title, uint8_t const index)
{
	int string_px_len;

	/* put selected in the middle with icon to denote the selected item.  Text is 16 high, so menu can be three high */

	if (items > index)
	{
		oled_clear();
		string_px_len = string_length_pixels(title,  &font_medium);

		if (string_px_len < 128)
		{
			graphics_put_text(title, (128-string_px_len)/2, 0, &font_medium);
		}
		else
		{
			graphics_put_text(title, 0, 0, &font_medium);
		}

		if (index > 0)
		{
			graphics_put_text(items[index-1], 12,16, &font_medium);
			graphics_put_text(items[index], 12,32, &font_medium);
			graphics_draw_bitmap_mono(0,32,&arrow);
			if ((index + 1) < items)
			{
				graphics_put_text(items[index+1], 12,48, &font_medium);
			}
		}
		else
		{
			graphics_put_text(items[index], 12,32, &font_medium);
			graphics_draw_bitmap_mono(0,32,&arrow);
			if ((index + 1) < items)
			{
				graphics_put_text(items[index+1], 12,48, &font_medium);
			}
		}

		oled_write_framebuffer();
	}
}

