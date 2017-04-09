//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameSerect.cpp
//!
//! @brief  �X�e�[�W�Z���N�g�V�[���̃\�[�X�t�@�C��
//!
//! @date   2017/4/7	
//!
//! @author Yuga Yamamoto	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GameSerect.h"


using namespace DirectX::SimpleMath;
using namespace DirectX;

GameSerect::GameSerect()
{
	m_cnt = 0;

	serectCheck = false;
	serectMap = 0;

	//2�̉摜�̍��W�̐ݒ�
	SerectForestPos = Vector2{ 10,10 };
	SerectTowerPos = Vector2{ 94,10 };

	//�Q�̉摜�̃T�C�Y�̐ݒ�
	forestRect = { 0,0,64,64 };
	towerRect = { 0,0,64,64 };
}

GameSerect::~GameSerect()
{

}

void GameSerect::Update()
{
	//�X�e�[�W�����肵�Ă��Ȃ��Ƃ�
	if (serectCheck == true)
	{
		m_cnt++;
		/*SerectForestPos.x += 8;
		SerectTowerPos.x += 8;*/

		if (m_cnt == 120)
		{
			g_NextScene = PLAY;
		}
	}
	else
	{
		//�}�E�X�ƃX�e�[�W�Z���N�g�i�X�j���������Ă���
		if (CheckVecMouse(SerectForestPos, forestRect, g_mouse) == true)
			forestCheck = true;
		else forestCheck = false;

		//�}�E�X�ƃX�e�[�W�Z���N�g�i���j������������
		if (CheckVecMouse(SerectTowerPos, towerRect, g_mouse) == true)
			towerCheck = true;
		else towerCheck = false;


		//���N���b�N�����Ă鎞
		if (g_mouse.leftButton)
		{

			//�}�E�X�ƃX�e�[�W�Z���N�g�i���j������������
			if (towerCheck == true)
			{
				serectMap = 1;
				//�v���C�V�[���ֈړ�
				serectCheck = true;
			}
			//�}�E�X�ƃX�e�[�W�Z���N�g�i�X�j���������Ă���
			else if (forestCheck == true)
			{
				serectMap = 2;
				//�v���C�V�[���ֈړ�
				serectCheck = true;
			}
		}
	}
	
}

void GameSerect::Render()
{
	RECT rect = { 0,0,320,480 };

	wchar_t buf[256];	// ������ҏW�p						
	wchar_t buf2[256];	// ������ҏW�p
	wchar_t buf3[256];	// ������ҏW�p

	//	�`�F�b�N�i�X�j�������Ă�Ƃ�
	if (forestCheck == true)
		g_spriteBatch->Draw(g_ForestStageImage->m_pTexture, Vector2(320 + (m_cnt * 4), 0),
			&rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

	//�`�F�b�N�i���j�������Ă�Ƃ�
	if (towerCheck == true)
		g_spriteBatch->Draw(g_TowerStageImage->m_pTexture, Vector2(320 + (m_cnt * 4), 0),
			&rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));


	//�X�e�[�W�Z���N�g�i�X�j�̕`��
	g_spriteBatch->Draw(g_SerectForestImage->m_pTexture, SerectForestPos,
		&forestRect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

	//�X�e�[�W�Z���N�g�i���j�̕`��
	g_spriteBatch->Draw(g_SerectTowerImage->m_pTexture, SerectTowerPos,
		&towerRect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));



	swprintf_s(buf, 16, L"X ,%d", serectMap);
	/*swprintf_s(buf2, 16, L"Y ,%d", (int)player->GetPosY());
	swprintf_s(buf3, 16, L"T ,%d", cnt);*/

	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(0, 0));
	/*g_spriteFont->DrawString(g_spriteBatch.get(), buf2, Vector2(0, 16));
	g_spriteFont->DrawString(g_spriteBatch.get(), buf3, Vector2(0, 32));*/

}

bool GameSerect::CheckVecMouse(DirectX::SimpleMath::Vector2 pos, RECT rect, DirectX::Mouse::State mouse)
{
	if ((mouse.x > pos.x && mouse.x < pos.x + rect.right) &&
		(mouse.y > pos.y && mouse.y < pos.y + rect.bottom))
	{
		return true;
	}
	else
	{
		return false;
	}
}
