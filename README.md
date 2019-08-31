# LightWave
광운대학교 산학연계 "한국인프라" &amp; "무민골짜기"팀 - 광파기와 연결된 PC와 모바일간의 통신

## 서버 애플리케이션 Visual Studio 기본 설정
프로젝트 > 프로젝트 속성 > 구성 속성 안에있는
1. **VC++ 디렉터리** 카테고리에서
    - 포함 디렉터리: **$(ProjectDir)\proj4\include;** 추가
    - 라이브러리 디렉터리: **$(ProjectDir)\proj4\lib;** 추가
2. **링커 > 입력** 카테고리에서
    - 추가 종속성: **msvcrtd.lib;msvcmrt.lib;proj.lib;proj_i.lib;** 추가
3. **C/C++ > 코드 생성** 카테고리에서
    - 런타임 라이브러리: **다중 스레드 디버그 DLL(/MDd)**(디버그 모드) 혹은 **다중 스레드 DLL(/MD)**(릴리즈 모드) 선택
## 각종 저장 위치
#### 작업
File file = new File(Environment.getExternalStorageDirectory() + "/" + taskId);
#### 점
File file2 = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum);
#### 앱에 올린 사진
File uploadFile = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/uploadfile");
#### 위경도, 방위 정보
File file4 = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/textfile");
#### 메모
File file5 = new File(Environment.getExternalStorageDirectory() + "/" + taskId + "/" + pointNum + "/memofile");
#### 사진 저장 위치
String path = Environment.getExternalStorageDirectory() + "/" + workNum + "/" + pointNum;
#### 위경도 저장 위치
String path2 = Environment.getExternalStorageDirectory() + "/" + workNum + "/" + pointNum + "/" + "textfile";
#### 사진 촬영할 때 왜 여기다 저장하는지 모르겠음.. 이 위치는 불러올때 저장하는 거 아닌가?
String path3 = Environment.getExternalStorageDirectory() + "/" + workNum + "/" + pointNum + "/uploadfile";
#### 사진 선택 위치
String filePath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/" + work_num + "/" + c_point_num;
#### recyclerView에 올리는 압축된 이미지
/data/data/com.example.einere.myapplication/cache/images/yyyyMMdd_hhmmss.png

