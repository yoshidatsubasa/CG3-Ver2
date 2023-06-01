#include "Light.h"
#include <cassert>

using namespace DirectX;

//静的メンバ変数の実態
ID3D12Device* Light::device = nullptr;

void Light::StaticInitialize(ID3D12Device* device)
{
	//再初期化チェック
	assert(!Light::device);
	//nullptrチェック
	assert(device);
	//静的メンバ変数のセット
	Light::device = device;
}

Light* Light::Create()
{
	//3Dオブジェクトのインスタンスを生成
	Light* instance = new Light();
	//初期化
	instance->Initialize();
	//生成したインスタンスを返す
	return instance;
}

void Light::Initialize()
{

	HRESULT result;

	D3D12_HEAP_PROPERTIES cbHeapProp{};		//ヒープ設定
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD; //GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC cbResourseDesc{};
	cbResourseDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourseDesc.Width = (sizeof(ConstBufferData) + 0xff) & ~0xff;//256バイトアラインメント
	cbResourseDesc.Height = 1;
	cbResourseDesc.DepthOrArraySize = 1;
	cbResourseDesc.MipLevels = 1;
	cbResourseDesc.SampleDesc.Count = 1;
	cbResourseDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//定数バッファの生成
	result = device->CreateCommittedResource(
		&cbHeapProp,//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourseDesc, //リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));

	//定数バッファへデータ転送
	TransferConstBuffer();
}

void Light::Update()
{
	//値の更新があった時だけ定数バッファに転送する
	if (dirty)
	{
		TransferConstBuffer();
		dirty = false;
	}
}

void Light::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff->GetGPUVirtualAddress());
}

void Light::TransferConstBuffer()
{
	HRESULT result;
	//定数バッファへデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		constMap->lightV = -lightDir;
		constMap->lightColor = lightColor;
		constBuff->Unmap(0, nullptr);
	}

}

void Light::SetLightDir(const XMVECTOR& lightdir)
{
	//正規化してセット
	this->lightDir = XMVector3Normalize(lightDir);
	dirty = true;
}

void Light::SetLightColor(const XMFLOAT3& lightcolor)
{
	//正規化してセット
	this->lightColor = lightcolor;
	dirty = true;
}
