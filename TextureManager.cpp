#include "TextureManager.h"
#include "DirectXBase.h"
#include<DirectXTex.h>

TextureManager::TextureManager() {
	//ディスクリプタヒープの生成
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;		//シェーダーから見える
	descHeapDesc.NumDescriptors = 512;									//SRV256個
	//ディスクリプタヒープの生成
	HRESULT result = DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&srvDescHeap));
}

int TextureManager::LoadTexture(LPCWSTR fileName) {
	//ファイルがロード済みかをチェック
	if (texture.size() > 0) {
		for (int i = 0; i < texture.size(); ++i) {
			//ロードしてあったら識別番号を返す
			if (texture.at(i).fileName == fileName) {
				return texture.at(i).IDNum;
			}
		}
	}

	//フルパスを分離して拡張子を取り出す
	wstring fileExt_;
	wstring fileName_;
	wstring directoryPath_;
	size_t pos1;
	std::wstring exceptExt;
	wstring fullPath = fileName;
	bool isComp = false;

	//区切り文字'.'が出てくる一番最後の部分を検索
	pos1 = fullPath.rfind('.');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos) {
		//区切り文字の後ろをファイル拡張子として保存
		fileExt_ = fullPath.substr(pos1 + 1, fullPath.size() - pos1 - 1);
		//区切り文字の前までを抜き出す
		exceptExt = fullPath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = fileName;
	}
	//区切り文字 '\\'が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('//');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos) {
		//区切り文字の後ろをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		isComp = true;
	}
	//区切り文字 '\'が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('/');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos&&!isComp) {
		//区切り文字の後ろをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		isComp = true;
	}
	//区切り文字がないのでファイル名のみとして扱う
	if (!isComp) {
		directoryPath_ = L"";
		fileName_ = exceptExt;
	}

	//ロードしていなかったらロードする
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage scratchImg;
	HRESULT result;

	if (fileExt_ == L"dds") {
		result = LoadFromDDSFile(
			fileName,
			DirectX::DDS_FLAGS_NONE,
			&metadata, scratchImg
		);
	}
	else {
		result = LoadFromWICFile(
			fileName,
			DirectX::WIC_FLAGS::WIC_FLAGS_NONE,
			&metadata, scratchImg
		);
	}
	const DirectX::Image* img = scratchImg.GetImage(0, 0, 0);

	//リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels);

	//テクスチャバッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff = nullptr;
	result = DirectXBase::Instance()->dev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texbuff));

	//データ転送
	//全ミップマップについて
	for (size_t i = 0; i < metadata.mipLevels; i++) {
		//ミップマップレベルを指定してイメージを取得
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		//テクスチャバッファにデータ転送
		result = texbuff->WriteToSubresource(
			(UINT)i,
			nullptr,							//全領域コピー
			img->pixels,						//元データの先頭アドレス
			(UINT)img->rowPitch,				//一ラインのサイズ
			(UINT)img->slicePitch				//いちまいのサイズ
		);
	}

	//テクスチャ配列の最後尾にロードしたテクスチャ情報を記録
	Texture proTexture{};
	proTexture.fileName = fileName;
	proTexture.IDNum = texture.size();
	proTexture.metadata = metadata;
	proTexture.scratchImg = &scratchImg;
	proTexture.texBuff = texbuff;
	texture.emplace_back(proTexture);
	descriptorHeadMgrIndex.emplace_back(-1);

	//ディスクリプタヒープのアドレスを取得
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		srvDescHeap->GetCPUDescriptorHandleForHeapStart(), texture.size() - 1, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	//シェーダーリソースビューの生成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	//ヒープにシェーダーリソースビュー生成
	DirectXBase::Instance()->dev->CreateShaderResourceView(
		texbuff.Get(),
		&srvDesc,
		basicHeapHandle
	);

	return texture.at(texture.size() - 1).IDNum;
}

