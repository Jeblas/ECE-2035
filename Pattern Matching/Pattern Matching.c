/*      I c o n   M a t c h
Student Name: John Blasco
Date: 9/30/2016

ECE 2035 Project 1-1

This program loads 12 icons (each is a 12x12 array of pixels) into a
linear array: 8 are reference icons, followed by 4 candidate icons.
Exactly one of the 4 candidates matches exactly one of the 8 reference icons.

Add code to find which of the eight reference icons matches one of
the candidate icons.
*/

#include <stdio.h>
#include <stdlib.h>

#define IconArraySize 12 * 12 * 12

int main(int argc, char *argv[]) {
  int	Icons[IconArraySize];
  int	Length, Match=0;
  int  Load_Mem(char *, int *);

  if (argc != 2) {
    printf("usage: P1-1 valuefile\n");
    exit(1);
  }
  Length = Load_Mem(argv[1], Icons);
  if (Length != IconArraySize) {
     printf("valuefile does not contain valid data.\n");
     exit(1);
  }

  /* Your icon matching code goes here */
  //loop through each of the 4 candidate icons
  for(int candidate = 0; candidate < 4; candidate++)
  {
  	int startingIndexCandidate = 1152 + (candidate * 144);
  	int indexOfNonBlack;

  	//Search diagonally through the candidate icon for a non black square
  	// 7 diagonal scans will find a non black value
  	for (int numDiagonalsScans = 0; numDiagonalsScans < 7; numDiagonalsScans++)
  	{
  		//upper half diagonal scans  //could make upper scans alternate with lower
  		if(numDiagonalsScans < 4)
  		{
  			//initalize the index search value to the starting pos of the diagonal
  			int currentSearchValue = startingIndexCandidate + 2*numDiagonalsScans;
  			int endSearchValue = startingIndexCandidate + (11- (2*numDiagonalsScans))*13;

  			//loop through each block of the diagonal
  			while(currentSearchValue <= endSearchValue)
  			{
  				if(Icons[currentSearchValue] != 0)
  				{
  					indexOfNonBlack = currentSearchValue;
  					goto p2;


  				}
  				currentSearchValue += 13;
  			}

  		}
  		else
  		{
  			//initalize the index search value to the starting pos of the diagonal
  			int currentSearchValue = startingIndexCandidate + 143 - 2*(numDiagonalsScans - 3);
  			int endSearchValue = startingIndexCandidate + 143-(2*(numDiagonalsScans-3)) - (11- (2*(numDiagonalsScans-3)))*13;

  			//loop through each block of the diagonal
  			while(currentSearchValue >= endSearchValue)
  			{
  				if(Icons[currentSearchValue] != 0)
  				{
  					indexOfNonBlack = currentSearchValue;
  					goto p2;


  				}
  				currentSearchValue -= 13;
  			}

  		}
  	}
  	// have index of non black at this point
  	//get the relative location of the non black cell
 	p2: ;	
	int indexCompareOffset = indexOfNonBlack - startingIndexCandidate;

  	//check if the relative location of the non black cell is the same value for a non reference icon
  	for( int referenceIcon = 0; referenceIcon < 8; referenceIcon++)
  	{

  		int matchCompare;

  		if(Icons[(referenceIcon * 144) + indexCompareOffset] == Icons[indexOfNonBlack])
  		{
  			//check to see if other cells of the grids are the same
  			for (int numDiagonalsScans = 0; numDiagonalsScans < 12; numDiagonalsScans++)
  			{
  				//upper half diagonal compare
  				if(numDiagonalsScans < 6)
  				{
  					//initalize the index search value to the starting pos of the diagonal
  					int currentSearchValue = startingIndexCandidate + 2*numDiagonalsScans;
  					int endSearchValue = startingIndexCandidate + (11- (2*numDiagonalsScans))*13;
  					int iconSearchValue = (referenceIcon * 144) + 2*numDiagonalsScans;

  					//loop through each block of the diagonal
  					while(currentSearchValue <= endSearchValue)
  					{

  						// if not equal at  got to next reference icon
  						if(Icons[currentSearchValue] != Icons[iconSearchValue])
  						{
  							//break out of scan if icons are not equal
  							matchCompare = 1;
  							goto p3;
  						}
						iconSearchValue += 13;
  						currentSearchValue += 13;
						matchCompare = 0;
  					}

  				}
  				else
  				{
  					// comnpare left diagonals
  					//initalize the index search value to the starting pos of the diagonal
  					int currentSearchValue = startingIndexCandidate + 143 - 2*(numDiagonalsScans - 3);
  					int endSearchValue = startingIndexCandidate + 143-(2*(numDiagonalsScans-3)) - (11- (2*(numDiagonalsScans-3)))*13;
  					int iconSearchValue = (referenceIcon * 144) + + 143 - 2*(numDiagonalsScans - 3);

  					//loop through each block of the diagonal
  					while(currentSearchValue >= endSearchValue)
  					{
  						if(Icons[currentSearchValue] != Icons[iconSearchValue])
  						{
  							matchCompare++;
  							goto p3;
  						}
						iconSearchValue -= 13;
  						currentSearchValue -= 13;
						matchCompare = 0;
  					}
  				}
  			}
  		}

  p3:		if(matchCompare == 0)
  		{
  			Match = referenceIcon;
  			goto p4;
  		}
  	}
  }

 p4:  printf("The matching reference icon is %d\n", Match);
 exit(0);
}

/* This routine loads in up to IconArraySize newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < IconArraySize; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
         if (NumVals == 2)
            IntArray[N] = Value;
         else
            break;
      }
      fclose(FP);
      return N;
   }
}
