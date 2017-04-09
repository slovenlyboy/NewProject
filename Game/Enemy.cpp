//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Enemy.cpp
//!
//! @brief  敵関連のソースファイル
//!
//! @date   2017/4/5
//!
//! @author Yuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#include"GameMain.h"
#include "Enemy.h"
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
//#include "..ADX2Le.h"
//#include "..\CueSheet_0.h"


using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;


Enemy::Enemy()
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


Enemy::~Enemy()
{
}


void Enemy::SetHandle(Texture* h)
{
	handle = h;

}

Texture* Enemy::GetHandle()
{
	return handle;

}


void Enemy::SetPosX(float x)
{
	pos_x = x;
}

float Enemy::GetPosX()
{
	return pos_x;
}
void Enemy::SetPosY(float y)
{
	pos_y = y;

}
float Enemy::GetPosY()
{
	return pos_y;
}


void Enemy::SetGrpX(int x)
{
	grp_x = x;
}
int Enemy::GetGrpX()
{
	return grp_x;
}


void Enemy::SetGrpY(int y)
{
	grp_y = y;
}
int Enemy::GetGrpY()
{
	return grp_y;
}


void Enemy::SetGrpW(int w)
{
	grp_w = w;

}
int Enemy::GetGrpW()
{

	return grp_w;
}

void Enemy::SetGrpH(int h)
{
	grp_h = h;
}
int Enemy::GetGrpH()
{
	return grp_h;
}


void Enemy::SetSpdX(float x)
{
	spd_x = x;
}
float Enemy::GetSpdX()
{
	return spd_x;
}

void Enemy::SetSpdY(float y)
{
	spd_y = y;
}
float Enemy::GetSpdY()
{
	return spd_y;
}

void Enemy::SetState(int s)
{
	state = s;
}
int Enemy::GetState()
{

	return state;
}


void  Enemy::SetJumpPower(float y)
{
	jumpPower = y;
}
float  Enemy::GetJumpPower()
{
	return jumpPower;
}


void  Enemy::SetJump(int s)
{
	jump = s;
}
int  Enemy::GetJump()
{
	return jump;
}

void Enemy::SetClimb(int s)
{
	climb = s;
}
int Enemy::GetClimb()
{
	return climb;
}

void Enemy::SetHold(int s)
{
	hold = s;
}
int Enemy::GetHold()
{

	return hold;
}



void Enemy::SetDir(int s)
{
	dir = s;
}
int Enemy::GetDir()
{
	return dir;
}




void Enemy::UpData()
{
	Control();

	if (GetSpdX() != 0 || GetSpdY() != 0)
	{
		m_cnt++;
	}
	else
	{
		m_cnt = 0;
	}

}

void Enemy::Render()
{
	RECT rect;			// 絵の左上の座標と右下の座標編集用


	//方向検出
	switch (GetDir())
	{
	case LEFT:
		SetGrpY(32);
		break;
	case RIGHT:
		SetGrpY(64);
		break;
	}



	//左右に移動している場合
	if (GetSpdX() != 0)
	{
		//移動してる場合歩く
		switch (m_cnt / 15 % 4)
		{
		case 0:
			SetGrpX(0);
			break;
		case 1:
		case 3:
			SetGrpX(32);
			break;
		case 2:
			SetGrpX(64);
			break;
		}
	}

	//上下に動いているなら（ジャンプを除く）
	if (GetClimb() == TRUE)
	{
		SetGrpY(96);

		//移動してる場合歩く
		switch (m_cnt / 15 % 4)
		{
		case 0:
			SetGrpX(0);
			break;
		case 1:
		case 3:
			SetGrpX(32);
			break;
		case 2:
			SetGrpX(64);
			break;
		}
	}

	if (GetState() == 1)
	{
		rect =
		{
			GetGrpX(),
			GetGrpY(),
			GetGrpX() + GetGrpW() ,
			GetGrpY() + GetGrpH()
		};


		float sx = GetPosX() - g_ScrollMap_x;
		float sy = GetPosY() - g_ScrollMap_y;


		g_spriteBatch->Draw(g_PlayerImage->m_pTexture,
			Vector2(sx, sy),
			&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);

	}

			

		
	

}

//プレイヤー操作
void Enemy::Control(void)
{
	float spd = 2.0f;
	float jumpPower = -12.0f;
	
		//座標変更処理/////////////////////////////
		SetPosX(GetPosX() + GetSpdX());
		SetPosY(GetPosY() + GetSpdY() + GetJumpPower());



		//移動してない場合両手をもとに戻す
		if (GetSpdX() == 0)
		{
			SetGrpX(32);
		}



		//状態による変更
		switch (GetState())
		{
		case 1:
			break;
		default:
			break;

		}
}
