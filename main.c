#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

int image_width       = 1000;
int image_height      = 1000;
int pixel_size        = 10;

void fill_pixel(int* pixels, int x, int y, int color);

void write_pixels(FILE* file, int* pixels);

int main(int argc, char** argv) 
{
  char* filename = "./noise.ppm";

  for(int i = 1; i < argc; i++)
  {
    if(strcmp(argv[i], "-f") == 0)
    {
      i++;
      assert(i < argc);
      filename = (char*)malloc(strlen(argv[i]));
      strcpy(filename, argv[i]);
      continue;
    }

    if(strcmp(argv[i], "-w") == 0)
    {
      i++;
      assert(i < argc);
      image_width = atoi(argv[i]);
      continue;
    }

    if(strcmp(argv[i], "-h") == 0)
    {
      i++;
      assert(i < argc);
      image_height = atoi(argv[i]);
      continue;
    }

    if(strcmp(argv[i], "-p") == 0)
    {
      i++;
      assert(i < argc);
      pixel_size = atoi(argv[i]);
      continue;
    }
  }

  FILE* file = fopen(filename, "w");

  int h_pixels_count = image_width / pixel_size;
  int v_pixels_count = image_height / pixel_size;

  int* pixels = (int*)malloc(sizeof(int) * image_height * image_width);
  printf("%d\n", image_height * image_width);

  if(file == NULL) 
  {
    printf("An error occurred while opening the file");
    exit(1);
  }

  fprintf(file, "P3\n");
  fprintf(file, "%d %d\n255\n", image_width, image_height);

  srand(time(NULL));

  for(int x = 0; x < h_pixels_count; x++)
  {
    for(int y = 0; y < v_pixels_count; y++)
    {
      int color = rand() % 256;
      fill_pixel(pixels, x * pixel_size, y * pixel_size, color);
    }
  }

  write_pixels(file, pixels);

  fclose(file);

  return 0;
}

void fill_pixel(int* pixels, int x, int y, int color)
{
  int pixel_x, pixel_y;

  for(int x_iter = 0; x_iter < pixel_size; x_iter++)
  {
    for(int y_iter = 0; y_iter < pixel_size; y_iter++)
    {
      pixel_x = x + x_iter;
      pixel_y = y + y_iter;

      pixels[(pixel_y * image_width) + pixel_x] = color;
    }
  }
}

void write_pixels(FILE* file, int* pixels)
{
  for(int i = 0; i < image_width * image_height; i++)
  {
    fprintf(file, "%d %d %d\n", pixels[i], pixels[i], pixels[i]);
  }
}
