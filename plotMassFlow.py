# -*- coding: utf-8 -*-
"""
Created on Sat Feb 10 10:26:16 2018

@author: Bruno
"""

import numpy as np
import matplotlib.pyplot as plt


t,N=np.loadtxt("output/particleCount.dat",skiprows=1, unpack=True)
plt.plot(t,N* mass)
 
i0=270
i1=490
a=np.polyfit(t[270:490],N[270:490],1)
mass=0.04**3. *1000 *np.pi / 8
print("Number flow is : ", a[0]*mass)
print("Total mass is : ", np.max(N)*mass)

plt.legend()
plt.show()


plt.legend()
plt.show()