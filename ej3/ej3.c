#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    float (*vertices)[2];
    size_t n;
} poligono_t;


void poligono_destruir(poligono_t *poligono);

poligono_t *poligono_crear(float vertices[][2], size_t n){
  //crear poligono y devolverlo
  if(n >= ~0UL) // chequear 0ul mayor valor posible
    return NULL;
  poligono_t *nuevo_poligono = malloc(sizeof(poligono_t));
  if(!nuevo_poligono)
    return NULL;

  nuevo_poligono->n = n;
  
  nuevo_poligono->vertices = malloc(n * sizeof(float *));
  if(!nuevo_poligono->vertices){
    free(nuevo_poligono);
    return NULL;
  }
  
  if(!memcpy(nuevo_poligono->vertices, vertices,sizeof(float *) *n)){
    poligono_destruir(nuevo_poligono);
    return NULL;
  }
  return nuevo_poligono;
}

void poligono_destruir(poligono_t *poligono){
  free(poligono->vertices);
  free(poligono);
}

size_t poligono_cantidad_vertices(const poligono_t *poligono){
  return poligono->n;
}

bool poligono_obtener_vertice(const poligono_t *poligono, size_t pos, float *x, float *y){
  if(pos >= poligono_cantidad_vertices(poligono))
    return false;
  *x = poligono->vertices[pos][0];
  *y = poligono->vertices[pos][1];
  return true;
}


poligono_t *poligono_clonar(const poligono_t *poligono){
  size_t cantidad = poligono_cantidad_vertices(poligono);
  poligono_t *clon = poligono_crear(poligono->vertices,cantidad); 
  if(!clon)
    return NULL;
  return clon;
}


bool poligono_agregar_vertice(poligono_t *poligono, float x, float y){
  size_t pos = poligono->n;
  float (*aux)[2] = realloc(poligono->vertices, sizeof(float *)*(pos +1));
  if(!aux)
    return false;
  poligono->vertices = aux;
  poligono->vertices[pos][0]=x;
  poligono->vertices[pos][1]=y;
  poligono->n +=1;
  return true;
}

int main(void) {
  float puntos[3][2] = {{0, 0}, {1, 0}, {0, 1}};

    poligono_t *p1 = poligono_crear(puntos, 3);
    if(p1 == NULL) {
        fprintf(stderr, "Error en creacion de poligono\n");
        return 1;
    }

    float x, y;

    assert(poligono_cantidad_vertices(p1) == 3);
    assert(! poligono_obtener_vertice(p1, 3, &x, &y));
    assert(poligono_obtener_vertice(p1, 1, &x, &y));
    assert(x == 1 && y == 0);

    poligono_t *p2 = poligono_clonar(p1);
    poligono_destruir(p1);
    if(p2 == NULL) {
        fprintf(stderr, "Error en creacion de poligono\n");
        return 1;
    }

    assert(poligono_cantidad_vertices(p2) == 3);
    assert(poligono_obtener_vertice(p2, 2, &x, &y));
    assert(x == 0 && y == 1);

    assert(poligono_agregar_vertice(p2, -1, 0.5));
    assert(poligono_cantidad_vertices(p2) == 4);
    assert(poligono_obtener_vertice(p2, 3, &x, &y));
    assert(x == -1 && y == 0.5);

    poligono_destruir(p2);

    //assert(poligono_crear(puntos, ~0UL) == NULL);

    printf("todo OK!\n");
    return 0;
}
