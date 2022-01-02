 #include "widget.h"

Widget *Widget::widget = nullptr;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

int Widget::getTileSize() const
{
    return tileSize;
}

void Widget::setTileSize(int value)
{
    tileSize = value;
}

void Widget::drawScreen(QPainter *painter)
{
    for(int x = 0; x < getScreenTileSize().width(); x++)
        for(int y = 0; y < getScreenTileSize().height(); y ++) {
            if(screenTiles.at((x+1) * (getScreenTileSize().height()+1) + (y+1)) == 1) {
                setPainterColor(painter, QColor(Qt::white));
            } else {
                setPainterColor(painter, QColor(Qt::black));
            }
//            if(screenTiles.at((x+1) * (getScreenTileSize().height()+1) + (y+1)) > 0 && screenTiles.at((x+1) * (getScreenTileSize().height()+1) + (y+1)) < 12) {
//                setPainterColor(painter, QColor(Qt::white));
//            } else {
//                switch (screenTiles.at((x+1) * (getScreenTileSize().height()+1) + (y+1))) {
//                    case 0: setPainterColor(painter, QColor(Qt::black)); break;
//                    case 12: setPainterColor(painter, QColor(Qt::gray)); break;
//                    case 13: setPainterColor(painter, QColor(Qt::blue)); break;
//                    case 14: setPainterColor(painter, QColor(Qt::green)); break;
//                    case 15: setPainterColor(painter, QColor(Qt::red)); break;
//                    case 16: setPainterColor(painter, QColor(Qt::cyan)); break;
//                    case 17: setPainterColor(painter, QColor(Qt::darkYellow)); break;
//                    default: setPainterColor(painter, QColor(Qt::magenta)); break;
//                }
//            }
            painter->drawRect(getTileOffset().width() + x * tileSize + animationOffset.x(),
                              getTileOffset().height() + y * tileSize + animationOffset.y(),
                              tileSize, tileSize);
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
    int tilesPerWidth = SCREEN_SIZE.width() / tileSize;
    int tilesPerHeigth = SCREEN_SIZE.height() / tileSize;
    if(SCREEN_SIZE.width() % tileSize || !(tilesPerWidth % 2)) tilesPerWidth++;
    if(SCREEN_SIZE.height() % tileSize || !(tilesPerHeigth % 2)) tilesPerHeigth++;
    return QSize(tilesPerWidth + 2, tilesPerHeigth + 2);
}

void Widget::moveUp()
{
    for(int i = 0; i < tileSize / ANIMATION_STEP; i++) {
        animationOffset.setY( i * ANIMATION_STEP);
        this->repaint();
        usleep(ANIMATION_SPEED);
    }
}

void Widget::moveDown()
{
    for(int i = 0; i < tileSize / ANIMATION_STEP; i++) {
        animationOffset.setY( -i * ANIMATION_STEP);
        this->repaint();
        usleep(ANIMATION_SPEED);
    }
}

void Widget::moveRight()
{
    for(int i = 0; i < tileSize / ANIMATION_STEP; i++) {
        animationOffset.setX( -i * ANIMATION_STEP);
        this->repaint();
        usleep(ANIMATION_SPEED);
    }
}

void Widget::moveLeft()
{
    for(int i = 0; i < tileSize / ANIMATION_STEP; i++) {
        animationOffset.setX( i * ANIMATION_STEP);
        this->repaint();
        usleep(ANIMATION_SPEED);
    }
}

QSize Widget::getTileOffset()
{
    int offsetWidth = SCREEN_SIZE.width() - getScreenTileSize().width() * tileSize;
    int offsetHeigth = SCREEN_SIZE.height() - getScreenTileSize().height() * tileSize;
    return QSize(offsetWidth / 2, offsetHeigth / 2);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);
    painter->setPen(Qt::NoPen);
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
    else if(event->key() == Qt::Key_P) emit pPressed();
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

