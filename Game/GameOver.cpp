//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameOver.cpp
//!
//! @brief  �Q�[���I�[�o�[�V�[���̃\�[�X�t�@�C��
//!
//! @date   2017/4/5	
//!
//! @author Yuhei M		
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GameOver.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;


GameOver::GameOver()
{
}

void GameOver::Update()
{
	if (g_init == 0)
	{
		g_init = 1;
	
	}

	// �X�y�[�X�L�[�Ń^�C�g���ɑJ��
	if (g_keyTracker->pressed.Space)
	{
		g_NextScene = TITLE;
	}
}

void GameOver::Render()
{
	RECT rect;			// �G�̍���̍��W�ƉE���̍��W�ҏW�p
	wchar_t buf[256];	//������ҏW�p


	rect = { 0, 0,640,480 };
	g_spriteBatch->Draw(g_OverImage->m_pTexture,
		Vector2(0, 0));
}

GameOver::~GameOver()
{
}
