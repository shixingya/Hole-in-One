#include "level_3.h"
#include <iostream>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>
#include <qdebug.h>
#include <QFile>
#include <QTextStream>
#include "string"


using namespace std;

/*!
 * \brief Level_3::Level_3
 * \param parent
 * Initialize Level1 - Screen/Scene SetuP...
 */
Level_3::Level_3()
{
    /*!Set Application-Name*/
    setWindowTitle(tr("Hole in One - Level 3"));

    //Screen setup. No scroll bar available
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    timer2=new QTimer(this);
    timer2->setInterval(1.0/120.0*1000.0);
    //timer2->connect(timer2, SIGNAL(timeout()),this, SLOT(position()));
    timer2->start();

    //Scene setup
    level = new QGraphicsScene();
    level->setSceneRect(0,0,1024,768);
    setScene(level);
    showLevel();
}


/*!
 * \brief Level_3::update
 * update function for moveable objects like our ball - sets the graphics of the ball to the position
 * of the box2D body.
 */
void Level_3::update(){
    myWorld->Step(framerate, 20, 20);
    win = ball->drawBall1(); //nur bewegende Elemente in Update
    qDebug()<<recyclebin1->body->GetPosition().x<<recyclebin1->body->GetPosition().y;

        if (win==true){
        Level_3::pauseLevel();

        msgbox = new MeinElement(level,QPointF(375,275),300,175);

        QGraphicsTextItem * winText = new QGraphicsTextItem;
        winText->setPos(400,300);
        winText->setPlainText("You have finished Level 3!");
        level->addItem(winText);
        QGraphicsTextItem * timeText = new QGraphicsTextItem;
        timeText->setPos(400,350);

        QString time = QString("Time: %1 s").arg(leveltime);
        qDebug()<<time;
        timeText->setPlainText( time);
        level->addItem(timeText);
        QPushButton* quitLevel = new QPushButton("Quit");
        quitLevel->move(400,400);
        level->addWidget(quitLevel);
        connect(quitLevel, SIGNAL(clicked()),this,SLOT(quitLevel()));
    }
}

/*!
 * \brief Level_3::startLevel
 * Set the flag of the QGraphicsItem, after start was clicked.
 * draw the graphics if the body was moved before start was clicked.
 */
void Level_3::startLevel(){

    //addtriangle1->drawGraphics();

    recyclebin1->drawGraphics();
    recyclebin1->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
    recyclebin2->drawGraphics();
    recyclebin2->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
    obstaclescircle1->drawGraphics();
    //obstaclescircle2->drawGraphics();

    ball->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
    obstaclescircle1->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
    obstaclescircle1->graphics->setFlag(QGraphicsItem::ItemIsSelectable,false);
    //obstaclescircle2->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
    //obstaclescircle2->graphics->setFlag(QGraphicsItem::ItemIsSelectable,false);


   // addtriangle1->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
    //addtriangle1->graphics->setFlag(QGraphicsItem::ItemIsSelectable,false);


    if(counterRec==1){
        addblock1->drawGraphics();
        addblock1->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
        addblock1->graphics->setFlag(QGraphicsItem::ItemIsSelectable,false);
    }

    if(counterRec==2){
        addblock1->drawGraphics();
        addblock1->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
        addblock1->graphics->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addblock2->drawGraphics();
        addblock2->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
        addblock2->graphics->setFlag(QGraphicsItem::ItemIsSelectable,false);
    }

    if(counterCircle==1){
        addcircle1->drawGraphics();
        addcircle1->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
    }

    if(counterCircle==2){
        addcircle1->drawGraphics();
        addcircle1->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
        addcircle2->drawGraphics();
        addcircle2->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);
    }


    timer=new QTimer(this);
    timer->setInterval(1.0/120.0*1000.0);
    timer->connect(timer, SIGNAL(timeout()),this, SLOT(update()));
    timer->start();
    bt_pause->setEnabled(true);
    bt__resume->setEnabled(false);
    bt_start->setEnabled(false);
    bt__rect->setEnabled(false);
    bt__circle->setEnabled(false);


    leveltime_elapsed.start();
}
/*!
 * \brief Level_3::pauseLevel
 * pauses game when button pause is clicked
 */
