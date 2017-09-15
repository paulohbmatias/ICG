#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h>
//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
class cor //Classe com as componentes RGBA da cor
{
public:
	double r, g, b, a;
	cor(double r, double g, double b, double a){
		this->r=r;
		this->g=g;
		this->b=b;
		this->a=a;
	}


	
};
class coordenada //Classe que contém as coordenadas X e Y de um ponto
{
public:
	double x, y;
	 coordenada(double x, double y){
	 	this->x = x;
	 	this->y = y;
	 }
	
	
};
//Imprimir um pixel na tela na posição x, y e em uma cor c
void PutPixel(int x, int y, cor c){ 
	FBptr[4*x + 4*y*IMAGE_WIDTH+0]=c.r; 
	FBptr[4*x + 4*y*IMAGE_WIDTH+1]=c.g;
	FBptr[4*x + 4*y*IMAGE_WIDTH+2]=c.b;
	FBptr[4*x + 4*y*IMAGE_WIDTH+3]=c.a;
}

double getX(int octante, double x, double y){ //Retorna o valor de x de acordo com o octante em que a linha se encontra

	if(octante == 2 || octante == 7){
		return y;
	}
	else if(octante == 3 || octante == 6){
		return -y;
	}
	else if(octante == 4 || octante == 5){
		return -x;
	}
	else{
		return x;
	}

}
double getY(int octante, double x, double y){ //Retorna o valor de y de acordo com o octante em que a linha se encontra
	
	if(octante == 2 || octante == 3){
		return x;
	}
	else if(octante == 5 || octante == 8){
		return -y;
	}
	else if(octante == 6 || octante == 7){
		return -x;
	}
	else{
		return y;
	}

}
void DrawLine(coordenada c1, coordenada c2, cor cor1, cor cor2){

	double dx = c2.x-c1.x; 	//delta x
	double dy = c2.y-c1.y;	//delta y
	double modulodx, modulody;	//modulo de delta x e delta y
	double aux; //variável auxiliar para trocar valores

	int octante;	//octante em que está a linha
	double x = c1.x; //coordenada x que varia para imprimir a linha na tela
	double y = c1.y; //coordenada y que varia para imprimir a linha na tela
	double x2 =  c2.x; //coordenada x final

	modulodx = abs(dx);
	modulody = abs(dy);
	//condição para saber se está no octante 1
	if(dx>=0 && dy>=0 && modulodx>=modulody){ 
		octante = 1;
	}
	/*
	condição para saber se está no octante 2, caso esteja, troca os valores de dx por dy, dy por dx,
	x por y, y por x e x2 por y final
	*/
	else if(dx>=0 && dy>=0 && modulody>=modulodx){ 
		octante = 2;
		aux = dx;
		dx = dy;
		dy = aux;
		aux = x;
		x = y;
		y = aux;
		x2 = c2.y;

	}
	/*
	condição para saber se está no octante 3, caso esteja, troca dy por -dx, dx por dy e x2 por y final
	*/
	else if(dx<0 && dy>=0 && modulody>=modulodx){ 
		octante = 3;
		aux = -dx;
		dx = dy;
		dy = aux;
		aux = -x;
		x = y;
		y = aux;
		x2 = c2.y;
	}
	/*
	condição para saber se está no octante 4, caso esteja, troca dx por -dx, x por -x, x2 por -x2
	*/
	else if(dx<0 && dy>=0 && modulodx>=modulody){
		octante = 4;
		dx = -dx;
		x = -x;
		x2 = -x2;
	}
	/*
	condição para saber se está no octante 5, caso esteja, troca dx por -dx, dy por -dy, x por -x, y por -y e x2 por -x2
	*/
	else if(dx<0 && dy<0 && modulodx>=modulody){
		octante = 5;
		dx = -dx;
		dy = -dy;
		x = -x;
		y = -y;
		x2 = -x2;
	}
	/*
	condição para saber se está no octante 6, caso esteja, troca dx por -dy, dy por -dx, x por -x, x2 por -x2
	*/
	else if(dx<0 && dy<0 && modulody>=modulodx){
		octante = 6;
		aux = -dx;
		dx = -dy;
		dy = aux;
		aux = -x;
		x = -y;
		y = aux;
		x2 = -c2.y;

	}
	/*
	condição para saber se está no octante 7, caso esteja, troca dx por -dy, dy por dx, x por -y, y por x e x2 por -y
	*/
	else if(dx>=0 && dy<0 && modulody>=modulodx){
		octante = 7;
		aux = dx;
		dx = -dy;
		dy = aux;
		aux = x;
		x = -y;
		y = aux;
		x2 = -c2.y;

	}
	/*
	condição para saber se está no octante 8, caso esteja, troca dy por -dy e y por -y
	*/
	else if(dx>=0 && dy<0 && modulodx>=modulody){
		octante = 8;
		dy = -dy;
		y = -y;
	}
	
	//variação das cores RGBA, quanto aumento cada vez que roda o while até chega ao x final
	double varR = (cor2.r - cor1.r) / dx;
	double varG = (cor2.g - cor1.g) / dx;
	double varB = (cor2.b - cor1.b) / dx; 
	double varA = (cor2.a - cor2.a) / dx;

	//Algoritmo de Bresenham
	double d = 2*dy-dx;
	double incr_e = 2*dy;
	double incr_ne = 2*(dy-dx);

	PutPixel(getX(octante, x, y), getY(octante, x, y), cor1);
	while(x<x2){
		
		if(d<=0){
			d += incr_e;
			x++;
		}else{
			d += incr_ne;
			x++;
			y++;
		}
		//incremento das cores de modo a interpolar do inicio ao fim da linha
		cor1.r += varR;
		cor1.g += varG;
		cor1.b += varB;
		cor1.a += varA;
		PutPixel(getX(octante, x, y), getY(octante, x, y), cor1);
			

	}
}

