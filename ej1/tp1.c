#include <stdio.h>
#include <math.h>

#define DT 0.001
#define G 9.81
#define VELOCIDAD_INICIAL 20
#define ANGULO_INICIAL 50
#define PI 3.14


double computar_velocidad(double vi, double a, double dt){
	return dt*a+vi; //devolver directamente, mas rapido, mas prolijo
}

double computar_posicion(double pi, double vi, double dt){
	return dt*vi+pi; //mismo de arriba, pi no es angulo es posicion inicial
}


//empezamos con el programa que calcula el tiro oblicuo;
//el programa debe imprimir en formato csv, ti, xi, vi;
int main(){
	double t=0,x=0,y=0; //consideramos el instante inicial t0=0[s];
	//la velocidad inicial se encuentra en funcion de un angulo por lo que hay que descomponerla
	double alpha = ANGULO_INICIAL*PI/180;//lo paso a radianes
	double vx_i=cos(alpha)*VELOCIDAD_INICIAL;
	double vy_i=sin(alpha)*VELOCIDAD_INICIAL;
	while(y>=0){
		printf("%f,%f,%f\n",t,x,y);
		//pasamos a incrementar los valores como corresponda
		t+=DT;
		vx_i=computar_velocidad(vx_i,0,DT);
		//tiro oblicuo la velocidad en x va a ser siempre la misma pero bueno la computo igual...
		vy_i=computar_velocidad(vy_i,-G,DT);
		x=computar_posicion(x,vx_i,DT);
		y=computar_posicion(y,vy_i,DT);
	}
	
}
