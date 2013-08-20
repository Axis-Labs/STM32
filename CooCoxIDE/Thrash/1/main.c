


#include<stm32f10x_rcc.h>
#include<stm32f10x_gpio.h>

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

void Delay(volatile uint32_t nCount);


GPIO_InitTypeDef GPIO_InitStructure;

volatile int main(void)
{

	unsigned char count;
// init for GPIO (LED)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;       // two LED (guess on what pin!!)
        GPIO_Init(GPIOC, &GPIO_InitStructure);

      GPIOC->ODR |= (1<<4|1<<3|1<<5);
      Delay(8000000);
      GPIOC->ODR &= (0<<4|0<<3|0<<5);
count = 0;
    while(1)

    {

    	while (count<10)
    	{
    	Delay(8000000);
    	   GPIOC->ODR &= (0<<4|0<<3|0<<5);
    	      Delay(8000000);
    	      GPIOC->ODR |= (1<<4|1<<3|1<<5);
    	      count++;
    	}

    	Delay(4000000);



        GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_RESET);
        GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_RESET);
                GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_SET);
                Delay(8000000);
                GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_RESET);
                GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_SET);
                GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_RESET);
                Delay(8000000);
                GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_RESET);
                               GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_RESET);
                               GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_SET);
                               Delay(8000000);






    }

}


//-------
void Delay(volatile uint32_t nCount)
{
    for (; nCount > 0; nCount--);
}



