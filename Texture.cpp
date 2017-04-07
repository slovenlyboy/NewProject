//--------------------------------------------------------------------------------------
// File: Texture.cpp
//
// �e�N�X�`���N���X
//
// Date: 2015.9.2
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include <WICTextureLoader.h>
#include "Texture.h"
#include "Direct3D.h"

// �R���X�g���N�^
Texture::Texture(wchar_t* fname)
{
	// �e�N�X�`���쐬
	DirectX::CreateWICTextureFromFile(g_pd3dDevice.Get(), fname, nullptr, &m_pTexture);
}

// �f�X�g���N�^
Texture::~Texture()
{
	// �e�N�X�`���̉��
	m_pTexture->Release();
}
