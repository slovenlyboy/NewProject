//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameTitle.h
//!
//! @brief  �^�C�g���V�[���̃w�b�_�[�t�@�C��
//!
//! @date   2017/4/5
//!
//! @author Yuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include "GameBase.h"
class GameTitle:public GameBase
{
private:
	int m_cnt;		// �J�E���^
public:
	GameTitle();
	void Update();
	void Render();
	~GameTitle();
};
