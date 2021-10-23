#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QListWidgetItem>
#include<QScroller>
#include<QSinglePointEvent>
#include<QString>
#include<QFont>
#include<QFile>
#include<QFontDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_listWidget_3_itemClicked(QListWidgetItem *item);

    void on_listWidget_2_itemClicked(QListWidgetItem *item);


private:
    Ui::MainWindow *ui;
    QPoint last;
    QString nowPic;
    void mousePressEvent(QMouseEvent *e) override;//重写鼠标事件实现窗口移动

    void mouseMoveEvent(QMouseEvent *e) override;//override是C++11的新特性 在虚函数未覆盖已有类虚函数时会报错

    void mouseReleaseEvent(QMouseEvent *e) override;

    void resetListWidget(int arr[]);

    QString loadFontFamilyFromFiles(const QString &fontFileName);


};
#endif // MAINWINDOW_H
