#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>
#include "t3dimlib.h"
#include "littlethings.h"
#include <iostream>

#define cout std::cout
#define endl std::endl
static double mouseposition_x{0};
static double mouseposition_y{0};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //resize(this->x(),this->y());
    clientwindow.x=0;
    clientwindow.y=this->menuBar()->height()
            +18;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    double x;
    class{
    public:
        void generaltest(MainWindow *m){
            D3Point s={1,1,1};
            D3Point end={2,3,4};

            double mathz=exp2(2);
            mathz=exp2(4);
            mathz=exp2(3);

            double r = T3Lib::D3::getLofAB(s,end);
            double r1=T3Lib::D3::SIN(toPai(30.0));
            double ang1=toDegree(T3Lib::D3::ASIN(0.5));
            //double r2r=T3Lib::D3::SIN(3.1415926/6.0);
            double r3 = T3Lib::D3::COS(toPai(60));
            double ang2 = toDegree(T3Lib::D3::ACOS(0.5));
            double ang3 = toDegree(T3Lib::D3::ACOS((-0.5)));
            double ang4 = toDegree((T3Lib::D3::ASIN((-0.5))));

            D3Line line1({1,1,1},{2,3,4});
            line1.refresh();
            D3Point dp = line1.antCrawl(10.0);

            D3Line line2({1,1,1},{3.67,6.35,9.02});
            line2.refresh();

            Point p1 = T3Lib::D3Map::Zsmap(0);
            Point p2 = T3Lib::D3Map::Zsmap(300);
            Point p3 = T3Lib::D3Map::Zsmap(300*10);
            Point p4 = T3Lib::D3Map::Zsmap(300 * 100);
            Point p5 = T3Lib::D3Map::Zsmap(300 * 1000);
            Point p6 = T3Lib::D3Map::Zsmap(100); double delx6 = 300 - p6.x;
            Point p7 = T3Lib::D3Map::Zsmap(200); double delx7 = p6.x - p7.x;
            Point p8 = T3Lib::D3Map::Zsmap(300); double delx8 = p7.x - p8.x;
            Point p9 = T3Lib::D3Map::Zsmap(400); double delx9 = p8.x - p9.x;
            Point p10 = T3Lib::D3Map::Zsmap(500); double delx10 = p9.x - p10.x;
            Point p11 = T3Lib::D3Map::Zsmap(600); double delx11 = p10.x - p11.x;
            Point p12 = T3Lib::D3Map::Zsmap(700); double delx12 = p11.x - p12.x;

            QPen pen(Qt::black,1);
            QPen redpen(Qt::red,3);
            QPen dotPen(Qt::black,6);

            m->drawdot(ViewWindow.getX(100),ViewWindow.getY(-100),dotPen);
            m->drawdot(ViewWindow.getX(100),ViewWindow.getY(100),dotPen);
            m->drawdot(ViewWindow.getX(-100),ViewWindow.getY(100),dotPen);
            m->drawdot(ViewWindow.getX(-100),ViewWindow.getY(-100),dotPen);


            //z集合映射测试
            Point xy;
            QPen bluepen(Qt::blue,6);
            double zx=0;
            for(int i=0;i<120;i++){
                xy=T3Lib::D3Map::pmap({100,300,zx});
                m->drawdot(ViewWindow.getX(xy.x),ViewWindow.getY(xy.y),bluepen);
                zx+=100;
            }
            zx=0;
            for(int i=0;i<120;i++){
                xy=T3Lib::D3Map::pmap({-100,300,zx});
                m->drawdot(ViewWindow.getX(xy.x),ViewWindow.getY(xy.y),bluepen);
                zx+=100;
            }
            zx=0;
            for(int i=0;i<120;i++){
                xy=T3Lib::D3Map::pmap({-100,-300,zx});
                m->drawdot(ViewWindow.getX(xy.x),ViewWindow.getY(xy.y),bluepen);
                zx+=100;
            }
            zx=0;
            for(int i=0;i<120;i++){
                xy=T3Lib::D3Map::pmap({100,-300,zx});
                m->drawdot(ViewWindow.getX(xy.x),ViewWindow.getY(xy.y),bluepen);
                zx+=100;
            }
            //标准z集映射测试
            double distance=0;
            for(int i=0;i<100;i++)
            {
                xy=T3Lib::D3Map::Zsmap(distance);
                m->drawdot(ViewWindow.getX(xy.x),ViewWindow.getY(xy.y),redpen);
                distance+=100;
            }
        }
        
        void computedisappertest(MainWindow *m){
            //标准z集映射测试
            double distance=0;
            QPen redpen(Qt::red,3);
            Point xy;
            for(int i=0;i<100;i++)
            {
                xy=T3Lib::D3Map::Zsmap(distance);
                m->drawdot(ViewWindow.getX(xy.x),ViewWindow.getY(xy.y),redpen);
                distance+=100;
            }
            double x1=m->ui->dis_x1_tx->toPlainText().toDouble();
            double y1=m->ui->dis_y1_tx->toPlainText().toDouble();
            double z1=m->ui->dis_z1_tx->toPlainText().toDouble();

            double x2=m->ui->dis_x2_tx->toPlainText().toDouble();
            double y2=m->ui->dis_y2_tx->toPlainText().toDouble();
            double z2=m->ui->dis_z2_tx->toPlainText().toDouble();


            //get data from UI element
            int step = m->ui->dis_step_tx->toPlainText().toInt();
            int dotcounts = m->ui->dis_dotcount_tx->toPlainText().toInt();
            cout<<"disappear:step="<<step<<endl;
            cout<<"disappear:dotcounts="<<dotcounts<<endl;
            QPen bluepen(Qt::blue,5);
            D3Line OA({x1,y1,z1},{x2,y2,z2});
            OA.refresh();
            D3Point C;
            distance = 0;
            Point mapped;
            for(int i=0;i<dotcounts;i++){
                C=OA.antCrawl(distance);
                mapped=T3Lib::D3Map::pmap(C);
                m->drawdot(ViewWindow.getX(mapped.x),ViewWindow.getY(mapped.y),bluepen);
                //distance+=T3Lib::D3Map::Zs;
                //distance+=T3Lib::D3Map::Zs;
                distance+=step;
            }

        }
        void cubetest(MainWindow *m){
            D3Point p3;
            //定位，将盒子放入窗后，因盒子坐标与映射坐标重合，故不需变化。
            //绘制盒子
            int x = m->ui->place_x_tx->toPlainText().toInt();
            int y = m->ui->place_y_tx->toPlainText().toInt();
            int z = m->ui->place_z_tx->toPlainText().toInt();
            int a = m->ui->init_change_a_tx->toPlainText().toInt();
            int b = m->ui->init_change_b_tx->toPlainText().toInt();
            int r = m->ui->init_change_r_tx->toPlainText().toInt();
            cube.box.location.position.x = x;
            cube.box.location.position.y = y;
            cube.box.location.position.z = z;
            cube.box.location.axis_change_a = a;
            cube.box.location.axis_change_b = b;
            cube.box.location.axis_change_r = r;
            m->drawThingwareinWindow(&cube);
            
        }
        void move_x_add(MainWindow *m){
            cube.box.location.position.x+=SHIFT_STEP;
            m->drawThingwareinWindow(&cube);
        }
        void move_x_sub(MainWindow *m){
            cube.box.location.position.x-=SHIFT_STEP;
            m->drawThingwareinWindow(&cube);
        }

        void move_y_up(MainWindow *m){
            cube.box.location.position.y+=SHIFT_STEP;
            m->drawThingwareinWindow(&cube);
        }

        void move_y_down(MainWindow *m){
            cube.box.location.position.y-=SHIFT_STEP;
            m->drawThingwareinWindow(&cube);
        }

        void move_Zz(MainWindow *m){
            cube.box.location.position.z+=SHIFT_STEP;
            m->drawThingwareinWindow(&cube);
        }

        void move_zZ(MainWindow *m){
            cube.box.location.position.z-=SHIFT_STEP;
            m->drawThingwareinWindow(&cube);
        }

        //绕x
        void rotate_lan(MainWindow *m){
            cout<<"fuckyou !"<<endl;

            cube.box.location.axis_change_a += ROTATE_STEP;
            //度数取余
            cube.box.location.axis_change_a = (int(cube.box.location.axis_change_a)) % 360;
            m->drawThingwareinWindow(&cube);
        }
        //绕y
        void rotate_long(MainWindow *m){
            cube.box.location.axis_change_b += ROTATE_STEP;
            //度数取余
            cube.box.location.axis_change_b = (int(cube.box.location.axis_change_b)) % 360;
            m->drawThingwareinWindow(&cube);
        }
        //绕z
        void rotate_z(MainWindow *m){
            cube.box.location.axis_change_r += ROTATE_STEP;
            //度数取余
            cube.box.location.axis_change_r = (int(cube.box.location.axis_change_r)) % 360;
            m->drawThingwareinWindow(&cube);
        }

        void mouse_move_lbutton_press(MainWindow *m){
            m->ui->mouse_realx_tx->setText(QString((int)mouseposition_x));
            m->ui->mouse_realy_tx->setText(QString((int)mouseposition_y));

            cube.box.location.position.x = ViewWindow.convertX( mouseposition_x )-100;
            cube.box.location.position.y = ViewWindow.convertY( mouseposition_y )-100;

            m->ui->mouse_w_x_tx->setText(QString((int)cube.box.location.position.x));
            m->ui->mouse_w_y_tx->setText(QString((int)cube.box.location.position.y));

            m->drawThingwareinWindow(&cube);
        }
        #if 0
        void computedisappertest(MainWindow *m){

            //标准z集映射测试
            double distance=0;
            QPen redpen(Qt::red,3);
            Point xy;
            for(int i=0;i<100;i++)
            {
                xy=T3Lib::D3Map::Zsmap(distance);
                m->drawdot(ViewWindow.getX(xy.x),ViewWindow.getY(xy.y),redpen);
                distance+=100;
            }

            double a= m->ui->dis_a_text->toPlainText().toDouble();
            double b= m->ui->dis_b_text->toPlainText().toDouble();
            double r=m->ui->dis_r_text->toPlainText().toDouble();
            double x=m->ui->dis_x_text->toPlainText().toDouble();
            double y=m->ui->dis_y_text->toPlainText().toDouble();
            double z=m->ui->dis_z_text->toPlainText().toDouble();

            double L=300;
            D3Point O={0+x,0+y,0+z};
            D3Point A={L* T3Lib::D3::COS(toPai(a))+x,L* T3Lib::D3::COS(toPai(b))+y,L* T3Lib::D3::COS(toPai(r))+z};
            D3Line OA(O,A);
            OA.refresh();
            const double step=100;
            distance=0;
            QPen dotPen(Qt::black,6);
            D3Point C; 
            Point mapped;
            for(int i=0;i<1200;i++){
                C=OA.antCrawl(distance);
                mapped=T3Lib::D3Map::pmap(C);
                m->drawdot(ViewWindow.getX(mapped.x),ViewWindow.getY(mapped.y),dotPen);
                distance+=step;
            }
        }
        #endif
    }dotest;

    showviewindow();

    switch(btnclicked){
    case WHICHBUTTON::GENERALTEST:
        dotest.generaltest(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    case WHICHBUTTON::DISAPPEAR_BTN:
        dotest.computedisappertest(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    case WHICHBUTTON::CUBE_PLACE_BTN:
        dotest.cubetest(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    case WHICHBUTTON::MOVE_X_ADD_BTN:
        dotest.move_x_add(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    case WHICHBUTTON::MOVE_X_SUB_BTN:
        dotest.move_x_sub(this);
        btnclicked=WHICHBUTTON::NONE;
        break;

    case WHICHBUTTON::MOVE_Y_UP_BTN:
        dotest.move_y_up(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    case WHICHBUTTON::MOVE_Y_DOWN_BTN:
        dotest.move_y_down(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    case WHICHBUTTON::MOVE_Zz_BTN:
        dotest.move_Zz(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    case WHICHBUTTON::MOVE_zZ_BTN:
        dotest.move_zZ(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    case WHICHBUTTON::ROTATE_LAN_BTN: //绕x
        dotest.rotate_lan(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    case WHICHBUTTON::ROTATE_LONG_BTN:  //绕y
        dotest.rotate_long(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    case WHICHBUTTON::ROTATE_Z_BTN:
        dotest.rotate_z(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    case WHICHBUTTON::MOUSE_MOVE_LBUTTON_PRESS:
        dotest.mouse_move_lbutton_press(this);
        btnclicked=WHICHBUTTON::NONE;
        break;
    default:
        btnclicked=WHICHBUTTON::NONE;
        break;

    }
   //任意直线消失点测试
    
}


void MainWindow::on_pushButton_clicked()
{
    btnclicked = WHICHBUTTON::GENERALTEST;
    static int testxx=1;
    resize(this->width()+(testxx)*(-1),this->height());
    testxx*=(-1);

}

void MainWindow::drawline(int x1, int y1, int x2, int y2,QPen& pen)
{
    //QPen penstyle(Qt::black,1);
    QPainter painter(this);
    QColor hourColor(127, 0, 127);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(hourColor);
    painter.save();

    painter.drawLine(x1,y1,x2,y2);
}

void MainWindow::drawdot(int x1, int y1,QPen &pen)
{
    //QPen penstyle(Qt::red,6);
    QPainter painter(this);
    QColor hourColor(127, 0, 127);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.setBrush(hourColor);
    painter.save();
    painter.drawLine(x1,y1,x1,y1);
}


void MainWindow::showviewindow()
{
    QPen pen(Qt::black,3);
    drawline(ViewWindow.A.x,ViewWindow.A.y, ViewWindow.B.x,ViewWindow.B.y,pen);
    drawline(ViewWindow.B.x,ViewWindow.B.y, ViewWindow.C.x,ViewWindow.C.y,pen);
    drawline(ViewWindow.C.x,ViewWindow.C.y, ViewWindow.D.x,ViewWindow.D.y,pen);
    drawline(ViewWindow.D.x,ViewWindow.D.y, ViewWindow.A.x,ViewWindow.A.y,pen);
    QPen pen2(Qt::gray,1);
    drawline(ViewWindow.O.x,ViewWindow.A.y, ViewWindow.O.x,ViewWindow.D.y,pen2);
    drawline(ViewWindow.A.x,ViewWindow.O.y, ViewWindow.C.x,ViewWindow.O.y,pen2);
}

void MainWindow::on_computedis_btn_clicked()
{
    btnclicked = WHICHBUTTON::DISAPPEAR_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);
}


void MainWindow::on_cube_place_btn_clicked()
{
    btnclicked = WHICHBUTTON::CUBE_PLACE_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);

}


void MainWindow::drawThingwareinWindow(T3Lib::File::ThingWare *thing){
    Point mappedpoint[100]{0};
    //首先分配内存，用来存放转化后的数据
    Point startpoint,endpoint;
    int len = sizeof(thing->box.dots[0]) * thing->box.dotscount;
    D3Point * dots = (D3Point*)malloc(len);
    for(int i=0;i<thing->box.dotscount;i++){
        dots[i] = thing->box.dots[i];
    }

    //绘图时，首先以盒子坐标系O点为参考进行旋转。然后在进行平移。
    //绕x轴
    if(!EQUALfloat(thing->box.location.axis_change_a,0)){
        for(int i=0;i<thing->box.dotscount;i++){
            dots[i]=T3Lib::D3::rotatex({0,0,0},dots[i],thing->box.location.axis_change_a);
            cout<<"0.("<<dots[i].x<<","<<dots[i].y<<","<<dots[i].z<<")"<<endl;
        }
       
    }
    //绕y轴
    if(!EQUALfloat(thing->box.location.axis_change_b,0)){
        for(int i=0;i<thing->box.dotscount;i++){
            dots[i]=T3Lib::D3::rotatey({0,0,0},dots[i],thing->box.location.axis_change_b);
        }        
    }
    //绕z轴
    if(!EQUALfloat(thing->box.location.axis_change_r,0)){
        for(int i=0;i<thing->box.dotscount;i++){
        dots[i]=T3Lib::D3::rotatez({0,0,0},dots[i],thing->box.location.axis_change_r);
        }        
    }    

    //平移所有的点
    for(int i=0;i<thing->box.dotscount;i++){
        dots[i].x+=thing->box.location.position.x;
        dots[i].y+=thing->box.location.position.y;
        dots[i].z+=thing->box.location.position.z;
    }

    //因为Zs为400，所以可以去掉坐标小数点后数字便于观察
    for(int i=0;i<thing->box.dotscount;i++){
        dots[i].x = int(dots[i].x+0.5f);
        dots[i].y = int(dots[i].y+0.5f);
        dots[i].z = int(dots[i].z+0.5f);
    }

    //映射这些点
    for(int i=0;i<thing->box.dotscount;i++){
        mappedpoint[i] = T3Lib::D3Map::pmap(dots[i]);
    }
    
    //映射并在窗口画出正方体
    for(int i=0; i<thing->box.linecount;i++){
        QPen bluepen(Qt::blue,3);

        startpoint=mappedpoint[thing->box.lines[i][0]];
        endpoint  =mappedpoint[thing->box.lines[i][1]];
        drawline(ViewWindow.getX(startpoint.x),ViewWindow.getY(startpoint.y),
                 ViewWindow.getX(endpoint.x),ViewWindow.getY(endpoint.y),bluepen);
    }
}
const double step=10.0f;
void MainWindow::on_move_x_add_btn_clicked()
{
    btnclicked = WHICHBUTTON::MOVE_X_ADD_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);
}

void MainWindow::on_move_x_sub_btn_clicked()
{
    btnclicked = WHICHBUTTON::MOVE_X_SUB_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);
}

void MainWindow::on_move_y_up_btn_clicked()
{
    btnclicked = WHICHBUTTON::MOVE_Y_UP_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);
}

void MainWindow::on_move_y_down_btn_clicked()
{
    btnclicked = WHICHBUTTON::MOVE_Y_DOWN_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);
}

void MainWindow::on_move_Zz_btn_clicked()
{
    btnclicked = WHICHBUTTON::MOVE_Zz_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);
}

void MainWindow::on_move_zZ_btn_clicked()
{
    btnclicked = WHICHBUTTON::MOVE_zZ_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);
}

void MainWindow::on_move_y_up_fuck_btn_clicked()
{
    btnclicked = WHICHBUTTON::MOVE_Y_UP_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);
}

//绕x
void MainWindow::on_rotate_lan_btn_clicked()
{
    btnclicked = WHICHBUTTON::ROTATE_LAN_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);
}

//绕y
void MainWindow::on_rotate_long_btn_clicked()
{
    btnclicked = WHICHBUTTON::ROTATE_LONG_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);
}
//绕z
void MainWindow::on_rotate_z_btn_clicked()
{
    btnclicked = WHICHBUTTON::ROTATE_Z_BTN;
    static int computex=1;
    resize(this->width()+(computex)*(-1),this->height());
    computex*=(-1);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint currentMousePt = event->pos();
    Qt::MouseButtons btns = event->buttons();
    if (Qt::LeftButton == (btns & Qt::LeftButton) )//左键按下鼠标移动响应事件
    {
        mouseposition_x = currentMousePt.x();
        mouseposition_y = currentMousePt.y();

        btnclicked = WHICHBUTTON::MOUSE_MOVE_LBUTTON_PRESS;
        update();      //更新窗口
    }
}
