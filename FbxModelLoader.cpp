#include "FbxModelLoader.h"
#include "struct.h"
#include <list>
//�ÓI�����o�ϐ��̎���
const string FbxModelLoader::baseDirectory = "Resources/";
const string FbxModelLoader::defaultTextureFileName = "white1x1.png";


FbxModelLoader::FbxModelLoader()
{
}

void FbxModelLoader::Init(ComPtr<ID3D12Device> dev)
{
	//�ď������`�F�b�N
	assert(fbxManager == nullptr);
	//�������烁���o�ϐ��ɑ��
	this->dev = dev;
	//FBX�}�l�[�W���[�̐���
	fbxManager = FbxManager::Create();
	//FBX�}�l�[�W���[�̓��o�͐ݒ�
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);
	//FBX�C���|�[�^�[�̐���
	fbxImporter = FbxImporter::Create(fbxManager, "");
}

void FbxModelLoader::Fainalize()
{
	//�e��FBX�C���X�^���X�̔j��
	fbxManager->Destroy();
	fbxImporter->Destroy();
}

FbxModel* FbxModelLoader::LoadModelFromFile(const string& modelName)
{
	//���f���Ɠ������O�̃t�H���_����ǂݍ���
	const string directoryPath = baseDirectory + modelName + "/";
	//�g���qfbx��t�^
	const string fileName = modelName + ".fbx";
	//�A�����ăt���p�X�𓾂�
	const string fullpath = directoryPath + fileName;

	//�t�@�C�������w�肵��FBX�t�@�C����ǂݍ���
	if (!fbxImporter->Initialize(fullpath.c_str(), -1, fbxManager->GetIOSettings()))
	{
		assert(0);
	}
	//�V�[������
	FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxScene");

	//�t�@�C�����烍�[�h����FBX�̏����V�[���ɃC���|�[�g
	fbxImporter->Import(fbxScene);

	//���f������
	FbxModel* model = new FbxModel();
	model->name = modelName;

	//FBX�m�[�h�̐����擾
	int nodeCount = fbxScene->GetNodeCount();
	
	//���炩���ߕK�v�����̃��������l�����邱�ƂŁA�A�h���X�������̂�\�h
	model->nodes.reserve(nodeCount);

	//���[�g�m�[�h���珇�ɉ�͂��ă��f���ɗ�������
	ParseNodeRecursive(model, fbxScene->GetRootNode());

	//FbxScene�J��
	//fbxScene->Destroy();
	model->fbxScene = fbxScene;

	//�o�b�t�@����
	model->CreateBuffers(dev);

	return model;
}

void FbxModelLoader::ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode, Node* parent)
{
	//�m�[�h�����擾
	string name = fbxNode->GetName();
	//���f���Ƀm�[�h��ǉ�
	model->nodes.emplace_back();
	Node& node = model->nodes.back();
	//�m�[�h�����擾
	node.name = fbxNode->GetName();

	//FBX�m�[�h�̏�����͂��ăm�[�h�ɋL�^
	
	//FBX�m�[�h�̃��[�J���ړ����
	FbxDouble3 rotation = fbxNode->LclRotation.Get();
	FbxDouble3 scaling = fbxNode->LclScaling.Get();
	FbxDouble3 translation = fbxNode->LclTranslation.Get();

	//�`���ϊ����đ��
	node.rotation = { (float)rotation[0],(float)rotation[1],(float)rotation[2],0.0f };
	node.scaling= { (float)scaling[0],(float)scaling[1],(float)scaling[2],0.0f };
	node.translation= { (float)translation[0],(float)translation[1],(float)translation[2],0.0f };

	//��]�p��x���@����ʓx�@�ɕύX
	node.rotation.m128_f32[0] = XMConvertToRadians(node.rotation.m128_f32[0]);
	node.rotation.m128_f32[1] = XMConvertToRadians(node.rotation.m128_f32[1]);
	node.rotation.m128_f32[2] = XMConvertToRadians(node.rotation.m128_f32[2]);

	//�X�P�[���A��]�A���s�ړ��s��̌v�Z
	XMMATRIX matScaling, matRotation, matTranslation;
	matScaling = XMMatrixScalingFromVector(node.scaling);
	matRotation = XMMatrixRotationRollPitchYawFromVector(node.rotation);
	matTranslation = XMMatrixTranslationFromVector(node.translation);

	//���[�J���ό`�s��̌v�Z
	node.transform = XMMatrixIdentity();
	node.transform *= matScaling;
	node.transform *= matRotation;
	node.transform *= matTranslation;

	//�O���[�o���ϊ��s��̌v�Z
	node.globalTransform = node.transform;
	if (parent) {
		node.parent = parent;
		//�e�̕ό`����Z
		node.globalTransform *= parent->globalTransform;
	}

	//FBX�m�[�h�̃��b�V���������
	FbxNodeAttribute* fbxNodeAttribute = fbxNode->GetNodeAttribute();

	if (fbxNodeAttribute) {
		if (fbxNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh) {
			model->meshNode = &node;
			ParseMesh(model, fbxNode);
		}
	}

	//�q�m�[�h�ɑ΂��čċA�Ăяo��
	for (int i = 0; i < fbxNode->GetChildCount(); i++)
	{
		ParseNodeRecursive(model, fbxNode->GetChild(i), &node);
	}
}

