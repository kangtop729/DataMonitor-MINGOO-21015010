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
│   ├── Model/
│   │   └── Item.h                      # id/name/quantity 최소 엔티티
│   ├── Serialization/
│   │   └── ItemSerialization.h/.cpp    # nlohmann/json ADL to_json/from_json
│   ├── Repository/
│   │   ├── IItemReader.h               # 읽기 전용 인터페이스 (FindAll만 존재)
│   │   └── JsonItemReader.h/.cpp       # JSON 파일을 매 호출마다 새로 읽는 로더
│   ├── View/
│   │   └── SummaryView.h/.cpp          # 전체 목록 + 총 건수/총 수량 요약 출력
│   ├── ThirdParty/nlohmann/json.hpp    # nlohmann/json single header
│   └── main.cpp                        # 새로고침(r)/종료(q) 조회 루프
├── test/                                # gmock 기반 단위 테스트 (Debug 빌드에 포함)
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

Release 앱은 실행 위치의 `items.json`을 읽어 목록/요약을 보여주고, `r`을 입력할 때마다 파일을
다시 읽어 최신 값을 반영한다(`q`로 종료). 이 도구는 읽기 전용이므로 `items.json`을 직접 쓰지
않는다 — 값을 바꿔보려면 다른 프로세스(예: DataPersistence PoC)나 텍스트 편집기로 파일을 수정한 뒤
`r`을 입력하면 된다.

## 테스트

- `JsonItemReaderTest` (4개): 파일 없을 때 빈 목록, 파일에서 로드, **파일이 갱신되면 재조회 결과가
  달라지는지(실시간 갱신의 핵심 전제)**, 파일 손상 시 예외
- `SummaryViewTest` (3개): 전체 목록 출력, 빈 목록 처리, 총 건수/총 수량 요약

모든 클래스는 Red(실패하는 테스트 작성) → Green(최소 구현) 순서로 TDD 사이클을 거쳐 구현했다.
