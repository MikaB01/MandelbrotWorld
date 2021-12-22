#include "widget.h"

Widget *Widget::widget = nullptr;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

void Widget::drawScreen(QPainter *painter)
{
    for(int y = 0; y < getScreenTileSize().height(); y++)
        for(int x = 0; x < getScreenTileSize().width(); x++) {
            if(screenTiles.at((y+1) * (x+1) + (x+1)) > 4) {
                setPainterColor(painter, QColor(Qt::red));
            } else {
                setPainterColor(painter, QColor(Qt::blue));
            }
            painter->drawRect(getTileOffset().width() + x * TILE_SIZE, getTileOffset().height() + y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }
}

void Widget::setPainterColor(QPainter *painter, QColor color)
{
    QBrush brush = QBrush(Qt::SolidPattern);
    brush.setColor(color);
    painter->setBrush(brush);
}

QSize Widget::getScreenTileSize()
{
    int tilesPerWidth = SCREEN_SIZE.width() / TILE_SIZE;
    int tilesPerHeigth = SCREEN_SIZE.height() / TILE_SIZE;
    if(SCREEN_SIZE.width() % TILE_SIZE || !(tilesPerWidth % 2)) tilesPerWidth++;
    if(SCREEN_SIZE.height() % TILE_SIZE || !(tilesPerHeigth % 2)) tilesPerHeigth++;
    return QSize(tilesPerWidth, tilesPerHeigth);
}

QSize Widget::getTileOffset()
{
    int offsetWidth = SCREEN_SIZE.width() - getScreenTileSize().width() * TILE_SIZE;
    int offsetHeigth = SCREEN_SIZE.height() - getScreenTileSize().height() * TILE_SIZE;
    return QSize(offsetWidth / 2, offsetHeigth / 2);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);
    drawScreen(painter);
    painter->end();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) this->close();
    else if(event->key() == Qt::Key_Up) emit upPressed();
    else if(event->key() == Qt::Key_Down) emit downPressed();
    else if(event->key() == Qt::Key_Right) emit rightPressed();
    else if(event->key() == Qt::Key_Left) emit leftPressed();
}

Widget::~Widget()
{
}

Widget *Widget::get()
{
    if( !widget )
        widget = new Widget();
    return widget;
}

