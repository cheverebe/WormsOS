BITS 32
%include "macrosmodoprotegido.mac"

extern fin_intr_pic1
extern ind_gdt_tarea_actual
extern proximo_indice
extern duplicar_tarea_actual
extern eliminar_tarea_actual
extern ind_gdt_tarea_actual
extern duplicar_proceso
extern eliminar_proceso

offset: dd 0
selector: dw 0

isr0: db "Division por 0"
isr0_len equ $ - isr0

isr1: db "RESERVADO"
isr1_len equ $ - isr1

isr2: db "Interrupcion no enmascarable"
isr2_len equ $ - isr2

isr3: db "Breakpoint"
isr3_len equ $ - isr3

isr4: db "Overflow"
isr4_len equ $ - isr4

isr5: db "BOUND Range Exceeded"
isr5_len equ $ - isr5

isr6: db "Opcode invalido"
isr6_len equ $ - isr6

isr7: db "Dispositivo no disponible"
isr7_len equ $ - isr7

isr8: db "Doble falta"
isr8_len equ $ - isr8

isr9: db " Coprocessor Segment Overrun"
isr9_len equ $ - isr9

isr10: db "TSS invalido"
isr10_len equ $ - isr10

isr11: db "Segmento no presente"
isr11_len equ $ - isr11

isr12: db "Falta de segmento de pila"
isr12_len equ $ - isr12

isr13: db "Proteccion general"
isr13_len equ $ - isr13

isr14: db "Falta de pagina"
isr14_len equ $ - isr14

isr15: db "Reservado para intel"
isr15_len equ $ - isr15

isr16: db "x87 FPU Floating-Point Error (Math Fault)"
isr16_len equ $ - isr16

isr17: db "Alignment Check"
isr17_len equ $ - isr17

isr18: db "Machine Check"
isr18_len equ $ - isr18

isr19: db "SIMD Floating-Point Exception"
isr19_len equ $ - isr19

_eax: db "EAX"
_eax_len equ $ - _eax

_ebx: db "EBX"
_ebx_len equ $ - _ebx

_ecx: db "ECX"
_ecx_len equ $ - _ecx

_edx: db "EDX"
_edx_len equ $ - _edx

_esi: db "ESI"
_esi_len equ $ - _esi

_edi: db "EDI"
_edi_len equ $ - _edi

_ebp: db "EBP"
_ebp_len equ $ - _ebp

_esp: db "ESP"
_esp_len equ $ - _esp

_cs: db "CS"
_cs_len equ $ - _cs

_ds: db "DS"
_ds_len equ $ - _ds

_es: db "ES"
_es_len equ $ - _es

_fs: db "FS"
_fs_len equ $ - _fs

_gs: db "GS"
_gs_len equ $ - _gs

_ss: db "SS"
_ss_len equ $ - _ss

_cr0: db "CR0"
_cr0_len equ $ - _cr0

_cr2: db "CR2"
_cr2_len equ $ - _cr2

_cr3: db "CR3"
_cr3_len equ $ - _cr3

_cr4: db "CR4"
_cr4_len equ $ - _cr4

pila: db "STACK"
pila_len equ $ - pila

backtrace: db "BACKTRACE"
backtrace_len equ $ - backtrace

_eflags: db "EFLAGS"
eflags_len equ $ - _eflags

valor_reg: db "aaaaaaaa"
valor_reg_len equ $ - valor_reg

teclado: db "aaaa"
teclado_len equ $ - teclado

f: db "F"

cantidad_ticks: dd 0x2

global _isr0
global _isr1
global _isr2
global _isr3
global _isr4
global _isr5
global _isr6
global _isr7
global _isr8
global _isr9
global _isr10
global _isr11
global _isr12
global _isr13
global _isr14
global _isr15
global _isr16
global _isr17
global _isr18
global _isr19
global _isr32
global _isr33
global _isr66
global _isr77
global _isr88
global _isr99

global prender_indice
global apagar_indice
global cambiar_a_tarea
global get_eip

_isr0:
IMPRIMIR_TEXTO isr0, isr0_len, 0x0a, 1, 0
call imprimir_registros
jmp $

_isr1:
IMPRIMIR_TEXTO isr1, isr1_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr2:
IMPRIMIR_TEXTO isr2, isr2_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr3:
IMPRIMIR_TEXTO isr3, isr3_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr4:
IMPRIMIR_TEXTO isr4, isr4_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr5:
IMPRIMIR_TEXTO isr5, isr5_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr6:
IMPRIMIR_TEXTO isr6, isr6_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr7:
IMPRIMIR_TEXTO isr7, isr7_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr8:
IMPRIMIR_TEXTO isr8, isr8_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr9:
IMPRIMIR_TEXTO isr9, isr9_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr10:
IMPRIMIR_TEXTO isr10, isr10_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr11:
IMPRIMIR_TEXTO isr11, isr11_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr12:
IMPRIMIR_TEXTO isr12, isr12_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr13:
IMPRIMIR_TEXTO isr13, isr13_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr14:
;xchg bx, bx
IMPRIMIR_TEXTO isr14, isr14_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr15:
IMPRIMIR_TEXTO isr15, isr15_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr16:
IMPRIMIR_TEXTO isr16, isr16_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr17:
IMPRIMIR_TEXTO isr17, isr17_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr18:
IMPRIMIR_TEXTO isr18, isr18_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr19:
IMPRIMIR_TEXTO isr19, isr19_len, 0x0A, 1, 0
call imprimir_registros
jmp $

