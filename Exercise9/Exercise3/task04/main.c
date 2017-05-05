
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <stdbool.h>
#include <unistd.h>

#include <math.h>
/**
 * @brief Contains color data for a single pixel.
 */
 struct pixel_rgb_t {
   uint8_t r; /*!< Holds the red-value as an 8-bit unsigned integer. */
   uint8_t g; /*!< Holds the green-value as an 8-bit unsigned integer. */
   uint8_t b; /*!< Holds the blue-value as an 8-bit unsigned integer. */
 };

/**
 * @brief Defines an image size.
 */
struct image_size_t {
    unsigned int width;
    unsigned int height;
};

typedef struct pixel_rgb_t pixel_rgb_t;
typedef struct image_size_t image_size_t;


/**
 * @brief Scales an image by applying a billinear interpolation filter.
 *
 * @param in pixel data of input image
 * @param out  pixel data of output image. Has to be pre allocated.
 * @param src_sz the size of the input image
 * @param trgt_sz the desired output size.
 */
void resize_image(pixel_rgb_t *in, pixel_rgb_t *out, image_size_t src_sz, image_size_t trgt_sz) {
  // Calculates dx, dy as described.
  double dx = (double)trgt_sz.width / (double)src_sz.width;
  double dy = (double)trgt_sz.height / (double)src_sz.height;

  // counts through all positions of the output.
  for (int y = 0; y < trgt_sz.height; y++){
    for (int x = 0; x < trgt_sz.width; x++){

        // Projects the outputposition to an input position.
        double x1 = x / dx;
        double y1 = y / dy;

        // Calculates the four nearest pixels.
        pixel_rgb_t p00 = in[ (int)(floor(x1) + floor(y1) * src_sz.width) ];
        pixel_rgb_t p01 = in[ (int)(ceil(x1) + floor(y1) * src_sz.width) ];
        pixel_rgb_t p10 = in[ (int)(floor(x1) + ceil(y1) * src_sz.width) ];
        pixel_rgb_t p11 = in[ (int)(ceil(x1) + ceil(y1) * src_sz.width) ];

        // Calculates the output channels as described.
        // Somewhere here is a bug that destroys the colours for dx, dy > 1.
        // I really don't know why this happens.
        // It seems that it happens espacially for dark colours which could hint
        // for some kind of unwanted negative values.
        pixel_rgb_t pxy;
        unsigned int q0r = (1.0 - dx) * p00.r + dx * p10.r;
        unsigned int q1r = (1.0 - dx) * p01.r + dx * p11.r;
        unsigned int q0g = (1.0 - dx) * p00.g + dx * p10.g;
        unsigned int q1g = (1.0 - dx) * p01.g + dx * p11.g;
        unsigned int q0b = (1.0 - dx) * p00.b + dx * p10.b;
        unsigned int q1b = (1.0 - dx) * p01.b + dx * p11.b;
        pxy.r = (1.0 - dy) * q0r + dy * q1r;
        pxy.g = (1.0 - dy) * q0g + dy * q1g;
        pxy.b = (1.0 - dy) * q0b + dy * q1b;

        // Writes the output pixel to the correct position of the output array.
        out[x + y * trgt_sz.width] = pxy;
        }
      }
}
/**
 * @brief Loads pixels from a JPEG file into memory.
 * @param name the path of the file to read
 * @param img pointer to pixel data. Will be allocated.
 * @param size the size of the image. Will be set by this function
 */
void load_jpeg(const char *name, pixel_rgb_t **img, image_size_t *const size) {
    uint8_t r, g, b;
    int width, height;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *infile;
    JSAMPARRAY pJpegBuffer;
    int row_stride;
    if ((infile = fopen(name, "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", name);
        exit(1);
    }
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);
    width = cinfo.output_width;
    height = cinfo.output_height;

    *img = calloc((size_t) width * height, sizeof(pixel_rgb_t));
    pixel_rgb_t *current_pixel = *img;
    if (!*img) {
        printf("NO MEM FOR JPEG CONVERT!\n");
        exit(1);
    }

    row_stride = width * cinfo.output_components;
    pJpegBuffer = (*cinfo.mem->alloc_sarray)
            ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
        for (int x = 0; x < width; x++) {
            r = pJpegBuffer[0][cinfo.output_components * x];
            if (cinfo.output_components > 2) {
                g = pJpegBuffer[0][cinfo.output_components * x + 1];
                b = pJpegBuffer[0][cinfo.output_components * x + 2];
            } else {
                g = r;
                b = r;
            }

            //r, g and b contain the color information for the channels read, green and blue
            // current_pixel is your current pixel to fill with info from the jpeg.

            // Below the channel data stored in r,g,b is copied to the corresponding
            // values of the struct pixel_rgb_t.
            current_pixel->r = r;
            current_pixel->g = g;
            current_pixel->b = b;

            current_pixel++;
        }
    }
    fclose(infile);
    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    size->height = (uint32_t) height;
    size->width = (uint32_t) width;
}

