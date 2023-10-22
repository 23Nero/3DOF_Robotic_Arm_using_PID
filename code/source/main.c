#include "./../include/LeNguyenKhanhLam.h"

static char buff[BUFFER];
static volatile int stateStopBase = 0;

int main()
{
  sysInit();

  Kp1 = 30;
  Ki1 = 0.15;
  Kd1 = 0.85;

  while (1)
  {
    // do something

  }
}

void USART2_IRQHandler(void)
{
  if (USART2->SR & USART_SR_RXNE)
  {
    USART_receiveString(USART2, buff, BUFFER);
    if (sscanf(buff, "Base: %lf", &setBase) == 1)
    {
      stateHome = 0;
			stateStopBase = 0;
      USART_sendString(USART2, "Success!");
    }
    else if (sscanf(buff, "Home: %d", &stateHome) == 1)
    {
			stateStopBase = 0;
    }
  }
}
void EXTI15_10_IRQHandler(void)
 {
   if (GPIO_readPin(GPIO_C, 10))
   {
		 setBase = 0;
     stateHome = 0;
     pulseBase = 0;
		 TIM_SetDutyCycle(TIM2, CHANEL1, 0);
     GPIO_resetPin(GPIO_C, 0);
     GPIO_resetPin(GPIO_C, 1);
   }
   EXTI->PR |= (1 << 10);

 }

void TIM4_IRQHandler(void)
{
  if ((!stateHome) && (!stateStopBase))
  {
    runBasePID();
    sendData();
  }
  else if(stateHome && (!stateStopBase))
  {
		TIM_SetDutyCycle(TIM2, CHANEL1, 255);
    GPIO_setPin(GPIO_C, 1);
    GPIO_resetPin(GPIO_C, 0);
  }
	else if (stateStopBase)
	{
		TIM_SetDutyCycle(TIM2, CHANEL1, 0);
    GPIO_resetPin(GPIO_C, 1);
    GPIO_resetPin(GPIO_C, 0);
	}

  TIM4->SR &= ~(1u << 0);
}
