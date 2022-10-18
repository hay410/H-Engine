#include "ModelLoader.h"
#include "Fbxsdk.h"
#include <sstream>
#include <fstream>
#include <memory>

vector<ModelData> ModelLoader::modelData{};

//void ModelLoader::LoadFbx(const char* fbxFileName, ObjectData& objectBuffer)
//{
//	//fbx�t�@�C�������[�h�ς݂��ǂ���
//	bool isLoad = false;
//	//���[�h�ς݂������ꍇ�A���Ԗڂ̗v�f�ɕۑ�����Ă���̂����擾����ϐ�
//	int dataNumber = 0;
//
//	for (int i = 0; i < ModelLoader::modelData.size(); ++i) {
//		if (modelData.at(i).modelName == fbxFileName) {
//			isLoad = true;
//			dataNumber = i;
//			break;
//		}
//	}
//
//	//fbx�t�@�C���������[�h�������烍�[�h����
//	if (isLoad == false) {
//		ModelLoader::modelData.push_back({});
//		ModelLoader::modelData.at(ModelLoader::modelData.size() - 1).modelName = fbxFileName;
//
//		//FbxManager�쐬			FbxImport��FbxScene���쐬���邽�߂ɕK�v�ȊǗ��N���X
//		FbxManager* fbx_manager = FbxManager::Create();
//
//		//FbxImporter�쐬		Fbx�t�@�C����Import���邽�߂̃p�[�T�[�N���X�B���̃N���X�Ńt�@�C���̎��f�[�^�����b�V����J�����Ȃǂ̏��ɕ������Ă����B
//		FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "ImportTest");
//
//		//FbxScene�쐬			�������ꂽFbx�̃f�[�^��ۑ����邽�߂̃N���X
//		FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "SceneTest");
//
//		//�t�@�C��������������		�t�@�C�������[�h
//		if (fbx_importer->Initialize(fbxFileName) == false)
//		{
//			fbx_importer->Destroy();
//			fbx_scene->Destroy();
//			fbx_manager->Destroy();
//
//			//���������s
//			return;
//		}
//
//		//�C���|�[�g				Import�ɓ����Ă��錳�f�[�^�𕪉������f�[�^��scene�ɓ����B��������������̂Ŕ��ɏ������d���B
//		if (fbx_importer->Import(fbx_scene) == false)
//		{
//			fbx_importer->Destroy();
//			fbx_scene->Destroy();
//			fbx_manager->Destroy();
//
//			//�C���|�[�g���s
//			return;
//		}
//
//		//���[�g�m�[�h���擾		�f�[�^�𒲂ׂ鎞�A���[�g�m�[�h���擾����ΑS�Ẵf�[�^�ɂ��ǂ蒅�����Ƃ��ł���B
//		FbxNode* root_node = fbx_scene->GetRootNode();
//
//		FbxGeometryConverter converter(fbx_manager);
//		//�|���S�����O�p�`�ɂ���		���̏����͏d���B
//		converter.Triangulate(fbx_scene, true);
//
//		//�SMesh����
//		bool i = converter.SplitMeshesPerMaterial(fbx_scene, true);
//
//		//���b�V��Node��T��		���_�Ɩ@���̃f�[�^���܂܂�Ă���eMesh��T��
//		vector<pair<string, FbxMesh*>> meshList;
//		CollectMeshNode(fbx_scene->GetRootNode(), meshList);
//
//		//���_�C���f�b�N�X�̐ݒ�		�|���S���̐������A�ԂƂ��ĕۑ�����
//		int polygonCount = 0;	//�܂��܂ł̃|���S������ۑ�����
//		for (int i = 0; i < meshList.size(); ++i) {
//			int* indices = meshList.at(i).second->GetPolygonVertices();
//			int vertexCount = meshList.at(i).second->GetPolygonCount();
//			for (int k = 0; k < vertexCount; k++)
//			{
//				//2 => 1 => 0�ɂ��Ă�͍̂���n�΍�
//				ModelLoader::modelData.at(ModelLoader::modelData.size() - 1).index.push_back(k * 3 + 2);
//				ModelLoader::modelData.at(ModelLoader::modelData.size() - 1).index.push_back(k * 3 + 1);
//				ModelLoader::modelData.at(ModelLoader::modelData.size() - 1).index.push_back(k * 3);
//
//				//���ł�proSprite�ɂ��l������
//				objectBuffer.index.push_back(k * 3 + 2);
//				objectBuffer.index.push_back(k * 3 + 1);
//				objectBuffer.index.push_back(k * 3);
//			}
//			polygonCount += vertexCount;
//		}
//
//		//���_�̐ݒ�
//		for (int i = 0; i < meshList.size(); ++i) {
//			//���_�o�b�t�@���擾
//			FbxVector4* vertices = meshList.at(i).second->GetControlPoints();
//			//���_���W�̐��̎擾
//			int polygon_vertex_count = meshList.at(i).second->GetPolygonVertexCount();
//			//���_�C���f�b�N�X�o�b�t�@�̎擾
//			int* indices = meshList.at(i).second->GetPolygonVertices();
//			//uvset�̖��O�ۑ��p
//			FbxStringList uvset_names;
//			//UVSet�̖��O���X�g���擾
//			meshList.at(i).second->GetUVSetNames(uvset_names);
//			FbxArray<FbxVector2> uv_buffer;
//			//UVSet�̖��O����UVSet���擾����
//			//����̓V���O���Ȃ̂ōŏ��̖��O���g��
//			meshList.at(i).second->GetPolygonVertexUVs(uvset_names.GetStringAt(0), uv_buffer);
//			//�@�����X�g�̎擾
//			FbxArray<FbxVector4> normals;
//			meshList.at(i).second->GetPolygonVertexNormals(normals);
//
//			for (int j = 0; j < polygon_vertex_count; j++)
//			{
//				int index = indices[j];
//				Vertex vertex{};
//				//���_�̐ݒ�
//				XMFLOAT3 pos{};
//				pos.x = (float)-vertices[index][0];
//				pos.y = (float)vertices[index][1];
//				pos.z = (float)vertices[index][2];
//				XMVECTOR a = XMVector3Transform(XMLoadFloat3(&pos), XMMatrixRotationX(XM_PIDIV2));
//				XMStoreFloat3(&vertex.pos, a);
//				//vertex.pos = pos;
//				//�@���̐ݒ�
//				XMFLOAT3 normal{};
//				normal.x = -normals[j][0];
//				normal.y = normals[j][1];
//				normal.z = normals[j][2];
//				vertex.normal = normal;
//				//uv�̐ݒ�
//				XMFLOAT2 uv{};
//				uv.x = uv_buffer[j][0];
//				uv.y = -uv_buffer[j][1];
//				vertex.uv = uv;
//				ModelLoader::modelData.at(ModelLoader::modelData.size() - 1).vertex.push_back(vertex);
//				//���ł�proSprite�ɂ��l������
//				objectBuffer.vertex.push_back(vertex);
//			}
//		}
//		return;
//	}
//
//	//fbx�̃f�[�^��proSprite�ɓ����
//	for (int i = 0; i < modelData.at(dataNumber).index.size(); ++i) {
//		objectBuffer.index.push_back(modelData.at(dataNumber).index.at(i));
//	}
//	for (int i = 0; i < modelData.at(dataNumber).vertex.size(); ++i) {
//		objectBuffer.vertex.push_back(modelData.at(dataNumber).vertex.at(i));
//	}
//}

