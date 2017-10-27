#include <stdio.h>
#include <stdlib.h>

/*
 Student Name: John Blasco
 Date: 9/9/2016

ECE 2035 Homework 1-2

This is the only file that should be modified for the C implementation
of Homework 1.

This program determines whether the value of the global variable x
(expressed in hexadecimal notation) is a 16-Harshad number and if so,
whether the factors involved are mirrors of each other.  That is, if x
= p * q, where p = sum of hexadecimal digits of x and q is the reverse
of p (same digits in reverse order).  For example, 6A5 = 15*51 in base
16.

The program prints a statement indicating which of 3 cases is true:
1) x is not a 16-Harshad number,
2) x is a 16-Harshad number without mirror factors (and gives the factors), or
3) x is a 16-Harshad number with mirror factors (and gives the factors).

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

*/

unsigned x = 0x6A5;


int main() {

   //create variables
   unsigned temp1 = x;
   unsigned p=0x0;
   unsigned q=0x0;
   unsigned mirroredP = 0x0;
   unsigned rightMostHexDig;
   unsigned tempP;



/* get the sum of x's digits */
while(temp1)
{
        //add the left most hex value of temp1 to P
	p = p + (temp1 % 16);
        // shift temp1 by one hex digit
	temp1 >>= 4;

}


/* check if p evenly divides into x*/
if (x % p)
{
	printf("%#x is not a 16-Harshad number.\n", x);

}
else
{
        //get q
        q = x/p;

        /* find the mirror of q */
        tempP = p;
        while(tempP)
        {
                // mask the last 4 bits of tempP and or them to mirroredP
                mirroredP |= 0x000f&tempP;
                //shift temP to the right and mirroredP to the left
                tempP >>= 4;
                mirroredP <<= 4;

        }

	//shift mirroredP to the right to remove trailing 0
	mirroredP >>= 4;


	/*determine if q and p are mirrored*/
	if (mirroredP == q)
	{
		printf("%#x is a 16-Harshad number, w/ mirror factors: %#x * %#x\n", x, p, q );
	}
	else
	{
		printf("%#x is a 16-Harshad number, w/out mirror factors: %#x * %#x\n", x, p, q );
	}
}
        return 0;
}
