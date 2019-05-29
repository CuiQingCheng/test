#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 500);

    pix = QPixmap(600, 400);

    pix.fill(Qt::white);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if(isDrawLine)
    {

        QPainter pp(&pix);
        pp.drawLine(lastPoint, endPoint);
        painter.drawPixmap(0, 0, pix);
        lastPoint = endPoint;
    }
    else
    {
        int x, y, w, h;
        x = lastPoint.x();
        y = lastPoint.y();
        w = endPoint.x()- x;
        h = endPoint.y()- y;

        if(isDrawing)
        {
            tempPix = pix;
            QPainter tempPainter(&tempPix);
            tempPainter.drawRect(x, y, w, h);
            painter.drawPixmap(0, 0, tempPix);
        }
        else
        {
            QPainter tempPainter(&pix);
            tempPainter.drawRect(x, y, w, h);
            painter.drawPixmap(0, 0, pix);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();
        isDrawLine = true;
    }

    if(event->button() == Qt::RightButton)
    {
        lastPoint = event->pos();
        isDrawLine = false;
    }
    endPoint = lastPoint;
    isDrawing = true;

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
       endPoint = event->pos();
    }

    if(event->buttons() & Qt::RightButton)
    {
        endPoint = event->pos();
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        endPoint = event->pos();
        isDrawLine = true;
    }
    if(event->button() == Qt::RightButton)
    {
        endPoint = event->pos();
        isDrawLine = false;
    }
    isDrawing = false;
    update();

}

