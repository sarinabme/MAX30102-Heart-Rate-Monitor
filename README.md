# Arduino Heart Rate Monitor❤️

> A real-time heart rate monitoring prototype using **Arduino UNO** and the **MAX30102 PPG sensor**.

<br>

## Overview

This project is an **Arduino-based heart rate monitoring prototype** developed using the **Arduino UNO** and the **MAX30102 optical pulse sensor**.

The system measures pulse signals using **photoplethysmography (PPG)**, calculates heart rate in **beats per minute (BPM)**, and displays the average measurement on a **16×2 I2C LCD**.

Based on **predefined BPM thresholds**, the measured heart rate is classified as **NORMAL**, **BRADYCARDIA**, or **TACHYCARDIA**. An audible **buzzer** provides feedback when the measured value falls outside the predefined normal range.

The prototype is designed as an **educational biomedical engineering project** to demonstrate the integration of **biosensors, microcontrollers, real-time signal acquisition, user feedback, and basic heart-rate classification**.

<br>

## 📸 Project Media

### 🧩 Hardware Setup

![Hardware Setup](media/images/hardware-setup.jpg)

The complete prototype, including the **Arduino UNO, MAX30102 pulse sensor, 16×2 I2C LCD, buzzer, breadboard, and connecting wires**.

### ⚙️ System Initialization

![System Initialization](media/images/system-startup.jpg)

The system initializes the heart-rate monitoring hardware and prepares the sensor for measurement.

### ❤️ Real-Time Measurement

![Real-Time Measurement](media/images/measuring.JPG)

During the measurement phase, the system continuously acquires pulse data while displaying the **remaining measurement time** on the LCD.

### 🔎 Data Analysis

![Data Analysis](media/images/analyzing.PNG)

After the **20-second measurement window**, the collected BPM data is processed to calculate the **average heart rate**.

### 📊 Normal Heart Rate Results

![74 BPM Normal](media/images/normal-74-bpm.jpg)

![83 BPM Normal](media/images/normal-83-bpm.PNG)

Example measurements classified as **NORMAL** according to the predefined BPM thresholds implemented in the program.

### 🎥 Demonstration Videos

#### Bradycardia Detection

[▶️ Watch the Bradycardia Detection Demo](media/videos/bradycardia-detection.mp4)

Demonstration of a low heart-rate measurement resulting in a **`BRADYCARDIA`** classification and an audible **buzzer alert**.

#### Full Measurement Cycle

[▶️ Watch the Full Measurement Cycle](media/videos/full-measurement-cycle.mp4)

Demonstration of the measurement workflow, from **system initialization and finger detection** to **BPM calculation, classification, and test reset**.

#### No Reading Handling

[▶️ Watch the No Reading Demo](media/videos/no-reading-handling.mp4)

Demonstration of the system response when **no valid heart-rate measurement is obtained**.
