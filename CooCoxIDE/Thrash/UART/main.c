// inc.
#define HSE_VALUE 8000000

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>



//Функция предназначена для формирования небольшой задержки
void Delay(void) {
  volatile uint32_t i;
  for (i=0; i != 0x1000; i++);
}




int main(void)
{
	unsigned char data,i,j = 0;
	unsigned char buf[10];
  GPIO_InitTypeDef GPIO_init_structure;
  // Включаем тактирование порта А и USART1
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC| RCC_APB2Periph_USART1, ENABLE);
  // Настраиваем ногу TxD (PA9) как выход push-pull c AF mode.
  GPIO_init_structure.GPIO_Pin = GPIO_Pin_9;
  GPIO_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_init_structure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_init_structure);

    GPIO_init_structure.GPIO_Pin = GPIO_Pin_10;
    GPIO_init_structure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_init_structure);

    GPIO_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_init_structure.GPIO_Mode  = GPIO_Mode_Out_PP;
            GPIO_init_structure.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;       // two LED (guess on what pin!!)
            GPIO_Init(GPIOC, &GPIO_init_structure);



 // Настраиваем UART
 // USART1->BRR=0x9c4; //BaudRate 9600
 // USART1->CR1 |= USART_CR1_UE; //Разрешаем работу USART1
 // USART1->CR1 |= USART_CR1_TE; //Включаем передатчик
  //Все остальные параметры (стоп биты, чётность,кол-во байт данных) уже настроены
  //как надо, (во все эти биты по умолчанию записаны нули), таким образом мы имеем
  // скорость 9600 1 стоп бит, 8 бит данных, без проверки чётности

  USART_InitTypeDef USART_InitStruct;
  USART_InitStruct.USART_BaudRate = 9600;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No ;
  USART_InitStruct.USART_Mode =  USART_Mode_Tx | USART_Mode_Rx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

  USART_Init(USART1,&USART_InitStruct);

  USART_Cmd(USART1,ENABLE);


   GPIOC->ODR |= (1<<4|1<<3|1<<5);


  while(1)
  {











    	 while(!(USART1->SR & USART_SR_RXNE));
	GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_RESET);
	buf[i]=USART1->DR;
	Delay();
	GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_SET);









	  while(!(USART1->SR & USART_SR_TC)); //Ждем пока бит TC в регистре SR станет 1
	  GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_RESET);
	  USART1->DR=buf[j]; //Отсылаем байт через UART
	  	Delay();
	  	GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_SET);



  }
}
