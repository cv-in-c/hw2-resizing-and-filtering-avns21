#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in
     x = fminf(fmaxf(x, 0), im.w - 1);
     y = fminf(fmaxf(y, 0), im.h - 1);
     c = fminf(fmaxf(c, 0), im.c - 1);

     int entry = x + y*im.w + c*im.w*im.h;
     return im.data[entry];


}
void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
     if (x < 0 || x >= im.w || y < 0 || y >= im.h || c < 0 || c >= im.c)
    {
        // Invalid coordinates, return without doing anything
        return;
    }
    
    // Calculate the index of the pixel in the image data array
    int entry = c * im.w * im.h + y * im.w + x;
    
    // Set the pixel value at the calculated index
    im.data[entry] = v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    memcpy(copy.data, im.data, im.w * im.h * im.c * sizeof(float));
    // TODO Fill this in
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    int i, j;
    float r, g, b, y;
    for ( j = 0; j < im.h; j++) {
        for ( i = 0; i < im.w; i++) {
            // Get the RGB values of the current pixel
            r = get_pixel(im, i, j, 0);
            g = get_pixel(im, i, j, 1);
            b = get_pixel(im, i, j, 2);

            // Calculate the luma value using the weighted sum formula
            y = 0.299 * r + 0.587 * g + 0.114 * b;

            // Set the grayscale pixel value in the new image
            set_pixel(gray, i, j, 0, y);
        }
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
    for (int y = 0; y < im.h; y++)
    {
        for (int x = 0; x < im.w; x++)
        {
            float pixel = get_pixel(im, x, y, c);
            set_pixel(im, x, y, c, pixel + v);
        }
    }
}

void clamp_image(image im)
{
    // TODO Fill this in
    for (int c = 0; c < im.c; c++)
    {
        for (int y = 0; y < im.h; y++)
        {
            for (int x = 0; x < im.w; x++)
            {
                float pixel = get_pixel(im, x, y, c);
                pixel = fminf(fmaxf(pixel, 0), 1);
                set_pixel(im, x, y, c, pixel);
            }
        }
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
    int num_pixels = im.w * im.h;

    for (int pixel_index = 0; pixel_index < num_pixels; pixel_index++) {
        float red = 0, green = 0, blue = 0;

        float hue = im.data[pixel_index];
        float saturation = im.data[pixel_index + num_pixels];
        float value = im.data[pixel_index + 2 * num_pixels];

        float chroma = value * saturation;
        if (saturation != 0) {
            hue *= 6.0;
            float hue_segment = hue - (int)hue;
            float m = value - chroma;
            float m1 = value - hue_segment * chroma;
            float m2 = value - (1 - hue_segment) * chroma;

            int hue_segment_int = (int)hue;
            switch (hue_segment_int) {
                case 0:
                    red = value;
                    green = m2;
                    blue = m;
                    break;
                case 1:
                    red = m1;
                    green = value;
                    blue = m;
                    break;
                case 2:
                    red = m;
                    green = value;
                    blue = m2;
                    break;
                case 3:
                    red = m;
                    green = m1;
                    blue = value;
                    break;
                case 4:
                    red = m2;
                    green = m;
                    blue = value;
                    break;
                case 5:
                    red = value;
                    green = m;
                    blue = m1;
                    break;
            }
        } else {
            red = value;
            green = value;
            blue = value;
        }

        im.data[pixel_index] = red;
        im.data[pixel_index + num_pixels] = green;
        im.data[pixel_index + 2 * num_pixels] = blue;
    }

}

void rgb_to_hsv(image im)
{
    for (int pixel_index = 0; pixel_index < im.w * im.h; pixel_index++) {
      
        float red = im.data[pixel_index];
        float green = im.data[pixel_index + im.w * im.h];
        float blue = im.data[pixel_index + 2 * im.w * im.h];

      
        float value = three_way_max(red, green, blue);

       
        float minimum = three_way_min(red, green, blue);

     
        float chroma = value - minimum;

   
        float saturation = (value == 0 ? 0 : chroma / value);

      
        float hue = 0;
        if (value != minimum) {
            if (value == red) {
                hue = (green - blue) / chroma;
            } else if (value == green) {
                hue = (blue - red) / chroma + 2;
            } else if (value == blue) {
                hue = (red - green) / chroma + 4;
            }
            hue /= 6.0;
            if (hue < 0) {
                hue += 1;
            }
        }

      
        im.data[pixel_index] = hue;
        im.data[pixel_index + im.w * im.h] = saturation;
        im.data[pixel_index + 2 * im.w * im.h] = value;
    }
}

