.text
.global _start
.global internal_local_handler
.extern local_handler
.extern ap_start
# Copy data (and other writable) section to RAM (0x100000)

# If this is CPU0, jump to bsp start
cmp $r26, $x0
br.eq _start

li $sp, stack_bottom
li $r0, 1024
addi $r25, $r26, 1
mul $r0, $r0, $r25
add $sp, $sp, $r0

call ap_start

_start:
    li $sp, stack_bottom
    addi $sp, $sp, 1024

    li $r0, _data_load
    li $r1, _data_start
    li $r2, _data_end

copy_data:
    cmp $r1, $r2
    br.eq zero_bss

    lw $r3, 0($r0)
    sw $r3, 0($r1)

    addi $r0, $r0, 4
    addi $r1, $r1, 4
    br copy_data

zero_bss:
    li $r1, _bss_start
    li $r2, _bss_end

zero_loop:
    cmp $r1, $r2
    br.eq call_main

    sw $x0, 0($r1)
    addi $r1, $r1, 4
    br zero_loop

call_main:
    push $r27
    call main
loop:
    br loop

internal_local_handler:
    call local_handler
    iret

.data
.align 4
stack_bottom:
.skip 1024*8 # 1 KiB for each CPU
stack_top: