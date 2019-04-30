#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>

using namespace std;
void init2D(float r, float g, float b) {
	glClearColor(1.0, 1.0, 1.0, 1.0); // Arka plan rengi -- beyaz RGBA format�nda 
	gluOrtho2D(-400.0, 400.0, -600.0, 600.0); //GLUT pencere �izim alan� b�y�kl��� 
}
float xr = 0, yr = -380;
float y_position = 500;   // ba�lang�c yukseklik pozisyonunu 500 verdik
float x_position;
float x2_position;
int i;
int t = 0;


void ucgen1(int i, int z) {
	float a = rand() & 2; 
	float b = rand() & 2;     // rekler icin randon deger atad�k
	float c = rand() & 2;



	glColor3f(a, b, c); // renkleri random degerlerini gonderdik
	glPointSize(5.0f);  
	glBegin(GL_POLYGON);    // bir ucgen tan�mlad�k ve kose degerlerini girdik  ucgenin pozisyonu 
							// degistirmek icin extradan x_position ve y_position verdik 
							//bu pozisyonlar� timer ad�ndaki idle fonksiyonumuzda azalt�p arttr�k
							// z ile ucgenlerin baslang�z noktalar�n� belirledik
	glVertex2i(+i + x_position + x2_position, y_position + z);
	glVertex2i(-25 + i + x_position + x2_position, y_position + 50 + z);
	glVertex2i(+25 + i + x_position + x2_position, y_position + 50 + z);
	glEnd();

}

void renderbitmap(int x, float y, void *font, char *string) {
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}                              // score u ekrana yazd�rmak icin score u artt�ran kodlar� yazd�k
void score() {
	glColor3f(1.0, 0.0, 0);
	char buf[100] = { 0 };
	sprintf_s(buf, "%d", t);


	renderbitmap(300, 550, GLUT_BITMAP_HELVETICA_12, buf);
}

void kare(void) {							// ucgenlerin carpmaya cal��t��� kare methodu tan�mlad�k 
											// bu methodun icine polygon ile kare cirdirdik
																						
	glColor3f(0, 0.60, 1); 
	glPointSize(5.0f); 
	glBegin(GL_POLYGON);
	glVertex2i(-25 + xr, -450);				// yon tuslar� ile hareket ettirebilek icin xr degerleri atad�k
	glVertex2i(-25 + xr, -400);
	glVertex2i(xr + 25, -400);
	glVertex2i(xr + 25, -450);
	glEnd();
}
void display() {								// nesneleri devaml� gorunt�letecegimiz fonksiyon 
	glClear(GL_COLOR_BUFFER_BIT);				//display tan�mlad�k
	score();									// oyun icin puan � tutan skor tan�mlad�k

	for (i = 0; i <= 400; i += 113)			// for dongusu ile 4 tane ucgen cizdirdik 
	{											// cizdirdigimiz ucgenleri farkl� noktalardan baslatmak icin z degeri tan�mlad�k 
											//	ve bu z   dongu dondukce 50 birim farkla artmas�n� saglad�k

		int z = (i / 2);

		ucgen1(i, z);						// bu z yi ucgenin yuksekligini belirleyen y_pozision ile toplad�k ki hepsi farkl� noktalardan baslam�s�n� saglad�k
	}
	kare();

	glFlush();
}



void specialkey(int key, int x, int y) {
	switch (key) {									//olusturdugumuz kareyi yon tuslar� ile farkl� yerlere hareket etmesini yon 
		                                         //tu�lar�na atad���m�z xr degerinin art�p azalma kontrolunu saglayarak saglad�k

	case GLUT_KEY_RIGHT:
		xr += 10;
		cout << x << endl;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		xr -= 10;
		cout << x << endl;
		glutPostRedisplay();
		break;
	}
}
void timer()		         
{/*Bir �eyleri de�i�tirin*/
	if (y_position > -1000) {         // ekranda ilk c�kan ucgen -600 de c�k�yor ama ucgenlerin hepsi ayn� anda hareket ettigi 
		y_position -= 0.12;			//icin en son c�kan ucgenle ilk c�kan ucgenin uzukl�g�n� katarak 
	}								//y_position ile ucgenin goruntusunun ekran�n baslang�c�ndan sonuna kadar ekranda kalmas�n� saglad�k


	if (x_position > -400)				// ekran�n geli�i soldan -400 birim olup 
	{									// pozisyonunu 0.10 ar birim azaltarak en sol noktaya varmas�n� saglad�k					

		x_position -= 0.10;

	}
	if (x_position < -400 && x2_position >= 0)  //ucgen ekran�n en soluna geldigi zaman if kosulunun icindeki degerleri sagmas� halinde ekran�n sag taraf�na kaymas�n� saglad�k 
	{
		x2_position += 0.10;
	}
	if (x2_position >= 400 && y_position < 120)  // en saga kayan ucgeninn tekrar en sola kaymas�n� saglayan �artlar� yazd�k
	{
		x_position -= 0.20;

	}

	t++;// tum bu olaylar meydana gelirken skorunda artmas�n� saglad�k
	glutPostRedisplay();

}



int main(int argc, char**argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(400, 600); 
	glutCreateWindow("OpenGL Proje1");
	init2D(0.0, 0.0, 0.0);
	glutDisplayFunc(display);
	glutIdleFunc(timer);
	glutSpecialFunc(specialkey);
	glutMainLoop();
	return 0;
}