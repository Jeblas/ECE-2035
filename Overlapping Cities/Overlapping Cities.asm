#     When Harry Met Sally
#
#
# This program finds the total number of years during which Harry and Sally
# lived in the same city at the same time.
#
#  required output register usage:
#  $2: total number of years in same city at same time
#
# <9/16/2016>					<John Blasco>

.data
Harry:  .alloc  10               # allocate static space for 5 moves
Sally:  .alloc  10               # allocate static space for 5 moves

.text
WhenMet:	addi  $1, $0, Harry     # set memory base
        	swi     586             # create timelines and store them

		addi $2, $0, 0		#initialize SumYears
		addi $1, $0, 4		#initialize i


Loop1:		slti $3, $1, 41
		beq $3, $0, Exit
		addi $3, $0, 4		# initialize j
Loop2:		slti $4, $3, 41		# j<10
		beq $4, $0, Exit2
		lw $5, Harry($1)        # Harry[i]
		lw $6, Sally($3)        # Sally[j]
		bne $5, $6, Exit3       # Harry[i] == sally[j]?

		addi $7, $1, -4		# i-1
		addi $8, $1, 4		# i+1
		addi $9, $3, 4		# j+1
		addi $10, $3, -4	# j-1
		lw $7, Harry($7)	# Harry[i-1]
		lw $8, Harry($8)	# Harry[i+1]
		lw $9, Sally($9)	# Sally[j+1]
		lw $10, Sally($10) 	# Sally[j-1]

		bne $9, $0, Jump      #check to see if value of Sally[j+1] == 0
		addi $9, $0, 2016     # if S[j]

		# if i == 4 and Harry[i-1] > Harry[i+1]
Jump:		addi $13, $0, 4		# move outside of loops
		beq $1, $13, Jump2

		slt $13, $8, $7
		beq $0, $13, Jump2
		addi $8, $0, 2016     # set end year for harry to 2016

                # check if years overlap
Jump2:		slt $11, $9, $7
		bne $11, $0, Exit3
		slt $11, $8, $10
		bne $11, $0, Exit3

                # while loop to see if tempYear < Harry[i+1]
Loop3:		slt $11, $7, $8
		beq $11, $0, Exit3

                # if tempYear is beteen sally's years add 1 to temp and sum
		slt $11, $7, $9
		beq $11, $0, Exit4
		slt $11, $7, $10
		bne $11, $0, Exit4
		addi $2, $2, 1		# SumYears++

Exit4:		addi $7, $7, 1          # tempYear++
		J Loop3
Exit3:		addi $3, $3, 8          # j++
		J Loop2
Exit2:		addi $1, $1, 8          # i++
		J Loop1

		#addi    $2, $0, 5	# guess 5 (TEMP: replace this)
Exit:		swi     590		# give answer
                jr      $31             # return to caller
