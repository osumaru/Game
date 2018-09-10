#include "engineStdafx.h"
#include "SkinmodelResource.h"
#include "../Graphics/Skelton.h"
#include "../Graphics/SkinModel.h"

DirectX::Model* CSkinmodelResource::Load(const wchar_t * filePath, CSkelton * skelton)
{
	int hash = MakeHash(filePath);
	auto& map = m_skinmodels.find(hash);
	if (map == m_skinmodels.end())
	{
		if (skelton != nullptr)
		{
			CSkinModelEffectFactory effectFactory(GetDevice());
			std::unique_ptr<DirectX::Model> skinModelPtr;
			//É{Å[ÉìÇíTÇ∑ä÷êî
			auto onFindBone = [&](
				const wchar_t* boneName,
				const VSD3DStarter::Bone* bone,
				std::vector<int>& localBoneIDtoGlobalBoneIDTbl
				) {
				int globalBoneID = skelton->FindBoneID(boneName);
				if (globalBoneID == -1) {
					return;
				}
				localBoneIDtoGlobalBoneIDTbl.push_back(globalBoneID);
			};
			skinModelPtr = Model::CreateFromCMO(GetDevice(), filePath, effectFactory, false, false, onFindBone);
			DirectX::Model* skinmodel = skinModelPtr.get();
			m_skinmodels.insert({ hash, std::move(skinModelPtr) });
			return skinmodel;
		}
		else
		{
			CSkinModelEffectFactory effectFactory(GetDevice());
			std::unique_ptr<DirectX::Model> skinModelPtr;
			skinModelPtr = Model::CreateFromCMO(GetDevice(), filePath, effectFactory);
			DirectX::Model* skinmodel = skinModelPtr.get();
			m_skinmodels.insert({ hash, std::move(skinModelPtr) });
			return skinmodel;
		}
	}
	else
	{
		return map->second.get();
	}
}
