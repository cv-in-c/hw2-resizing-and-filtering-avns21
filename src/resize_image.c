#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
     int ix = (int)(x + 0.5);  
    int iy = (int)(y + 0.5);  

    return get_pixel(im, ix, iy, c);
    //hii
    return 0;
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
     image resized = make_image(w, h, im.c);
    float w_scale = (float)(im.w) / w;
    float h_scale = (float)(im.h) / h;

    for (int k = 0; k < im.c; ++k) {
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w; ++i) {
                float im_x = (i + 0.5) * w_scale - 0.5;
                float im_y = (j + 0.5) * h_scale - 0.5;
                set_pixel(resized, i, j, k, nn_interpolate(im, im_x, im_y, k));
            }
        }
    }

    return resized;
   // return make_image(1,1,1);
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    int x1 = (int)x;
    int y1 = (int)y;
    int x2 = x1 + 1;
    int y2 = y1 + 1;

    float dx = x - x1;
    float dy = y - y1;

    float Q11 = get_pixel(im, x1, y1, c);
    float Q12 = get_pixel(im, x1, y2, c);
    float Q21 = get_pixel(im, x2, y1, c);
    float Q22 = get_pixel(im, x2, y2, c);

    float top_interp = (1 - dx) * Q11 + dx * Q21;
    float bottom_interp = (1 - dx) * Q12 + dx * Q22;
    float interpolated_value = (1 - dy) * top_interp + dy * bottom_interp;

    return interpolated_value;
    //return 0;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    image resized = make_image(w, h, im.c);
    float w_scale = (float)(im.w) / w;
    float h_scale = (float)(im.h) / h;

    for (int k = 0; k < im.c; ++k) {
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w; ++i) {
                float im_x = (i + 0.5) * w_scale - 0.5;
                float im_y = (j + 0.5) * h_scale - 0.5;
                set_pixel(resized, i, j, k, bilinear_interpolate(im, im_x, im_y, k));
            }
        }
    }

    return resized;
    //return make_image(1,1,1);
}

