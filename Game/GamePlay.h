//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.h
//!
//! @brief  �v���C�V�[���̃w�b�_�[�t�@�C��
//!
//! @date   2017/4/5
//!
//! @author Yuhei M	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
#include "GameBase.h"
#include "ObjectBase.h"
#include "../Game/Player.h"

#include <string>
class GamePlay :public GameBase
{
private:
	Player* player;//�v���C���[�|�C���^
	bool mouseState = 0;
	int m_timeCount = 0;	//	�J�E���g
	int cnt = 0;			//	����
public:
	GamePlay();
	void Initialize();//������
	void Update();//�X�V
	void Render();//�`��
	void importData(std::string f);//�}�b�v�ǂݍ���
	void Collisionfloor(ObjectBase* obj);//���Ƃ̔���
	void GamePlay::SetSpeadToAsaaignedPosition(ObjectBase* obj, float AposX, float AposY, float Time);//�w����W�ړ��֐�
	void GamePlay::ScrollMap(void);
	void Collisiontrup(ObjectBase * obj);
	//�}�b�v�X�N���[���ʌ��o
	~GamePlay();

};
