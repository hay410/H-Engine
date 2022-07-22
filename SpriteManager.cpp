//#include"SpriteManager.h"
//
//SpriteManager::SpriteManager(){};
//
//Sprite SpriteManager::InitSprite(XMFLOAT3 pos, XMFLOAT2 size, int projectionID, LPCWSTR fileName)
//{
//	Sprite sprite;
//	sprite.projectionID = projectionID;
//	sprite.isDisplay = true;
//
//	//�ݒ�\����
//	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
//	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;			//�V�F�[�_�[���猩����
//	descHeapDesc.NumDescriptors = 2;										//CBV2��
//	//�f�B�X�N���v�^�q�[�v�̐���
//	HRESULT result = DirectXBase::Instance()->dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&sprite.constDescHeap));
//
//	//�e�N�X�`�������[�h
//	sprite.textureIDnum = TextureManager::Instance()->LoadTexture(fileName);
//
//	////���_�o�b�t�@�̐���
//	//float left = (0.0f - sprite.anchorPoint.x) * size.x;
//	//float right = (1.0f - sprite.anchorPoint.x) * size.x;
//	//float top = (0.0f - sprite.anchorPoint.y) * size.y;
//	//float bottom = (1.0f - sprite.anchorPoint.y) * size.y;
//
//	////����ۑ�
//	//sprite.SavePos = { left, right, top, bottom };
//
//	//���_�o�b�t�@�̐���
//	Vertex vertex;
//	vertex.pos = XMFLOAT3(-size.x, -size.y, 0);	//����
//	vertex.uv = XMFLOAT2(0, 1);
//	sprite.vertices.push_back(vertex);
//	vertex.pos = XMFLOAT3(-size.x, size.y, 0);	//����
//	vertex.uv = XMFLOAT2(0, 0);
//	sprite.vertices.push_back(vertex);
//	vertex.pos = XMFLOAT3(size.x, -size.y, 0);	//�E��
//	vertex.uv = XMFLOAT2(1, 1);
//	sprite.vertices.push_back(vertex);
//	vertex.pos = XMFLOAT3(size.x, size.y, 0);		//�E��
//	vertex.uv = XMFLOAT2(1, 0);
//	sprite.vertices.push_back(vertex);
//
//
//	//���_�o�b�t�@�r���[�̐���
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer(sprite.vertices.size() * sizeof(Vertex)),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&sprite.vertBuff)
//	);
//
//	//���_�o�b�t�@�r���[�̐ݒ�
//	sprite.vbView.BufferLocation = sprite.vertBuff->GetGPUVirtualAddress();
//	sprite.vbView.SizeInBytes = sprite.vertices.size() * sizeof(Vertex);
//	sprite.vbView.StrideInBytes = sizeof(Vertex);
//
//	//�萔�o�b�t�@�̐���
//	result = DirectXBase::Instance()->dev->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
//		D3D12_HEAP_FLAG_NONE,
//		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&sprite.constBuff)
//	);
//
//	//�s���������
//	sprite.matRot = XMMatrixIdentity();
//	sprite.matScale = XMMatrixScaling(2.0f, 2.0f, 1.0f);
//	sprite.matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
//	sprite.pos = XMFLOAT3(sprite.matTrans.r[3].m128_f32[0], sprite.matTrans.r[3].m128_f32[1], sprite.matTrans.r[3].m128_f32[2]);
//
//	//�}�b�v����
//	Vertex* vertMap = nullptr;
//	sprite.vertBuff->Map(0, nullptr, (void**)&vertMap);
//	//�S���_�ɑ΂���
//	for (int i = 0; i < sprite.vertices.size(); ++i)
//	{
//		vertMap[i] = sprite.vertices.at(i);
//	}
//	//�}�b�v������
//	sprite.vertBuff->Unmap(0, nullptr);
//
//	//CBV�f�B�X�N���v�^�q�[�v�̐擪�A�h���X���擾
//	CD3DX12_CPU_DESCRIPTOR_HANDLE basicHeapHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
//		sprite.constDescHeap->GetCPUDescriptorHandleForHeapStart(), 0, DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
//	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
//	cbvDesc.BufferLocation = sprite.constBuff->GetGPUVirtualAddress();
//	cbvDesc.SizeInBytes = (UINT)sprite.constBuff->GetDesc().Width;
//	DirectXBase::Instance()->dev->CreateConstantBufferView(&cbvDesc, basicHeapHandle);
//
//	//�萔�o�b�t�@�ւ̃f�[�^�]��
//	ConstBufferData* constMap = nullptr;
//	result = sprite.constBuff->Map(0, nullptr, (void**)&constMap);
//	constMap->color = sprite.constBufferData.color;;
//	sprite.constBuff->Unmap(0, nullptr);
//
//	return sprite;
//}
//
//void SpriteManager::CommonInit(int blendID,D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType)
//{
//	//�n���ꂽ�f�[�^���ǂ��g�����̉��ߕ��@��GPU�ɓ`���邽�߂̂���
//	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
//		{	//���_���W
//			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
//		},
//		{	//�@���x�N�g��
//			"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
//		},
//		{	//uv���W
//			"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
//		}
//	};
//
//	//�V�F�[�_�[�ǂݍ���
//	ComPtr<ID3DBlob> vsBlob = nullptr;		//���_�V�F�[�_�I�u�W�F�N�g
//	ComPtr<ID3DBlob> psBlob = nullptr;		//�s�N�Z���V�F�[�_�I�u�W�F�N�g
//	ComPtr<ID3DBlob> errorBlob = nullptr;	//�G���[�I�u�W�F�N�g
//	//���_�V�F�[�_�[�̓ǂݍ��݃R���p�C��
//	HRESULT result = D3DCompileFromFile(
//		L"Resources/Shader/SpriteVS.hlsl",									//�V�F�[�_�[�t�@�C��
//		nullptr,
//		D3D_COMPILE_STANDARD_FILE_INCLUDE,					//�C���N���[�h�\�ɂ���
//		"main", "vs_5_0",									//�G���g���[�|�C���g���A�V�F�[�_�[���f������
//		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,	//�f�o�b�N�p�Œ�
//		0,
//		&vsBlob, &errorBlob
//	);
//
//	//�s�N�Z���V�F�[�_�[�̓ǂݍ��݂ƃR���p�C��
//	result = D3DCompileFromFile(
//		L"Resources/Shader/SpritePS.hlsl",									//�V�F�[�_�[�t�@�C����
//		nullptr,
//		D3D_COMPILE_STANDARD_FILE_INCLUDE,					//�C���N���[�h�\�ɂ���
//		"main", "ps_5_0",									//�G���g���[�|�C���g���A�V�F�[�_�[���f���Œ�
//		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,	//�f�o�b�N�p�Œ�
//		0,
//		&psBlob, &errorBlob
//	);
//
//	//�f�X�N���v�^�e�[�u���̐ݒ�
//	CD3DX12_DESCRIPTOR_RANGE descRangeCBV{}, descRangeSRV{};
//	descRangeCBV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);					//b0���W�X�^
//	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);					//t0���W�X�^
//
//	//���[�g�p�����[�^�[�̐ݒ�
//	CD3DX12_ROOT_PARAMETER rootparam[2]{};
//	//�萔�p
//	rootparam[0].InitAsDescriptorTable(1, &descRangeCBV, D3D12_SHADER_VISIBILITY_ALL);
//	//�e�N�X�`���p
//	rootparam[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);
//
//	//�O���t�B�b�N�X�p�C�v���C������
//	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
//	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
//	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
//	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;						//�W���ݒ�
//	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);		//�w�ʃJ�����O,�|���S�����h��Ԃ�,�[�x�N���b�s���O��L����
//	//gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
//	gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
//	gpipeline.BlendState.AlphaToCoverageEnable = true;
//
//	//�����_�[�^�[�Q�b�g�̃u�����h�ݒ�
//	D3D12_RENDER_TARGET_BLEND_DESC& blendDesc = gpipeline.BlendState.RenderTarget[0];
//	blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
//	blendDesc.BlendEnable = true;											//�u�����h��L���ɂ���
//	blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;							//���Z
//	blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;								//�\�[�X�̒l��100%�g��
//	blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;							//�f�X�g�̒l��0%�g��
//
//	switch (blendID) {
//	case bLEND_MODE_ADD:
//		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;									//���Z
//		blendDesc.SrcBlend = D3D12_BLEND_ONE;									//�\�[�X�̒l��100%�g��
//		blendDesc.DestBlend = D3D12_BLEND_ONE;									//�\�[�X�̒l��100%�g��
//		break;
//	case BLEND_MODE_ALPHA:
//		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;									//���Z
//		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;								//�\�[�X�̒l��100%�g��
//		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;						//�\�[�X�̒l��100%�g��
//		break;
//	default:
//		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;									//���Z
//		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;								//�\�[�X�̒l��100%�g��
//		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;						//�\�[�X�̒l��100%�g��
//	}
//
//	//���_���C�A�E�g�̐ݒ�
//	gpipeline.InputLayout.pInputElementDescs = inputLayout;
//	gpipeline.InputLayout.NumElements = _countof(inputLayout);
//
//	//�}�`�̌`����O�p�`�ɐݒ�
//	gpipeline.PrimitiveTopologyType = primitiveType;
//
//	//���̑��̐ݒ�
//	gpipeline.NumRenderTargets = 1;							//�`��Ώۂ�1��
//	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;	//0�`255�w���RGBA
//	gpipeline.SampleDesc.Count = 1;											//1�s�N�Z���ɂ�1��T���v�����O
//
//	//�f�v�X�X�e���V���X�e�[�g�̐ݒ�
//	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);//�[�x�e�X�g���s��,�������݋���,�[�x����������΍��i
//	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;
//
//	//�e�N�X�`���T���v���[�̃Z�b�g
//	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);
//
//	//���[�g�V�O�l�`���̐ݒ�
//	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
//	rootSignatureDesc.Init_1_0(_countof(rootparam), rootparam, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
//
//	ComPtr<ID3DBlob> rootSigBlob = {};
//	//�o�[�W������������ł̃V���A���C�Y
//	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
//	//���[�g�V�O�l�`���̐���
//	result = DirectXBase::dev->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootsignature));
//
//	//�p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
//	gpipeline.pRootSignature = rootsignature.Get();
//
//	result = DirectXBase::dev->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelinestate));
//
//}
//
//void SpriteManager::CommonDraw(D3D12_PRIMITIVE_TOPOLOGY topology)
//{
//	//�p�C�v���C���X�e�[�g�ݒ�R�}���h
//	DirectXBase::Instance()->cmdList->SetPipelineState(pipelinestate.Get());
//
//	//���[�g�V�O�l�`���ݒ�R�}���h
//	DirectXBase::Instance()->cmdList->SetGraphicsRootSignature(rootsignature.Get());
//
//	//�v���~�e�B�u�`��ݒ�R�}���h
//	DirectXBase::Instance()->cmdList->IASetPrimitiveTopology(topology);
//}
//
//void SpriteManager::Draw(Sprite& sprite)
//{
//	//��\����Ԃ�������`�揈�����s��Ȃ�
//	if (sprite.isDisplay == false) return;
//
//	//�萔�o�b�t�@�ւ̃f�[�^�]��
//	ConstBufferData* constMap = nullptr;
// 	HRESULT result = sprite.constBuff->Map(0, nullptr, (void**)&constMap);
//	constMap->color = sprite.constBufferData.color;
//	
//	//���[���h�s��̍X�V
//	if (sprite.projectionID == PROJECTIONID_UI)
//	{
//		constMap->mat.world = Camera::Instance()->matProjection;
//	}
//	else if (sprite.projectionID == PROJECTIONID_OBJECT)
//	{
//		XMMATRIX matWorld = XMMatrixIdentity();
//		matWorld *= sprite.matScale;
//		matWorld *= sprite.matRot;
//		matWorld *= sprite.matTrans;
//		constMap->mat.world = matWorld * Camera::matView * Camera::matPerspective;				//���[���h�ϊ� * �r���[�ϊ� * �������e�ϊ�
//		//constMap->mat.viewproj = matView * matProjection;
//	}
//	//�r���{�[�h�̏ꍇ
//	else if (sprite.projectionID == PROJECTIONID_BILLBOARD) {
//		//���_���W
//		XMVECTOR eyePosition = XMLoadFloat3(&Camera::Instance()->eye);
//		//�����_���W
//		XMVECTOR targetPosition = XMLoadFloat3(&Camera::Instance()->target);
//		//(����)�����
//		XMVECTOR upVector = XMLoadFloat3(&Camera::Instance()->up);
//		//�J����Z��
//		XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
//		//0�x�N�g�����ƌ�������܂�Ȃ��̂ŏ��O
//		assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
//		assert(!XMVector3IsInfinite(cameraAxisZ));
//		assert(!XMVector3Equal(upVector, XMVectorZero()));
//		assert(!XMVector3IsInfinite(upVector));
//		//�x�N�g���𐳋K��
//		cameraAxisZ = XMVector3Normalize(cameraAxisZ);
//		//�J������X������(�E����)
//		XMVECTOR cameraAxisX{};
//		//X���͏����->Z���̊O�ςŋ��܂�
//		cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
//		//�x�N�g���𐳋K��
//		cameraAxisX = XMVector3Normalize(cameraAxisX);
//		//�J������Y��(�����)
//		XMVECTOR cameraAxisY{};
//		//Y����Z��->X���̊O�ςŋ��߂�
//		cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);
//		//�x�N�g���𐳋K��
//		cameraAxisY = XMVector3Normalize(cameraAxisY);
//		//�J������]�s��
//		XMMATRIX matCameraRot;
//		//�J�������W�n->���[���h���W�n�̕Ԋҍs��
//		matCameraRot.r[0] = cameraAxisX;
//		matCameraRot.r[1] = cameraAxisY;
//		matCameraRot.r[2] = cameraAxisZ;
//		matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);
//		//�]�n�ɂ��t�s��(�t��])���v�Z
//		XMMATRIX matView = XMMatrixTranspose(matCameraRot);
//		//���_���W��-1�����������W
//		XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
//		//�J�����̈ʒu���烏�[���h���_�ւ̃x�N�g��(�J�������W�n)
//		XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);		//X����
//		XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);		//Y����
//		XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);		//Z����
//		//��̃x�N�g���ɂ܂Ƃ߂�
//		XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
//		//�r���[�s��ɕ��s�ړ�����ݒ�
//		matView.r[3] = translation;
//
//		//�r���{�[�h�s��
//		XMMATRIX billboardMat = XMMatrixIdentity();
//		billboardMat.r[0] = cameraAxisX;
//		billboardMat.r[1] = cameraAxisY;
//		billboardMat.r[2] = cameraAxisZ;
//		billboardMat.r[3] = XMVectorSet(0, 0, 0, 1);
//		//���[���h�s��̍X�V
//		XMMATRIX matWorld = XMMatrixIdentity();
//		matWorld *= billboardMat;
//		matWorld *= sprite.matScale;
//		matWorld *= sprite.matRot;
//		matWorld *= sprite.matTrans;
//		constMap->mat.world = matWorld * matView * Camera::Instance()->matPerspective;												//���[���h�ϊ� * �r���[�ϊ� * �������e�ϊ�
//		//constMap->mat.viewproj = 
//	}
//	sprite.constBuff->Unmap(0, nullptr);
//
//	//�f�B�X�N���v�^�q�[�v�ݒ�R�}���h
//	ID3D12DescriptorHeap* ppHeaps[] = { sprite.constDescHeap.Get() };
//	DirectXBase::Instance()->cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
//
//	//�萔�o�b�t�@�r���[�ݒ�R�}���h
//	D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandle;
//	gpuDescHandle = sprite.constDescHeap->GetGPUDescriptorHandleForHeapStart();
//	//gpuDescHandle.ptr += DirectXBase::Instance()->dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
//	DirectXBase::Instance()->cmdList->SetGraphicsRootDescriptorTable(0, gpuDescHandle);
//
//	//�f�B�X�N���v�^�q�[�v�ݒ�R�}���h
//	ID3D12DescriptorHeap* ppHeaps2[] = { TextureManager::Instance()->GetDescHeap().Get() };
//	DirectXBase::Instance()->cmdList->SetDescriptorHeaps(_countof(ppHeaps2), ppHeaps2);
//	
//	//�V�F�[�_�[���\�[�X�r���[�ݒ�R�}���h
//	DirectXBase::Instance()->cmdList->SetGraphicsRootDescriptorTable(1, TextureManager::Instance()->GetSRV(sprite.textureIDnum));
//	
//
//	//���_�o�b�t�@�r���[�ݒ�R�}���h
//	DirectXBase::Instance()->cmdList->IASetVertexBuffers(0, 1, &sprite.vbView);
//
//	DirectXBase::Instance()->cmdList->DrawInstanced(sprite.vertices.size(), 1, 0, 0);
//}
//
//void SpriteManager::ChangeScale(Sprite& sprite, XMFLOAT3 scale)
//{
//	sprite.matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
//}
//
//void SpriteManager::ChangeRotation(Sprite& sprite, XMFLOAT3 rotation)
//{
//	XMMATRIX mat = XMMatrixIdentity();
//	mat *= XMMatrixRotationZ(rotation.z);
//	mat *= XMMatrixRotationX(rotation.x);
//	mat *= XMMatrixRotationY(rotation.y);
//	sprite.matRot = mat * sprite.matRot;
//}
//
//void SpriteManager::ChangePosition(Sprite& sprite, XMFLOAT3 position)
//{
//	sprite.matTrans = XMMatrixTranslation(position.x, position.y, position.z);
//	sprite.pos = XMFLOAT3(sprite.matTrans.r[3].m128_f32[0], sprite.matTrans.r[3].m128_f32[1], sprite.matTrans.r[3].m128_f32[2]);
//}
//
//void SpriteManager::ChangePositionAdd(Sprite& sprite, XMFLOAT3 position)
//{
//	sprite.matTrans *= XMMatrixTranslation(position.x, position.y, position.z);
//	sprite.pos = XMFLOAT3(sprite.matTrans.r[3].m128_f32[0], sprite.matTrans.r[3].m128_f32[1], sprite.matTrans.r[3].m128_f32[2]);
//}