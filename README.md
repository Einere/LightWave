# LightWave
광운대학교 산학연계 "한국인프라" &amp; "무민골짜기"팀 - 광파기와 연결된 PC와 모바일간의 통신

---
## 서버 애플리케이션 Visual Studio 기본 설정
프로젝트 > 프로젝트 속성 > 구성 속성 안에있는
1. **VC++ 디렉터리** 카테고리에서
    - 포함 디렉터리: **$(ProjectDir)\proj4\include;** 추가
    - 라이브러리 디렉터리: **$(ProjectDir)\proj4\lib;** 추가
2. **링커 > 입력** 카테고리에서
    - 추가 종속성: **msvcrtd.lib;msvcmrt.lib;proj.lib;proj_i.lib;** 추가
3. **C/C++ > 코드 생성** 카테고리에서
    - 런타임 라이브러리: **다중 스레드 디버그 DLL(/MDd)**(디버그 모드) 혹은 **다중 스레드 DLL(/MD)**(릴리즈 모드) 선택
