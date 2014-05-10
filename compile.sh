#!/bin/bash
#cp /home/fhntop/.gvfs/tp3\ on\ thecore/* .
#cd src

#cd final
#make clean
#make
#if [ $? == "0" ]; then
	#clear

	#cd ..
	make clean
	make

	if [ $? == "0" ]; then
		clear
		if [ -f "../../../bochs-2.4.6/bin/bochs" ]; then
			../../../bochs-2.4.6/bin/bochs -q
		else
			../../bochs-2.4.6/bin/bochs -q
		fi
	fi
	cd ..
#fi

#clear
#nasm -fbin kernel.asm -okernel.bin
#mcopy -o -i diskette.img kernel.bin ::/
#../../../bochs-2.4.6/bin/bochs -q
