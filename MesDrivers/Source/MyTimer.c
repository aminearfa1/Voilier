#include "../Include/MyTimer.h"


void (* pointer1) (void);
void (* pointer2) (void);
void (* pointer3) (void);
void (* pointer4) (void);




// Initialize TIMER
void MyTimer_Base_Init (TIM_TypeDef * Timer, unsigned short ARR, unsigned short PSC) {
	if (Timer == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	else if (Timer == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	else if (Timer == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	else if (Timer == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	else
		return;
	
	Timer->PSC = PSC;
	Timer->ARR = ARR;
}

// Activate Interruption
void MyTimer_ActiveIT  (TIM_TypeDef * Timer , char Prio , void (*IT_function ) (void) ) 
{
	Timer->DIER |= TIM_DIER_UIE;
	if(Timer==TIM1){
		NVIC_SetPriority(TIM1_UP_IRQn, Prio);
		NVIC_EnableIRQ(TIM1_UP_IRQn);
		pointer1 = IT_function;
	}
	if(Timer==TIM2){
		NVIC_SetPriority(TIM2_IRQn, Prio);
		NVIC_EnableIRQ(TIM2_IRQn);
		pointer2 = IT_function;
	}else if(Timer==TIM3){
		NVIC_SetPriority(TIM3_IRQn, Prio);
		NVIC_EnableIRQ(TIM3_IRQn);
		pointer3 = IT_function;
	}else if(Timer==TIM4){
		NVIC_SetPriority(TIM4_IRQn, Prio);
		NVIC_EnableIRQ(TIM4_IRQn);
		pointer4 = IT_function;
	}
}

// Initialize PWM
void MyTimer_PWM_Init (TIM_TypeDef * Timer , char Channel ) 
{	
	//TIMx control register 1 (TIMx_CR1) / RPE: Auto-reload preload enable
	Timer -> CR1 |= TIM_CR1_ARPE; 
	//TIMx event generation register (TIMx_EGR) / UG: Update generation
	Timer -> EGR |= TIM_EGR_UG;
	switch(Channel){
		case 1:
			//TIMx capture/compare enable register (TIMx_CCER) / CCxE: Capture/Compare x output enable
			Timer->CCER |= TIM_CCER_CC1E;
			//Reset all the bits
			Timer -> CCMR1 &=~ (TIM_CCMR1_OC1M);
			//TIMx capture/compare mode register x (TIMx_CCMRx) / OC1M: Output compare 1 mode OC2PE: Output compare 2 preload enable
			Timer -> CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE; //PWM mode 1
			//Timer -> CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC1PE; //PWM mode 2
		break;
		case 2:
			//TIMx capture/compare enable register (TIMx_CCER) / CCxE: Capture/Compare x output enable
			Timer->CCER |= TIM_CCER_CC2E;
			//Reset all the bits
			Timer -> CCMR1 &=~ (TIM_CCMR1_OC2M);
			//TIMx capture/compare mode register x (TIMx_CCMRx) / OC1M: Output compare 1 mode OC2PE: Output compare 2 preload enable
			Timer -> CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC2PE; //PWM mode 1
			//Timer -> CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE; //PWM mode 2
			break;
		case 3:
			//TIMx capture/compare enable register (TIMx_CCER) / CCxE: Capture/Compare x output enable
			Timer->CCER |= TIM_CCER_CC3E;
			//Reset all the bits
			Timer -> CCMR2 &=~ (TIM_CCMR2_OC3M);
			//TIMx capture/compare mode register x (TIMx_CCMRx) / OC1M: Output compare 1 mode OC2PE: Output compare 2 preload enable
			Timer -> CCMR2 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR2_OC3PE; //PWM mode 1
			//Timer -> CCMR2 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR2_OC3PE; //PWM mode 2
			break;
		case 4:
			//TIMx capture/compare enable register (TIMx_CCER) / CCxE: Capture/Compare x output enable
			Timer->CCER |= TIM_CCER_CC4E;
			//Reset all the bits
			Timer -> CCMR2 &=~ (TIM_CCMR2_OC4M);
			//TIMx capture/compare mode register x (TIMx_CCMRx) / OC1M: Output compare 1 mode OC2PE: Output compare 2 preload enable
			Timer -> CCMR2 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR2_OC4PE; //PWM mode 1
			//Timer -> CCMR2 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR2_OC4PE; //PWM mode 2
			break;
	}

}

// Configuration of PWM ratio
void MyTimer_PWM_ConfigureRatio(TIM_TypeDef * Timer, char Channel, int Ratio){
	int r = (Ratio * Timer->ARR) / 100;
	uint16_t value = (uint16_t) r;
	//TIMx capture/compare register 1 (TIMx_CCR1)
	switch(Channel){
		case 1:
			Timer->CCR1 = value;
			break;
		case 2:
			Timer->CCR2 = value;
			break;
		case 3:
			Timer->CCR3 = value;
			break;
		case 4:
			Timer->CCR4 = value;
			break;
		default:
			break;
	}
}

//Mode Incrémental
void MyTimer_Codeur_Incremental_Init(TIM_TypeDef * Timer){
	Timer->CCMR1 &= ~(TIM_CCMR1_CC1S |TIM_CCMR1_CC2S);
	Timer->CCMR1 |= TIM_CCMR1_CC1S_0 |TIM_CCMR1_CC2S_0;
	Timer->SMCR &= ~(TIM_SMCR_SMS) ;
	Timer->SMCR |= TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0 ;
	Timer->CCER &=~(TIM_CCER_CC1P |TIM_CCER_CC2P | TIM_CCER_CC1NP | TIM_CCER_CC2NP);
}

void TIM2_IRQHandler( void)
{
	TIM2->SR &= ~TIM_SR_UIF; //scruter
	if (pointer2 !=0)
		pointer2 ();
}
//mettre à jour CCRX

	void setCycle_PWM(TIM_TypeDef * Timer, char Channel, int cycle) {
		
		if (Channel == 1) {
			Timer->CCR1 = ((Timer->ARR + 1)* cycle)/100 ; 
		} else if (Channel==2) {
			Timer->CCR2 = ((Timer->ARR + 1)* cycle)/100 ; 
		} else if (Channel==3) {
			Timer->CCR3 = ((Timer->ARR + 1)* cycle)/100 ; 
		} else if (Channel==4) {
			Timer->CCR4 = ((Timer->ARR + 1)* cycle)/100 ; 
		}
}
