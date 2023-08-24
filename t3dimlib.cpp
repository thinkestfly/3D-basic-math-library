#include "t3dimlib.h"
#include <math.h>

D3Line::D3Line(D3Point s, D3Point e)
{
    START = s;
    END = e;
}
D3Line::D3Line(){
    this->START = {0,0,0};
    this->END = {0,0,0};
    this->a = 0;
    this->b = 0;
    this->r = 0;
    this->lanti = 0;
    this->longiti = 0;
    this->LineLen =0;
}

void D3Line::refresh()
{
    double tempvalue;
    double L = T3Lib::D3::getLofAB(START,END);

    //初始化线段长度
    LineLen = L;

    //初始化a,b,c三个角度
    if(EQUALfloat(L,0.0)){
        a=b=r=0.0;
        lanti=longiti=0;
        return;
    }
    else{
        tempvalue = (END.x-START.x)/L;
        a=toDegree(T3Lib::D3::ACOS(tempvalue));
        tempvalue = (END.y - START.y)/L;
        b=toDegree(T3Lib::D3::ACOS(tempvalue));
        tempvalue = (END.z - START.z)/L;
        r=toDegree(T3Lib::D3::ACOS(tempvalue));
    }

    //初始化地球仪移动度数
    tempvalue = L*T3Lib::D3::SIN(toPai(b));
    if(!EQUALfloat(tempvalue,0.0))
        tempvalue=(END.x-START.x)/tempvalue;
    lanti=toDegree(T3Lib::D3::ACOS(tempvalue));
    longiti=b;
}

D3Point D3Line::antCrawl(double distance)
{
    double x = START.x + distance*T3Lib::D3::COS(toPai(a));
    double y = START.y + distance*T3Lib::D3::COS(toPai(b));
    double z = START.z + distance*T3Lib::D3::COS(toPai(r));
    D3Point p{x,y,z};
    return p;
}

D3Point D3Line::dotRotateEarth(double lat_change, double longi_change)
{
    D3Point newpos;
    newpos.x = START.x + this->LineLen*T3Lib::D3::SIN(toPai(this->longiti-longi_change))
                        *T3Lib::D3::COS(toPai(this->lanti+lat_change));
    newpos.y = START.y + this->LineLen*T3Lib::D3::COS(toPai(this->longiti-longi_change));
    newpos.z = START.z + this->LineLen*T3Lib::D3::SIN(toPai(this->longiti-longi_change))
                        *T3Lib::D3::SIN(toPai(this->lanti+lat_change));
    return newpos;
}

void T3Lib::D3::dotmove(){ ;}


//库函数的度数以pai衡量，而非度数
//angle -
double T3Lib::D3::SIN(double angle){

    return sin(angle);
}
double T3Lib::D3::COS(double angle){
    return cos(angle);
}
double T3Lib::D3::ASIN(double v){
    return asin(v);
}
double T3Lib::D3::ACOS(double v){
    return acos(v);
}

//使用(1,1,1) (2,3,4)，已测
double T3Lib::D3::getLofAB(D3Point A, D3Point B){
    double res = (A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y) + (A.z - B.z)*(A.z - B.z);
    return sqrt(res);
}


//L=L_0 (e^(-az))
//distance,蚂蚁爬过的距离
Point T3Lib::D3Map::Zsmap(double distance)
{
#if 0
    double Lz = sqrt(Zs * Zs*2);
    double z = distance;
    //算出L
    double tempval=exp2(-z/Lz);
    double L = Lz * tempval;
    //求出X(Zx,Zx)
    double Zx = L * T3Lib::D3::COS(toPai(45));
    return {Zx,Zx};
#endif
#if 0 //使用L=Lz*Zs/sqrt(Zs*Zs+z*z)衰减函数
    double z = distance;
    double Lz = sqrt(Zs*Zs*2);
    double L = (Lz*Zs)/sqrt(Zs*Zs+z*z);
    double Zx=L*T3Lib::D3::COS(toPai(45));
    return {Zx,Zx};
#endif
#if 0
    //使用L=Lz-Lz.z/sqrt(Zs*Zs+z*z)
    double z = distance;
    double Lz = sqrt(Zs*Zs*2);
    double L = Lz - Lz*z/sqrt(Zs*Zs+z*z);
    double Zx = L*T3Lib::D3::COS(toPai(45));
    return {Zx,Zx};
#endif
#if 1
    //再次修改衰减函数，使用 L=Lz.Zs/(Zs+z)
    double z = distance;
    double Lz = sqrt(Zs*Zs*2);
    double L=Lz*Zs/(Zs+z);
    double Zx = L*T3Lib::D3::COS(toPai(45));
    return {Zx,Zx};

#endif
}

