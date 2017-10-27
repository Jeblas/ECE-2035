/*    When Harry Met Sally

This program finds the total number of years in which Harry and Sally
live in the same city at the same time.

<9/16/2016>	               <John Blasco>   */

#include <stdio.h>
#include <stdlib.h>

/* City IDs used in timelines. */
enum Cities{ London, Boston, Paris, Atlanta, Miami,
             Tokyo, Metz, Seoul, Toronto, Austin };

int main(int argc, char *argv[]) {
   int	HarryTimeline[10];
   int	SallyTimeline[10];
   int	NumNums, SumYears=0;
   int  Load_Mem(char *, int *, int *);
   int 	tempYear;

   /* You may add more local variables here if needed. */

   if (argc != 2) {
     printf("usage: ./HW2-1 valuefile\n");
     exit(1);
   }
   NumNums = Load_Mem(argv[1], HarryTimeline, SallyTimeline);
   if (NumNums != 20) {
     printf("valuefiles must contain 20 entries\n");
     exit(1);
   }

   /* Your program goes here. */

   // loop through all cities in Harry
   for(int i =1; i < 10; i= i+2)
   {
   	// loop through cities in Sally
   	for(int j = 1; j<10; j = j+2)
   	{
   		//check if cities are the same
   		if(HarryTimeline[i] == SallyTimeline[j])
   		{
   			// filter for when HarryTimeline[i] is the last city
   			if(i == 9)
   			{
   				// filter for when SallyTimeline[j] is the last city
   				if(j == 9)
   				{
					// check if years overlap
   					if( !(HarryTimeline[i-1]>2016 || 2016 < SallyTimeline[j-1]) )
   					{
   						tempYear = HarryTimeline[i-1];
   						while(tempYear<2016)
   						{
            // if tempYear is beteen a sally's last move and 2016 add 1 to sum
   							if(tempYear < 2016 && tempYear >= SallyTimeline[j-1])
   							{
   								SumYears++;

   							}
   							tempYear++;
   						}

   					}

   				}
   				else
   				{
   					if( !(HarryTimeline[i-1]>SallyTimeline[j+1] || 2016 < SallyTimeline[j-1]) )
   					{
   						tempYear = HarryTimeline[i-1];
   						while(tempYear<2016)
   						{
                // see if tempYear is in between Sally [i+-1] if yes add 1 to sum
   							if(tempYear < SallyTimeline[j+1] && tempYear >= SallyTimeline[j-1])
   							{
   								SumYears++;

   							}
   							tempYear++;
   						}

   					}

   				}


   			}
   			else
   			{
                                // check if years overlap
   				if( !(HarryTimeline[i-1]>SallyTimeline[j+1] || HarryTimeline[i+1] < SallyTimeline[j-1]) )
   				{
   					tempYear = HarryTimeline[i-1];
   					while(tempYear<HarryTimeline[i+1])
   					{
          // see if tempYear is in between Sally [i+-1] if yes add 1 to sum
   						if(tempYear < SallyTimeline[j+1] && tempYear >= SallyTimeline[j-1])
   						{
   							SumYears++;

   						}
   						tempYear++;
   					}

   				}

   			}
   		}



   	}



   }













   printf("Total number of years in which both lived in the same city: %d\n", SumYears);
   exit(0);
}

/* This subroutine loads in up to 20 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray1[], int IntArray2[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
     printf("%s could not be opened; check the filename\n", InputFileName);
     return 0;
   } else {
     for (N=0; N < 20; N++) {
       NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
       if (NumVals == 2)
	 if (N < 10)
	   IntArray1[N] = Value;
	 else
	   IntArray2[N-10] = Value;
       else
	 break;
     }
     fclose(FP);
     return N;
   }
}
