# DataMonitor-MINGOO-21015010

JSON 파일로 저장된 데이터를 읽기 전용으로 실시간 조회하는 콘솔 모니터링 도구 PoC.

Main 프로젝트 [`SampleOrderSystem-MINGOO-21015010`](https://github.com/kangtop729/SampleOrderSystem-MINGOO-21015010)의
"모니터링" 메뉴 설계에 아이디어 차원에서 참고되는 산출물이다.

## 목적

- JSON 파일이 갱신되면 재조회 시 최신 값이 반영되는지 검증한다.
- 조회 전용 도구로서 어떤 write 연산도 수행하지 않는 구조를 실험한다.

## 구조

```
DataMonitor-MINGOO-21015010/
├── src/
│   ├── Model/                       # 최소 엔티티
│   ├── Repository/                  # 읽기 전용 JSON 로더
│   ├── View/                        # 콘솔 테이블/요약 출력 포맷터
│   ├── ThirdParty/nlohmann/json.hpp # nlohmann/json single header
│   └── main.cpp                     # 조회 루프
├── test/                            # gmock 기반 단위 테스트 (Debug 빌드에 포함)
├── CLAUDE.md
├── PLAN.md
└── README.md
```

자세한 구현 계획은 [`PLAN.md`](PLAN.md) 참고.

## 빌드 및 실행

```
# 테스트 빌드 및 실행 (Debug 빌드 = 테스트 실행)
msbuild DataMonitor-MINGOO-21015010.vcxproj /p:Configuration=Debug /p:Platform=x64
x64\Debug\DataMonitor-MINGOO-21015010.exe

# 조회 앱 빌드/실행
msbuild DataMonitor-MINGOO-21015010.vcxproj /p:Configuration=Release /p:Platform=x64
x64\Release\DataMonitor-MINGOO-21015010.exe
```

(구현 진행에 따라 테스트 구성/실행 결과 절 추가 예정)
