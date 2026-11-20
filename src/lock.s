.text
.global lock
.global unlock

lock:
    # Lock address is passed as argument
    push $fp
    mov $fp, $sp
    lw $r0, 4($fp)
.retry:
    ll $r1, 0($r0)
    cmp $r1, $x0
    br.ne .retry # Spin while locked

    li $r1, 1
    sc $r1, 0($r0)

    cmp $r1, $x0
    br.eq .retry # if SC fails spin
.done:
    mov $sp, $fp
    pop $fp
    spc $rp

unlock:
    push $fp
    mov $fp, $sp
    lw $r0, 4($fp)
    fence
    sw $x0, 0($r0) # Store 0 to lock (unlock)
    mov $sp, $fp
    pop $fp
    spc $rp