void Level_3::pauseLevel(){
    if(timer!=NULL){
        timer->stop();
    }
    Level_3::getTime();
    Level_3::highscoreCounter();
    bt_pause->setEnabled(false);
    bt__resume->setEnabled(true);
    bt_start->setEnabled(false);
    qDebug()<<"Level paused";
    qDebug()<<leveltime_elapsed.elapsed()<<"milliseconds";
}
/*!
 * \brief Level_3::resumeLevel
 * resumes game when button resume is clicked
 */
void Level_3::resumeLevel()
{
    timer->start();
    bt_pause->setEnabled(true);
    bt__resume->setEnabled(false);
    bt_start->setEnabled(false);
}

/*!
 * \brief Level_3::addRectangle
 * Create new rectangle and count the rectangle items. limited to number.
 */
void Level_3::addRectangle()
{
    counterRec++;


    if (counterRec==1){
        addblock1 = new Block(myWorld, level, b2Vec2 (50.0,20.0), 0, 100, 40, b2_staticBody,1.0,"tool");

        bt__rect->setText("Rectangle (2)");
        //bt__circle->setText("Circle (2)");

        addblock1->draw();
    }

    else if(counterRec==2){
        addblock2 = new Block(myWorld, level, b2Vec2 (50.0,20.0), 0, 100, 40, b2_staticBody,1.0,"tool");

        bt__rect->setText("Rectangle (1)");
        //bt__circle->setText("Circle (1)");

        addblock2->draw();
    }



}
/*!
 * \brief Level_3::addCircle
 * create new circle and count the circle items. limited to number.
 */
void Level_3::addCircle(){
    counterCircle++;

    b2CircleShape circle;

    qDebug()<<counterCircle;
    if(counterCircle==1){
        circle.m_radius = 21.0;
        addcircle1 = new Circle(myWorld, level, QPointF(0.0,0.0), 0*(3.14/180.0), b2_staticBody, circle,"tool");

        //bt__rect->setText("Rectangle (2)");
        bt__circle->setText("Circle (2)");

        addcircle1->draw();

    }

    if(counterCircle==2){
        circle.m_radius = 21.0;
        addcircle2 = new Circle(myWorld, level, QPointF(0.0,0.0), 0*(3.14/180.0), b2_staticBody, circle,"tool");

        //bt__rect->setText("Rectangle (1)");
        bt__circle->setText("Circle (1)");

        addcircle2->draw();

    }

    if(counterCircle==3){
        circle.m_radius = 21.0;
        addcircle3 = new Circle(myWorld, level, QPointF(0.0,0.0), 0*(3.14/180.0), b2_staticBody, circle,"tool");

        //bt__rect->setText("Rectangle (0)");
        bt__circle->setText("Circle (0)");

        addcircle3->draw();

        bt__rect->setEnabled(false);
        bt__circle->setEnabled(false);

    }

}
/*!
 * \brief Level_3::getTime
 * Stop time and convert it to ms.
 */
void Level_3::getTime(){
    leveltime = leveltime_elapsed.elapsed(); //leveltime in msec
    leveltime = leveltime/1000; //leveltime in sec
}
/*!
 * \brief Level_3::highscoreCounter
 * Calculate the highscore.
 */
void Level_3::highscoreCounter(){

    counterTogether = counterRec + counterCircle;

    if ( (counterTogether==6)||(counterTogether==5) ){
        highscore = 1;
    }

    else if( (counterTogether==4)||(counterTogether==3) ){
        highscore = 2;
    }

    else if( (counterTogether==1)||(counterTogether==2)||(counterTogether==0) ){
        highscore = 3;
    }

    if ( (leveltime>=30) ){
        highscore = highscore*1;
    }

    else if( (leveltime<30)&&(leveltime>=15) ){
        highscore = highscore*2;
    }

    else if( (leveltime<15)&&(leveltime>=0) ){
        highscore = highscore*3;
    }

    highscore=highscore*100;
}
/*!
 * \brief Level_3::reset
 * Clear scene and load Level again.
 */
void Level_3::reset(){
   pauseLevel();
   level->clear();
   counterRec = 0;
   counterCircle = 0;

   showLevel();
}
/*!
 * \brief Level_3::quitLevel
 * quits game and writes time/score into highscore table
 */
