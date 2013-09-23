#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "stm32f10x.h"
#include "stm32f10x_conf.h"


void Delay(volatile uint32_t nCount);




volatile int main(void)

{
    IO_init();


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




