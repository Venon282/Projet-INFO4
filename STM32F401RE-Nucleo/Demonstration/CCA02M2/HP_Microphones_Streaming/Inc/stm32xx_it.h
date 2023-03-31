/**
  ******************************************************************************
  * @file    stm32xx_it.h
  * @author  SRA
  * @version v1.0.0
  * @date    17-Jul-2020
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

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USB_IRQHandler(void);

void AUDIO_DFSDM_DMAx_MIC1_IRQHandler(void);
void AUDIO_DFSDM_DMAx_MIC2_IRQHandler(void);
void AUDIO_DFSDM_DMAx_MIC3_IRQHandler(void);
void AUDIO_DFSDM_DMAx_MIC4_IRQHandler(void);
void AUDIO_IN_I2S_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32xx_IT_H */


