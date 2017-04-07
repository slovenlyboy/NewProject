//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ���C���̃\�[�X�t�@�C��
//!
//! @date   2017/4/5	
//!
//! @author Yuhei.M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#define _GAMEMAIN_
#include "GameMain.h"

#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
//#include "..\ADX2Le.h"
//#include "..\CueSheet_0.h"
#include"GameClear.h"
#include"GameLogo.h"
#include"GameOver.h"
#include"GamePlay.h"
#include"GameTitle.h"
#include"GameSerect.h"

#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;



// �v���g�^�C�v�錾 ====================================================
void importData(string filename);


// �O���[�o���ϐ��̒�` ====================================================
GameLogo logo;
GameTitle title;
GamePlay play;
GameClear clear;
GameOver over;
GameBase* base;

// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeGame(void)
{
	base = new GameLogo();
	

	// �摜�̓ǂݍ��� 
	g_StageImage = new Texture(L"Resources\\Images\\StageImage.png");//�X�e�[�W�摜
	g_BlackImage = new Texture(L"Resources\\Images\\black.png");//�t�F�[�h�p���摜
	g_BackImage = new Texture(L"Resources\\Images\\back.png");//�w�i�摜
	g_PlayerImage = new Texture(L"Resources\\Images\\player.png");//�v���C���[�摜
	g_TitleImage = new Texture(L"Resources\\Images\\title.png");//�^�C�g���摜
	g_ClearImage = new Texture(L"Resources\\Images\\CLEAR.png");//�N���A�摜
	g_LogoImage = new Texture(L"Resources\\Images\\logo.png");//���S�摜
	g_OverImage = new Texture(L"Resources\\Images\\OVER.png");//�N���A�摜

	g_SerectForestImage = new Texture(L"Resources\\Images\\Serect_Forest.png");
	g_SerectTowerImage = new Texture(L"Resources\\Images\\Serect_Tower.png");

	g_ForestStageImage = new Texture(L"Resources\\Images\\ForestStage.png");
	g_TowerStageImage = new Texture(L"Resources\\Images\\TowerStage.png");

	// ���̓ǂݍ���
	
	

	

	g_NextScene = g_scene;//�V�[���J��
	g_init = 0;
}



//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateGame(void)
{
	// �V�[���Ǘ�
	if (g_scene != g_NextScene)
	{
		g_scene = g_NextScene;
		// �V�[���폜
		delete base;
		 // �V�[������
		switch (g_scene)
		{
		case LOGO:
			base = new GameLogo();
			break;
		case TITLE:
			base = new GameTitle();
			break;
		case SERECT:
			base = new GameSerect();
			break;
		case PLAY:
			base = new GamePlay();
			break;
		case CLEAR:
			base = new GameClear();
			break;
		case OVER:
			base = new GameOver();
			break;
		}
		g_init = 0;
	}


	base->Update();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderGame(void)
{	
	wchar_t buf[256];

	base->Render();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	/*ADX2Le::Finalize();*/
}


//----------------------------------------------------------------------
//! @brief ���l�`�揈��
//!
//! @param[in] xy���W�C���lw
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawNum(int x, int y, int n)
{
	int w = n;		// �v�Z�p
	int i = 0;		// ������

	if (w == 0)
	{
	}
	else
	{
		while (w)
		{
			w = w / 10;
			i++;
		}
	}

}


//test1