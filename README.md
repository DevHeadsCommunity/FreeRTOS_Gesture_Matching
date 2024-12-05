# **Gesture Matching with MPU-6050 and STM32 using FreeRTOS**

This project collects motion data by using a MPU-6050 sensor and STM32 microcontoller after that with the help of tensorflow-lite-micro it recongnize the gesture accoring to our pre trained model

---

## **Features**
- **Real-Time Data Acquisition**: Captures accelerometer and gyroscope data from the MPU-6050.
- **Task Scheduling with FreeRTOS**:
  - Sensor reading task.
  - Data processing task (optional filtering or transformations).
  - Communication task to send collected data to a PC via UART/USB.
- **Gesture Recognigation**: Reconigation Various gesture and log it for better visiblity

---

## **Hardware Requirements**
1. **STM32 Microcontroller**: Any STM32 board with I2C and UART capabilities (e.g., STM32F4, STM32F103).
2. **MPU-6050 Sensor**: IMU sensor with a 3-axis accelerometer and gyroscope.
3. **USB-to-Serial Adapter**: For transmitting data to a PC(Not Require if you are using a STM32 Nucleo board since it is already built in).
4. **Power Supply**: USB or battery-powered STM32 board.

---

## **Software Requirements**
1. **Development Tools**: Code IDE or Code Editor
2. **FreeRTOS**: For real-time task management.
3. **Serial Monitoring Software**: Tools like PuTTY, Tera Term, or CoolTerm to log data on a Windows PC and screen, minicom like package for linux.

---

## **Getting Started**
### 1. **Hardware Setup**
- **Connect the MPU-6050** to the STM32:
  - **I2C Pins**:
    - SDA → STM32 I2C SDA pin.
    - SCL → STM32 I2C SCL pin.
  - **Power Pins**:
    - VCC → 3.3V or 5V.
    - GND → Ground.
- Connect the STM32 UART pins to the USB-to-Serial Adapter.

### 2. **FreeRTOS Task Overview**
| Task Name            | Description                                      |
|----------------------|--------------------------------------------------|
| **SensorTask**       | Reads accelerometer and gyroscope data from MPU-6050. |
| **ProcessingTask**   | Process data and Match the Gesture                    |
| **CommunicationTask**| Sends data to the PC via UART/USB.                    |

---

## **Workflow**
1. **Set Up and Flash Firmware**:
   - Use STM32CubeMX to configure:
     - I2C for communicating with the MPU-6050.
     - UART for serial communication.
     - FreeRTOS for task scheduling.
   - Write code for the tasks listed above.
   - Compile and flash the code onto the STM32 board using STM32CubeIDE.

3. **Logging Data**:
   - Use a serial monitor to log the name of the gesture or the Accelerometer and Gyroscope Axis's.
---

  
## **References**
- [MPU-6050 Datasheet](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/)
- [STM32 FreeRTOS Guide](https://www.freertos.org/RTOS.html)
- [Serial Communication with STM32](https://www.st.com/en/microcontrollers-microprocessors/stm32.html)

