#include "chams.hpp"

IMaterial* mat_regular;
IMaterial* mat_flat;
IMaterial* mat_metallic;
IMaterial* mat_plastic;
IMaterial* mat_elixir;
IMaterial* mat_glow;
IMaterial* mat_crystal;
IMaterial* mat_snow;
IMaterial* mat_glass;

IMaterial* create_material(std::string name, std::string type, std::string material) 
{
	auto kv = static_cast<c_key_values*>(malloc(36));
	kv->init(type.c_str());
	kv->load_from_buffer(name.c_str(), material.c_str());
	return g_MatSystem->CreateMaterial(name.c_str(), kv);
}

void override_material(bool ignorez, int type, color clr)
{
	IMaterial* material = nullptr;

	switch (type) 
	{
	     case 0: material = mat_regular; break;
	     case 1: material = mat_flat; break;
		 case 2: material = mat_metallic; break;
		 case 3: material = mat_plastic; break;
		 case 4: material = mat_elixir; break;
		 case 5: material = mat_glow; break;
		 case 6: material = mat_regular; break;
		 case 7: material = mat_crystal; break;
		 case 8: material = mat_snow; break;
		 case 9: material = mat_glass; break;
	}

	material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignorez);
	material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, type == 6);

	material->ColorModulate(clr.get_red() / 255.0f, clr.get_green() / 255.0f, clr.get_blue() / 255.0f);
	material->AlphaModulate(clr.get_alpha() / 255.0f);

	g_MdlRender->ForcedMaterialOverride(material);
}

void override_overlay_material(bool ignorez, bool wireframe, int type, color clr)
{
	IMaterial* material = nullptr;

	switch (type)
	{
	    case 0: material = mat_regular; break;
	    case 1: material = mat_flat; break;
	    case 2: material = mat_metallic; break;
	    case 3: material = mat_plastic; break;
	    case 4: material = mat_elixir; break;
	    case 5: material = mat_glow; break;
	    case 6: material = mat_regular; break;
	    case 7: material = mat_crystal; break;
	    case 8: material = mat_snow; break;
	    case 9: material = mat_glass; break;
	}

	material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignorez);
	material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, wireframe);

	auto overlay = material->FindVar(xorstr("$envmaptint"), nullptr);
	overlay->set_vector_value(clr.get_red() / 255.0f, clr.get_green() / 255.0f, clr.get_blue() / 255.0f);

	material->ColorModulate(clr.get_red() / 255.0f, clr.get_green() / 255.0f, clr.get_blue() / 255.0f);
	material->AlphaModulate(clr.get_alpha() / 255.0f);

	g_MdlRender->ForcedMaterialOverride(material);
}

