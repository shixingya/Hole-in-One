#ifndef LEVEL_4_H
#define LEVEL_4_H
#include"Box2D/Box2D.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "meinelement.h"
#include "triangle.h"
#include <QPushButton>
#include <QGraphicsSceneMouseEvent>
#include <QElapsedTimer>
#include <QTime>
#include "recyclebin.h"
#include "recyclebingraphics.h"
#include "circle.h"
#include "gui.h"
#include <QItemSelection>
#include <paperball.h>
#include "triangle.h"
#include "picbutton.h"
#include "block.h"




#define framerate 1.0/35.0  //2 framerates eines grafik eines physic nötig //TODO

class Level_4 : public QGraphicsView
{
    Q_OBJECT

public:
    Level_4();
    //void displayLevel();

    std::vector<Block*> vectb;
    std::vector<Triangle*> vectt;

public slots:
    void update();
    void startLevel();
    void pauseLevel();
    void resumeLevel();
    void addRectangle();
    void addCircle();
    void addTriangle();
    void reset();


    void rotateLeft();
    void rotateRight();
//    void enableRotation();
//    void disableRotation();


    void getTime();
    void highscoreCounter();



private:

    b2World* myWorld4;
    QGraphicsScene* level4;
    QGraphicsItem* backgnd;

    bool newhighscore=false;
    void saveLevel();
    QList <QString> levelenab;

    //Elements to add
    Block* addblock1;
    Block* addblock2;


    RecycleBin* recyclebin1;
    RecycleBin* recyclebin2;
    RecycleBinGraphics* recyclebin3;
    Triangle* addtriangle1;
    Triangle* addtriangle2;

    Circle* addcircle1;
    Circle* addcircle2;


    //fixed Elements

    Paperball* ball;
    Circle* obstaclescircle1;

    Block* obstaclesrec1;
    Block* obstaclesrec2;
    Block* obstaclesrec3;
    Block* obstaclesrec4;
    Block* obstaclesrec5;
    Block* obstaclesrec6;
    Block* obstaclesrec7;
    Block* obstaclesrec8;
    Block* obstaclesrec9;
    Block* obstaclesrec10;
    Block* obstaclesrec11;
    Block* obstaclesrec12;
    Block* obstaclesrec13;
    Block* obstaclesrec14;
    Block* obstaclesrec15;
    Block* obstaclesrec16;
    Block* obstaclesrec17;
    Block* obstaclesrec18;
    Block* obstaclesrec19;
    Block* obstaclesrec20;
    Block* obstaclesrec21;
    Block* obstaclesrec22;
    Block* obstaclesrec23;
    Block* obstaclesrec24;
    //Block* obstaclesrec25;


    Triangle* obstacletriangle1;
    Triangle* obstacletriangle2;


    MeinElement* bottom;
    MeinElement* umrandung1;
    MeinElement* umrandung2;
    MeinElement* msgbox;

    QTimer* timer;
    int anzahl;
    b2Vec2 positionElem;
    picButton* bt_start;
    picButton* bt_pause;
    picButton* bt__resume;
    QElapsedTimer leveltime_elapsed;
    QTime leveltime_normal;
    picButton* bt__rect;
    picButton* bt__circle;
    picButton* bt__triangle;

    picButton* bt__reset;
    picButton* bt__left;
    picButton* bt__right;

    int counterRec = 0;
    int counterCircle=0;
    int counterTriangle=0;
    int highscore = 0;
    int counterTogether = 0;
    int leveltime;
    bool win = false;
    int counterTriangleangle1=0;
    int counterTriangleangle2=0;

    void showLevel();


};

#endif // LEVEL_4_H
