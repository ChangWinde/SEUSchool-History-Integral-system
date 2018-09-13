#include "console.h"
#include "ui_console.h"
#include <QFile>
#include <QMap>
#include <QHash>
#include <QList>
#include <QTextStream>
#include <QDebug>
#include <QtAlgorithms>
#include <QTextCodec>
Console::Console(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Console)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    ui->setupUi(this);
    //比赛环节数目
    _terms = 7;
    //数据初始化
    _line = new QString[7];
    _nameOfTeams = new QString[7];
    _scoreOfTeam = new QString[7];
    _labelOfTeam = new QString[7];
    setAny();
    //环节名字初始化
    _nameList = new QString[_terms + 1];
    _nameList[1] = "必答题";
    _nameList[2] = "抢答题";
    _nameList[3] = "蜂巢题";
    _nameList[4] = "车轮战";
    _nameList[5] = "视频改错题";
    _nameList[6] = "巅峰对决";
    _nameList[7] = "比赛结果";
    //环节分数初始化
    _goal = new int[_terms + 1];
    _goal[1] = 10;
    _goal[2] = 10;
    _goal[3] = 40;
    _goal[4] = 5;
    _goal[5] = 10;
    _goal[6] = 0;//这一环节人工调分数
    _goal[7] = 0;
    //环节
    _part = 1;
    //部件初始化
    ui->labelPart->setText(_nameList[_part]);
    ui->pb_Next->setEnabled(true);
    ui->pb_Last->setEnabled(false);
}

