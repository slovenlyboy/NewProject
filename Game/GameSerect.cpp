//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameSerect.cpp
//!
//! @brief  ステージセレクトシーンのソースファイル
//!
//! @date   2017/4/7	
//!
//! @author Yuga Yamamoto	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "GameSerect.h"


using namespace DirectX::SimpleMath;
using namespace DirectX;

GameSerect::GameSerect()
{
	m_cnt = 0;

	serectCheck = false;
	serectMap = 0;

	//2つの画像の座標の設定
	SerectForestPos = Vector2{ 10,10 };
	SerectTowerPos = Vector2{ 94,10 };

	//２つの画像のサイズの設定
	forestRect = { 0,0,64,64 };
	towerRect = { 0,0,64,64 };
}

GameSerect::~GameSerect()
{

}

void GameSerect::Update()
{
	//ステージを決定していないとき
	if (serectCheck == true)
	{
		if (m_cnt == 120)
		{
			g_NextScene = PLAY;
		}

		m_cnt++;
	}
	else
	{
		//マウスとステージセレクト（森）が当たってたら
		//if (CheckVecMouse(SerectForestPos, forestRect, g_mouse) == true)
		//	左キーが押されたら
		if (g_keyTracker->pressed.Left)
		{
			forestCheck = true;
			towerCheck = false;
		}

		//マウスとステージセレクト（塔）が当たったら
		//if (CheckVecMouse(SerectTowerPos, towerRect, g_mouse) == true)
		//	右キーが押されたら
		if (g_keyTracker->pressed.Right)
		{
			towerCheck = true;
			forestCheck = false;
		}

		//左クリックをしてる時
		//if (g_mouse.leftButton)
		//	スペースキーが押されたら
		if (g_keyTracker->pressed.Space)
		{
			//マウスとステージセレクト（塔）が当たったら
			if (towerCheck == true)
			{
				serectMap = 1;
				//プレイシーンへ移動
				serectCheck = true;
			}
			//マウスとステージセレクト（森）が当たってたら
			else if (forestCheck == true)
			{
				serectMap = 2;
				//プレイシーンへ移動
				serectCheck = true;
			}
		}
	}
	
}

void GameSerect::Render()
{
	RECT rect = { 0,0,320,480 };

	//wchar_t buf[256];	// 文字列編集用						
	//wchar_t buf2[256];	// 文字列編集用
	//wchar_t buf3[256];	// 文字列編集用

	//森選択の描画
		g_spriteBatch->Draw(g_ForestStageImage->m_pTexture, Vector2(0,0),
			&rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

	//塔選択の描画
		g_spriteBatch->Draw(g_TowerStageImage->m_pTexture, Vector2(320, 0),
			&rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

		if (forestCheck == true)
		{
			if (serectCheck == false || ((m_cnt / 10) % 2 == 0))
			{
				g_spriteBatch->Draw(g_StageSerect->m_pTexture, Vector2(0, 0),
					&rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));
			}

		}
		else
		{
			if (serectCheck == false || ((m_cnt / 10) % 2 == 0))
			{
				g_spriteBatch->Draw(g_StageSerect->m_pTexture, Vector2(320, 0),
					&rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));
			}
		}


	/*swprintf_s(buf, 16, L"X ,%d", serectMap);*/
	/*swprintf_s(buf2, 16, L"Y ,%d", (int)player->GetPosY());
	swprintf_s(buf3, 16, L"T ,%d", cnt);*/

	/*g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(0, 0));*/
	/*g_spriteFont->DrawString(g_spriteBatch.get(), buf2, Vector2(0, 16));
	g_spriteFont->DrawString(g_spriteBatch.get(), buf3, Vector2(0, 32));*/

}
//
//bool GameSerect::CheckVecMouse(DirectX::SimpleMath::Vector2 pos, RECT rect, DirectX::Mouse::State mouse)
//{
//	if ((mouse.x > pos.x && mouse.x < pos.x + rect.right) &&
//		(mouse.y > pos.y && mouse.y < pos.y + rect.bottom))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
