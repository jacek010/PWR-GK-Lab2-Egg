/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacją osi 
//  układu współrzednych

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

const int N = 50;
typedef float point3[3]; //[0]-x / [1]-y / [2]-z
point3 colors[N][N];
point3 punkty[N][N];

#define PI 3.14159265358979323846

int model = 1;  // 1- punkty, 2- siatka, 3 - trójkąty, 4 - czajnik solid, 5 - czajnik siatka

static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy kąty obrotu

float rotateSpeed = 0.05;


//funkcja generuje losową wartość do użycia przy wyborze koloru
float kolor()
{
    return float(rand() % 101) / 100;
}

//funkcja wypełnia całą tabelę dwuwymiarową punktów losowymi kolorami
void randomColors()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            colors[i][j][0] = kolor();
            colors[i][j][1] = kolor();
            colors[i][j][2] = kolor();
        }
    }
}

//funkcja odpowiada za ustawienie jednolitego koloru
void oneColor(int color)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(color==1)
            { 
                colors[i][j][0] = 1.0;
                colors[i][j][1] = 0.0;
                colors[i][j][2] = 0.0;
            }
            else if (color == 2)
            {
                colors[i][j][0] = 0.0;
                colors[i][j][1] = 1.0;
                colors[i][j][2] = 0.0;
            }
            else if (color == 3)
            {
                colors[i][j][0] = 0.0;
                colors[i][j][1] = 0.0;
                colors[i][j][2] = 1.0;
            }
            else if (color == 4)
            {
                colors[i][j][0] = 1.0;
                colors[i][j][1] = 1.0;
                colors[i][j][2] = 1.0;
            }
        }
    }
}

//funkcja zmienia kąt położenia jajka
void spinEgg()
{

    theta[0] -= rotateSpeed;
    if (theta[0] > 360.0) theta[0] -= 360.0;

    theta[1] -= rotateSpeed;
    if (theta[1] > 360.0) theta[1] -= 360.0;

    theta[2] -= rotateSpeed;
    if (theta[2] > 360.0) theta[2] -= 360.0;

    glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
}

//funkcja zmienia prędkość rotacji jajka
void changeSpeed(float speed)
{
    rotateSpeed = speed;
}

/*************************************************************************************/

// Funkcja rysująca osie układu współrzędnych
void Axes(void)
{

    point3  x_min = { -5.0, 0.0, 0.0 };
    point3  x_max = { 5.0, 0.0, 0.0 };
    // początek i koniec obrazu osi x

    point3  y_min = { 0.0, -5.0, 0.0 };
    point3  y_max = { 0.0,  5.0, 0.0 };
    // początek i koniec obrazu osi y

    point3  z_min = { 0.0, 0.0, -5.0 };
    point3  z_max = { 0.0, 0.0,  5.0 };
    //  początek i koniec obrazu osi y
    glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
    glBegin(GL_LINES); // rysowanie osi x
    glVertex3fv(x_min);
    glVertex3fv(x_max);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
    glBegin(GL_LINES);  // rysowanie osi y

    glVertex3fv(y_min);
    glVertex3fv(y_max);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
    glBegin(GL_LINES); // rysowanie osi z

    glVertex3fv(z_min);
    glVertex3fv(z_max);
    glEnd();

}


//rysowanie jajka z punktów
void pointEgg()
{
    //narysowanie punktów
    glBegin(GL_POINTS);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            glVertex3fv(punkty[i][j]);
        }
    }
    glEnd();
}


//rysownaie jajka z siatki (linii)
void lineEgg()
{
    //narysowanie linii
    glBegin(GL_LINES);
    for (int i = 0; i < N-1; i++)
    {
        for (int j = 0; j < N-1; j++)
        {
            
            glBegin(GL_LINES);
            glVertex3fv(punkty[i][j]);//x y z 3 wierzcholki
            glVertex3fv(punkty[i][j + 1]);

            glVertex3fv(punkty[i][j]);
            glVertex3fv(punkty[i + 1][j]);

            glVertex3fv(punkty[i + 1][j]);
            glVertex3fv(punkty[i][j + 1]);

            glVertex3fv(punkty[i + 1][j]);
            glVertex3fv(punkty[i + 1][j + 1]);
        }
    }
    glEnd();
}


