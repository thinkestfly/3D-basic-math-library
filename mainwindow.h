#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "t3dimlib.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct ClientWindow{
    int x;
    int y;
};

#define SHIFT_STEP 10
#define ROTATE_STEP 30 //degree not pai

enum WHICHBUTTON{
    GENERALTEST,
    DISAPPEAR_BTN,
    CUBE_PLACE_BTN,
    MOVE_X_ADD_BTN,
    MOVE_X_SUB_BTN,
    MOVE_Y_UP_BTN,
    MOVE_Y_DOWN_BTN,
    MOVE_Zz_BTN,
    MOVE_zZ_BTN,
    ROTATE_LAN_BTN,
    ROTATE_LONG_BTN,
    ROTATE_Z_BTN,
    MOUSE_MOVE_LBUTTON_PRESS,
    NONE
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ClientWindow clientwindow;
    enum WHICHBUTTON btnclicked;
    void drawline(int x1,int y1, int x2, int y2,QPen &pen);
    void drawdot(int x1,int y1,QPen &pen);
    void showviewindow();
    void drawThingwareinWindow(T3Lib::File::ThingWare* thing);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_computedis_btn_clicked();

    void on_cube_place_btn_clicked();

    void on_pushButton_2_clicked();
    
    void on_move_x_add_btn_clicked();

    void on_move_x_sub_btn_clicked();

    void on_move_y_up_btn_clicked();

    void on_move_y_down_btn_clicked();

    void on_move_Zz_btn_clicked();

    void on_move_zZ_btn_clicked();

    void on_move_y_up_fuck_btn_clicked();

    void on_rotate_lan_btn_clicked();

    void on_rotate_long_btn_clicked();

    void on_rotate_z_btn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
