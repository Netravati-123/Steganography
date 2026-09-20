#include <stdio.h>
#include "encode.h"
#include "types.h"
#include<string.h>

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
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "rb");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "rb");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "wb");
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

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    
    //check argv[2] have ".bmp" as last 4 char
     //if not,print error msg,return e_failure

     int len;
     len=strlen(argv[2]);
     if(len<4||strcmp(argv[2]+len-4,".bmp")!=0)
     {
        printf("ERROR: Source image must be.bmp\n");
        return e_failure;
     }

      //encInfo ->src_image_fname=argv[2]
      encInfo->src_image_fname=argv[2];

      //encInfo ->secret_fname =argv[3]
      encInfo->secret_fname =argv[3];

     //check argv[4]==NULL
     //encInfo -> stego_image_fname= "output.bmp"
     if(argv[4]==NULL)
     {
        encInfo -> stego_image_fname= "output.bmp";
     }
     //validate argv[4] is ".bmp"
     //  if not,print error msg,return e_failure
    // encInfo ->stego_image_fname=argv[4]

     else
     {
        len=strlen(argv[4]);
        if(len<4||strcmp(argv[4]+len-4,".bmp")!=0)
        {
            printf("ERROR:Output file must be .bmp\n");
            return e_failure;
        }
        encInfo->stego_image_fname=argv[4];
     }
    
    //call open_files() == e_failure ,return e_failure ,return e_success
    if(open_files(encInfo)==e_failure)
    {
        return e_failure;
    }
    return e_success;
    
}

/*Status open_files(EncodeInfo *encInfo)
{
    // open encInfo -> src_image_fname file in read mode
    //if return value is NULL,print error,return e_failure
    //fptr_src_image=fopen()//store it in structure
    encInfo-> fptr_src_image=fopen(encInfo-> src_image_fname,"r");
    if(encInfo->fptr_src_image==NULL)
    {
        printf("ERROR:Unable to open source image\n");
        return e_failure;
    }
    //open encInfo -> secrete_file  in read mode
     //fptr_secret=fopen()
    //if return value is NULL,print error,return e_failure

    encInfo->fptr_secret=fopen(encInfo->secret_fname,"r");
    if(encInfo->fptr_secret==NULL)
    {
        printf("ERROR: Unable to open secret file\n");
        return e_failure;
    }

    // open encInfo -> stego_image_fname file in write mode
    //fptr_stego_image=fopen()
     //return e_success

    encInfo->fptr_stego_image=fopen=fopen(encInfo->stego_image_fname,"w");
    if(encInfo->fptr_stego_image==NULL)
    {
        printf("ERROR:Unable toopen output file\n");
        return e_failure;
    }
    return e_success;
}*/

Status do_encoding(EncodeInfo *encInfo)
{
    
    //call check_capacity(encInfo) ==e_failure
    //print error and return e_failure
    if(check_capacity(encInfo)==e_failure)
    {
        printf("ERROR:Insufficient image capacity\n");
        return e_failure;
    }

    //call copy_bmp_header(fptr_src_file,fptr_dest_file)==e_failure
    //print errormsg,return e_failure
    if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_failure)
    {
        printf("ERROR:Failed to copy BMP header\n");
        retrun e_failure;
    }

    //call encode_magic_string(MAGIc_STRING,encInfo)==e_failure
    //print error msg,return e_failure
    if(encode_magic_string(MAGIC_STRING,encInfo)==e_failure)
    {
        printf("ERROR:Failed to encode magic string\n");
        return e_failure;
    }

    //call encode_secret_file_extn_size(encInfo)==e_failure
    //print error msg, return e_failure
    if(encode_secret_file_extn_size(encInfo)==e_failure)
    {
        printf("ERROR:Failed to encode extension size\n");
        return e_failure;
    }


    //call encode_secret_file_extn(extn_secrete_file,encInfo) ==e_failure
    //print error msg, return e_failure
    if(encode_secret_file_extn(encInfo->extn_secret_file,encInfo)==e_failure)
    {
        printf("ERROR:Failed to encode extension\n");
        return e_failure;
    }


    //call encode_secret_file_size(size_secrete_file,encInfo) ==e_failure
    //print error msg, return e_failure
    if(encode_secret_file_size(encInfo->size_secret_file,encInfo)==e_failure)
    {
        printf("ERROR:Failed to encode secret file size\n");
        return e_failure;
    }

    //call encode_secret_file_data(encInfo)==e_failure    
    //print error msg, return e_failure
    if(encode_secret_file_data(encInfo)==e_failure)
    {
        printf("ERROR:Failed to encode secret data\n");
        return e_failure;
    }

    //call copy_remaining_img_data(fptr_src_file,fptr_dest_file) ==e_failure   
    //print error msg, return e_failure
    if(copy_remaining_img_data(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_failure)
    {
        printf("ERROR:Failed tocopy remaining image data\n");
        return e_failure;
    }
    return e_success;

}

Status check_capacity(EncodeInfo *encInfo)
{
    uint image_capacity;
    uint secret_file_size;
   
        //call get_image_size_for_bmp(encode -> fptr_src_image)
        //image_capacity=get_image_size()
        image_capacity=get_image_size_for_bmp(encInfo->fptr_src_image);
        encInfo->image_capacity=image_capacity;

        //call get_file_size(encode->fptr_secret)
        //size_secret_file=get_file_size()
        secret_file_size=get_file_size(encInfo->fptr_secret);
        encInfo->size_secret_file=secret_file_size;

        //check ((14+size_secret_file)*8)> image_capacity
        
        if((14+secret_file_size)*8>image_capacity)

        {
            //return e_failure
            return e_failure;
        }
        
    //return e_success
    return e_success;
    

}

