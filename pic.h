#ifndef __PIC_H__
#define __PIC_H__

void resetear_pic(void);
void habilitar_pic();
void deshabilitar_pic();

static __inline __attribute__((always_inline)) void outb(int port, unsigned char data);

__inline __attribute__((always_inline)) void fin_intr_pic1(void);
__inline __attribute__((always_inline)) void fin_intr_pic2(void);

#endif
