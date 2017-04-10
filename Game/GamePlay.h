//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.h
//!
//! @brief  プレイシーンのヘッダーファイル
//!
//! @date   2017/4/5
//!
//! @author Yuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include "GameBase.h"
#include "ObjectBase.h"
#include "../Game/Player.h"
#include "../Game/Gimmik.h"
#include "../Game/Enemy.h"
#include <string>
class GamePlay :public GameBase
{
private:
	Player* player;//プレイヤーポインタ
	Gimmik* lift;//リフトポインタ

	Enemy* enemy[15];//敵ポインタ

	float gimmikPosAX = 0;//ギミック可動範囲AX座標
	float gimmikPosAY = 0;//ギミック可動範囲AY座標

	float gimmikPosBX = 0;//ギミック可動範囲BX座標
	float gimmikPosBY = 0;//ギミック可動範囲BY座標

	int enemyCnt = 0;
	int enemyNum = 0;
	int gimmikFlag = 0;
	int gimmikCnt = 0;
	bool mouseState = 0;
	int m_timeCount = 0;	//	カウント
	int cnt = 0;			//	時間

	int soundFlag = 0;
	int soundSet = 0;
	int soundCnt = 0;

public:
	GamePlay();
	void Initialize();//初期化
	void Update();//更新
	void Render();//描画
	void importData(std::string f);//マップ読み込み
	void Collisionfloor(ObjectBase* obj);//床との判定
	void timeOver();//	制限時間
	void GamePlay::SetSpeadToAsaaignedPosition(ObjectBase* obj, float AposX, float AposY, float Time);//指定座標移動関数
	void GamePlay::ScrollMap(void);
	bool GamePlay::Collision(ObjectBase* obj1, ObjectBase*obj2);
	//マップスクロール量検出
	~GamePlay();

};
