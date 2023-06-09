/**
  ******************************************************************************
  * @file    stm32xx_it.h
  * @author  SRA
  * @version v1.3.0
  * @date    17-Sep-2021
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32xx_IT_H
#define __STM32xx_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cube_hal.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern I2S_HandleTypeDef                hAudioInI2s;

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USB_IRQHandler(void);
void AUDIO_IN_I2S_IRQHandler(void);
void BSP_USART_DMA_STREAM_TX_IRQHandler(void);
void USARTx_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);



#ifdef __cplusplus
}
#endif

#endif /* __STM32xx_IT_H */


