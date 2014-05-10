#ifndef __MMU_H__
#define __MMU_H__

#define INICIO_PAGINAS_KERNEL   0x00102000
#define INICIO_PAGINAS_USUARIO  0x00200000
#define TAMANO_PAGINA           0x1000

#endif

void inicializar_dir_kernel();
unsigned int inicializar_dir_usuario();
void inicializar_mmu();
unsigned int pagina_libre_kernel();
unsigned int pagina_libre_usuario();
void desmapear_pagina(unsigned int virtual, unsigned int cr3);
void mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica);


/* Struct de descriptor de pd */
typedef struct str_pagdir {
	unsigned char p:1;
	unsigned char rw:1;
	unsigned char us:1;
	unsigned char pwt:1;
	unsigned char pcd:1;
	unsigned char a:1;
	unsigned char cero:1;
	unsigned char ps:1;
	unsigned char g:1;
	unsigned char disponible:3;
	unsigned int base:20;
} __attribute__((__packed__)) pagdir;

/* Struct de descriptor de pagtable */
typedef struct str_pagtable {
	unsigned char p:1;
	unsigned char rw:1;
	unsigned char us:1;
	unsigned char pwt:1;
	unsigned char pcd:1;
	unsigned char a:1;
	unsigned char d:1;
	unsigned char pat:1;
	unsigned char g:1;
	unsigned char disponible:3;
	unsigned int base:20;
} __attribute__((__packed__)) pagtable;
/*
typedef struct str_crtres {
	unsigned char fruta:3;
	unsigned char pwt:1;
	unsigned char pcd:1;
	unsigned char mas_fruta:7;
	unsigned int base_dir:20;
} __attribute__((__packed__)) crtres;*/
//poner la base del directorio en CR3
//limpiar bits pcd y pwt del CR3
//activar paginacion con el bit 31 dwl CR0
