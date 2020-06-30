/*
 * GPIOE6.h
 *
 *  Created on: Oct 26, 2019
 *      Author: dadmin
 */

#ifndef SRC_GPIOE6_H_
#define SRC_GPIOE6_H_

#include "xparameters.h"
#include "xil_io.h"

#define GPIOE6_BASEADDR XPAR_E6_GPIO_0_S00_AXI_BASEADDR
#define GPIOE6_DIR_REG 		0U
#define GPIOE6_DATAOUT_REG	4U
#define GPIOE6_FUNCSELECT_REG	8U
#define GPIOE6_PORTVALUE_REG	12U


#define GPIOE6_FUNC_OUTPUT 0U
#define GPIOE6_FUNC_7SEC 1U
#define GPIOE6_FUNC_PWM 2U
#define GPIOE6_FUNC_INPUT 3U

#define GPIOE6_NUM_PINES 12U
#define PIN0 0x1U
#define PIN1 0x2U
#define PIN2 0x4U
#define PIN3 0x8U
#define PIN4 0x10U
#define PIN5 0x20U
#define PIN6 0x40U
#define PIN7 0x80U
#define PIN8 0x100U
#define PIN9 0x200U
#define PIN10 0x400U
#define PIN11 0x800U

void GPIOE6SetDirection(unsigned Pines,unsigned Direccion);
void GPIOE6SetFunction(unsigned Pines, unsigned Function);
void GPIOE6PortWrite(unsigned PortValue);
void GPIOE6PinWrite(unsigned Pin,unsigned Value);
unsigned GPIOE6PinRead(unsigned Pin);
unsigned GPIOE6PortRead(void);

#endif /* SRC_GPIOE6_H_ */
