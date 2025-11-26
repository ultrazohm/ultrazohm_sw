import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.ticker as mtick

columns=['index','number']
xoshiro=pd.read_csv('uz_prng_xoshiro/uz_prng_xoshiro_uint32.csv', header=None, names=columns)
twister=pd.read_csv('uz_prng_mtwister/uz_prng_mtwister_uint32.csv', header=None, names=columns)
pcg=pd.read_csv('uz_prng_pcg/uz_prng_pcg_uint32.csv', header=None, names=columns)
squares=pd.read_csv('uz_prng_squares/uz_prng_squares_uint32.csv', header=None, names=columns)
halton=pd.read_csv('uz_prng_halton/uz_prng_halton_float.csv', header=None, names=columns)
halton_x=pd.read_csv('uz_prng_halton/uz_prng_halton_2d_float_x.csv', header=None, names=columns)
halton_y=pd.read_csv('uz_prng_halton/uz_prng_halton_2d_float_y.csv', header=None, names=columns)

start_x1=1
end_x1=50
start_x2=end_x1+1
end_x2=start_x2+end_x1-1

# %%
fig, axs = plt.subplots(2, 3,layout='constrained')
axs[0,0].plot(xoshiro.number[start_x1:end_x1],xoshiro.number[start_x2:end_x2],'o')
axs[0,0].set_title('Xoshiro128++')
axs[0,1].plot(twister.number[start_x1:end_x1],twister.number[start_x2:end_x2],'x')
axs[0,1].set_title('Mersenne Twister')
axs[1,0].plot(pcg.number[start_x1:end_x1],pcg.number[start_x2:end_x2],'+')
axs[1,0].set_title('PCG')
axs[1,1].plot(squares.number[start_x1:end_x1],squares.number[start_x2:end_x2],'*')
axs[0,2].plot(halton.number[start_x1:end_x1],halton.number[start_x2:end_x2],'x')
axs[0,2].set_title('Halton 1D')
axs[1,2].plot(halton_x.number[start_x1:end_x1],halton_y.number[start_x1:end_x1],'o')
axs[1,2].set_title('Halton 2D')
fig.suptitle('100 random values plotted as x=rnd(1:50) and y=rnd(2:100)')
plt.show()

plt.show()
