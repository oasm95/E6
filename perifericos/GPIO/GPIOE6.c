/*
 * GPIOE6.c
 *
 *  Created on: Oct 26, 2019
 *      Author: dadmin
 */

#include "GPIOE6.h"

/* Se utiliza para asignar la Direccion de los Pines
 * 	@Pines: Utilizar las Definiciones PIN0,PIN1 ... PIN11
 * 			En el caso de asignar direccion a un pin utilizar el operador
 * 			"|".
 * 	@Direccion: Indica si es entrada o salida
 * 				1: Entrada
 * 				0: Salida
 * Ejem. GPIOE6SetDirection(PIN0|PIN2|PIN5,0);
 * 		 Asigna los pines 0,2 y 5 como salidas.
 * */
void GPIOE6SetDirection(unsigned Pines,unsigned Direccion){
	unsigned RegValue = Xil_In32(GPIOE6_BASEADDR|GPIOE6_DIR_REG);
	if(Direccion == 0)
		Xil_Out32(GPIOE6_BASEADDR|GPIOE6_DIR_REG,RegValue&((~Pines)&0xFFF));
	else
		Xil_Out32(GPIOE6_BASEADDR|GPIOE6_DIR_REG,RegValue|Pines);
}

/* Se utiliza para escribir el valor de un solo Pin.
 * Utilizar cuando el pin este en funcion GPIO Output.
 * 	@Pin: Utilizar las Definiciones PIN0,PIN1 ... PIN11
 * 		  Solo se puede asignar a un Pin.
 * 	
 *  @Value: Valor del pin a escribir.
 *  
 *  Ejem. GPIOE6PinWrite(PIN2,0);
 * 		 Asigna al pin2 un valor de 0.
 * */
void GPIOE6PinWrite(unsigned Pin,unsigned Value){
	unsigned RegValue = Xil_In32(GPIOE6_BASEADDR|GPIOE6_DATAOUT_REG);
	if (Value)
		Xil_Out32(GPIOE6_BASEADDR|GPIOE6_DATAOUT_REG,RegValue |(Pin&0xFFF));
	else
		Xil_Out32(GPIOE6_BASEADDR|GPIOE6_DATAOUT_REG,RegValue &(~Pin));
}
/* Se utiliza para escribir un valor a todo el puerto.
 * En caso de que un pin no se encuentre en funcion GPIO Output
 * ignorara el valor escrito.
 * 	@PortValue: valor a escribir al puerto.
 * 
 * 	Ejem. GPIOE6PortWrite(0xFFF);
 * 		  Escribe '1's en todo el puerto.
 * */
void GPIOE6PortWrite(unsigned PortValue){
	Xil_Out32(GPIOE6_BASEADDR|GPIOE6_DATAOUT_REG,PortValue&0xFFF);
}

/* Se utiliza para leer el valor de un solo Pin.
 * Utilizar cuando el pin este en funcion GPIO Input.
 * 	@Pin: Utilizar las Definiciones PIN0,PIN1 ... PIN11
 * 		  Solo se puede asignar a un Pin.
 * 	
 *  @return: Valor del pin.
 *   
 * Ejem. var = GPIOE6PinRead(PIN4);
 * 		 var posee el valor actual del PIN4.
 * */
unsigned GPIOE6PinRead(unsigned Pin){
	Pin &= Xil_In32(GPIOE6_BASEADDR|GPIOE6_PORTVALUE_REG);
	
	if(Pin)
		return 1;
	else
		return 0;
}

/* Se utiliza para leer el valor de todo el puerto.
 * En caso de que un pin no se encuentre en funcion GPIO Input
 * desplegara el valor asignado por otras funciones.
 * 	@return: valor del puerto.
 * 
 * 	Ejem. var = GPIOE6PortRead();
 * 		  var posee el valor actual del puerto.
 * */
unsigned GPIOE6PortRead(void){
	return Xil_In32(GPIOE6_BASEADDR|GPIOE6_PORTVALUE_REG);
}

/* Se utiliza para asignar la Direccion de los Pines
 * 	@Pines: Utilizar las Definiciones PIN0,PIN1 ... PIN11
 * 			En el caso de asignar direccion a un pin utilizar el operador
 * 			"|".
 * 	@Function: Asigna la funcion a utilizar en los pines
 * 			   Utilizar definiciones GPIOE6_FUNC_OUTPUT, GPIOE6_FUNC_PWM
 * 			   GPIOE6_FUNC_7SEC o GPIOE6_FUNC_INPUT. de lo contrario.
 * 				0: GPIO Output
 * 				1: Decodificador 7 Seg.
 * 				2: PWM
 * 				3: GPIO Input
 * Ejem. GPIOE6SetFunction(PIN0|PIN2|PIN5,GPIOE6_FUNC_OUTPUT);
 * 		 Asigna los pines 0,2 y 5 con la funcion GPIO OutPut.
 * */
void GPIOE6SetFunction(unsigned Pines, unsigned Function){
	unsigned RegValue = Xil_In32(GPIOE6_BASEADDR|GPIOE6_FUNCSELECT_REG);
	unsigned ChangeMask = 0;
	unsigned UnchangeMask = 0;
	unsigned j = 1;

	Function &= 0x3;
	if(Function == GPIOE6_FUNC_PWM){
		Pines &=0xF00;
		if (Pines <PIN8)
			return;
	}

	for (unsigned i = 1; i <= PIN11; i = 1 << j++)
		if(i & Pines)
			ChangeMask |= Function << 2*(j-1);
		else
			UnchangeMask |= 3 << 2*(j-1);

	Xil_Out32(GPIOE6_BASEADDR|GPIOE6_FUNCSELECT_REG,
			(UnchangeMask & RegValue)|ChangeMask);
}
