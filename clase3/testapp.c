/*
 * testapp.c
 *
 *  Created on: Sep 14, 2019
 *      Author: dadmin
 */


#include "xil_printf.h"
#include "sleep.h"
#include "xparameters.h"
#include "xscugic.h"
#include "xil_io.h"

#define BASE_ADDR 		0X43C10000
#define PS_INTR_ID 		XPAR_PS7_SCUGIC_0_DEVICE_ID
#define DEVICE_INTR_ID 	XPAR_FABRIC_GPIOINTR_0_IRQ_INTR
#define PINREADADDR		XPAR_GPIOINTR_0_S00_AXI_BASEADDR


static void handler(void *Pointer);
int InterruptSetup(XScuGic *Instance, u16 PSDeviceID, u16 DeviceID);

int main (void){
	XScuGic InterruptInstance;
	xil_printf("Iniciando el Programa\r\n");

	//Configurando Interrupcion
	xil_printf("Configurando Interrupciones\r\n");
	int status = InterruptSetup(&InterruptInstance,PS_INTR_ID,DEVICE_INTR_ID);
	if(status != XST_SUCCESS) return XST_FAILURE;

	while(1){
		/*status = Xil_In32(BASE_ADDR + 0x10);
		xil_printf("Main, Pen: %x, En: %x, Stat: %x, GE: %x\r\n",
					status,
					Xil_In32(BASE_ADDR + 0x4),
					Xil_In32(BASE_ADDR + 0x8),
					Xil_In32(BASE_ADDR));
		sleep(2);
		*/
	}
	return 0;
}

static void handler(void *Pointer){
	Xil_Out32(BASE_ADDR+0x4,0x0);//IntrDisable

	xil_printf("Interrupcion:\r\n Valor Pines %d\r\n",Xil_In32(PINREADADDR));

	Xil_Out32(BASE_ADDR+0xc,0x1);//IntrAck
	Xil_Out32(BASE_ADDR+0x4,0x1);//IntrEn
}
int InterruptSetup(XScuGic *Instance, u16 PSDeviceID, u16 DeviceID){
	XScuGic_Config *IntConfig;
	int status;

	//ConfigInterrupt Instance
	IntConfig = XScuGic_LookupConfig(PSDeviceID);
	status = XScuGic_CfgInitialize(Instance, IntConfig, IntConfig->CpuBaseAddress);
	if(status != XST_SUCCESS) return XST_FAILURE;

	//Configure Exception Handlers
	Xil_Out32(BASE_ADDR+0x4,0x1);//IntrEn
	Xil_Out32(BASE_ADDR,0x1);//IntrGlobalEn

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			 	 	 	 	 	 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
			 	 	 	 	 	 Instance);
	Xil_ExceptionEnable();
	//Configure Handler

	status = XScuGic_Connect(Instance,
					  	  	 DeviceID,
					  	  	 (Xil_ExceptionHandler)handler,
					  	  	 (void *)Instance);
	if(status != XST_SUCCESS) return XST_FAILURE;


	Xil_Out32(BASE_ADDR+0x4,0x1);//IntrEn
	Xil_Out32(BASE_ADDR,0x1);//IntrGlobalEn
	XScuGic_Enable(Instance, DeviceID);
	return XST_SUCCESS;
}
