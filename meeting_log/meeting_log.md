KWU LightWave Meeting Log
=========================

About Team
-------------------------

- Team : Moomin Valley
- Leader : Hyung-jun Choi
- Member : Jeong-woo Kim, Jun-hyung Kim

18/12/21
-------------------------

## 역할 분담

socket transmission implement

- android client : CHJ, KJH
- windows MFC server : KJW

## 깃 설정

깃허브 리포지토리 생성
포크 및 클론

# 다음주 계획

각자 소켓 통신 구현하기

18/12/28
-------------------------

# 코드 리뷰

- 테스트용 클라이언트를 통해 에코 서버 리뷰 (KJW)
- 모바일 간 소켓 통신 리뷰 (CHJ)

# 다음주 계획

- 패킷 정의하기
- PC서버와 Mobile클라이언트 간 통신 구현하기

19/01/03
-------------------------

# Android 실행 흐름 정의 (CHJ, KJH)

1. 앱 실행
2. 서버 연결 액티비티 실행, 연결
3. 연결 성공시 세션 서비스 실행
4. 홈 화면 액티비티 실행
5. 작업 정보 취득 액티비티 실행, 서버로 request 요청, response 받아서 화면에 작업 정보 랜더링
6. 작업 시작 버튼 클릭시, 작업 정보 작성 액티비티 실행, 사용자가 작업 정보를 작성한 뒤 전송 버튼 클릭
7. 사용자의 작업 정보를 패킷에 담아서 서버로 전송
8. ...

# 서버 연결 정보 유지 (CHJ, KJH)

singleton패턴을 적용한 manager service 사용

# 코딩 스타일 정의명 (CHJ, KJH)

명확하고 자세한 변수명과 메소드명.
카멜 케이스 사용.

# 서버와 클라이언트 간의 송수신 확인 (KJW, KJH)

# 다음주 계획

- 패킷 정의
- server UI update
- client 개발 시작

19/01/10
-------------------------

# 중복 binding으로 인한 에러 (KJH, CHJ)

하나의 service에 여러 Activity가 binding될 수 없다.
따라서 다음과 같은 솔루션이 있다.

- [Application 사용][application]
- [Activity 전환시 unbind][unbind]
- 한 Activity에 service를 binding한 뒤, broadcast로 액티비티간 service 요청 및 응답.

[application]: URL "https://stackoverflow.com/questions/30648766/binding-a-service-to-multiple-activities"
[unbind]: URL "http://sterl.org/2016/06/android-bind-service-to-the-application-cross-activities/"