//rysowanie jajka z pełnym płaszczem
void triangleEgg()
{
    //narysowanie trójkątów
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {

            glBegin(GL_TRIANGLES);
            glColor3fv(colors[i][j + 1]);
            glVertex3fv(punkty[i][j + 1]);

            glColor3fv(colors[i + 1][j]);
            glVertex3fv(punkty[i + 1][j]);

            glColor3fv(colors[i + 1][j + 1]);
            glVertex3fv(punkty[i + 1][j + 1]);

            glColor3fv(colors[i + 1][j]);
            glVertex3fv(punkty[i + 1][j]);


            glColor3fv(colors[i][j + 1]);
            glVertex3fv(punkty[i][j + 1]);


            glColor3fv(colors[i][j]);
            glVertex3fv(punkty[i][j]);
            glEnd();
        }
    }
}


//Główna funkcja odpowiadająca za rysowanie jaja
void Egg()
{
    


    float u = 0.0;
    float v = 0.0;

    //wyznaczenie współrzędnych
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            //float u = (rand()%100)/100;
            u = (float)i / (N - 1);
            v = (float)j / (N - 1);

            punkty[i][j][0] = (float)(-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * cos(PI * v); // X(u,v)
            punkty[i][j][1] = (float)(160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2) - 5); //Y(u,v)
            punkty[i][j][2] = (float)(-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * sin(PI * v); //Z(u,v)
        }
    }

    switch (model)
    {
    case 1:
        pointEgg();
        break;
    case 2:
        lineEgg();
        break;
    case 3:
        triangleEgg();
        break;
    case 4:
        glutSolidTeapot(3.0);
        break;
    case 5:
        glutWireTeapot(3.0);
    }

}

//Funkcja przerysowuje scenę
void RenderScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszczącym

    glLoadIdentity();
    // Czyszczenie macierzy bieżącej
    Axes();
    // Narysowanie osi przy pomocy funkcji zdefiniowanej wyżej
    glColor3f(colors[1][1][0], colors[1][1][1], colors[1][1][2]); // Ustawienie koloru rysowania na biały


    //fragment odpowiadający za rotowanie obrazu
    glRotatef(theta[0], 1.0, 0.0, 0.0);

    glRotatef(theta[1], 0.0, 1.0, 0.0);

    glRotatef(theta[2], 0.0, 0.0, 1.0);
    Egg();//funkcja rysująca jajko

    glFlush();
    // Przekazanie poleceń rysujących do wykonania


    glutSwapBuffers();
    //
}

//funkcja wypisuje w konsoli menu aby użytkownik wiedział co robić
void printMenu()
{
    cout << "Niech moc jajeCZKA bedzie z Toba" << endl;
    cout << "Oto co mozesz uczynic z ta moca wciskajac odpowiednie klawisze:\n" << endl;
    cout << "Do woli zmieniaj strukture jajeCZKA:" << endl;
    cout << "\t 'p' - punkty" << endl;
    cout << "\t 's' - siatka" << endl;
    cout << "\t 't' - trojkaty" << endl;
    cout << "Wybieraj kolory:" << endl;
    cout << "\t 'c' - zawsze nowy kolor losowy" << endl;
    cout << "\t 'r' - red (taki troche komunistyczny)" << endl;
    cout << "\t 'g' - green (to jak chcesz byc eko frjendli)" << endl;
    cout << "\t 'b' - blue " << endl;
    cout << "\t 'w' - white " << endl;
    cout << "Zarzadzaj predkoscia rotacji:" << endl;
    cout << "\t '-' - zwolnij rotacje" << endl;
    cout << "\t '=' - przyspiesz rotacje" << endl;
    cout << "\t '0' - brak rotacji" << endl;
    cout << "\t '1' - wolno" << endl;
    cout << "\t '2' - szypko" << endl;
    cout << "\t '3' - szypko szybko " << endl;
    cout << "\t '4' - najszypciej (naprawde to jest bardzo szypko, do zestawu proponujemy trzymac potem wcisniety klawisz 'c') " << endl;

    cout << "\n\nFunkcje extra dodatkowe:" << endl;
    cout << "\t 'z' - czajnik pelny" << endl;
    cout << "\t 'x' - czajnik z siatki" << endl;
}