void Level_3::quitLevel()
{
    QList <QString> levelenab;
    QFile file("level.txt");
    file.open(QIODevice::ReadWrite |QIODevice::Text);
    if(file.exists("level.txt")){

        levelenab.clear();
        while(!file.atEnd()){
            levelenab.append(file.readLine());
        }
       file.resize(0);

    }

    if(levelenab.size()>11){
        if(levelenab.at(13).toInt()<highscore){

            levelenab.replace(11,QString::number(leveltime)+" s\n");
            levelenab.replace(12,QString::number(counterTogether)+"\n");
            levelenab.replace(13,QString::number(highscore)+"\n");
        }

    }
    else{

        levelenab.insert(11,QString::number(leveltime)+" s\n");
        levelenab.insert(12,QString::number(counterTogether)+"\n");
        levelenab.insert(13,QString::number(highscore)+"\n");
    }

    QTextStream out(&file);
    foreach (QString data, levelenab) {
        out<<data;
    }


    file.close();
    this->close();
}
/*!
 * \brief Level_3::showLevel
 * Create all Objects for Level 1.
 * Connect Buttons with SLOT.
 */
void Level_3::showLevel(){

     //set Background Image
     QPixmap background(":/pic/Game_background_spwn.png");
     background.scaled(QSize(1021,766));
     backgnd = level->addPixmap(background);
     backgnd->setPos(0,0); //Set Graphic to top left corner
     backgnd->setFlag(QGraphicsItem::ItemIsMovable, false);

     //Start Button
     bt_start=new QPushButton();
     bt_start->setText("Start");
     bt_start->move(900.0,620.0);
     connect(bt_start,SIGNAL(clicked()),this,SLOT(startLevel()));
     level->addWidget(bt_start);

     //Pause Button
     bt_pause=new QPushButton();
     bt_pause->setText("Pause");
     bt_pause->setEnabled(false);
     bt_pause->move(900.0,660.0);
     connect(bt_pause,SIGNAL(clicked()),this,SLOT(getTime()));
     connect(bt_pause,SIGNAL(clicked()),this,SLOT(highscoreCounter()));
     connect(bt_pause,SIGNAL(clicked()),this,SLOT(pauseLevel()));
     level->addWidget(bt_pause);

     //Resume Button
     bt__resume=new QPushButton();
     bt__resume->setText("Resume");
     bt__resume->setEnabled(false);
     bt__resume->move(900.0,700.0);
     connect(bt__resume,SIGNAL(clicked()),this,SLOT(resumeLevel()));
     level->addWidget(bt__resume);

     //Reset
     bt__reset=new QPushButton();
     bt__reset->setText("Reset");
     bt__reset->setEnabled(true);
     bt__reset->move(900.0, 740.0);
     connect(bt__reset, SIGNAL(clicked()), this, SLOT(reset()), Qt::QueuedConnection);
     level->addWidget(bt__reset);

     //Rect Button

//     picButton *rectButton = new picButton(QPixmap(":/images/block_tool.png"), QPixmap(":/images/block_toolhover.png"));
//     rectButton->move(200.0,650.0);
//     connect(rectButton, SIGNAL(clicked()), this, SLOT(addRectangle()));
//     level->addWidget(rectButton);
     bt__rect=new QPushButton();
     bt__rect->setText("Rectangle (3)");
     bt__rect->setEnabled(true);
     bt__rect->move(200.0,700.0);
     connect(bt__rect,SIGNAL(clicked()),this,SLOT(addRectangle()));
     level->addWidget(bt__rect);


     //Circle Button
//     picButton *circleButton = new picButton(QPixmap(":/images/circle_tool.png"), QPixmap(":/images/circle_toolhover.png"));
//     circleButton->move(400.0,650.0);
//     connect(circleButton, SIGNAL(clicked()), this, SLOT(addCircle()));
//     level->addWidget(circleButton);
     bt__circle=new QPushButton();
     bt__circle->setText("Circle  (3)");
     bt__circle->setEnabled(true);
     bt__circle->move(400.0,700.0);
     connect(bt__circle,SIGNAL(clicked()),this,SLOT(addCircle()));
     level->addWidget(bt__circle);

     //Rotate Left
     bt__left=new QPushButton();
     bt__left->setText("Rotate Left");
     bt__left->setEnabled(true);
     bt__left->move(5.0,650.0);
     connect(bt__left,SIGNAL(clicked()),this,SLOT(rotateLeft()));
     level->addWidget(bt__left);

     //Rotate Left
     bt__right=new QPushButton();
     bt__right->setText("Rotate Right");
     bt__right->setEnabled(true);
     bt__right->move(105.0,650.0);
     connect(bt__right,SIGNAL(clicked()),this,SLOT(rotateRight()));
     level->addWidget(bt__right);

     b2Vec2 gravity(0, 9.8); //normal earth gravity, 9.8 m/s/s straight down!

     myWorld = new b2World(gravity);

     float32 timeStep = 1.0/100.0;     //the length of time passed to simulate (seconds)
     int32 velocityIterations = 8.0;   //how strongly to correct velocity
     int32 positionIterations = 3.0;   //how strongly to correct position

     myWorld->Step(timeStep, velocityIterations, positionIterations);

     b2CircleShape circle;
     circle.m_radius = 21.0;

     //Outer borders
     umrandung1 = new MeinElement(myWorld,level, b2Vec2 (-30.0,0.0), 10, 1024, b2_staticBody, 1.0);
     umrandung2 = new MeinElement(myWorld,level, b2Vec2 (1002.0,0.0), 0, 1024, b2_staticBody, 1.0);
     bottom= new MeinElement(myWorld, level, b2Vec2(0.0,level->height()-200), level->width(), 22, b2_staticBody, 0.1);

     // game Objects
     ball  = new Paperball(myWorld, level, QPointF(520.0,40.0), 0*(3.14/180.0), b2_dynamicBody, circle);

     recyclebin1 = new RecycleBin(myWorld, level, QPointF(500,508),QPointF(510,508),QPointF(530,568),QPointF(520,568), 0.0, b2_staticBody, 0.5);
     recyclebin2 = new RecycleBin(myWorld, level, QPointF(550,568),QPointF(570,508),QPointF(580,508),QPointF(560,568), 0.0, b2_staticBody, 0.5);
     recyclebin3 = new RecycleBinGraphics(level);

     triangle1 = new Triangle(myWorld, level, QPointF(200.0,400.0), QPointF(300.0,400.0), QPointF(300.0,500.0), 1.57, b2_staticBody, 1.0,"obs");

     //so that ball is not moveable like the other objects
     ball->graphics->setFlag(QGraphicsItem::ItemIsMovable,false);

     ball->drawBall1();

     //obstaclescircle1->draw(); //static Elemente may be drawn here
     //obstaclescircle2->draw();
     bottom->drawBottom();
     umrandung1->graphics->hide();
     umrandung2->graphics->hide();
}
/*!
 * \brief Level_3::rotateLeft
 * possibility to rotate objects to the left
 */