void chams::initialize()
{
	mat_regular = g_MatSystem->FindMaterial(xorstr("debug/debugambientcube"), TEXTURE_GROUP_MODEL);
	mat_regular->IncrementReferenceCount();

	mat_flat = g_MatSystem->FindMaterial(xorstr("debug/debugdrawflat"), TEXTURE_GROUP_MODEL);
	mat_flat->IncrementReferenceCount();

	mat_plastic = g_MatSystem->FindMaterial(xorstr("models/inventory_items/trophy_majors/gloss"), TEXTURE_GROUP_MODEL);
	mat_plastic->IncrementReferenceCount();

	mat_glow = g_MatSystem->FindMaterial(xorstr("dev/glow_armsrace"), TEXTURE_GROUP_MODEL);
	mat_glow->IncrementReferenceCount();

	mat_glass = g_MatSystem->FindMaterial(xorstr("models/inventory_items/cologne_prediction/cologne_prediction_glass"), TEXTURE_GROUP_MODEL);
	mat_glass->IncrementReferenceCount();

	mat_metallic = create_material(xorstr("metallic"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric" {
      "$basetexture" "vgui/white_additive"
      "$ignorez" "0"
      "$envmap" "env_cubemap"
      "$normalmapalphaenvmapmask" "1"
      "$envmapcontrast"  "1"
      "$nofog" "1"
      "$model" "1"
      "$nocull" "0"
      "$selfillum" "1"
      "$halflambert" "1"
      "$znearer" "0"
      "$flat" "1" 
}
)#"));

	mat_elixir = create_material(xorstr("elixir"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric" {
        "$basetexture" "VGUI/white_additive"
		"$bumpmap" "de_nuke/hr_nuke/pool_water_normals_002"
		"$bumptransform" "center 0.5 0.5 scale 0.25 0.25 rotate 0.0 translate 0.0 0.0"
		"$ignorez" "0"
		"$nofog" "1"
		"$model" "1"
		"$color2" "[1.0, 1.0, 1.0]"
		"$halflambert" "1"
		"$envmap" "env_cubemap"
		"$envmaptint" "[0.1 0.1 0.1]"
		"$envmapfresnel" "1.0"
		"$envmapfresnelminmaxexp" "[1.0, 1.0, 1.0]"
		"$phong" "1"
		"$phongexponent" "1024"
		"$phongboost" "4.0"
		"$phongfresnelranges" "[1.0, 1.0, 1.0]"
		"$rimlight" "1"
		"$rimlightexponent" "4.0"
		"$rimlightboost" "2.0"
    
		"Proxies"
		{
			"TextureScroll"
			{
				"textureScrollVar" "$bumptransform"
				"textureScrollRate" "0.25"
				"textureScrollAngle" "0.0"
			}
		}
   }  )#"));

	mat_crystal = create_material(xorstr("crystal"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric"
        {
            "$basetexture" "vgui/white"
            "$envmap" "models/effects/crystal_cube_vertigo_hdr"
            "$envmaptint" "[1 1 1]"
            "$envmapfresnel" "1"
            "$envmapfresnelminmaxexp" "[0 1 2]"
            "$phong" "1"
            "$reflectivity" "[2 2 2]"
            "$bumpmap" "models/weapons/customization/materials/origamil_camo"
            "$bumptransform" "center 0.5 0.5 scale 0.25 0.25 rotate 0.0 translate 0.0 0.0"
            "Proxies"
            {
                "TextureScroll"
                {
                    "textureScrollVar" "$bumptransform"
                    "textureScrollRate" "0.2"
                    "textureScrollAngle" "0.0"
                }
            }
        })#"));

	mat_snow = create_material(xorstr("snow"), xorstr("VertexLitGeneric"), xorstr(R"#("VertexLitGeneric"
        {
               "$basetexture"                "dev/snowfield"
		       "$ignorez" "0"
		       "$nofog" "1"
		       "$model" "1"
               "$nocull" "0"
               "$selfillum" "1"
               "$halflambert" "1"
               "$znearer" "0"
               "$flat" "1" 
                "$additive"                    "1"
                "$envmap"                    "editor/cube_vertigo"
                "$envmaptint"                "[0 0.5 0.55]"
                "$envmapfresnel"            "1"
                "$envmapfresnelminmaxexp"   "[0.00005 0.6 6]"
                "$alpha"                    "1"
 
                Proxies
                {
                    TextureScroll
                    {
                        "texturescrollvar"            "$baseTextureTransform"
                        "texturescrollrate"            "0.10"
                        "texturescrollangle"        "270"
                    }
                }
        })#"));
}

void chams::run(IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* matrix)
{
	if (!variables::config::esp::enable)
	{
		return;
	}

	if (!Utils::bind(variables::config::esp::key, variables::config::esp::key_type))
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player)
	{
		return;
	}

	const model_t* model = info.pModel;
	bool is_player = strstr(model->szName, xorstr("models/player")) != nullptr;
	auto ent = g_EntityList->GetClientEntity(info.entity_index);

	if (is_player)
	{
		player_t *player = reinterpret_cast<player_t*>(ent);

		if (!player || !player->is_alive() || player->IsDormant() || player == csgo::local_player || player->team() == csgo::local_player->team() && !variables::config::esp::teammates)
		{
			return;
		}

		if (variables::config::chams::occluded)
		{
			override_material(true, variables::config::chams::occluded_style, color(variables::config::chams::occluded_clr));
			draw_model_execute_original(g_MdlRender, ctx, state, info, matrix);
		}

		if (variables::config::chams::occluded_overlay)
		{
			override_overlay_material(true, variables::config::chams::occluded_wireframe_overlay, variables::config::chams::occluded_style_overlay, color(variables::config::chams::occluded_clr_overlay));
			draw_model_execute_original(g_MdlRender, ctx, state, info, matrix);
		}

		if (variables::config::chams::visible)
		{
			override_material(false, variables::config::chams::visible_style, color(variables::config::chams::visible_clr));
			draw_model_execute_original(g_MdlRender, ctx, state, info, matrix);
		}

		if (variables::config::chams::visible_overlay)
		{
			override_overlay_material(false, variables::config::chams::visible_wireframe_overlay, variables::config::chams::visible_style_overlay, color(variables::config::chams::visible_clr_overlay));
			draw_model_execute_original(g_MdlRender, ctx, state, info, matrix);
		}
	}
}