#ifndef BASICDEF_H
#define BASICDEF_H
namespace Module{
namespace AssistDesign{
    class XYZCoor{
    public:
        struct Point{
            int x;  //值以xyz最小单位计算。当前最小单位设为1个像素，简化设计
            int y;
        };
    };
}
}
#endif // BASICDEF_H