_isr32:
pushad
pushfd

;incrementar_reloj
mov ebx, [cantidad_ticks]
inc ebx
mov [cantidad_ticks], ebx

call proximo_reloj

call proximo_indice

mov bx, ax

call ind_gdt_tarea_actual
cmp bx, ax

je no_cambio
shl bx, 3
mov [selector], bx
call fin_intr_pic1
;xchg bx,bx
jmp far [offset]
jmp end

no_cambio:
call fin_intr_pic1

end:

popfd
popad
iret

_isr33:
pushad
pushfd


in al, 0x60

cmp al, 0x0b
ja fin_teclado
je zero

xor ebx, ebx
mov bl, al
dec ebx
push ebx
call eliminar_tarea
pop ebx
jmp mostrar_num

zero:
xor ebx, ebx
push ebx
call eliminar_tarea
pop ebx

mostrar_num:
push ebx
call prender_numero
pop ebx

call ind_gdt_tarea_actual
xor ecx, ecx
mov cx, ax
sub ecx, 9
cmp ebx, ecx
jne fin_teclado

;xchg bx, bx
;shl ax, 3
;mov [selector], ax
;call fin_intr_pic1
;jmp far [offset]

fin_teclado:
call fin_intr_pic1
popfd
popad
iret


_isr66:
;mov eax, 666
;iret


push esp
push ebx
push ecx
push edi
push esi
push edx
pushfd
push ebp
push no_duplico

call duplicar_proceso

mov eax, 0
;xchg bx, bx
add esp, 4
pop ebp
popfd
pop edx
pop esi
pop edi
pop ecx
pop ebx
pop esp

call fin_intr_pic1

iret


no_duplico:
mov eax, 1
;xchg bx, bx

;call fin_intr_pic1

iret

_isr77:
;mov eax, 777
;iret

pushad
; bx,bx
pushf
;mov eax, 777
call eliminar_tarea_actual

call proximo_indice
shl ax, 3
mov [selector], ax
call fin_intr_pic1
jmp far [offset]

popf
popad
iret

_isr88_aux: dd 0
_isr88:
;mov eax, 1;
;iret
pushad

call ind_gdt_tarea_actual
cmp ax, 8
jne worm
xor eax,eax
mov ax, 10
jmp fin_tareas

worm:
sub ax, 9
xor ebx,ebx
mov bx, ax
mov eax, ebx

fin_tareas:
mov [_isr88_aux], eax
popad
mov eax, [_isr88_aux]
iret

_isr99:
mov eax, [cantidad_ticks]
iret

imprimir_registros:

;EAX
IMPRIMIR_TEXTO _eax, _eax_len, 0x0a, 3, 1

DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 3, 10

;CS
IMPRIMIR_TEXTO _cs, _cs_len, 0x0a, 3, 26

DWORD_TO_HEX cs, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 3, 33

;EBX
IMPRIMIR_TEXTO _ebx, _ebx_len, 0x0a, 4, 1

DWORD_TO_HEX ebx, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 4, 10

;DS
IMPRIMIR_TEXTO _ds, _ds_len, 0x0a, 4, 26

DWORD_TO_HEX ds, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 4, 33

;ECX
IMPRIMIR_TEXTO _ecx, _ecx_len, 0x0a, 5, 1

DWORD_TO_HEX ecx, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 5, 10

;ES
IMPRIMIR_TEXTO _es, _es_len, 0x0a, 5, 26

DWORD_TO_HEX es, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 5, 33

;EDX
IMPRIMIR_TEXTO _edx, _edx_len, 0x0a, 6, 1

DWORD_TO_HEX edx, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 6, 10

;FS
IMPRIMIR_TEXTO _fs, _fs_len, 0x0a, 6, 26

DWORD_TO_HEX fs, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 6, 33

;ESI
IMPRIMIR_TEXTO _esi, _esi_len, 0x0a, 7, 1

DWORD_TO_HEX esi, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 7, 10

;GS
IMPRIMIR_TEXTO _gs, _gs_len, 0x0a, 7, 26

DWORD_TO_HEX gs, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 7, 33

;EDI
IMPRIMIR_TEXTO _edi, _edi_len, 0x0a, 8, 1

DWORD_TO_HEX edi, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 8, 10

;SS
IMPRIMIR_TEXTO _ss, _ss_len, 0x0a, 8, 26

DWORD_TO_HEX ss, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 8, 33

;EBP
IMPRIMIR_TEXTO _ebp, _ebp_len, 0x0a, 9, 1

