


#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <IO.h>

#define LED1ON GPIOC->ODR &=~(1<<3)
#define LED1OFF GPIOC->ODR |=(1<<3)
#define LED2ON GPIOC->ODR &=~(1<<4)
#define LED2OFF GPIOC->ODR |=(1<<4)
#define LED3ON GPIOC->ODR &=~(1<<5)
#define LED3OFF GPIOC->ODR |=(1<<5)
#define LEDALLON GPIOC->ODR &=~((1<<3)|(1<<4)|(1<<5))
#define LEDALLOFF GPIOC->ODR |=(1<<3)|(1<<4)|(1<<5)


int r=0;





void TIM2_IRQHandler (void)
             {


	           TIM2->SR &= ~TIM_SR_UIF;

	LED3ON;
	for(r=0;r<100000;r++);
	LED3OFF;

	    	            	//   LED3OFF;


             }


void TIM6_init()
{
	 RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;     // уже привычное, ключаю тактирование модуля
	        //TIM2->PSC = 182;      // пределитель 12000000/65536 - 1
	        // так точнее будет
	        TIM2->ARR = 60000;              // макс. значение до которого считаем
	        TIM2->PSC = 600;                // пределитель 12000000/60000 - 1
	        TIM2->CR1 |= TIM_CR1_CEN;       // запускаю счет
	        TIM2->DIER |= TIM_DIER_UIE;            // запуск счета

}






int main(void)
{
   IO_init();
   LEDALLOFF;
	 __enable_irq();                 // общее включение прерывания
	    NVIC_EnableIRQ(TIM2_IRQn);
	     TIM6_init();
	     LED1ON;




    while(1)
    {






    }
}
