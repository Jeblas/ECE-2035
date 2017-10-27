# P1-2
# Student Name: John Blasco
# Date: 10/13/2016
#
#     I c o n   M a t c h
#
#
# This routine matches one of four candidate icons in a library
# of eight reference icons.
.data
Array:  .alloc	1728

.text

IconMatch:	addi	$1, $0, Array		# point to array base
			#addi    $2, $0, -1         # allow puzzle to be loaded in
			swi		543					# generate puzzle icons

			addi $10, $0, 13			# init values that appear a lot
			addi $9, $0, 44
			addi $5, $0, 576

			addi $3,$0,0				# init candidate
for1:		slti $27, $3, 4				#starting for loop
			beq $27, $0, end1

			mult $5, $3				#startingIndexCandidate = 1152 +(candidate*144)
			mflo $4					#(candidate*144)
			addi $4, $4, 4608		# $4  = 1152 +(candidate*144)

			addi $6, $0, 0			# number of diagonal scans
for2:		slti $27, $6, 28		# maximum of of 8 diagonal scans
			beq $27, $0, P2

if:			slti $27, $6, 16		#for scans 0-3
			beq $27, $0, else1

			sll $8, $6, 1			# get start and stop values for each diagonal
			add $7, $8, $4			# current search value 	$7
			sub $8, $9, $8
			mult $8, $10
			mflo $8
			add $8, $8, $4			# end search value $8

while1: 	slt $27, $8, $7			# while the search value is less than the end value
			bne $27, $0, efor2

if2:		lw $27, Array($7)		# get the current value in the candidate cell
			beq $27, $0, ewhle1		# if it's black go to while1

			j P2					# value of element stored in $27

ewhle1: 	addi $7, $7, 52			# add 13 to current search value
			j while1				#end of while1

			j efor2


else1:		addi $8, $6, -12		# get start and stop values for bottom left diags
			sll $8, $8, 1
			sub $7, $4, $8
			addi $7, $7, 572		# current search value 	$7
			sub $8, $9, $8
			mult $8, $10
			mflo $8
			sub $8, $7, $8			# end search value		$8

while2: 	slt $27, $7, $8			# check if search values are appropriate
			bne $27, $0, efor2

if3:		lw $27, Array($8)		# current value in candidate cell
			beq $27, $0, ewhle2

			addi $1, $7, 0			# flip values of $7 and $8
			addi $7, $8, 0
			addi $8, $1, 0

			j P2
ewhle2:	 	addi $8, $8, 52			# subtract 13 from current search value
			j while2				# end of while2

efor2:		addi $6, $6, 4			# end for2
			j for2

P2:			sub $8, $7, $4			#  get indexCompareOffset

			addi $6, $0, 0			# init $6 as a counter for ref Icons
for3:		slti $26, $6, 8			# for loop to loop through reference Icons
			beq $0,$26, efor1

			mult $5, $6				# get value of relative index location
			mflo $26
			add $26, $26, $8
			lw $26, Array($26)		# see if color in ref Icon matches cand Icon

if4:		bne $27, $26, efor3		# if icons match at location

			mult $6, $5
			mflo $2					#start index for reference icon $1


			add $13, $0, $4			# current search value 	$13

			addi $14, $13, 564		# end search value		$14

while4: 	slt $12, $13, $14		# is the current search val les then max
			beq $12, $0, ans

			lw $15, Array($13)		# get value at equivalent relative locations
			lw $12, Array($2)

			bne $15, $12, efor3		# compare values if not equal exit check
			addi $13,  $13, 16		# increment through each icon skipping 3 cells
			addi $2, $2, 16
			j while4

ans:		add $2, $0, $6			# break if all diagonal scan index values match
			j end1

efor3:		addi $6, $6, 1			# end of for3
			j for3

efor1:		addi $3, $3, 1			# end of for1
			j for1

end1:		swi	544			# submit answer and check
			jr	$31			# return to caller
