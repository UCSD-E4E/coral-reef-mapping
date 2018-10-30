import numpy as np 
import math

num_values = 360;

offset = math.pi/num_values

angles = [0] * (int)(num_values/4.0)

for i in range(len(angles)):
	angles[i] =  (i + 1) * (math.pi / (num_values/2)) - offset

# print(np.multiply(angles, 180/math.pi))



tan_angles = np.tan(angles)

tan_angles = tan_angles * math.pow(2, 17)
print(tan_angles)

hi = tan_angles.astype(int)


print(hi, sep = ",kjhfaksfahkljsdhafljk ")

#for i in range(len(hi)):
#	print(str(hi[i]) + ',')
