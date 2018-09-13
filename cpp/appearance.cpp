#include "appearance.h"
#include "ui_appearance.h"
#include <QDebug>
#include <QMouseEvent>
#include<QKeyEvent>
#include<QDesktopWidget>
#include <QRect>

Appearance::Appearance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Appearance)
{
    ui->setupUi(this);
    //数据初始化
    _log = new QFile("./Data.txt");
    _line = new QString[7];
    _nameOfTeams = new QString[7];
    _scoreOfTeam = new QString[7];
    _labelOfTeam = new QString[7];
    setAny();
    //提升窗口等级
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
}

Appearance::~Appearance()
{
    delete ui;
}

//重载鼠标事件让窗口可以拖动
void Appearance::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;
}

void Appearance::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}

//设置全屏/关闭快捷键
void Appearance::keyPressEvent(QKeyEvent *event)
{
    //快捷键Ctrl+F全屏
    if(event->key() == Qt::Key_F && (event->modifiers()& Qt::ControlModifier)) {
        //提升等级，全屏显示
        this->setWindowFlags(Qt::Window);
        this->showFullScreen();
        //进行自适应
        selfAdaption();
    }
    //快捷键Ctrl+E关闭
    if(event->key() == Qt::Key_E && (event->modifiers()& Qt::ControlModifier)) {
        this->close();
    }
}
//自适应函数
void Appearance::selfAdaption()
{
    //获取窗口的当前大小
    double w = this->width();
    double h = this->height();

    //排名的宽高设置
    this->ui->leRank_1->setGeometry(100*w/922,50*h/677,71*w/922,71*h/677);
    this->ui->leRank_2->setGeometry(100*w/922,150*h/677,71*w/922,71*h/677);
    this->ui->leRank_3->setGeometry(100*w/922,250*h/677,71*w/922,71*h/677);
    this->ui->leRank_4->setGeometry(100*w/922,350*h/677,71*w/922,71*h/677);
    this->ui->leRank_5->setGeometry(100*w/922,450*h/677,71*w/922,71*h/677);
    this->ui->leRank_6->setGeometry(100*w/922,550*h/677,71*w/922,71*h/677);

    //院系名称的设置
    this->ui->label_1->setGeometry(200*w/922,50*h/677,521*w/922,71*h/677);
    this->ui->label_2->setGeometry(200*w/922,150*h/677,521*w/922,71*h/677);
    this->ui->label_3->setGeometry(200*w/922,250*h/677,521*w/922,71*h/677);
    this->ui->label_4->setGeometry(200*w/922,350*h/677,521*w/922,71*h/677);
    this->ui->label_5->setGeometry(200*w/922,450*h/677,521*w/922,71*h/677);
    this->ui->label_6->setGeometry(200*w/922,550*h/677,521*w/922,71*h/677);

    //分数的设置
    this->ui->leGoal1_1->setGeometry(660*w/922,67*h/677,221*w/922,40*h/677);
    this->ui->leGoal1_2->setGeometry(660*w/922,167*h/677,221*w/922,40*h/677);
    this->ui->leGoal1_3->setGeometry(660*w/922,267*h/677,221*w/922,40*h/677);
    this->ui->leGoal1_4->setGeometry(660*w/922,367*h/677,221*w/922,40*h/677);
    this->ui->leGoal1_5->setGeometry(660*w/922,467*h/677,221*w/922,40*h/677);
    this->ui->leGoal1_6->setGeometry(660*w/922,567*h/677,221*w/922,40*h/677);

    int fontSize = 53*h/677;

    //获取原来的样式表
    QString qss = this->ui->label_1->styleSheet();
    QString fontQss = qss + "font-size:"+ QString::number(fontSize,10) + "px";

    this->ui->label_1->setStyleSheet(fontQss);
    this->ui->label_2->setStyleSheet(fontQss);
    this->ui->label_3->setStyleSheet(fontQss);
    this->ui->label_4->setStyleSheet(fontQss);
    this->ui->label_5->setStyleSheet(fontQss);
    this->ui->label_6->setStyleSheet(fontQss);
    this->ui->leGoal1_1->setStyleSheet(fontQss);
    this->ui->leGoal1_2->setStyleSheet(fontQss);
    this->ui->leGoal1_3->setStyleSheet(fontQss);
    this->ui->leGoal1_4->setStyleSheet(fontQss);
    this->ui->leGoal1_5->setStyleSheet(fontQss);
    this->ui->leGoal1_6->setStyleSheet(fontQss);

}
//初始化信息
void Appearance::setAny()
{
    int i = 0;
    QStringList dataList;
    _log->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(_log);
    while (!in.atEnd()) {
        _line[++i] = in.readLine();
        dataList = _line[i].split("$");
        _scoreOfTeam[i] = dataList[0];
        _labelOfTeam[i] = dataList[1];
        _nameOfTeams[i] = dataList[2];
    }
    _log->close();
    for(int i = 1;i<7;i++)
    {
        int control = _labelOfTeam[i].toInt();
        switch (control) {
        case 1:
            ui->label_1->setText(_nameOfTeams[i]);
            ui->leGoal1_1->setText(_scoreOfTeam[i]);
            break;
        case 2:
            ui->label_2->setText(_nameOfTeams[i]);
            ui->leGoal1_2->setText(_scoreOfTeam[i]);
            break;
        case 3:
            ui->label_3->setText(_nameOfTeams[i]);
            ui->leGoal1_3->setText(_scoreOfTeam[i]);
            break;
        case 4:
            ui->label_4->setText(_nameOfTeams[i]);
            ui->leGoal1_4->setText(_scoreOfTeam[i]);
            break;
        case 5:
            ui->label_5->setText(_nameOfTeams[i]);
            ui->leGoal1_5->setText(_scoreOfTeam[i]);
            break;
        case 6:
            ui->label_6->setText(_nameOfTeams[i]);
            ui->leGoal1_6->setText(_scoreOfTeam[i]);
            break;
        default:
            break;
        }
    }
    //初始化排名信息
    setRank();
}
//设置排名
void Appearance::setRank()
{
    int rank[7];
    rank[1] = 1;
    int score[7];
    score[1] = ui->leGoal1_1->text().toInt();
    score[2] = ui->leGoal1_2->text().toInt();
    score[3] = ui->leGoal1_3->text().toInt();
    score[4] = ui->leGoal1_4->text().toInt();
    score[5] = ui->leGoal1_5->text().toInt();
    score[6] = ui->leGoal1_6->text().toInt();
    for(int i = 2;i<7;i++)
    {
        if(score[i] == score[i-1])
            rank[i] = rank[i-1];
        else
            rank[i] = i;
    }
    for(int i = 2;i<7;i++)
    {
        QString qss = "border-image: url(:/new/prefix"+QString::number(rank[i])+"/"+QString::number(rank[i])+".png);";

        switch (i) {
        case 2:
            ui->leRank_2->setStyleSheet(qss);
            break;
        case 3:
            ui->leRank_3->setStyleSheet(qss);
            break;
        case 4:
            ui->leRank_4->setStyleSheet(qss);
            break;
        case 5:
            ui->leRank_5->setStyleSheet(qss);
            break;
        case 6:
            ui->leRank_6->setStyleSheet(qss);
            break;
        }
    }
}

