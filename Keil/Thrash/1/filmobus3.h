#ifndef __filmobus3_H
#define __filmobus3_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stm32f10x_gpio.h>
#include <stm32f10x_dma.h>
#include <stm32F10x_rcc.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define RE_SetUp						GPIOC->ODR |= GPIO_Pin_6
#define RE_SetDown					    GPIOC->ODR &= ~GPIO_Pin_6
//----------------------------------------
//направление передачи посылки							//
#define	_FromDesk	0x00							//
#define	_FromRTU	0x80							//
//----------------------------------------
//необходимость ответа от блока							//
#define	_NoAnswer	0x00                                                    //
#define	_NeedAnswer	0x80                                                    //

//----------------------------------------
//флаг передачи установок в хвосте посылки					//
#define	_NoSettings	0x00                                                    //
#define	_SendSettings	0x40                                                    //

//----------------------------------------
//флаг запроса установок от удаленного устройства
#define	_NoAsk		0x00                                                    //
#define	_SendAsk	0x20                                                    //

//		маски битов в байте Identifikator (для декодирования посылки)
#define	_AnswerReq	0x80		//запрос ответа от блока
#define _SettingsTx	0x40		//наличие в посылке массива установок
#define _SettingsReq	0x20		//запрос установок от блока


//----------------------------------------
// Типы посылок
#define _InfoPacket	0x00                                                    //
#define _FH1Packet	0x01                                                    //
#define _ARPacket	0x02                                                    //
#define _PB1Packet	0x03                                                    //
#define _PB2Packet	0x04                                                    //
#define _DollyPacket	0x05                                                    //
#define _Mov2Packet	0x06                                                    //
#define _ReqSettPacket	0x07                                                    //

//----------------------------------------
// Номера флагов в информационной посылке                                       //
#define _Focus1		0x0001                                                  //
#define _Iris1 		0x0002                                                  //
#define _Zoom1		0x0004                                                  //
#define _Pan1		0x0008                                                  //
#define _Tilt1		0x0010                                                  //
#define _Roll1		0x0020                                                  //
#define _Mover1		0x0040                                                  //
#define _rezerv1	0x0080                                                  //
#define _Focus2		0x0100                                                  //
#define _Iris2		0x0200                                                  //
#define _Zoom2		0x0400                                                  //
#define _Pan2		0x0800                                                  //
#define _Tilt2		0x1000                                                  //
#define _Roll2		0x2000                                                  //
#define _Mover2		0x4000                                                  //
#define _rezerv2	0x8000                                                  //
/* Exported functions ------------------------------------------------------- */
void UART1Init (void);
void FormingPosilka_Filmobus3(unsigned int Focus1Force,
															unsigned int Iris1Force,
															unsigned int Zoom1Force,
															unsigned int Pan1Force,
															unsigned int Tilt1Force,
															unsigned int Roll1Force,
															unsigned int Mover1Force,
															unsigned int rezerv1,
															unsigned int Focus2Force,
															unsigned int Iris2Force,
															unsigned int Zoom2Force,
															unsigned int Pan2Force,
															unsigned int Tilt2Force,
															unsigned int Roll2Force,
															unsigned int Mover2Force,
															unsigned int rezerv2Force,
															unsigned char SettingsByte0,
															unsigned char SettingsByte1,
															unsigned char DiskretByte,
															unsigned char Direction,
															unsigned char AnswerFlag,
															unsigned char SettingsFlag,
															unsigned char AskSettingsFlag,
															unsigned char PacketType,
															unsigned int InfoFlags_RTU
															) ;
#endif 
