	.file	"main.c"
	.text
	.global	intb
	.bss
	.align	2
	.type	intb, @object
	.size	intb, 8
intb:
	.zero	8
	.global	reason
	.section	.rodata
.LC0:
	.string	"Division by zero"
	.data
	.align	2
	.type	reason, @object
	.size	reason, 64
reason:
	.long	.LC0
	.zero	60
	.section	.rodata
.LC1:
	.string	"Handled exception %d [%s].\n"
	.text
	.align	2
	.global	exc_handler
	.type	exc_handler, @function
exc_handler:
	push	$rp
	push	$fp
	mov	$fp, $sp
	subi	$sp, $sp, 4
	addi	$r0, $x0, -1
	sb	$r0, -1($fp)
# 22 "src/main.c" 1
	rcr $r0, 3

# 0 "" 2
	sb	$r0, -1($fp)
	lb	$r0, -1($fp)
	li	$r1, reason
	shli	$r0, $r0, 2
	add	$r0, $r1, $r0
	lw	$r1, 0($r0)
	lb	$r0, -1($fp)
	push	$r1
	push	$r0
	li	$r0, .LC1
	push	$r0
	call	printf
	addi	$sp, $sp, 12
.L2:
	br	.L2
	.size	exc_handler, .-exc_handler
	.global	top_level
	.bss
	.align	12
	.type	top_level, @object
	.size	top_level, 4096
top_level:
	.zero	4096
	.global	bottom_level
	.align	12
	.type	bottom_level, @object
	.size	bottom_level, 4096
bottom_level:
	.zero	4096
	.section	.rodata
.LC2:
	.string	"mapped 0x%x to 0x%x.\n"
	.text
	.align	2
	.global	map
	.type	map, @function
map:
	push	$rp
	push	$fp
	mov	$fp, $sp
	subi	$sp, $sp, 8
	lw	$r0, 8($fp)
	shri	$r0, $r0, 12
	andi	$r0, $r0, 511
	sw	$r0, -4($fp)
	lw	$r0, 8($fp)
	shri	$r0, $r0, 21
	andi	$r0, $r0, 511
	sw	$r0, -8($fp)
	li	$r1, bottom_level
	lw	$r0, -8($fp)
	shli	$r0, $r0, 2
	add	$r0, $r1, $r0
	lw	$r1, 0($r0)
	lw	$r0, 16($fp)
	or	$r1, $r1, $r0
	li	$r2, top_level
	lw	$r0, -4($fp)
	shli	$r0, $r0, 2
	add	$r0, $r2, $r0
	sw	$r1, 0($r0)
	lw	$r1, 12($fp)
	lw	$r0, 16($fp)
	or	$r1, $r1, $r0
	li	$r2, bottom_level
	lw	$r0, -8($fp)
	shli	$r0, $r0, 2
	add	$r0, $r2, $r0
	sw	$r1, 0($r0)
	lw	$r0, 12($fp)
	push	$r0
	lw	$r0, 8($fp)
	push	$r0
	li	$r0, .LC2
	push	$r0
	call	printf
	addi	$sp, $sp, 12
	nop
	mov	$sp, $fp
	pop	$fp
	pop	$rp
	spc	$rp
	.size	map, .-map
	.section	.rodata
.LC3:
	.string	"Hello world from SRA32 Apollo firmware.\n"
.LC4:
	.string	"top_level: 0x%x\n"
	.text
	.align	2
	.global	main
	.type	main, @function
main:
	push	$rp
	push	$fp
	mov	$fp, $sp
	li	$r0, .LC3
	push	$r0
	call	uart_puts
	addi	$sp, $sp, 4
	li	$r1, exc_handler
	li	$r0, intb
	sw	$r1, 0($r0)
	addi	$r0, $x0, 3
	push	$r0
	addi	$r0, $x0, 0
	push	$r0
	addi	$r0, $x0, 0
	push	$r0
	call	map
	addi	$sp, $sp, 12
	addi	$r0, $x0, 3
	push	$r0
	li	$r0, 4096
	push	$r0
	li	$r0, -559042560
	push	$r0
	call	map
	addi	$sp, $sp, 12
	li	$r0, top_level
	push	$r0
	li	$r0, .LC4
	push	$r0
	call	printf
	addi	$sp, $sp, 8
	li	$r1, intb
	li	$r2, top_level
# 51 "src/main.c" 1
	mov $r0, $r1
wcr $r0, 0
li $r0, 0($r2)
wcr $r0, 8
rfl $r0
ori $r0, $r0, (1 << 4) | (1 << 5)
wfl $r0

# 0 "" 2
.L5:
	br	.L5
	.size	main, .-main
	.section	.rodata
.LC5:
	.string	"Handled interrupt %d.\n"
	.text
	.align	2
	.global	int_handler
	.type	int_handler, @function
int_handler:
	push	$rp
	push	$fp
	mov	$fp, $sp
	subi	$sp, $sp, 4
	call	sic_claim
	sb	$r0, -1($fp)
	addi	$r0, $x0, 1
	push	$r0
	addi	$r0, $x0, 0
	push	$r0
	addi	$r0, $x0, 0
	push	$r0
	addi	$r0, $x0, 1
	push	$r0
	call	sic_remap_irq
	addi	$sp, $sp, 16
	lb	$r0, -1($fp)
	push	$r0
	li	$r0, .LC5
	push	$r0
	call	printf
	addi	$sp, $sp, 8
	call	sic_eoi
# 76 "src/main.c" 1
	iret
# 0 "" 2
	nop
	mov	$sp, $fp
	pop	$fp
	pop	$rp
	spc	$rp
	.size	int_handler, .-int_handler
	.align	2
	.global	printf
	.type	printf, @function
printf:
	push	$rp
	push	$fp
	mov	$fp, $sp
	subi	$sp, $sp, 1032
	addi	$r0, $fp, 12
	sw	$r0, -8($fp)
	lw	$r0, -8($fp)
	push	$r0
	lw	$r0, 8($fp)
	push	$r0
	addi	$r0, $x0, 1024
	push	$r0
	addi	$r0, $fp, -1032
	push	$r0
	call	vsnprintf
	addi	$sp, $sp, 16
	sw	$r0, -4($fp)
	addi	$r0, $fp, -1032
	push	$r0
	call	uart_puts
	addi	$sp, $sp, 4
	lw	$r0, -4($fp)
	mov	$sp, $fp
	pop	$fp
	pop	$rp
	spc	$rp
	.size	printf, .-printf
	.section	.rodata
.LC6:
	.string	"%s\n"
	.text
	.align	2
	.global	puts
	.type	puts, @function
puts:
	push	$rp
	push	$fp
	mov	$fp, $sp
	lw	$r0, 8($fp)
	push	$r0
	li	$r0, .LC6
	push	$r0
	call	printf
	addi	$sp, $sp, 8
	mov	$sp, $fp
	pop	$fp
	pop	$rp
	spc	$rp
	.size	puts, .-puts
	.ident	"GCC: (GNU) 14.1.0"
