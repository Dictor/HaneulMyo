# HaneulMyo
인천하늘고등학교 Myo 기반 의수 프로젝트 Git 저장소입니다.
이 문서는 저장소에 대해 설명하는 문서입니다.

폴더별 설명
-------------
* excample : 제작 중 테스트에 사용할 수 있는 예제 파일
  + Lm : 리니어 엑츄에이터 테스트 예제
  + printFirmwareInfo : Myo 암밴드 정보 출력 예제, 기존의 예제에서 Serial을 Serial1로 변경
  + readPoseData : Myo 암밴드 정보 출력 예제, 기존의 예제에서 Serial을 Serial1로 변경
* library : 소스에 필요한 라이브러리, Arduino IDE에 추가하여 사용
  + SoftReset-master.zip : 소프트웨어 리셋 구현 라이브러리, zip 채로 IDE에서 추가하여 사용
  + MyoBridge : Myo 암밴드 라이브러리, 폴더채로 IDE에서 추가하여 사용
* source : 이 프로젝트의 메인 코드
  + CCLoader : CCLoader 사용시 아두이노에 다운로드 해야하는 소스
  + complete : 메인 프로그램 소스
* tools : 제작에 필요한 여러가지 도구들
  + CCLoader : CCLoader 사용시 PC에서 실행시켜야 하는 프로그램
  + SerialPortMon : 시리얼 터미널 