//funkcja wywołuje odpowiednie funkcje w zależnośći od naciśniętego klawisza
void keys(unsigned char key, int x, int y)
{
    if (key == 'p') model = 1;
    if (key == 's') model = 2;
    if (key == 't') model = 3;
    if (key == 'c') randomColors();
    if (key == 'r') oneColor(1);
    if (key == 'g') oneColor(2);
    if (key == 'b') oneColor(3);
    if (key == 'w') oneColor(4);
    if (key == '0') changeSpeed(0.00);
    if (key == '1') changeSpeed(0.01);
    if (key == '2') changeSpeed(0.2);
    if (key == '3') changeSpeed(2.0);
    if (key == '4') changeSpeed(5.0);
    if (key == '=') changeSpeed(rotateSpeed += 0.05);
    if (key == '-')
    {
        if (rotateSpeed<=0.1) changeSpeed(0.0);
        else changeSpeed(rotateSpeed -= 0.05);
    }
    if (key == 'z') model = 4;
    if (key == 'x') model = 5;

    RenderScene(); // przerysowanie obrazu sceny
}



void MyInit(void)
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Kolor czyszcący (wypełnienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

    GLfloat AspectRatio;
    // Deklaracja zmiennej AspectRatio  określającej proporcję
    // wymiarów okna 
    if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
        vertical = 1;
    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkościokna okna widoku (viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)  
    glMatrixMode(GL_PROJECTION);
    // Przełączenie macierzy bieżącej na macierz projekcji 
    glLoadIdentity();
    // Czyszcznie macierzy bieżącej            
    AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
    // Wyznaczenie współczynnika  proporcji okna
    // Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
    // przestrzeni ograniczającej pozwalającej zachować właściwe
    // proporcje rysowanego obiektu.
    // Do okreslenia przestrzeni ograniczjącej służy funkcja
    // glOrtho(...)            
    if (horizontal <= vertical)

        glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
    else

        glOrtho(-7.5 * AspectRatio, 7.5 * AspectRatio, -7.5, 7.5, 10.0, -10.0);
    glMatrixMode(GL_MODELVIEW);
    // Przełączenie macierzy bieżącej na macierz widoku modelu                                   

    glLoadIdentity();
    // Czyszcenie macierzy bieżącej
}

/*************************************************************************************/

// Główny punkt wejścia programu. Program działa w trybie konsoli



int main(int argc, char** argv)
{

    printMenu();
    randomColors();
    glutInit(&argc, argv);

    glutIdleFunc(spinEgg);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(300, 300);

    glutCreateWindow("JajeCZKO");

    glutDisplayFunc(RenderScene);
    // Określenie, że funkcja RenderScene będzie funkcją zwrotną
    // (callback function).  Bedzie ona wywoływana za każdym razem
    // gdy zajdzie potrzba przeryswania okna 

    glutKeyboardFunc(keys);

    glutReshapeFunc(ChangeSize);
    // Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
    // zazmiany rozmiaru okna      
    MyInit();
    // Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
    // inicjalizacje konieczne  przed przystąpieniem do renderowania
    glEnable(GL_DEPTH_TEST);
    // Włączenie mechanizmu usuwania powierzchni niewidocznych

    

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

    return 0;
}

/*************************************************************************************/