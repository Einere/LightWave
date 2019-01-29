KWU LightWave Meeting Log
=========================

About Team
-------------------------

- Team : Moomin Valley
- Leader : Hyung-jun Choi
- Member : Jeong-woo Kim, Jun-hyung Kim

# 18/12/21

## 역할 분담
socket transmission implement

- android client : CHJ, KJH
- windows MFC server : KJW

## 깃 설정
깃허브 리포지토리 생성
포크 및 클론

## 다음주 계획
각자 소켓 통신 구현하기

# 18/12/28

## 코드 리뷰
- 테스트용 클라이언트를 통해 에코 서버 리뷰 (KJW)
- 모바일 간 소켓 통신 리뷰 (CHJ)

## 다음주 계획
- 패킷 정의하기
- PC서버와 Mobile클라이언트 간 통신 구현하기

# 19/01/03

## Android 실행 흐름 정의 (CHJ, KJH)
1. 앱 실행
2. 서버 연결 액티비티 실행, 연결
3. 연결 성공시 세션 서비스 실행
4. 홈 화면 액티비티 실행
5. 작업 정보 취득 액티비티 실행, 서버로 request 요청, response 받아서 화면에 작업 정보 랜더링
6. 작업 시작 버튼 클릭시, 작업 정보 작성 액티비티 실행, 사용자가 작업 정보를 작성한 뒤 전송 버튼 클릭
7. 사용자의 작업 정보를 패킷에 담아서 서버로 전송
8. ...

## 서버 연결 정보 유지 (CHJ, KJH)
singleton패턴을 적용한 manager service 사용

## 코딩 스타일 가이드 정의 (CHJ, KJH)
명확하고 자세한 변수명과 메소드명.
카멜 케이스 사용.

## 서버와 클라이언트 간의 송수신 확인 (KJW, KJH)

## 다음주 계획
- 패킷 정의
- server UI update
- client 개발 시작

# 19/01/10

## 중복 binding으로 인한 에러 (KJH, CHJ)
하나의 service에 여러 Activity가 binding될 수 없다.
따라서 다음과 같은 솔루션이 있다.

- [Application 사용][application]
- [Activity 전환시 unbind][unbind]
- 한 Activity에 service를 binding한 뒤, broadcast로 액티비티간 service 요청 및 응답.

[application]: URL "https://stackoverflow.com/questions/30648766/binding-a-service-to-multiple-activities"
[unbind]: URL "http://sterl.org/2016/06/android-bind-service-to-the-application-cross-activities/"

# 19/01/22

## GPS정보 취득, 지도 API 활용 (KJH)
GPS정보 취득 구현. 지도 API활용 방법 구현중. 현재 지도 API는 일정 건수 이상 요청이 발생하는 경우, 요금을 청구하는 방식을 사용 중. 회사와 협의를 해야 하는 상태.

## 앨범(갤러리)에서 사진 선택 후 전송 기능 (CHJ)
버튼을 클릭하여 앨범에서 사진 하나를 선택, serialize하여 json문자열에 포함시켜 전송하는 기능 구현.

## 각종 서버 기능 구현 (KJW)
여러가지 서버 기능 구현.

## 업체에 궁금한 사항들을 문의 (KJW, KJH, CHJ)
1. 작업정보에 대해 자세한 설명이 필요합니다. (필요한 데이터에 무엇이 있는지)
2. 소켓 통신 테스트용 광파기 데이터 파일이 필요합니다.
3. 서버에서 UI를 크게 할 필요가 있는지 궁금합니다. 현재 논의된 사항으로는 서버는 작업자들의 작업정보만 간단하게 조회하는 기능만이 필요한 것으로 예상됩니다.
4. 보안상 c++이 더 유리한 이유가 궁금합니다. 그렇다고 한다면 보안상 구현해야 될 부분을 가르쳐주세요.
6. 어느 지도api를, 어떻게 사용하는 것이 좋을까요? 결제는 어떻게 할것인지? (현재 대부분의 지도 api는 유료라고 합니다.)
7. 서버 로직을 웹서버처럼 요청&응답 구조로 구현해야 하나요? 아니면 서버에서 능동적으로 클라이언트에게 데이터를 전송할 필요가 있나요?
8. 서버에서 데이터 관리를 어떻게 하나요? DB를 사용해야 하나요? 아니면 단순히 파일로 저장하나요?
9. api 최소 버전 어디까지 지원? 기기 종류가 아닌, api넘버로 답변을 부탁드립니다..
10. 라이브러리에 대한 제한은 없는지? (ex. c++ 부스트 라이브러리)

## 다음주 계획

회사의 피드백에 따라 진행 방향 결정.

# 19/01/27

## 카메라, 갤러리, 방위 기능 구현 (CHJ)
버튼 클릭시 카메라 앱을 연 뒤, 촬영한 사진을 가져오는 기능 구현.
버튼 클릭시 갤러리에서 사진을 선택하여 가져오는 기능 구현.
모바일의 현재 방위(azimuth)값을 가져오는 기능 구현.

## 리팩토링, 접속자 수 실시간 집계 (KJW)

## 중간보고서 작성 (KJW, KJH, CHJ)
중간보고서 작성

## 다음주 계획
요구사항 2-4 ~ 2-6 수행 (KJH, CHJ)
2차 미팅 질문 정리 (KJW, KJH, CHJ)
스크롤 뷰 구현 (CHJ)
테스트용 공기계에서 카메라를 통해 사진 촬영 후 가져오기 실패 이유 분석 (KJH, CHJ)
사진 촬영 시 방위 값 가져올 방법 검색 (KJH, CHJ)