//更新排序信息
void Appearance::setSort()
{
    int i = 0;
    QStringList dataList;
    _log->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(_log);
    while (!in.atEnd()) {
        _line[++i] = in.readLine();
        dataList = _line[i].split("$");
        _scoreOfTeam[i] = dataList[0];
        _labelOfTeam[i] = dataList[1];
        _nameOfTeams[i] = dataList[2];
    }
    _log->close();
    for(int i = 1;i<7;i++)
    {
        int control = _labelOfTeam[i].toInt();
        switch (control) {
        case 1:
            ui->label_1->setText(_nameOfTeams[i]);
            ui->leGoal1_1->setText(_scoreOfTeam[i]);
            break;
        case 2:
            ui->label_2->setText(_nameOfTeams[i]);
            ui->leGoal1_2->setText(_scoreOfTeam[i]);
            break;
        case 3:
            ui->label_3->setText(_nameOfTeams[i]);
            ui->leGoal1_3->setText(_scoreOfTeam[i]);
            break;
        case 4:
            ui->label_4->setText(_nameOfTeams[i]);
            ui->leGoal1_4->setText(_scoreOfTeam[i]);
            break;
        case 5:
            ui->label_5->setText(_nameOfTeams[i]);
            ui->leGoal1_5->setText(_scoreOfTeam[i]);
            break;
        case 6:
            ui->label_6->setText(_nameOfTeams[i]);
            ui->leGoal1_6->setText(_scoreOfTeam[i]);
            break;
        default:
            break;
        }
    }
    setRank();
}
//单次修改分数
void Appearance::ChangScoreOnlyOne(int id,int goal)
{
    _scoreOfTeam[id] = QString::number(goal);
    switch (_labelOfTeam[id].toInt()) {
    case 1:
        ui->leGoal1_1->setText(_scoreOfTeam[id]);
        break;
    case 2:
        ui->leGoal1_2->setText(_scoreOfTeam[id]);
        break;
    case 3:
        ui->leGoal1_3->setText(_scoreOfTeam[id]);
        break;
    case 4:
        ui->leGoal1_4->setText(_scoreOfTeam[id]);
        break;
    case 5:
        ui->leGoal1_5->setText(_scoreOfTeam[id]);
        break;
    case 6:
        ui->leGoal1_6->setText(_scoreOfTeam[id]);
        break;
    default:
        break;
    }
}

