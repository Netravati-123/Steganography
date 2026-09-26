#include <stdio.h>
#include "encode.h"
#include "types.h"
#include "decode.h"

int main(int argc, char *argv[])
{
    EncodeInfo encInfo;
    DecodeInfo decInfo;

    if(argc < 2)
    {
        printf("Invalid arguments\n");
        return 0;
    }

    if(check_operation_type(argv[1][1]) == e_encode)
    {
        if(argc < 4)
        {
            printf("Use:./a.out -e source.bmp secret.txt[output.bmp]\n");
            return 0;
        }

        //call check_operation_type(argv[1][1])==e_encode
        //call read_and_validate_encode_args(argv,&encInfo)==e_sucess
        //call do_encoding(&encInfo)==e_success
        //print "Encoding is success"

        if(read_and_validate_encode_args(argv,&encInfo)==e_success)
        {
            if(do_encoding(&encInfo)==e_success)
            {
                printf("Encoding completed successfully\n");
            }
            else
            {
                printf("Encoding failed\n");
            }
        }
    }

    else if(check_operation_type(argv[1][1]) == e_decode)
    {
        if(argc < 3)
        {
            printf("Usage: ./a.out -d output.bmp output.txt\n");
            return 0;
        }

        if(read_and_validate_decode_args(argv, &decInfo) == e_success)
        {
            if(do_decoding(&decInfo) == e_success)
            {
                printf("Decoding completed successfully\n");
            }
            else
            {
                printf("Decoding failed\n");
            }
        }
        else
        {
            printf("Invalid decoding arguments\n");
        }
    }

    else
    {
        printf("Unsupported operation\n");
    }

    return 0;
}


OperationType check_operation_type(char opt)
{
    //check optis 'e' return e_encode;
    //check opt is 'd' return e_decode;
    //else return e_unsupported;

    if(opt=='e')
    {
        return e_encode;
    }
    else if(opt=='d')
    {
        return e_decode;
    }
    else
    {
        return e_unsupported;
    }
}