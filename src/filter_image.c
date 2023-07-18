#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
    // TODO
     float sum_of_pixels = 0; 

   
    for (int channel = 0; channel < im.c; ++channel) {
        for (int height = 0; height < im.h; ++height) {
            for (int width = 0; width < im.w; ++width) {
                sum_of_pixels += get_pixel(im, width, height, channel); 
            }
        }
    }

 
    for (int channel = 0; channel < im.c; ++channel) {
        for (int height = 0; height < im.h; ++height) {
            for (int width = 0; width < im.w; ++width) {
               
                float pixel_value = get_pixel(im, width, height, channel);
                
              
                set_pixel(im, width, height, channel, pixel_value / sum_of_pixels);
            }
        }
    }
}

image make_box_filter(int w)
{
    // TODO
     image filter = make_image(w, w, 1);

    for (int y = 0; y < w; ++y) {
        for (int x = 0; x < w; ++x) {
            set_pixel(filter, x, y, 0, 1.0);
        }
    }

    l1_normalize(filter);

    return filter;
    
   // return make_image(1,1,1);
}

image convolve_image(image im, image filter, int preserve)
{
    // TODO
    image convolve_image(image input_image, image convolution_filter, int preserve_channels)
{
    assert(convolution_filter.c == 1 || convolution_filter.c == input_image.c || convolution_filter.c == input_image.c);
    
    int half_filter_width = convolution_filter.w / 2;
    int half_filter_height = convolution_filter.h / 2;

    image result_image;

    if (preserve_channels && convolution_filter.c == input_image.c) {
       
        result_image = make_image(input_image.w, input_image.h, input_image.c);

        for (int channel = 0; channel < input_image.c; ++channel) {
            for (int y = 0; y < input_image.h; ++y) {
                for (int x = 0; x < input_image.w; ++x) {
                    float weighted_sum = 0.0;

                    for (int fy = 0; fy < convolution_filter.h; ++fy) {
                        for (int fx = 0; fx < convolution_filter.w; ++fx) {
                            int input_x = x + fx - half_filter_width;
                            int input_y = y + fy - half_filter_height;

                            float input_pixel = get_pixel(input_image, input_x, input_y, channel);
                            float filter_pixel = get_pixel(convolution_filter, fx, fy, 0);

                            weighted_sum += input_pixel * filter_pixel;
                        }
                    }

                    set_pixel(result_image, x, y, channel, weighted_sum);
                }
            }
        }
    }
    else {
       
        result_image = make_image(input_image.w, input_image.h, 1);

        for (int y = 0; y < input_image.h; ++y) {
            for (int x = 0; x < input_image.w; ++x) {
                float weighted_sum = 0.0;

                for (int channel = 0; channel < input_image.c; ++channel) {
                    for (int fy = 0; fy < convolution_filter.h; ++fy) {
                        for (int fx = 0; fx < convolution_filter.w; ++fx) {
                            int input_x = x + fx - half_filter_width;
                            int input_y = y + fy - half_filter_height;

                            float input_pixel = get_pixel(input_image, input_x, input_y, channel);
                            float filter_pixel = get_pixel(convolution_filter, fx, fy, 0);

                            weighted_sum += input_pixel * filter_pixel;
                        }
                    }
                }

                set_pixel(result_image, x, y, 0, weighted_sum);
            }
        }
    }

    return result_image;
}

   // return make_image(1,1,1);
}

image make_highpass_filter()
{
    // TODO
    int filter_size = 3;
    image filter = make_image(filter_size, filter_size, 1);

  
    float highpass_kernel[3][3] = {
        { -1, -1, -1 },
        { -1,  8, -1 },
        { -1, -1, -1 }
    };

   
    for (int y = 0; y < filter_size; ++y) {
        for (int x = 0; x < filter_size; ++x) {
            set_pixel(filter, x, y, 0, highpass_kernel[y][x]);
        }
    }

    return filter;
    
   // return make_image(1,1,1);
}

image make_sharpen_filter()
{
    // TODO
    int filter_size = 3;
    image filter = make_image(filter_size, filter_size, 1);

   
    float sharpen_kernel[3][3] = {
        { 0, -1, 0 },
        { -1, 5, -1 },
        { 0, -1, 0 }
    };

  
    for (int y = 0; y < filter_size; ++y) {
        for (int x = 0; x < filter_size; ++x) {
            set_pixel(filter, x, y, 0, sharpen_kernel[y][x]);
        }
    }

    return filter;
    return make_image(1,1,1);
}

