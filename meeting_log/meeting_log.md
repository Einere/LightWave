KWU LightWave Meeting Log
=========================


## About Team
Team : Moomin Valley<br>
Leader : Hyung-jun Choi<br>
Member : Jeong-woo Kim, Jun-hyung Kim<br>
<br>
<br>
# 18/12/21
## 역할 분담
socket transmission implement
- android client : CHJ, KJH
- windows MFC server : KJW
## 깃 설정
깃허브 리포지토리 생성<br>
포크 및 클론<br>
## 다음주 계획
각자 소켓 통신 구현하기<br>
<br>
<br>
# 18/12/28
## 코드 리뷰
KJW : 테스트용 클라이언트를 통해 에코 서버 리뷰<br>
CHJ : 모바일 간 소켓 통신 리뷰<br>
## 다음주 계획
패킷 정의하기<br>
PC서버와 Mobile클라이언트 간 통신 구현하기<br>
<br>
<br>
# 19/01/03
## Android 실행 흐름 정의 (CHJ, KJH)
1. 앱 실행
2. 서버 연결 액티비티 실행, 연결
3. 연결 성공시 세션 서비스 실행
4. 홈 화면 액티비티 실행
5. 작업 정보 취득 액티비티 실행, 서버로 request 요청, response 받아서 화면에 작업 정보 랜더링
6. 작업 시작 버튼 클릭시, 작업 정보 작성 액티비티 실행, 사용자가 작업 정보를 작성한 뒤 전송 버튼 클릭
7. 사용자의 작업 정보를 패킷에 담아서 서버로 전송<br>
...

## 서버 연결 정보 유지 (CHJ, KJH)
singleton패턴을 적용한 manager service 사용 

## 코딩 스타일 정의명 (CHJ, KJH)
명확하고 자세한 변수명과 메소드명.
카멜 케이스 사용.

## 서버와 클라이언트 간의 송수신 확인 (KJW, KJH)

## 다음주 계획
패킷 정의<br>
server UI update<br>
client 개발 시작<br>

