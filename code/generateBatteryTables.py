import numpy as np 
import math

R1 = 560000.0
R2 = 820000.0
maxSteps = 1024.0
Vcc = 3.3

voltDivision = R2 / (R1 + R2)


voltageValues = [2.1, 2.4, 2.7, 3.0, 3.05, 3.1, 3.15, 3.2, 3.25, 3.3, 3.35, 3.4, 3.45, 3.5, 3.55, 3.65, 3.7, 3.75, 3.8, 3.9, 4.0, 4.1, 4.17, 4.2]

multiplier = voltDivision * maxSteps / Vcc
voltageValues = np.multiply(voltageValues, multiplier)
voltageValues = voltageValues.astype(int)

for i in range(24):
	print(voltageValues[i]),
	print(','),

#print voltageValues