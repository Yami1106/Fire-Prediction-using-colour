<div align="center">

# Fire Prediction using Color Sensor + ML

![Stars](https://img.shields.io/github/stars/Yami1106/Fire-Prediction-using-colour?style=for-the-badge)
[![Jupyter](https://img.shields.io/badge/Jupyter-F37626?style=for-the-badge&logo=jupyter&logoColor=white)](https://jupyter.org)
[![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://python.org)

*Predicting fire hazards early using a color sensor and a neural network — lightweight edge ML + IoT integration.*

</div>

---

## Idea

Color changes are an early indicator of fire and smoke. This project trains a neural network on color sensor patterns from fire and non-fire environments, enabling **proactive fire detection** before a flame is fully established — earlier than traditional flame detectors.

---

## Pipeline

```
Color sensor readings → Feature extraction
                     → Neural network classifier (fire / no-fire)
                     → Confidence score → Alert threshold
```

---

## Dataset

- Collected color sensor readings (R, G, B, Clear, Color temperature, Lux) in controlled environments
- Two classes: **fire present** / **no fire**
- Augmented with varied lighting conditions and distances

---

## Model

- Lightweight neural network designed for **edge deployment**
- Binary classification with confidence output
- Trained and validated in Jupyter Notebook

---

## Results

- High accuracy on held-out test set
- Demonstrated feasibility of ML-based early fire detection using low-cost color sensors
- Integrated as the sensing layer of the Fire Aware Smart-Bot

---

## Tech stack

`Python` · `TensorFlow/Keras` · `NumPy` · `Pandas` · `Jupyter Notebook`

---

<div align="center">
<a href="https://github.com/Yami1106">Ashish Sukumar</a>
</div>
<!-- -->
