#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>

using namespace std;
void init2D(float r, float g, float b) {
	glClearColor(1.0, 1.0, 1.0, 1.0); // Arka plan rengi -- beyaz RGBA formatýnda 
	gluOrtho2D(-400.0, 400.0, -600.0, 600.0); //GLUT pencere çizim alaný büyüklüðü 
}
float xr = 0, yr = -380;
float y_position = 500;   // baþlangýc yukseklik pozisyonunu 500 verdik
float x_position;
float x2_position;
int i;
int t = 0;


void ucgen1(int i, int z) {
	float a = rand() & 2; 
	float b = rand() & 2;     // rekler icin randon deger atadýk
	float c = rand() & 2;



	glColor3f(a, b, c); // renkleri random degerlerini gonderdik
	glPointSize(5.0f);  
	glBegin(GL_POLYGON);    // bir ucgen tanýmladýk ve kose degerlerini girdik  ucgenin pozisyonu 
							// degistirmek icin extradan x_position ve y_position verdik 
							//bu pozisyonlarý timer adýndaki idle fonksiyonumuzda azaltýp arttrýk
							// z ile ucgenlerin baslangýz noktalarýný belirledik
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
}                              // score u ekrana yazdýrmak icin score u arttýran kodlarý yazdýk
void score() {
	glColor3f(1.0, 0.0, 0);
	char buf[100] = { 0 };
	sprintf_s(buf, "%d", t);


	renderbitmap(300, 550, GLUT_BITMAP_HELVETICA_12, buf);
}

void kare(void) {							// ucgenlerin carpmaya calýþtýðý kare methodu tanýmladýk 
											// bu methodun icine polygon ile kare cirdirdik
																						
	glColor3f(0, 0.60, 1); 
	glPointSize(5.0f); 
	glBegin(GL_POLYGON);
	glVertex2i(-25 + xr, -450);				// yon tuslarý ile hareket ettirebilek icin xr degerleri atadýk
	glVertex2i(-25 + xr, -400);
	glVertex2i(xr + 25, -400);
	glVertex2i(xr + 25, -450);
	glEnd();
}
void display() {								// nesneleri devamlý goruntületecegimiz fonksiyon 
	glClear(GL_COLOR_BUFFER_BIT);				//display tanýmladýk
	score();									// oyun icin puan ý tutan skor tanýmladýk

	for (i = 0; i <= 400; i += 113)			// for dongusu ile 4 tane ucgen cizdirdik 
	{											// cizdirdigimiz ucgenleri farklý noktalardan baslatmak icin z degeri tanýmladýk 
											//	ve bu z   dongu dondukce 50 birim farkla artmasýný sagladýk

		int z = (i / 2);

		ucgen1(i, z);						// bu z yi ucgenin yuksekligini belirleyen y_pozision ile topladýk ki hepsi farklý noktalardan baslamýsýný sagladýk
	}
	kare();

	glFlush();
}



void specialkey(int key, int x, int y) {
	switch (key) {									//olusturdugumuz kareyi yon tuslarý ile farklý yerlere hareket etmesini yon 
		                                         //tuþlarýna atadýðýmýz xr degerinin artýp azalma kontrolunu saglayarak sagladýk

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
{/*Bir þeyleri deðiþtirin*/
	if (y_position > -1000) {         // ekranda ilk cýkan ucgen -600 de cýkýyor ama ucgenlerin hepsi ayný anda hareket ettigi 
		y_position -= 0.12;			//icin en son cýkan ucgenle ilk cýkan ucgenin uzuklýgýný katarak 
	}								//y_position ile ucgenin goruntusunun ekranýn baslangýcýndan sonuna kadar ekranda kalmasýný sagladýk


	if (x_position > -400)				// ekranýn geliði soldan -400 birim olup 
	{									// pozisyonunu 0.10 ar birim azaltarak en sol noktaya varmasýný sagladýk					

		x_position -= 0.10;

	}
	if (x_position < -400 && x2_position >= 0)  //ucgen ekranýn en soluna geldigi zaman if kosulunun icindeki degerleri sagmasý halinde ekranýn sag tarafýna kaymasýný sagladýk 
	{
		x2_position += 0.10;
	}
	if (x2_position >= 400 && y_position < 120)  // en saga kayan ucgeninn tekrar en sola kaymasýný saglayan þartlarý yazdýk
	{
		x_position -= 0.20;

	}

	t++;// tum bu olaylar meydana gelirken skorunda artmasýný sagladýk
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