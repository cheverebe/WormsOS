#include "tss.h"
#include "i386.h"
#include "gdt.h"
#include "mmu.h"

#define TASKIDLE      0x12000


tss tarea_idle = (tss) { 0 };
tss tarea_inicial;

tss tsss[TSS_COUNT];

void descriptorTss(int indice, tss * dirTss){
    unsigned int limit = sizeof(*dirTss) - 1;

    gdt[indice].limit_0_15=(unsigned short)(limit);
    gdt[indice].base_0_15=(unsigned short)(unsigned int)(dirTss);
    gdt[indice].base_23_16 = (unsigned char)(unsigned int)(dirTss) >> 16;
    gdt[indice].type=0x9;
    gdt[indice].s=0x0;
    gdt[indice].dpl=0x0;
    gdt[indice].p=0x1;
    gdt[indice].limit_16_19=(unsigned char)(unsigned int)(limit) >> 16;
    gdt[indice].avl=(unsigned char)0x1;
    gdt[indice].l=(unsigned char)0x0;
    gdt[indice].db=(unsigned char)0x0;
    gdt[indice].g=(unsigned char)0x1;
    gdt[indice].base_31_24=(unsigned char)(unsigned int)(dirTss) >> 24;
}

void inicializar_tarea_inicial(){
    descriptorTss(7,&tarea_inicial);
}

void inicializar_tarea_idle(){
    unsigned int v_cr3= rcr3();

    unsigned int pila = pagina_libre_kernel();
    //calculo la pos mas alta dentro de la pagina
    pila=pila+TAMANO_PAGINA;

    tarea_idle.cr3 = v_cr3;
    tarea_idle.eip = 0x00012000;
    tarea_idle.eflags = 0x202;
    tarea_idle.esp = (unsigned int) pila;
    tarea_idle.ebp = (unsigned int) pila;
    tarea_idle.cs = (unsigned short)0x30;         //0011-0000 segmento CODIGo
    tarea_idle.ss = (unsigned short)0x20;         //0011-0000 segmento DATOS
    tarea_idle.ds = (unsigned short)0x20;         //0010-0000 segmento DATOS
    tarea_idle.gs = (unsigned short)0x20;         //0010-0000 segmento DATOS
    tarea_idle.es = (unsigned short)0x20;         //0010-0000 segmento DATOS
    tarea_idle.fs = (unsigned short)0x10;         //0010-0000 segmento VIDEP

    descriptorTss(8,&tarea_idle);
}

void inicializar_tareas_worm(){

    unsigned int v_cr3= inicializar_dir_usuario();

    unsigned int pila = pagina_libre_usuario();

    //mapear_pagina(TASKWORMP_VIR,v_cr3,pila);           //PILA

    //calculo la pos mas alta dentro de la pagina
    //pila=pila+TAMANO_PAGINA;

    mapear_pagina(TASKWORMC_VIR,v_cr3,TASKWORMC);      //CODIGO
    mapear_pagina(TASKWORMD_VIR,v_cr3,TASKWORMD);      //DATOS
    mapear_pagina(TASKWORMP_VIR,v_cr3,pila);           //PILA

    tsss[0] = (tss){
        .ptl        = (unsigned short)0x00,
        .unused0    = (unsigned short)0x00,
        .esp0       = (unsigned int)TASKWORMP_VIR+TAMANO_PAGINA,
        .ss0        = (unsigned short)0x20,
        .unused1    = (unsigned short)0x00,
        .esp1       = (unsigned int)0x0000,
        .ss1        = (unsigned short)0x00,
        .unused2    = (unsigned short)0x00,
        .esp2       = (unsigned int)0x0000,
        .ss2        = (unsigned short)0x00,
        .unused3    = (unsigned short)0x00,
        .cr3        = v_cr3,
        .eip        = (unsigned int)TASKWORMC_VIR,
        .eflags     = (unsigned int)0x202,
        .eax        = (unsigned int)0x0000,
        .ecx        = (unsigned int)0x0000,
        .edx        = (unsigned int)0x0000,
        .ebx        = (unsigned int)0x0000,
        .esp        = (unsigned int)TASKWORMP_VIR+TAMANO_PAGINA,
        .ebp        = (unsigned int)TASKWORMP_VIR+TAMANO_PAGINA,
        .esi        = (unsigned int)0x0000,
        .edi        = (unsigned int)0x0000,
        .es         = (unsigned short)0x20,
        .unused4    = (unsigned short)0x00,
        .cs         = (unsigned short)0x30,         //0011-0000 segmento CODIGo USUARIO
        .unused5    = (unsigned short)0x00,
        .ss         = (unsigned short)0x20,         //0010-0000 segmento PILA USUARIO
        .unused6    = (unsigned short)0x00,
        .ds         = (unsigned short)0x20,         //0010-0000 segmento DATOS USUARIO
        .unused7    = (unsigned short)0x00,
        .fs         = (unsigned short)0x10,
        .unused8    = (unsigned short)0x00,
        .gs         = (unsigned short)0x20,
        .unused9    = (unsigned short)0x00,
        .ldt        = (unsigned short)0x00,
        .unused10   = (unsigned short)0x00,
        .dtrap      = (unsigned short)0x00,
        .iomap      = (unsigned short)0x00,
    };
    int i;
    for(i=0;i<10;i++)
        descriptorTss(9+i,(tss*)((unsigned int)&tsss)+4*i);

}


