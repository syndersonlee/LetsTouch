using System;
using System.Collections.Generic;
using System.Text;

namespace EnumLT
{
    ///<summary>디바이스가 인식 중인 모션의 종류입니다.</summary>
    enum Motion
    {
        NONE,
        JAM,

    }
    ///<summary>디바이스 내부에 있는 센서의 위치입니다.</summary>
    enum Position
    {
        THUMB,
        INDEX_TIP,
        INDEX,
        MIDDLE_TIP,
        MIDDLE,
        RING_TIP,
        RING,
        LITTLE,
        LITTLE_TIP,
        PALM_RIGHT,
        PALM_LEFT,
        PALM_FREE,
    }
}
