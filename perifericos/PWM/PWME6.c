/*
 * PWME6.c
 *
 *  Created on: Oct 28, 2019
 *      Author: dadmin
 */
#include "PWME6.h"

/* Habilita el canal de PWM seleccionado
 * 	@PwmChannel: Indica el canal PWM
 * 				 Utilizar definiciones PWME6_PWM0, PWME6_PWM1, PWME6_PWM2
 * 				 PWME6_PWM3 o simplemente escribir el numero del canal
 * 	
 * Ejem. PwmE6Start(PWME6_PWM2);
 * 		  PwmE6Start(2);
 * 		  Habilita el PWM2.
 * */
void PwmE6Start(unsigned PwmChannel){
	unsigned RegValue = Xil_In32(PWME6_BASEADDR|PWME6_ENABLE_REG);
	RegValue |= 1 << PwmChannel;
	Xil_Out32BE(PWME6_BASEADDR|PWME6_ENABLE_REG,RegValue);
}

/* Desabilita el canal de PWM seleccionado
 * 	@PwmChannel: Indica el canal PWM
 * 				 Utilizar definiciones PWME6_PWM0, PWME6_PWM1, PWME6_PWM2
 * 				 PWME6_PWM3 o simplemente escribir el numero del canal
 * 
 * 	Ejem. PwmE6Stop(PWME6_PWM0);
 * 		  PwmE6Stop(0);
 * 		  Desabilita el PWM0.
 * */
void PwmE6Stop(unsigned PwmChannel){
	unsigned RegValue = Xil_In32(PWME6_BASEADDR|PWME6_ENABLE_REG);
	PwmChannel = 1 << PwmChannel;
	Xil_Out32(PWME6_BASEADDR|PWME6_ENABLE_REG,RegValue&(~PwmChannel));
}

/* Asigna el valor global de frecuancia en la que operaran los canales
 * de pwm.
 * 	@freq : valor de frecencia en Hz.
 * 		    valor entero dentro de 1 a 100,000,000 
 * 	
 * 	Ejem. PwmE6SetGlobalFreq(50);
 * 		  Los 4 PWMs trabajaran a una frecuencia de 50Hz.
 * */
void PwmE6SetGlobalFreq(unsigned freq){
	freq = PWME6_PL_CLK_FREQ/freq;
	Xil_Out32(PWME6_BASEADDR|PWME6_FREQ_REG,freq);
}

/* Escribe el valor de ciclo de trabajo al canal de pwm indicado.
 * El ciclo de trabajo esta dado por la ecuacion descrita en la 
 * documentacion del periferico.
 * 	@PwmChannel: Indica el canal PWM
 * 				 Utilizar definiciones PWME6_PWM0, PWME6_PWM1, PWME6_PWM2
 * 				 PWME6_PWM3 o simplemente escribir el numero del canal
 * 	@Duty: valor de ciclo de trabajo
 * 
 * 	Ejem. PwmE6SetDutyCicle(PWME6_PWM1,484984);
 * 		  PwmE6SetDutyCicle(1,484984);
 * 		  Asigna un valor de 484984 al registro DUTY del PWM1.
 * */
void PwmE6SetDutyCicle(unsigned PwmChannel, unsigned Duty){
	unsigned RegSelector = ((PwmChannel&0x3) << 2) + 8;
	Xil_Out32(PWME6_BASEADDR|RegSelector,Duty);

}

/* Asigna un valor de ciclo de trabajo al canal de pwm indicado.
 * 	@PwmChannel: Indica el canal PWM
 * 				 Utilizar definiciones PWME6_PWM0, PWME6_PWM1, PWME6_PWM2
 * 				 PWME6_PWM3 o simplemente escribir el numero del canal
 * 	@Duty: valor de ciclo de trabajo
 * 		   valores con decimales entre 0 y 100 
 * 
 * 	Ejem. PwmE6SetDutyCiclePercent(PWME6_PWM1,58.7);
 * 		  PwmE6SetDutyCiclePercent(1,58.7);
 * 		  Le asigna un ciclo de trabajo del %58.7 al PWM1.
 * */
void PwmE6SetDutyCiclePercent(unsigned PwmChannel, float Duty){
	unsigned RegSelector = ((PwmChannel&0x3) << 2) + 8;
	unsigned freq = Xil_In32(PWME6_BASEADDR|PWME6_FREQ_REG);
	Duty = Duty/100.0;
	freq =  (unsigned) ((float)Duty*freq);
	Xil_Out32(PWME6_BASEADDR|RegSelector,freq);
}
