
void SysTick_Handler(void);
void SysTick_Conf(int PERIOD);

void Systick_Set_IT(char Prio, void(*Systick_function)(void));