void ModelLoader::LoadObj(string directoryPath, string fileName, ObjectData& objectBuffer, bool isSmoothing)
{
	//obj�t�@�C�������[�h�ς݂��ǂ���
	bool isLoad = false;
	//���[�h�ς݂������ꍇ�A���Ԗڂ̗v�f�ɕۑ�����Ă���̂����擾����ϐ�
	int dataNumber = 0;

	for (int i = 0; i < ModelLoader::modelData.size(); ++i) {
		if (modelData.at(i).modelName == directoryPath + fileName && modelData.at(i).isSmoothing == isSmoothing) {
			isLoad = true;
			dataNumber = i;
			break;
		}
	}

	//obj�t�@�C���������[�h�������烍�[�h����
	if (isLoad == false) {
		//�������_���w�������Ă��钸�_�C���f�b�N�X��ۑ����Ă������߂̃}�b�v
		map<unsigned short, vector<unsigned short>> smoothData;

		modelData.push_back({});
		ModelLoader::modelData.at(ModelLoader::modelData.size() - 1).modelName = directoryPath + fileName;
		ModelLoader::modelData.at(ModelLoader::modelData.size() - 1).isSmoothing = isSmoothing;

		//�t�B���X�g���[��
		ifstream file;
		//.obj�t�@�C�����J��
		file.open(directoryPath + fileName);
		//�t�@�C���I�[�v�����s���`�F�b�N
		if (file.fail()) {
			//assert(0);
		}
		//��s���ǂݍ���
		string line;
		vector<XMFLOAT3> position;	//���W��ۑ����Ă���
		vector<XMFLOAT2> uv;		//uv��ۑ����Ă���
		vector<XMFLOAT3> normal;	//�@���x�N�g����ۑ����Ă���
		vector<unsigned short> index;
		while (getline(file, line)) {
			//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
			istringstream lineStream(line);
			//���p�X�y�[�X��؂�ōs�̐擪�������擾
			string key;
			getline(lineStream, key, ' ');

			//�擪������v�Ȃ璸�_���W
			if (key == "v") {
				//X,Y,Z���W�ǂݍ���
				XMFLOAT3 pos{};
				lineStream >> pos.x;
				lineStream >> pos.y;
				lineStream >> pos.z;
				//���W����U�ۑ�
				position.push_back(pos);
			}
			//�擪������vt�Ȃ�e�N�X�`��
			if (key == "vt") {
				//U,V�����ǂݍ���
				XMFLOAT2 texcoord{};
				lineStream >> texcoord.x;
				lineStream >> texcoord.y;
				//V�������]
				texcoord.y = 1.0f - texcoord.y;
				//�e�N�X�`�����W�f�[�^�ɒǉ�
				uv.push_back(texcoord);
			}
			//�擪������vn�Ȃ�@���x�N�g��
			if (key == "vn") {
				//X,Y,Z�����ǂݍ���
				XMFLOAT3 norm{};
				lineStream >> norm.x;
				lineStream >> norm.y;
				lineStream >> norm.z;
				//�@���x�N�g���f�[�^�ɒǉ�
				normal.push_back(norm);
			}
			//�擪������f�Ȃ�|���S��(�O�p�`)
			if (key == "f") {
				//���p�X�y�[�X��؂�ōs�̑�����ǂݍ���
				string indexString;
				unsigned short indexPosition;		//�󂯎M
				unsigned short indexNormal;			//�󂯎M
				unsigned short indexTexcoord;		//�󂯎M
				while (getline(lineStream, indexString, ' ')) {
					//���_�C���f�b�N�X����̕�������X�g���[���ɕϊ����ĉ�͂��₷������
					istringstream indexStream(indexString);
					indexStream >> indexPosition;
					indexStream.seekg(1, ios_base::cur);	//�X���b�V�����΂�
					indexStream >> indexTexcoord;
					indexStream.seekg(1, ios_base::cur);	//�X���b�V�����΂�
					indexStream >> indexNormal;
					//���_�f�[�^�̒ǉ�
					Vertex vert{};
					vert.pos = position[indexPosition - 1];
					vert.normal = normal[indexNormal - 1];
					vert.uv = uv[indexTexcoord - 1];
					//���f���f�[�^�ɒǉ�
					modelData.at(modelData.size() - 1).vertex.push_back(vert);
					modelData.at(modelData.size() - 1).index.push_back(modelData.at(modelData.size() - 1).index.size());
					//proSprite�ɂ��ǉ�
					objectBuffer.vertex.push_back(vert);
					objectBuffer.index.push_back(objectBuffer.index.size());
					//isSmoothing��true�Ȃ璸�_����ǉ�����
					if (isSmoothing == true) {
						smoothData[indexPosition].push_back(objectBuffer.vertex.size() - 1);
					}
				}
			}
			//�擪������mtllib�Ȃ�}�e���A��
			if (key == "mtllib") {
				//�}�e���A���̃t�@�C�����ǂݍ���
				string materialFileName;
				lineStream >> materialFileName;
				//�}�e���A���̓ǂݍ���
				LoadObjMaterial(directoryPath + materialFileName, modelData.at(modelData.size() - 1), objectBuffer);
			}
		}
		//�t�@�C�������
		file.close();

		//isSmoothing��true��������@�������Ȃ߂炩�ɂ���
		if (isSmoothing == true) {
			CalculateSmoothedVertexNormals(smoothData, objectBuffer, modelData.at(modelData.size() - 1));
		}

		return;
	}

	//obj�̃f�[�^��proSprite�ɓ����
	for (int i = 0; i < modelData.at(dataNumber).index.size(); ++i) {
		objectBuffer.index.push_back(modelData.at(dataNumber).index.at(i));
	}
	for (int i = 0; i < modelData.at(dataNumber).vertex.size(); ++i) {
		objectBuffer.vertex.push_back(modelData.at(dataNumber).vertex.at(i));
	}
	objectBuffer.constBufferDataB1.alpha = 1;
	objectBuffer.constBufferDataB1.ambient = modelData.at(dataNumber).material.ambient;
	objectBuffer.constBufferDataB1.diffuse = modelData.at(dataNumber).material.diffuse;
	objectBuffer.constBufferDataB1.specular = modelData.at(dataNumber).material.specular;
}

