#ifndef __SCHED_H__
#define __SCHED_H__

#include "tss.h"
#include "gdt.h"
#include "mmu.h"
#include "i386.h"

#define CANT_TAREAS 10

extern unsigned short tareas[CANT_TAREAS];


void inicializar_scheduler();
unsigned short proximo_indice();
void cambiar_a_tarea(unsigned short n);
void duplicar_proceso(unsigned int geip,  unsigned int ebp_orig, unsigned int flags_orig, unsigned int edx_orig, unsigned int esi_orig,  unsigned int edi_orig,  unsigned int ecx_orig, unsigned int ebx_orig, unsigned int esp_orig);
void eliminar_tarea_actual();
unsigned int get_eip();
void prender_indice(unsigned int indice);
void apagar_indice(unsigned int indice);
#endif
