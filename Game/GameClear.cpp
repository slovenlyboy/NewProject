//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameClear.cpp
//!
//! @brief  クリアシーンのソースファイル
//!
//! @date   2017/4/5	
//!
//! @author Yuhei M		
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "GameClear.h"

#include "../ADX2Le.h"


using namespace DirectX::SimpleMath;
using namespace DirectX;


GameClear::GameClear()
{
	ADX2Le::Stop();
	m_fade = 0;
	m_cnt = 0;
	m_flag = 0;
	ADX2Le::Play(BGM_CLEAR);
}
void GameClear::Update()
{
	
	m_cnt++;

	// スペースキーが押されたら
	if (g_keyTracker->pressed.Space)
	{
		//タイトルへ行く
		g_NextScene = TITLE;

	}

	


	if (m_cnt >= 480)
	{
		m_flag = 1;
		
	}

	if (m_flag == 1)
	{
		m_fade += 0.01f;
	}

	if (m_cnt >= 600)
	{
		//タイトルへ行く
		g_NextScene = TITLE;
	}
}

void GameClear::Render()
{
	RECT rect;			// 絵の左上の座標と右下の座標編集用

	//クリア画像の描画
	rect = { 0, 0,640,480 };
	if (serectMap == 1)
	{
		g_spriteBatch->Draw(g_TowerClearImage->m_pTexture, Vector2(0, 0));
	}
	else if (serectMap == 2)
	{
		g_spriteBatch->Draw(g_ForestClearImage->m_pTexture, Vector2(0, 0));
	}
	
	g_spriteBatch->Draw(g_BlackImage->m_pTexture, Vector2(0, 0), Vector4(255, 255, 255, m_fade));

}

GameClear::~GameClear()
{
}