Console::~Console()
{
    delete ui;
}
//初始化信息
void Console::setAny()
{
    int key = 0;
    int i = 0;
    _log = new QFile("./Data.txt");
    QStringList dataList;
    if(!_log->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        key = 1;
        for(int j = 1;j<7;j++)
            _labelOfTeam[j] = j;
        _log->open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream temp(_log);
        for(int j = 1;j<7;j++)
            temp<<"0$"+QString::number(j)+"$"+"学院"<<endl;
        _log->close();
    }
    if(key == 1)
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
    ui->label_1->setText(_nameOfTeams[1]);
    ui->label_2->setText(_nameOfTeams[2]);
    ui->label_3->setText(_nameOfTeams[3]);
    ui->label_4->setText(_nameOfTeams[4]);
    ui->label_5->setText(_nameOfTeams[5]);
    ui->label_6->setText(_nameOfTeams[6]);
    ui->leGoal1_1->setText(_scoreOfTeam[1]);
    ui->leGoal1_2->setText(_scoreOfTeam[2]);
    ui->leGoal1_3->setText(_scoreOfTeam[3]);
    ui->leGoal1_4->setText(_scoreOfTeam[4]);
    ui->leGoal1_5->setText(_scoreOfTeam[5]);
    ui->leGoal1_6->setText(_scoreOfTeam[6]);
}
//修改信息
void Console::setScore(int id, int score)
{
    _scoreOfTeam[id] = QString::number(score);
    QStringList dataList = _line[id].split("$");
    dataList[0] = QString::number(score);
    _line[id] = dataList.join("$");
    //修改日志
    _log->open(QIODevice::WriteOnly| QIODevice::Truncate);
    QTextStream out(_log);
    for(int j = 1;j<7;j++)
        out<<_line[j]<<endl;
    _log->close();
    //改为排序后的界面
    //排序
    setSort();
    //发信号 界面修改
    emit StartSort();
}
//排序函数
void Console::setSort()
{
    QStringList forSplit;
    int score[6];
    for(int i = 0;i <6;i++)
        score[i] = _scoreOfTeam[i+1].toInt();
    int B[6] = {1,2,3,4,5,6};
    MergeSortIteration(score,6,B);
    for(int i=0;i < 6;i++)
        _labelOfTeam[B[i]] = QString::number(6-i);
    for(int i = 1;i<7;i++)
    {
        forSplit = _line[i].split("$");
        forSplit[1] = _labelOfTeam[i];
        _line[i] = forSplit.join("$");
    }
    //写入文件
    _log->open(QIODevice::WriteOnly| QIODevice::Truncate);
    QTextStream out(_log);
    for(int j = 1;j<7;j++)
        out<<_line[j]<<endl;
    _log->close();
}
void Console::Merge(int A[], int left, int mid, int right,int B[])
{
    int len = right - left + 1;
    int *temp = new int[len];
    int *temp2 = new int[len];
    int index = 0;
    int i = left;
    int j = mid + 1;
    while (i <= mid && j <= right)
    {
        if(A[i] <= A[j])
        {
            int a = i;
            int b = index;
            temp[index++] = A[i++];
            temp2[b] = B[a];
        }
        else
        {
            int a = j;
            int b = index;
            temp[index++] = A[j++];
            temp2[b] = B[a];
        }
    }
    while (i <= mid)
    {
        int a = i;
        int b = index;
        temp[index++] = A[i++];
        temp2[b] = B[a];
    }
    while (j <= right)
    {
        int a = j;
        int b = index;
        temp[index++] = A[j++];
        temp2[b] = B[a];
    }
    for (int k = 0; k < len; k++)
    {
        int l = left;
        A[left++] = temp[k];
        B[l] = temp2[k];
    }
}
void Console::MergeSortIteration(int A[], int len,int B[])
{
    int left, mid, right;
    for (int i = 1; i < len; i *= 2)
    {
        left = 0;
        while (left + i < len)
        {
            mid = left + i - 1;
            right = mid + i < len ? mid + i : len - 1;
            Merge(A, left, mid, right,B);
            left = right + 1;
        }
    }
}
//Next按钮
void Console::on_pb_Next_clicked()
{
    if(_part < _terms)
    {
        ++_part;
        ui->labelPart->setText(_nameList[_part]);
        if(_part == 2||_part == 5)
            ui->labelPart->setStyleSheet("color: rgb(255, 0, 0);");
        else
            ui->labelPart->setStyleSheet("color: rgb(0, 0, 0);");
        emit Nextpart(_part);
        if(_part == _terms)
            ui->pb_Next->setEnabled(false);
        if(_part == 2)
            ui->pb_Last->setEnabled(true);
    }
}
//Last按钮
void Console::on_pb_Last_clicked()
{
    if(_part > 1)
    {
        --_part;
        ui->labelPart->setText(_nameList[_part]);
        if(_part == 2||_part == 5)
            ui->labelPart->setStyleSheet("color: rgb(255, 0, 0);");
        else
            ui->labelPart->setStyleSheet("color: rgb(0, 0, 0);");
        emit Lastpart(_part);
        if(_part == 1)
            ui->pb_Last->setEnabled(false);
        if(_part == _terms - 1)
            ui->pb_Next->setEnabled(true);
    }
}
//Show按钮
void Console::on_pb_Show_clicked()
{
    _appearance = new Appearance;
    connect(this,&Console::ChangeGoal,
            _appearance,&Appearance::ChangScoreOnlyOne);
    connect(this,&Console::StartSort,
            _appearance,&Appearance::setSort);
    _appearance->show();
}
//Hide按钮
void Console::on_pb_Hide_clicked()
{
    _appearance->hide();
}
//Clear按钮
void Console::on_pb_Clear_clicked()
{
    //重置部件
    _part = 1;
    ui->labelPart->setText(_nameList[_part]);
    ui->pb_Next->setEnabled(true);
    ui->pb_Last->setEnabled(false);

    //重置日志
     QStringList temp;
    _log->open(QIODevice::WriteOnly| QIODevice::Truncate);
    QTextStream out(_log);
    for(int i = 1;i<7;i++)
    {
        temp = _line[i].split("$");
        temp[0] = "0";
        temp[1] = QString::number(i);
        _line[i] = temp.join("$");
        //重置数组
        _scoreOfTeam[i] = temp[0];
        _labelOfTeam[i] = temp[1];
        out<<_line[i]<<endl;
    }
    _log->close();

    //重写部件
    ui->label_1->setText(_nameOfTeams[1]);
    ui->label_2->setText(_nameOfTeams[2]);
    ui->label_3->setText(_nameOfTeams[3]);
    ui->label_4->setText(_nameOfTeams[4]);
    ui->label_5->setText(_nameOfTeams[5]);
    ui->label_6->setText(_nameOfTeams[6]);
    ui->leGoal1_1->setText(_scoreOfTeam[1]);
    ui->leGoal1_2->setText(_scoreOfTeam[2]);
    ui->leGoal1_3->setText(_scoreOfTeam[3]);
    ui->leGoal1_4->setText(_scoreOfTeam[4]);
    ui->leGoal1_5->setText(_scoreOfTeam[5]);
    ui->leGoal1_6->setText(_scoreOfTeam[6]);

    //修改界面
    emit StartSort();
}
//ShowAgain按钮
void Console::on_pb_Result_clicked()
{
   _appearance->show();
}
//SetAll按钮
void Console::on_pb_SetAll_clicked()
{
    on_pbReset1_1_clicked();
    on_pbReset1_2_clicked();
    on_pbReset1_3_clicked();
    on_pbReset1_4_clicked();
    on_pbReset1_5_clicked();
    on_pbReset1_6_clicked();
}
//以下是加分，减分，重置函数
void Console::on_pbAdd1_1_clicked()
{
    int goal = ui->leGoal1_1->text().toInt() + _goal[_part];
    ui->leGoal1_1->setText(QString::number(goal));
    emit ChangeGoal(1,goal);
    setScore(1,goal);
}

