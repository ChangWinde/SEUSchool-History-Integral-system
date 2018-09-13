#ifndef APPEARANCE_H
#define APPEARANCE_H

#include <QDialog>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPoint>
#include <QFile>
namespace Ui {
class Appearance;
}

class Appearance : public QDialog
{
    Q_OBJECT

public:
    explicit Appearance(QWidget *parent = 0);

    ~Appearance();

    //重载鼠标移动，窗体移动函数
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    //重载键盘事件，全屏/关闭
    void keyPressEvent(QKeyEvent *event);

    //自适应设置子部件大小
    void selfAdaption();
public slots:
    //排序
    void setSort();
    //改分函数
    void ChangScoreOnlyOne(int id, int goal);
private:
    Ui::Appearance *ui;
    //窗口位置，移动位置，鼠标位置
    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;
    //初始化信息
    void setAny();
    //设置排名信息
    void setRank();
    //系统信息（整体，行）
    QFile* _log;
    QString* _line;
    //队伍名
    QString* _nameOfTeams;
    //队伍分数
    QString* _scoreOfTeam;
    //队伍所对应的label
    QString* _labelOfTeam;
};

#endif // APPEARANCE_H
