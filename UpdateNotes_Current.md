# T4Framework : MMO Action RPG Framework for UE4
``` 
Powerful toolset and Flexible layer solution
``` 

- Release Notes (2020.03 ~ 2020.ING)
  - **[2020.03.30] [M6] Copying //Private to //Deploy (private commit bcbf303)**
    - #125 [버그수정] Entity Editor, Undo/Redo 가 정상적으로 동작하지 않던 문제 수정
	  - World Explorer, Content Editor 관련 문제도 점진적으로 해결 예정
    - #118 [기능개선] Content Editor, WorldDataID 변경시 재오픈을 통해 선택한 월드 반영 처리 추가
  - **[2020.03.29] [M6] Copying //Private to //Deploy (private commit 9a5d8c7)**
    - #123 [버그수정] Entity Editor, Zone Entity 의 Environment TimeTag 뷰포트 미반영 문제 수정
    - #124 [기능개선] World Explorer, LevelActor ListView 를 TreeView 로 변경해 사용성 개선
    - #123 [버그수정] World Explorer, TimeTag DropList 를 통한 Name 변경이 되지 않던 문제 수정
    - #123 [버그수정] World Explorer, SkyBP TimeTag 설정이 EditorWorld 에 적용도히지 않던 문제 수정
  - **[2020.03.28] [M6] Copying //Private to //Deploy (private commit a8ab451)**
    - #118 [기능개선] Content Editor, Spawn Object/Actor 의 EntityAsset Thumbnail 표시 추가
	- #126 [기능개선] Entity Editor, Prop/DropItem 에 대한 ReceivedDecals 옵션 적용 추가
	- #40 [기능개선] Shoulder Control Mode 에서 마우스 우클릭 회전시 커서가 보이도록 수정
	- #121 [버그수정] FPS Control Mode 의 조준경 사용시 줌인 거리내 충돌 지점이 무시되던 문제 수정
	- #126 [기능개선] Content Editor, SpawnActor Nameplate 를 BoundHeight 를 사용하도록 개선
    - #122 [버그수정] Content Editor, DataTable Stat/Experience 의 TreeView Colume 미출력 문제 수정
  - **[2020.03.27] [M6] Copying //Private to //Deploy (private commit c7f0f99)**
    - #126 [기능개선] 기본 카메라의 Yaw 앵글을 캐릭터 뒤에 위치하도록 수정 (Entity, Action Editor 제외)
    - #126 [기능추가] FieldObject (Prop Entity) 에 대한 Projectile 동작 처리 추가
	- #126 [기능개선] Content Editor, FieldObject (Prop Entity) 편집시는 별도의 Anchor 출력 처리
	- #126 [기능추가] Content Editor, Spawn Asset 에 테스트용 Player 정보 설정 및 스폰 기능 추가
    - #126 [기능개선] Content Editor, Spawn Asset 을 오픈 시 SpawnLayer 자동 선택 처리 추가
    - #126 [기능개선] Content Editor, Prop Entity 를 사용한 FieldObject 사용 처리 추가
    - #126 [기능개선] Content Editor, TreeView 의 Folder 에서 AddItem 을 통한 ChildItem 처리 추가
  - **[2020.03.25] [M6] Copying //Private to //Deploy (private commit d6ee84d)**
    - #126 [기능추가] Entity Editor, Prop Entity 설정 처리 추가 (Static/Skeletal Mesh or Particle)
  - **[2020.03.24] [M6] Copying //Private to //Deploy (private commit a2c2289)**
    - #125 [버그수정] Rehearsal Editor, 일부 기능에서 Undo/Redo 가 동작하지 않던 문제 수정
    - #124 [기능개선] World Explorer, Details 메뉴 정리 및 사용성 개선
  - **[2020.03.23] [M6] Copying //Private to //Deploy (private commit c638a3a)**
    - #124 [기능개선] Actor Editor, Details 메뉴 정리 및 사용성 개선
    - #124 [기능개선] Entity Editor, Entity Details 메뉴 정리 및 사용성 개선
  - **[2020.03.20] [M6] Copying //Private to //Deploy (private commit 0acf35a)**
    - #124 [기능개선] Entity Editor, Entity Details 의 Property Category 를 Tab 으로 분리
  - **[2020.03.19] [M6] Copying //Private to //Deploy (private commit ca442f2)**
    - #124 [기능개선] Entity Editor, AnimSet Details 메뉴 정리 및 사용성 개선
