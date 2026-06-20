#include "io.h"
#include "LIBFEMTORV32/femtorv32.h"

int main()
{
    unsigned int write_val = 0x12345678;

    IO_OUT(IO_GPIO, write_val);

    unsigned int read_val = IO_IN(IO_GPIO);

    printf("GPIO Write = %d\n", write_val);
    printf("GPIO Read  = %d\n", read_val);

    if(write_val == read_val)
        printf("GPIO TEST PASSED\n");
    else
        printf("GPIO TEST FAILED\n");

    asm("ecall");
    
	return 0;
}
