import math
import cmath
from machine import ADC
potentiometer_value = ADC(26)





sr = 128
x = [0] * sr



# recursive implementation of Cooley-Tukey FFT algorithm
def FFT(x):
    N = len(x)
    if N is 1:
        return x
    else:
        X_even = FFT(x[::2])
        X_odd = FFT(x[1::2])

        factor = [complex(cmath.exp(-2j * 3.14 * k / N), 0) for k in range(N)]
        X = [0] * N
        for k in range(N//2):
            X[k] = X_even[k] + factor[k] * X_odd[k]
            X[k+N//2] = X_even[k] + factor[k+N//2] * X_odd[k]

        return X



def get_FFT():

    for n in range(sr):
        x[n] = potentiometer_value.read_u16()
    
    
    # sampling interval
    ts = 5/sr

    t = (i*ts for i in range(sr))
    
    N = sr//2

    X = FFT(x)
    
    # calculate the frequency
    
    
    freq = [i/(N*ts) for i in range(N)]

    n_oneside = N #// 2


    # get the one-side frequency
    #f_oneside = freq[:n_oneside]

    # normalize the amplitude
    X_oneside = [abs(X[i]) / n_oneside for i in range(n_oneside)]

    return X_oneside
    

if __name__=="__main__":
    import time
    t1 = time.ticks_ms()
    for n in range(4):
        print(len(get_FFT()))
    t2 = time.ticks_ms()
    print("Time=%s" % ( (t2 - t1)/n))


