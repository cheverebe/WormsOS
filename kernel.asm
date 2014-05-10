BITS 16

;%include "macrosmodoreal.mac"
%include "macrosmodoprotegido.mac"

%define KORG 0x1200

global start
global funcionPrueba
extern tsss
extern gdt
extern GDT_DESC
extern IDT_DESC
extern inicializar_idt
extern inicializar_dir_kernel
extern inicializar_dir_usuario
extern inicializar_mmu
extern resetear_pic
extern habilitar_pic
extern inicializar_tarea_idle
extern inicializar_tarea_inicial
extern inicializar_tareas_worm
extern inicializar_scheduler
;Aca arranca todo, en el primer byte.
start:
		cli ;no me interrumpan por ahora
		;xchg bx, bx
		jmp bienvenida

;aca ponemos todos los mensajes
iniciando: db 'Iniciando el kernel'
iniciando_len equ $ - iniciando

numeros: db '0123456789'
numeros_len equ $ - numeros

nombre: db 'Fally Farson'
nombre_len equ $ - nombre

;offset: dd 0
;selector: dw 0

%define indice_idle 0x40:0x0

bienvenida:

		;IMPRIMIR_MODO_REAL iniciando, iniciando_len, 0x07, 0, 0

		;Habilitar A20
		call habilitar_A20
		;Dehsabilitar las interrupciones
		cli
		;Pasar a modo protegido
		lgdt [GDT_DESC]


		mov eax, cr0
		or eax, 1
		mov cr0, eax
		jmp 0x30:modo_protegido				;saltamos a modo protegido




BITS 32
modo_protegido:
;CARGO LOS SELECTORES DE SEGMENTO
		xor eax, eax
		mov ax, 0x10			;cargo el selector de video en ax
		mov fs, ax				; fs=selector de video
		mov ax, 0x20			;cargo el selector de datos
		mov ds, ax				;ds=selector de datos
		mov es, ax				;ds=selector de datos
		mov gs, ax				;ds=selector de datos
		mov ss, ax				;ss=selector de datos

		mov esp, 0x18000
		mov ebp, 0x18000

;IMPRIMO EN PANTALLA
		xor eax, eax
		mov ecx, 70

		primera_fila:
			mov word [fs:eax], 0xffff
			add eax, 2
			loop primera_fila


				IMPRIMIR_TEXTO numeros, numeros_len, 0x70, 0, 70

;		xchg bx,bx

		mov eax, 80*2
		mov ecx, 80*25-160
		pantalla_negra:
			mov word [fs:eax], 0x0000
			add eax, 2
			loop pantalla_negra

;		xchg bx,bx

		mov eax, 24*80*2
		mov ecx, 80
		ultima_linea:
			mov word [fs:eax], 0xffff
			add eax,2
			loop ultima_linea
;		xchg bx,bx
		;Inicializar la IDT
		call inicializar_idt

				lidt [IDT_DESC]
		;int 0

		;Habilitar paginacion

		call inicializar_dir_kernel


		mov eax, 0x00100000
		mov cr3, eax

;		xchg bx,bx

		mov eax, cr0
		or eax, 0x80000000
		mov cr0, eax

		;xchg bx, bx

		IMPRIMIR_TEXTO nombre, nombre_len, 0x70, 0, 0

;EJ 4

		call inicializar_mmu
		call inicializar_dir_usuario

		mov cr3, eax
		mov byte [fs:0x1], 0x50

		mov eax, 0x00100000
		mov cr3, eax


		;Habilitar pic
		call resetear_pic
		call habilitar_pic
		sti

		;Inicializar el scheduler de tareas
		call inicializar_tarea_inicial
		call inicializar_tarea_idle
		call inicializar_tareas_worm

		IMPRIMIR_TEXTO numeros, numeros_len, 0x70, 0, 70

		mov ax, 0x38
		ltr ax
		call inicializar_scheduler

		;sti

        ;mov ax, 40
        ;mov [selector], ax
		jmp indice_idle


		jmp $




%include "a20.asm"
