//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLogo.cpp
//!
//! @brief  ロゴシーンのソースファイル
//!
//! @date   2017/4/5	
//!
//! @authorYuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "GameLogo.h"

#include "..\ADX2Le.h"
#include "..\CueSheet_0.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;




//----------------------------------------------------------------------
//! @brief ロゴ描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
GameLogo::GameLogo()
	:m_cnt(0),m_fade(1)
{
}
void GameLogo::Update()
{

	m_cnt++;
	if (m_cnt <= 90)
	{
		m_fade -= 0.01f;
	}
	else
	{
		m_fade += 0.01f;
	}
	// ロゴ表示
	if (m_cnt > 180)
	{

		g_NextScene = TITLE;
	}
}
void GameLogo::Render()
{

	RECT rect;			// 絵の左上の座標と右下の座標編集用

	//ロゴ画像の表示
	rect = { 0, 0,640,480 };
	g_spriteBatch->Draw(g_BlackImage->m_pTexture,
		Vector2(0, 0));


	rect = { 0, 0,640,480 };
	g_spriteBatch->Draw(g_LogoImage->m_pTexture,
		Vector2(0, 0));
	
}
GameLogo::~GameLogo()
{
}