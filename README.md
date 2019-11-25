# LetsTouch
## Team greyglass

> 10기 소프트웨어 마에스트로 LetsTouch 프로젝트 Git
>
> 손 마디 압력 센서, 밴딩 센서 및 가속도 센서를 이용한 장갑 디바이스

![license_badge](https://img.shields.io/github/license/JeonHa/JeonHa-Server)

* 프로젝트 기간: 2019.06.01 ~ 2019.11.22




## 프로젝트 설명

**LetsTouch** 프로젝트를 통해 손의 모양과 손에 가해지는 압력을 측정할 수 있는 장갑형 디바이스를 개발한다. 디바이스에 들어가는 압력 센서를 통해 각 마디에 작용하는 힘을 측정하고, 밴딩 센서를 통해 손 마디가 굽어지는 모양을 인지 그리고 가속도 센서를 이용한 손이 돌아가는 모양을 측정한다. 센서를 통해 가져온 값을 데이터로 변환해서 SDK를 통해 제공한다. 해당 데이터를 통해 3D 손 모양 모델에 색상 및 상태를 입혀 보여준다. 



## Depenedncy

```json
{
  "dependencies": {
    "com.unity.ads": "2.0.8",
    "com.unity.analytics": "3.2.2",
    "com.unity.collab-proxy": "1.2.15",
    "com.unity.package-manager-ui": "2.0.8",
    "com.unity.purchasing": "2.0.3",
    "com.unity.textmeshpro": "1.4.1",
    "com.unity.modules.ai": "1.0.0",
    "com.unity.modules.animation": "1.0.0",
    "com.unity.modules.assetbundle": "1.0.0",
    "com.unity.modules.audio": "1.0.0",
    "com.unity.modules.cloth": "1.0.0",
    "com.unity.modules.director": "1.0.0",
    "com.unity.modules.imageconversion": "1.0.0",
    "com.unity.modules.imgui": "1.0.0",
    "com.unity.modules.jsonserialize": "1.0.0",
    "com.unity.modules.particlesystem": "1.0.0",
    "com.unity.modules.physics": "1.0.0",
    "com.unity.modules.physics2d": "1.0.0",
    "com.unity.modules.screencapture": "1.0.0",
    "com.unity.modules.terrain": "1.0.0",
    "com.unity.modules.terrainphysics": "1.0.0",
    "com.unity.modules.tilemap": "1.0.0",
    "com.unity.modules.ui": "1.0.0",
    "com.unity.modules.uielements": "1.0.0",
    "com.unity.modules.umbra": "1.0.0",
    "com.unity.modules.unityanalytics": "1.0.0",
    "com.unity.modules.unitywebrequest": "1.0.0",
    "com.unity.modules.unitywebrequestassetbundle": "1.0.0",
    "com.unity.modules.unitywebrequestaudio": "1.0.0",
    "com.unity.modules.unitywebrequesttexture": "1.0.0",
    "com.unity.modules.unitywebrequestwww": "1.0.0",
    "com.unity.modules.vehicles": "1.0.0",
    "com.unity.modules.video": "1.0.0",
    "com.unity.modules.vr": "1.0.0",
    "com.unity.modules.wind": "1.0.0",
    "com.unity.modules.xr": "1.0.0"
  }
}
```
```
nRF5_SDK_15.2.0
nRF5_SDK_15.3.0
```




## 시작하기

소스 코드는 Window 10 + Rider + Visual Studio + Unity + Pycharm + Visual Studio Code + Unity + Segger Embbed Studio를 이용하여 개발되었습니다.



#### 디바이스 설치하기
* Lets Touch Device와 함께 제공된 블루투스 동글을 꽂습니다.
* Lets Touch Device를 손에 낀 후에 전원을 켜주세요.
* 손을 가장 크게 핀 후에 LED가 점멸할 동안 3초 동안 손을 쫙 펴주세요.
* LED가 지속될 동안 손을 움크리는 자세를 취해주세요
* 그 후 LED가 3초 동안 점멸할 때 손을 꽉 쥐어주세요
* 자유롭게 움직이면 됩니다.



## 사용된 도구 

* [Node.js](https://nodejs.org/ko/) - Chrome V8 자바스크립트 엔진으로 빌드된 자바스크립트 런타임
* [Visual Studio](https://visualstudio.microsoft.com/ko/) - 유니티 및 C# 어플리케이션 개발 도구
* [Segger](https://www.segger.com/) - 펌웨어 개발 도구
* [Embbeded Studio](https://www.segger.com/) - 펌웨어 개발 도구
* [Unity](https://unity.com/kr/) - 손 모양 시각화 개발 도구
* [Pycharm](https://www.jetbrains.com/pycharm/) - SDK 개발용 도구
* [GitKraken](https://www.gitkraken.com/) - 형상 관리용 도구
* [Notion](https://www.notion.so/) - 커뮤니케이션 도구

## 개발자

* 김경준
* 오정민
* 이상윤