void Level_3::rotateLeft(){

//    if(rechteck1->graphics->isSelected()){
//        qreal angle=rechteck1->angle-0.5235;
//        QPointF pos=rechteck1->graphics->pos();
//        qreal degreeangle=angle*180/3.1415;
//        level->removeItem(rechteck1->graphics);
//        rechteck1 =new Block(myWorld, level, b2Vec2(pos.x()+(rechteck1->length)/2.0,pos.y()+(rechteck1->width)/2.0),angle , 100, 40, b2_staticBody,1.0);
//        rechteck1->graphics->setRotation(degreeangle);

//    }

    if(counterRec==1){
        if(addblock1->graphics->isSelected()){
            qreal angle=addblock1->angle-0.5235;
            //QPointF pos=addblock1->graphics->pos();
            qreal degreeangle=angle*180/3.1415;
            level->removeItem(addblock1->graphics);
            addblock1 =new Block(myWorld, level, b2Vec2 (50,20),angle , 100, 40, b2_staticBody,1.0,"tool");
            addblock1->graphics->setRotation(degreeangle);
        }
    }
    if(counterRec==2){
        if(addblock1->graphics->isSelected()){
            qreal angle=addblock1->angle-0.5235;
           // QPointF pos=addblock1->graphics->pos();
            qreal degreeangle=angle*180/3.1415;
            level->removeItem(addblock1->graphics);
            addblock1 =new Block(myWorld, level, b2Vec2 (50,20),angle , 100, 40, b2_staticBody,1.0,"tool");
            addblock1->graphics->setRotation(degreeangle);
        }
       if(addblock2->graphics->isSelected()){
           qreal angle=addblock2->angle-0.5235;
          // QPointF pos=addblock2->graphics->pos();
           qreal degreeangle=angle*180/3.1415;
           level->removeItem(addblock2->graphics);
           addblock2 =new Block(myWorld, level, b2Vec2 (50,20),angle , 100, 40, b2_staticBody,1.0,"tool");
           addblock2->graphics->setRotation(degreeangle);
        }
    }

    if(counterRec==3){
        if(addblock1->graphics->isSelected()){
            qreal angle=addblock1->angle-0.5235;
           // QPointF pos=addblock1->graphics->pos();
            qreal degreeangle=angle*180/3.1415;
            level->removeItem(addblock1->graphics);
            addblock1 =new Block(myWorld, level, b2Vec2 (50,20),angle , 100, 40, b2_staticBody,1.0,"tool");
            addblock1->graphics->setRotation(degreeangle);
        }
        if(addblock2->graphics->isSelected()){
            qreal angle=addblock2->angle-0.5235;
           // QPointF pos=addblock2->graphics->pos();
            qreal degreeangle=angle*180/3.1415;
            level->removeItem(addblock2->graphics);
            addblock2 =new Block(myWorld, level, b2Vec2 (50,20),angle , 100, 40, b2_staticBody,1.0,"tool");
            addblock2->graphics->setRotation(degreeangle);
         }

    }

//    if(triangle1->graphics->isSelected()){
//        triangle1->rotateleft();

//    }
}
/*!
 * \brief Level_3::rotateRight
 * possibility to rotate right
 */
