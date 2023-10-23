
# 3-DOF Robotic Arm Control with PID using Encoder Motors



A 3-DOF (Three Degrees of Freedom) robotic arm is a versatile and essential tool in the field of automation and robotics. This robotic arm employs encoder motors to precisely control and monitor its position and movement. The integration of a PID (Proportional-Integral-Derivative) control system enhances its accuracy and stability, making it a reliable choice for a wide range of applications.




## PID controller
A PID Controller is a commonly used automatic control system in engineering and automation. "PID" stands for Proportional-Integral-Derivative, which are the three main components of this system. The PID Controller operates by adjusting an output based on the comparison between the current input value and the desired target value. The three basic PID components are:

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/4/40/Pid-feedback-nct-int-correct.png/450px-Pid-feedback-nct-int-correct.png">

 - Proportional (P): It adjusts the output based on the difference between the current input value and the target value. This helps reduce errors but can lead to oscillations.
 - Integral (I): It is the time integral of the error. It helps eliminate any residual errors after the P stage, ensuring the system reaches the target value without ever reaching equilibrium.
 - Derivative (D): It takes the derivative of the error. This helps control the rate of change of the output, reducing oscillations and stabilizing the system.

# USART2 Interrupt-based Data Handling

This repository contains code for handling data received through USART2 interrupts on a microcontroller. The code extracts and processes incoming data based on specific patterns and triggers actions accordingly.

## Table of Contents

- [Introduction](#introduction)
- [Usage](#usage)
- [Code Explanation](#code-explanation)
- [Author](#author)

## Introduction

The provided code demonstrates how to work with USART2 interrupts to receive and process data in various formats. It is particularly useful for scenarios where you need to interact with a microcontroller through a serial communication interface.

## Usage

1. **Include the Code**: You can incorporate this code into your microcontroller project to enable USART2 interrupt handling. Make sure to adapt the code to your specific requirements.

2. **Define Variables**: Define the necessary variables and buffer sizes as needed for your project.

3. **Customize Data Parsing**: In the `USART2_IRQHandler` function, data is parsed based on specific patterns within the received strings. Customize the format strings and variables to match your data format.

4. **Response Handling**: Modify the response actions as required. In the example, variables (`setBase`, `stateHome`, `stateStopBase`, `Kp1`, `Ki1`, and `Kd1`) are adjusted based on the received data.

## Code Explanation

### USART2_IRQHandler

- Handles USART2 interrupts.
- Receives data and checks if it matches specific patterns.
- Sets variables and sends responses accordingly.

### EXTI15_10_IRQHandler

- Handles external interrupts on GPIO pin C10.
- Resets variables and GPIO pins based on the external interrupt event.

### TIM4_IRQHandler

- Handles Timer 4 interrupts.
- Executes control logic and sends data depending on the values of `stateHome` and `stateStopBase`.

### runBasePID

- Implements a PID control algorithm to control a motor or other system.
- Calculates various control variables and sets motor duty cycle.



## Author

- Name: Lam Khanh Nguyen Le
- Github: [23Nero](https://github.com/23Nero)
- 
