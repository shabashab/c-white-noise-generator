#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

void create_image(size_t image_width, size_t image_height, size_t pixel_size, char *filename);

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

  create_image(image_width, image_height, pixel_size, filename);

  return 0;
}

void create_image(size_t image_width, size_t image_height, size_t pixel_size, char *filename)
{
  FILE *file;

  if ((file = fopen(filename, "w")) == NULL)
  {
    printf("Can't open the file %s\n", filename);
    exit(1);
  }

  //Write header for ppm image file
  fprintf(file, "P3\n");
  fprintf(file, "%lu %lu\n255\n", image_width, image_height);

  //Initialize pixels
  int image_buffer_length = image_width * image_height;
  uint8_t *image_buffer = (uint8_t *)malloc(sizeof(uint8_t) * image_buffer_length);

  //Initialize data pixels
  int pixels_count =
      (image_height / pixel_size) * (image_width / pixel_size);
  uint8_t *pixels = (uint8_t *)malloc(sizeof(uint8_t) * pixels_count);

  //Initialize random nums generator
  srand(time(NULL));

  //Fill the array of data pixels
  while (--pixels_count)
    pixels[pixels_count] = rand() % 255;

  //Fill the image buffer based on array of pixels
  for (int x = 0; x < image_width; x++)
    for (int y = 0; y < image_height; y++)
      image_buffer[(y * image_width) + x] = pixels[((y / pixel_size) * (image_width / pixel_size)) + (x / pixel_size)];

  //Write the image buffer to the file
  for (int i = 0; i < image_buffer_length; i++)
    fprintf(file, "%d %d %d\n", image_buffer[i], image_buffer[i], image_buffer[i]);

  fclose(file);
}