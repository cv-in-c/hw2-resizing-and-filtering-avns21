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

void rgb_to_hsv(image im)
{
    // TODO Fill this in

}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
