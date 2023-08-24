#ifndef T3DIMLIB_H
#define T3DIMLIB_H

//度数大小比较。
//度数为浮点数，精确到1位。如1.10和1.14是相等的
#define EQUALdegree(a,b) (int(a*10.0)==int(b*10.0))? 1: 0
#define GREATERdegree(a,b)(int(a*10.0)>int(b*10.0))? 1: 0
#define LESSdegree(a,b)(int(a*10.0)<int(b*10.0))? 1: 0
#define EQUALfloat(a,b) (int(a*1000.0)==int(b*1000.0))? 1: 0

#define toPai(a) (3.1415926*(a)/180.0)
#define toDegree(pai) (180.0*(pai)/3.1415926)

//判断f的正负，真为正或0，假为负
bool isFloatPositive(double f);

class D3Point{
    public:
    double x,y,z;
};
class Point{
    public:
    double x,y;
};

//窗口
class {
public:
    const double start_x{50};
    const double start_y{80};
    const double width{800.0};
    const double height{800.0};
    const Point A{start_x,start_y};
    const Point B{start_x+width,start_y};
    const Point C{start_x+width,start_y+height};
    const Point D{start_x,start_y+height};
    const Point O{start_x+width/2,start_y+height/2};
    //将3D窗口的坐标转为实际的x坐标
    double getX(double x){
        return O.x+x;
    };
    //将3D窗口的坐标转为实际的y坐标
    double getY(double y){
        return O.y-y;
    };
    //将实际的坐标转为3D窗口坐标
    double convertX(double x){
        return x-O.x;
    }
    //将实际的坐标转为3D窗口坐标
    double convertY(double y){
        return O.y-y;
    }
}ViewWindow;


//3D空间中的一条线段
class D3Line{
public:
    D3Point START;
    D3Point END;

    D3Line(D3Point s, D3Point e);
    D3Line();
    void refresh();
    //线段长度
    double LineLen;

    //3D坐标系度量参数, 单位度数
    double a;  //与x轴夹角
    double b;  //与y轴夹角
    double r;  //与z轴夹角

    //地球仪旋转法相关。以startpoint为中心，做地球仪旋转运动，单位度数
    double lanti;
    double longiti;
    //latitudedegree 移动纬度单位度数, longitudedegree 移动经度单位度数
    //这个函数只对点有意义。刚体使用三轴方式旋转
    D3Point dotRotateEarth(double latitudedegree, double longitudedegree);

    //蚁爬行相关
    D3Point antCrawl(double distance); //从起点沿着AB移动len长度后C点的坐标
};

namespace T3Lib{
    //窗后3D世界算法
    namespace D3{ 
        //点平移
        //点平移非常简单，无需函数
        void dotmove();
        //点旋转。地球仪测量方式
        //角度的sin值. degree单位为度数，而非原周长
        //反三角函数返回的是-pai到+pai中的一个值。
        double SIN(double degree);
        double COS(double degree);
        double ASIN(double v);
        double ACOS(double v);
        //线段AB的长度. A为起点，B为终点
        double getLofAB(D3Point A, D3Point B);
        //o,A坐标均已映射坐标系为参考,change_a为度数。以o为原点，绕x轴旋转
        D3Point rotatex(D3Point o, D3Point A, double change_a);
        //o,A坐标均已映射坐标系为参考，change_b为度数。以o为原点，绕y轴旋转
        D3Point rotatey(D3Point o, D3Point A, double change_b);
        //o,A坐标均已映射坐标系为参考，change_z 为度数.以o为原点，绕z轴旋转
        D3Point rotatez(D3Point o, D3Point A, double change_z);
    }

    //3D向窗口映射算法
    namespace D3Map{
        //标准z集点映射
        //标准z集点映射, 起点X(400,400)。标准窗口本应该以物理长度单位，如10cm,
        // 但为简单起见，设为400个像素
        //飞镖坐标系，仅仅窗后，故z轴坐标均为正
        //映射函数为，窗后蚂蚁在Z(400,400)集直线上爬过的距离distance，即z，
        //与窗口上点到原点的距离L的
        //关系为 L= Lz . 2^(-z/Zs)，
        static const float Zs =400.0;
        Point Zsmap(double distance);

        //任意点映射到窗口，利用标准z集和平行约束
        //p为窗后任意一点，返回窗口上的映射点
        Point pmap(D3Point p);
    }
    //物件存档子模块
    namespace File{
        class LOCATION{
        public:
            D3Point position;
            double lanti;       //degree ,not pai，对于刚体，此参数无意义
            double longiti;     //degree ,not pai, 对于刚体，此参数无意义
            double axis_change_a;      //绕x轴 delta a，度数
            double axis_change_b;      //绕y轴 delta b，度数
            double axis_change_r;      //绕z轴 delta r，度数
            LOCATION():position({0,0}),lanti(0.0),longiti(0.0)
                ,axis_change_a(0.0),axis_change_b(0.0),axis_change_r(0.0){}
            LOCATION(D3Point d3,double la,double lg):
                position(d3),lanti(la),longiti(lg){}
        };

        class BOX{
            public:
            //盒子坐标为飞镖
            //盒子定位的平移坐标,默认在第三象限，以便俯视观察。为了调试方便，设在第一象限
            //D3Point shiftposition;
            //盒子定位的经纬角度，默认保持水平和垂直
            //double lanti;
            //double longiti;
            LOCATION location;
            //点集合。数点方式逆时针，从进向远
            D3Point *dots;
            int dotscount;
            //线集合
            //linedata格式 {{start,end},{start,end},{start,end}},其中点为在点集总的序号
            int (*lines)[2];
            int linecount;
            BOX(D3Point *dots,int dotcount, int (*lines)[2],int linecount,
                LOCATION loc);
            BOX();
            ~BOX();
        };
        class ThingWare{
        public:
            BOX box;
            ThingWare(BOX b);
            
        };
    }
}

#endif // T3DIMLIB_H
