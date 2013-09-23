#include <stm32f10x_rcc.h>
//#define DAC_DATA_SIZE_12b_LA
#define DAC_DATA_SIZE_12b_RA
//#define DAC_DATA_SIZE_8b
#define HSE_VALUE 8000000


const uint16_t sin[32] = {

2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,

3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909,

599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647};





uint16_t a;

void Delay(unsigned int d)
{
  volatile uint32_t i;
  for (i=0; i !=d; i++);
}



void DMA_init (void)
{
        RCC->AHBENR |= RCC_AHBENR_DMA1EN;       // подаю такты на DMA1
        DMA1_Channel3->CCR |= DMA_CCR3_MSIZE_0;         // будем передавать 16 бит данных
        DMA1_Channel3->CCR |= DMA_CCR3_PSIZE_0;
        DMA1_Channel3->CCR |= DMA_CCR3_CIRC;    // цыклическая передача
        DMA1_Channel3->CCR |= DMA_CCR3_DIR;             // чтение с памяти
       // DMA1_Channel3->CCR |= DMA_CCR3_MINC;

        DMA1_Channel3->CNDTR = 1;                       // для того чтобы работало
        DMA1_Channel3->CPAR = (uint32_t) &DAC->DHR12R1;
        DMA1_Channel3->CMAR = (uint32_t) &a;

        DMA1_Channel3->CCR |= DMA_CCR3_EN;      // вкл. ПДП
}


void TIM6_init(void)
{
        RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;             // тактирование таймера

        TIM6->PSC = 0XFFFF;                             // предделитель
        TIM6->ARR = 244;                                // переполнение две секунды

        TIM6->DIER |= TIM_DIER_UIE;             // прерывание по переполнению
        TIM6->DIER |= TIM_DIER_UDE;             // влк. запуск ПДП

        TIM6->CR2 |= TIM_CR2_MMS_1;     // ЦАП будет запускаться по переполнению
        TIM6->CR1 |= TIM_CR1_CEN;               // запуск счета
}


void DAC_init(void)
{


	RCC->APB1ENR |= RCC_APB1ENR_DACEN;      // такты на ЦАП.
  //DAC->CR |= DAC_CR_BOFF1;                // выкл выходной буфер ЦАП1.
  //DAC->CR |= DAC_CR_BOFF2;                // выкл выходной буфер ЦАП2.
  //DAC->CR |= DAC_CR_TSEL1;                // ЦАП преобразования по команде программы.
  //DAC->CR |= DAC_CR_TEN1;                 // включение запуска от события ЦАП1.
  //DAC->CR |= DAC_CR_TEN2;                 // вкл. запуска от события ЦАП2.
    DAC->CR |= DAC_CR_EN1;                  // вкл. ЦАП1.
    DAC->CR |= DAC_CR_EN2;                  // вкл. ЦАП2.




}

void DAC_convertD(unsigned int data)
{
#ifdef DAC_DATA_SIZE_12b_LA
	DAC->DHR12LD = data;
#endif

#ifdef DAC_DATA_SIZE_12b_RA
	DAC->DHR12RD = data;
#endif

#ifdef DAC_DATA_SIZE_8b
	DAC->DHR8RD = data & 0xFFFF0000;
#endif
}

void DAC1_convert(uint16_t d)
{

#ifdef DAC_DATA_SIZE_12b_LA
 	DAC->DHR12L1 = d<<4;
#endif

#ifdef DAC_DATA_SIZE_12b_RA
	DAC->DHR12R1 = d;
#endif

#ifdef DAC_DATA_SIZE_8b
	DAC->DHR8R1 = (unsigned char)d;
#endif

}

void DAC2_convert(uint16_t d)
{

#ifdef DAC_DATA_SIZE_12b_LA
 	DAC->DHR12L2 = d<<4;
#endif

#ifdef DAC_DATA_SIZE_12b_RA
	DAC->DHR12R2 = d;
#endif

#ifdef DAC_DATA_SIZE_8b
	DAC->DHR8R2 = (unsigned char)d;
#endif

}





int main(void)
{
	//a = 2048;
	//TIM6_init();

	// DMA_init();
	 DAC_init();
	DAC1_convert(sin[a++]);
//	DAC2_convert(4095);



    while(1)
    {

    	unsigned int aaaaaaa;
    	aaaaaaa = (sin[a])<<8;
    //	aaaaaaa |= sin[a]
    	a++;

    	DAC_convertD(sin[a++]);
    //	DAC2_convert(sin[a]);

    	if(a==32)
    	{
    		a=0;
    	}
    	Delay(0x10);
    }
}
