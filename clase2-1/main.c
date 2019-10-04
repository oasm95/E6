/*
 * main.c
 *
 *  Created on: Sep 26, 2019
 *      Author: dadmin
 */
#include "xparameters.h"
#include "xil_types.h"
#include "xil_printf.h"
#include "AxiInterfaz.h"
#include "sleep.h"

#define BASEADDR XPAR_AXIINTERFAZ_0_S00_AXI_BASEADDR
void WriteReg(unsigned int *Addr,u32 Data){
	*Addr = Data;
}
u32 ReadReg(unsigned int *Addr){
	return *Addr;
}

int main(void){
	u32 data, sw;
	while(1){
		for(unsigned char i = 0; i<16;i++){
			AXIINTERFAZ_mWriteReg(BASEADDR,0,i);
			data = AXIINTERFAZ_mReadReg(BASEADDR,4);
			xil_printf("El valor de entrada: %d Salida: %d\r\n",i,data);
			//sleep(2);
		}

		sw = ReadReg(BASEADDR+8);
		xil_printf("El valor del Switch: %d \r\n",sw);
		if (sw < 7){
			WriteReg(BASEADDR + 12,0);

		}else{
			WriteReg(BASEADDR + 12,1);

		}
		sleep(1);
	}
	return 0;
}
