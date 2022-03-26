/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IT_H
#define __IT_H

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void Delay (uint32_t dlyTicks);

#ifdef USE_STM32F103C8

void ResetTimeout(void);
void TIMER13_IRQHandler(void);
void TIMER0_BRK_UP_TRG_COM_IRQHandler(void);
void DMA_Channel0_IRQHandler(void);
void DMA_Channel1_2_IRQHandler(void);
void DMA_Channel3_4_IRQHandler(void);
void DMA1_Channel1_IRQHandler(void);
void DMA2_Channel4_5_IRQHandler(void);

#endif // USE_STM32F103C8

#ifdef USE_GD32F130C8

void USART0_IRQHandler(void);
void USART1_IRQHandler(void);
void I2C0_EV_IRQHandler(void);
void I2C0_ER_IRQHandler(void);
#ifdef AUX45_USE_I2C
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
#endif

#endif // USE_GD32F130C8

#endif // _IT_H
