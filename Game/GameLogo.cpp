//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLogo.cpp
//!
//! @brief  ���S�V�[���̃\�[�X�t�@�C��
//!
//! @date   2017/4/5	
//!
//! @authorYuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GameLogo.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;




//----------------------------------------------------------------------
//! @brief ���S�`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
GameLogo::GameLogo()
	:m_cnt(0)
{
}
void GameLogo::Update()
{

	m_cnt++;
	
	// ���S�\��
	if (m_cnt > 180)
	{
		g_NextScene = TITLE;
	}
}
void GameLogo::Render()
{

	RECT rect;			// �G�̍���̍��W�ƉE���̍��W�ҏW�p

	//���S�摜�̕\��
	rect = { 0, 0,640,480 };
	g_spriteBatch->Draw(g_LogoImage->m_pTexture,
		Vector2(0, 0));
	
}
GameLogo::~GameLogo()
{
}