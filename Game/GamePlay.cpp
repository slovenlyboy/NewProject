//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.cpp
//!
//! @brief  �v���C�V�[���̃\�[�X�t�@�C��
//!
//! @date   2017/4/5	
//!
//! @author Yuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GamePlay.h"
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
//#include "..ADX2Le.h"
//#include "..\CueSheet_0.h"


using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;

void Initialize();
void Update();


//	�R���X�g���N�^
GamePlay::GamePlay()
{
	//�v���C���[�쐬
	player = new Player;
	
	// �}�b�v�̐ݒ�

	importData("map.csv");//�}�b�v�f�[�^�̓ǂݍ���
	// �}�b�v�̐ݒ�
	for (int i = 0; i < MAX_TIP; i++)
	{
		
		if (g_map[i / 20][i % 20] == 0)//�󔒎w��}�b�v�`�b�v
		{
			g_tip[i].state = 0;
		}
		else
		{
			g_tip[i].grp_x = CHIP_SIZE * g_map[i / 20][i % 20];
			g_tip[i].grp_y = 0;
			g_tip[i].grp_w = CHIP_SIZE;
			g_tip[i].grp_h = CHIP_SIZE;
			g_tip[i].pos_x = (i % 20) * g_tip[i].grp_w;
			g_tip[i].pos_y = (i / 20) * g_tip[i].grp_h;
			g_tip[i].spd_x = 0.0f;
			g_tip[i].spd_y = 0.0f;
			g_tip[i].state = 1;
		}
	}


}


//�X�V
void GamePlay::Update()
{

	////////////////////  �X�V����  //////////////////
	player->UpData();
	////////////////////  �L�[����  //////////////////	


	//���Ƃ̔���
	Collisionfloor(player);

	// �}�E�X�N���b�N��
	if (g_mouse.leftButton)
	{
		SetSpeadToAsaaignedPosition(player, 200.0f, 200.0f, 3.0f);//�w��ʒu�Ɉړ��֐��e�X�g
	}

	mouseState = g_mouse.leftButton;
	
}



//�`��
void GamePlay::Render()
{
	//�}�E�X�J�[�\���B��
	ShowCursor(FALSE);

	RECT rect;			// �G�̍���̍��W�ƉE���̍��W�ҏW�p
						wchar_t buf[256];	// ������ҏW�p
						wchar_t buf2[256];	// ������ҏW�p

	rect = { 0, 0,640,480 };
	g_spriteBatch->Draw(g_BackImage->m_pTexture,
		Vector2(0, 0));

	//�X�e�[�W�`��
	for (int i = 0; i < MAX_TIP; i++)
	{
		//�}�b�v�`�b�v���̐ݒ�
		/*if (g_map[i / 20][i % 20] == 1)
		{
		
		}*/

		if (g_tip[i].state)
		{
			rect = { g_tip[i].grp_x, g_tip[i].grp_y,
				g_tip[i].grp_x + g_tip[i].grp_w,
				g_tip[i].grp_y + g_tip[i].grp_h };


			g_spriteBatch->Draw(g_StageImage->m_pTexture,
				Vector2(g_tip[i].pos_x, g_tip[i].pos_y),
				&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);
		}
	}



	//	 �v���C���[
	player->Render();

	//�f�o�b�O�p����
	/*swprintf_s(buf, 16, L"", );
	swprintf_s(buf2, 32, L"", );
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(0, 0));
	g_spriteFont->DrawString(g_spriteBatch.get(), buf2, Vector2(0, 32));*/
	
}

//�}�b�v�̓ǂݍ���
void GamePlay::importData(string filename)
{
	ifstream ifs(filename);
	string str;
	int i;

	if (!ifs) {
		for (i = 0; i < MAX_TIP; i++)
		{
			g_map[i / 20][i % 20] = 0;
		}
		return;
	}

	i = 0;
	while (getline(ifs, str)) {
		string token;
		istringstream stream(str);

		// 1�s�̂����A������ƃR���}�𕪊�����
		while (getline(stream, token, ',')) {
			// ���ׂĕ�����Ƃ��ēǂݍ��܂�邽��
			// ���l�͕ϊ����K�v
			g_map[i / 20][i % 20] = atoi(token.c_str());
			i++;
		}
	}
}

