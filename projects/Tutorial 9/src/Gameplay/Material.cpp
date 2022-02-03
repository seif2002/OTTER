#include "Gameplay/Material.h"
#include "Utils/ResourceManager/ResourceManager.h"

namespace Gameplay {
	void Material::Apply() {
		// Material properties
		//MatShader->SetUniform("u_Material.Shininess", Shininess);
		MatShader->SetUniform("u_Material.Specular", 1);

		if (Specular != nullptr) {
			Specular->Bind(1);
		}
		
			// For textures, we pass the *slot* that the texture sure draw from
			MatShader->SetUniform("u_Material.Diffuse", 1);
			// Bind the texture
			if (Texture != nullptr) {
				Texture->Bind(1);
			}
		

	}

	Material::Sptr Material::FromJson(const nlohmann::json& data) {
		Material::Sptr result = std::make_shared<Material>();
		result->OverrideGUID(Guid(data["guid"]));
		result->Name = data["name"].get<std::string>();
		result->MatShader = ResourceManager::Get<Shader>(Guid(data["shader"]));

		// material specific parameters
		result->Texture = ResourceManager::Get<Texture2D>(Guid(data["texture"]));
		result->Specular = ResourceManager::Get<Texture2D>(Guid(data["specular"]));
		//result->Shininess = data["shininess"].get<float>();
		return result;
	}

	nlohmann::json Material::ToJson() const { 
		return {
			{ "guid", GetGUID().str() },
			{ "name", Name },
			{ "shader", MatShader ? MatShader->GetGUID().str() : "null" },

			{ "texture", Texture ? Texture->IResource::GetGUID().str() : "null" },
			{"specular", Specular ? Specular ->IResource::GetGUID().str() : "null"},
			//{ "shininess", Shininess },
		};
	}
}