unit get_file_size(FILE *fptr)
{
        //move the offset tolast position
        // return ftell()
        {
            fseek(fptr,0,SEEK_END);
            return ftell(fptr);
        }
        
        fseek(encInfo->fptr_secrt,0,SEEK_SET);//move fptr back to beginning of file
}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    //declare the buff[54]
    char buffer[54];
    
    //move the file pointers to the SEEK_SET
    fseek(fptr_src_image,0,SEEK_SET);
    
    //read 54 bytes from src file
    fread(buffer,54,1,fptr_src_image);
    //write 54 bytes to destfile
    fwrite(buffer,54,1,fptr_dest_image);
    // return e_success
    return e_success;
    
}

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    
        //declare a buff of 8 bytes
        char buffer[8];
        int i;
        //loop for 2 times(length of magic_string)
        for(i=0;magic_string[i]!='\0';i++)
        {
            //read 8 bytes from the src_file
            fread(buffer,8,1,encInfo->fptr_src_image);
            //encode_byte_to_lsb(magic_string[1],buff)
            encode_byte_to_lsb(magic_string[i],buffer);
            //write the encoded buff to otput_file
            fwrite(buffeer,8,1,encInfo->fptr_stego_image);
        }
        //return e_success
        return e_success;
}

Status encode_byte_to_lsb(char data, char *image_buffer)
{
    int i;
     //for(int i=7;i>=0;i--)
     for(int i=7;i>=0;i--)
     {
        //get the ith bit is or not
        if(data&(1<<i))
        {
              //if set,set the LSB of image_buffer[]
            image_buffer[7-i]=image_buffer[7-i]|1;
        }
        else
        {
             //if clear,clear the LSB of image_buffer[]
             image_buffer[7-i]=image_buffer[7-i]&~1;
        }
     }
     //return e_success
     return e_success;
    
}

status encode_secret_file_extn_size(EncodeInfo *encInfo)
{
    
    //char *dot= strchr(secret_file_name, '.')
     //declare a buff[32]
    char *dot;
    char buffer[32];
    dot=strrchr(encInfo->secret_fname,'.');
    //strcpy(extn_secret_file,dot);
    strcpy(encInfo->extn_secret_file,dot);

     //read 32 bytes from src_file into buffer
     fread(buffer,32,1,encInfo->fptr_src_image);

     //call encode_size_to_lsb(strlen(extn_secret_file),buffer)
     encode_size_to_lsb(strlen(encInfo->extn_secret_file),buffer);

     //write 32 byte of buff to output_file
     fwrite(buffer,32,1,encInfo->fptr_stego_image);

        //return e_success
    return e_success;
}


Status encode_size_to_lsb( int size, char *Image_buff)
{
    int i;
     //for(int i=31;i>=0;i--)
        for(i=31;i>=0;i--)
        {
            //get the ith bit is or not
            if(size&(1<<i))
            {
                //if set,set the LSB of image_buffer[]
                image_buffer[31-i]=image_buffer[31-i]|1;
            }
            else
            {
                //if clear,clear the LSB of image_buffer[]
                 image_buffer[31-i]=image_buffer[31-i]&~1;

            }
        }
      
    //return e_success
    return e_success;

}

Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
     //declare buff[8]
     char buffer[8];
     int i;
     //loop for extension length
     for(i=0;file_extn[i]!='\0';i++)
     {
         //Read 8 bytes from src_image
        fread(buffer,8,1,encInfo->fptr_src_image);
        //encode_byte_to_lsb(file_extn[],buff)
        encode_byte_to_lsb(file_extn[i],buffer);
        //write the 8 bytes of buff to output_file
        fwrite(buffer,8,1,encInfo->fptr_stego_image);
     }
     //return e_success
     return e_success;
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    
    //declare the buff[32]
    char buffer[32];
    //read 32 bytes fromsrc_image
    fread(buffer,32,1,encInfo->fptr_src_image);
    //call encode_size_to_lsb(file_size,buff)
    encode_size_to_lsb((int)file_size,buffer);
    //write  the 32 bytes of buff tooutput_file
    fwrite(buffer,32,1,encInfo->fptr_stego_image);
    //return e_success
    return e_success;
}


Status encode_secret_file_data(EncodeInfo *encInfo)
{
    //Declare buff[8],data
    char buffer[8];
    char data;
    
//loop till EOF of secret_file
//read 1 byte from secret_file
while(fread(&data,sizeof(char),1,encInfo->fptr_secret)==1)
{
    //read 8 bytes from src_file
    fread(buffer,8,1,encInfo->fptr_src_image);

    //encode_byte_to_lsb(data,buff)
    encode_byte_to_lsb(data,buffer);
    
    //write encoded bytes
    fwrite(buffer,8,1,encInfo->fptr_stego_image);
    
} 
    //return e_success
    return e_success;
}


Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    //declare charecter as data
    char data;
    
    //loop till EOF of src_file
     //read a char from src_file
    while(fread(&data,sizeof(char),1,fptr_src)==1)
   {
    //write the data to dest_file
    fwrite(&data,sizeof(char),1,fptr_dest);
   }
    
    //return e_success
    return e_success;

}