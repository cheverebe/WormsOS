#include "gdt.h"
#include "tss.h"

gdt_entry gdt[GDT_COUNT] = {
	/* Descriptor nulo*/
	(gdt_entry){(unsigned int) 0x00000000, (unsigned int) 0x00000000 },
	/* Descriptor nulo*/
	(gdt_entry){(unsigned int) 0x00000000, (unsigned int) 0x00000000 },
	//Descriptor de video
	(gdt_entry){
		.limit_0_15=(unsigned short)0xf9f,
		.base_0_15=(unsigned short)0x8000,
		.base_23_16=(unsigned char)0x0b,
		.type=(unsigned char)0x2,
		.s=(unsigned char)0x1,
		.dpl=(unsigned char)0x00,
		.p=(unsigned char)0x1,
		.limit_16_19=(unsigned char)0,
		.avl=(unsigned char)0x1,
		.l=(unsigned char)0x0,
		.db=(unsigned char)0x1,
		.g=(unsigned char)0x0,
		.base_31_24=(unsigned char)0x0,
		},
	/* Descriptor nulo*/
	(gdt_entry){(unsigned int) 0x00000000, (unsigned int) 0x00000000 },
	//Descriptor de datos
	(gdt_entry){
		.limit_0_15=(unsigned short)0xffff,
		.base_0_15=(unsigned short)0x00,
		.base_23_16=(unsigned char)0x00,
		.type=(unsigned char)0x2,
		.s=(unsigned char)0x1,
		.dpl=(unsigned char)0x00,
		.p=(unsigned char)0x1,
		.limit_16_19=(unsigned char)0xf,
		.avl=(unsigned char)0x1,
		.l=(unsigned char)0x0,
		.db=(unsigned char)0x1,
		.g=(unsigned char)0x1,
		.base_31_24=(unsigned char)0x00,
		},
	/* Descriptor nulo*/
	(gdt_entry){(unsigned int) 0x00000000, (unsigned int) 0x00000000 },
	//Descriptor de código
	(gdt_entry){
		.limit_0_15=(unsigned short)0xffff,
		.base_0_15=(unsigned short)0x00,
		.base_23_16=(unsigned char)0x00,
		.type=(unsigned char)0xa,
		.s=(unsigned char)0x1,
		.dpl=(unsigned char)0x00,
		.p=(unsigned char)0x1,
		.limit_16_19=(unsigned char)0xf,
		.avl=(unsigned char)0x1,
		.l=(unsigned char)0x0,
		.db=(unsigned char)0x1,
		.g=(unsigned char)0x1,
		.base_31_24=(unsigned char)0x00,
		}

};

unsigned int armar_base(gdt_entry entrada){
	unsigned int base2;
	unsigned int base = entrada.base_31_24;
	base = base << 24;
	base2 = entrada.base_23_16;
	base2 = base2 << 16;
	base += base2;
	base2 = entrada.base_0_15;
	base += base2;
	return base;
}

gdt_descriptor GDT_DESC = {sizeof(gdt)-1, (unsigned int)&gdt};