void FbxModelLoader::ParseMesh(FbxModel* model, FbxNode* fbxNode)
{
	//�m�[�h�̃��b�V�����擾
	FbxMesh* fbxMesh = fbxNode->GetMesh();

	//���_���W�ǂݎ��
	ParseMeshVertices(model, fbxMesh);

	//�ʂ��\������f�[�^�̓ǂݎ��
	ParseMeshFaces(model, fbxMesh);

	//�}�e���A���̓ǂݎ��
	ParseMaterial(model, fbxNode);

	//�X�L�j���O���ǂݎ��(�o�O����܂ŃR�����g�A�E�g)
	ParceSkin(model, fbxMesh);
}

void FbxModelLoader::ParseMeshVertices(FbxModel* model, FbxMesh* fbxMesh)
{
	auto& vertices = model->vertices;

	//���_�f�[�^�̐�
	const int controlPointCount = fbxMesh->GetControlPointsCount();
	//�K�v���������_�f�[�^�z����m��
	FbxModel::VertexFbx vert{};
	model->vertices.resize(controlPointCount, vert);

	//FBX���b�V���̒��_���W�z����擾
	FbxVector4* pCoord = fbxMesh->GetControlPoints();
	//FBX���b�V���̑S���_���W�����f�����̔z��ɃR�s�[����
	for (int i = 0;i < controlPointCount; i++) {
		FbxModel::VertexFbx& vertex = vertices[i];
		//���W�̃R�s�[
		vertex.pos.x = (float)pCoord[i][0];
		vertex.pos.y = (float)pCoord[i][1];
		vertex.pos.z = (float)pCoord[i][2];
	}
}

void FbxModelLoader::ParseMeshFaces(FbxModel* model, FbxMesh* fbxMesh)
{
	auto& vertices = model->vertices;
	auto& indices = model->indices;

	//1�t�@�C���ɕ����̃��b�V���̃��f���͔�Ή�
	assert(indices.size() == 0);
	//�ʂ̐�
	const int polygonCount = fbxMesh->GetPolygonCount();
	//UV�f�[�^�̐�
	const int textureUVCount = fbxMesh->GetTextureUVCount();
	//UV�����X�g
	FbxStringList uvNames;
	fbxMesh->GetUVSetNames(uvNames);

	//�ʂ��Ƃ̏��ǂݎ��
	for (int i = 0; i < polygonCount; i++) {
		//�ʂ��\�����钸�_�̐����擾(3�Ȃ�O�p�`�|���S��)
		const int polygonSize = fbxMesh->GetPolygonSize(i);
		assert(polygonSize <= 4);

		//�P���_������
		for (int j = 0; j < polygonSize; j++) {
			int index = fbxMesh->GetPolygonVertex(i, j);
			assert(index >= 0);

			//���_�@���ǂݍ���
			FbxModel::VertexFbx& vertex = vertices[index];
			FbxVector4 normal;
			if (fbxMesh->GetPolygonVertexNormal(i, j, normal))
			{
				vertex.normal.x = (float)normal[0];
				vertex.normal.y = (float)normal[1];
				vertex.normal.z = (float)normal[2];
			}
			//�e�N�X�`��UV�ǂݍ���
			if (textureUVCount > 0) {
				FbxVector2 uvs;
				bool lUnmappedUV;
				//0�Ԍ��ߑł��œǂݍ���
				if (fbxMesh->GetPolygonVertexUV(i, j, uvNames[0], uvs, lUnmappedUV)) {
					vertex.uv.x = (float)uvs[0];
					vertex.uv.y = (float)uvs[1];
				}
			}

			//�C���f�b�N�X�z��ɒ��_�C���f�b�N�X�ǉ�
			//3���_�ڂ܂łȂ�
			if (j < 3) {
				//1�_�ǉ����A�ق���2�_�ƎO�p�`���\�z����
				indices.push_back(index);
			}
			//4���_��
			else {
				//3�_�ǉ����A
				//�l�p�`��,1,2,3�̓� 2,3,0�ŎO�p�`���\�z����
				int index2 = indices[indices.size() - 1];
				int index3 = index;
				int index0 = indices[indices.size() - 3];
				indices.push_back(index2);
				indices.push_back(index3);
				indices.push_back(index0);
			}
		}
	}
}

