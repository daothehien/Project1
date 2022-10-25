#include <math.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

unsigned char *background_filter(unsigned char *pic1, unsigned char *pic2, unsigned char *pic3, int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < channel; k++)
            {
                temp_array[i * width * channel + j * channel + k] = pic2[i * width * channel + j * channel + k];
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int devi = 0;
            for (int k = 0; k < channel; k++)
            {
                devi += abs(pic2[i * width * channel + j * channel + k] - pic1[i * width * channel + j * channel + k]);
            }
            if(devi<150)
            {
                for (int k = 0; k < channel; k++)
                {
                    temp_array[i * width * channel + j * channel + k] = pic3[i * width * channel + j * channel + k];
                }
            }
        }
    }
    return temp_array;
}

int main()
{
    int width, height, channel;
    int width1, height1, channel1;
    int width2, height2, channel2;
    char background[] = "./images/background.png";
    char foreground[] = "./images/foreground.png";
    char forecast[] = "./images/weather_forecast-resized.jpg";
    char save_path[] = "./images/new.png";

    unsigned char *pic1 = stbi_load(background, &width, &height, &channel, 0);
    if (pic1 == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    unsigned char *pic2 = stbi_load(foreground, &width1, &height1, &channel1, 0);
    if (pic2 == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    unsigned char *pic3 = stbi_load(forecast, &width2, &height2, &channel2, 0);
    if (pic3 == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }

    unsigned char *mimage = background_filter(pic1, pic2, pic3, width, height, channel);
    stbi_write_png(save_path, width, height, channel, mimage, width * channel);
    printf("New image saved to %s\n", save_path);
}