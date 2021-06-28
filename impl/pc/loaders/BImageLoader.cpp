#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <Bizarre.h>


void ReadDataFromInputStream(png_structp png_ptr, png_bytep outBytes, png_size_t byteCountToRead)
{
   png_voidp io_ptr = png_get_io_ptr(png_ptr);
   if(io_ptr == NULL)
      return;   // add custom error handling here

    BFile * file = (BFile*)io_ptr;
    M_fread( (char*)outBytes, sizeof(char), byteCountToRead, file );
    file->seek( file->tell(), byteCountToRead );
    
}  // end ReadDataFromInputStream()


bool B_loadImage(const char * filename, void * data){
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_bytep *row_pointers = NULL;

    
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png) return false;

    png_infop info = png_create_info_struct(png);
    if(!info) return false;

   
    if(setjmp(png_jmpbuf(png))) return false;


    BFile * file = M_fopen(filename, "rb");
    png_set_read_fn(png, file, ReadDataFromInputStream);
    png_read_info(png, info);
    

    width      = png_get_image_width(png, info);
    height     = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth  = png_get_bit_depth(png, info);

    // Read any color_type into 8bit depth, RGBA format.
    // See http://www.libpng.org/pub/png/libpng-manual.txt
     
    if(bit_depth == 16)
        png_set_strip_16(png);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if(color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if(color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    if (row_pointers) return false;

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for(int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }

    
    
    png_read_image(png, row_pointers);
    BImage * image = (BImage *)data;
    //std::cout << "x7 " << std::endl;
    image->create(M_UBYTE, (unsigned int)width, (unsigned int)height, (unsigned int)4u);
    //memcpy(image->getData(), &row_pointers, width*height ); // TODO: No funciona
    
   
   
    for(int y = 0; y < height; y++) {
    png_bytep row = row_pointers[y];
    for(int x = 0; x < width; x++) {
      png_bytep px = &(row[x * 4]);

      char color[] = { px[0], px[1], px[2], px[3] };
      image->writePixel( x, y, &color );
      // Do something awesome for each pixel here...
      //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
    }
  }


    M_fclose(file);

    png_destroy_read_struct(&png, &info, NULL);

    return true;
}