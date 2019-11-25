using System;
using System.Collections.Generic;
using System.Text;
using EnumLT;

///<summary>SDK의 객체를 총괄 관리</summary>
namespace LT
{
    ///<summary>메인 클래스</summary>
    class LetsTouch

    {
        ///<summary>단 하나라도 Device와 연결되었는지 확인합니다.</summary>
        ///<returns>Device와 연결되었는가?</returns>  
        public static bool isConnected()
        {
            return false;
        }
        ///<summary>가장 빠르게 찾은 Device와 연결합니다.</summary>
        ///<returns>연결된 Device 객체를 반환합니다.</returns>  
        public static Device connect()
        {
            return null;
        }
        ///<summary>Device와 연결합니다.</summary>
        ///<param name = "port" ></param>
        ///<returns>연결된 Device 객체를 반환합니다.</returns>  
        public static Device connect(int port)
        {
            return null;
        }
        ///<summary>연결된 Device 객체를 제공합니다.</summary>
        ///<returns>연결된 Device 객체 배열을 반환합니다.</returns>  
        public static Device[] GetDevices()
        {
            return null;
        }
        ///<summary>연결된 Device 객체를 제공합니다.</summary>
        ///<param name = "index" ></param>
        ///<returns>연결된 Device 객체를 반환합니다.</returns>  
        public static Device GetDevice(int index)
        {
            return GetDevices()[index];
        }
        ///<summary>모든 Device 객체를 초기화합니다.</summary>
        public void Reset()
        {

        }
    }
    ///<summary>연결된 디바이스들을 관리합니다.</summary>
    class Device
    {
        ///<summary>Hand 객체를 반환합니다.</summary>
        ///<returns>Hand 객체를 반환합니다.</returns>
        public Hand GetHand()
        {
            return null;
        }
        ///<summary>해당 Device를 Reload합니다</summary>
        public void Reload()
        {

        }
        ///<summary>해당 Device를 초기화합니다</summary>
        public void Reset()
        {

        }
    }
    ///<summary>연결된 디바이스의 센서와 모션을 관리합니다.</summary>
    class Hand
    {
        private Motion currentMotion = Motion.NONE;
        private int[] positionValue = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ///<summary>Device의 현재 모션을 반환합니다.</summary>
        ///<returns>Motion Enum을 반환합니다.</returns>
        public Motion GetMotion()
        {
            return Motion.NONE;
        }
        ///<summary>센서의 현재 값을 반환합니다.</summary>
        ///<param name = "position" ></param >
        ///<returns>0~255 사이의 값을 반환합니다.</returns>
        public int GetValue(Position position)
        {
            return positionValue[(int)position];
        }
    }
}
