#ifndef GUI_H
#define GUI_H


#include <QGraphicsScene>
#include <QGraphicsView>
#include <button.h>
#include <picbutton.h>

class Button;
class MainWindow;
class MeinElement;
class picButton;
class GUI : public QGraphicsView
{
    Q_OBJECT

public:
    GUI(QWidget* parent=NULL);  //constructor

    void displayGUI();

    QGraphicsScene* scene;  //attributes



public slots:
    void levelMenu();
    void highscore();
    void back();
    void showLevel1();

private:


};

#endif // GUI_H
