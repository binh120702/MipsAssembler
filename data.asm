
.data   
	kjsdk: .byte 1
	bbb: .half 2
	array: .word 0:100
	inp: .asciiz "Nhap n: "
	maxstr: .asciiz"\nMax la: "
	minstr: .asciiz "\nMin la: "
	sumstr: .asciiz "\nSum la: "
	index: .asciiz "\nNhap vao chi so i can in ra: "
	indexout: .asciiz "\na[i] la: "

.text 
li $v0, 4
	# nhap n
                    	La $a0,           inp
	syscall
	 
	li $v0, 5 
	syscall
	MOVE $s0, $v0  # S0 = n
	
	# nhap vao day
	la $s1, array	# gan dia chi mang vao $s1
	li $s2, 1	# i=1, mang bat dau tu 1
loopRead: slt $t0, $s0, $s2 
	bne $t0, $zero, endLoopRead	#kiem tra neu n<i thi thoat vong lap
	addi $s1, $s1, 4		#tang dia chi den vi tri cua a[i]
	
	li $v0, 5
	syscall
	sw $v0, 0($s1)			#doc roi luu lai a[i]
	
	addi $s2, $s2, 1		#i=i+1	
	j loopRead	
endLoopRead:

	#find max, min, sum	
	la $s1, array	# gan dia chi mang vao $s1
	li $s2, 1	# i=1, mang bat dau tu 1
	li $s5, 0		#sum
	li $s6, -10000000	#max
	li $s7,  10000000	#min
findLoop:
	slt $t0, $s0, $s2 
	bne $t0, $zero, endFindLoop	#kiem tra neu n<i thi thoat vong lap
	addi $s1, $s1, 4		#tang dia chi den vi tri cua a[i]
	lw $t1, 0($s1) 			# t1 = a[i]
	
	#find max
	slt $t0, $s6, $t1
	beq $t0, $zero, outMax
	add $s6, $zero, $t1 		#if s6<t1 then s6 = t1
	outMax:
	
	#find min
	slt $t0, $t1, $s7
	beq $t0, $zero, outMin
	add $s7, $zero, $t1		#if t1<s7 then s7 = t1
	outMin:
	
	#find sum
	add  $s5, $s5, $t1
	
	addi $s2, $s2, 1		#i=i+1
	j findLoop
endFindLoop:

#pr max
	li $v0, 4
	la $a0, maxstr
	syscall 	
	li $v0, 1
	move $a0, $s6
	syscall
#pr min
	li $v0, 4
	la $a0, minstr
	syscall 	
	li $v0, 1
	move $a0, $s7
	syscall
#pr sum
	li $v0, 4
	la $a0, sumstr
	syscall 	
	li $v0, 1
	move $a0, $s5
	syscall
# nhap vao chi so i va in ra a[i]
	li $v0, 4
	la $a0, index
	syscall 
	li $v0, 5
	syscall
	move $t0, $v0 # luu i vao t0
	li $t1, 4
	mult $t0, $t1
	mflo $t0
	la $s1, array
	add $s1, $s1, $t0
	
	li $v0, 4
	la $a0, indexout
	syscall 
	li $v0, 1
	lw $a0, 0($s1)
	syscall
	
