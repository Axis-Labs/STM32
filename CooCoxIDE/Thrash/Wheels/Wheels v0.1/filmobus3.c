#include "filmobus3.h"


//================================================================================
#define _MaxTransLength	49                                              	// максимальный размер буфера передатчика
#define _MaxRecLength 	34                                              	// максимальный размер буфера приемника
//--------------------------------------------------------------------------------


unsigned char CurrentTransRTUByte;                                        	// номер передаваемого байта
unsigned char TransMassivRTULong;                                         	// длина передаваемого массива
unsigned char TxMassivRTU[_MaxTransLength];                               	// массив передатчика
//unsigned int InfoFlags_RTU;
unsigned char RxMassivDK[_MaxRecLength];                                 	// массив приемника от платы DigitalKeys
unsigned char NumberBytesToRec;                  				// количество байт для приема по каналу
unsigned int DirectionRx;
//==========================================================
unsigned int TxCRCkod = 0;
unsigned int RxCRCkod = 0;
//==========================================================

void TxCRC(unsigned char Byte)
    {
    unsigned int temp_i;
    unsigned char temp;
    temp_i = Byte;
    temp_i <<= 8;
    TxCRCkod ^= temp_i;
    temp = 0;
    while (temp < 8)
        {
        if ((TxCRCkod & 0x8000) == 0) TxCRCkod <<= 1;
        else
            {
            TxCRCkod <<= 1;
            TxCRCkod ^= 0x1021;
            }
        temp++;
        }
    }
//==========================================================
void RxCRC(unsigned char Byte)
    {
    unsigned int temp_i;
    unsigned char temp;
    temp_i = Byte;
    temp_i <<= 8;
    RxCRCkod ^= temp_i;
    temp = 0;
    while (temp < 8)
        {
        if ((RxCRCkod & 0x8000) == 0) RxCRCkod <<= 1;
        else
            {
            RxCRCkod <<= 1;
            RxCRCkod ^= 0x1021;
            }
        temp++;
        }
    }
