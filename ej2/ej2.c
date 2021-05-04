#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.14159265359

//operaciones basicas:
float producto_vectorial(float ax, float ay, float bx, float by, float px, float py){
  float term_1[2]={bx-ax,by-ay};
  float term_2[2]={px-ax,py-ay};
  return term_1[0]*term_2[1]-term_1[1]*term_2[0];
}

void trasladar(float poligono[][2], size_t n, float dx, float dy){
	for(size_t i=0; i<n; i++){
    poligono[i][0]+=dx;
    poligono[i][1]+=dy;
	}
}


void rotar(float poligono[][2], size_t n, double rad){
  double angulo=180*PI*rad;
  for(size_t i=0; i<n; i++){
    float x=poligono[i][0];
    float y=poligono[i][1];
    poligono[i][0]=x*cos(angulo)-y*sin(angulo);
    poligono[i][1]=x*sin(angulo)+y*cos(angulo);
  }
}

bool punto_en_triangulo(float px, float py, float ax, float ay, float bx, float by, float cx, float cy){
  if(producto_vectorial(ax,ay,bx,by,px,py)>0)
    return false;
  if(producto_vectorial(bx,by,cx,cy,px,py)>0)
    return false;
  if(producto_vectorial(cx,cy,ax,ay,px,py)>0)
    return false;
  return true;
}

bool punto_en_poligono(float poligono[][2], size_t n, float px, float py){
  for(size_t i=0; i<n; i+=3){
    if(i!= n-2){
      if(!punto_en_triangulo(px,py,poligono[i][0],poligono[i][1],poligono[i+1][0],poligono[i+1][1],poligono[i+2][0],poligono[i+2][1]))
        return false;
    }
      if(!punto_en_triangulo(px,py,poligono[i][0],poligono[i][1],poligono[i+1][0],poligono[i+1][1],poligono[0][0],poligono[0][1]))
      return false;
  }
  return true;
}

int main(){

}
