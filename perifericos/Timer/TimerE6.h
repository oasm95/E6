/*
 * TimerE6.h
 *
 *  Created on: Oct 30, 2019
 *      Author: dadmin
 */

#ifndef SRC_TIMERE6_H_
#define SRC_TIMERE6_H_

#include "xparameters.h"
#include "xil_io.h"

#define TIMERE6_BASEADDR XPAR_E6_TIMER_0_S00_AXI_BASEADDR

#define TIMERE6_CONFIG_REG	0x0U
#define TIMERE6_LOAD_REG	0x4U
#define TIMERE6_COUNT_REG 	0x8U

#define TIMERE6_ONESHOT	0x0U
#define TIMERE6_PERIODIC 0x2U
#define TIMERE6_ENABLE 0x1U

void TimerE6SetLoad(unsigned Load);
void TimerE6Config(unsigned Type);
void TimerE6Start(void);
void TimerE6Stop(void);
unsigned TimerE6GetValue(void);

// Funciones  y Definiciones para control de  Interrupciones
#define TIMERE6_INTR_GLOBAL_EN	0x10000U
#define TIMERE6_INTR_EN			0x10004U
#define TIMERE6_INTR_STS		0x10008U
#define TIMERE6_INTR_ACK		0x1000CU
#define TIMERE6_INTR_PENDING	0x10010U

#define TIMERE6_INTR_ENABLE_VAL 0x1U
#define TIMERE6_INTR_DISABLE_VAL 0x0U

void TimerE6IntrGlobalEnable(void);
void TimerE6IntrGlobalDisable(void);
void TimerE6IntrEnable(void);
void TimerE6IntrDisable(void);
void TimerE6IntrClear(void);
unsigned TimerE6IntrStatus(void);





#endif /* SRC_TIMERE6_H_ */