//==========================================================
void FormingCRC_Filmobus3(unsigned char *Adres,unsigned char Length)            //
{unsigned char Index;								//
 unsigned char temp;                                                            //
//-----------------------                                                       //
 TxCRCkod = 0;                                                              	//
 Index = 3;									//
 while (Index < Length)                                                         //
	{                                                                       //
	temp = *(Adres + Index);                   				//
	TxCRC(temp);								//
	Index++;                                                                //
	}                                                                       //
//-----------------------                                                       //
 *(Adres + Index++) = (unsigned char)(TxCRCkod>>8);                                  //
 *(Adres + Index++) = (unsigned char)(TxCRCkod);                               //
 *(Adres + Index++) = 0;							//
//-----------------------                                                       //
}										//
//================================================================================
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
															)                                   	        //
{                                                       	                //
unsigned char temp;                                                         //
unsigned int temp_i;								//
//unsigned char AnswerFlag;					//необходимость ответа от блока
//unsigned char SettingsFlag;					//флаг передачи установок в хвосте посылки
//unsigned char AskSettingsFlag;					//флаг запроса установок от удаленного устройства
//unsigned char PacketType;					//тип посылки
//unsigned char Direction;					//направление передачи посылки
static unsigned char SettingsGroupCounter = 0;  		//счетчик номер группы передаваемых установок
static unsigned char AskSettingsGroupCounter = 0;		//счетчик номера группы запрашиваемых установок

//--------------------------------------------------------------------------------
temp = 0;

TxMassivRTU[temp++] = 0xFF;							//Стартовый флаг: 0xFF,0xFF,0xFF
TxMassivRTU[temp++] = 0xFF;							//
TxMassivRTU[temp++] = 0xFF;							//
//--------------------------------------------------------------------------------
temp++;										//длина посылки - записываетмя после формирования всей посылки
//--------------------------------------------------------------------------------
//Параметры посылки
//Direction = _FromDesk;								//направление передачи посылки
//AnswerFlag =   _NoAnswer;							//необходимость ответа
//SettingsFlag = _SendSettings;							//флаг передачи массива установок
//AskSettingsFlag = _NoAsk;							//флаг передачи запроса установок
//PacketType = _InfoPacket;							//тип передаваемой посылки
//--------------------------------------------------------------------------------
TxMassivRTU[temp++] = AnswerFlag | SettingsFlag | AskSettingsFlag | PacketType;//идентификатор послыки
//--------------------------------------------------------------------------------
//InfoFlags_RTU = 0_Focus1 | _Iris1 | _Zoom1 | _Pan1 | _Tilt1 | _Roll1 | _Mover1 | _rezerv1 
//								;//| _Focus2 | _Iris2 | _Zoom2 | _Pan2 | _Tilt2 | _Roll2 | _Mover2 | _rezerv2;
//--------------------------------------------------------------------------------
TxMassivRTU[temp++] = (unsigned char)(InfoFlags_RTU);				//
TxMassivRTU[temp++] = (unsigned char)(InfoFlags_RTU >> 8);      		//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU &_Focus1 )                                  			//
  {temp_i = Focus1Force;                                                   	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Iris1)                                  			//
  {temp_i = Iris1Force;                                                     	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Zoom1)                                  			//
  {temp_i = Zoom1Force;                                                   	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Pan1)                                  			//
  {temp_i = Pan1Force;                                                       	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Tilt1)                                  			//
  {temp_i = Tilt1Force;                                                      	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Roll1)                                 			//
  {temp_i = Roll1Force;                                                   	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Mover1)                                 			//
  {temp_i = Mover1Force;                                                   	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//	
//--------------------------------------------------------------------------------

if (InfoFlags_RTU & _rezerv1)                                 			//
  {temp_i = rezerv1;                                                   		//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU &_Focus2 )                                  			//
  {temp_i = Focus2Force;                                                   	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Iris2)                                  			//
  {temp_i = Iris2Force;                                                       	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//	
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Zoom2)                                  			//
  {temp_i = Zoom2Force;                                                       	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//	
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Pan2)                                  			//
  {temp_i = Pan2Force;                                                       	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Tilt2)                                  			//
  {temp_i = Tilt2Force;                                                       	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Roll2)                                  			//
  {temp_i = Roll2Force;                                                       	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _Mover2)                                  			//
  {temp_i = Mover2Force;                                                       	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (InfoFlags_RTU & _rezerv2)                                  			//
  {temp_i = rezerv2Force;                                                       	//
   if (temp_i == 0xffff) {temp_i --;}
   TxMassivRTU[temp++] = (unsigned char)(temp_i);          			//
   TxMassivRTU[temp++] = (unsigned char)(temp_i >> 8);     			//
  }										//
//--------------------------------------------------------------------------------
if (SettingsFlag == _SendSettings)						//
  {SettingsGroupCounter = 6;							//
  										//
   // Settings groups                                                       	//
   TxMassivRTU[temp++] = SettingsGroupCounter;                            	//
   //-----------------------------------------------------------------------------
   TxMassivRTU[temp++] = SettingsByte0;                                  			//
   TxMassivRTU[temp++] = SettingsByte1;                                  			//
   TxMassivRTU[temp++] = DiskretByte;                                  			//
   TxMassivRTU[temp++] = 0;                                  			//
   TxMassivRTU[temp++] = 0;                                  			//
   TxMassivRTU[temp++] = 0;                                  			//
  }
//--------------------------------------------------------------------------------
if (AskSettingsFlag == _SendAsk)
  {TxMassivRTU[temp++] = AskSettingsGroupCounter;
   if (++AskSettingsGroupCounter == 16) AskSettingsGroupCounter = 0;
  }
//--------------------------------------------------------------------------------
TransMassivRTULong = temp;                          				//
//--------------------------------------------------------------------------------
TxMassivRTU[3] = Direction | (temp - 2);                                        // Длина посылки = посчитанное общее количество байт,
										// + 2 байта КПК - 4 байта (стартовый флаг + байт длины )
//--------------------------------------------------------------------------------
FormingCRC_Filmobus3(&TxMassivRTU[0],TransMassivRTULong);             	//
TransMassivRTULong += 3;
DMA_Cmd(DMA1_Channel7, DISABLE);//
DMA_SetCurrDataCounter(DMA1_Channel7,TransMassivRTULong+2);
DMA_ClearFlag(DMA1_FLAG_GL7);
DMA_ClearFlag(DMA1_FLAG_TC7);
DMA_ClearFlag(DMA1_FLAG_HT7);
DMA_ClearFlag(DMA1_FLAG_TE7);
DMA_ClearITPendingBit(DMA1_IT_GL7);
DMA_ClearITPendingBit(DMA1_IT_TC7);
DMA_ClearITPendingBit(DMA1_IT_HT7);
DMA_ClearITPendingBit(DMA1_IT_TE7);


RE_SetUp;
DMA_Cmd(DMA1_Channel7, ENABLE);
}                                                                               //
//================================================================================


void UART_DMA_INIT (void)
{








	        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	        DMA_InitTypeDef DMA_InitStructure;

	        //==Configure DMA1 - Channel1==
	           DMA_DeInit(DMA1_Channel7); //Set DMA registers to default values
	           DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) &USART2->DR; //Address of peripheral the DMA must map to
	           DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&TxMassivRTU[0];
	           DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST ;
	           DMA_InitStructure.DMA_BufferSize = _MaxTransLength;
	           DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	           DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	           DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	           DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	           DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	           DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	           DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	           DMA_ITConfig(DMA1_Channel7,DMA_IT_TC ,DISABLE);
	           DMA_ITConfig(DMA1_Channel7,DMA_IT_HT ,DISABLE);
	           DMA_ITConfig(DMA1_Channel7,DMA_IT_TE ,DISABLE);

	           DMA_Init(DMA1_Channel7, &DMA_InitStructure); //Initialise the DMA
	        //   DMA_Cmd(DMA1_Channel7, ENABLE); //Enable the DMA1 - Channel1



}







	/*
DMA_InitTypeDef  DMA_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

// Configure DMA Stream
DMA_Cmd(DMA2_Stream7, DISABLE);
DMA_DeInit(DMA2_Stream7); 
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART1->DR);
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)& TxMassivRTU[0];
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = _MaxTransLength;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream7, &DMA_InitStructure);
	
//	DMA_Cmd(DMA2_Stream7, ENABLE);

//Int. For Dma

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		DMA_ITConfig (DMA2_Stream7,DMA_IT_TC,ENABLE);


*/



/*
void UART1Init (void)
{
USART_InitTypeDef USART_InitStructure;			//структура инициализ. UART
GPIO_InitTypeDef  GPIO_InitStructure;				//структура иниц. порта в/в
//NVIC_InitTypeDef NVIC_InitStructure;				//структура иниц. контроллера прерываний

RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);     		//вкл. тактирование на порт UART
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);					//вкл. тактирования на портА, на нем ножки UART2
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);					//вкл. тактирования на портВ, на нем будетножка привем/передача PB0


	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			//TX pin conf for UART
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//GPIO_Pin_6;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			//GPIO_Init(GPIOB, &GPIO_InitStructure);
			//RX pin conf for UART
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//GPIO_Pin_7;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			//GPIO_Init(GPIOB, &GPIO_InitStructure);
			//RE pin conf for RS485
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//GPIO_Pin_1 ;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			
				GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
				GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
				USART_Init(USART1, &USART_InitStructure);
				
				USART_Cmd(USART1, ENABLE);
//**************************************************************************************************************************
//**************************************************************************************************************************

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig (USART2,USART_IT_TC,ENABLE);


UART_DMA_INIT();

}
*/

//UART_DMA_INIT();
/*
void DMA2_Stream7_IRQHandler (void) {
		if (DMA_GetFlagStatus(DMA2_Stream7, DMA_FLAG_TCIF7))
		{
		DMA_ClearFlag (DMA2_Stream7, DMA_FLAG_TCIF7);
		RE_SetDown;
		DMA_Cmd(DMA2_Stream7, ENABLE);
		};
} 
*/