/**
 * @brief Writes pixel data to a JPEG file with 80% quality and defined image size.
 * @param pixel_data the pixel to compress
 * @param size the size of this image
 * @param filename paht to write this file to.
 */
void save_jpeg(const pixel_rgb_t *pixel_data, const image_size_t size, const char *filename) {
    FILE *outfile = fopen(filename, "wb");

    if (!outfile) {
        fprintf(stderr, "can't open %s\n for write", filename);
        exit(1);
    }

    struct jpeg_compress_struct jpeg_info;
    struct jpeg_error_mgr jpeg_error;

    jpeg_info.err = jpeg_std_error(&jpeg_error);
    jpeg_create_compress(&jpeg_info);
    jpeg_stdio_dest(&jpeg_info, outfile);

    jpeg_info.image_width = size.width;
    jpeg_info.image_height = size.height;
    jpeg_info.input_components = 3;
    jpeg_info.in_color_space = JCS_RGB;

    jpeg_set_defaults(&jpeg_info);
    jpeg_set_quality(&jpeg_info, 80, true);
    jpeg_start_compress(&jpeg_info, true);

    JSAMPROW row_pointer;

    pixel_rgb_t p;

    unsigned char *row = malloc(sizeof(unsigned char) * 3 * size.width);

    while (jpeg_info.next_scanline < jpeg_info.image_height) {

        //current is your current scanline to fill with information.
        unsigned char *current = row;

        //this is the index of the beginning of the current row in your source array.
        unsigned int current_row = jpeg_info.next_scanline * size.width;


        // The Loop below counts through the current row of the input pixel_data
        // and writes it to the corresponding position of the output row.
        for (int i = 0; i < size.width; i++) {
          (*current) = pixel_data[current_row + i].r;
          current++;
          (*current) = pixel_data[current_row + i].g;
          current++;
          (*current) = pixel_data[current_row + i].b;
          current++;
        }

        row_pointer = (JSAMPROW) row;
        jpeg_write_scanlines(&jpeg_info, &row_pointer, true);
    }

    free(row);

    jpeg_finish_compress(&jpeg_info);
}

int main(int argc, char **argv) {
  const char * inputName = NULL;
  const char * outputName = NULL;
  int width = -1;
  int height = -1;
  int c;
  // Gets arguments specified by -i, -o, -w and -h and writes them into corresponding
  // variables inputName, outputName, width and height.
  while ((c = getopt (argc, argv, "i:o:w:h:")) != -1)
  switch (c)
    {
    case 'i':
      inputName = optarg;
      break;
    case 'o':
      outputName = optarg;
      break;
    case 'w':
      // For -w all arguments which can't be detected by sscanf as an unsigned
      // integer are invalid. Also checks if the other value was already give.
      if( (height >= 0) || (sscanf(optarg, "%u", &width) != 1) ){
        printf("invalid argument!\n");
        return 1;
      }
      break;
    case 'h':
      // For -h all arguments which can't be detected by sscanf as an unsigned
      // integer are invalid.  Also checks if the other value was already give.
      if( (width >= 0) || (sscanf(optarg, "%u", &height) != 1) ){
        printf("invalid arguments!\n");
        return 1;
      }
      break;
    default:
      abort ();
    }
    // Checks if arguments for -w and -h were given. And if they were bigger than  0.
    if (width == 0 || height == 0) {
      printf("invalid arguments!\n");
      return 1;
    }

    // Initializes the required variables then loads and saves the jpg
    pixel_rgb_t pixel;
    pixel_rgb_t * pixel_data = &pixel;
    pixel_rgb_t ** img = &pixel_data;
    image_size_t size;
    image_size_t * size_pointer = &size;
    image_size_t * newSize_pointer;
    load_jpeg(inputName, img, size_pointer );

    // Here the missing value is calculated.
    if( width >= 0)
      height = ( (double)width / size.width) * size.height;
    else
      width = ( (double)height / size.height) * size.width;
    printf("arguments: i= %s o= %s w= %u h= %u\n", inputName, outputName, width, height);

    pixel_rgb_t out[width * height];
    image_size_t newSize;
    newSize.width = width;
    newSize.height = height;

    resize_image(pixel_data, out, size, newSize);

    save_jpeg(&out[0], newSize, outputName);
    return 0;
}
