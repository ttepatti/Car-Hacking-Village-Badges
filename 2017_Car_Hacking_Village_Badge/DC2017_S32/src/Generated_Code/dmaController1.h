/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : dmaController1.h
**     Project     : DC2017_S32
**     Processor   : S32K144_100
**     Component   : edma
**     Version     : Component SDK_S32K144_04, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32K144_04
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-06-08, 10:35, # CodeGen: 1
**     Contents    :
**         EDMA_DRV_Init                        - status_t EDMA_DRV_Init(edma_state_t *edmaState, const edma_user_config_t...
**         EDMA_DRV_Deinit                      - status_t EDMA_DRV_Deinit(void);
**         EDMA_DRV_ChannelInit                 - status_t EDMA_DRV_ChannelInit(edma_chn_state_t * edmaChannelState,const...
**         EDMA_DRV_ReleaseChannel              - status_t EDMA_DRV_ReleaseChannel(uint8_t channel);
**         EDMA_DRV_StartChannel                - status_t EDMA_DRV_StartChannel(uint8_t channel);
**         EDMA_DRV_StopChannel                 - status_t EDMA_DRV_StopChannel(uint8_t channel);
**         EDMA_DRV_InstallCallback             - status_t EDMA_DRV_InstallCallback(uint8_t channel,edma_callback_t...
**         EDMA_DRV_GetChannelStatus            - static inline edma_chn_status_t EDMA_DRV_GetChannelStatus(uint8_t channel);
**         EDMA_DRV_PushConfigToReg             - void EDMA_DRV_PushConfigToReg(uint8_t channel,edma_transfer_config_t * config);
**         EDMA_DRV_PushConfigToSTCD            - void EDMA_DRV_PushConfigToSTCD(uint8_t channel,edma_transfer_config_t *...
**         EDMA_DRV_ConfigSingleBlockTransfer   - status_t EDMA_DRV_ConfigSingleBlockTransfer(uint8_t...
**         EDMA_DRV_ConfigLoopTransfer          - status_t EDMA_DRV_ConfigLoopTransfer(uint8_t channel,edma_transfer_config_t *...
**         EDMA_DRV_ConfigScatterGatherTransfer - status_t EDMA_DRV_ConfigScatterGatherTransfer(uint8_t...
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     All Rights Reserved.
**     
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file dmaController1.h
** @version 01.00
*/
/*!
**  @addtogroup dmaController1_module dmaController1 module documentation
**  @{
*/

/* MODULE dmaController1
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * The macros are defined to be used by application code.
 */

#ifndef dmaController1_H
#define dmaController1_H

/* Include inherited beans */
#include "clockMan1.h"
#include "Cpu.h"

/*! @brief Physical channel number for channel configuration #0 */
#define EDMA_CHN0_NUMBER   0U

/*! @brief The total number of configured channels */
#define EDMA_CONFIGURED_CHANNELS_COUNT   1U

/*! @brief Driver state structure which holds driver runtime data */
extern edma_state_t dmaController1_State;

/*! @brief eDma channel state structure 0. Holds channel runtime data */
extern edma_chn_state_t dmaController1Chn0_State;

/*! @brief Array of channel state structures */
extern edma_chn_state_t * const edmaChnStateArray[EDMA_CONFIGURED_CHANNELS_COUNT];

/*! @brief Configuration declaration */
extern const edma_user_config_t dmaController1_InitConfig0;

/*! @brief eDma channel configuration 0 */
extern edma_channel_config_t dmaController1Chn0_Config;

/*! @brief Array of channel configuration structures */
extern const edma_channel_config_t * const edmaChnConfigArray[EDMA_CONFIGURED_CHANNELS_COUNT];

#endif  /* ifndef dmaController1_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/