void Level_3::rotateRight(){

//    if(rechteck1->graphics->isSelected()){
//        qreal angle=rechteck1->angle+0.5235;
//        QPointF pos=rechteck1->graphics->pos();
//        qreal degreeangle=angle*180/3.1415;
//        level->removeItem(rechteck1->graphics);
//        rechteck1 =new Block(myWorld, level, b2Vec2(pos.x()+(rechteck1->length)/2.0,pos.y()+(rechteck1->width)/2.0),angle , 100, 40, b2_staticBody,1.0);
//        rechteck1->graphics->setRotation(degreeangle);

    //}

    if(counterRec==1){
        if(addblock1->graphics->isSelected()){
            qreal angle=addblock1->angle+0.5235;
          //  QPointF pos=addblock1->graphics->pos();
            qreal degreeangle=angle*180/3.1415;
            level->removeItem(addblock1->graphics);
            addblock1 =new Block(myWorld, level, b2Vec2 (50,20),angle , 100, 40, b2_staticBody,1.0,"tool");
            addblock1->graphics->setRotation(degreeangle);
        }
    }
    if(counterRec==2){
        if(addblock1->graphics->isSelected()){
            qreal angle=addblock1->angle+0.5235;
          //  QPointF pos=addblock1->graphics->pos();
            qreal degreeangle=angle*180/3.1415;
            level->removeItem(addblock1->graphics);
            addblock1 =new Block(myWorld, level, b2Vec2 (50,20),angle , 100, 40, b2_staticBody,1.0,"tool");
            addblock1->graphics->setRotation(degreeangle);
        }
        if(addblock2->graphics->isSelected()){
            qreal angle=addblock2->angle+0.5235;
          //  QPointF pos=addblock2->graphics->pos();
            qreal degreeangle=angle*180/3.1415;
            level->removeItem(addblock2->graphics);
            addblock2 =new Block(myWorld, level, b2Vec2 (50,20),angle , 100, 40, b2_staticBody,1.0,"tool");
            addblock2->graphics->setRotation(degreeangle);
        }
    }

    if(counterRec==3){
        if(addblock1->graphics->isSelected()){
            qreal angle=addblock1->angle+0.5235;
        //    QPointF pos=addblock1->graphics->pos();
            qreal degreeangle=angle*180/3.1415;
            level->removeItem(addblock1->graphics);
            addblock1 =new Block(myWorld, level, b2Vec2 (50,20),angle , 100, 40, b2_staticBody,1.0,"tool");
            addblock1->graphics->setRotation(degreeangle);
        }
        if(addblock2->graphics->isSelected()){
            qreal angle=addblock2->angle+0.5235;
           // QPointF pos=addblock2->graphics->pos();
            qreal degreeangle=angle*180/3.1415;
            level->removeItem(addblock2->graphics);
            addblock2 =new Block(myWorld, level, b2Vec2 (50,20),angle , 100, 40, b2_staticBody,1.0,"tool");
            addblock2->graphics->setRotation(degreeangle);
        }

    }


}







