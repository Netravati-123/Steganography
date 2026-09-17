#include <stdio.h>
#include "encode.h"
#include "types.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo);
{
    /*
    check argv[2] have ".bmp" as last 4 char
     *if not,print error msg,return e_failure
      encInfo ->src_image_fname==argv[2]

      encInfo ->secret_fname =argv[3]

     check argv[4]==NULL
     *encInfo -> stego_image_fname= "output.bmp"
    ->else
        *validate argv[4] is ".bmp"
          *  if not,print error msg,return e_failure
          *encInfo ->stego_image_fname=argv[4]

    call open_files() == e_failure
        return e_failure
    return e_success
    */
}

Status open_files(EncodeInfo *encInfo);
{
    /*
     open encInfo -> src_image_fname file in read mode
        *if return value is NULL,print error,return e_failure
        fptr_src_image=fopen()//store it in structure

        open encInfo -> secrete_file  in read mode
        *if return value is NULL,print error,return e_failure
        fptr_secret=fopen()

        open encInfo -> stego_image_fname file in write mode
        fptr_stego_image=fopen()

        return e_success


    */

}

Status do_encoding(EncodeInfo *encInfo);
{
    /*
    //call check_capacity(encInfo) ==e_failure
    print error and return e_failure

    //call copy_bmp_header(fptr_src_file,fptr_dest_file)==e_failure
    print errormsg,return e_failure

    //call encode_magic_string(MAGIc_STRING,encInfo)==e_failure
    print error msg,return e_failure

    //call encode 

    */
}

Status check_capacity(EncodeInfo *encInfo);
{
    /*
        call get_image_size_for_bmp(encode -> fptr_src_image)
        image_capacity=get_image_size()
        call get_file_size(encode->fptr_secret)
        size_secret_file=get_file_size()

        ->check ((14+size_secret_file)*8)> image_capacity
        return e_failure
    return e_sucess
    */

}

unit get_file_size(FILE *fptr)
{
    /*
        ->move the offset tolast position
        -. rtwurn ftell()
    */

}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image);
{
    /*
    ->move the file pointers to the SEEK_SET
    ->declare the buff[54]
    ->read 54 bytes from src file
    ->write 54 bytes to destfile

    -> return e_success
    */
}

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo);
{
    /*
        declare a buff of 8 bytes
        ->loop for 2 times(length of magic_string)
        read 8 bytes from the src_file
        encode_byte_to_lsb(magic_string[1],buff)
        write the encoded buff tootput_file
        ->return e_success
    */
}

Status encode_byte_to_lsb(char data, char *image_buffer);
{
    /*
        ->for(int i=7;i>=0;i--)
        {
        ->get the ith bit is or not
        -> if set,set the LSB of image_buffer[]
        ->if clear,clear the LSB of image_buffer[]
        }
        ->

    */
}

status encode_secret_file_extn_size(EncodeInfo *encInfo)
{
    /*
    ->char *dot= strchr(secret_file_name, '.')
    strcpy(extn_secret_file,dot);


        ->declare a buff[32]
        ->read 32 bytes from src_file into buffer
        ->call encode_size_to_lsb(strlen(extn_secret_file),buffer)
    */
}


Status encode_size_to_lsb( int size, char *Image_buff);



