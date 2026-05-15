[![Build](https://github.com/Beebird-Labs/Arduino-UNO-R4-VSS-Simulator/actions/workflows/build.yml/badge.svg)](https://github.com/Beebird-Labs/Arduino-UNO-R4-VSS-Simulator/actions/workflows/build.yml)

# Arduino UNO R4 VSS Simulator

This project is a Vehicle Speed Sensor (VSS) simulator for the Arduino Uno R4. It generates a simulated speed signal that ramps up and down, mimicking the output of a vehicle's speed sensor for testing purposes. This code simulates the VSS (or SPD) signal from a 2000 Toyota Crown, but it should work for any Toyota of that vintage and should be easily adaptable to other vehicles.

## Features

- VSS signal generation
- Speed ramps from 0 to 120 MPH and back down
- Random cycle durations for varied simulation
- Outputs on digital pin 7
- Serial output for monitoring

## Requirements

- Arduino Uno R4 board
- PlatformIO IDE (recommended) or Arduino IDE with PlatformIO extension
- USB cable for programming

## Setup

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/Arduino-UNO-R4-VSS-Simulator.git
   ```

2. Open the project in PlatformIO:
   - Launch PlatformIO IDE
   - Open the project folder

3. Build and upload:
   - Connect your Arduino Uno R4
   - Click "Upload" in PlatformIO

## Usage

1. Connect pin 7 of the Arduino to your speedometer input or testing device
2. Power on the Arduino
3. The simulator will start automatically, cycling through speed ramps
4. Monitor the serial output (115200 baud) for cycle information

## Configuration

You can modify the following constants in `src/main.cpp`:

- `VSS_PIN`: Output pin (default: 7)
- `HZ_PER_MPH`: Frequency multiplier per MPH (default: 1.139)
- `MAX_MPH`: Maximum simulated speed (default: 120.0)
- `MIN_LOOP_MS` / `MAX_LOOP_MS`: Range for cycle durations (15-45 seconds)

## How It Works

The simulator generates a square wave signal where the frequency is proportional to the simulated vehicle speed. The speed ramps up from 0 to 120 MPH, then back down to 0, with random cycle times. The phase is continuous to avoid glitches in connected systems.

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE).
