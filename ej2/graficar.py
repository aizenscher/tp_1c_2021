import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


#main
#prueba rotacion y translacion
data = pd.read_csv('data_tras_rot.csv')
print("ejecutando prueba traslacion y rotacion");
n=int(input("ingrese la cantidad de elementos del poligono"))
print(n)
values_1=np.append(data[:n].values,data[:1].values,axis=0)
i=n*2
values_2=np.append(data[n:i].values,data[n:n+1].values,axis=0)
n=i
i=n*2
values_3=np.append(data[n:i].values,data[n:n+1].values,axis=0)

plt.figure()
plt.plot(values_1[:,0],values_1[:,1],'red')
plt.plot(values_2[:,0],values_2[:,1],'blue')
plt.plot(values_3[:,0],values_3[:,1],'green')
plt.show()

#prueba esta en triangulo

data1=pd.read_csv('data_triangulo.csv')
data_tri=pd.read_csv('triangulo.csv')

triangulo = np.append(data_tri[:3].values,data_tri[:1].values,axis=0)
puntos= data1[:].values

plt.figure()
plt.plot(triangulo[:,0],triangulo[:,1],'black')
for element in puntos:
    if(element[2]== 'ok'):
        aux_color = 'green'
    else:
        aux_color = 'red'
    plt.scatter(element[0],element[1],color=[aux_color])

plt.show()


#prueba poligono

data_pol=pd.read_csv('polygon');
data_p=pd.read_csv('puntos_pol.csv');
n=int(input("ingrese la cantidad de elementos del poligono"))
print(n)

polygon=np.append(datos[:].values,[datos[:0].values],axis=0)
puntos=data_p[:].values;
for element in polygon:
    plt.plot(polygon[i:i+2,0],polygon[i:i+2,1])

for element in puntos:
    if(element[2]== 'ok'):
        aux_color = 'green'
    else:
        aux_color = 'red'
    plt.scatter(element[0],element[1],color=[aux_color])









