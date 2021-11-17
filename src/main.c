#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "image.h"

#define DEFAULT_IMAGE_WIDTH 1000;
#define DEFAULT_IMAGE_HEIGHT 1000;
#define DEFAULT_PIXEL_SIZE 10;
#define DEFAULT_FILE_NAME "output.ppm";

int main(int argc, char **argv)
{
  size_t image_width = DEFAULT_IMAGE_WIDTH;
  size_t image_height = DEFAULT_IMAGE_HEIGHT;
  size_t pixel_size = DEFAULT_PIXEL_SIZE;
  char *filename = DEFAULT_FILE_NAME;

  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-f") == 0)
    {
      i++;
      assert(i < argc);
      filename = (char *)malloc(strlen(argv[i]));
      strcpy(filename, argv[i]);
      continue;
    }

    if (strcmp(argv[i], "-w") == 0)
    {
      i++;
      assert(i < argc);
      image_width = atoi(argv[i]);
      continue;
    }

    if (strcmp(argv[i], "-h") == 0)
    {
      i++;
      assert(i < argc);
      image_height = atoi(argv[i]);
      continue;
    }

    if (strcmp(argv[i], "-p") == 0)
    {
      i++;
      assert(i < argc);
      pixel_size = atoi(argv[i]);
      continue;
    }
  }

  IMAGE *image = image_create(image_width, image_height);

  //Initialize random nums generator
  srand(time(NULL));

  //Fill the image buffer based on array of pixels
  for (int x = 0; x < image_width / pixel_size; x++)
  {
    for (int y = 0; y < image_height / pixel_size; y++)
    {
      int x_from = x * pixel_size;
      int y_from = y * pixel_size;
      int x_to = (x + 1) * pixel_size - 1;
      int y_to = (y + 1) * pixel_size - 1;

      image_set_pixel_range(image, x_from, y_from, x_to, y_to, rand() % 256);
    }
  }


  image_save(image, filename);

  return 0;
}
