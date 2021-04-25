#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui -> start_button, &QPushButton::clicked, this, &MainWindow::on_start_button_clicked);
    connect(ui -> stop_button, &QPushButton::clicked, this, &MainWindow::on_stop_button_clicked);
    connect(ui -> reset_button, &QPushButton::clicked, this, &MainWindow::on_reset_button_clicked);
    connect(ui -> close_button, &QPushButton::clicked, this, &MainWindow::on_close_button_clicked);

    connect(timer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timer_timeout()
{
    int current_min = ui -> lcd_min -> intValue();
    int current_sec = ui -> lcd_sec -> intValue();

    if(current_sec == 59)
    {
        updatedisplay(current_min + 1, 0);
    }
    else
    {
        updatedisplay(current_min, current_sec + 1);
    }
}

void MainWindow::on_start_button_clicked()
{
    timer -> start(100);
}

void MainWindow::on_stop_button_clicked()
{
    timer -> stop();
}

void MainWindow::on_reset_button_clicked()
{
    updatedisplay(0, 0);
}

void MainWindow::on_close_button_clicked()
{
    MainWindow::close();
}

void MainWindow::updatedisplay(int min, int sec)
{
    ui -> lcd_min -> display(min);
    ui -> lcd_sec -> display(sec);
}
