import matplotlib.pyplot as plt
import sys
fig1 = plt.figure(1)
ax1 = plt.axes()
y1 = []
for i in range(10):
    y1.append(float(sys.argv[i+1]))
x1 = [0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4]
ax1.set_xlabel("Time to maturity")
ax1.set_ylabel("Implied Volatility")
plt.plot(x1, y1)
fig2 = plt.figure(2)
ax2 = plt.axes()
y2 = []
for i in range(10):
    y2.append(float(sys.argv[i+10]))
x2 = [55, 56, 57, 58, 59, 60, 61, 62, 63, 64]
ax2.set_xlabel("Strike Price")
ax2.set_ylabel("Implied Volatility")
plt.plot(x2, y2)
plt.show()