image make_emboss_filter()
{
    // TODO
    int filter_size = 3;
    image filter = make_image(filter_size, filter_size, 1);

    // Emboss filter kernel
    float emboss_kernel[3][3] = {
        { -2, -1, 0 },
        { -1,  1, 1 },
        {  0,  1, 2 }
    };

    // Copy the kernel values to the filter image
    for (int y = 0; y < filter_size; ++y) {
        for (int x = 0; x < filter_size; ++x) {
            set_pixel(filter, x, y, 0, emboss_kernel[y][x]);
        }
    }

    return filter;
    
    //return make_image(1,1,1);
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
    
    int size = (int)(ceil(6 * sigma));
    size = size % 2 == 0 ? size + 1 : size; // Ensure it's an odd number

    image filter = make_image(size, size, 1);
    float sum = 0.0;

   
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            int center_x = size / 2;
            int center_y = size / 2;
            float exponent = -(pow(x - center_x, 2) + pow(y - center_y, 2)) / (2 * pow(sigma, 2));
            float value = exp(exponent) / (TWO_PI * pow(sigma, 2));

            set_pixel(filter, x, y, 0, value);
            sum += value;
        }
    }

   
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            set_pixel(filter, x, y, 0, get_pixel(filter, x, y, 0) / sum);
        }
    }

    return filter;
    //return make_image(1,1,1);
}

image add_image(image a, image b)
{
    // TODO
      assert(first_image.width == second_image.width &&
           first_image.height == second_image.height &&
           first_image.channels == second_image.channels);

  
    image result_image = make_image(first_image.width, first_image.height, first_image.channels);


    for (int i = 0; i < first_image.width * first_image.height * first_image.channels; ++i) {
        // Get the pixel values for the current pixel from both images
        float pixel_value_a = first_image.data[i];
        float pixel_value_b = second_image.data[i];

      
        result_image.data[i] = pixel_value_a + pixel_value_b;
    }

  
    return result_image;
 //   return make_image(1,1,1);
}

image sub_image(image a, image b)
{
    // TODO
    assert(a.w == b.w && a.h == b.h && a.c == b.c);

    image result = make_image(a.w, a.h, a.c);

    for (int c = 0; c < a.c; ++c) {
        for (int y = 0; y < a.h; ++y) {
            for (int x = 0; x < a.w; ++x) {
                float pixel_value_a = get_pixel(a, x, y, c);
                float pixel_value_b = get_pixel(b, x, y, c);
                set_pixel(result, x, y, c, pixel_value_a - pixel_value_b);
            }
        }
    }

    return result;
   // return make_image(1,1,1);
}

image make_gx_filter()
{
    // TODO
    image filter = make_image(3, 3, 1);

   
    float gx_filter[3][3] = {
        { -1, 0, 1 },
        { -2, 0, 2 },
        { -1, 0, 1 }
    };

  
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            set_pixel(filter, x, y, 0, gx_filter[y][x]);
        }
    }

    return filter;
  //  return make_image(1,1,1);
}

image make_gy_filter()
{
    // TODO
     float gy_filter[3][3] = {
        { -1, -2, -1 },
        { 0, 0, 0 },
        { 1, 2, 1 }
    };

  
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            set_pixel(filter, x, y, 0, gy_filter[y][x]);
        }
    }

    return filter;
    //return make_image(1,1,1);
}

void feature_normalize(image im)
{
    // TODO
    float mini_v = im.data[0];
    float maxi_v = im.data[0];

   
    for (int i = 0; i < im.w * im.h * im.c; i++) {
        if (im.data[i] < mini_v) mini_v = im.data[i];
        if (im.data[i] > maxi_v) maxi_v = im.data[i];
    }

   
    float r = maxi_v - mini_v;

   
    for (int i = 0; i < im.w * im.h * im.c; i++) {
        im.data[i] = (im.data[i] - min_val) / r;
    }
}

image *sobel_image(image im)
{
    // TODO
    image *result = calloc(2, sizeof(image));
    result[0] = make_image(im.w, im.h, 1); 
    result[1] = make_image(im.w, im.h, 1); 

    image gx_filter = make_gx_filter();
    image gy_filter = make_gy_filter();

   
    image gx = convolve_image(im, gx_filter, 0);
    image gy = convolve_image(im, gy_filter, 0);

   
    for (int y = 0; y < im.h; ++y) {
        for (int x = 0; x < im.w; ++x) {
            float gx_val = get_pixel(gx, x, y, 0);
            float gy_val = get_pixel(gy, x, y, 0);

            float magnitude = sqrt(gx_val * gx_val + gy_val * gy_val);
            set_pixel(result[0], x, y, 0, magnitude);

            float direction = atan2(gy_val, gx_val);
            set_pixel(result[1], x, y, 0, direction);
        }
    }

   
    feature_normalize(result[0]);

    free_image(gx);
    free_image(gy);
    free_image(gx_filter);
    free_image(gy_filter);

    return result;
   // return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
     image colored = copy_image(im);

    
    feature_normalize(colored);

  
    for (int y = 0; y < im.h; ++y) {
        for (int x = 0; x < im.w; ++x) {
            float magnitude = get_pixel(colored, x, y, 0);
            float direction = get_pixel(im, x, y, 0);

         
            float hue = (direction + TWOPI/2) / (TWOPI) * 360;

           
            set_pixel(colored, x, y, 0, hue);
            set_pixel(colored, x, y, 1, magnitude);
            set_pixel(colored, x, y, 2, magnitude);
        }
    }

    hsv_to_rgb(colored);

    return colored;
    //return make_image(1,1,1);
}
