#ifndef SERVICES_H
#define SERVICES_H
#include "BasicDef.h"

namespace Serivces{
    namespace HAL{
        //在窗口上绘制2D
        void dotdraw(Module::AssistDesign::XYZCoor::Point p, int radius);
        void linedraw(Module::AssistDesign::XYZCoor::Point p1,
                      Module::AssistDesign::XYZCoor::Point p2,
                      int width);
    }
}

#endif // SERVICES_H
