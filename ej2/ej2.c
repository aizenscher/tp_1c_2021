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

void transladar(float poligono[][2], size_t n, float dx, float dy){
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

  int signo=producto_vectorial(ax,ay,bx,by,cx,cy);
  if(!signo){
    perror("Las coordenadas no representan un triangulo");
    return false;
  }

  if(producto_vectorial(ax,ay,bx,by,px,py)*signo<0)
    return false;
  if(producto_vectorial(bx,by,cx,cy,px,py)*signo<0)
    return false;
  if(producto_vectorial(cx,cy,ax,ay,px,py)*signo<0)
    return false;
  return true;
}

bool punto_en_poligono(float poligono[][2], size_t n, float px, float py){
  for(size_t i=1; i<n ;i++){
      if(punto_en_triangulo(px,py,poligono[0][0],poligono[0][1],poligono[i][0],poligono[i][1],poligono[i+1][0],poligono[i+1][1]))
        return true;
  }
  return false;
}


int main(){
  //test transaldar y rotar poligono
  float poligono[][2]={{0,0},{0,1},{1,1},{1,0}};
  FILE *f=fopen("data_tras_rot.csv","wt");
  fprintf(f,"valor x, valor y\n");
  for(size_t i=0; i<4; i++)
    fprintf(f,"%f,%f\n",poligono[i][0],poligono[i][1]);
  transladar(poligono,4,1,1);
  for(size_t i=0; i<4; i++)
    fprintf(f,"%f,%f\n",poligono[i][0],poligono[i][1]);
  transladar(poligono,4,-1,-1);
  rotar(poligono,4,PI/2);
  for(size_t i=0; i<4; i++)
    fprintf(f,"%f,%f\n",poligono[i][0],poligono[i][1]);
  fclose(f);
  
  //test esta en triangulo
  FILE *f1= fopen("data_triangulo.csv","wt");
  FILE *ft=fopen("triangulo.csv","wt");
  float triangulo[][2]={{1,2},{3,1},{2,3}};
  fprintf(ft,"valor x, valor y\n");
  for(size_t i=0; i<3; i++)
    fprintf(ft,"%f,%f\n",triangulo[i][0],triangulo[i][1]);
  fclose(ft);
  float puntos[][2]={{1.5,1.5},{1.5,2.6},{2.5,2.5},{0.5,2},{0,0},{3.5,0.5},{1.1,2},{2,2.9},{2.9,1.1},{2,2},{2,1.5},{1.5,2.5},{2.5,2},{1,2},{3,1},{2,3}};
  fprintf(f1,"valor x, valor y, ok/x\n");
  for(size_t i=0;i<15;i++){
    fprintf(f1,"%f,%f,%s\n",puntos[i][0],puntos[i][1],punto_en_triangulo(puntos[i][0],puntos[i][1],triangulo[0][0],triangulo[0][1],triangulo[1][0],triangulo[1][1],triangulo[2][0],triangulo[2][1])?"ok":"x");
  }
  fclose(f1);
  return 0;
}
