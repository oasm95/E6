/*
 * TimerE6.c
 *
 *  Created on: Oct 30, 2019
 *      Author: dadmin
 */
#include "TimerE6.h"

/* Especifica el valor a contar
 * Si el PL_CLK es igual a 100,000,000 hz asignarle un valor
 * de 100,000,000 a Load hara que cuente por un segundo.
 * en el caso de utilizar interrupciones, se generara una interrupcion
 * al pasar un segundo.
 * */
void TimerE6SetLoad(unsigned Load){
	Xil_Out32(TIMERE6_BASEADDR|TIMERE6_LOAD_REG,Load);
}
/* Especifica el modo de operacion del Timer
 * 	@Type: modo de operacion
 * 		   Utilizar definiciones TIMERE6_ONESHOT o TIMERE6_PERIODIC
 * 		   ONESHOT: Realiza el conteo una unica vez
 * 		   PERIODIC: Al terminar el conteo, se reinicia y empiza a contar
 * 					 otra vez automaticamente.
 * */
void TimerE6Config(unsigned Type){
	unsigned RegValue = Xil_In32(TIMERE6_BASEADDR|TIMERE6_CONFIG_REG);
	if(Type != TIMERE6_ONESHOT)
		Xil_Out32(TIMERE6_BASEADDR|TIMERE6_CONFIG_REG,RegValue|TIMERE6_PERIODIC);
	else
		Xil_Out32(TIMERE6_BASEADDR|TIMERE6_CONFIG_REG,RegValue&(~TIMERE6_PERIODIC));
}
//inicia el conteo
void TimerE6Start(void){
	unsigned RegValue = Xil_In32(TIMERE6_BASEADDR|TIMERE6_CONFIG_REG);
	Xil_Out32(TIMERE6_BASEADDR|TIMERE6_CONFIG_REG,RegValue|TIMERE6_ENABLE);

}
//Detiene el conteo
void TimerE6Stop(void){
	unsigned RegValue = Xil_In32(TIMERE6_BASEADDR|TIMERE6_CONFIG_REG);
	Xil_Out32(TIMERE6_BASEADDR|TIMERE6_CONFIG_REG,RegValue&(~TIMERE6_ENABLE));
}

/* Devuelve el valor actual del conteo del timer.
 * 	@return: valor actual del conteo.
 * */
unsigned TimerE6GetValue(void){
	return Xil_In32(TIMERE6_BASEADDR|TIMERE6_COUNT_REG);
}

/*Funciones para control de Interrupciones*/

//Habilita la generacion de interrupciones del periferico
void TimerE6IntrGlobalEnable(void){
	Xil_Out32(TIMERE6_BASEADDR+TIMERE6_INTR_GLOBAL_EN,TIMERE6_INTR_ENABLE_VAL);
}
//Desabilita la generacion de interrupciones del periferico
void TimerE6IntrGlobalDisable(void){
	Xil_Out32(TIMERE6_BASEADDR+TIMERE6_INTR_GLOBAL_EN,TIMERE6_INTR_DISABLE_VAL);
}
// habilita la deteccion de interrupciones del periferico
void TimerE6IntrEnable(void){
	Xil_Out32(TIMERE6_BASEADDR+TIMERE6_INTR_EN,TIMERE6_INTR_ENABLE_VAL);
}
// Desabilita la deteccion de interrupciones del periferico
void TimerE6IntrDisable(void){
	Xil_Out32(TIMERE6_BASEADDR+TIMERE6_INTR_EN,TIMERE6_INTR_DISABLE_VAL);
}
//Limpia interrupciones del periferico
void TimerE6IntrClear(void){
	Xil_Out32(TIMERE6_BASEADDR+TIMERE6_INTR_ACK,TIMERE6_INTR_ENABLE_VAL);
}
// regresa el valor del estatus de las interrupciones
unsigned TimerE6IntrStatus(void){
	return Xil_In32(TIMERE6_BASEADDR+TIMERE6_INTR_STS);
}
