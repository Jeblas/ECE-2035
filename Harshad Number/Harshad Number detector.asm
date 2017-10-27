# HW1-3
# Student Name: John Blasco
# Date:	9/7/2016
#
# This program determines whether the value x (at XLoc) is a 16-Harshad number
# and if so, whether the factors involved are mirrors of each other.
# That is, if x = p * q, where p = sum of hexadecimal digits of x and q is the
# reverse of p (same digits in reverse order).
# For example, 6A5 = 15*51 in base 16.
#
# If x is a 16-Harshad number and its factors are mirrors, 1 will be written
# to memory location labeled Result, otherwise 0 is written there.

.data
XLoc:     .word  0x6A5
Result:   .alloc 1

.text

		lw $1, XLoc($0)
		addi $2, $0, 0		# initialize sum value
		addiu $3, $1, 0		# copy x
		addi $4, $0, 16		# store 16 to divide with

					# get sum
Loop1:		div $3, $4		# divide X by 16
		mfhi $5			# get the remainder x/16
		add $2, $2, $5		# sum += remainder
		srl $3, $3, 4		# shift copy of x 4 bits
		bne $3, $0, Loop1	# if copy of x != 0 go to loop

		div $1, $2		# divide X by P (sum of X digits)
		mfhi $4			# get remainder X/P
		bne $4, $0, neither	# check is P is a factor of X
		mflo $3			# get Q = X/P
		addi $6, $0, 0		# initialize mirror of P
		addi $4, $2, 0		# copy P to $4

Loop2: 		andi $5, $4, 0x000f	# get mask the last 4 bits
		or $6, $6, $5		# or the mask to the get a mirror of P
		srl $4, $4, 4		# shift the  copy of P to the right
		beq $4, $0, wasd  	# prevent a trailing 0 in the mirror of P
		sll $6, $6, 4		# shift the mirror of P to the left
wasd:		bne $4, $0, Loop2	# if copy of P is not zero loop

		beq $3, $6, Yes 	# see if the mirror of P is equal to Q
neither:	sw $0, Result($0)	# store 0 in Result
		j end
Yes:    	addi $4, $0, 1		# add one to a register
		sw $4, Result($0)	# store 1 into result
end:  		jr $31   		# return to OS