DWORD_TO_HEX ebp, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 9, 10

;ESP
IMPRIMIR_TEXTO _esp, _esp_len, 0x0a, 10, 1

DWORD_TO_HEX esp, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 10, 10

;CR0
IMPRIMIR_TEXTO _cr0, _cr0_len, 0x0a, 12, 1

DWORD_TO_HEX cr0, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 12, 10

;CR2
IMPRIMIR_TEXTO _cr2, _cr2_len, 0x0a, 13, 1

DWORD_TO_HEX cr2, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 13, 10

;CR3
IMPRIMIR_TEXTO _cr3, _cr3_len, 0x0a, 14, 1

DWORD_TO_HEX cr3, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 14, 10

;CR4
IMPRIMIR_TEXTO _cr4, _cr4_len, 0x0a, 15, 1

DWORD_TO_HEX cr4, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 15, 10


;IMPRIMO LOS EFLAGS
IMPRIMIR_TEXTO _eflags, eflags_len, 0x0a, 17, 1

mov eax, [esp-8]
DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 17, 10


;IMPRIMIMOS LOS 5 VALORES DE LA PILA

IMPRIMIR_TEXTO pila, pila_len, 0x0a, 10, 26

mov eax, [esp]

DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 12, 26


mov eax, [esp+4]

DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 13, 26


mov eax, [esp+8]

DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 14, 26


mov eax, [esp+12]

DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 15, 26


mov eax, [esp+16]

DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 16, 26


;IMPRIMIMOS LAS DIRECCIONES DE RETORNO


IMPRIMIR_TEXTO backtrace, backtrace_len, 0x0a, 10, 44

mov eax, [ebp+4]
DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 12, 44

mov ebx, [ebp]

cmp esp, ebx
ja fin

cmp ebx, 0x18000
ja fin


mov eax, [ebx+4]
DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 13, 44



mov ebx, [ebx]

cmp esp, ebx
ja fin

cmp ebx, 0x18000
ja fin


mov eax, [ebx+4]
DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 14, 44


mov ebx, [ebx]

cmp esp, ebx
ja fin

cmp ebx, 0x18000
ja fin



mov eax, [ebx+4]
DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 15, 44

mov ebx, [ebx]

cmp esp, ebx
ja fin

cmp ebx, 0x18000
ja fin


mov eax, [ebx+4]
DWORD_TO_HEX eax, valor_reg
IMPRIMIR_TEXTO valor_reg, valor_reg_len, 0x0a, 16, 44

fin:
ret

proximo_reloj:
	pushad
	inc DWORD [isrnumero]
	mov ebx, [isrnumero]
	cmp ebx, 0x4
	jl .ok
		mov DWORD [isrnumero], 0x0
		mov ebx, 0
	.ok:
		add ebx, isrmensaje1
		mov edx, isrmensaje
		IMPRIMIR_TEXTO edx, 6, 0x0A, 24, 73
		IMPRIMIR_TEXTO ebx, 1, 0x0A, 24, 79
	popad
	ret

cambiar_a_tarea:
	push ebp
	mov ebp, esp
	push esi
	push edi
	push ebx

	mov eax, [ebp+8] 				;cargo el indice en esi
	shl eax, 3
	mov gs, ax

	jmp [gs:0]

	pop ebx
	pop edi
	pop esi
	pop ebp
	ret
;FIN

get_eip:
	mov eax, [ebp+4]
	ret

isrmensaje: db 'Clock:'
isrnumero: dd 0x00000000
isrmensaje1: db '|'
isrmensaje2: db '/'
isrmensaje3: db '-'
isrmensaje4: db '\'

prender_indice:
push ebp
mov ebp, esp
push esi
push edi
push ebx

mov ebx, [ebp+8]
mov edx, ebx
add ebx, 0x30

mov al, 0x40
mov [fs:edx*2+141], al
mov [fs:edx*2+140], bl

pop ebx
pop edi
pop esi
pop ebp

ret

prender_numero:
push ebp
mov ebp, esp
push esi
push edi
push ebx

mov ebx, [ebp+8]
mov edx, ebx
add ebx, 0x30

mov al, 0x0A
mov [fs:18+301], al
mov [fs:18+300], bl

pop ebx
pop edi
pop esi
pop ebp

ret

apagar_indice:
push ebp
mov ebp, esp
push esi
push edi
push ebx

mov ebx, [ebp+8]
mov al, 0x70
mov [fs:ebx*2+141], al


pop ebx
pop edi
pop esi
pop ebp

ret

eliminar_tarea:
pushad
pushf

;mov ebx, [ebp+8]

push ebx
call eliminar_proceso
add esp, 4

call ind_gdt_tarea_actual
xor ecx, ecx
mov cx, ax
sub ecx, 9
cmp ebx, ecx
jne dont_jump

call proximo_indice
shl ax, 3
mov [selector], ax

call fin_intr_pic1
jmp far [offset]

dont_jump:

popf
popad

ret