int TextureManager::LoadTextureInDescriptorHeapMgr(LPCWSTR fileName)
{
	//ファイルがロード済みかをチェック
	if (texture.size() > 0) {
		for (int i = 0; i < texture.size(); ++i) {
			//ロードしてあったら識別番号を返す
			if (texture.at(i).fileName == fileName) {
				return descriptorHeadMgrIndex[i];
			}
		}
	}

	// テクスチャデータを保存
	Texture tex
	{};
	tex.fileName = fileName;

	//ロードしていなかったらロードする
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage scratchImg;
	HRESULT result = LoadFromWICFile(
		fileName,
		DirectX::WIC_FLAGS::WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	const DirectX::Image* img = scratchImg.GetImage(0, 0, 0);

	//リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels);

	//テクスチャバッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff = nullptr;
	result = DirectXBase::Instance()->dev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texbuff));

	//データ転送
	result = texbuff->WriteToSubresource(
		0,
		nullptr,							//全領域コピー
		img->pixels,						//元データの先頭アドレス
		(UINT)img->rowPitch,				//一ラインのサイズ
		(UINT)img->slicePitch				//いちまいのサイズ
	);

	//テクスチャ配列の最後尾にロードしたテクスチャ情報を記録
	tex.IDNum = texture.size();
	tex.metadata = metadata;
	tex.scratchImg = &scratchImg;
	tex.texBuff = texbuff;
	texture.emplace_back(tex);
	descriptorHeadMgrIndex.emplace_back(DescriptorHeapManager::Instance()->GetHead());

	//ディスクリプタヒープのアドレスを取得
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		DescriptorHeapManager::Instance()->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(), DescriptorHeapManager::Instance()->GetHead(), DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	//シェーダーリソースビューの生成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	//ヒープにシェーダーリソースビュー生成
	DirectXBase::Instance()->dev->CreateShaderResourceView(
		texbuff.Get(),
		&srvDesc,
		basicHeapHandle
	);

	// ディスクリプタヒープをインクリメント
	DescriptorHeapManager::Instance()->IncrementHead();

	return DescriptorHeapManager::Instance()->GetHead() - 1;
}

int TextureManager::CreateTexture(DirectX::XMFLOAT4 color)
{
	//同じ色のテクスチャがすでに生成済みかをチェックする
	for (int i = 0; i < texture.size(); ++i) {
		if (texture.at(i).fileName == L"selfTexture" && texture.at(i).colorData.x == color.x && texture.at(i).colorData.y == color.y &&
			texture.at(i).colorData.z == color.z && texture.at(i).colorData.w == color.w) {
			//すでに生成してあるテクスチャなのでSRVヒープの番号を返す
			return i;
		}
	}

	//画像データを作成する
	const int texWidth = 256;
	const int imageDataCount = texWidth * texWidth;
	//画像イメージデータ配列
	DirectX::XMFLOAT4* imageData = new DirectX::XMFLOAT4[imageDataCount];

	//全ピクセルの色を初期化
	for (int i = 0; i < imageDataCount; ++i) {
		imageData[i].x = color.x;
		imageData[i].y = color.y;
		imageData[i].z = color.z;
		imageData[i].w = color.w;
	}

	//リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		texWidth,
		(UINT)texWidth,
		(UINT16)1,
		(UINT16)1);

	//テクスチャバッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff = nullptr;
	HRESULT result = DirectXBase::Instance()->dev->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texbuff));

	//データ転送
	result = texbuff->WriteToSubresource(
		0,
		nullptr,							//全領域コピー
		imageData,							//元データの先頭アドレス
		sizeof(DirectX::XMFLOAT4) * texWidth,		//一ラインのサイズ
		sizeof(DirectX::XMFLOAT4) * imageDataCount	//いちまいのサイズ
	);

	//テクスチャ配列の最後尾にロードしたテクスチャ情報を記録
	Texture proTexture{};
	proTexture.fileName = L"selfTexture";
	proTexture.IDNum = texture.size();
	proTexture.metadata = {};
	proTexture.scratchImg = {};
	proTexture.texBuff = texbuff;
	proTexture.colorData = color;
	texture.push_back(proTexture);

	//ディスクリプタヒープのアドレスを取得
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		srvDescHeap->GetCPUDescriptorHandleForHeapStart(), texture.size() - 1, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	//シェーダーリソースビューの生成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	//ヒープにシェーダーリソースビュー生成
	DirectXBase::Instance()->dev->CreateShaderResourceView(
		texbuff.Get(),
		&srvDesc,
		basicHeapHandle
	);

	delete[] imageData;

	return texture.at(texture.size() - 1).IDNum;
}