//void ModelLoader::LoadObj(string directoryPath, string fileName, Object3DShadow& objectBuffer, bool isSmoothing)
//{
//	//obj�t�@�C�������[�h�ς݂��ǂ���
//	bool isLoad = false;
//	//���[�h�ς݂������ꍇ�A���Ԗڂ̗v�f�ɕۑ�����Ă���̂����擾����ϐ�
//	int dataNumber = 0;
//
//	for (int i = 0; i < ModelLoader::modelData.size(); ++i) {
//		if (modelData.at(i).modelName == directoryPath + fileName && modelData.at(i).isSmoothing == isSmoothing) {
//			isLoad = true;
//			dataNumber = i;
//			break;
//		}
//	}
//
//	//obj�t�@�C���������[�h�������烍�[�h����
//	if (isLoad == false) {
//		//�������_���w�������Ă��钸�_�C���f�b�N�X��ۑ����Ă������߂̃}�b�v
//		map<unsigned short, vector<unsigned short>> smoothData;
//
//		modelData.push_back({});
//		ModelLoader::modelData.at(ModelLoader::modelData.size() - 1).modelName = directoryPath + fileName;
//		ModelLoader::modelData.at(ModelLoader::modelData.size() - 1).isSmoothing = isSmoothing;
//
//		//�t�B���X�g���[��
//		ifstream file;
//		//.obj�t�@�C�����J��
//		file.open(directoryPath + fileName);
//		//�t�@�C���I�[�v�����s���`�F�b�N
//		if (file.fail()) {
//			assert(0);
//		}
//		//��s���ǂݍ���
//		string line;
//		vector<XMFLOAT3> position;	//���W��ۑ����Ă���
//		vector<XMFLOAT2> uv;		//uv��ۑ����Ă���
//		vector<XMFLOAT3> normal;	//�@���x�N�g����ۑ����Ă���
//		vector<unsigned short> index;
//		while (getline(file, line)) {
//			//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
//			istringstream lineStream(line);
//			//���p�X�y�[�X��؂�ōs�̐擪�������擾
//			string key;
//			getline(lineStream, key, ' ');
//
//			//�擪������v�Ȃ璸�_���W
//			if (key == "v") {
//				//X,Y,Z���W�ǂݍ���
//				XMFLOAT3 pos{};
//				lineStream >> pos.x;
//				lineStream >> pos.y;
//				lineStream >> pos.z;
//				//���W����U�ۑ�
//				position.push_back(pos);
//			}
//			//�擪������vt�Ȃ�e�N�X�`��
//			if (key == "vt") {
//				//U,V�����ǂݍ���
//				XMFLOAT2 texcoord{};
//				lineStream >> texcoord.x;
//				lineStream >> texcoord.y;
//				//V�������]
//				texcoord.y = 1.0f - texcoord.y;
//				//�e�N�X�`�����W�f�[�^�ɒǉ�
//				uv.push_back(texcoord);
//			}
//			//�擪������vn�Ȃ�@���x�N�g��
//			if (key == "vn") {
//				//X,Y,Z�����ǂݍ���
//				XMFLOAT3 norm{};
//				lineStream >> norm.x;
//				lineStream >> norm.y;
//				lineStream >> norm.z;
//				//�@���x�N�g���f�[�^�ɒǉ�
//				normal.push_back(norm);
//			}
//			//�擪������f�Ȃ�|���S��(�O�p�`)
//			if (key == "f") {
//				//���p�X�y�[�X��؂�ōs�̑�����ǂݍ���
//				string indexString;
//				unsigned short indexPosition;		//�󂯎M
//				unsigned short indexNormal;			//�󂯎M
//				unsigned short indexTexcoord;		//�󂯎M
//				while (getline(lineStream, indexString, ' ')) {
//					//���_�C���f�b�N�X����̕�������X�g���[���ɕϊ����ĉ�͂��₷������
//					istringstream indexStream(indexString);
//					indexStream >> indexPosition;
//					indexStream.seekg(1, ios_base::cur);	//�X���b�V�����΂�
//					indexStream >> indexTexcoord;
//					indexStream.seekg(1, ios_base::cur);	//�X���b�V�����΂�
//					indexStream >> indexNormal;
//					//���_�f�[�^�̒ǉ�
//					Vertex vert{};
//					vert.pos = position[indexPosition - 1];
//					vert.normal = normal[indexNormal - 1];
//					vert.uv = uv[indexTexcoord - 1];
//					//���f���f�[�^�ɒǉ�
//					modelData.at(modelData.size() - 1).vertex.push_back(vert);
//					modelData.at(modelData.size() - 1).index.push_back(modelData.at(modelData.size() - 1).index.size());
//					//proSprite�ɂ��ǉ�
//					objectBuffer.vertex.push_back(vert);
//					objectBuffer.index.push_back(objectBuffer.index.size());
//					//isSmoothing��true�Ȃ璸�_����ǉ�����
//					if (isSmoothing == true) {
//						smoothData[indexPosition].push_back(objectBuffer.vertex.size() - 1);
//					}
//				}
//			}
//			//�擪������mtllib�Ȃ�}�e���A��
//			if (key == "mtllib") {
//				//�}�e���A���̃t�@�C�����ǂݍ���
//				string materialFileName;
//				lineStream >> materialFileName;
//				//�}�e���A���̓ǂݍ���
//				LoadObjMaterial(directoryPath + materialFileName, modelData.at(modelData.size() - 1), objectBuffer);
//			}
//		}
//		//�t�@�C�������
//		file.close();
//
//		//isSmoothing��true��������@�������Ȃ߂炩�ɂ���
//		if (isSmoothing == true) {
//			CalculateSmoothedVertexNormals(smoothData, objectBuffer, modelData.at(modelData.size() - 1));
//		}
//
//		return;
//	}
//
//	//obj�̃f�[�^��proSprite�ɓ����
//	for (int i = 0; i < modelData.at(dataNumber).index.size(); ++i) {
//		objectBuffer.index.push_back(modelData.at(dataNumber).index.at(i));
//	}
//	for (int i = 0; i < modelData.at(dataNumber).vertex.size(); ++i) {
//		objectBuffer.vertex.push_back(modelData.at(dataNumber).vertex.at(i));
//	}
//	objectBuffer.constBuffDataB1.alpha = 1;
//	objectBuffer.constBuffDataB1.ambient = modelData.at(dataNumber).material.ambient;
//	objectBuffer.constBuffDataB1.diffuse = modelData.at(dataNumber).material.diffuse;
//	objectBuffer.constBuffDataB1.specular = modelData.at(dataNumber).material.specular;
//}

