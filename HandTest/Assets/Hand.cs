using TMPro;
using UnityEngine;

public class Hand
{
    private readonly Palm _palm;
    private readonly Phalanx[] _thumb, _index, _middle, _ring, _little;
    private readonly GameObject[] _pressure;

    public Hand(string type, Vector3 pos)
    {
        _palm = new Palm(type, pos);
        _thumb = new Phalanx[2];
        _index = new Phalanx[3];
        _middle = new Phalanx[3];
        _ring = new Phalanx[3];
        _little = new Phalanx[3];

        var dir = 0;
        if (type == "left") dir = 1;
        else if (type == "right") dir = -1;
        
        for (var i = 0; i < _thumb.Length; ++i)
        {
            var name = "thumb" + (i + 1);
            var phalanxPos = new Vector3(0, 0, 1);
            var parent = _palm.Body;
            if (i == 0) phalanxPos += _palm.LocalFingerPoints[0] + new Vector3(dir * 0.5f, 0, -0.5f);
            else parent = _thumb[i - 1].Body;
            _thumb[i] = new Phalanx(type, name, phalanxPos, parent);
            
            
        }
        for (var i = 0; i < _index.Length; ++i)
        {
            var name = "index" + (i + 1);
            var phalanxPos = new Vector3(0, 0, 1);
            var parent = _palm.Body;
            if (i == 0) phalanxPos += _palm.LocalFingerPoints[1] + new Vector3(0, 0, -0.5f);
            else parent = _index[i - 1].Body;
            _index[i] = new Phalanx(type, name, phalanxPos, parent);
            
        }
        for (var i = 0; i < _middle.Length; ++i)
        {
            var name = "middle" + (i + 1);
            var phalanxPos = new Vector3(0, 0, 1);
            var parent = _palm.Body;
            if (i == 0) phalanxPos += _palm.LocalFingerPoints[2] + new Vector3(0, 0, -0.5f);
            else parent = _middle[i - 1].Body;
            _middle[i] = new Phalanx(type, name, phalanxPos, parent);
        }
        for (var i = 0; i < _ring.Length; ++i)
        {
            var name = "ring" + (i + 1);
            var phalanxPos = new Vector3(0, 0, 1);
            var parent = _palm.Body;
            if (i == 0) phalanxPos += _palm.LocalFingerPoints[3] + new Vector3(0, 0, -0.5f);
            else parent = _ring[i - 1].Body;
            _ring[i] = new Phalanx(type, name, phalanxPos, parent);
        }
        for (var i = 0; i < _little.Length; ++i)
        {
            var name = "little" + (i + 1);
            var phalanxPos = new Vector3(0, 0, 1);
            var parent = _palm.Body;
            if (i == 0) phalanxPos += _palm.LocalFingerPoints[4] + new Vector3(0, 0, -0.5f);
            else parent = _little[i - 1].Body;
            _little[i] = new Phalanx(type, name, phalanxPos, parent);
        }
        
        var parentArray = new[]
        {
            _thumb[1], _index[2], _index[0], _middle[2], _middle[0], _little[2], _little[0], _ring[2], _ring[0]
        };
        _pressure = new GameObject[12];
        for (var i = 0; i < _pressure.Length; ++i)
        {
            _pressure[i] = GameObject.CreatePrimitive(PrimitiveType.Quad);
            _pressure[i].name = "P" + (i + 1);
            if (i < parentArray.Length)
            {
                _pressure[i].transform.parent = parentArray[i].Body.transform;
                _pressure[i].transform.localPosition = new Vector3(0, -0.4001f, 0);
                _pressure[i].transform.localScale = new Vector3(0.6f, 0.6f, 1);
            }
            else
            {
                _pressure[i].transform.parent = _palm.Body.transform;
                _pressure[i].transform.localScale = new Vector3(1.8f, 1.8f, 1);
            }
            _pressure[i].transform.localEulerAngles = new Vector3(-90, -90, 0);
        }
        _pressure[9].transform.localPosition = new Vector3(dir * 1, -0.4001f, -1);
        _pressure[10].transform.localPosition = new Vector3(dir * 1, -0.4001f, 1);
        _pressure[11].transform.localPosition = new Vector3(dir * -1, -0.4001f, 1);
    }

    public void Move(Vector3 v)
    {
        _palm.Body.transform.localPosition += v;
    }

    public void setPosition(Vector3 v)
    {
        _palm.Body.transform.localPosition = v;
    }

    public void Rotate(Vector3 angle)
    {
        _palm.Body.transform.localEulerAngles += angle;
    }

    public void SetEulerAngles(Vector3 angle)
    {
        _palm.Body.transform.localEulerAngles = angle;
    }
    
    public void RotateThumb(int idx, float angle)
    {
        if (idx > _thumb.Length - 1) return;
        var point = _palm.Body.transform.TransformPoint(_palm.LocalFingerPoints[0]);
        var axis = _palm.Body.transform.TransformDirection(_palm.ThumbVector);
        if (idx > 0)
        {
            point = _thumb[idx - 1].Body.transform.TransformPoint(_thumb[idx - 1].LocalJointPoint);
            axis = _thumb[idx - 1].Body.transform.TransformDirection(_thumb[idx - 1].JointVector);
        }
        _thumb[idx].Body.transform.RotateAround(point, axis, angle);
        _thumb[idx].Angle += angle;
    }
    
