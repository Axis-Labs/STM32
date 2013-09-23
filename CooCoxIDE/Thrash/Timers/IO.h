// IO initalization file
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
void IO_init(void)
{
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		  GPIO_InitTypeDef PORT;

		  PORT.GPIO_Pin = (GPIO_Pin_4 | GPIO_Pin_3|GPIO_Pin_5);
		  PORT.GPIO_Mode = GPIO_Mode_Out_PP;
		  PORT.GPIO_Speed = GPIO_Speed_2MHz;
		  GPIO_Init(GPIOC , &PORT);

		     //     PORT1.GPIO_Pin = (GPIO_Pin_4);
		  	//	  PORT1.GPIO_Mode = GPIO_Mode_Out_PP;
		  	//	  PORT1.GPIO_Speed = GPIO_Speed_50MHz;
		  	//	  GPIO_Init(GPIOA , &PORT1);


}
