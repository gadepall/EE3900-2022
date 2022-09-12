import time
import numpy as np
import matplotlib.pyplot as plt

def dft(x):
	n = len(x)
	F = np.zeros((n,n),dtype=np.complex128)
	for i in range(n):
		for j in range(n):
				F[i][j] = np.exp(-2j*np.pi*i*j/n)
	return F@x

def fft(x):	
	n = len(x)
	
	if(n == 1):
		return x
	
	elif(n == 2):
		return np.hstack((x[0]+x[1],x[0]-x[1]))
	
	X1 = fft(x[::2])
	X2 = fft(x[1::2])
	
	D = np.zeros((n//2,), dtype=np.complex128)
	for i in range(n//2):
		D[i] = np.exp(-2j*np.pi*i/n)
	
	X_u = X1 + D*X2
	X_l = X1 - D*X2
	
	return np.hstack((X_u,X_l))

dft_time = np.zeros(12)
fft_time = np.zeros(12)

for i in range(12):
	N = 2**i
	x = np.random.randint(1,5,size=N)
	t1 = time.time()
	X_d = dft(x)
	t2 = time.time()
	X = fft(x)
	t3 = time.time()
	#print("Time of execution of ", N ,"-point DFT = ", t2-t1)
	#print("Time of execution of ", N ,"-point FFT = ", t3-t2)
	#print("="*50)
	dft_time[i] = t2-t1
	fft_time[i] = t3-t2
	
axis = 2**np.arange(12)
plt.plot(axis, dft_time, label = 'DFT Computation Time')
plt.plot(axis, fft_time, label = 'FFT Computation Time')
plt.title('DFT vs FFT Computation Times')
plt.xlabel('N')
plt.ylabel('Time of execution (in s)')
plt.xscale('log', basex=2)
plt.grid()
plt.legend()
plt.savefig('../figs/EE18BTECH11021_3.eps')
plt.show()
