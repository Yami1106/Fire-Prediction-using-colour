# Fire Prediction System using IoT Framework

## Overview

This project presents a comprehensive fire prediction system leveraging the Internet of Things (IoT) framework. The core functionality lies in a custom-designed neural network model, trained on user-collected fire and non-fire data, analyzing color sensor readings. This analysis enables the system to predict potential fire hazards. The system incorporates an MQ-2 gas sensor for enhanced detection of flammable gases or smoke, strengthening overall fire risk assessment.

## Key Features

- Custom-designed neural network model for fire prediction based on color sensor readings.
- Integration of MQ-2 gas sensor for enhanced detection of flammable gases or smoke.
- LCD screen displays temperature and humidity under normal circumstances.
- Immediate alerts triggered upon exceeding predefined thresholds:
  - High fire prediction probability (above 90%).
  - Significant gas concentration (MQ-2 sensor reading exceeding 400 ppm).
- Audible buzzer sounds and clear message displayed on the LCD screen in case of a fire threat.

## How It Works

1. The system continuously monitors color sensor readings and analyzes them using a custom neural network model.
2. Simultaneously, the MQ-2 gas sensor detects flammable gases/smoke.
3. Under normal circumstances, the LCD screen displays temperature and humidity.
4. If the fire prediction probability exceeds 90% or the gas concentration exceeds 400 ppm, the system triggers immediate alerts.
5. An audible buzzer sounds, and a clear message indicating the threat is displayed on the LCD screen.
