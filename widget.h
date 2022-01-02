#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <iostream>
#include <unistd.h>

class Widget : public QWidget
{
    Q_OBJECT

private:
    static Widget *widget;
    Widget(QWidget *parent = nullptr);

    const int ANIMATION_STEP = 4;
    const int ANIMATION_SPEED = 2500;
    const QSize SCREEN_SIZE = qApp->screens()[0]->size();

    int tileSize = 64;
    QPoint animationOffset = QPoint(0, 0);

    void drawScreen(QPainter *painter);
    void setPainterColor(QPainter *painter, QColor color);

    QSize getTileOffset();

public:
    ~Widget();
    static Widget *get();

    QList<int> screenTiles;

    QSize getScreenTileSize();
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    int getTileSize() const;
    void setTileSize(int value);

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void upPressed();
    void downPressed();
    void rightPressed();
    void leftPressed();
    void pPressed();
};
#endif // WIDGET_H
