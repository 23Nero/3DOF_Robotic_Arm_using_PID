#include "./../include/LeNguyenKhanhLam.h"

volatile int stateHome = 0;

void sysInit(void)
{
  enaleClockModule();
  configGPIO();
  configTim();
  configUsart();
  configSysTickInt(NULL);
}

void enaleClockModule(void)
{
  /* Enable clock */
  RCC->AHB1ENR |= (1 << 0);  // Port A
  RCC->AHB1ENR |= (1 << 1);  // Port B
  RCC->AHB1ENR |= (1 << 2);  // Port C
  RCC->APB1ENR |= (1 << 17); // USART2
  RCC->APB1ENR |= (1 << 0);  // TIM2
  RCC->APB1ENR |= (1 << 1);  // TIM3
  RCC->APB1ENR |= (1 << 2);  // TIM4
  RCC->APB2ENR |= SYSCFGEN;  // Exti
}

void configTim(void)
{
  TIM_Stop(TIM2);
  TIM_Stop(TIM3);
  TIM_Stop(TIM4);
  /* Set timer2 channel 1 - PA0 */
  GPIO_setMode(GPIO_A, 0, ALTERNATE); // General purpose output mode
  GPIO_setAlternateFunction(GPIO_A, 0, AF1);

  TIM_Config(TIM2, PWM_PRESCALER, PWM_PERIOD, TIM_MODE_BASIC);

  TIM_ConfigOutputCompare(TIM2, CHANEL1, TIM_OCMODE1_PWM1);
  TIM_EnableOutputCompare(TIM2, CHANEL1, ACTIVE_HIGH);

  /* Set timer2 channel 2 - PA1 */
  GPIO_setMode(GPIO_A, 1, ALTERNATE); // General purpose output mode
  GPIO_setAlternateFunction(GPIO_A, 1, AF1);

  TIM_ConfigOutputCompare(TIM2, CHANEL2, TIM_OCMODE2_PWM1);
  TIM_EnableOutputCompare(TIM2, CHANEL2, ACTIVE_HIGH);

  //    /* Set timer2 channel 3 - PA2 */
  //    GPIO_setMode(GPIO_A, 2, ALTERNATE); // General purpose output mode
  //    GPIO_setAlternateFunction(GPIO_A, 2, AF1);

  //    TIM_ConfigOutputCompare(TIM2, CHANEL3, TIM_OCMODE2_PWM1);
  //    TIM_EnableOutputCompare(TIM2, CHANEL3, ACTIVE_HIGH);

  //    /* Set timer2 channel 4 - PA3 */
  //    GPIO_setMode(GPIO_A, 3, ALTERNATE); // General purpose output mode
  //    GPIO_setAlternateFunction(GPIO_A, 3, AF1);

  //    TIM_ConfigOutputCompare(TIM2, CHANEL4, TIM_OCMODE2_PWM1);
  //    TIM_EnableOutputCompare(TIM2, CHANEL4, ACTIVE_HIGH);

  /* Set timer3 channel 1 - PA6 */
  GPIO_setMode(GPIO_A, 6, ALTERNATE); // General purpose output mode
  GPIO_setAlternateFunction(GPIO_A, 6, AF2);

  TIM_Config(TIM3, PWM_PRESCALER, PWM_PERIOD, TIM_MODE_BASIC);

  TIM_ConfigOutputCompare(TIM3, CHANEL1, TIM_OCMODE1_PWM1);
  TIM_EnableOutputCompare(TIM3, CHANEL1, ACTIVE_HIGH);

  /* Set timer3 channel 2 - PA7 */
  GPIO_setMode(GPIO_A, 7, ALTERNATE); // General purpose output mode
  GPIO_setAlternateFunction(GPIO_A, 7, AF2);

  TIM_ConfigOutputCompare(TIM3, CHANEL2, TIM_OCMODE1_PWM1);
  TIM_EnableOutputCompare(TIM3, CHANEL2, ACTIVE_HIGH);

  /* Set timer3 channel 3 - PC8 */
  GPIO_setMode(GPIO_C, 8, ALTERNATE); // General purpose output mode
  GPIO_setAlternateFunction(GPIO_C, 8, AF2);

  TIM_ConfigOutputCompare(TIM3, CHANEL3, TIM_OCMODE1_PWM1);
  TIM_EnableOutputCompare(TIM3, CHANEL3, ACTIVE_HIGH);

  /* Set timer3 channel 4 - PC9 */
  GPIO_setMode(GPIO_A, 9, ALTERNATE); // General purpose output mode
  GPIO_setAlternateFunction(GPIO_A, 7, AF2);

  TIM_ConfigOutputCompare(TIM3, CHANEL2, TIM_OCMODE1_PWM1);
  TIM_EnableOutputCompare(TIM3, CHANEL2, ACTIVE_HIGH);

  TIM_Start(TIM2);
  TIM_Start(TIM3);

  TIM_Config(TIM4, 1600, 1000, TIM_MODE_BASIC);
  /*Enable interrupt TIM4*/
  TIM4->DIER |= (1 << 0);
  /*Enable IRQ tim4*/
  NVIC->ISER[0] |= (1 << 30);
  TIM_Start(TIM4);
}

void configGPIO(void)
{
  /* Set PB8 input */
  GPIO_setMode(GPIO_B, 8, INPUT);
  GPIO_setPullUpDown(GPIO_B, 8, PULL_UP);

  /* Enable interrupt EXTI8_9 */
  NVIC->ISER[0] |= (1 << 23);

  /* Select PORTB for EXTI8 */
  SYSCFG->EXTICR3 |= (1 << 0);
  /* Unmask EXTI8 */
  EXTI->IMR |= (1 << 8);
  /* Rising or Falling */
  EXTI->RTSR |= (1 << 8);

  /* Set PB9 input */
  GPIO_setMode(GPIO_B, 9, INPUT);
  GPIO_setPullUpDown(GPIO_B, 9, PULL_UP);

  GPIO_setMode(GPIO_C, 1, OUTPUT);
  GPIO_setMode(GPIO_C, 0, OUTPUT);

  GPIO_setMode(GPIO_C, 10, INPUT);
  GPIO_setPullUpDown(GPIO_C, 10, PULL_UP);
  /* Enable interrupt EXTI10_15 */
  NVIC->ISER[1] |= (1 << 8);

  /* Select PORTC for EXTI10 */
  SYSCFG->EXTICR3 |= (2 << 8);
  /* Unmask EXTI10 */
  EXTI->IMR |= (1 << 10);
  /* Rising or Falling */
  EXTI->RTSR |= (1 << 10);
}

void configUsart(void)
{
  // Configure Usart2
  NVIC->ISER[1] |= (1 << 6);
  GPIO_setMode(GPIO_A, 2, ALTERNATE);
  GPIO_setAlternateFunction(GPIO_A, 2, AF7);

  GPIO_setMode(GPIO_A, 3, ALTERNATE);
  GPIO_setAlternateFunction(GPIO_A, 3, AF7);

  uart_set_baudrate(USART2, SYSTEM_CORE_CLOCK, 115200);

  USART2->CR1 |= (1 << 3);
  USART2->CR1 |= (1 << 2);
  USART2->CR1 |= USART_CR1_RXNEIE;
  USART2->CR1 |= (1 << 13);
}

// Calculate the number of pulses corresponding to a specific angle (in radians)
int calculatePulses(float angle)
{
  double pulsesPerRevolution = 11.0 * 30.0;                                  // Number of pulses from the Encoder per revolution
  double pulsesEquivalent = (pulsesPerRevolution * (double)angle) / (360.0); // Calculate the equivalent pulses
  return (int)pulsesEquivalent;                                              // Return the number of pulses as an integer
}

void runBasePID(void)
{
  posBase = ((pulseBase * 360) / 1250);
  Ea = setBase - posBase;
  alpha1 = 2 * T * Kp1 + Ki1 * T * T + 2 * Kd1;
  beta1 = T * T * Ki1 - 4 * Kd1 - 2 * T * Kp1;
  gama1 = 2 * Kd1;
  outputBase = (alpha1 * Ea + beta1 * E1 + gama1 * E2 + 2 * T * lastoutputBase) / (2 * T);
  lastoutputBase = outputBase;
  E2 = E1;
  E1 = Ea;

  if (outputBase > 255)
  {
    outputBase = 255;
  }
  else if (outputBase < -255)
  {
    outputBase = -255;
  }
  if (outputBase > 0)
  {
    TIM_SetDutyCycle(TIM2, CHANEL1, (uint16_t)outputBase);
    GPIO_setPin(GPIO_C, 1);
    GPIO_resetPin(GPIO_C, 0);
  }
  else if (outputBase < 0)
  {
    TIM_SetDutyCycle(TIM2, CHANEL1, (uint16_t)-outputBase);
    GPIO_setPin(GPIO_C, 0);
    GPIO_resetPin(GPIO_C, 1);
  }
  else
  {
    GPIO_resetPin(GPIO_C, 0);
    GPIO_resetPin(GPIO_C, 1);
  }
}

void EXTI9_5_IRQHandler(void)
{
  if (GPIO_readPin(GPIO_B, 9))
    pulseBase--;
  else
    pulseBase++;
  sendData();
  EXTI->PR |= (1 << 8);
}


void sendData(void)
{
  char buffer[33];
  sprintf(buffer, "%d", pulseBase);
  USART_sendString(USART2, buffer);
  USART_sendString(USART2, "\n");
}
