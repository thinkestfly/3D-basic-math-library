#include "t3dimlib.h"

//内存文件，定义物件
T3Lib::File::ThingWare cube(
        T3Lib::File::BOX{
            new D3Point[8]{
                {0  ,0  ,0  },
                {200,0  ,0},
                {200,200,0},
                {0  ,200,0},
                {0  ,0  ,200},
                {200,0  ,200},
                {200,200,200},
                {0  ,200,200}
            },
            8,
            new int[12][2]{
                {0,1},{1,2},{2,3},{3,0},
                {4,5},{5,6},{6,7},{7,4},
                {0,4},{1,5},{2,6},{3,7}
            },
            12,
            T3Lib::File::LOCATION{{0,0,0},0,0}
        });