void DrawTrianglePreenchido(coordenada c1, coordenada c2, coordenada c3, cor cor1, cor cor2){
	double i=c1.x, j=c1.y, varX=1, varY=1; //i inicia no x inicial, j inicia no y inicial, variação de x e y começam com 1
	coordenada p(c2.x-c1.x, c2.y-c1.y); //ponto médio das coordenadas c1 e c2
	bool incrementaI = false; //variavel pra saber se o i vai ser incrementado ou decrementado
	bool incrementaJ = false; //variavel pra saber se o j vai ser incrementado ou decrementado

	if(c1.x<=c2.x){ // se o ponto x inicial for menor que o ponto x final, então i incrementa, se não, decrementa
		incrementaI = true;
	}
	if(c1.y<=c2.y){// se o ponto y inicial for menor que o ponto y final, então j incrementa, se não, decrementa
		incrementaJ = true;
	}

	double modulopx = abs(p.x); //modulo de x do ponto médio
	double modulopy = abs(p.y); //modulo de y do ponto médio

	/*
	se o modulo de x for maior que o modulo de y e modulo de y for diferente de 0, 
	então a variação de x vai ser modulo de x do ponto médio dividido pelo modulo de y
	do ponto médio
	*/

	if(modulopx>modulopy && modulopy!=0){ 
		varX = modulopx/modulopy;
	}
	/*
	se o modulo de y for maior que o modulo de x e modulo de x for diferente de 0, 
	então a variação de y vai ser modulo de y do ponto médio dividido pelo modulo de x
	do ponto médio
	*/
	if(modulopy>modulopx && modulopx!=0){
		varY = modulopy/modulopx;
	}
	
	double variacao = 0.1; //variação de incremento/decremento
	while(true){
		/*
		vai ser impresso linhas variando de c1 a c2 com a destino a c3, de modo a preencher o triangulo
		*/
		DrawLine(coordenada(i, j), c3, cor1, cor2); 

		if(incrementaI){
			if(i<c2.x){ //i incrementa até a coordenada x final
			i+= varX*variacao;	
			}
				
		}else{
			if(i>c2.x){ //i decrementa até a coordenada x inicial
			i-= varX*variacao;	
			}
		}
			
		if(incrementaJ){
			if(j<c2.y){//j incrementa até a coordenada y final
			j+= varY*variacao;	
			}
				
		}else{
			if(j>c2.y){//j decrementa até a coordenada y inicial
			j-= varY*variacao;	
			}
		}

		if(incrementaI && incrementaJ){
			/*
			Caso i incremente e J incremente, a condição de parada é quando i for menor ao x final
			e j for menor que o y final
			*/
			if(i>=c2.x && j>=c2.y){ 
			break;
			}
		}
		if(!incrementaI && incrementaJ){
			/*
			Caso i decremente e J incremente, a condição de parada é quando i for maior ao x final
			e j for menor que o y final
			*/
			if(i<=c2.x && j>=c2.y){
			break;
			}
		}
		if(incrementaI && !incrementaJ){
			/*
			Caso i incremente e J decremente, a condição de parada é quando i for menor ao x final
			e j for maior que o y final
			*/
			if(i>=c2.x && j<=c2.y){
			break;
			}
		}
		if(!incrementaI && !incrementaJ){
			/*
			Caso i decremente e J decremente, a condição de parada é quando i for maior ao x final
			e j for maior que y final
			*/
			if(i<=c2.x && j<=c2.y){
			break;
			}
		}
	}
}
double Distancia(coordenada c1,coordenada c2){ //retorna a distancia de dois pontos
	coordenada p(c2.x - c1.x, c2.y - c1.y);
	return sqrt(pow(p.x, 2)+pow(p.y, 2));
}
void DrawTriangle(coordenada c1, coordenada c2, coordenada c3, cor cor1, cor cor2){
	/*
	imprime o triangulo preenchido, partido da variação das coordenadas do menor lado e indo em direção
	ao terceiro ponto
	*/
	if(Distancia(c1, c2) <= Distancia(c1,c3) && Distancia(c1, c2)<=Distancia(c2, c3)){
		DrawTrianglePreenchido(c1, c2, c3, cor1, cor2);		
	}else if(Distancia(c1, c3)<=Distancia(c1, c2) && Distancia(c1, c3)<=Distancia(c2, c3)){
		DrawTrianglePreenchido(c1, c3, c2, cor1, cor2);
	}else{
		DrawTrianglePreenchido(c2, c3, c1, cor1, cor2);
	}

}









#endif // _MYGL_H_

