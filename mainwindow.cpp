#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFont>
#include<QFile>
#include<QFontDatabase>
#include<QString>
QString loadFontFamilyFromFiles(const QString &fontFileName)
{

    static QHash<QString, QString> tmd;
    if (tmd.contains(fontFileName))
        return tmd.value(fontFileName);
    QString font = "";
    QFile fontFile(fontFileName);
    if(!fontFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Open font file error";
        return font;
    }

    int loadedFontID = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    if(!loadedFontFamilies.empty())
    {
        font = loadedFontFamilies.at(0);
    }
    fontFile.close();

    if (!(font.isEmpty()))
        tmd.insert(fontFileName, font);
    qDebug()<<QApplication::applicationDirPath() + "/font.otf";
    return font;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    QFont font = ui->label->font();//默认值
    QString family = loadFontFamilyFromFiles(QApplication::applicationDirPath() + "/font.otf");
    font.setFamily(family);

    ui->listWidget->setIconSize(QSize(30,30));
    ui->listWidget_2->setIconSize(QSize(30,30));
    ui->listWidget_3->setIconSize(QSize(30,30));
    ui->listWidget->setFont(font);
    ui->listWidget_2->setFont(font);
    ui->listWidget_3->setFont(font);
    ui->label->setFont(font);
    ui->label_2->setFont(font);//设置字体
    ui->label_2->setOpenExternalLinks( true );//开启超链接
    ui->label_2->setWordWrap(true);//开启自动换行
    //ui->listWidget_2->setIconSize(QSize(30,30));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetListWidget(int arr[],int len)
{
    //通过reset其他ListWidget使得其他ListWidget的样式回归未按下
    //在鼠标点击事件调用或者在itemClicked调用
    for(int i=0;i<len;i++)
    {
        if(arr[i]==1)ui->listWidget->reset();
        if(arr[i]==2)ui->listWidget_2->reset();
        if(arr[i]==3)ui->listWidget_3->reset();
    }

}

void MainWindow::mousePressEvent(QMouseEvent *e)//重写鼠标事件实现窗口移动
{
    last = e->globalPos();
    int waitlist[3]={1,2,3};
    resetListWidget(waitlist,3);
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();

    move(x()+dx, y()+dy);

}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
}

void MainWindow::on_pushButton_2_clicked()
{
    this->showMinimized();
}


void MainWindow::on_pushButton_3_clicked()
{
    this->close();
    qApp->quit();// 多此一举，但是适合学习多种方法
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int waitlist[2]={2,3};
    resetListWidget(waitlist,3);
    //ui->label_2->setContentsMargins(0,0,0,0);
    //qDebug()<<item;
    if(item->text()==" 学校官网")
        ui->label_2->setText(tr("<p>华南理工大学学校官网\n</p><a href = 'http://www.scut.edu.cn/new/'>www.scut.edu.cn/new/</a>"));
    if(item->text()==" 学生工作管理系统")
        ui->label_2->setText(tr("<p>华南理工大学学生工作管理系统\n</p><p>管理学生档案信息、成绩信息等\n</p><a href = 'http://sms.scut.edu.cn/'>sms.scut.edu.cn/</a>"));
    if(item->text()==" 统一门户")
        ui->label_2->setText(tr("<p>华南理工大学统一门户\n</p><p>信息中心，应用中心，消息提醒等\n</p><a href = 'http://my.scut.edu.cn/up/view?m=up#act=portal/viewhome'>my.scut.edu.cn/up/view?m=up#act=portal/viewhome</a>"));
    if(item->text()==" 办事大厅")
        ui->label_2->setText(tr("<p>华南理工大学办事大厅\n</p><p>教室借用申请、活动申请、换宿申请、缴费中心等\n</p><a href = 'http://ehall.scut.edu.cn/fp/view?m=fp#act=fp/formHome'>ehall.scut.edu.cn/fp/view?m=fp#act=fp/formHome</a>"));
    if(item->text()==" 线上图书馆")
        ui->label_2->setText(tr("<p>华南理工大学线上图书馆\n</p><p>借书还书，电子书，学术资源等。有些功能在校外访问时必须使用VPN。\n</p><a href = 'http://www.lib.scut.edu.cn/main.htm'>www.lib.scut.edu.cn/main.htm</a>"));
    if(item->text()==" 统一支付平台")
        ui->label_2->setText(tr("<p>华南理工大学统一支付平台\n</p><p>学费、宿舍费缴纳等\n</p><a href = 'http://pay.cw.scut.edu.cn/main.aspx'>pay.cw.scut.edu.cn/main.aspx</a>"));
    if(item->text()==" 教务系统")
        ui->label_2->setText(tr("<p>华南理工大学教务系统\n</p><p>选课，查看课表，报名，教学评价等\n</p><a href = 'http://xsjw2018.jw.scut.edu.cn/sso/driotlogin'>xsjw2018.jw.scut.edu.cn/sso/driotlogin</a>"));
    if(item->text()==" VPN")
        ui->label_2->setText(tr("<p>华南理工大学VPN\n</p><a href = 'http://www.scut.edu.cn/vpn'>www.scut.edu.cn/vpn</a>"));
}


void MainWindow::on_listWidget_3_itemClicked(QListWidgetItem *item)
{
    int waitlist[2]={1,2};
    resetListWidget(waitlist,3);
    if(item->text()==" 校园卡管理")
        ui->label_2->setText(tr("<p>校园卡管理\n</p><p>由于企业微信的神奇程序员直接通过网址中的加密JSON访问个人校园卡界面，还加了时间校验，还没留接口，所以本条目请通过教程自行访问（我要是能解析出来这个JSON我已经不在这里当学生了）\n</p>"
                                "<a href = 'http://www.scut.edu.cn/new/'>图片教程</a>"));
    if(item->text()==" 宿舍报修")
        ui->label_2->setText(tr("<p>宿舍报修\n</p><p>宿舍物品损坏后报修\n</p><a href = 'http://sms.scut.edu.cn/'>图片教程</a>"));
    if(item->text()==" 校园网管理")
        ui->label_2->setText(tr("<p>校园网管理\n</p><p>校园网缴费，查看IP，子网掩码，DNS。请确保按照教程进行以正确连接互联网。\n</p><a href = 'http://my.scut.edu.cn/up/view?m=up#act=portal/viewhome'>图片教程</a>"));
    if(item->text()==" 水电空调")
        ui->label_2->setText(tr("<p>水电空调\n</p><p>缴纳水费、电费和空调费，热水水控小程序\n</p><a href = 'http://ehall.scut.edu.cn/fp/view?m=fp#act=fp/formHome'>图片教程</a>"));

}


void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    int waitlist[2]={1,3};
    resetListWidget(waitlist,3);
    if(item->text()==" 关于程序")
    {
        ui->label_2->setText(tr("<p>Environment:</p>"
                                "<p>QT6.2.0 MinGW 64-bit</p>"
                                "<p>C++ MinGW 8.1.0 64-bit</p>"
                                "<p>Schedule：JSON reading</p>"
                                "<a href = 'http://github.com/EMILIIIIA/InformationSearchingHelper'>Join me on GitHub</a>"));
    }
    if(item->text()==" 关于作者")
    {
        ui->label_2->setText(tr("<p>作者是个摸鱼怪+躺平人，不保证更新速率。一般来说当季新番越拉作者更新越快（逃</p>"));
    }
}


