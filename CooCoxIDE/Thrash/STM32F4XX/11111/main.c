#define HSE_VALUE 8000000
#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>


void Delay(void)
{
  volatile uint32_t i;
  for (i=0; i != 0x50000; i++);
}
void usart_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	  // set Pin TxD (PA9) to push-pull mode with Alternate Function (AF).
	   GPIO_InitTypeDef GPIO_init_structure;
	   GPIO_init_structure.GPIO_Pin = GPIO_Pin_9;
	   GPIO_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
	   GPIO_init_structure.GPIO_Mode = GPIO_Mode_AF;
	   GPIO_Init(GPIOA, &GPIO_init_structure);

	   GPIO_init_structure.GPIO_Pin = GPIO_Pin_10;
	   GPIO_init_structure.GPIO_Mode = GPIO_Mode_AF;
	   GPIO_Init(GPIOA, &GPIO_init_structure);

	  // init USART1.
	    USART_InitTypeDef USART_InitStruct;
	    USART_InitStruct.USART_BaudRate = 9600;
	    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	    USART_InitStruct.USART_StopBits = USART_StopBits_1;
	    USART_InitStruct.USART_Parity = USART_Parity_No ;
	    USART_InitStruct.USART_Mode =  USART_Mode_Tx | USART_Mode_Rx;
	    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	    USART_Init(USART1,&USART_InitStruct);

	    USART_Cmd(USART1,ENABLE);

}

int main(void)
{

  unsigned char data;


  //initalize clock on gpio & USART1.
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef GPIO_init_structure;
  GPIO_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_init_structure.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_init_structure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
 GPIO_Init(GPIOD, &GPIO_init_structure);









  while(1) // infinite loop.
  {


/*

	 GPIOD->ODR |= GPIO_Pin_12;
	  GPIOD->ODR &= ~GPIO_Pin_13;
	  GPIOD->ODR &= ~GPIO_Pin_14;
	  GPIOD->ODR &= ~GPIO_Pin_15;
	  Delay();

	  GPIOD->ODR &= ~GPIO_Pin_12;
	 	  GPIOD->ODR |= GPIO_Pin_13;
	 	  GPIOD->ODR &= ~GPIO_Pin_14;
	 	  GPIOD->ODR &= ~GPIO_Pin_15;
	  Delay();
	  GPIOD->ODR &= ~GPIO_Pin_12;
	 	 	  GPIOD->ODR |= GPIO_Pin_14;
	 	 	  GPIOD->ODR &= ~GPIO_Pin_13;
	 	 	  GPIOD->ODR &= ~GPIO_Pin_15;
	 	  Delay();
	 	 GPIOD->ODR &= ~GPIO_Pin_12;
	 		 	  GPIOD->ODR |= GPIO_Pin_15;
	 		 	  GPIOD->ODR &= ~GPIO_Pin_14;
	 		 	  GPIOD->ODR &= ~GPIO_Pin_13;
	 		  Delay();

*/
	// 		 while(!(USART1->SR & USART_SR_RXNE)); // wait for byte will be recieved.
	 		//	GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_RESET);
	 //			data=USART1->DR;
	 		//	Delay();
	 		//	GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_SET);




	 //			     while(!(USART1->SR & USART_SR_TC)); // wait for previous transmition.
	 			// GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_RESET);
	 	//		 USART1->DR=data;
	 			// Delay();
	 		//	 GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_SET);






    GPIOD->ODR |=(1<<9);
    GPIOD->ODR &=~(1<<9);



  }
}