    public void SetRotateThumb(int idx, float angle)
    {
        if (idx > _thumb.Length - 1) return;
        var point = _palm.Body.transform.TransformPoint(_palm.LocalFingerPoints[0]);
        var axis = _palm.Body.transform.TransformDirection(_palm.ThumbVector);
        if (idx > 0)
        {
            point = _thumb[idx - 1].Body.transform.TransformPoint(_thumb[idx - 1].LocalJointPoint);
            axis = _thumb[idx - 1].Body.transform.TransformDirection(_thumb[idx - 1].JointVector);
        }
        _thumb[idx].Body.transform.RotateAround(point, axis, angle - _thumb[idx].Angle);
        _thumb[idx].Angle = angle;
    }
    
    public void RotateIndexFinger(int idx, float angle)
    {
        if (idx > _index.Length - 1) return;
        var point = _palm.Body.transform.TransformPoint(_palm.LocalFingerPoints[1]);
        var axis = _palm.Body.transform.TransformDirection(_palm.FingersVector);
        if (idx > 0)
        {
            point = _index[idx - 1].Body.transform.TransformPoint(_index[idx - 1].LocalJointPoint);
            axis = _index[idx - 1].Body.transform.TransformDirection(_index[idx - 1].JointVector);
        }
        _index[idx].Body.transform.RotateAround(point, axis, angle);
        _index[idx].Angle += angle;
    }
    
    public void SetRotateIndexFinger(int idx, float angle)
    {
        if (idx > _index.Length - 1) return;
        var point = _palm.Body.transform.TransformPoint(_palm.LocalFingerPoints[1]);
        var axis = _palm.Body.transform.TransformDirection(_palm.FingersVector);
        if (idx > 0)
        {
            point = _index[idx - 1].Body.transform.TransformPoint(_index[idx - 1].LocalJointPoint);
            axis = _index[idx - 1].Body.transform.TransformDirection(_index[idx - 1].JointVector);
        }
        _index[idx].Body.transform.RotateAround(point, axis, angle - _index[idx].Angle);
        _index[idx].Angle = angle;
    }

    public void RotateMiddleFinger(int idx, float angle)
    {
        if (idx > _middle.Length - 1) return;
        var point = _palm.Body.transform.TransformPoint(_palm.LocalFingerPoints[2]);
        var axis = _palm.Body.transform.TransformDirection(_palm.FingersVector);
        if (idx > 0)
        {
            point = _middle[idx - 1].Body.transform.TransformPoint(_middle[idx - 1].LocalJointPoint);
            axis = _middle[idx - 1].Body.transform.TransformDirection(_middle[idx - 1].JointVector);
        }
        _middle[idx].Body.transform.RotateAround(point, axis, angle);
        _middle[idx].Angle += angle;
    }
    
    public void SetRotateMiddleFinger(int idx, float angle)
    {
        if (idx > _middle.Length - 1) return;
        var point = _palm.Body.transform.TransformPoint(_palm.LocalFingerPoints[2]);
        var axis = _palm.Body.transform.TransformDirection(_palm.FingersVector);
        if (idx > 0)
        {
            point = _middle[idx - 1].Body.transform.TransformPoint(_middle[idx - 1].LocalJointPoint);
            axis = _middle[idx - 1].Body.transform.TransformDirection(_middle[idx - 1].JointVector);
        }
        _middle[idx].Body.transform.RotateAround(point, axis, angle - _middle[idx].Angle);
        _middle[idx].Angle = angle;
    }
    
    public void RotateRingFinger(int idx, float angle)
    {
        if (idx > _ring.Length - 1) return;
        var point = _palm.Body.transform.TransformPoint(_palm.LocalFingerPoints[3]);
        var axis = _palm.Body.transform.TransformDirection(_palm.FingersVector);
        if (idx > 0)
        {
            point = _ring[idx - 1].Body.transform.TransformPoint(_ring[idx - 1].LocalJointPoint);
            axis = _ring[idx - 1].Body.transform.TransformDirection(_ring[idx - 1].JointVector);
        }
        _ring[idx].Body.transform.RotateAround(point, axis, angle);
        _ring[idx].Angle += angle;
    }
    
    public void SetRotateRingFinger(int idx, float angle)
    {
        if (idx > _ring.Length - 1) return;
        var point = _palm.Body.transform.TransformPoint(_palm.LocalFingerPoints[3]);
        var axis = _palm.Body.transform.TransformDirection(_palm.FingersVector);
        if (idx > 0)
        {
            point = _ring[idx - 1].Body.transform.TransformPoint(_ring[idx - 1].LocalJointPoint);
            axis = _ring[idx - 1].Body.transform.TransformDirection(_ring[idx - 1].JointVector);
        }
        _ring[idx].Body.transform.RotateAround(point, axis, angle - _ring[idx].Angle);
        _ring[idx].Angle = angle;
    }
    
