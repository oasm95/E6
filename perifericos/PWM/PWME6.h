/*
 * PWME6.h
 *
 *  Created on: Oct 28, 2019
 *      Author: dadmin
 */

#ifndef SRC_PWME6_H_
#define SRC_PWME6_H_

#include "xparameters.h"
#include "xil_io.h"

#define PWME6_BASEADDR XPAR_E6_PWM_0_S00_AXI_BASEADDR
#define PWME6_ENABLE_REG 0x0U
#define PWME6_FREQ_REG 0x4U
#define PWME6_PWM0_DUTY_REG 0x8U
#define PWME6_PWM1_DUTY_REG 0xCU
#define PWME6_PWM2_DUTY_REG 0x10U
#define PWME6_PWM3_DUTY_REG 0x14U

#define PWME6_PWM0 0U
#define PWME6_PWM1 1U
#define PWME6_PWM2 2U
#define PWME6_PWM3 3U

#define PWME6_PL_CLK_FREQ 100000000U

void PwmE6Start(unsigned PwmChannel);
void PwmE6Stop(unsigned PwmChannel);
void PwmE6SetGlobalFreq(unsigned freq);
void PwmE6SetDutyCicle(unsigned PwmChannel, unsigned Duty);
void PwmE6SetDutyCiclePercent(unsigned PwmChannel, float Duty);

#endif /* SRC_PWME6_H_ */