int TextureManager::CreateRenderTargetTexture(int width, int height, int mipLevel, int arraySize, DXGI_FORMAT format, float clearColor[4])
{
	//画像データを作成する
	const int texWidth = width;
	const int texHeight = height;
	const int imageDataCount = texWidth * texHeight;
	//画像イメージデータ配列
	DirectX::XMFLOAT4* imageData = new DirectX::XMFLOAT4[imageDataCount];

	//全ピクセルの色を初期化
	for (int i = 0; i < imageDataCount; ++i) {
		imageData[i].x = 0;
		imageData[i].y = 0;
		imageData[i].z = 0;
		imageData[i].w = 0;
	}

	////リソース設定
	//CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
	//	DXGI_FORMAT_R32G32B32A32_FLOAT,
	//	texWidth,
	//	(UINT)texHeight,
	//	(UINT16)1,
	//	(UINT16)1);

	CD3DX12_RESOURCE_DESC desc(
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,
		0,
		static_cast<UINT>(width),
		static_cast<UINT>(height),
		arraySize,
		mipLevel,
		format,
		1,
		0,
		D3D12_TEXTURE_LAYOUT_UNKNOWN,
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	D3D12_CLEAR_VALUE clearValue;
	clearValue.Format = format;
	if (clearColor != nullptr) {
		clearValue.Color[0] = clearColor[0];
		clearValue.Color[1] = clearColor[1];
		clearValue.Color[2] = clearColor[2];
		clearValue.Color[3] = clearColor[3];
	}
	else {
		clearValue.Color[0] = 0.0f;
		clearValue.Color[1] = 0.0f;
		clearValue.Color[2] = 0.0f;
		clearValue.Color[3] = 1.0f;
	}

	//テクスチャバッファの生成
	auto prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff = nullptr;
	HRESULT result = DirectXBase::Instance()->dev->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_COMMON,
		&clearValue,
		IID_PPV_ARGS(&texbuff)
	);

	//データ転送
	//result = texbuff->WriteToSubresource(
	//	0,
	//	nullptr,							//全領域コピー
	//	imageData,							//元データの先頭アドレス
	//	sizeof(XMFLOAT4) * texWidth,		//一ラインのサイズ
	//	sizeof(XMFLOAT4) * imageDataCount	//いちまいのサイズ
	//);

	//テクスチャ配列の最後尾にロードしたテクスチャ情報を記録
	Texture proTexture{};
	proTexture.fileName = L"selfTexture";
	proTexture.IDNum = texture.size();
	proTexture.metadata = {};
	proTexture.scratchImg = {};
	proTexture.texBuff = texbuff;
	proTexture.colorData = {};
	texture.push_back(proTexture);

	//ディスクリプタヒープのアドレスを取得
	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		srvDescHeap->GetCPUDescriptorHandleForHeapStart(), texture.size() - 1, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	//シェーダーリソースビューの生成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = mipLevel;
	//ヒープにシェーダーリソースビュー生成
	DirectXBase::Instance()->dev->CreateShaderResourceView(
		texbuff.Get(),
		&srvDesc,
		basicHeapHandle
	);

	delete[] imageData;

	return texture.at(texture.size() - 1).IDNum;
}

D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetSRV(int IDNum) {
	D3D12_GPU_DESCRIPTOR_HANDLE basicHeapHandle = srvDescHeap->GetGPUDescriptorHandleForHeapStart();
	//消費した分だけアドレスをずらす
	for (int i = 0; i < IDNum; ++i) {
		basicHeapHandle.ptr += DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	}
	return basicHeapHandle;
}

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> TextureManager::GetDescHeap()
{
	return srvDescHeap;
}

Texture TextureManager::GetTexture(int ID)
{
	return texture.at(ID);
}