    public void RotateLittleFinger(int idx, float angle)
    {
        if (idx > _little.Length - 1) return;
        var point = _palm.Body.transform.TransformPoint(_palm.LocalFingerPoints[4]);
        var axis = _palm.Body.transform.TransformDirection(_palm.FingersVector);
        if (idx > 0)
        {
            point = _little[idx - 1].Body.transform.TransformPoint(_little[idx - 1].LocalJointPoint);
            axis = _little[idx - 1].Body.transform.TransformDirection(_little[idx - 1].JointVector);
        }
        _little[idx].Body.transform.RotateAround(point, axis, angle);
        _little[idx].Angle += angle;
    }
    
    public void SetRotateLittleFinger(int idx, float angle)
    {
        if (idx > _little.Length - 1) return;
        var point = _palm.Body.transform.TransformPoint(_palm.LocalFingerPoints[4]);
        var axis = _palm.Body.transform.TransformDirection(_palm.FingersVector);
        if (idx > 0)
        {
            point = _little[idx - 1].Body.transform.TransformPoint(_little[idx - 1].LocalJointPoint);
            axis = _little[idx - 1].Body.transform.TransformDirection(_little[idx - 1].JointVector);
        }
        _little[idx].Body.transform.RotateAround(point, axis, angle - _little[idx].Angle);
        _little[idx].Angle = angle;
    }

    public void SetColors(Color[] colorArray)
    {
        for (var i = 0; i < (colorArray.Length > _pressure.Length ? colorArray.Length : _pressure.Length); ++i)
            _pressure[i].GetComponent<Renderer>().material.color = colorArray[i];
    }

    public void SetColor(int idx, Color color)
    {
        _pressure[idx].GetComponent<Renderer>().material.color = color;
    }
    public void SetColor(int idx, int level)
    {
        _pressure[idx].GetComponent<Renderer>().material.color = new Color(level/255f,0,1-level/255f);
    }
    
    public void RotateFinger5(float angle)
    {
        for (var i = 0; i < _little.Length; ++i)
            SetRotateLittleFinger(i, angle);
    }
    public void RotateFinger4(float angle)
    {
        for (var i = 0; i < _ring.Length; ++i)
            SetRotateRingFinger(i,angle);
    }
    public void RotateFinger3(float angle)
    {
        for (var i = 0; i < _middle.Length; ++i)
            SetRotateMiddleFinger(i,angle);
    }
    
    public void RotateFinger2(float angle)
    {
        for (var i = 0; i < _index.Length; ++i)
            SetRotateIndexFinger(i,angle);
    }
    public void RotateFinger1(float angle)
    {
        for (var i = 0; i < _thumb.Length; ++i)
            SetRotateThumb(i,angle);
    }
}

public class Palm
{
    public readonly GameObject Body;
    public Vector3 ThumbVector, FingersVector;
    public readonly Vector3[] LocalFingerPoints;

    public Palm(string type, Vector3 pos)
    {
        Body = new GameObject("PalmBody_" + type);
        Body.transform.position = pos;
        Body.transform.rotation = Quaternion.identity;
        
        var ob = GameObject.CreatePrimitive(PrimitiveType.Cube);
        ob.transform.parent = Body.transform;
        ob.name = "palm_" + type;
        ob.transform.localScale = new Vector3(4, 0.8f, 4);
        ob.transform.localPosition = Vector3.zero;
        ob.transform.localRotation = Quaternion.identity;

        var dir = 0;
        if (type == "left") dir = 1;
        else if (type == "right") dir = -1;
        LocalFingerPoints = new []
        {
            new Vector3(dir * 2, -0.5f, 0),
            new Vector3(dir * 1.5f, 0, 2),
            new Vector3(dir * 0.5f, 0, 2),
            new Vector3(dir * -0.5f, 0, 2),
            new Vector3(dir * -1.5f, 0, 2)
        };
        ThumbVector = new Vector3(0, 0, dir * -1);
        FingersVector = new Vector3(1, 0, 0);
    }
}

public class Phalanx
{
    public readonly GameObject Body;
    public Vector3 JointVector, LocalJointPoint;
    public float Angle;

    public Phalanx(string type, string name, Vector3 pos, GameObject parent)
    {
        Body = new GameObject(name + "Body_" + type);
        Body.transform.parent = parent.transform;
        Body.transform.localPosition = pos;
        Body.transform.localRotation = Quaternion.identity;
        
        var ob = GameObject.CreatePrimitive(PrimitiveType.Cube);
        ob.transform.parent = Body.transform;
        ob.name = name + "_" + type;
        ob.transform.localScale = new Vector3(0.8f, 0.8f, 0.8f);
        ob.transform.localPosition = Vector3.zero;
        ob.transform.localRotation = Quaternion.identity;
        
        LocalJointPoint = new Vector3(0, 0, 0.5f);
        JointVector = new Vector3(1, 0, 0);

        Angle = 0f;
    }
}