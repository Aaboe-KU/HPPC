import numpy as np
import matplotlib.pyplot as plt
t, S, I, R = np.loadtxt('sir_output.txt', skiprows=1, unpack=True)

plt.figure(figsize=(16,8))
plt.grid(linestyle=':')
plt.title("SIR model", fontsize=15)
plt.xlabel("Time [days]", fontsize=12)
plt.ylabel("Population", fontsize=12)
plt.plot(t,S,label='S')
plt.plot(t,I,label='I')
plt.plot(t,R,label='R')
plt.legend()
plt.savefig("plot.pdf")