void Console::on_pbAdd1_2_clicked()
{
    int goal = ui->leGoal1_2->text().toInt() + _goal[_part];
    ui->leGoal1_2->setText(QString::number(goal));
    emit ChangeGoal(2,goal);
    setScore(2,goal);
}

void Console::on_pbAdd1_3_clicked()
{
    int goal = ui->leGoal1_3->text().toInt() + _goal[_part];
    ui->leGoal1_3->setText(QString::number(goal));
    emit ChangeGoal(3,goal);
    setScore(3,goal);
}

void Console::on_pbAdd1_4_clicked()
{
    int goal = ui->leGoal1_4->text().toInt() + _goal[_part];
    ui->leGoal1_4->setText(QString::number(goal));
    emit ChangeGoal(4,goal);
    setScore(4,goal);
}

void Console::on_pbAdd1_5_clicked()
{
    int goal = ui->leGoal1_5->text().toInt() + _goal[_part];
    ui->leGoal1_5->setText(QString::number(goal));
    emit ChangeGoal(5,goal);
    setScore(5,goal);
}

void Console::on_pbAdd1_6_clicked()
{
    int goal = ui->leGoal1_6->text().toInt() + _goal[_part];
    ui->leGoal1_6->setText(QString::number(goal));
    emit ChangeGoal(6,goal);
    setScore(6,goal);
}

void Console::on_pbSubtract1_1_clicked()
{
    int goal = ui->leGoal1_1->text().toInt() - _goal[_part];
    ui->leGoal1_1->setText(QString::number(goal));
    emit ChangeGoal(1,goal);
    setScore(1,goal);
}

void Console::on_pbSubtract1_2_clicked()
{
    int goal = ui->leGoal1_2->text().toInt() - _goal[_part];
    ui->leGoal1_2->setText(QString::number(goal));
    emit ChangeGoal(2,goal);
    setScore(2,goal);
}

void Console::on_pbSubtract1_3_clicked()
{
    int goal = ui->leGoal1_3->text().toInt() - _goal[_part];
    ui->leGoal1_3->setText(QString::number(goal));
    emit ChangeGoal(3,goal);
    setScore(3,goal);
}

void Console::on_pbSubtract1_4_clicked()
{
    int goal = ui->leGoal1_4->text().toInt() - _goal[_part];
    ui->leGoal1_4->setText(QString::number(goal));
    emit ChangeGoal(4,goal);
    setScore(4,goal);
}

void Console::on_pbSubtract1_5_clicked()
{
    int goal = ui->leGoal1_5->text().toInt() - _goal[_part];
    ui->leGoal1_5->setText(QString::number(goal));
    emit ChangeGoal(5,goal);
    setScore(5,goal);
}

void Console::on_pbSubtract1_6_clicked()
{
    int goal = ui->leGoal1_6->text().toInt() - _goal[_part];
    ui->leGoal1_6->setText(QString::number(goal));
    emit ChangeGoal(6,goal);
    setScore(6,goal);
}

void Console::on_pbReset1_1_clicked()
{
    int goal = ui->leGoal1_1->text().toInt();
    emit ChangeGoal(1,goal);
    setScore(1,goal);
}

void Console::on_pbReset1_2_clicked()
{
    int goal = ui->leGoal1_2->text().toInt();
    emit ChangeGoal(2,goal);
    setScore(2,goal);
}

void Console::on_pbReset1_3_clicked()
{
    int goal = ui->leGoal1_3->text().toInt();
    emit ChangeGoal(3,goal);
    setScore(3,goal);
}

void Console::on_pbReset1_4_clicked()
{
    int goal = ui->leGoal1_4->text().toInt();
    emit ChangeGoal(4,goal);
    setScore(4,goal);
}

void Console::on_pbReset1_5_clicked()
{
    int goal = ui->leGoal1_5->text().toInt();
    emit ChangeGoal(5,goal);
    setScore(5,goal);
}

void Console::on_pbReset1_6_clicked()
{
    int goal = ui->leGoal1_6->text().toInt();
    emit ChangeGoal(6,goal);
    setScore(6,goal);
}







