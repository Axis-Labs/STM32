// include
#include <periph.c>

#include <filmobus3.h>

// Definitions
#define LED1ON GPIOC->ODR &=~(1<<3)
#define LED1OFF GPIOC->ODR |=(1<<3)
#define LED2ON GPIOC->ODR &=~(1<<4)
#define LED2OFF GPIOC->ODR |=(1<<4)
#define LED3ON GPIOC->ODR &=~(1<<5)
#define LED3OFF GPIOC->ODR |=(1<<5)
#define LEDALLON GPIOC->ODR &=~(1<<3)|(1<<4)|(1<<5)
#define LEDALLOFF GPIOC->ODR |=(1<<3)|(1<<4)|(1<<5)

// Global variables
unsigned int count,count2,t,adc_res = 0;


// delay
void Delay(unsigned int d)
{
  volatile uint32_t i;
  for (i=0; i != d; i++);
}



int main(void)
{

	  RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA) , ENABLE);

	  GPIO_InitTypeDef PORT;
	  PORT.GPIO_Pin = (GPIO_Pin_4 | GPIO_Pin_3|GPIO_Pin_5);
	  PORT.GPIO_Mode = GPIO_Mode_Out_PP;
	  PORT.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOC , &PORT);

	//USART2_init(230400);
  //  UART_DMA_INIT();
	  ADC_init();
	  DAC_init();







		//GPIOC->ODR |= GPIO_Pin_6;

  while(1) // infinite loop.
  {

	//  FormingPosilka_Filmobus3(count,count2,(((ADC_buff[0]*3.26)/4095)*1000),ADC_buff[1],ADC_buff[2],1000,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767, 		//analog outputs
	//  		  																		0,																																																	//settingsbyte0
	//  		  																		0,																																																							//settingsbyte1
	//  		  																		0, 																																																							//DiskretByte
	//  		  																		_FromDesk,_NoAnswer,_SendSettings,_NoAsk,_InfoPacket,
	///  		  																		(_Focus1 | _Iris1 | _Zoom1 | _Pan1 | _Tilt1 | _Roll1 | _Mover1 )
	//  		  																		);



	//  DAC->DHR12R1 = ADC_buff[0];




	  Delay(0x800);
  }
}
