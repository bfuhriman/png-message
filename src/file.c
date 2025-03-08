#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include "../hdr/utils.h"

/* Reads image file into memory and prepares it for encoding. */
Image read(char *filename) {
    Image img;
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening %s\n", filename);
        exit(1);
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png) {
        printf("Error creating png read structure\n");
        fclose(file);
        exit(1);
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        printf("Error creating png info structure\n");
        png_destroy_read_struct(&png, NULL, NULL);
        fclose(file);
        exit(1);
    }

    if(setjmp(png_jmpbuf(png))) {
        printf("Error during png read setup\n");
        png_destroy_read_struct(&png, &info, NULL);
        fclose(file);
        exit(1);
    }

    png_init_io(png, file);
    png_read_info(png, info);

    img.width = png_get_image_width(png, info);
    img.height = png_get_image_height(png, info);

    png_set_strip_16(png);
    png_set_palette_to_rgb(png);
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    png_set_gray_to_rgb(png);
    png_read_update_info(png, info);

    img.rows = malloc(sizeof(png_bytep) * img.height);
    for (int i = 0; i < img.height; i++) {
        img.rows[i] = malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, img.rows);
    fclose(file);
    png_destroy_read_struct(&png, &info, NULL);
    return img;
}

/* Saves the image to an output file. */
void save(Image img, char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening %s\n", filename);
        return;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        printf("Error creating png write structure\n");
        fclose(file);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        printf("Error creating png info structure\n");
        png_destroy_write_struct(&png, NULL);
        fclose(file);
        return;
    }

    if (setjmp(png_jmpbuf(png))) {
        printf("Error during png write setup\n");
        png_destroy_read_struct(&png, &info, NULL);
        fclose(file);
        return;
    }

    png_init_io(png, file);
    png_set_IHDR(png, info, img.width, img.height, 8,
                 PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);
    png_write_image(png, img.rows);
    png_write_end(png, NULL);

    for (int i = 0; i < img.height; i++) {
        free(img.rows[i]);
    }
    free(img.rows);
    fclose(file);
    png_destroy_write_struct(&png, &info);
}
