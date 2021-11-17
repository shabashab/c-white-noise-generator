#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
  size_t width;
  size_t height;
  uint8_t *buf;
  size_t buf_len;
} IMAGE;

IMAGE* image_create(size_t width, size_t height);
void image_set_pixel(IMAGE* image, size_t x, size_t y, uint8_t color);
void image_set_pixel_range(IMAGE* image, size_t x_from, size_t y_from, size_t x_to, size_t y_to, uint8_t color);
void image_save(IMAGE* image, char *filename);

#ifndef IMAGE_IMPL
#define IMAGE_IMPL


void fatal(char *message)
{
  printf("%s\n", message);
  exit(1);
}

IMAGE* image_create(size_t width, size_t height)
{
  IMAGE* result = (IMAGE*)malloc(sizeof(IMAGE));
  result->width = width;
  result->height = height;
  result->buf_len = width * height;
  result->buf = (uint8_t*)malloc(sizeof(uint8_t) * result->buf_len);
  return result;
}

void image_set_pixel(IMAGE* image, size_t x, size_t y, uint8_t color)
{
  image->buf[(y * image->width) + x] = color;
}

void image_set_pixel_range(IMAGE* image, size_t x_from, size_t y_from, size_t x_to, size_t y_to, uint8_t color)
{
  for(size_t x = x_from; x <= x_to; x++)
    for(size_t y = y_from; y <= y_to; y++)
      image_set_pixel(image, x, y, color);
}

void image_save(IMAGE* image, char *filename)
{
  FILE* file = fopen(filename, "w");

  if(file < 0)
    fatal("Can't open file");

  //Write image headers
  fprintf(file, "P3\n");
  fprintf(file, "%lu %lu\n255\n", image->width, image->height);

  //Fill the image with the buffer values
  for(int i = 0; i < image->buf_len; i++)
    fprintf(file, "%d %d %d\n", image->buf[i], image->buf[i], image->buf[i]);
  
  fclose(file);
}

#endif