//���A�V��̔���
void  GamePlay::Collisionfloor(ObjectBase* obj)
{
	//�v���C���[�̍��E���W�����߂�
	float left = obj->GetPosX() + 0.01f;
	float right = obj->GetPosX() + (obj->GetGrpW() - 0.01f);

	// �v���C���[�̑����̍��W�����߂�
	float bottom = obj->GetPosY() + (obj->GetGrpH() + 0.01f);
	//�v���C���[�̓��̔���
	float head = obj->GetPosY();
	//�v���C���[�̓��̔���
	float body = obj->GetPosY() + (obj->GetGrpH() / 2);
	// �}�b�v�̔z��̈ʒu�@
	int map_x, map_y, map_y2;

	// �v���C���[�̍����̈ʒu
	map_x = (int)floor(left / CHIP_SIZE + 0.5f);
	map_y = (int)floor(bottom / CHIP_SIZE);


	// ���ǂ�������
	if (g_map[map_y][map_x] == 1 )
	{
		if (bottom > -map_y * CHIP_SIZE + obj->GetGrpH())
		{
			if (obj->GetJump() == TRUE)
			{
				// �v���C���[�̈ʒu�����̏�Ɉړ�������
				if (obj->GetState() == 1)
				{
					if (obj->GetGrpH() == 64)
					{
						obj->SetPosY((map_y - 1) * CHIP_SIZE - 32);
					}
					else
					{
						obj->SetPosY((map_y - 1) * CHIP_SIZE);
					}
				}
				else
				{
					obj->SetPosY((map_y - 1) * CHIP_SIZE - 32);
				}
			}
			// ���x��0�ɂ���
			obj->SetSpdY(0.0f);
			obj->SetJump(FALSE);
			obj->SetJumpPower(0);
			obj->SetState(1);
			
		}
	}
	else
	{
		//���������Ŗ�����Δ��ł���
		obj->SetJump(TRUE);
	}

	map_y = (int)floor(head / CHIP_SIZE);
	// �V�䂾������
	if (g_map[map_y][map_x] == 1  )
	{
		if (bottom > -map_y * CHIP_SIZE + obj->GetGrpH())
		{
			// ���Ƃ�
			obj->SetSpdY(10.0f);
		}
	}


	map_y = (int)floor(bottom / CHIP_SIZE);

	// �v���C���[�̉E���̈ʒu
	map_x = (int)floor(right / CHIP_SIZE);
	// ����������
	if (g_map[map_y][map_x] == 1)
	{
		if (bottom > -map_y * CHIP_SIZE + obj->GetGrpH())
		{
			if (obj->GetJump() == TRUE)
			{
				// �v���C���[�̈ʒu�����̏�Ɉړ�������
				if (obj->GetState())
				{
					if (obj->GetGrpH() == 64)
					{
						obj->SetPosY((map_y - 1) * CHIP_SIZE - 32);
					}
					else
					{
						obj->SetPosY((map_y - 1) * CHIP_SIZE);
					}
				}
			}
			// ���x��0�ɂ���
			obj->SetSpdY(0.0f);
			obj->SetJump(FALSE);
			obj->SetJumpPower(0);
			obj->SetState(1);
		}
	}
	else
	{
		//���������Ŗ�����Δ��ł���
		obj->SetJump(TRUE);
	}



	map_y = (int)floor(head / CHIP_SIZE);
	// �V�䂾������
	if (g_map[map_y][map_x] == 1)
	{
		if (bottom > -map_y * CHIP_SIZE + obj->GetGrpH())
		{
			// ���Ƃ�
			obj->SetSpdY(10.0f);
		}
	}
}


GamePlay::~GamePlay()
{
	//delete player;
}

void GamePlay::Initialize()
{
	
}




////////////////////////////////////////////////////////////////////////////////////
//�I�u�W�F�N�g�̌��ݒn�ƖړI�n�̍������߁A���x��{���������Đݒ肷��֐�
//�߂�l:�Ȃ�
//����:(OBJECT�^�I�u�W�F�N�g��,float�^ �ړI���WX,float�^ �ړI���WY,float�^�@���B�܂ł̎���(0.0�ŏu�ԓ��B)�j
////////////////////////////////////////////////////////////////////////////////////
void GamePlay::SetSpeadToAsaaignedPosition(ObjectBase* obj, float AposX, float AposY, float Time)
{
	//�ړI�|�C���g�Ƃ̍����L������ϐ�
	float disX = 0.0f;
	float disY = 0.0f;
	int moveFlag = 0;
	int moveCnt = 0;


	//�ϐ��ɃI�u�W�F�N�g�ƖړI�|�C���g�Ƃ̍�������
	disX = AposX - obj->GetPosX();
	disY = AposY - obj->GetPosY();

	//�I�u�W�F�N�g�̑��x�ݒ�
	//X����
	//�I�u�W�F�N�g�̃|�W�V�����ƖړI�|�C���g�ɍ����������ꍇ
	if (disX != 0.0f)
	{
		obj->SetSpdX(disX / Time / 60.0f);

	}
	else if (disX == 0.0f)
	{
		obj->SetSpdX(0.0f);
	}
	//�ړI�|�C���g���߂�����
	if ((obj->GetSpdX() > 0 && obj->GetPosX() >= AposX) || (obj->GetSpdX() < 0 && obj->GetPosX() <= AposX))
	{
		obj->SetSpdX(0);
		obj->SetPosX(AposX);
	}
	//Y����
	//�I�u�W�F�N�g�̃|�W�V�����ƖړI�|�C���g�ɍ����������ꍇ
	if (disY != 0.0f)
	{
		obj->SetSpdY(disY / Time / 60.0f);

	}
	else if (disY == 0.0f)
	{
		obj->SetSpdY(0.0f);
	}
	//�ړI�|�C���g���߂�����
	if ((obj->GetSpdY() > 0.0f && obj->GetPosY() >= AposY) || (obj->GetSpdY() < 0.0f && obj->GetPosY() <= AposY))
	{
		obj->SetSpdY(0.0f);
		obj->SetPosY(AposY);
	}
	//�I�u�W�F�N�g�������Ă���ꍇ�b�����J�E���g����
	if (obj->GetSpdY() != 0 || obj->GetSpdY() != 0)
	{
		moveFlag = 1;
	}
	if (moveFlag == 1)
	{
		moveCnt++;
		if (moveCnt / 60 == Time)
		{
			obj->SetPosX(AposX);
			obj->SetPosY(AposY);
		}
	}
	obj->SetPosX(obj->GetPosX() + obj->GetSpdX());
	obj->SetPosY(obj->GetPosY() + obj->GetSpdY());
}

