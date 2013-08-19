
#include<stm32f10x_rcc.h>
#include<stm32f10x_gpio.h>
#include "stm32f10x.h"
void delay(uint32_t i) {
 volatile uint32_t j;
 for (j=0; j!= i * 1000; j++)
  ;
}

int main(void)
{
  GPIO_InitTypeDef PORT;
  //�������� ����� � � �
  RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA) , ENABLE);
  //����������� ���� PC8 � PC9 �� �����. ��� � ��� ����� ����������
  PORT.GPIO_Pin = (GPIO_Pin_4 | GPIO_Pin_3|GPIO_Pin_5);
  PORT.GPIO_Mode = GPIO_Mode_Out_PP;
  PORT.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init( GPIOC , &PORT);
  //���� A ����������� ������ ���, ��� ��� ���� �� ��������� ����� ��� ��� � �����
  RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC1EN, ENABLE); //�������� ������������ ���
  ADC1->CR2 |= ADC_CR2_CAL; //������ ���������� ���
  while (!(ADC1->CR2 & ADC_CR2_CAL))
    ; //������� ��������� ����������
  ADC1->SMPR2 |= (ADC_SMPR2_SMP1_2 | ADC_SMPR2_SMP1_1 | ADC_SMPR2_SMP1_0); //������
                                                                                            // ������������ �������
  ADC1->CR2 |= ADC_CR2_JEXTSEL; //�������������� ��������������� ������
                                                       //���������� ���������� ���� JSWSTART
  ADC1->CR2 |= ADC_CR2_JEXTTRIG; //��������� ������� ������ ��������������� ������
  ADC1->CR2 |= ADC_CR2_CONT; //�������������� ����������� ���� �� ������
  ADC1->CR1 |= ADC_CR1_JAUTO; //��������� �������������� ��������������� ������
                                     //����� ����������. �� ������� �����, �� ��� ����� �� ��������
  ADC1->JSQR |= (10<<15); //������ ����� ������ (������ ADC1)
  ADC1->CR2 |= ADC_CR2_ADON;//������ �������� ���
  ADC1->CR2 |= ADC_CR2_JSWSTART; //������ ��������������
  while (!(ADC1->SR & ADC_SR_JEOC)) //���� ���� ������ �������������� ����������
    ;
  //������ ����� ������ ��������� �� JDR1
  uint32_t adc_res; //����������� ���������� ��� �������. ����� � ��� ��
  while(1)
  {
    adc_res=ADC1->JDR1;
    delay(adc_res); //������ �� �������� ��� ������ ��������
    GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_RESET);
    GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_SET);
    GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_RESET);
   // adc_res=ADC1->JDR1;
    delay(adc_res); //�� �����������...
    GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_RESET);
    GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_SET);
    GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_RESET);
    delay(adc_res);
    GPIO_WriteBit(GPIOC,GPIO_Pin_4,Bit_RESET);
        GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_RESET);
        GPIO_WriteBit(GPIOC,GPIO_Pin_5,Bit_SET);
  }
}
