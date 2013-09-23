// Peripheral initalization




uint16_t ADC_buff[3];
// Dac initalization
void DAC_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;      // вкл. тактирование ЦАП
	DAC->CR |= DAC_CR_EN1;
}

void USART2_init(unsigned int baud)
{
	         GPIO_InitTypeDef GPIO_init_structure;
			 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC, ENABLE);
			 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
			  // set Pin TxD (PA9) to push-pull mode with Alternate Function (AF).
			  GPIO_init_structure.GPIO_Pin = GPIO_Pin_2;
			  GPIO_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
			  GPIO_init_structure.GPIO_Mode = GPIO_Mode_AF_PP;
			  GPIO_Init(GPIOA, &GPIO_init_structure);
			  GPIO_init_structure.GPIO_Pin = GPIO_Pin_6;
			  GPIO_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
			  GPIO_init_structure.GPIO_Mode = GPIO_Mode_Out_PP;
     		  GPIO_Init(GPIOC,&GPIO_init_structure);
			  GPIO_init_structure.GPIO_Pin = GPIO_Pin_3;
			  GPIO_init_structure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			  GPIO_Init(GPIOA, &GPIO_init_structure);

			  USART_InitTypeDef USART_InitStructure;
			  USART_InitStructure.USART_BaudRate = baud;
			  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			  USART_InitStructure.USART_Parity = USART_Parity_No;
			  USART_InitStructure.USART_StopBits = USART_StopBits_1;
			  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			  USART_Init(USART2,&USART_InitStructure);
			  USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
			  USART_Cmd(USART2,ENABLE);


}

void ADC_init(void)
{
	 RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC1EN, ENABLE); //Включаем тактирование АЦП
		  RCC_AHBPeriphClockCmd ( RCC_AHBPeriph_DMA1 , ENABLE ) ;



		  ADC_InitTypeDef ADC_InitStructure;
		  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent ;
		  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		  ADC_InitStructure.ADC_NbrOfChannel = 3;
		  ADC_RegularChannelConfig(ADC1,ADC_Channel_10, 1,ADC_SampleTime_239Cycles5); // define regular conversion config
		  ADC_RegularChannelConfig(ADC1,ADC_Channel_11, 2,ADC_SampleTime_239Cycles5);
		  ADC_RegularChannelConfig(ADC1,ADC_Channel_12, 3,ADC_SampleTime_239Cycles5);

		  	ADC_Init (ADC1, &ADC_InitStructure);	//set config of ADC1
		  	ADC_DMACmd(ADC1,ENABLE);

		  // enable ADC
		  	ADC_Cmd (ADC1,ENABLE);	//enable ADC1

		  //	ADC calibration (optional, but recommended at power on)
		  	ADC_ResetCalibration(ADC1);	// Reset previous calibration
		  	while(ADC_GetResetCalibrationStatus(ADC1));
		  	ADC_StartCalibration(ADC1);	// Start new calibration (ADC must be off at that time)
		  	while(ADC_GetCalibrationStatus(ADC1));

		  // start conversion
		  	ADC_Cmd (ADC1,ENABLE);	//enable ADC1
		  	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

		  	DMA_InitTypeDef DMA_InitStructure;
		  		  		  	DMA_InitStructure.DMA_BufferSize = 3;
		  		  		  	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		  		  		  	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		  		  		  	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_buff[0];
		  		  		  	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		  		  		  	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		  		  		  	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		  		  		  	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
		  		  		  	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		  		  		  	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		  		  		  	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		  		  		  	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
		  		  		  	DMA_Cmd ( DMA1_Channel1 , ENABLE ) ;
}
