#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main()
{
    float x = 1.0f;

    /*
       uint32_t is used because a standard IEEE 754 float
       is expected to occupy 32 bits.

       32 bits = 1 Sign bit + 8 Exponent bits + 23 Mantissa bits
    */
    uint32_t bits;

    /*
       We use memcpy to copy the raw bits of the float
       into an unsigned integer.

       This lets us examine the actual bit representation
       without changing the value of x.
    */
    memcpy(&bits, &x, sizeof(x));

    printf("IEEE 754 representation of %f\n\n", x);

    /*
       Print all 32 bits.

       i starts at 31 because the leftmost bit is bit 31.
       i decreases until bit 0.
    */
    printf("Bits: ");

    for (int i = 31; i >= 0; i--)
    {
        /*
           (bits >> i) moves the required bit to position 0.

           & 1 extracts that single bit.
        */
        printf("%d", (bits >> i) & 1);

        /*
           Add a space after the Sign bit
           and after the 8 Exponent bits.

           This makes the output:

           Sign Exponent Mantissa
        */
        if (i == 31 || i == 23)
        {
            printf(" ");
        }
    }

    printf("\n\n");

    /*
       Extract the Sign bit.

       Bit 31 is the Sign bit in IEEE 754.
    */
    printf("Sign     : %u\n",
           (bits >> 31) & 1);

    /*
       Extract the Exponent.

       IEEE 754 float has 8 exponent bits:
       bits 30 to 23.

       0xFF = 11111111
       So & 0xFF keeps only those 8 bits.
    */
    printf("Exponent : %u\n",
           (bits >> 23) & 0xFF);

    /*
       Extract the Mantissa.

       IEEE 754 float has 23 mantissa bits:
       bits 22 to 0.

       0x7FFFFF = 23 ones in binary.
       Therefore, & 0x7FFFFF keeps only the mantissa.
    */
    printf("Mantissa : %u\n",
           bits & 0x7FFFFF);

    /*
       For IEEE 754, 1.0 should have:

       Sign     = 0
       Exponent = 127
       Mantissa = 0

       Binary representation:

       0 01111111 00000000000000000000000
    */

    if (((bits >> 31) & 1) == 0 &&
        ((bits >> 23) & 0xFF) == 127 &&
        (bits & 0x7FFFFF) == 0)
    {
        printf("\nfloat uses IEEE 754 representation\n");
    }
    else
    {
        printf("\nfloat does NOT use the expected IEEE 754 representation\n");
    }

    return 0;
}