void FbxModelLoader::ParseMaterial(FbxModel* model, FbxNode* fbxNode)
{
	const int materialCount = fbxNode->GetMaterialCount();
	if (materialCount > 0) {
		//�擪�̃}�e���A�����擾
		FbxSurfaceMaterial* material = fbxNode->GetMaterial(0);
		//�e�N�X�`����ǂݍ��񂾂��ǂ�����\���t���O
		bool textureLoaded = false;

		if (material) {
			//FbxSurfaceLambert�N���X���ǂ����𒲂ׂ�
			if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
			{
				FbxSurfaceLambert* lambert = static_cast<FbxSurfaceLambert*>(material);

				//�����W��
				FbxPropertyT<FbxDouble3> ambient = lambert->Ambient;
				model->ambient.x = (float)ambient.Get()[0];
				model->ambient.y = (float)ambient.Get()[1];
				model->ambient.z = (float)ambient.Get()[2];

				//�g�U���ˌ��W��
				FbxPropertyT<FbxDouble3> diffuse = lambert->Diffuse;
				model->diffuse.x = (float)diffuse.Get()[0];
				model->diffuse.y = (float)diffuse.Get()[1];
				model->diffuse.z = (float)diffuse.Get()[2];

				//�f�B�t���[�Y�e�N�X�`�������o��
				const FbxProperty diffuseProperty = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
				if (diffuseProperty.IsValid())
				{
					const FbxFileTexture* texture = diffuseProperty.GetSrcObject<FbxFileTexture>();
					if (texture)
					{
						const char* filepath = texture->GetFileName();
						//�t�@�C���p�X����t�@�C�������o
						string path_str(filepath);
						string name = ExtractFileName(path_str);
						//�e�N�X�`���ǂݍ���
						LoadTexture(model, baseDirectory + model->name + "/" + name);
						textureLoaded = true;
					}
				}

			}
		}

		//�e�Ns�����Ȃ��ꍇ�͔��e�N�X�`���𒣂�
		if (!textureLoaded) {
			LoadTexture(model, baseDirectory + defaultTextureFileName);
		}
	}
}

void FbxModelLoader::LoadTexture(FbxModel* model, string& fileName)
{
	HRESULT result = S_FALSE;
	//WIC�e�N�X�`���̃��[�h
	TexMetadata& metadata = model->metadata;
	ScratchImage& scratchImg = model->scratchImg;
	//���j�R�[�h������ɕϊ�
	wchar_t wfilepath[128];
	MultiByteToWideChar(CP_ACP, 0, fileName.c_str(), -1, wfilepath, _countof(wfilepath));
	result = LoadFromWICFile(wfilepath, WIC_FLAGS_NONE, &metadata, scratchImg);
	if (FAILED(result)) {
		assert(0);
	}
}

