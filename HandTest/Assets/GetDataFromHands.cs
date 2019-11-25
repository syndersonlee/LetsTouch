using System;
using System.IO.Ports;
using System.Text;
using UnityEngine;
using GreyGlass;

public class GetDataFromHands : MonoBehaviour
{
    private Hand _left, _right;
    private int[] _leftPressure=new int[12], _leftBending=new int[5], _leftAccelerate=new int[3];
    private int[] _rightPressure=new int[12], _rightBending=new int[5], _rightAccelerate=new int[3];
    
    // Start is called before the first frame update
    private void Handle(object sender, SerialDataReceivedEventArgs e)
    {
        print("HANDL");
        /*
        IsAlive = true;
        posttime = DateTime.Now.Ticks;
        IsConnected = true;
        int rSize = _port.BytesToRead;
        byte[] b = new byte[rSize];
        _port.Read(b, 0, rSize);
        if (rSize >= 23)
        {
            for (int i = 0; i < 5; i++)
                Bending[i] = b[i];
            for (int i = 0; i < 12; i++)
                Pressure[i] = b[5 + i];
            for (int i = 0; i < 3; i++)
                Accelerate[i] = b[17 + i*2]*(b[17 + i*2+1]==0?1:-1)*9;
        }
*/
    }
    SerialPort serialPort = new SerialPort("COM3", 115200);
    void Start()
    {
        print("INIT");
        
        
        serialPort.Encoding = Encoding.Default;
        serialPort.Parity = Parity.None;
        serialPort.DataBits = 8;
        serialPort.DtrEnable = true;
        serialPort.StopBits = StopBits.One;
        serialPort.DataReceived += Handle;
        serialPort.Open();
        
        // if (InitLeft("COM3"))
//        {
//            _left = new Hand("left", new Vector3(-7, 0, 0));
//            //
//            _left.RotateThumb(0, 45);
//            _left.RotateThumb(1, 45);
//            _left.RotateIndexFinger(0, 60);
//            _left.RotateIndexFinger(1, 60);
//            _left.RotateIndexFinger(2, 60);
//            _left.RotateMiddleFinger(0, 45);
//            _left.RotateMiddleFinger(1, 45);
//            _left.RotateMiddleFinger(2, 45);
//            _left.RotateRingFinger(0, 30);
//            _left.RotateRingFinger(1, 30);
//            _left.RotateRingFinger(2, 30);
//            _left.RotateLittleFinger(0, 15);
//            _left.RotateLittleFinger(1, 15);
//            _left.RotateLittleFinger(2, 15);
//            _left.Move(new Vector3(-1, -1, 1));
//            
//            var colors = new[]
//            {
//                new Color(1f, 0.0f, 0.0f, 1f),
//                Color.red, 
//                new Color(0/255f, 127/255f, 255/255f, 255/255f),
//                Color.black, Color.blue, Color.blue, Color.gray, Color.magenta, Color.gray, Color.yellow, 
//                Color.green, Color.blue
//            };
//            _left.SetColor(colors);
//            //
//        }

        // if (InitRight("COM4"))
        {
            _right = new Hand("right", new Vector3(7, 0, 0));
            //
//            _right.Rotate(new Vector3(30, 30, 0));
        }
    }
    // Update is called once per frame
    void Update()
    {
        
        // get Data from BlueTooth

        print("UPDATE1"+serialPort.IsOpen+_rightAccelerate[0]);
        if (serialPort.IsOpen)
        {
            print("ss" + serialPort.BytesToRead);
            if (serialPort.BytesToRead >= 23)
            {
//                posttime = DateTime.Now.Ticks;
//                IsConnected = true;
                int rSize = serialPort.BytesToRead;
                byte[] b = new byte[rSize];
                serialPort.Read(b, 0, rSize);
                if (rSize >= 23)
                {
                    for (int i = 0; i < 5; i++)
                        _rightBending[i] = b[i];
                    /*for (int i = 0; i < 5; i++)
                        switch (i)
                        {
                            case 0:
                                _right.RotateFinger1(_rightBending[i]);
                                break;
                            case 1:
                                _right.RotateFinger2(_rightBending[i]);
                                break;
                            case 2:
                                _right.RotateFinger3(_rightBending[i]);
                                break;
                            case 3:
                                _right.RotateFinger4(_rightBending[i]);
                                break;
                            case 4://새끼
                                _right.RotateFinger5(_rightBending[i]);
                                break;
                        }*/
                    for (int i = 0; i < 12; i++)
                    {
                        _rightPressure[i] = b[5 + i];
                        _right.SetColor(i,_rightPressure[i]);
                    }
                    for (int i = 0; i < 3; i++)
                        _rightAccelerate[i] = b[17 + i*2]*(b[17 + i*2+1]==0?1:-1);
                }
                _right.SetEulerAngles(new Vector3(-_rightAccelerate[0],-_rightAccelerate[2],-_rightAccelerate[1]));
            }
        }
/*
        if (LetsTouch.InitRight("COM3"))
        {
            print("UPDATE2");
            Device d=LetsTouch.RightDevice;
            if (d.IsConnected)
            {
                print("UPDATE3"+d.IsAlive);
                if (d.IsAlive)
                {
                    print("UPDATE4");
                    _leftAccelerate = LetsTouch.LeftDevice.Accelerate;
                    _leftPressure = LetsTouch.LeftDevice.Pressure;
                    _leftBending = LetsTouch.LeftDevice.Bending;
                    
                    print($"UPDATE {_leftAccelerate[0]}/{_leftAccelerate[1]}/{_leftAccelerate[2]}");
                    _right.setEulerAngles(new Vector3(_leftAccelerate[0],_leftAccelerate[1],_leftAccelerate[2]));
                    
                }
            }
        }*/
    }

    private void OnApplicationQuit()
    {
        serialPort.Close();
        LetsTouch.LeftDevice?.Close();
    }
}
