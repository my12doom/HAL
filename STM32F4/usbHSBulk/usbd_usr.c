/**
  ******************************************************************************
  * @file    usbd_usr.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    19-March-2012
  * @brief   This file includes the user application layer
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbd_usr.h"
#include "usbd_ioreq.h"

#ifdef	USE_PRINTF_DEBUG
#include <stdio.h>
#endif

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
* @{
*/

/** @defgroup USBD_USR
* @brief    This file includes the user application layer
* @{
*/

/** @defgroup USBD_USR_Private_TypesDefinitions
* @{
*/
/**
* @}
*/


/** @defgroup USBD_USR_Private_Defines
* @{
*/
/**
* @}
*/


/** @defgroup USBD_USR_Private_Macros
* @{
*/
/**
* @}
*/


/** @defgroup USBD_USR_Private_Variables
* @{
*/

USBD_Usr_cb_TypeDef USR_cb =
{
	USBD_USR_Init,
	USBD_USR_DeviceReset,
	USBD_USR_DeviceConfigured,
	USBD_USR_DeviceSuspended,
	USBD_USR_DeviceResumed,


	USBD_USR_DeviceConnected,
	USBD_USR_DeviceDisconnected,
};

/**
* @}
*/

/** @defgroup USBD_USR_Private_Constants
* @{
*/

/**
* @}
*/



/** @defgroup USBD_USR_Private_FunctionPrototypes
* @{
*/
/**
* @}
*/


/** @defgroup USBD_USR_Private_Functions
* @{
*/

/**
* @brief  USBD_USR_Init
*         Displays the message on LCD for host lib initialization
* @param  None
* @retval None
*/
void USBD_USR_Init(void)
{

	// ?????????4???led?????????????????????LED???FSMC???????????????!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	STM_EVAL_LEDInit(LED1);
//	STM_EVAL_LEDInit(LED2);
//	STM_EVAL_LEDInit(LED3);
//	STM_EVAL_LEDInit(LED4);

//   LCD_LOG_Init();
//
// #ifdef USE_USB_OTG_HS
//   LCD_LOG_SetHeader(" USB OTG HS VCP Device");
// #else
//   LCD_LOG_SetHeader(" USB OTG FS VCP Device");
// #endif
//   LCD_UsrLog("> USB device library started.\n");
//   LCD_LOG_SetFooter ("     USB Device Library v1.1.0" );
#ifdef	USE_PRINTF_DEBUG
#ifdef USE_USB_OTG_HS

	printf(" USB OTG HS VCP Device\r\n");		// ??????????????????????????????????????????????????????USB????????????
#else
	printf(" USB OTG FS VCP Device\r\n");
#endif
	printf("> USB device library started.\r\n");
	printf ("     USB Device Library v1.1.0\r\n" );
#endif
}

/**
* @brief  USBD_USR_DeviceReset
*         Displays the message on LCD on device Reset Event
* @param  speed : device speed
* @retval None
*/
void USBD_USR_DeviceReset(uint8_t speed )
{
	switch (speed)
	{
	case USB_OTG_SPEED_HIGH:
//     LCD_LOG_SetFooter ("     USB Device Library v1.1.0 [HS]" );
#ifdef	USE_PRINTF_DEBUG
		printf("     USB Device Library v1.1.0 [HS]\r\n" );
#endif
		break;

	case USB_OTG_SPEED_FULL:
//     LCD_LOG_SetFooter ("     USB Device Library v1.1.0 [FS]" );
#ifdef	USE_PRINTF_DEBUG
		printf ("     USB Device Library v1.1.0 [FS]\r\n" );
#endif
		break;
	default:
	{
//     LCD_LOG_SetFooter ("     USB Device Library v1.1.0 [??]" );
#ifdef	USE_PRINTF_DEBUG
		printf ("     USB Device Library v1.1.0 [??]\r\n" );
#endif
	}
	}
}


/**
* @brief  USBD_USR_DeviceConfigured
*         Displays the message on LCD on device configuration Event
* @param  None
* @retval Status
*/
void USBD_USR_DeviceConfigured (void)
{
//  LCD_UsrLog("> VCP Interface configured.\n");
#ifdef	USE_PRINTF_DEBUG
	printf("> VCP Interface configured.\r\n");
#endif
}

/**
* @brief  USBD_USR_DeviceSuspended
*         Displays the message on LCD on device suspend Event
* @param  None
* @retval None
*/
void USBD_USR_DeviceSuspended(void)
{
//  LCD_UsrLog("> USB Device in Suspend Mode.\n");
#ifdef	USE_PRINTF_DEBUG
	printf("> USB Device in Suspend Mode.\r\n");
#endif
	/* Users can do their application actions here for the USB-Reset */
}


/**
* @brief  USBD_USR_DeviceResumed
*         Displays the message on LCD on device resume Event
* @param  None
* @retval None
*/
void USBD_USR_DeviceResumed(void)
{
//    LCD_UsrLog("> USB Device in Idle Mode.\n");
#ifdef	USE_PRINTF_DEBUG
	printf("> USB Device in Idle Mode.\r\n");
#endif
	/* Users can do their application actions here for the USB-Reset */
}


/**
* @brief  USBD_USR_DeviceConnected
*         Displays the message on LCD on device connection Event
* @param  None
* @retval Staus
*/
void USBD_USR_DeviceConnected (void)
{
//  LCD_UsrLog("> USB Device Connected.\n");
#ifdef	USE_PRINTF_DEBUG
	printf("> USB Device Connected.\r\n");
#endif
}


/**
* @brief  USBD_USR_DeviceDisonnected
*         Displays the message on LCD on device disconnection Event
* @param  None
* @retval Staus
*/
void USBD_USR_DeviceDisconnected (void)
{
//  LCD_UsrLog("> USB Device Disconnected.\n");
#ifdef	USE_PRINTF_DEBUG
	printf("> USB Device Disconnected.\r\n");
#endif
}
/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
