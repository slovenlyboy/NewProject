//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   player.cpp
//!
//! @brief  �v���C���[�֘A�̃\�[�X�t�@�C��
//!
//! @date   2017/4/5
//!
//! @author Yuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include "Player.h"
#include"GameMain.h"
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
//#include "..ADX2Le.h"
//#include "..\CueSheet_0.h"


using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;



Player::Player()
{
	SetHandle(g_PlayerImage);
	SetGrpX(0);
	SetGrpY(0);
	SetGrpW(32);
	SetGrpH(32);
	SetPosX(32);
	SetPosY(32);
	SetSpdX(0.0f);
	SetSpdY(0.0f);
	SetState(1);
	SetJump(FALSE);
}


Player::~Player()
{
}


void Player::SetHandle(Texture* h)
{
	handle = h;

}

Texture* Player::GetHandle()
{
	return handle;

}


void Player::SetPosX(float x)
{
	pos_x = x;
}

float Player::GetPosX()
{
	return pos_x;
}
void Player::SetPosY(float y)
{
	pos_y = y;

}
float Player::GetPosY()
{
	return pos_y;
}


void Player::SetGrpX(int x)
{
	grp_x = x;
}
int Player::GetGrpX()
{
	return grp_x;
}


void Player::SetGrpY(int y)
{
	grp_y = y;
}
int Player::GetGrpY()
{
	return grp_y;
}


void Player::SetGrpW(int w)
{
	grp_w = w;

}
int Player::GetGrpW()
{

	return grp_w;
}

void Player::SetGrpH(int h)
{
	grp_h = h;
}
int Player::GetGrpH()
{
	return grp_h;
}


void Player::SetSpdX(float x)
{
	spd_x = x;
}
float Player::GetSpdX()
{
	return spd_x;
}

void Player::SetSpdY(float y)
{
	spd_y = y;
}
float Player::GetSpdY()
{
	return spd_y;
}

void Player::SetState(int s)
{
	state = s;
}
int Player::GetState()
{

	return state;
}


void  Player::SetJumpPower(float y)
{
	jumpPower = y;
}
float  Player::GetJumpPower()
{
	return jumpPower;
}


void  Player::SetJump(int s)
{
	jump = s;
}
int  Player::GetJump()
{
	return jump;
}






void Player::UpData()
{
	GetPosX();
	GetPosY();
	GetGrpX();
	GetGrpY();
	GetGrpW();
	GetGrpH();
	GetSpdX();
	GetSpdY();
	GetState();

	PlayerControl();

}

void Player::Render()
{
	RECT rect;			// �G�̍���̍��W�ƉE���̍��W�ҏW�p
	if (GetState() == 1)
	{
		rect = {GetGrpX(),GetGrpY(),GetGrpX() + GetGrpW() ,
			GetGrpY() + GetGrpH() };
	}
	
	float sx = GetPosX() - g_ScrollMap_x;
	float sy = GetPosY() - g_ScrollMap_y;
	

	g_spriteBatch->Draw(g_PlayerImage->m_pTexture,
		Vector2(sx, sy),
		&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);

}

//�v���C���[����
void Player::PlayerControl(void)
{
	float spd = 2.0f;
	float jumpPower = -16.0f;

	//���x���Z�b�g
	SetSpdX(0);
	if (GetJump() == TRUE)
	{
		SetSpdY(GetSpdY() + GRAVITY);
	}
	else
	{
		SetSpdY(0);
	}



	//�L�[����

	int index_x = (int)GetPosX() / CHIP_SIZE;//�}�b�v�ɑ΂���v���C���[��X���W
	
	int index_y = ((int)GetPosY() + (int)GetGrpH()) / CHIP_SIZE;//�}�b�v�ɑ΂���v���C���[��Y���W
	
	

	if (GetState() != 0)
	{
		if (g_key.Right)//�E�L�[����
		{
			int* mapdata = &g_map[index_y - 1][index_x + 1];//�v���C���[�̉E���̃}�b�v�`�b�v����

			if (*mapdata == 0 || *mapdata == 6)//�ړ��\�}�b�v�`�b�v
			{

			SetSpdX(spd);

				/*if (*mapdata == )//�S�[���̃`�b�v�ԍ��w��
				{
				g_NextScene = CLEAR;
				}*/
			}



		}
		else if (g_key.Left)//���L�[����
		{
			int* mapdata = &g_map[index_y - 1][index_x];//�v���C���[�̍��̃}�b�v�`�b�v����

			if (*mapdata == 0 || *mapdata == 6)
			{
				SetSpdX(-spd);
			}
		}

		//�X�y�[�X�L�[�ŃW�����v
		if (g_keyTracker->pressed.Space&&GetState() == 1 && GetJump() == FALSE)
		{
			SetJump(TRUE);
			SetJumpPower(jumpPower);
		}


		//�v���C���[�L�����̈ړ�
		//���W�ύX����/////////////////////////////
		SetPosX(GetPosX() + GetSpdX());
		SetPosY(GetPosY() + GetSpdY() + GetJumpPower());


		//��Ԃɂ��ύX
		switch (GetState())
		{
		case 1:
			break;
		default:
			break;

		}
	}
}
