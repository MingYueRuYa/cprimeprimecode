	.file	"main.cpp"
	.section	.text._ZnwjPv,"axG",@progbits,_ZnwjPv,comdat
	.weak	_ZnwjPv
	.type	_ZnwjPv, @function
_ZnwjPv:
.LFB267:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	12(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE267:
	.size	_ZnwjPv, .-_ZnwjPv
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.text
	.globl	main
	.type	main, @function
main:
.LFB1329:
	.cfi_startproc
	.cfi_personality 0,__gxx_personality_v0
	.cfi_lsda 0,.LLSDA1329
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	andl	$-16, %esp
	subl	$48, %esp
	.cfi_offset 3, -12
	leal	36(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEC1Ev
	movl	$0, 28(%esp)
	jmp	.L4
.L5:
	leal	28(%esp), %eax
	movl	%eax, 4(%esp)
	leal	36(%esp), %eax
	movl	%eax, (%esp)
.LEHB0:
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE9push_backERKi
	movl	28(%esp), %eax
	addl	$1, %eax
	movl	%eax, 28(%esp)
.L4:
	movl	28(%esp), %eax
	cmpl	$9, %eax
	jle	.L5
	movl	$0, 32(%esp)
	jmp	.L6
.L7:
	movl	32(%esp), %eax
	movl	%eax, 4(%esp)
	leal	36(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEixEj
	movl	(%eax), %eax
	movl	%eax, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPFRSoS_E
.LEHE0:
	addl	$1, 32(%esp)
.L6:
	cmpl	$9, 32(%esp)
	jle	.L7
	movl	$0, %ebx
	leal	36(%esp), %eax
	movl	%eax, (%esp)
.LEHB1:
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEED1Ev
.LEHE1:
	movl	%ebx, %eax
	jmp	.L11
.L10:
	movl	%eax, %ebx
	leal	36(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEED1Ev
	movl	%ebx, %eax
	movl	%eax, (%esp)
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
.L11:
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1329:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1329:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1329-.LLSDACSB1329
.LLSDACSB1329:
	.uleb128 .LEHB0-.LFB1329
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L10-.LFB1329
	.uleb128 0
	.uleb128 .LEHB1-.LFB1329
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB2-.LFB1329
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE1329:
	.text
	.size	main, .-main
	.section	.text._ZN6vectorIi24__default_alloc_templateILb0ELi0EEEC2Ev,"axG",@progbits,_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEC5Ev,comdat
	.align 2
	.weak	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEC2Ev
	.type	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEC2Ev, @function
_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEC2Ev:
.LFB1351:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	$0, (%eax)
	movl	8(%ebp), %eax
	movl	$0, 4(%eax)
	movl	8(%ebp), %eax
	movl	$0, 8(%eax)
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1351:
	.size	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEC2Ev, .-_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEC2Ev
	.weak	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEC1Ev
	.set	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEC1Ev,_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEC2Ev
	.section	.text._ZN6vectorIi24__default_alloc_templateILb0ELi0EEED2Ev,"axG",@progbits,_ZN6vectorIi24__default_alloc_templateILb0ELi0EEED5Ev,comdat
	.align 2
	.weak	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEED2Ev
	.type	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEED2Ev, @function
_ZN6vectorIi24__default_alloc_templateILb0ELi0EEED2Ev:
.LFB1354:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_Z7destroyIPiEvT_S1_
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10deallocateEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1354:
	.size	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEED2Ev, .-_ZN6vectorIi24__default_alloc_templateILb0ELi0EEED2Ev
	.weak	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEED1Ev
	.set	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEED1Ev,_ZN6vectorIi24__default_alloc_templateILb0ELi0EEED2Ev
	.section	.text._ZN6vectorIi24__default_alloc_templateILb0ELi0EEE9push_backERKi,"axG",@progbits,_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE9push_backERKi,comdat
	.align 2
	.weak	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE9push_backERKi
	.type	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE9push_backERKi, @function
_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE9push_backERKi:
.LFB1356:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	%eax, %edx
	je	.L16
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_Z9constructIiiEvPT_RKT0_
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	leal	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 4(%eax)
	jmp	.L15
.L16:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv
	movl	12(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10insert_auxEPiRKi
.L15:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1356:
	.size	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE9push_backERKi, .-_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE9push_backERKi
	.section	.text._ZN6vectorIi24__default_alloc_templateILb0ELi0EEEixEj,"axG",@progbits,_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEixEj,comdat
	.align 2
	.weak	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEixEj
	.type	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEixEj, @function
_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEixEj:
.LFB1357:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv
	movl	12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1357:
	.size	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEixEj, .-_ZN6vectorIi24__default_alloc_templateILb0ELi0EEEixEj
	.section	.text._ZN24__default_alloc_templateILb0ELi0EE8allocateEj,"axG",@progbits,_ZN24__default_alloc_templateILb0ELi0EE8allocateEj,comdat
	.weak	_ZN24__default_alloc_templateILb0ELi0EE8allocateEj
	.type	_ZN24__default_alloc_templateILb0ELi0EE8allocateEj, @function
_ZN24__default_alloc_templateILb0ELi0EE8allocateEj:
.LFB1360:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	cmpl	$128, 8(%ebp)
	jbe	.L21
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN23__malloc_alloc_templateILi0EE8allocateEj
	jmp	.L22
.L21:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj
	sall	$2, %eax
	addl	$_ZN24__default_alloc_templateILb0ELi0EE9free_listE, %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -16(%ebp)
	cmpl	$0, -16(%ebp)
	jne	.L23
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE8ROUND_UPEj
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE6refillEj
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	jmp	.L22
.L23:
	movl	-16(%ebp), %eax
	movl	(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, (%eax)
	movl	-16(%ebp), %eax
.L22:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1360:
	.size	_ZN24__default_alloc_templateILb0ELi0EE8allocateEj, .-_ZN24__default_alloc_templateILb0ELi0EE8allocateEj
	.section	.text._ZN24__default_alloc_templateILb0ELi0EE10deallocateEPvj,"axG",@progbits,_ZN24__default_alloc_templateILb0ELi0EE10deallocateEPvj,comdat
	.weak	_ZN24__default_alloc_templateILb0ELi0EE10deallocateEPvj
	.type	_ZN24__default_alloc_templateILb0ELi0EE10deallocateEPvj, @function
_ZN24__default_alloc_templateILb0ELi0EE10deallocateEPvj:
.LFB1361:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
	cmpl	$128, 12(%ebp)
	jbe	.L25
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN23__malloc_alloc_templateILi0EE10deallocateEPvj
	jmp	.L24
.L25:
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj
	sall	$2, %eax
	addl	$_ZN24__default_alloc_templateILb0ELi0EE9free_listE, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	(%eax), %edx
	movl	-16(%ebp), %eax
	movl	%edx, (%eax)
	movl	-12(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, (%eax)
.L24:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1361:
	.size	_ZN24__default_alloc_templateILb0ELi0EE10deallocateEPvj, .-_ZN24__default_alloc_templateILb0ELi0EE10deallocateEPvj
	.section	.text._Z7destroyIPiEvT_S1_,"axG",@progbits,_Z7destroyIPiEvT_S1_,comdat
	.weak	_Z7destroyIPiEvT_S1_
	.type	_Z7destroyIPiEvT_S1_, @function
_Z7destroyIPiEvT_S1_:
.LFB1370:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z10value_typeIiEPT_PKS0_
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z9__destroyIPiiEvT_S1_PT0_
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1370:
	.size	_Z7destroyIPiEvT_S1_, .-_Z7destroyIPiEvT_S1_
	.section	.text._ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10deallocateEv,"axG",@progbits,_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10deallocateEv,comdat
	.align 2
	.weak	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10deallocateEv
	.type	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10deallocateEv, @function
_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10deallocateEv:
.LFB1371:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	je	.L28
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sarl	$2, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE10deallocateEPij
.L28:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1371:
	.size	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10deallocateEv, .-_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10deallocateEv
	.section	.text._Z9constructIiiEvPT_RKT0_,"axG",@progbits,_Z9constructIiiEvPT_RKT0_,comdat
	.weak	_Z9constructIiiEvPT_RKT0_
	.type	_Z9constructIiiEvPT_RKT0_, @function
_Z9constructIiiEvPT_RKT0_:
.LFB1372:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$4, (%esp)
	call	_ZnwjPv
	testl	%eax, %eax
	je	.L30
	movl	12(%ebp), %edx
	movl	(%edx), %edx
	movl	%edx, (%eax)
.L30:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1372:
	.size	_Z9constructIiiEvPT_RKT0_, .-_Z9constructIiiEvPT_RKT0_
	.section	.text._ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10insert_auxEPiRKi,"axG",@progbits,_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10insert_auxEPiRKi,comdat
	.align 2
	.weak	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10insert_auxEPiRKi
	.type	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10insert_auxEPiRKi, @function
_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10insert_auxEPiRKi:
.LFB1373:
	.cfi_startproc
	.cfi_personality 0,__gxx_personality_v0
	.cfi_lsda 0,.LLSDA1373
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$52, %esp
	.cfi_offset 3, -12
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	%eax, %edx
	je	.L34
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	leal	-4(%eax), %edx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_Z9constructIiiEvPT_RKT0_
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	leal	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	16(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -24(%ebp)
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	leal	-4(%eax), %edx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	subl	$8, %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
.LEHB3:
	call	_Z13copy_backwardIPiS0_ET0_T_S2_S1_
	movl	12(%ebp), %eax
	movl	-24(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L33
.L34:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE4sizeEv
	movl	%eax, -20(%ebp)
	cmpl	$0, -20(%ebp)
	je	.L36
	movl	-20(%ebp), %eax
	addl	%eax, %eax
	jmp	.L37
.L36:
	movl	$1, %eax
.L37:
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE8allocateEj
.LEHE3:
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
.LEHB4:
	call	_Z18uninitialized_copyIPiS0_ET0_T_S2_S1_
	movl	%eax, -28(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z9constructIiiEvPT_RKT0_
	addl	$4, -28(%ebp)
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z18uninitialized_copyIPiS0_ET0_T_S2_S1_
.LEHE4:
	movl	%eax, -28(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv
	movl	%eax, %ebx
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
.LEHB5:
	call	_Z7destroyIPiEvT_S1_
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10deallocateEv
.LEHE5:
	movl	8(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 4(%eax)
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	-12(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 8(%eax)
	jmp	.L33
.L41:
	movl	%eax, %ebx
	call	__cxa_end_catch
	movl	%ebx, %eax
	movl	%eax, (%esp)
.LEHB6:
	call	_Unwind_Resume
.LEHE6:
.L40:
	movl	%eax, (%esp)
	call	__cxa_begin_catch
	movl	-28(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
.LEHB7:
	call	_Z7destroyIPiEvT_S1_
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE10deallocateEPij
	call	__cxa_rethrow
.LEHE7:
.L33:
	addl	$52, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1373:
	.section	.gcc_except_table
	.align 4
.LLSDA1373:
	.byte	0xff
	.byte	0
	.uleb128 .LLSDATT1373-.LLSDATTD1373
.LLSDATTD1373:
	.byte	0x1
	.uleb128 .LLSDACSE1373-.LLSDACSB1373
.LLSDACSB1373:
	.uleb128 .LEHB3-.LFB1373
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB1373
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L40-.LFB1373
	.uleb128 0x1
	.uleb128 .LEHB5-.LFB1373
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB6-.LFB1373
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB7-.LFB1373
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L41-.LFB1373
	.uleb128 0
.LLSDACSE1373:
	.byte	0x1
	.byte	0
	.align 4
	.long	0
.LLSDATT1373:
	.section	.text._ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10insert_auxEPiRKi,"axG",@progbits,_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10insert_auxEPiRKi,comdat
	.size	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10insert_auxEPiRKi, .-_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE10insert_auxEPiRKi
	.section	.text._ZN6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv,"axG",@progbits,_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv,comdat
	.align 2
	.weak	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv
	.type	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv, @function
_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv:
.LFB1374:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1374:
	.size	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv, .-_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv
	.section	.text._ZN6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv,"axG",@progbits,_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv,comdat
	.align 2
	.weak	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv
	.type	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv, @function
_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv:
.LFB1375:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1375:
	.size	_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv, .-_ZN6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv
	.section	.text._ZN23__malloc_alloc_templateILi0EE8allocateEj,"axG",@progbits,_ZN23__malloc_alloc_templateILi0EE8allocateEj,comdat
	.weak	_ZN23__malloc_alloc_templateILi0EE8allocateEj
	.type	_ZN23__malloc_alloc_templateILi0EE8allocateEj, @function
_ZN23__malloc_alloc_templateILi0EE8allocateEj:
.LFB1378:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -12(%ebp)
	cmpl	$0, -12(%ebp)
	jne	.L47
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN23__malloc_alloc_templateILi0EE10oom_mallocEj
	movl	%eax, -12(%ebp)
.L47:
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1378:
	.size	_ZN23__malloc_alloc_templateILi0EE8allocateEj, .-_ZN23__malloc_alloc_templateILi0EE8allocateEj
	.section	.text._ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj,"axG",@progbits,_ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj,comdat
	.weak	_ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj
	.type	_ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj, @function
_ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj:
.LFB1379:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	addl	$7, %eax
	shrl	$3, %eax
	subl	$1, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1379:
	.size	_ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj, .-_ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj
	.section	.text._ZN24__default_alloc_templateILb0ELi0EE6refillEj,"axG",@progbits,_ZN24__default_alloc_templateILb0ELi0EE6refillEj,comdat
	.align 2
	.weak	_ZN24__default_alloc_templateILb0ELi0EE6refillEj
	.type	_ZN24__default_alloc_templateILb0ELi0EE6refillEj, @function
_ZN24__default_alloc_templateILb0ELi0EE6refillEj:
.LFB1380:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	movl	$20, -36(%ebp)
	leal	-36(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE11chunk_allocEjRi
	movl	%eax, -24(%ebp)
	movl	-36(%ebp), %eax
	cmpl	$1, %eax
	jne	.L52
	movl	-24(%ebp), %eax
	jmp	.L57
.L52:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj
	sall	$2, %eax
	addl	$_ZN24__default_alloc_templateILb0ELi0EE9free_listE, %eax
	movl	%eax, -20(%ebp)
	movl	-24(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	8(%ebp), %eax
	movl	-24(%ebp), %edx
	addl	%edx, %eax
	movl	%eax, -32(%ebp)
	movl	-20(%ebp), %eax
	movl	-32(%ebp), %edx
	movl	%edx, (%eax)
	movl	$1, -28(%ebp)
.L56:
	movl	-32(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	8(%ebp), %eax
	addl	%eax, -32(%ebp)
	movl	-36(%ebp), %eax
	subl	$1, %eax
	cmpl	-28(%ebp), %eax
	jne	.L54
	movl	-12(%ebp), %eax
	movl	$0, (%eax)
	nop
	movl	-16(%ebp), %eax
	jmp	.L57
.L54:
	movl	-12(%ebp), %eax
	movl	-32(%ebp), %edx
	movl	%edx, (%eax)
	addl	$1, -28(%ebp)
	jmp	.L56
.L57:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1380:
	.size	_ZN24__default_alloc_templateILb0ELi0EE6refillEj, .-_ZN24__default_alloc_templateILb0ELi0EE6refillEj
	.section	.text._ZN24__default_alloc_templateILb0ELi0EE8ROUND_UPEj,"axG",@progbits,_ZN24__default_alloc_templateILb0ELi0EE8ROUND_UPEj,comdat
	.weak	_ZN24__default_alloc_templateILb0ELi0EE8ROUND_UPEj
	.type	_ZN24__default_alloc_templateILb0ELi0EE8ROUND_UPEj, @function
_ZN24__default_alloc_templateILb0ELi0EE8ROUND_UPEj:
.LFB1381:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	addl	$7, %eax
	andl	$-8, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1381:
	.size	_ZN24__default_alloc_templateILb0ELi0EE8ROUND_UPEj, .-_ZN24__default_alloc_templateILb0ELi0EE8ROUND_UPEj
	.section	.text._ZN23__malloc_alloc_templateILi0EE10deallocateEPvj,"axG",@progbits,_ZN23__malloc_alloc_templateILi0EE10deallocateEPvj,comdat
	.weak	_ZN23__malloc_alloc_templateILi0EE10deallocateEPvj
	.type	_ZN23__malloc_alloc_templateILi0EE10deallocateEPvj, @function
_ZN23__malloc_alloc_templateILi0EE10deallocateEPvj:
.LFB1382:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1382:
	.size	_ZN23__malloc_alloc_templateILi0EE10deallocateEPvj, .-_ZN23__malloc_alloc_templateILi0EE10deallocateEPvj
	.section	.text._Z10value_typeIiEPT_PKS0_,"axG",@progbits,_Z10value_typeIiEPT_PKS0_,comdat
	.weak	_Z10value_typeIiEPT_PKS0_
	.type	_Z10value_typeIiEPT_PKS0_, @function
_Z10value_typeIiEPT_PKS0_:
.LFB1387:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$0, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1387:
	.size	_Z10value_typeIiEPT_PKS0_, .-_Z10value_typeIiEPT_PKS0_
	.section	.text._Z9__destroyIPiiEvT_S1_PT0_,"axG",@progbits,_Z9__destroyIPiiEvT_S1_PT0_,comdat
	.weak	_Z9__destroyIPiiEvT_S1_PT0_
	.type	_Z9__destroyIPiiEvT_S1_PT0_, @function
_Z9__destroyIPiiEvT_S1_PT0_:
.LFB1388:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movb	%al, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z13__destroy_auxIPiEvT_S1_11__true_type
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1388:
	.size	_Z9__destroyIPiiEvT_S1_PT0_, .-_Z9__destroyIPiiEvT_S1_PT0_
	.section	.text._ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE10deallocateEPij,"axG",@progbits,_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE10deallocateEPij,comdat
	.weak	_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE10deallocateEPij
	.type	_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE10deallocateEPij, @function
_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE10deallocateEPij:
.LFB1389:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$0, 12(%ebp)
	je	.L64
	movl	12(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE10deallocateEPvj
.L64:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1389:
	.size	_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE10deallocateEPij, .-_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE10deallocateEPij
	.section	.text._Z13copy_backwardIPiS0_ET0_T_S2_S1_,"axG",@progbits,_Z13copy_backwardIPiS0_ET0_T_S2_S1_,comdat
	.weak	_Z13copy_backwardIPiS0_ET0_T_S2_S1_
	.type	_Z13copy_backwardIPiS0_ET0_T_S2_S1_, @function
_Z13copy_backwardIPiS0_ET0_T_S2_S1_:
.LFB1390:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-9(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN24__copy_backward_dispatchIPiS0_EclES0_S0_S0_
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1390:
	.size	_Z13copy_backwardIPiS0_ET0_T_S2_S1_, .-_Z13copy_backwardIPiS0_ET0_T_S2_S1_
	.section	.text._ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE4sizeEv,"axG",@progbits,_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE4sizeEv,comdat
	.align 2
	.weak	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE4sizeEv
	.type	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE4sizeEv, @function
_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE4sizeEv:
.LFB1391:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv
	movl	%eax, %ebx
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv
	subl	%eax, %ebx
	movl	%ebx, %eax
	sarl	$2, %eax
	addl	$20, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1391:
	.size	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE4sizeEv, .-_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE4sizeEv
	.section	.text._ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE8allocateEj,"axG",@progbits,_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE8allocateEj,comdat
	.weak	_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE8allocateEj
	.type	_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE8allocateEj, @function
_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE8allocateEj:
.LFB1392:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$0, 8(%ebp)
	je	.L71
	movl	8(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE8allocateEj
	jmp	.L72
.L71:
	movl	$0, %eax
.L72:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1392:
	.size	_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE8allocateEj, .-_ZN12simple_allocIi24__default_alloc_templateILb0ELi0EEE8allocateEj
	.section	.text._Z18uninitialized_copyIPiS0_ET0_T_S2_S1_,"axG",@progbits,_Z18uninitialized_copyIPiS0_ET0_T_S2_S1_,comdat
	.weak	_Z18uninitialized_copyIPiS0_ET0_T_S2_S1_
	.type	_Z18uninitialized_copyIPiS0_ET0_T_S2_S1_, @function
_Z18uninitialized_copyIPiS0_ET0_T_S2_S1_:
.LFB1393:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z10value_typeIiEPT_PKS0_
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z20__uninitialized_copyIPiS0_iET0_T_S2_S1_PT1_
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1393:
	.size	_Z18uninitialized_copyIPiS0_ET0_T_S2_S1_, .-_Z18uninitialized_copyIPiS0_ET0_T_S2_S1_
	.section	.rodata
.LC0:
	.string	"out of memory"
	.section	.text._ZN23__malloc_alloc_templateILi0EE10oom_mallocEj,"axG",@progbits,_ZN23__malloc_alloc_templateILi0EE10oom_mallocEj,comdat
	.align 2
	.weak	_ZN23__malloc_alloc_templateILi0EE10oom_mallocEj
	.type	_ZN23__malloc_alloc_templateILi0EE10oom_mallocEj, @function
_ZN23__malloc_alloc_templateILi0EE10oom_mallocEj:
.LFB1395:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
.L80:
	movl	_ZN23__malloc_alloc_templateILi0EE26__malloc_alloc_oom_handlerE, %eax
	movl	%eax, -16(%ebp)
	cmpl	$0, -16(%ebp)
	jne	.L77
	movl	$.LC0, 4(%esp)
	movl	$_ZSt4cerr, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSolsEPFRSoS_E
	movl	$1, (%esp)
	call	exit
.L77:
	movl	-16(%ebp), %eax
	call	*%eax
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -12(%ebp)
	cmpl	$0, -12(%ebp)
	je	.L78
	movl	-12(%ebp), %eax
	jmp	.L81
.L78:
	jmp	.L80
.L81:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1395:
	.size	_ZN23__malloc_alloc_templateILi0EE10oom_mallocEj, .-_ZN23__malloc_alloc_templateILi0EE10oom_mallocEj
	.section	.text._ZN24__default_alloc_templateILb0ELi0EE11chunk_allocEjRi,"axG",@progbits,_ZN24__default_alloc_templateILb0ELi0EE11chunk_allocEjRi,comdat
	.align 2
	.weak	_ZN24__default_alloc_templateILb0ELi0EE11chunk_allocEjRi
	.type	_ZN24__default_alloc_templateILb0ELi0EE11chunk_allocEjRi, @function
_ZN24__default_alloc_templateILb0ELi0EE11chunk_allocEjRi:
.LFB1396:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$52, %esp
	.cfi_offset 3, -12
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	imull	8(%ebp), %eax
	movl	%eax, -36(%ebp)
	movl	_ZN24__default_alloc_templateILb0ELi0EE8end_freeE, %eax
	movl	%eax, %edx
	movl	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %eax
	cmpl	-36(%ebp), %eax
	jb	.L83
	movl	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, %eax
	movl	%eax, -28(%ebp)
	movl	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, %edx
	movl	-36(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, _ZN24__default_alloc_templateILb0ELi0EE10start_freeE
	movl	-28(%ebp), %eax
	jmp	.L84
.L83:
	movl	-32(%ebp), %eax
	cmpl	8(%ebp), %eax
	jb	.L85
	movl	-32(%ebp), %eax
	movl	$0, %edx
	divl	8(%ebp)
	movl	%eax, %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	imull	8(%ebp), %eax
	movl	%eax, -36(%ebp)
	movl	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, %eax
	movl	%eax, -28(%ebp)
	movl	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, %edx
	movl	-36(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, _ZN24__default_alloc_templateILb0ELi0EE10start_freeE
	movl	-28(%ebp), %eax
	jmp	.L84
.L85:
	movl	-36(%ebp), %eax
	leal	(%eax,%eax), %ebx
	movl	_ZN24__default_alloc_templateILb0ELi0EE9heap_sizeE, %eax
	shrl	$4, %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE8ROUND_UPEj
	addl	%ebx, %eax
	movl	%eax, -24(%ebp)
	cmpl	$0, -32(%ebp)
	je	.L86
	movl	-32(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj
	sall	$2, %eax
	addl	$_ZN24__default_alloc_templateILb0ELi0EE9free_listE, %eax
	movl	%eax, -20(%ebp)
	movl	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, %eax
	movl	-20(%ebp), %edx
	movl	(%edx), %edx
	movl	%edx, (%eax)
	movl	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, %edx
	movl	-20(%ebp), %eax
	movl	%edx, (%eax)
.L86:
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, _ZN24__default_alloc_templateILb0ELi0EE10start_freeE
	movl	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, %eax
	testl	%eax, %eax
	jne	.L87
	movl	8(%ebp), %eax
	movl	%eax, -40(%ebp)
	jmp	.L88
.L90:
	movl	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE14FREELIST_INDEXEj
	sall	$2, %eax
	addl	$_ZN24__default_alloc_templateILb0ELi0EE9free_listE, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -12(%ebp)
	cmpl	$0, -12(%ebp)
	je	.L89
	movl	-12(%ebp), %eax
	movl	(%eax), %edx
	movl	-16(%ebp), %eax
	movl	%edx, (%eax)
	movl	-12(%ebp), %eax
	movl	%eax, _ZN24__default_alloc_templateILb0ELi0EE10start_freeE
	movl	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, %edx
	movl	-40(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, _ZN24__default_alloc_templateILb0ELi0EE8end_freeE
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE11chunk_allocEjRi
	jmp	.L84
.L89:
	addl	$8, -40(%ebp)
.L88:
	cmpl	$128, -40(%ebp)
	jle	.L90
	movl	$0, _ZN24__default_alloc_templateILb0ELi0EE8end_freeE
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN23__malloc_alloc_templateILi0EE8allocateEj
	movl	%eax, _ZN24__default_alloc_templateILb0ELi0EE10start_freeE
.L87:
	movl	_ZN24__default_alloc_templateILb0ELi0EE9heap_sizeE, %edx
	movl	-24(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, _ZN24__default_alloc_templateILb0ELi0EE9heap_sizeE
	movl	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, %edx
	movl	-24(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, _ZN24__default_alloc_templateILb0ELi0EE8end_freeE
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN24__default_alloc_templateILb0ELi0EE11chunk_allocEjRi
.L84:
	addl	$52, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1396:
	.size	_ZN24__default_alloc_templateILb0ELi0EE11chunk_allocEjRi, .-_ZN24__default_alloc_templateILb0ELi0EE11chunk_allocEjRi
	.section	.text._Z13__destroy_auxIPiEvT_S1_11__true_type,"axG",@progbits,_Z13__destroy_auxIPiEvT_S1_11__true_type,comdat
	.weak	_Z13__destroy_auxIPiEvT_S1_11__true_type
	.type	_Z13__destroy_auxIPiEvT_S1_11__true_type, @function
_Z13__destroy_auxIPiEvT_S1_11__true_type:
.LFB1402:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1402:
	.size	_Z13__destroy_auxIPiEvT_S1_11__true_type, .-_Z13__destroy_auxIPiEvT_S1_11__true_type
	.section	.text._ZN24__copy_backward_dispatchIPiS0_EclES0_S0_S0_,"axG",@progbits,_ZN24__copy_backward_dispatchIPiS0_EclES0_S0_S0_,comdat
	.align 2
	.weak	_ZN24__copy_backward_dispatchIPiS0_EclES0_S0_S0_
	.type	_ZN24__copy_backward_dispatchIPiS0_EclES0_S0_S0_, @function
_ZN24__copy_backward_dispatchIPiS0_EclES0_S0_S0_:
.LFB1403:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z15__copy_backwardIPiS0_ET0_T_S2_S1_
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1403:
	.size	_ZN24__copy_backward_dispatchIPiS0_EclES0_S0_S0_, .-_ZN24__copy_backward_dispatchIPiS0_EclES0_S0_S0_
	.section	.text._ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv,"axG",@progbits,_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv,comdat
	.align 2
	.weak	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv
	.type	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv, @function
_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv:
.LFB1404:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1404:
	.size	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv, .-_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE5beginEv
	.section	.text._ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv,"axG",@progbits,_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv,comdat
	.align 2
	.weak	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv
	.type	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv, @function
_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv:
.LFB1405:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1405:
	.size	_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv, .-_ZNK6vectorIi24__default_alloc_templateILb0ELi0EEE3endEv
	.section	.text._Z20__uninitialized_copyIPiS0_iET0_T_S2_S1_PT1_,"axG",@progbits,_Z20__uninitialized_copyIPiS0_iET0_T_S2_S1_PT1_,comdat
	.weak	_Z20__uninitialized_copyIPiS0_iET0_T_S2_S1_PT1_
	.type	_Z20__uninitialized_copyIPiS0_iET0_T_S2_S1_PT1_, @function
_Z20__uninitialized_copyIPiS0_iET0_T_S2_S1_PT1_:
.LFB1406:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movb	%al, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z24__uninitialized_copy_auxIPiS0_ET0_T_S2_S1_11__true_type
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1406:
	.size	_Z20__uninitialized_copyIPiS0_iET0_T_S2_S1_PT1_, .-_Z20__uninitialized_copyIPiS0_iET0_T_S2_S1_PT1_
	.section	.text._Z15__copy_backwardIPiS0_ET0_T_S2_S1_,"axG",@progbits,_Z15__copy_backwardIPiS0_ET0_T_S2_S1_,comdat
	.weak	_Z15__copy_backwardIPiS0_ET0_T_S2_S1_
	.type	_Z15__copy_backwardIPiS0_ET0_T_S2_S1_, @function
_Z15__copy_backwardIPiS0_ET0_T_S2_S1_:
.LFB1408:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	jmp	.L101
.L102:
	subl	$4, 16(%ebp)
	subl	$4, 12(%ebp)
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
.L101:
	movl	8(%ebp), %eax
	cmpl	12(%ebp), %eax
	jne	.L102
	movl	16(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1408:
	.size	_Z15__copy_backwardIPiS0_ET0_T_S2_S1_, .-_Z15__copy_backwardIPiS0_ET0_T_S2_S1_
	.section	.text._Z24__uninitialized_copy_auxIPiS0_ET0_T_S2_S1_11__true_type,"axG",@progbits,_Z24__uninitialized_copy_auxIPiS0_ET0_T_S2_S1_11__true_type,comdat
	.weak	_Z24__uninitialized_copy_auxIPiS0_ET0_T_S2_S1_11__true_type
	.type	_Z24__uninitialized_copy_auxIPiS0_ET0_T_S2_S1_11__true_type, @function
_Z24__uninitialized_copy_auxIPiS0_ET0_T_S2_S1_11__true_type:
.LFB1409:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z4copyIPiS0_ET0_T_S2_S1_
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1409:
	.size	_Z24__uninitialized_copy_auxIPiS0_ET0_T_S2_S1_11__true_type, .-_Z24__uninitialized_copy_auxIPiS0_ET0_T_S2_S1_11__true_type
	.section	.text._Z4copyIPiS0_ET0_T_S2_S1_,"axG",@progbits,_Z4copyIPiS0_ET0_T_S2_S1_,comdat
	.weak	_Z4copyIPiS0_ET0_T_S2_S1_
	.type	_Z4copyIPiS0_ET0_T_S2_S1_, @function
_Z4copyIPiS0_ET0_T_S2_S1_:
.LFB1411:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-9(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN15__copy_dispatchIPiS0_EclES0_S0_S0_
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1411:
	.size	_Z4copyIPiS0_ET0_T_S2_S1_, .-_Z4copyIPiS0_ET0_T_S2_S1_
	.section	.text._ZN15__copy_dispatchIPiS0_EclES0_S0_S0_,"axG",@progbits,_ZN15__copy_dispatchIPiS0_EclES0_S0_S0_,comdat
	.align 2
	.weak	_ZN15__copy_dispatchIPiS0_EclES0_S0_S0_
	.type	_ZN15__copy_dispatchIPiS0_EclES0_S0_S0_, @function
_ZN15__copy_dispatchIPiS0_EclES0_S0_S0_:
.LFB1413:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$52, %esp
	.cfi_offset 3, -12
	leal	-25(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_Z17iterator_categoryIiE26random_access_iterator_tagPKT_
	subl	$4, %esp
	movb	%bl, 12(%esp)
	movl	20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z6__copyIPiS0_ET0_T_S2_S1_26random_access_iterator_tag
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1413:
	.size	_ZN15__copy_dispatchIPiS0_EclES0_S0_S0_, .-_ZN15__copy_dispatchIPiS0_EclES0_S0_S0_
	.section	.text._Z17iterator_categoryIiE26random_access_iterator_tagPKT_,"axG",@progbits,_Z17iterator_categoryIiE26random_access_iterator_tagPKT_,comdat
	.weak	_Z17iterator_categoryIiE26random_access_iterator_tagPKT_
	.type	_Z17iterator_categoryIiE26random_access_iterator_tagPKT_, @function
_Z17iterator_categoryIiE26random_access_iterator_tagPKT_:
.LFB1414:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	nop
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE1414:
	.size	_Z17iterator_categoryIiE26random_access_iterator_tagPKT_, .-_Z17iterator_categoryIiE26random_access_iterator_tagPKT_
	.section	.text._Z6__copyIPiS0_ET0_T_S2_S1_26random_access_iterator_tag,"axG",@progbits,_Z6__copyIPiS0_ET0_T_S2_S1_26random_access_iterator_tag,comdat
	.weak	_Z6__copyIPiS0_ET0_T_S2_S1_26random_access_iterator_tag
	.type	_Z6__copyIPiS0_ET0_T_S2_S1_26random_access_iterator_tag, @function
_Z6__copyIPiS0_ET0_T_S2_S1_26random_access_iterator_tag:
.LFB1415:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z13distance_typeIiEPiPKT_
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z8__copy_dIPiS0_iET0_T_S2_S1_PT1_
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1415:
	.size	_Z6__copyIPiS0_ET0_T_S2_S1_26random_access_iterator_tag, .-_Z6__copyIPiS0_ET0_T_S2_S1_26random_access_iterator_tag
	.section	.text._Z13distance_typeIiEPiPKT_,"axG",@progbits,_Z13distance_typeIiEPiPKT_,comdat
	.weak	_Z13distance_typeIiEPiPKT_
	.type	_Z13distance_typeIiEPiPKT_, @function
_Z13distance_typeIiEPiPKT_:
.LFB1416:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$0, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1416:
	.size	_Z13distance_typeIiEPiPKT_, .-_Z13distance_typeIiEPiPKT_
	.section	.text._Z8__copy_dIPiS0_iET0_T_S2_S1_PT1_,"axG",@progbits,_Z8__copy_dIPiS0_iET0_T_S2_S1_PT1_,comdat
	.weak	_Z8__copy_dIPiS0_iET0_T_S2_S1_PT1_
	.type	_Z8__copy_dIPiS0_iET0_T_S2_S1_PT1_, @function
_Z8__copy_dIPiS0_iET0_T_S2_S1_PT1_:
.LFB1417:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sarl	$2, %eax
	movl	%eax, -4(%ebp)
	jmp	.L117
.L118:
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
	subl	$1, -4(%ebp)
	addl	$4, 16(%ebp)
	addl	$4, 8(%ebp)
.L117:
	cmpl	$0, -4(%ebp)
	jg	.L118
	movl	16(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1417:
	.size	_Z8__copy_dIPiS0_iET0_T_S2_S1_PT1_, .-_Z8__copy_dIPiS0_iET0_T_S2_S1_PT1_
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1418:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$1, 8(%ebp)
	jne	.L120
	cmpl	$65535, 12(%ebp)
	jne	.L120
	movl	$_ZStL8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, 8(%esp)
	movl	$_ZStL8__ioinit, 4(%esp)
	movl	$_ZNSt8ios_base4InitD1Ev, (%esp)
	call	__cxa_atexit
.L120:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1418:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.section	.rodata
	.align 4
	.type	_ZL10__WORD_BIT, @object
	.size	_ZL10__WORD_BIT, 4
_ZL10__WORD_BIT:
	.long	32
	.weak	_ZN23__malloc_alloc_templateILi0EE26__malloc_alloc_oom_handlerE
	.section	.bss._ZN23__malloc_alloc_templateILi0EE26__malloc_alloc_oom_handlerE,"awG",@nobits,_ZN23__malloc_alloc_templateILi0EE26__malloc_alloc_oom_handlerE,comdat
	.align 4
	.type	_ZN23__malloc_alloc_templateILi0EE26__malloc_alloc_oom_handlerE, @gnu_unique_object
	.size	_ZN23__malloc_alloc_templateILi0EE26__malloc_alloc_oom_handlerE, 4
_ZN23__malloc_alloc_templateILi0EE26__malloc_alloc_oom_handlerE:
	.zero	4
	.weak	_ZN24__default_alloc_templateILb0ELi0EE9free_listE
	.section	.bss._ZN24__default_alloc_templateILb0ELi0EE9free_listE,"awG",@nobits,_ZN24__default_alloc_templateILb0ELi0EE9free_listE,comdat
	.align 32
	.type	_ZN24__default_alloc_templateILb0ELi0EE9free_listE, @gnu_unique_object
	.size	_ZN24__default_alloc_templateILb0ELi0EE9free_listE, 64
_ZN24__default_alloc_templateILb0ELi0EE9free_listE:
	.zero	64
	.weak	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE
	.section	.bss._ZN24__default_alloc_templateILb0ELi0EE10start_freeE,"awG",@nobits,_ZN24__default_alloc_templateILb0ELi0EE10start_freeE,comdat
	.align 4
	.type	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, @gnu_unique_object
	.size	_ZN24__default_alloc_templateILb0ELi0EE10start_freeE, 4
_ZN24__default_alloc_templateILb0ELi0EE10start_freeE:
	.zero	4
	.weak	_ZN24__default_alloc_templateILb0ELi0EE8end_freeE
	.section	.bss._ZN24__default_alloc_templateILb0ELi0EE8end_freeE,"awG",@nobits,_ZN24__default_alloc_templateILb0ELi0EE8end_freeE,comdat
	.align 4
	.type	_ZN24__default_alloc_templateILb0ELi0EE8end_freeE, @gnu_unique_object
	.size	_ZN24__default_alloc_templateILb0ELi0EE8end_freeE, 4
_ZN24__default_alloc_templateILb0ELi0EE8end_freeE:
	.zero	4
	.weak	_ZN24__default_alloc_templateILb0ELi0EE9heap_sizeE
	.section	.bss._ZN24__default_alloc_templateILb0ELi0EE9heap_sizeE,"awG",@nobits,_ZN24__default_alloc_templateILb0ELi0EE9heap_sizeE,comdat
	.align 4
	.type	_ZN24__default_alloc_templateILb0ELi0EE9heap_sizeE, @gnu_unique_object
	.size	_ZN24__default_alloc_templateILb0ELi0EE9heap_sizeE, 4
_ZN24__default_alloc_templateILb0ELi0EE9heap_sizeE:
	.zero	4
	.text
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB1419:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$65535, 4(%esp)
	movl	$1, (%esp)
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1419:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 4
	.long	_GLOBAL__sub_I_main
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
