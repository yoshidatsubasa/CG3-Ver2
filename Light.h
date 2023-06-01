#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

class Light
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMVECTOR lightV;		//���C�g�ւ̕�����\���x�N�g��
		XMFLOAT3 lightColor;	//���C�g�̐F
	};

public://�ÓI�����o�֐�
	//�ÓI������
	static void StaticInitialize(ID3D12Device* device);

	//�C���X�^���X����
	static Light* Create();

private://�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;

private://�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//���C�g��������(�P�ʃx�N�g��)
	XMVECTOR lightDir = { 1.0f,0.0f,0.0f,0.0f };
	//���C�g�F
	XMFLOAT3 lightColor = { 1.0f,1.0f,1.0f };
	//�_�[�e�B�t���O
	bool dirty = false;

public://�����o�֐�
	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	//�萔�o�b�t�@�]��
	void TransferConstBuffer();

	//���C�g�����̃Z�b�g
	void SetLightDir(const XMVECTOR& lightdir);

	//���C�g�F�̃Z�b�g
	void SetLightColor(const XMFLOAT3& lightcolor);
};