#include<stm32f4xx_rcc.h>
#include<stm32f4xx_gpio.h>

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

void Delay(volatile uint32_t nCount);


GPIO_InitTypeDef GPIO_InitStructure;

volatile int main(void)

{
// init for GPIO (LED)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;       // two LED (guess on what pin!!)
        GPIO_Init(GPIOC, &GPIO_InitStructure);



    while(1)
    {
        GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_RESET);
        GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_RESET);
                GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_SET);
                Delay(1000000);
                GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_RESET);
                GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_SET);
                GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_RESET);
                Delay(1000000);
                GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_RESET);
                               GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_RESET);
                               GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_SET);
                               Delay(1000000);
    }

}


//-------
void Delay(volatile uint32_t nCount)
{
    for (; nCount > 0; nCount--);
}
