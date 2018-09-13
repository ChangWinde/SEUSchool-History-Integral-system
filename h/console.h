#ifndef CONSOLE_H
#define CONSOLE_H

#include <QDialog>
#include <QFile>
#include<QStringList>
#include"appearance.h"
namespace Ui {
class Console;
}

class Console : public QDialog
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    ~Console();
signals:
    void Nextpart(int part);
    void Lastpart(int part);
    void ChangeGoal(int name,int goal);
    void StartSort();
private slots:
    void on_pb_Next_clicked();

    void on_pb_Last_clicked();

    void on_pb_Show_clicked();

    void on_pb_Clear_clicked();

    void on_pbAdd1_1_clicked();

    void on_pbAdd1_2_clicked();

    void on_pbAdd1_3_clicked();

    void on_pbAdd1_4_clicked();

    void on_pbAdd1_5_clicked();

    void on_pbAdd1_6_clicked();

    void on_pbSubtract1_1_clicked();

    void on_pbSubtract1_2_clicked();

    void on_pbSubtract1_3_clicked();

    void on_pbSubtract1_4_clicked();

    void on_pbSubtract1_5_clicked();

    void on_pbSubtract1_6_clicked();

    void on_pbReset1_1_clicked();

    void on_pbReset1_2_clicked();

    void on_pbReset1_3_clicked();

    void on_pbReset1_4_clicked();

    void on_pbReset1_5_clicked();

    void on_pbReset1_6_clicked();

    void on_pb_Result_clicked();

    void on_pb_Hide_clicked();

    void on_pb_SetAll_clicked();

private:
    //初始化信息
    void setAny();
    //修改分数
    void setScore(int id, int score);
    //排序
    void setSort();
    void Merge(int A[], int left, int mid, int right,int B[]);
    void MergeSortIteration(int A[], int len,int B[]);
    Ui::Console *ui;
    //系统信息（整体，行）
    QFile* _log;
    QString* _line;
    //队伍名
    QString* _nameOfTeams;
    //队伍分数
    QString* _scoreOfTeam;
    //队伍所对应的label
    QString* _labelOfTeam;
    //环节名称
    QString* _nameList;
    //每环节分数
    int* _goal;
    //第几环节
    int _part;
    //环节数目
    int _terms;
    //展示窗口
    Appearance * _appearance;
};

#endif // CONSOLE_H