//void ModelLoader::CollectMeshNode(FbxNode* node, vector<pair<string, FbxMesh*>>& list)
//{
//	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
//	{
//		FbxNodeAttribute* attribute = node->GetNodeAttributeByIndex(i);
//		int aaa = attribute->GetAttributeType();
//
//		// Attribute�����b�V���Ȃ�ǉ�
//		if (attribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
//		{
//			pair<string, FbxMesh*> pre;
//			pre.first = node->GetName();
//			pre.second = (FbxMesh*)attribute;
//			int polygon_vertex_count = pre.second->GetPolygonVertexCount();
//			list.push_back(pre);
//		}
//	}
//
//	for (int i = 0; i < node->GetChildCount(); i++)
//	{
//		CollectMeshNode(node->GetChild(i), list);
//	}
//}

void ModelLoader::LoadObjMaterial(const string& materialFileName, ModelData& modelData, ObjectData& objectBuffer)
{
	//�}�e���A������U����������
	objectBuffer.constBufferDataB1.alpha = 1;
	objectBuffer.constBufferDataB1.ambient = modelData.material.ambient;
	objectBuffer.constBufferDataB1.diffuse = modelData.material.diffuse;
	objectBuffer.constBufferDataB1.specular = modelData.material.specular;

	//�t�@�C���X�g���[��
	ifstream file;
	//�}�e���A���t�@�C�����J��
	file.open(materialFileName);
	//�t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail()) {
		//assert(0);
	}
	//��s���ǂݍ���
	string line;
	while (getline(file, line)) {
		//�ʒu�s���̕�������X�g���[���ɕϊ�
		istringstream lineStream(line);
		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(lineStream, key, ' ');
		//�擪�̃^�u�����͖�������
		if (key[0] == '\t') {
			key.erase(key.begin());	//�擪�̕������폜
		}
		//�擪������newmtl�Ȃ�}�e���A����
		if (key == "newmtl") {
			//�}�e���A�����̓ǂݍ���
			lineStream >> modelData.material.name;
		}
		//�擪������Ka�Ȃ�A���r�G���g�F
		if (key == "Ka") {
			lineStream >> modelData.material.ambient.x;
			lineStream >> modelData.material.ambient.y;
			lineStream >> modelData.material.ambient.z;
			objectBuffer.constBufferDataB1.ambient.x = modelData.material.ambient.x;
			objectBuffer.constBufferDataB1.ambient.y = modelData.material.ambient.y;
			objectBuffer.constBufferDataB1.ambient.z = modelData.material.ambient.z;
		}
		//�擪������Kd�Ȃ�f�B�t���[�Y�F
		if (key == "Kd") {
			lineStream >> modelData.material.diffuse.x;
			lineStream >> modelData.material.diffuse.y;
			lineStream >> modelData.material.diffuse.z;
			objectBuffer.constBufferDataB1.diffuse.x = modelData.material.diffuse.x;
			objectBuffer.constBufferDataB1.diffuse.y = modelData.material.diffuse.y;
			objectBuffer.constBufferDataB1.diffuse.z = modelData.material.diffuse.z;
		}
		//�擪������Ks�Ȃ�X�y�L�����[�F
		if (key == "Ks") {
			lineStream >> modelData.material.specular.x;
			lineStream >> modelData.material.specular.y;
			lineStream >> modelData.material.specular.z;
			objectBuffer.constBufferDataB1.specular.x = modelData.material.specular.x;
			objectBuffer.constBufferDataB1.specular.y = modelData.material.specular.y;
			objectBuffer.constBufferDataB1.specular.z = modelData.material.specular.z;
		}
	}
}

void ModelLoader::CalculateSmoothedVertexNormals(map<unsigned short, vector<unsigned short>>& smoothData, ObjectData& objectBuffer, ModelData& modelData)
{
	auto itr = smoothData.begin();
	for (; itr != smoothData.end(); ++itr) {
		// �e�ʗp�̋��ʒ��_�R���N�V����
		std::vector<unsigned short>& v = itr->second;
		// �S���_�̖@���𕽋ς���
		XMVECTOR normal = {};
		for (unsigned short index : v) {
			normal += XMVectorSet(objectBuffer.vertex[index].normal.x, objectBuffer.vertex[index].normal.y, objectBuffer.vertex[index].normal.z, 0);
		}
		normal = XMVector3Normalize(normal / (float)v.size());

		for (unsigned short index : v) {
			objectBuffer.vertex[index].normal = { normal.m128_f32[0], normal.m128_f32[1], normal.m128_f32[2] };
			modelData.vertex[index].normal = { normal.m128_f32[0], normal.m128_f32[1], normal.m128_f32[2] };
		}
	}
}