void FbxModelLoader::ParceSkin(FbxModel* model, FbxMesh* fbxMesh)
{
	//�X�L�j���O���
	FbxSkin* fbxSkin = static_cast<FbxSkin*>(fbxMesh->GetDeformer(0, FbxDeformer::eSkin));
	//�X�L�j���O��񂪂Ȃ���ΏI��
	if (fbxSkin == nullptr) {
		//�e���_�ɂ��ď���
		for (int i = 0; i < model->vertices.size(); i++) {
			//�ŏ��̃{�[���̉e��100���ɂ���
			model->vertices[i].boneIndex[0] = 0;
			model->vertices[i].boneWeight[0] = 1.0f;
		}
		return;
	}

	//�{�[���z��̎Q��
	vector<FbxModel::Bone>& bones = model->bones;

	//�{�[���̐�
	int clusterCount = fbxSkin->GetClusterCount();
	bones.reserve(clusterCount);

	//�S�Ẵ{�[���ɂ���
	for (int i = 0; i < clusterCount; i++) {
		//FBX�{�[�����
		FbxCluster* fbxCluster = fbxSkin->GetCluster(i);

		//�{�[�����̂̃m�[�h�̖��O���擾
		const char* boneName = fbxCluster->GetLink()->GetName();

		//�V�����{�[����ǉ����A�ǉ������{�[���̎Q�Ƃ𓾂�
		bones.emplace_back(FbxModel::Bone(boneName));
		FbxModel::Bone& bone = bones.back();
		//����{�[����FBX�̃{�[����R�Â���
		bone.fbxCluster = fbxCluster;
		//FBX���珉���p���s����擾����
		FbxAMatrix fbxMat;
		fbxCluster->GetTransformLinkMatrix(fbxMat);

		//XMMATRIX�^�ɕϊ�����
		XMMATRIX initialPose;
		ConvertMatrixFromFbx(&initialPose, fbxMat);

		//�����p���s��̋t�s��𓾂�
		bone.invInitialPose = XMMatrixInverse(nullptr, initialPose);

		//�{�[���ԍ��ƃX�L���E�F�C�g�̃y�A
		struct WeightSet {
			UINT index;
			float weight;
		};

		//�񎟌��z��(�W���O�z��)
		//list:���_���e�����󂯂�{�[���̑S���X�g
		//vector:�����S���_��
		vector<list<WeightSet>>weightLists(model->vertices.size());

		//�S�Ẵ{�[���ɂ���
		for (int i = 0; i < clusterCount; i++) {
			//FBX�{�[�����
			FbxCluster* fbxCluster = fbxSkin->GetCluster(i);
			//���̃{�[���ɉe�����󂯂钸�_�̐�
			int controlPointIndicesCount = fbxCluster->GetControlPointIndicesCount();
			//���̃{�[���ɉe�����󂯂钸�_�̔z��
			int* controlPointIndices = fbxCluster->GetControlPointIndices();
			double* controlPointWeight = fbxCluster->GetControlPointWeights();

			//�e�����󂯂�S���_�ɂ���
			for (int j = 0; j < controlPointIndicesCount; j++) {
				//���_�ԍ�
				int vertIndex = controlPointIndices[j];
				//�X�L���E�F�C�g
				float weight = (float)controlPointWeight[j];
				//���̒��_�̉e�����󂯂�{�[�����X�g�ɁA�{�[���ƃE�F�C�g�̃y�A��ǉ�
				weightLists[vertIndex].emplace_back(WeightSet{ (UINT)i,weight });
			}
		}

		//���_�z�񏑂������p�̎Q��
		auto& vertices = model->vertices;
		//�e���_�ɂ��ď���
		for (int i = 0; i < vertices.size(); i++) {
			//���_�̃E�F�C�g����ł��傫��4��I��
			auto& weightList = weightLists[i];
			//��ؔ�v�p�̃����_�����w�肵�č~���Ƀ\�[�g
			weightList.sort(
				[](auto const& lhs, auto const& rhs) {
					//���̗v�f�̕����傫�����rue�A�����łȂ����false
					return lhs.weight > rhs.weight;
				}
			);

			int weightArrayIndex = 0;
			//�~���\�[�g�ς݂̃E�F�C�g���X�g����
			for (auto& weightSet : weightList) {
				//���_�f�[�^�ɏ�������
				vertices[i].boneIndex[weightArrayIndex] = weightSet.index;
				vertices[i].boneWeight[weightArrayIndex] = weightSet.weight;
				//4�ɒB������C��
				if (++weightArrayIndex >= FbxModel::MAX_BONE_INDICES) {
					float weight = 0.0f;
					//2�Ԗڈȍ~�̃E�F�C�g�����v
					for (int j = 0; j < FbxModel::MAX_BONE_INDICES; j++) {
						weight += vertices[i].boneWeight[j];
					}
					//���v��1.0f(100%)�ɂȂ�悤�ɒ���
					vertices[i].boneWeight[0] = 1.0f - weight;
					break;
				}

			}
		}
	}
}

string FbxModelLoader::ExtractFileName(const string& path)
{
	size_t pos1;
	//��؂蕶��'\\'���o�Ă����ԍŌ�̕���������
	pos1 = path.rfind('\\');
	if (pos1 != string::npos) {
		return path.substr(pos1 + 1, path.size() - pos1 - 1);
	}
	//��؂蕶��'/'���o�Ă����ԍŌ�̕���������
	pos1 = path.rfind('/');
	if (pos1 != string::npos) {
		return path.substr(pos1 + 1, path.size() - pos1 - 1);
	}

	return path;
}

void FbxModelLoader::ConvertMatrixFromFbx(XMMATRIX* dst, const FbxAMatrix& src)
{
	//�s
	for (int i = 0; i < 4; i++) {
		//��
		for (int j = 0; j < 4; j++) {
			dst->r[i].m128_f32[j] = (float)src.Get(i, j);
		}
	}
}