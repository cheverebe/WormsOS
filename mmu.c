#include "mmu.h"
#include "i386.h"
#define ALIGNED(dir) (dir & ~0xFFF)

//extern void funcionPrueba(pagtable* dirtabla);
//pimer pagina libre 0x00102000.

unsigned int ultima_libre_kernel;
unsigned int ultima_libre_usuario;

void inicializar_mmu(){
    ultima_libre_kernel=(unsigned int)INICIO_PAGINAS_KERNEL;
    ultima_libre_usuario=(unsigned int)INICIO_PAGINAS_USUARIO;
}
unsigned int pagina_libre_kernel(){
    unsigned int pagina_a_devolver = ultima_libre_kernel;
    ultima_libre_kernel+= 0x1000;
    return pagina_a_devolver;
}

unsigned int pagina_libre_usuario(){
    unsigned int pagina_a_devolver = ultima_libre_usuario;
    ultima_libre_usuario+= 0x1000;
    return pagina_a_devolver;
}
void desmapear_pagina(unsigned int virtual, unsigned int cr3){
    pagdir* pd = (pagdir*) (ALIGNED(cr3));
	unsigned int direc = virtual;
	direc = direc >> 22;
	pagdir desc_dir = pd[direc];

	pagtable* dir_tabla = (pagtable*)0x00000000;
	unsigned int  dir_aux = desc_dir.base;
	if(desc_dir.p==1){
		dir_tabla=(pagtable*)dir_aux;
		dir_tabla=(pagtable*)(((unsigned int)dir_tabla) << 12);
		unsigned int ind_table = virtual;
        ind_table=ind_table >> 12;
        ind_table = virtual & (0x000003ff);
		dir_tabla[ind_table].p=0;
	}
	tlbflush();

}

void mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica){

	pagdir* pd = (pagdir*) (ALIGNED(cr3));
	unsigned int direc = virtual;
	direc = direc >> 22;
	pagdir* desc_dir = &pd[direc];

	pagtable* dir_tabla = (pagtable*)0x00000000;
	//pagtable tabla;
	unsigned int  dir_aux = desc_dir->base;

	if(desc_dir->p==1){
		dir_tabla=(pagtable*)dir_aux;
		dir_tabla=(pagtable*)(((unsigned int)dir_tabla) << 12);
		//tabla = *dir_tabla;
	}else{
        //crear tabla
		dir_tabla = (pagtable*)pagina_libre_kernel();

		//tabla = *dir_tabla
        unsigned int i;
		for(i=0; i<1024; i++){
			dir_tabla[i]=(pagtable){
				.p=(unsigned char)0x00,
				.rw=(unsigned char)0x01,
				.us=(unsigned char)0x00,
				.pwt=(unsigned char)0x00,
				.pcd=(unsigned char)0x00,
				.a=(unsigned char)0x00,
				.d=(unsigned char)0x00,
				.pat=(unsigned char)0x00,
				.g=(unsigned char)0x00,
				.disponible=(unsigned char)0x00,
				.base=(unsigned int)i,
			};
		}
			//poner descriptor presente del directory
		desc_dir->p = 0x01;
		desc_dir->rw = 0x01;
		dir_tabla=(pagtable*)(((unsigned int)dir_tabla) >> 12);
		desc_dir->base = (unsigned int)dir_tabla;
		dir_tabla=(pagtable*)(((unsigned int)dir_tabla) << 12);
	}
    //funcionPrueba(dir_tabla);
	//aca tengo en desc_table la page table
	//poner presente la pagina en la tabla y mapear

	unsigned int ind_table = virtual;
	ind_table=ind_table >> 12;
	ind_table = ind_table & (0x000003ff);
	dir_tabla[ind_table] = (pagtable){
			.p=(unsigned char)0x01,
			.rw=(unsigned char)0x01,
			.us=(unsigned char)0x00,
			.pwt=(unsigned char)0x00,
			.pcd=(unsigned char)0x00,
			.a=(unsigned char)0x00,
			.d=(unsigned char)0x00,
			.pat=(unsigned char)0x00,
			.g=(unsigned char)0x00,
			.disponible=(unsigned char)0x00,
			.base=(unsigned int)fisica>>12,
		};
	tlbflush();

}
//definir la tabla y el directorio con un arreglo
void inicializar_dir_kernel()
 {
	pagdir* directorio = (pagdir*)0x00100000;
    pagtable* tabla = (pagtable*)0x00101000;
    unsigned int tabla_ptr= 0x00101;


	directorio[0]=(pagdir){
		.p=(unsigned char)0x01,
		.rw=(unsigned char)0x01,
		.us=(unsigned char)0x00,
		.pwt=(unsigned char)0x00,
		.pcd=(unsigned char)0x00,
		.a=(unsigned char)0x00,
		.cero=(unsigned char)0x00,
		.ps=(unsigned char)0x00,
		.g=(unsigned char)0x00,
		.disponible=(unsigned char)0x00,
		.base=(unsigned int)tabla_ptr,
	};
    unsigned int i;
	for(i=1; i<1024; i++){
		directorio[i]=(pagdir){
		.p=(unsigned char)0x00,
		.rw=(unsigned char)0x00,
		.us=(unsigned char)0x00,
		.pwt=(unsigned char)0x00,
		.pcd=(unsigned char)0x00,
		.a=(unsigned char)0x00,
		.cero=(unsigned char)0x00,
		.ps=(unsigned char)0x00,
		.g=(unsigned char)0x00,
		.disponible=(unsigned char)0x00,
		.base=(unsigned int)0x00,
		};
	}
	for(i=0; i<1024; i++){
		tabla[i]=(pagtable){
			.p=(unsigned char)0x01,
			.rw=(unsigned char)0x01,
			.us=(unsigned char)0x00,
			.pwt=(unsigned char)0x00,
			.pcd=(unsigned char)0x00,
			.a=(unsigned char)0x00,
			.d=(unsigned char)0x00,
			.pat=(unsigned char)0x00,
			.g=(unsigned char)0x00,
			.disponible=(unsigned char)0x00,
			.base=(unsigned int)i,
		};
	}
}

unsigned int inicializar_dir_usuario(){
    pagdir* directorio = (pagdir*)pagina_libre_kernel();
    unsigned int i;
	for(i=0; i<1024; i++){
		directorio[i]=(pagdir){
		.p=(unsigned char)0x00,
		.rw=(unsigned char)0x00,
		.us=(unsigned char)0x00,
		.pwt=(unsigned char)0x00,
		.pcd=(unsigned char)0x00,
		.a=(unsigned char)0x00,
		.cero=(unsigned char)0x00,
		.ps=(unsigned char)0x00,
		.g=(unsigned char)0x00,
		.disponible=(unsigned char)0x00,
		.base=(unsigned int)0x00,
		};
	}
	unsigned int cr3=(unsigned int)directorio;
	for(i=0x00000000;i<=0x001FFFFF;i+=TAMANO_PAGINA){
        mapear_pagina(i,cr3,i);

	}
    return cr3;

}




