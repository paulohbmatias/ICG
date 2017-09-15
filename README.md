# Trabalho Individual 1

## PutPixel
A primeira função a ser implementada foi a PutPixel. A mesma foi baseada no código exemplo disponibilizado pelo professor. Ela recebe como parâmetro uma coordenada x, y e uma cor, então ela imprime a cor passada como parâmetro no pixel na coordenada indicada
``` c++
void PutPixel(int x, int y, cor c){ 
	FBptr[4*x + 4*y*IMAGE_WIDTH+0]=c.r; 
	FBptr[4*x + 4*y*IMAGE_WIDTH+1]=c.g;
	FBptr[4*x + 4*y*IMAGE_WIDTH+2]=c.b;
	FBptr[4*x + 4*y*IMAGE_WIDTH+3]=c.a;
}
```
## DrawLine
Essa função foi feita com base no código exemplo do professor, a mesma altera o algoritmo de bresenham no primeiro octante para que esse funcione em todos os octantes(vale ressaltar que o algoritmo de bresenham funciona em todos os octantes, porém foi alterado apenas a parte do primeiro octante), de acordo com as condições do delta x, delta y, y, x e x final.
Além disso, a mesma pega a variação de duas cores dividindo-as pelo delta x, e incrementa essa variação a cada componente da cor, de modo a interpolar duas cores ao longo da linha
```c++
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
```

![Triangulo](/Trabalho%20Individual/imagens/icg_linhas.png)

## DrawTriangle
Essa função foi relativamente simples de ser feita, pois bastava chamar a função DrawLine 3 vezes. Todavia ela foi feita com o triângulo preenchido, de modo que uma alternativa encontrada foi variar duas coordenadas em um laço de repetição, e a cada variação era chamado uma função DrawLine até um terceiro ponto.
Houve um problema ao fazer isso, pois estava ficando umas partes sem preencher, então a saída encontrada foi identificar qual o menor lado do triângulo, e variar esse lado até uma terceira coordenada, assim preenchendo melhor o triangulo.
![Triangulo](/Trabalho%20Individual/imagens/icg_triangulo.png)
```c++
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
```
