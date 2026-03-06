# 🌡️ Temperature Monitoring and Visual Indicator System

An embedded system project built with **Arduino and TMP36** that measures ambient temperature, displays it on an **I2C LCD**, and visualizes temperature levels using an **LED bar indicator with overheat warning**.

This project was developed **incrementally in phases** to understand core embedded systems concepts such as sensor interfacing, ADC conversion, signal filtering, and modular software design.

---

# 📌 Project Overview

The system reads analog voltage from a **TMP36 temperature sensor**, converts it into temperature using Arduino’s **10-bit ADC**, and displays the result through:

- **LED bar indicator** showing temperature levels  
- **16×2 LCD display** showing exact temperature  
- **Overheat warning system**

If the temperature exceeds **45°C**, the system triggers an alert by displaying **OVERHEAT!** on the LCD and blinking the last LED.

---

# 🏗️ System Architecture

```
TMP36 Sensor
     │
     ▼
Arduino ADC
     │
     ▼
Moving Average Filter
     │
     ▼
Temperature Calculation
     │
     ▼
Decision Logic
   │        │
   ▼        ▼
LED Bar    LCD Display
Indicator  (Temp + Status)
```

This represents a typical **embedded monitoring pipeline**:

**Sensor → Signal Processing → Decision Logic → User Interface**

---

# 🔧 Hardware Components

- Arduino Uno R3  
- TMP36 Temperature Sensor  
- 8 LEDs  
- 8 × 220Ω resistors  
- 16×2 LCD with **PCF8574 I2C module**  
- Breadboard  
- Jumper wires  

---

# 💻 Software Requirements

- Arduino IDE  
- LiquidCrystal_I2C Library  
- Tinkercad Circuits Simulator  

---

# 🔌 Circuit Connections

## TMP36 Sensor

| TMP36 Pin | Arduino |
|-----------|---------|
|    VCC    | 5V      |
|    Vout   | A0      |
|    GND    | GND     |

---

## LCD (I2C)

| LCD Pin | Arduino |
|---------|---------|
|   VCC   | 5V      |
|   GND   | GND     |
|   SDA   | A4      |
|   SCL   | A5      |

---

## LED Bar Indicator

| LED  | Arduino Pin |
|------|-------------|
| LED1 |     2       |
| LED2 |     3       |
| LED3 |     4       |
| LED4 |     5       |
| LED5 |     6       |
| LED6 |     7       |
| LED7 |     8       |
| LED8 |     9       |

---

# ⚙️ Working Principle

1. The **TMP36 sensor outputs analog voltage proportional to temperature**.  
2. Arduino reads the signal using its **10-bit ADC (0–1023)**.  
3. A **moving average filter** is applied to stabilize sensor readings.  
4. Temperature is calculated using the TMP36 transfer function.  
5. The temperature value is:  
   - displayed numerically on the LCD  
   - mapped to an LED bar using linear scaling  
6. If temperature exceeds **45°C**, the system triggers an overheat warning.

---

# 🧠 Key Algorithms

## ADC Voltage Conversion

```
Voltage = (ADC × 5.0) / 1023.0
```

---

## Temperature Conversion

```
Temperature = (Voltage − 0.5) × 100.0
```

---

## Linear Scaling for LED Indicator

```
LED = ((Temperature − Tmin) × N) / (Tmax − Tmin)
```

Where:

```
Tmin = 10°C
Tmax = 50°C
N = 8 LEDs
```

LED Visualisation Example:
```
Temp = 15°C → ■□□□□□□□
Temp = 25°C → ■■■□□□□□
Temp = 35°C → ■■■■■□□□
Temp = 45°C → ■■■■■■■□
```

---

# 📉 Noise Filtering

To reduce fluctuations in ADC readings, a **moving average filter** is used.

```
Take 15 ADC samples
Delay 5 ms between samples
Compute the average
```

This improves **measurement stability**.

---

# 🚨 Overheat Warning Logic

Condition:

```
Temperature > 45°C
```

System Response:

- LCD displays **OVERHEAT!**  
- Last LED blinks  
- Remaining LEDs continue to represent temperature level  

---

Visual Behavior:
```
Normal Condition
■■■■■□□□

Overheat Condition
■■■■■■■▣ (blinking)
```

# 🧩 Software Structure

The program follows a **modular embedded design**.

```
loop()
 ├── readTemperature()
 ├── updateLEDBar()
 ├── updateLCD()
 └── handleOverheat()
```

Benefits:

- Clear program structure  
- Easier debugging  
- Scalable for future improvements  

---

# 🛠️ Development Phases

### Phase 0 – Fundamentals
Studied:

- Analog vs digital signals  
- ADC resolution  
- TMP36 sensor characteristics  

---

### Phase 1 – Sensor Interfacing
Implemented:

- ADC reading  
- Temperature calculation  
- Serial monitoring  

---

### Phase 2 – LED Temperature Indicator
Implemented **linear scaling algorithm** for LED visualization.

---

### Phase 3 – Signal Stabilization
Added **moving average filtering** to reduce sensor noise.

---

### Phase 4 – LCD Integration
Integrated **I2C LCD display** for real-time temperature visualization.

During debugging, the LCD initially failed due to an **MCP23008 vs PCF8574 I2C backpack mismatch**, which was resolved by switching to **PCF8574 with address 0x27**.

---

### Phase 5 – Overheat Alert
Added warning system when temperature exceeds safe limits.

---

# 📚 Learning Outcomes

Through this project, the following embedded system concepts were practiced:

- Sensor interfacing  
- Analog-to-Digital Conversion  
- Signal filtering  
- Linear scaling algorithms  
- I2C communication  
- Modular embedded programming  
- Real-time monitoring and alert systems  

---

# 🚀 Possible Improvements

Future upgrades could include:

- Hysteresis to prevent LED flickering  
- Wireless monitoring using ESP32  
- Data logging using an SD card  
- OLED graphical display  
- PID temperature control system  

---

# 📜 License

This project is open source and available for learning and experimentation.
