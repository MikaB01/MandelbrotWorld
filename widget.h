#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <iostream>

class Widget : public QWidget
{
    Q_OBJECT

private:
    static Widget *widget;
    Widget(QWidget *parent = nullptr);

    void drawScreen(QPainter *painter);
    void setPainterColor(QPainter *painter, QColor color);

    QSize getTileOffset();

    const int TILE_SIZE = 64;
    const QSize SCREEN_SIZE = qApp->screens()[0]->size();

public:
    ~Widget();
    static Widget *get();

    QList<int> screenTiles;

    QSize getScreenTileSize();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void upPressed();
    void downPressed();
    void rightPressed();
    void leftPressed();
};
#endif // WIDGET_H
