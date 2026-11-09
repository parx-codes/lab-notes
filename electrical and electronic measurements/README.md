# Electrical and Electronic Measurements

My STM32CubeIDE lab exercises for the STM32F303VC. The projects use peripheral registers directly to work with GPIO and timers.

| Exercise | What it does |
| --- | --- |
| [01 · Digital outputs](01-digital-outputs/) | Configures GPIO pins as outputs and drives two LEDs. |
| [02 · Button-controlled LEDs](02-button-controlled-leds/) | Reads the USER button and switches the LEDs on or off. |
| [03 · Button press timer](03-button-press-timer/) | Uses TIM2 to count how long the USER button is held. |
| [04 · One-second LED blink](04-one-second-led-blink/) | Toggles the LEDs at one-second intervals. |
| [05 · TIM6 LED blink](05-tim6-led-blink/) | Polls the TIM6 update flag to toggle the LEDs periodically. |

Import an exercise folder into STM32CubeIDE as an existing project, then build it for the STM32F303VC. Each folder contains the source, project settings, and its CubeMX configuration.
