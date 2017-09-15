#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*******************************************************************
	coordenada c1(0, 0), c2(510, 510), c3(256, 0), c4(256, 510), c5(510, 0), c6(0, 510), c7(0, 256), c8(510, 256), c9(256,256);
	cor cor1(0, 166, 0, 1), cor2(0, 55, 255, 1), cor3(255, 0, 0, 0);
	//DrawTriangle(coordenada(256, 30), coordenada(), coordenada(490, 490))
	//DrawTriangle(c4, c8, c9, cor1, cor2);
	//DrawTriangle(c3, c6, c2, cor1, cor2);
	DrawTriangle(c6, c3, c2, cor1, cor2);
	//DrawTriangle(c7, c4, c6, cor1, cor2);
	//DrawLine(coordenada(226, 30), c9, cor1, cor2);
	/*
	DrawLine(c1, c9, cor1, cor2);
	DrawLine(c3, c9, cor1, cor2);
	DrawLine(c5, c9, cor1, cor2);
	DrawLine(c8, c9, cor1, cor2);
	DrawLine(c2, c9, cor1, cor2);
	DrawLine(c4, c9, cor1, cor2);
	DrawLine(c6, c9, cor1, cor2);
	DrawLine(c7, c9, cor1, cor2);
	*/

	


}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

