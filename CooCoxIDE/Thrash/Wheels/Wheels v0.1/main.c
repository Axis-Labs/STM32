// include

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_dma.h>
#include <stm32f10x_adc.h>
#include <IO.h>
#include <periph.h>




// Definitions
#define LED1ON GPIOC->ODR &=~(1<<3)
#define LED1OFF GPIOC->ODR |=(1<<3)
#define LED2ON GPIOC->ODR &=~(1<<4)
#define LED2OFF GPIOC->ODR |=(1<<4)
#define LED3ON GPIOC->ODR &=~(1<<5)
#define LED3OFF GPIOC->ODR |=(1<<5)
#define LEDALLON GPIOC->ODR &=~((1<<3)|(1<<4)|(1<<5))
#define LEDALLOFF GPIOC->ODR |=(1<<3)|(1<<4)|(1<<5)





// Global variables



// delay
void Delay(unsigned int d)
{
  volatile uint32_t i;
  for (i=0; i !=d; i++);
}




int main(void)
{

	IO_init();
	//DAC_init();










  while(1) // infinite loop.
  {

	 // GPIOA->ODR |=(1<<4);
	//  Delay(0x1);
	//  GPIOA->ODR &=~(1<<4);
	//  Delay(0x1);
	  GPIOA->BRR = (1<<4);
	  __NOP;

	  GPIOA->BSRR = (1<<4);
	  __NOP;

  }


}
