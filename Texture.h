//--------------------------------------------------------------------------------------
// File: Texture.h
//
// �e�N�X�`���N���X
//
// Date: 2015.9.2
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <d3d11.h>

// �e�N�X�`���N���X
class Texture
{
public:
	// �e�N�X�`���n���h��
	ID3D11ShaderResourceView* m_pTexture;

	// �R���X�g���N�^
	Texture(wchar_t* fname);
	// �f�X�g���N�^
	~Texture();
};
