# -*- coding: utf-8 -*-
"""
Created on Sat Feb 10 10:26:16 2018

@author: Bruno
"""

import numpy as np
import matplotlib.pyplot as plt

diameter = 0.04
volume = diameter**3 * np.pi / 6
rho = 1000
mass = rho * volume


#%% 500 particles 0.4m hole
t,particlesLeft=np.loadtxt("C:/Users/Ad/Desktop/particles/500p/particleCount.dat",skiprows=1, unpack=True)

i0=270 #start fit here
i1=350 #end fit here      

polynom1=np.polyfit(t[i0:i1],particlesLeft[i0:i1],1)
linearfit=polynom1[0]*t[i0:i1]+polynom1[1]

print("Mass flow for 500 particles : %3.3f (kg/s)"  %(-polynom1[0] * mass))
print("Total mass is : ", np.max(particlesLeft) * mass)

plt.plot(t,particlesLeft * mass, label='Experimental data') 
plt.plot(t[i0:i1],linearfit * mass, label='Linear Regression') 

#%% smol hole 0.2
t,particlesLeft=np.loadtxt("C:/Users/Ad/Desktop/particles/smallhole500/particleCount.dat",skiprows=1, unpack=True)
       
i0=250 #start fit here
i1=400 #end fit here
polynom1=np.polyfit(t[i0:i1],particlesLeft[i0:i1],1)
linearfit=polynom1[0]*t[i0:i1]+polynom1[1]

print("Mass flow for 500 particles : %3.3f (kg/s)" % (-polynom1[0] * mass))
print("Total mass is : ", np.max(particlesLeft) * mass)

plt.plot(t,particlesLeft * mass, label='Experimental data-s500') 
plt.plot(t[i0:i1],linearfit * mass, label='Linear Regression-s500')


plt.legend()
plt.show


#%% 100 particles 0.4m hole
t,particlesLeft=np.loadtxt("C:/Users/Ad/Desktop/particles/100p/particleCount.dat",skiprows=1, unpack=True)
       
i0=250 #start fit here
i1=400 #end fit here
polynom1=np.polyfit(t[i0:i1],particlesLeft[i0:i1],1)
linearfit=polynom1[0]*t[i0:i1]+polynom1[1]

print("Mass flow for 100 particles : %3.3f (kg/s)" % (-polynom1[0] * mass))
print("Total mass is : ", np.max(particlesLeft) * mass)

plt.plot(t,particlesLeft * mass, label='Experimental data-100') 
plt.plot(t[i0:i1],linearfit * mass, label='Linear Regression-100')


plt.legend()
plt.show

