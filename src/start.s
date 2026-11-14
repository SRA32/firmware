.text
.global _start
# Copy data (and other writable) section to RAM (0x100000)

_start:
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
    li $sp, stack_top
    wcr $r0, 0
    call main
loop:
    br loop

.data
.align 4
stack_bottom:
.skip 8192 # 8 KiB
stack_top: