#include "./../include/timer.h"

// Hàm cấu hình timer với chu kỳ và chế độ cơ bản
void TIM_Config(timer_t *tim, uint32_t prescaler, uint32_t period, uint32_t mode)
{
    // Dừng timer trước khi cấu hình
    TIM_Stop(tim);

    // Cấu hình Prescaler và Period
    tim->PSC = prescaler - 1; // Đặt bộ chia tần số (chia tần số)
    tim->ARR = period - 1;    // Đặt giá trị tự động nạp (chu kì)

    // Cấu hình chế độ
    tim->CR1 |= mode; // Chế độ cơ bản

    // Xóa cờ Update (chờ cho lần đầu tiên)
    TIM_ClearUpdateInterruptFlag(tim);
}

// Hàm bắt đầu timer
void TIM_Start(timer_t *tim)
{
    tim->CR1 |= TIM_CR1_CEN; // Bật bit CEN để bắt đầu đếm
}

// Hàm dừng timer
void TIM_Stop(timer_t *tim)
{
    tim->CR1 &= ~TIM_CR1_CEN; // Tắt bit CEN để dừng đếm
}

// Hàm xác định trạng thái cờ Update
uint32_t TIM_GetUpdateInterruptStatus(timer_t *tim)
{
    return (tim->SR & TIM_SR_UIF);
}

// Hàm xóa cờ Update
void TIM_ClearUpdateInterruptFlag(timer_t *tim)
{
    tim->SR &= ~TIM_SR_UIF;
}

// Cấu hình chế độ Output Compare cho một kênh cụ thể của timer
void TIM_ConfigOutputCompare(timer_t *tim, uint8_t channel, uint32_t mode)
{
    // Đảm bảo timer đã tắt trước khi cấu hình
    tim->CR1 &= ~TIM_CR1_CEN;

    // Cấu hình chế độ Output Compare cho kênh cụ thể
    switch (channel)
    {
    case 1:
        // Thiết lập chế độ Output Compare cho kênh 1
        tim->CCMR1 &= ~(7U << 4); // Xóa các bits của chế độ
        tim->CCMR1 |= mode;       // Đặt chế độ mới
        break;

    case 2:
        // Thiết lập chế độ Output Compare cho kênh 2
        tim->CCMR1 &= ~(7U << 12); // Xóa các bits của chế độ
        tim->CCMR1 |= mode;        // Đặt chế độ mới
        break;

    case 3:
        // Thiết lập chế độ Output Compare cho kênh 3
        tim->CCMR2 &= ~(7U << 4); // Xóa các bits của chế độ
        tim->CCMR2 |= mode;       // Đặt chế độ mới
        break;

    case 4:
        // Thiết lập chế độ Output Compare cho kênh 4
        tim->CCMR2 &= ~(7U << 12); // Xóa các bits của chế độ
        tim->CCMR2 |= mode;        // Đặt chế độ mới
        break;

    default:
        // Xử lý ngoại lệ nếu kênh không hợp lệ
        break;
    }

    // Bật lại timer sau khi cấu hình xong
    tim->CR1 |= TIM_CR1_CEN;
}

// Đặt giá trị (duty cycle) cho kênh Output Compare cụ thể của timer
void TIM_SetDutyCycle(timer_t *tim, uint8_t channel, uint16_t dutyCycle)
{
    // Đảm bảo timer đã tắt trước khi cấu hình
    tim->CR1 &= ~TIM_CR1_CEN;

    // Đặt giá trị (duty cycle) cho kênh cụ thể
    switch (channel)
    {
    case 1:
        tim->CCR1 = dutyCycle;
        break;

    case 2:
        tim->CCR2 = dutyCycle;
        break;

    case 3:
        tim->CCR3 = dutyCycle;
        break;

    case 4:
        tim->CCR4 = dutyCycle;
        break;

    default:
        // Xử lý ngoại lệ nếu kênh không hợp lệ
        break;
    }

    // Bật lại timer sau khi cấu hình xong
    tim->CR1 |= TIM_CR1_CEN;
}

void TIM_EnableOutputCompare(timer_t *tim, uint8_t channel, int polarity)
{
    // Đảm bảo timer đã tắt trước khi cấu hình
    tim->CR1 &= ~TIM_CR1_CEN;

    // Bật kênh Output Compare cụ thể với chế độ polarity
    switch (channel)
    {
    case 1:
        if (polarity == ACTIVE_LOW )
        {
            tim->CCER |= TIM_CCER_CC1P; // Set CC1P bit for active low
        }
        else
        {
            tim->CCER &= ~TIM_CCER_CC1P; // Clear CC1P bit for active high
        }
        tim->CCER |= TIM_CCER_CC1E; // Enable CC1E bit
        break;

    case 2:
        if (polarity == ACTIVE_LOW )
        {
            tim->CCER |= TIM_CCER_CC2P; // Set CC2P bit for active low
        }
        else
        {
            tim->CCER &= ~TIM_CCER_CC2P; // Clear CC2P bit for active high
        }
        tim->CCER |= TIM_CCER_CC2E; // Enable CC2E bit
        break;

    case 3:
        if (polarity == ACTIVE_LOW )
        {
            tim->CCER |= TIM_CCER_CC3P; // Set CC3P bit for active low
        }
        else
        {
            tim->CCER &= ~TIM_CCER_CC3P; // Clear CC3P bit for active high
        }
        tim->CCER |= TIM_CCER_CC3E; // Enable CC3E bit
        break;

    case 4:
        if (polarity == ACTIVE_LOW )
        {
            tim->CCER |= TIM_CCER_CC4P; // Set CC4P bit for active low
        }
        else
        {
            tim->CCER &= ~TIM_CCER_CC4P; // Clear CC4P bit for active high
        }
        tim->CCER |= TIM_CCER_CC4E; // Enable CC4E bit
        break;

    default:
        // Xử lý ngoại lệ nếu kênh không hợp lệ
        break;
    }

    // Bật lại timer sau khi cấu hình xong
    tim->CR1 |= TIM_CR1_CEN;
}

// Tắt kênh Output Compare cụ thể của timer
void TIM_DisableOutputCompare(timer_t *tim, uint8_t channel)
{
    // Đảm bảo timer đã tắt trước khi cấu hình
    tim->CR1 &= ~TIM_CR1_CEN;

    // Tắt kênh Output Compare cụ thể
    switch (channel)
    {
    case 1:
        tim->CCER &= ~TIM_CCER_CC1E;
        break;

    case 2:
        tim->CCER &= ~TIM_CCER_CC2E;
        break;

    case 3:
        tim->CCER &= ~TIM_CCER_CC3E;
        break;

    case 4:
        tim->CCER &= ~TIM_CCER_CC4E;
        break;

    default:
        // Xử lý ngoại lệ nếu kênh không hợp lệ
        break;
    }

    // Bật lại timer sau khi cấu hình xong
    tim->CR1 |= TIM_CR1_CEN;
}

// Cấu hình chế độ Input Capture cho một kênh cụ thể của timer
void TIM_ConfigInputCapture(timer_t *tim, uint8_t channel, uint32_t mode)
{
    // Đảm bảo timer đã tắt trước khi cấu hình
    tim->CR1 &= ~TIM_CR1_CEN;

    // Cấu hình chế độ Input Capture cho kênh cụ thể
    switch (channel)
    {
    case 1:
        // Thiết lập chế độ Input Capture cho kênh 1
        tim->CCMR1 &= ~(3U << 0); // Xóa các bits của chế độ
        tim->CCMR1 |= (mode); // Đặt chế độ mới
        break;

    case 2:
        // Thiết lập chế độ Input Capture cho kênh 2
        tim->CCMR1 &= ~(3U << 8); // Xóa các bits của chế độ
        tim->CCMR1 |= (mode); // Đặt chế độ mới
        break;

    case 3:
        // Thiết lập chế độ Input Capture cho kênh 3
        tim->CCMR2 &= ~(3U << 0); // Xóa các bits của chế độ
        tim->CCMR2 |= (mode); // Đặt chế độ mới
        break;

    case 4:
        // Thiết lập chế độ Input Capture cho kênh 4
        tim->CCMR2 &= ~(3U << 8); // Xóa các bits của chế độ
        tim->CCMR2 |= (mode); // Đặt chế độ mới
        break;

    default:
        // Xử lý ngoại lệ nếu kênh không hợp lệ
        break;
    }

    // Bật lại timer sau khi cấu hình xong
    tim->CR1 |= TIM_CR1_CEN;
}

// Đọc giá trị đã capture từ kênh Input Capture cụ thể
uint32_t TIM_ReadCapturedValue(timer_t *tim, uint8_t channel)
{
    uint32_t capturedValue = 0;

    // Đọc giá trị đã capture từ kênh cụ thể
    switch (channel)
    {
    case 1:
        capturedValue = tim->CCR1;
        break;

    case 2:
        capturedValue = tim->CCR2;
        break;

    case 3:
        capturedValue = tim->CCR3;
        break;

    case 4:
        capturedValue = tim->CCR4;
        break;

    default:
        // Xử lý ngoại lệ nếu kênh không hợp lệ
        break;
    }

    return capturedValue;
}

// Xóa cờ Capture/Compare cụ thể sau khi đã đọc giá trị đã capture
void TIM_ClearCaptureFlag(timer_t *tim, uint8_t channel)
{
    // Xóa cờ Capture/Compare cụ thể
    switch (channel)
    {
    case 1:
        tim->SR &= ~TIM_SR_CC1IF;
        break;

    case 2:
        tim->SR &= ~TIM_SR_CC2IF;
        break;

    case 3:
        tim->SR &= ~TIM_SR_CC3IF;
        break;

    case 4:
        tim->SR &= ~TIM_SR_CC4IF;
        break;

    default:
        // Xử lý ngoại lệ nếu kênh không hợp lệ
        break;
    }
}
