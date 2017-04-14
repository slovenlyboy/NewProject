//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameOver.cpp
//!
//! @brief  ゲームオーバーシーンのソースファイル
//!
//! @date   2017/4/5	
//!
//! @author Yuhei M		
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "GameOver.h"

#include "..\ADX2Le.h"
#include "..\CueSheet_0.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;


GameOver::GameOver()
{
	ADX2Le::Stop();
	m_cnt = 0;
	m_fade = 0;
	m_flag = 0;
	ADX2Le::Play(BGM_OVER);
}

void GameOver::Update()
{
	// スペースキーでタイトルに遷移
	if (g_keyTracker->pressed.Space)
	{
		g_NextScene = TITLE;	
	}

	m_cnt++;
	
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

void GameOver::Render()
{
	RECT rect;			// 絵の左上の座標と右下の座標編集用
	wchar_t buf[256];	//文字列編集用


	rect = { 0, 0,640,480 };
	g_spriteBatch->Draw(g_OverImage->m_pTexture,
		Vector2(0, 0));

	//暗転用黒背景
	g_spriteBatch->Draw(g_BlackImage->m_pTexture, Vector2(0, 0), Vector4(255, 255, 255, m_fade));


}

GameOver::~GameOver()
{
}
