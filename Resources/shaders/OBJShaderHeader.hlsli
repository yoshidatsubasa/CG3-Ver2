cbuffer cbuff0 : register(b0)
{
	matrix viewproj;		//ビュープロジェクション行列
	matrix world;			//ワールド座標
	float3 cameraPos;		//カメラ座標(ワールド座標)
};

cbuffer cbuff1 : register(b1)
{
	float3 m_ambient  : packoffset(c0); // アンビエント係数
	float3 m_diffuse  : packoffset(c1); // ディフューズ係数
	float3 m_specular : packoffset(c2); // スペキュラー係数
	float m_alpha : packoffset(c2.w);	// アルファ
}

cbuffer cbuff2 : register(b2)
{
	float3 lightv;		//ライトへの方向を表すベクトル
	float3 lightcolor;	//ライトの色(RGB)
};

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; // システム用頂点座標
	//float3 normal :NORMAL; // 法線ベクトル
	float4 color : COLOR;	//色
	float2 uv  :TEXCOORD; // uv値
};
