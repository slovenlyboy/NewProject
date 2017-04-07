//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameTitle.cpp
//!
//! @brief  �^�C�g���̃\�[�X�t�@�C��
//!
//! @date   2017/4/5	
//!
//! @author Yuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GameTitle.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;


//----------------------------------------------------------------------
//! @brief �^�C�g������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void GameTitle(void)
{
}

//----------------------------------------------------------------------
//! @brief �^�C�g���`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderTitle(void)
{
}
void GameTitle::Update()
{
	if (g_init == 0)
	{
		g_init = 1;

	}

	// �X�y�[�X�L�[�Ńv���C�ɑJ��
	if (g_keyTracker->pressed.Space)
	{
		g_NextScene = SERECT;

	}

}
void GameTitle::Render()
{
	RECT rect;			// �G�̍���̍��W�ƉE���̍��W�ҏW�p
	wchar_t buf[256];	// ������ҏW�p
	
	// �^�C�g���摜
	rect = { 0,0,640,480 };
	g_spriteBatch->Draw(g_TitleImage->m_pTexture, Vector2(0, 0));

	

}
GameTitle::GameTitle()
{
	
}

GameTitle::~GameTitle()
{
}