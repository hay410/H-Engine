//#include"ObjectManager.h"
//
//ObjectManager::ObjectManager() {};
//
//Object3D ObjectManager::InitBox(XMFLOAT3 pos, XMFLOAT3 size, int projectionID, LPCWSTR fileName)
//{
//	Object3D objectBuff;
//	objectBuff.projectionID = projectionID;
//
//	//設定構造体
//	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
//	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;			//シェーダーから見える
//	descHeapDesc.NumDescriptors = 2;										//CBV2つ
//	//ディスクリプタヒープの生成
//	HRESULT result = DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&objectBuff.constDescHeap));
//
//	//テクスチャをロード
//	objectBuff.textureIDnum = TextureManager::Instance()->LoadTexture(fileName);
//
//	//頂点バッファの生成
//#pragma region 頂点初期化
//	Vertex vertices;
//	//前
//	vertices.pos = XMFLOAT3(-size.x, -size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 0);
//	objectBuff.vertices.push_back(vertices);	//左下
//	vertices.pos = XMFLOAT3(-size.x, size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 1);
//	objectBuff.vertices.push_back(vertices);	//左上
//	vertices.pos = XMFLOAT3(size.x, -size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 0);
//	objectBuff.vertices.push_back(vertices);	//右下
//	vertices.pos = XMFLOAT3(size.x, size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 1);
//	objectBuff.vertices.push_back(vertices);	//右上
//	//後ろ
//	vertices.pos = XMFLOAT3(size.x, -size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 0);
//	objectBuff.vertices.push_back(vertices);	//左下
//	vertices.pos = XMFLOAT3(size.x, size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 1);
//	objectBuff.vertices.push_back(vertices);	//左上
//	vertices.pos = XMFLOAT3(-size.x, -size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 0);
//	objectBuff.vertices.push_back(vertices);	//右下
//	vertices.pos = XMFLOAT3(-size.x, size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 1);
//	objectBuff.vertices.push_back(vertices);	//右上
//	//右
//	vertices.pos = XMFLOAT3(size.x, -size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 0);
//	objectBuff.vertices.push_back(vertices);	//左下
//	vertices.pos = XMFLOAT3(size.x, size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 1);
//	objectBuff.vertices.push_back(vertices);	//左上
//	vertices.pos = XMFLOAT3(size.x, -size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 0);
//	objectBuff.vertices.push_back(vertices);	//右下
//	vertices.pos = XMFLOAT3(size.x, size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 1);
//	objectBuff.vertices.push_back(vertices);	//右上
//	//左
//	vertices.pos = XMFLOAT3(-size.x, -size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 0);
//	objectBuff.vertices.push_back(vertices);	//左下
//	vertices.pos = XMFLOAT3(-size.x, size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 1);
//	objectBuff.vertices.push_back(vertices);	//左上
//	vertices.pos = XMFLOAT3(-size.x, -size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 0);
//	objectBuff.vertices.push_back(vertices);	//右下
//	vertices.pos = XMFLOAT3(-size.x, size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 1);
//	objectBuff.vertices.push_back(vertices);	//右上
//	//下
//	vertices.pos = XMFLOAT3(-size.x, -size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 0);
//	objectBuff.vertices.push_back(vertices);	//左下
//	vertices.pos = XMFLOAT3(-size.x, -size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 1);
//	objectBuff.vertices.push_back(vertices);	//左上
//	vertices.pos = XMFLOAT3(size.x, -size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 0);
//	objectBuff.vertices.push_back(vertices);	//右下
//	vertices.pos = XMFLOAT3(size.x, -size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 1);
//	objectBuff.vertices.push_back(vertices);	//右上
//	//上
//	vertices.pos = XMFLOAT3(-size.x, size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 0);
//	objectBuff.vertices.push_back(vertices);	//左下
//	vertices.pos = XMFLOAT3(-size.x, size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(0, 1);
//	objectBuff.vertices.push_back(vertices);	//左上
//	vertices.pos = XMFLOAT3(size.x, size.y, -size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 0);
//	objectBuff.vertices.push_back(vertices);	//右下
//	vertices.pos = XMFLOAT3(size.x, size.y, size.z);
//	vertices.normal = XMFLOAT3(0, 0, 0);
//	vertices.uv = XMFLOAT2(1, 1);
//	objectBuff.vertices.push_back(vertices);	//右上
//#pragma endregion
//
//	//インデックスの設定
//	int buff = 0;
//	for (int i = 0; i < 6; ++i) {
//		objectBuff.indices.push_back(0 + buff);
//		objectBuff.indices.push_back(1 + buff);
//		objectBuff.indices.push_back(2 + buff);
//		objectBuff.indices.push_back(2 + buff);
//		objectBuff.indices.push_back(1 + buff);
//		objectBuff.indices.push_back(3 + buff);
//		buff += 4;
//	}
//
//	//法線ベクトルの計算
//	for (int i = 0; i < objectBuff.indices.size() / 3; ++i)
//	{
//		//三角形ひとつひとつ計算していく
//		//三角形のインデックスを取り出して、一時的な変数に入れる
//		unsigned short index0 = objectBuff.indices.at(i * 3 + 0);
//		unsigned short index1 = objectBuff.indices.at(i * 3 + 1);
//		unsigned short index2 = objectBuff.indices.at(i * 3 + 2);
//		//三角形を構成する頂点座標をベクトルに代入
//		XMVECTOR p0 = XMLoadFloat3(&objectBuff.vertices.at(index0).pos);
//		XMVECTOR p1 = XMLoadFloat3(&objectBuff.vertices.at(index1).pos);
//		XMVECTOR p2 = XMLoadFloat3(&objectBuff.vertices.at(index2).pos);
//		//p0->p1ベクトル,p0->p2ベクトルを計算
//		XMVECTOR v1 = XMVectorSubtract(p1, p0);
//		XMVECTOR v2 = XMVectorSubtract(p2, p0);
//		//外戚は両方から垂直なベクトル
//		XMVECTOR normal = XMVector3Cross(v1, v2);
//		//正規化
//		normal = XMVector3Normalize(normal);
//		//求めた法線を頂点データに代入
//		XMStoreFloat3(&objectBuff.vertices.at(index0).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(index1).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(index2).normal, normal);
//	}
//
//	//頂点バッファビューの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.vertices.size() * sizeof(Vertex)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.vertBuff)
//	);
//
//	//頂点バッファビューの設定
//	objectBuff.vbView.BufferLocation = objectBuff.vertBuff->GetGPUVirtualAddress();
//	objectBuff.vbView.SizeInBytes = objectBuff.vertices.size() * sizeof(Vertex);
//	objectBuff.vbView.StrideInBytes = sizeof(Vertex);
//
//	//インデックスバッファの設定
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.indices.size() * sizeof(unsigned short)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.indexBuff)
//	);
//
//	//インデックスバッファビューの設定
//	objectBuff.ibView.BufferLocation = objectBuff.indexBuff->GetGPUVirtualAddress();
//	objectBuff.ibView.Format = DXGI_FORMAT_R16_UINT;
//	objectBuff.ibView.SizeInBytes = objectBuff.indices.size() * sizeof(unsigned short);
//
//	//定数バッファの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.constBuff)
//	);
//
//	//行列を初期化
//	objectBuff.matRot = XMMatrixIdentity();
//	objectBuff.matScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
//	objectBuff.matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
//	objectBuff.pos = XMFLOAT3(objectBuff.matTrans.r[3].m128_f32[0], objectBuff.matTrans.r[3].m128_f32[1], objectBuff.matTrans.r[3].m128_f32[2]);
//
//	//マップ処理
//	Vertex* vertMap = nullptr;
//	objectBuff.vertBuff->Map(0, nullptr, (void**)&vertMap);
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.vertices.size(); ++i)
//	{
//		vertMap[i] = objectBuff.vertices.at(i);
//	}
//	//マップを解除
//	objectBuff.vertBuff->Unmap(0, nullptr);
//
//	unsigned short* indexMap = nullptr;
//	result = objectBuff.indexBuff->Map(0, nullptr, (void**)&indexMap);
//
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.indices.size(); ++i)
//	{
//		indexMap[i] = objectBuff.indices.at(i);
//	}
//	//マップを解除
//	objectBuff.indexBuff->Unmap(0, nullptr);
//
//	//CBVディスクリプタヒープの先頭アドレスを取得
//	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
//		objectBuff.constDescHeap->GetCPUDescriptorHandleForHeapStart(), 0, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
//	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
//	cbvDesc.BufferLocation = objectBuff.constBuff->GetGPUVirtualAddress();
//	cbvDesc.SizeInBytes = (UINT)objectBuff.constBuff->GetDesc().Width;
//	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);
//
//	//定数バッファへのデータ転送
//	ConstBufferData* constMap = nullptr;
//	result = objectBuff.constBuff->Map(0, nullptr, (void**)&constMap);
//	constMap->color = XMFLOAT4(1, 1, 1, 1);//Object3D.constBufferData.color;;
//	objectBuff.constBuff->Unmap(0, nullptr);
//
//	return objectBuff;
//}
//
//Object3D ObjectManager::InitCone(XMFLOAT3 pos, int projectionID, XMFLOAT4 color, LPCWSTR fileName)
//{
//	Object3D objectBuff;
//	objectBuff.projectionID = projectionID;
//
//	//設定構造体
//	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
//	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;			//シェーダーから見える
//	descHeapDesc.NumDescriptors = 2;										//CBV2つ
//	//ディスクリプタヒープの生成
//	HRESULT result = DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&objectBuff.constDescHeap));
//
//	//テクスチャをロード
//	if (fileName != 0)
//	{
//		objectBuff.textureIDnum = TextureManager::Instance()->LoadTexture(fileName);
//	}
//	else
//	{
//		objectBuff.textureIDnum = TextureManager::Instance()->CreateTexture(color);
//	}
//
//	//頂点の生成
//	ShapeManager::Instance()->LoadObject(SHAPE_DATA_CONE, objectBuff);
//
//	//頂点バッファビューの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.vertices.size() * sizeof(Vertex)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.vertBuff)
//	);
//
//	//頂点バッファビューの設定
//	objectBuff.vbView.BufferLocation = objectBuff.vertBuff->GetGPUVirtualAddress();
//	objectBuff.vbView.SizeInBytes = objectBuff.vertices.size() * sizeof(Vertex);
//	objectBuff.vbView.StrideInBytes = sizeof(Vertex);
//
//	//インデックスバッファの設定
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.indices.size() * sizeof(unsigned short)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.indexBuff)
//	);
//
//	//インデックスバッファビューの設定
//	objectBuff.ibView.BufferLocation = objectBuff.indexBuff->GetGPUVirtualAddress();
//	objectBuff.ibView.Format = DXGI_FORMAT_R16_UINT;
//	objectBuff.ibView.SizeInBytes = objectBuff.indices.size() * sizeof(unsigned short);
//	//定数バッファの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.constBuff)
//	);
//
//	//行列を初期化
//	objectBuff.matRot = XMMatrixIdentity();
//	objectBuff.matScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
//	objectBuff.matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
//	objectBuff.pos = XMFLOAT3(objectBuff.matTrans.r[3].m128_f32[0], objectBuff.matTrans.r[3].m128_f32[1], objectBuff.matTrans.r[3].m128_f32[2]);
//
//	//マップ処理
//	Vertex* vertMap = nullptr;
//	objectBuff.vertBuff->Map(0, nullptr, (void**)&vertMap);
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.vertices.size(); ++i)
//	{
//		vertMap[i] = objectBuff.vertices.at(i);
//	}
//	//マップを解除
//	objectBuff.vertBuff->Unmap(0, nullptr);
//
//	unsigned short* indexMap = nullptr;
//	result = objectBuff.indexBuff->Map(0, nullptr, (void**)&indexMap);
//
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.indices.size(); ++i)
//	{
//		indexMap[i] = objectBuff.indices.at(i);
//	}
//	//マップを解除
//	objectBuff.indexBuff->Unmap(0, nullptr);
//
//	//CBVディスクリプタヒープの先頭アドレスを取得
//	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
//		objectBuff.constDescHeap->GetCPUDescriptorHandleForHeapStart(), 0, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
//	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
//	cbvDesc.BufferLocation = objectBuff.constBuff->GetGPUVirtualAddress();
//	cbvDesc.SizeInBytes = (UINT)objectBuff.constBuff->GetDesc().Width;
//	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);
//
//	//定数バッファへのデータ転送
//	objectBuff.constBufferData.color = color;
//	ConstBufferData* constMap = nullptr;
//	result = objectBuff.constBuff->Map(0, nullptr, (void**)&constMap);
//	constMap->color = objectBuff.constBufferData.color;;
//	objectBuff.constBuff->Unmap(0, nullptr);
//
//	return objectBuff;
//}
//
//Object3D ObjectManager::InitCylinder(XMFLOAT3 pos, float radius, float height, int projectionID, XMFLOAT4 color, LPCWSTR fileName)
//{
//	Object3D objectBuff;
//	objectBuff.projectionID = projectionID;
//
//	//設定構造体
//	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
//	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;			//シェーダーから見える
//	descHeapDesc.NumDescriptors = 2;										//CBV2つ
//	//ディスクリプタヒープの生成
//	HRESULT result = DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&objectBuff.constDescHeap));
//
//	//テクスチャをロード
//	//テクスチャをロード
//	if (fileName != 0)
//	{
//		objectBuff.textureIDnum = TextureManager::Instance()->LoadTexture(fileName);
//	}
//	else
//	{
//		objectBuff.textureIDnum = TextureManager::Instance()->CreateTexture(color);
//	}
//
//	//頂点の生成
//	ShapeManager::Instance()->LoadObject(SHAPE_DATA_CYLINDER, objectBuff);
//
//	//頂点バッファビューの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.vertices.size() * sizeof(Vertex)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.vertBuff)
//	);
//
//	//頂点バッファビューの設定
//	objectBuff.vbView.BufferLocation = objectBuff.vertBuff->GetGPUVirtualAddress();
//	objectBuff.vbView.SizeInBytes = objectBuff.vertices.size() * sizeof(Vertex);
//	objectBuff.vbView.StrideInBytes = sizeof(Vertex);
//
//	//インデックスバッファの設定
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.indices.size() * sizeof(unsigned short)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.indexBuff)
//	);
//
//	//インデックスバッファビューの設定
//	objectBuff.ibView.BufferLocation = objectBuff.indexBuff->GetGPUVirtualAddress();
//	objectBuff.ibView.Format = DXGI_FORMAT_R16_UINT;
//	objectBuff.ibView.SizeInBytes = objectBuff.indices.size() * sizeof(unsigned short);
//	//定数バッファの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.constBuff)
//	);
//
//	//行列を初期化
//	objectBuff.matRot = XMMatrixIdentity();
//	objectBuff.matScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
//	objectBuff.matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
//	objectBuff.pos = XMFLOAT3(objectBuff.matTrans.r[3].m128_f32[0], objectBuff.matTrans.r[3].m128_f32[1], objectBuff.matTrans.r[3].m128_f32[2]);
//
//	//マップ処理
//	Vertex* vertMap = nullptr;
//	objectBuff.vertBuff->Map(0, nullptr, (void**)&vertMap);
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.vertices.size(); ++i)
//	{
//		vertMap[i] = objectBuff.vertices.at(i);
//	}
//	//マップを解除
//	objectBuff.vertBuff->Unmap(0, nullptr);
//
//	unsigned short* indexMap = nullptr;
//	result = objectBuff.indexBuff->Map(0, nullptr, (void**)&indexMap);
//
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.indices.size(); ++i)
//	{
//		indexMap[i] = objectBuff.indices.at(i);
//	}
//	//マップを解除
//	objectBuff.indexBuff->Unmap(0, nullptr);
//
//	//CBVディスクリプタヒープの先頭アドレスを取得
//	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
//		objectBuff.constDescHeap->GetCPUDescriptorHandleForHeapStart(), 0, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
//	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
//	cbvDesc.BufferLocation = objectBuff.constBuff->GetGPUVirtualAddress();
//	cbvDesc.SizeInBytes = (UINT)objectBuff.constBuff->GetDesc().Width;
//	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);
//
//	//定数バッファへのデータ転送
//	objectBuff.constBufferData.color = color;
//	ConstBufferData* constMap = nullptr;
//	result = objectBuff.constBuff->Map(0, nullptr, (void**)&constMap);
//	constMap->color = objectBuff.constBufferData.color;;
//	objectBuff.constBuff->Unmap(0, nullptr);
//
//	return objectBuff;
//}
//
//Object3D ObjectManager::InitSphere(XMFLOAT3 pos, float radius, int projectionID, XMFLOAT4 color, LPCWSTR fileName)
//{
//	Object3D objectBuff;
//	objectBuff.projectionID = projectionID;
//
//	//設定構造体
//	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
//	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;			//シェーダーから見える
//	descHeapDesc.NumDescriptors = 2;										//CBV2つ
//	//ディスクリプタヒープの生成
//	HRESULT result = DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&objectBuff.constDescHeap));
//
//	//テクスチャをロード
//	if (fileName != 0)
//	{
//		objectBuff.textureIDnum = TextureManager::Instance()->LoadTexture(fileName);
//	}
//	else
//	{
//		objectBuff.textureIDnum = TextureManager::Instance()->CreateTexture(color);
//	}
//
//	//頂点の生成
//	ShapeManager::Instance()->LoadObject(SHAPE_DATA_SPHERE, objectBuff);
//
//	//頂点バッファビューの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.vertices.size() * sizeof(Vertex)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.vertBuff)
//	);
//
//	//頂点バッファビューの設定
//	objectBuff.vbView.BufferLocation = objectBuff.vertBuff->GetGPUVirtualAddress();
//	objectBuff.vbView.SizeInBytes = objectBuff.vertices.size() * sizeof(Vertex);
//	objectBuff.vbView.StrideInBytes = sizeof(Vertex);
//
//	//インデックスバッファの設定
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.indices.size() * sizeof(unsigned short)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.indexBuff)
//	);
//
//	//インデックスバッファビューの設定
//	objectBuff.ibView.BufferLocation = objectBuff.indexBuff->GetGPUVirtualAddress();
//	objectBuff.ibView.Format = DXGI_FORMAT_R16_UINT;
//	objectBuff.ibView.SizeInBytes = objectBuff.indices.size() * sizeof(unsigned short);
//	//定数バッファの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.constBuff)
//	);
//
//	//行列を初期化
//	objectBuff.matRot = XMMatrixIdentity();
//	objectBuff.matScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
//	objectBuff.matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
//	objectBuff.pos = XMFLOAT3(objectBuff.matTrans.r[3].m128_f32[0], objectBuff.matTrans.r[3].m128_f32[1], objectBuff.matTrans.r[3].m128_f32[2]);
//
//	//マップ処理
//	Vertex* vertMap = nullptr;
//	objectBuff.vertBuff->Map(0, nullptr, (void**)&vertMap);
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.vertices.size(); ++i)
//	{
//		vertMap[i] = objectBuff.vertices.at(i);
//	}
//	//マップを解除
//	objectBuff.vertBuff->Unmap(0, nullptr);
//
//	unsigned short* indexMap = nullptr;
//	result = objectBuff.indexBuff->Map(0, nullptr, (void**)&indexMap);
//
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.indices.size(); ++i)
//	{
//		indexMap[i] = objectBuff.indices.at(i);
//	}
//	//マップを解除
//	objectBuff.indexBuff->Unmap(0, nullptr);
//
//	//CBVディスクリプタヒープの先頭アドレスを取得
//	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
//		objectBuff.constDescHeap->GetCPUDescriptorHandleForHeapStart(), 0, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
//	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
//	cbvDesc.BufferLocation = objectBuff.constBuff->GetGPUVirtualAddress();
//	cbvDesc.SizeInBytes = (UINT)objectBuff.constBuff->GetDesc().Width;
//	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);
//
//	//定数バッファへのデータ転送
//	//Object3D.constBufferData.color = color;
//	ConstBufferData* constMap = nullptr;
//	result = objectBuff.constBuff->Map(0, nullptr, (void**)&constMap);
//	constMap->color = objectBuff.constBufferData.color;;
//	objectBuff.constBuff->Unmap(0, nullptr);
//
//	return objectBuff;
//}
//
//Object3D ObjectManager::Init3DObject(XMFLOAT3 pos, int projectionID, LPCWSTR texFileName, const char* objFileName)
//{
//	Object3D objectBuff;
//	objectBuff.projectionID = projectionID;
//
//	//設定構造体
//	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
//	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;			//シェーダーから見える
//	descHeapDesc.NumDescriptors = 2;										//CBV2つ
//	//ディスクリプタヒープの生成
//	HRESULT result = DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&objectBuff.constDescHeap));
//
//	//テクスチャをロード
//	objectBuff.textureIDnum = TextureManager::Instance()->LoadTexture(texFileName);
//
//	ShapeManager::Instance()->LoadObject(SHAPE_DATA_OBJECT, objectBuff, objFileName);
//
//	//法線ベクトルの計算
//	for (int i = 0; i < objectBuff.indices.size() / 3; ++i) {
//		//三角形ひとつひとつ計算していく
//		//三角形のインデックスを取り出して、一時的な変数に入れる
//		unsigned short index0 = objectBuff.indices.at(i * 3 + 0);
//		unsigned short index1 = objectBuff.indices.at(i * 3 + 1);
//		unsigned short index2 = objectBuff.indices.at(i * 3 + 2);
//		//三角形を構成する頂点座標をベクトルに代入
//		XMVECTOR p0 = XMLoadFloat3(&objectBuff.vertices.at(index0).pos);
//		XMVECTOR p1 = XMLoadFloat3(&objectBuff.vertices.at(index1).pos);
//		XMVECTOR p2 = XMLoadFloat3(&objectBuff.vertices.at(index2).pos);
//		//p0->p1ベクトル,p0->p2ベクトルを計算
//		XMVECTOR v1 = XMVectorSubtract(p1, p0);
//		XMVECTOR v2 = XMVectorSubtract(p2, p0);
//		//外戚は両方から垂直なベクトル
//		XMVECTOR normal = XMVector3Cross(v1, v2);
//		//正規化
//		normal = XMVector3Normalize(normal);
//		//求めた法線を頂点データに代入
//		//Object3Dへのコピー
//		XMStoreFloat3(&objectBuff.vertices.at(index0).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(index1).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(index2).normal, normal);
//	}
//
//	//頂点バッファビューの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.vertices.size() * sizeof(Vertex)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.vertBuff)
//	);
//
//	//頂点バッファビューの設定
//	objectBuff.vbView.BufferLocation = objectBuff.vertBuff->GetGPUVirtualAddress();
//	objectBuff.vbView.SizeInBytes = objectBuff.vertices.size() * sizeof(Vertex);
//	objectBuff.vbView.StrideInBytes = sizeof(Vertex);
//
//	//インデックスバッファの設定
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.indices.size() * sizeof(unsigned short)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.indexBuff)
//	);
//
//	//インデックスバッファビューの設定
//	objectBuff.ibView.BufferLocation = objectBuff.indexBuff->GetGPUVirtualAddress();
//	objectBuff.ibView.Format = DXGI_FORMAT_R16_UINT;
//	objectBuff.ibView.SizeInBytes = objectBuff.indices.size() * sizeof(unsigned short);
//	//定数バッファの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.constBuff)
//	);
//
//	//行列を初期化
//	objectBuff.matRot = XMMatrixIdentity();
//	objectBuff.matScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
//	objectBuff.matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
//	objectBuff.pos = XMFLOAT3(objectBuff.matTrans.r[3].m128_f32[0], objectBuff.matTrans.r[3].m128_f32[1], objectBuff.matTrans.r[3].m128_f32[2]);
//
//	//マップ処理
//	Vertex* vertMap = nullptr;
//	objectBuff.vertBuff->Map(0, nullptr, (void**)&vertMap);
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.vertices.size(); ++i)
//	{
//		vertMap[i] = objectBuff.vertices.at(i);
//	}
//	//マップを解除
//	objectBuff.vertBuff->Unmap(0, nullptr);
//
//	unsigned short* indexMap = nullptr;
//	result = objectBuff.indexBuff->Map(0, nullptr, (void**)&indexMap);
//
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.indices.size(); ++i)
//	{
//		indexMap[i] = objectBuff.indices.at(i);
//	}
//	//マップを解除
//	objectBuff.indexBuff->Unmap(0, nullptr);
//
//	//CBVディスクリプタヒープの先頭アドレスを取得
//	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
//		objectBuff.constDescHeap->GetCPUDescriptorHandleForHeapStart(), 0, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
//	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
//	cbvDesc.BufferLocation = objectBuff.constBuff->GetGPUVirtualAddress();
//	cbvDesc.SizeInBytes = (UINT)objectBuff.constBuff->GetDesc().Width;
//	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);
//
//	//定数バッファへのデータ転送
//	ConstBufferData* constMap = nullptr;
//	result = objectBuff.constBuff->Map(0, nullptr, (void**)&constMap);
//	constMap->color = objectBuff.constBufferData.color;;
//	objectBuff.constBuff->Unmap(0, nullptr);
//
//	return objectBuff;
//}
//
//Object3D ObjectManager::InitFdxModel(XMFLOAT3 pos, int projectionID, const char* fbxFileName)
//{
//	Object3D objectBuff;
//	objectBuff.projectionID = projectionID;
//
//	//設定構造体
//	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
//	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;			//シェーダーから見える
//	descHeapDesc.NumDescriptors = 2;										//CBV2つ
//	//ディスクリプタヒープの生成
//	HRESULT result = DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&objectBuff.constDescHeap));
//
//	//ShapeManager::Instance()->LoadObject(SHAPE_DATA_OBJECT, objectBuff, objFileName);
//
//	FbxModelLoader::Instance()->LoadModelFromFile(fbxFileName);
//
//	//法線ベクトルの計算
//	for (int i = 0; i < objectBuff.indices.size() / 3; ++i) {
//		//三角形ひとつひとつ計算していく
//		//三角形のインデックスを取り出して、一時的な変数に入れる
//		unsigned short index0 = objectBuff.indices.at(i * 3 + 0);
//		unsigned short index1 = objectBuff.indices.at(i * 3 + 1);
//		unsigned short index2 = objectBuff.indices.at(i * 3 + 2);
//		//三角形を構成する頂点座標をベクトルに代入
//		XMVECTOR p0 = XMLoadFloat3(&objectBuff.vertices.at(index0).pos);
//		XMVECTOR p1 = XMLoadFloat3(&objectBuff.vertices.at(index1).pos);
//		XMVECTOR p2 = XMLoadFloat3(&objectBuff.vertices.at(index2).pos);
//		//p0->p1ベクトル,p0->p2ベクトルを計算
//		XMVECTOR v1 = XMVectorSubtract(p1, p0);
//		XMVECTOR v2 = XMVectorSubtract(p2, p0);
//		//外戚は両方から垂直なベクトル
//		XMVECTOR normal = XMVector3Cross(v1, v2);
//		//正規化
//		normal = XMVector3Normalize(normal);
//		//求めた法線を頂点データに代入
//		//Object3Dへのコピー
//		XMStoreFloat3(&objectBuff.vertices.at(index0).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(index1).normal, normal);
//		XMStoreFloat3(&objectBuff.vertices.at(index2).normal, normal);
//	}
//
//	//頂点バッファビューの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.vertices.size() * sizeof(Vertex)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.vertBuff)
//	);
//
//	//頂点バッファビューの設定
//	objectBuff.vbView.BufferLocation = objectBuff.vertBuff->GetGPUVirtualAddress();
//	objectBuff.vbView.SizeInBytes = objectBuff.vertices.size() * sizeof(Vertex);
//	objectBuff.vbView.StrideInBytes = sizeof(Vertex);
//
//	//インデックスバッファの設定
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(objectBuff.indices.size() * sizeof(unsigned short)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.indexBuff)
//	);
//
//	//インデックスバッファビューの設定
//	objectBuff.ibView.BufferLocation = objectBuff.indexBuff->GetGPUVirtualAddress();
//	objectBuff.ibView.Format = DXGI_FORMAT_R16_UINT;
//	objectBuff.ibView.SizeInBytes = objectBuff.indices.size() * sizeof(unsigned short);
//	//定数バッファの生成
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&objectBuff.constBuff)
//	);
//
//	//行列を初期化
//	objectBuff.matRot = XMMatrixIdentity();
//	objectBuff.matScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
//	objectBuff.matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
//	objectBuff.pos = XMFLOAT3(objectBuff.matTrans.r[3].m128_f32[0], objectBuff.matTrans.r[3].m128_f32[1], objectBuff.matTrans.r[3].m128_f32[2]);
//
//	//マップ処理
//	Vertex* vertMap = nullptr;
//	objectBuff.vertBuff->Map(0, nullptr, (void**)&vertMap);
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.vertices.size(); ++i)
//	{
//		vertMap[i] = objectBuff.vertices.at(i);
//	}
//	//マップを解除
//	objectBuff.vertBuff->Unmap(0, nullptr);
//
//	unsigned short* indexMap = nullptr;
//	result = objectBuff.indexBuff->Map(0, nullptr, (void**)&indexMap);
//
//	//全頂点に対して
//	for (int i = 0; i < objectBuff.indices.size(); ++i)
//	{
//		indexMap[i] = objectBuff.indices.at(i);
//	}
//	//マップを解除
//	objectBuff.indexBuff->Unmap(0, nullptr);
//
//	//CBVディスクリプタヒープの先頭アドレスを取得
//	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
//		objectBuff.constDescHeap->GetCPUDescriptorHandleForHeapStart(), 0, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
//	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
//	cbvDesc.BufferLocation = objectBuff.constBuff->GetGPUVirtualAddress();
//	cbvDesc.SizeInBytes = (UINT)objectBuff.constBuff->GetDesc().Width;
//	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);
//
//	//定数バッファへのデータ転送
//	ConstBufferData* constMap = nullptr;
//	result = objectBuff.constBuff->Map(0, nullptr, (void**)&constMap);
//	constMap->color = objectBuff.constBufferData.color;;
//	objectBuff.constBuff->Unmap(0, nullptr);
//
//	return objectBuff;
//}
//
//void ObjectManager::CommonInit(int blendID, D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType)
//{
//	//渡されたデータをどう使うかの解釈方法をGPUに伝えるためのもの
//	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
//		{	//頂点座標
//			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
//		},
//		{	//法線ベクトル
//			"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
//		},
//		{	//uv座標
//			"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
//		}
//	};
//
//	//シェーダー読み込み
//	ComPtr<ID3DBlob> vsBlob = nullptr;		//頂点シェーダオブジェクト
//	ComPtr<ID3DBlob> psBlob = nullptr;		//ピクセルシェーダオブジェクト
//	ComPtr<ID3DBlob> errorBlob = nullptr;	//エラーオブジェクト
//	//頂点シェーダーの読み込みコンパイル
//	HRESULT result = D3DCompileFromFile(
//		L"Resources/Shader/ObjectVS.hlsl",					//シェーダーファイル
//		nullptr,
//		D3D_COMPILE_STANDARD_FILE_INCLUDE,					//インクルード可能にする
//		"main", "vs_5_0",									//エントリーポイント名、シェーダーモデル限定
//		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,	//デバック用固定
//		0,
//		&vsBlob, &errorBlob
//	);
//
//	//ピクセルシェーダーの読み込みとコンパイル
//	result = D3DCompileFromFile(
//		L"Resources/Shader/ObjectPS.hlsl",					//シェーダーファイル名
//		nullptr,
//		D3D_COMPILE_STANDARD_FILE_INCLUDE,					//インクルード可能にする
//		"main", "ps_5_0",									//エントリーポイント名、シェーダーモデル固定
//		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,	//デバック用固定
//		0,
//		&psBlob, &errorBlob
//	);
//
//	//デスクリプタテーブルの設定
//	CD3DX12_DESCRIPTOR_RANGE descRangeCBV{}, descRangeSRV{};
//	descRangeCBV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);					//b0レジスタ
//	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);					//t0レジスタ
//
//	//ルートパラメーターの設定
//	CD3DX12_ROOT_PARAMETER rootparam[2]{};
//	//定数用
//	rootparam[0].InitAsDescriptorTable(1, &descRangeCBV, D3D12_SHADER_VISIBILITY_ALL);
//	//テクスチャ用
//	rootparam[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);
//
//	//グラフィックスパイプライン生成
//	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
//	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
//	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
//	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;						//標準設定
//	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);		//背面カリング,ポリゴン内塗りつぶし,深度クリッピングを有効に
//	//gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
//	gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
//	gpipeline.BlendState.AlphaToCoverageEnable = true;
//
//	//レンダーターゲットのブレンド設定
//	D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = gpipeline.BlendState.RenderTarget[0];
//	blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
//	blendDesc.BlendEnable = true;											//ブレンドを有効にする
//	blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;							//加算
//	blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;								//ソースの値を100%使う
//	blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;							//デストの値を0%使う
//
//	switch (blendID) {
//	case bLEND_MODE_ADD:
//		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;									//加算
//		blendDesc.SrcBlend = D3D12_BLEND_ONE;									//ソースの値を100%使う
//		blendDesc.DestBlend = D3D12_BLEND_ONE;									//ソースの値を100%使う
//		break;
//	case BLEND_MODE_ALPHA:
//		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;									//加算
//		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;								//ソースの値を100%使う
//		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;						//ソースの値を100%使う
//		break;
//	default:
//		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;									//加算
//		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;								//ソースの値を100%使う
//		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;						//ソースの値を100%使う
//	}
//
//	//頂点レイアウトの設定
//	gpipeline.InputLayout.pInputElementDescs = inputLayout;
//	gpipeline.InputLayout.NumElements = _countof(inputLayout);
//
//	//図形の形状を三角形に設定
//	gpipeline.PrimitiveTopologyType = primitiveType;
//
//	//その他の設定
//	gpipeline.NumRenderTargets = 1;							//描画対象は1つ
//	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;	//0～255指定のRGBA
//	gpipeline.SampleDesc.Count = 1;											//1ピクセルにつき1回サンプリング
//
//	//デプスステンシルステートの設定
//	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);//深度テストを行う,書き込み許可,深度が小さければ合格
//	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;
//
//	//テクスチャサンプラーのセット
//	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);
//
//	//ルートシグネチャの設定
//	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
//	rootSignatureDesc.Init_1_0(_countof(rootparam), rootparam, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
//
//	ComPtr<ID3DBlob> rootSigBlob = {};
//	//バージョン自動判定でのシリアライズ
//	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
//	//ルートシグネチャの生成
//	result = DirectXBase::dev->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootsignature));
//
//	//パイプラインにルートシグネチャをセット
//	gpipeline.pRootSignature = rootsignature.Get();
//
//	result = DirectXBase::dev->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelinestate));
//
//}
//
//void ObjectManager::CommonDraw(D3D12_PRIMITIVE_TOPOLOGY topology)
//{
//	//パイプラインステート設定コマンド
//	DirectXBase::Instance()->cmdList->SetPipelineState(pipelinestate.Get());
//
//	//ルートシグネチャ設定コマンド
//	DirectXBase::Instance()->cmdList->SetGraphicsRootSignature(rootsignature.Get());
//
//	//プリミティブ形状設定コマンド
//	DirectXBase::Instance()->cmdList->IASetPrimitiveTopology(topology);
//}
//
//void ObjectManager::Draw(Object3D& objectBuff)
//{
//	//非表示状態だったら描画処理を行わない
//	if (objectBuff.isDisplay == false) return;
//
//	//定数バッファへのデータ転送
//	ConstBufferData* constMap = nullptr;
//	HRESULT result = objectBuff.constBuff->Map(0, nullptr, (void**)&constMap);
//	constMap->color = objectBuff.constBufferData.color;
//
//	//ワールド行列の更新
//	if (objectBuff.projectionID == PROJECTIONID_UI)
//	{
//		constMap->mat.world = Camera::Instance()->matProjection;
//	}
//	else if (objectBuff.projectionID == PROJECTIONID_OBJECT)
//	{
//		XMMATRIX matWorld = XMMatrixIdentity();
//		matWorld *= objectBuff.matScale;
//		matWorld *= objectBuff.matRot;
//		matWorld *= objectBuff.matTrans;
//		constMap->mat.world = matWorld * Camera::matView * Camera::matPerspective;				//ワールド変換 * ビュー変換 * 透視投影変換
//		//constMap->mat.viewproj = matView * matProjection;
//	}
//	//ビルボードの場合
//	else if (objectBuff.projectionID == PROJECTIONID_BILLBOARD) {
//		//視点座標
//		XMVECTOR eyePosition = XMLoadFloat3(&Camera::Instance()->eye);
//		//注視点座標
//		XMVECTOR targetPosition = XMLoadFloat3(&Camera::Instance()->target);
//		//(仮の)上方向
//		XMVECTOR upVector = XMLoadFloat3(&Camera::Instance()->up);
//		//カメラZ軸
//		XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
//		//0ベクトルだと向きが定まらないので除外
//		assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
//		assert(!XMVector3IsInfinite(cameraAxisZ));
//		assert(!XMVector3Equal(upVector, XMVectorZero()));
//		assert(!XMVector3IsInfinite(upVector));
//		//ベクトルを正規化
//		cameraAxisZ = XMVector3Normalize(cameraAxisZ);
//		//カメラのX軸方向(右方向)
//		XMVECTOR cameraAxisX{};
//		//X軸は上方向->Z軸の外積で求まる
//		cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
//		//ベクトルを正規化
//		cameraAxisX = XMVector3Normalize(cameraAxisX);
//		//カメラのY軸(上方向)
//		XMVECTOR cameraAxisY{};
//		//Y軸はZ軸->X軸の外積で求める
//		cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);
//		//ベクトルを正規化
//		cameraAxisY = XMVector3Normalize(cameraAxisY);
//		//カメラ回転行列
//		XMMATRIX matCameraRot;
//		//カメラ座標系->ワールド座標系の返還行列
//		matCameraRot.r[0] = cameraAxisX;
//		matCameraRot.r[1] = cameraAxisY;
//		matCameraRot.r[2] = cameraAxisZ;
//		matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);
//		//転地により逆行列(逆回転)を計算
//		XMMATRIX matView = XMMatrixTranspose(matCameraRot);
//		//視点座標に-1をかけた座標
//		XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
//		//カメラの位置からワールド原点へのベクトル(カメラ座標系)
//		XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);		//X成分
//		XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);		//Y成分
//		XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);		//Z成分
//		//一つのベクトルにまとめる
//		XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
//		//ビュー行列に平行移動分を設定
//		matView.r[3] = translation;
//
//		//ビルボード行列
//		XMMATRIX billboardMat = XMMatrixIdentity();
//		billboardMat.r[0] = cameraAxisX;
//		billboardMat.r[1] = cameraAxisY;
//		billboardMat.r[2] = cameraAxisZ;
//		billboardMat.r[3] = XMVectorSet(0, 0, 0, 1);
//		//ワールド行列の更新
//		XMMATRIX matWorld = XMMatrixIdentity();
//		matWorld *= billboardMat;
//		matWorld *= objectBuff.matScale;
//		matWorld *= objectBuff.matRot;
//		matWorld *= objectBuff.matTrans;
//		constMap->mat.world = matWorld * matView * Camera::Instance()->matPerspective;												//ワールド変換 * ビュー変換 * 透視投影変換
//		//constMap->mat.viewproj = 
//	}
//	objectBuff.constBuff->Unmap(0, nullptr);
//
//	//ディスクリプタヒープ設定コマンド
//	ID3D12DescriptorHeap* ppHeaps[] = { objectBuff.constDescHeap.Get() };
//	DirectXBase::Instance()->cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
//
//	//定数バッファビュー設定コマンド
//	D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandle;
//	gpuDescHandle = objectBuff.constDescHeap->GetGPUDescriptorHandleForHeapStart();
//	//gpuDescHandle.ptr += DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
//	DirectXBase::Instance()->cmdList->SetGraphicsRootDescriptorTable(0, gpuDescHandle);
//
//	//ディスクリプタヒープ設定コマンド
//	ID3D12DescriptorHeap* ppHeaps2[] = { TextureManager::Instance()->GetDescHeap().Get() };
//	DirectXBase::Instance()->cmdList->SetDescriptorHeaps(_countof(ppHeaps2), ppHeaps2);
//
//	//シェーダーリソースビュー設定コマンド
//	DirectXBase::Instance()->cmdList->SetGraphicsRootDescriptorTable(1, TextureManager::Instance()->GetSRV(objectBuff.textureIDnum));
//
//
//	//頂点バッファビュー設定コマンド
//	DirectXBase::Instance()->cmdList->IASetVertexBuffers(0, 1, &objectBuff.vbView);
//
//	//インデックスバッファビュー設定コマンドを実行する
//	if (objectBuff.indices.size() > 0) {
//		DirectXBase::Instance()->cmdList->IASetIndexBuffer(&objectBuff.ibView);
//	}
//
//	//描画コマンド
//	if (objectBuff.indices.size() > 0) {
//		DirectXBase::Instance()->cmdList->DrawIndexedInstanced(objectBuff.indices.size(), 1, 0, 0, 0);
//	}
//	else {
//		DirectXBase::Instance()->cmdList->DrawInstanced(objectBuff.vertices.size(), 1, 0, 0);
//	}
//}
//
//void ObjectManager::ChangeScale(Object3D& objectBuff, XMFLOAT3 scale)
//{
//	objectBuff.matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
//}
//
//void ObjectManager::ChangeRotation(Object3D& objectBuff, XMFLOAT3 rotation)
//{
//	XMMATRIX mat = XMMatrixIdentity();
//	mat *= XMMatrixRotationZ(rotation.z);
//	mat *= XMMatrixRotationX(rotation.x);
//	mat *= XMMatrixRotationY(rotation.y);
//	objectBuff.matRot = mat * objectBuff.matRot;
//}
//
//void ObjectManager::ChangePosition(Object3D& objectBuff, XMFLOAT3 position)
//{
//	objectBuff.matTrans = XMMatrixTranslation(position.x, position.y, position.z);
//	objectBuff.pos = XMFLOAT3(objectBuff.matTrans.r[3].m128_f32[0], objectBuff.matTrans.r[3].m128_f32[1], objectBuff.matTrans.r[3].m128_f32[2]);
//}
//
//void ObjectManager::ChangePositionAdd(Object3D& objectBuff, XMFLOAT3 position)
//{
//	objectBuff.matTrans *= XMMatrixTranslation(position.x, position.y, position.z);
//	objectBuff.pos = XMFLOAT3(objectBuff.matTrans.r[3].m128_f32[0], objectBuff.matTrans.r[3].m128_f32[1], objectBuff.matTrans.r[3].m128_f32[2]);
//}