Point T3Lib::D3Map::pmap(D3Point A)
{
    //const double a = 0.34657 / Zs;

    //点在窗口上
    if(EQUALfloat(A.z,0.0))
        return {A.x,A.y};
    //点在xz平面上
    //if(EQUALfloat(A.y,0.0))
        //return {A.x,0.0};
    //点在yz平面上
    //if(EQUALfloat(A.x,0.0))
        //return {0.0,A.y};
    //点在z轴上
    if( (EQUALfloat(A.x,0.0)) & (EQUALfloat(A.y,0.0)) )
        return {0,0};
    //
#if 0
    double tempval = exp2(-A.z/Zs);
    double mx=A.x * tempval;
    double my = A.y * tempval;
    return {mx,my};
#endif
#if 0    //使用L=Lz*Zs/sqrt(Zs*Zs+z*z)衰减函数
    double temp = sqrt(Zs*Zs+A.z*A.z);
    //mx = x.L/Lz = x.Zs/sqrt(Zs*Zs+z*z)
    double mx = A.x * Zs /temp;
    //my = y.L/Lz = y.Zs/sqrt(Zs*Zs+z*z)
    double my = A.y * Zs/temp;
    return {mx,my};
#endif
#if 0
    // 使用L=Lz-Lz.z/sqrt(Zs*Zs+z*z)衰减函数
    double z = A.z;
    double a = 1-z/sqrt(Zs*Zs+z*z);
    //mx = x.L/Lz
    double mx = A.x * a;
    //my = y.L/Lz 
    double my = A.y * a;
    return {mx,my};
#endif
#if 1
    //再次修改衰减函数，使用 L=Lz.Zs/(Zs+z)
    double z=A.z;
    //mx = x.L/Lz=x.Zs/(Zs+z)
    double mx = A.x * Zs/(Zs+z);
    //my = y.L/Lz = y.Zs/(Zs+z)
    double my = A.y * Zs/(Zs+z);
    return {mx,my};

#endif
}
#if 0
Point T3Lib::D3Map::pmap(D3Point A)
{
    //点在窗口上
    if(EQUALfloat(A.z,0.0))
        return {A.x,A.y};
    //点在xz平面上
    if(EQUALfloat(A.y,0.0))
        return {A.x,0.0};
    //点在yz平面上
    if(EQUALfloat(A.x,0.0))
        return {0.0,A.y};

    //由标准z集计算蚂蚁爬行比例
    Point C=T3Lib::D3Map::Zsmap(A.z);
    double scale=C.x / T3Lib::D3Map::Zx;
    //蚂蚁在OA2线段上爬行
    D3Point A2{A.x,A.y,0};
    D3Line LOA2({0,0,0},A2);
    LOA2.refresh();
    double distance = LOA2.LineLen*scale;
    D3Point r = LOA2.antCrawl(distance);

    return { r.x,r.y };
}
#endif

T3Lib::File::BOX::BOX(D3Point *dotp,int dotcountp,int linesp[12][2],int linecoutp,
                     LOCATION loc){
    this->dots = dotp;
    this->dotscount = dotcountp;
    this->lines = linesp;
    this->linecount = linecoutp;
    this->location = loc;
}
T3Lib::File::BOX::BOX(){
    this->dots = nullptr;
    this->lines = nullptr;
    this->dotscount =0;
    this->linecount =0;
    this->location.lanti = 0;
    this->location.longiti = 0;
    this->location.position = {0,0,0};
}

//这里内存释放有问题。退出函数体时，局部变量b将被销毁，
//导致thingware的dots失去数据。所以将b设为null。
T3Lib::File::ThingWare::ThingWare(BOX b)
{
    //this->box = b;
    this->box.dotscount = b.dotscount;
    this->box.linecount = b.linecount;
    this->box.location = b.location;
    this->box.dots = b.dots;
    this->box.lines = b.lines;
    b.dots = nullptr;
    b.lines = nullptr;

}
T3Lib::File::BOX::~BOX(){
    if(nullptr != this->dots)
       delete [] this->dots;
    if(nullptr != lines)
       delete [] lines;
}

D3Point T3Lib::D3::rotatex(D3Point O, D3Point A, double change_a){
    double temp = (A.z - O.z)*(A.z - O.z) + (A.y - O.y)*(A.y - O.y);
    double R = sqrt(temp);
    if(EQUALfloat(R,0))
        return A;
    //计算角度，并调整正负
    double a = toDegree( T3Lib::D3::ACOS((A.z-O.z)/R) );
    if(isFloatPositive(A.y-O.y)){
        a=a;
    }else{
        a=a*(-1.0);
    }

    double x = O.x+A.x;
    double y = O.y + R*T3Lib::D3::SIN(toPai(a+change_a));
    double z = O.z + R*T3Lib::D3::COS(toPai(a+change_a));
    return {x,y,z};
}

D3Point T3Lib::D3::rotatey(D3Point O, D3Point A, double change_b){
    double temp = (A.z - O.z)*(A.z - O.z) + (A.x - O.x)*(A.x - O.x);
    double R = sqrt(temp);
    if(EQUALfloat(R,0))
        return A;
    //计算角度，并调整正负
    double b = toDegree( T3Lib::D3::ACOS((A.x-O.x)/R) ); //ACOS返回值不可能是负数
    if(isFloatPositive(A.z-O.z))
    {
        b=b;
    }else{
        b=b*(-1.0);
    }

    double x = O.x+R*T3Lib::D3::COS(toPai(b+change_b));
    double y = O.y + A.y;
    double z = O.z + R*T3Lib::D3::SIN(toPai(b+change_b));
    return {x,y,z};
}

D3Point T3Lib::D3::rotatez(D3Point O, D3Point A, double change_z){
    double temp = (A.y - O.y)*(A.y - O.y) + (A.x - O.x)*(A.x - O.x);
    double R = sqrt(temp);
    if(EQUALfloat(R,0))
        return A;
    //计算角度，并调整正负
    double r = toDegree( T3Lib::D3::ACOS((A.x-O.x)/R) );
    if(isFloatPositive(A.y-O.y)){
        r=r;
    }else{
        r=r*(-1.0);
    }

    double x = O.x+R*T3Lib::D3::COS(toPai(r+change_z));
    double y = O.y+R*T3Lib::D3::SIN(toPai(r+change_z));
    double z = O.z + A.z;
    return {x,y,z};
}


bool isFloatPositive(double f) {
    int r;
    r = (int)f;
    if (r > 0)
        return true;
    if (r < 0)
        return false;
    //纯小数，0.2， -0.2等
    f += 1.0;
    r = (int)f;
    if (r == 1)
        return true;
    else
        return false;
}