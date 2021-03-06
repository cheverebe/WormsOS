#include "sched.h"



unsigned short tareas[CANT_TAREAS];
char tareas_presentes[CANT_TAREAS];

void inicializar_scheduler() {
	int i;
	for(i=0; i<CANT_TAREAS; i++){
		unsigned short pos = 9+i;
		tareas[i]=pos;
		tareas_presentes[i]=0;
	}
	tareas_presentes[0]=1;
	prender_indice(0);
}

unsigned short ind_gdt_tarea_actual(){
	return rtr() >> 3;
}
char hay_worms(){
	int i;
	for(i=0; i<10; i++){
		if(tareas_presentes[i]==1){
			return 1;
		}
	}
	return 0;
}

unsigned short lugar_libre(){
	unsigned short i;
	for(i=0;i<10;i++){
		if (tareas_presentes[i]==0)
			return i;

	}
	return 10;
}

unsigned short next_presente(){
	unsigned short indice;
	if(hay_worms()==1){
	    if(ind_gdt_tarea_actual()==8)
            indice=0;
        else
            indice=ind_gdt_tarea_actual()-9;
		unsigned short i;
		for(i=indice+1;i<10;i++){
			if(tareas_presentes[i]==1){
				return i;
			}
		}
		for(i=0;i<=indice;i++){
			if(tareas_presentes[i]==1){
				return i;
			}
		}
	}
	return 10;
}

unsigned short proximo_indice() {
	unsigned short indice;
	if(hay_worms()){
		indice = next_presente();
		return tareas[indice];
	}
	else{
		return 8;
	}
}

unsigned int mostrar(unsigned int param){
    return param;
}

void copiar_pagina(unsigned int origen, unsigned int destino){
	unsigned int * orig=(unsigned int*)origen;
	unsigned int * dest=(unsigned int*)destino;
	unsigned int i;
	for(i=0; i<1024; i++){
	    dest[i]=orig[i];

	}
}

void copiar_tss(tss* original, tss* nuevo){
	nuevo->ptl = original->ptl;
    nuevo->cs  = original->cs;
    nuevo->ds  = original->ds;
    nuevo->fs  = original->fs;
    nuevo->gs  = original->gs;
    nuevo->es  = original->es;
    nuevo->ss  = original->ss;
    nuevo->ss0  = original->ss0;
}

void duplicar_proceso_aux(tss* tarea,unsigned int ip,  unsigned int ebp_orig, unsigned int flags_orig, unsigned int edx_orig, unsigned int esi_orig,  unsigned int edi_orig,  unsigned int ecx_orig, unsigned int ebx_orig, unsigned int esp_orig){


	unsigned short libre = lugar_libre();
    if(libre!=10){
        tareas_presentes[libre]=1;
	prender_indice(libre);
        unsigned short indice = (unsigned short) tareas[libre];
		tss *duplicado = (tss*)armar_base(gdt[indice]);
        copiar_tss(tarea,duplicado);

        unsigned int pila = pagina_libre_usuario();
        mapear_pagina(pila, tarea->cr3, pila);

        unsigned int pagina_pila = TASKWORMP_VIR;
        copiar_pagina(pagina_pila,pila);

        unsigned int pagina_codigo = pagina_libre_usuario();
        mapear_pagina(pagina_codigo,tarea->cr3,pagina_codigo);

        unsigned int origen_codigo=TASKWORMC_VIR;
        copiar_pagina(origen_codigo,pagina_codigo);

        unsigned int pagina_datos =  pagina_libre_usuario();
        mapear_pagina(pagina_datos,tarea->cr3,pagina_datos);

        unsigned int origen_datos=TASKWORMD_VIR;
        copiar_pagina(origen_datos,pagina_datos);

        duplicado->cr3=inicializar_dir_usuario();
        mapear_pagina(TASKWORMC_VIR,duplicado->cr3,pagina_codigo);
        mapear_pagina(TASKWORMD_VIR,duplicado->cr3,pagina_datos);
        mapear_pagina(TASKWORMP_VIR,duplicado->cr3,pila);
        duplicado->eax = 1;
        duplicado->eip = ip;
        duplicado->esi = esi_orig;
        duplicado->edi = edi_orig;
        duplicado->ebx = ebx_orig;
        duplicado->edx = edx_orig;
        duplicado->ecx = ecx_orig;
        duplicado->eflags = flags_orig;

        duplicado->esp = esp_orig;
        duplicado->ebp = ebp_orig;
    }
}

void duplicar_proceso(unsigned int geip,  unsigned int ebp_orig, unsigned int flags_orig, unsigned int edx_orig, unsigned int esi_orig,  unsigned int edi_orig,  unsigned int ecx_orig, unsigned int ebx_orig, unsigned int esp_orig){
    unsigned short indice = ind_gdt_tarea_actual();
    tss * ts = (tss*)armar_base(gdt[indice]);

    duplicar_proceso_aux(ts, geip, ebp_orig, flags_orig, edx_orig, esi_orig, edi_orig, ecx_orig, ebx_orig, esp_orig);
    //VER A DONDE APUNTAR EL EIP
    //DAR DE ALTA EN EL SCHEDULER
}

void eliminar_proceso(unsigned int pid){
/*	if(ind_gdt_tarea_actual()-9==pid){
			unsigned short prox_indice = proximo_indice();
			if(prox_indice==pid){
                cambiar_a_tarea(8);
			}else{
                cambiar_a_tarea(prox_indice);
			}
		}*/
	tareas_presentes[pid]=0;
	apagar_indice(pid);
}
void eliminar_tarea_actual(){
	unsigned short indice = ind_gdt_tarea_actual()-9;
	eliminar_proceso(indice);
}
