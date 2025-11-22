#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <set>
#include <iostream>
using namespace std;

#define export extern "C" __declspec( dllexport )

typedef unsigned int uint;

aiString ret_string;	//Global scope string for avoid return dereferenced pointers

double aiColorToGmColor(const aiColor3D& aiCol)
{
	uint r = min(max(int(aiCol.r * 255.0), 0), 255);
	uint g = min(max(int(aiCol.g * 255.0), 0), 255);
	uint b = min(max(int(aiCol.b * 255.0), 0), 255);

	g <<= 8;
	b <<= 16;
	return r + g + b;
}

uint importer_id;
map <uint, Assimp::Importer> importers;

Assimp::Importer* act_importer;
aiScene* act_scene;
aiMesh* act_mesh;
aiMaterial* act_material;
aiLight* act_light;
aiCamera* act_camera;
aiNode* act_node;
aiBone* act_bone;
aiMatrix4x4 act_matrix;
aiAnimation* act_animation;
aiNodeAnim* act_node_anim;
aiMeshAnim* act_mesh_anim;

aiScene* act_mesh_scene;
aiScene* act_material_scene;
aiScene* act_light_scene;
aiScene* act_camera_scene;
aiScene* act_node_scene;
aiScene* act_animation_scene;

namespace GMAssimpEnums
{
	namespace GMEnums
	{
		enum GMA_POST_PROCESS
		{
			GMA_PP_CALC_TANGENT_SPACE			= 0x1,
			GMA_PP_JOIN_IDENTICAL_VERTICES		= 0x2,
			GMA_PP_MAKE_LEFT_HANDED				= 0x4,
			GMA_PP_TRIANGULATE					= 0x8,
			GMA_PP_REMOVE_COMPONENT				= 0x10,
			GMA_PP_GEN_NORMALS					= 0x20,
			GMA_PP_GEN_SMOOTH_NORMALS			= 0x40,
			GMA_PP_SPLIT_LARGE_MESHES			= 0x80,
			GMA_PP_PRETRANSFORM_VERTICES		= 0x100,
			GMA_PP_LIMIT_BONE_WEIGHTS			= 0x200,
			GMA_PP_VALIDATE_DATA_STRUCTURE		= 0x400,
			GMA_PP_IMPROVE_CACHE_LOCALITY		= 0x800,
			GMA_PP_REMOVE_REDUNDANT_MATERIALS	= 0x1000,
			GMA_PP_FIX_INFACING_NORMALS			= 0x2000,
			GMA_PP_POPULATE_ARMATURE_DATA		= 0x4000,
			GMA_PP_SORT_BY_PTYPE				= 0x8000,
			GMA_PP_FIND_DEGENERATES				= 0x10000,
			GMA_PP_FIND_INVALID_DATA			= 0x20000,
			GMA_PP_GEN_UV_COORDS				= 0x40000,
			GMA_PP_TRANSFORM_UV_COORDS			= 0x80000,
			GMA_PP_FIND_INSTANCES				= 0x100000,
			GMA_PP_OPTIMIZE_MESHES				= 0x200000,
			GMA_PP_OPTIMIZE_GRAPH				= 0x400000,
			GMA_PP_FLIP_UVS						= 0x800000,
			GMA_PP_FLIP_WINDING_ORDER			= 0x1000000,
			GMA_PP_SPLIT_BONE_COUNT				= 0x2000000,
			GMA_PP_DEBONE						= 0x4000000,
			GMA_PP_GLOBAL_SCALE					= 0x8000000,
			GMA_PP_EMBED_TEXTURES				= 0x10000000,
			GMA_PP_FORCE_GEN_NORMALS			= 0x20000000,
			GMA_PP_DROP_NORMALS					= 0x40000000,
			GMA_PP_GEN_BOUNDING_BOXES			= 0x80000000
		};

		enum GMA_TEXTURE_TYPE
		{
			GMA_TEXTURE_TYPE_NONE = 0,
			GMA_TEXTURE_TYPE_DIFFUSE = 1,
			GMA_TEXTURE_TYPE_SPECULAR = 2,
			GMA_TEXTURE_TYPE_AMBIENT = 3,
			GMA_TEXTURE_TYPE_EMISSIVE = 4,
			GMA_TEXTURE_TYPE_HEIGHT = 5,
			GMA_TEXTURE_TYPE_NORMALS = 6,
			GMA_TEXTURE_TYPE_SHININESS = 7,
			GMA_TEXTURE_TYPE_OPACITY = 8,
			GMA_TEXTURE_TYPE_DISPLACEMENT = 9,
			GMA_TEXTURE_TYPE_LIGHTMAP = 10,
			GMA_TEXTURE_TYPE_REFLECTION = 11,
			GMA_TEXTURE_BASE_COLOR = 12,
			GMA_TEXTURE_NORMAL_CAMERA = 13,
			GMA_TEXTURE_EMISSION_COLOR = 14,
			GMA_TEXTURE_METALNESS = 15,
			GMA_TEXTURE_DIFFUSE_ROUGHNESS = 16,
			GMA_TEXTURE_AMBIENT_OCCLUSION = 17,
			GMA_TEXTURE_TYPE_UNKNOWN = 18
		};

		enum GMA_LIGHT_SOURCE_TYPE
		{
			GMA_LIGHT_SOURCE_UNDEFINED = 0,
			GMA_LIGHT_SOURCE_DIRECTIONAL = 1,
			GMA_LIGHT_SOURCE_POINT = 2,
			GMA_LIGHT_SOURCE_SPOT = 3,
			GMA_LIGHT_SOURCE_AMBIENT = 4,
			GMA_LIGHT_SOURCE_AREA = 5
		};

		enum GMA_SHADING_MODE
		{
			GMA_SHADING_MODE_FLAT = 1,
			GMA_SHADING_MODE_GOURAUD = 2,
			GMA_SHADING_MODE_PHONG = 3,
			GMA_SHADING_MODE_BLINN = 4,
			GMA_SHADING_MODE_TOON = 5,
			GMA_SHADING_MODE_OREN_NAYAR = 6,
			GMA_SHADING_MODE_MINNAERT = 7,
			GMA_SHADING_MODE_COOK_TORRANCE = 8,
			GMA_SHADING_MODE_NO_SHADING = 9,
			GMA_SHADING_MODE_FRESNEL = 10
		};

		enum GMA_BLEND_MODE
		{
			GMA_BLEND_MODE_DEFAULT = 0,
			GMA_BLEND_MODE_ADDITIVE = 1
		};

		enum GMA_TEXTURE_OPERATION
		{
			GMA_TEXTURE_OP_MULTIPLY = 0,
			GMA_TEXTURE_OP_ADD = 1,
			GMA_TEXTURE_OP_SUBTRACT = 2,
			GMA_TEXTURE_OP_DIVIDE = 3,
			GMA_TEXTURE_OP_SMOOTH_ADD = 4,
			GMA_TEXTURE_OP_SIGNED_ADD = 5
		};

		enum GMA_TEXTURE_MAPPING
		{
			GMA_TEXTURE_MAPPING_UV = 0,
			GMA_TEXTURE_MAPPING_SPHERE = 1,
			GMA_TEXTURE_MAPPING_CYLINDER = 2,
			GMA_TEXTURE_MAPPING_BOX = 3,
			GMA_TEXTURE_MAPPING_PLANE = 4,
			GMA_TEXTURE_MAPPING_OTHER = 5
		};

		enum GMA_TEXTURE_MAP_MODE
		{
			GMA_TEXTURE_MAP_MODE_WRAP = 0,
			GMA_TEXTURE_MAP_MODE_CLAMP = 1,
			GMA_TEXTURE_MAP_MODE_MIRROR = 2,
			GMA_TEXTURE_MAP_MODE_DECAL = 3
		};

		enum GMA_TEXTURE_FLAGS
		{
			GMA_TEXTURE_FLAGS_INVERT = 0x1,
			GMA_TEXTURE_FLAGS_USE_ALPHA = 0x2,
			GMA_TEXTURE_FLAGS_IGNORE_ALPHA = 0x4
		};

		enum GMA_PRIMITIVE_TYPE
		{
			GMA_PRIMITIVE_TYPE_POINT = 0x1,
			GMA_PRIMITIVE_TYPE_LINE = 0x2,
			GMA_PRIMITIVE_TYPE_TRIANGLE = 0x4,
			GMA_PRIMITIVE_TYPE_POLYGON = 0x8
		};

		enum GMA_ANIMATION_BEHAVIOUR
		{
			GMA_ANIMATION_BEHAVIOUR_DEFAULT = 0,
			GMA_ANIMATION_BEHAVIOUR_CONSTANT = 1,
			GMA_ANIMATION_BEHAVIOUR_LINEAR = 2,
			GMA_ANIMATION_BEHAVIOUR_REPEAT = 3
		};

		enum GMA_MORPH_METHOD
		{
			GMA_MORPH_METHOD_VERTEX_BLEND = 1,
			GMA_MORPH_METHOD_MORPH_NORMALIZED = 2,
			GMA_MORPH_METHOD_MORPH_RELATIVE = 3
		};
	}

	namespace GM_TO_AI
	{
		using namespace GMEnums;

		aiPostProcessSteps ConvertGMEnum(GMA_POST_PROCESS gm_enum)
		{
			int pp_step = 0;
			if (gm_enum & GMA_PP_CALC_TANGENT_SPACE) { pp_step |= aiProcess_CalcTangentSpace; }
			if (gm_enum & GMA_PP_JOIN_IDENTICAL_VERTICES) { pp_step |= aiProcess_JoinIdenticalVertices; }
			if (gm_enum & GMA_PP_MAKE_LEFT_HANDED) { pp_step |= aiProcess_MakeLeftHanded; }
			if (gm_enum & GMA_PP_TRIANGULATE) { pp_step |= aiProcess_Triangulate; }
			if (gm_enum & GMA_PP_REMOVE_COMPONENT) { pp_step |= aiProcess_RemoveComponent; }
			if (gm_enum & GMA_PP_GEN_NORMALS) { pp_step |= aiProcess_GenNormals; }
			if (gm_enum & GMA_PP_GEN_SMOOTH_NORMALS) { pp_step |= aiProcess_GenSmoothNormals; }
			if (gm_enum & GMA_PP_SPLIT_LARGE_MESHES) { pp_step |= aiProcess_SplitLargeMeshes; }
			if (gm_enum & GMA_PP_PRETRANSFORM_VERTICES) { pp_step |= aiProcess_PreTransformVertices; }
			if (gm_enum & GMA_PP_LIMIT_BONE_WEIGHTS) { pp_step |= aiProcess_LimitBoneWeights; }
			if (gm_enum & GMA_PP_VALIDATE_DATA_STRUCTURE) { pp_step |= aiProcess_ValidateDataStructure; }
			if (gm_enum & GMA_PP_IMPROVE_CACHE_LOCALITY) { pp_step |= aiProcess_ImproveCacheLocality; }
			if (gm_enum & GMA_PP_REMOVE_REDUNDANT_MATERIALS) { pp_step |= aiProcess_RemoveRedundantMaterials; }
			if (gm_enum & GMA_PP_FIX_INFACING_NORMALS) { pp_step |= aiProcess_FixInfacingNormals; }
			if (gm_enum & GMA_PP_POPULATE_ARMATURE_DATA) { pp_step |= aiProcess_PopulateArmatureData; }
			if (gm_enum & GMA_PP_SORT_BY_PTYPE) { pp_step |= aiProcess_SortByPType; }
			if (gm_enum & GMA_PP_FIND_DEGENERATES) { pp_step |= aiProcess_FindDegenerates; }
			if (gm_enum & GMA_PP_FIND_INVALID_DATA) { pp_step |= aiProcess_FindInvalidData; }
			if (gm_enum & GMA_PP_GEN_UV_COORDS) { pp_step |= aiProcess_GenUVCoords; }
			if (gm_enum & GMA_PP_TRANSFORM_UV_COORDS) { pp_step |= aiProcess_TransformUVCoords; }
			if (gm_enum & GMA_PP_FIND_INSTANCES) { pp_step |= aiProcess_FindInstances; }
			if (gm_enum & GMA_PP_OPTIMIZE_MESHES) { pp_step |= aiProcess_OptimizeMeshes; }
			if (gm_enum & GMA_PP_OPTIMIZE_GRAPH) { pp_step |= aiProcess_OptimizeGraph; }
			if (gm_enum & GMA_PP_FLIP_UVS) { pp_step |= aiProcess_FlipUVs; }
			if (gm_enum & GMA_PP_FLIP_WINDING_ORDER) { pp_step |= aiProcess_FlipWindingOrder; }
			if (gm_enum & GMA_PP_SPLIT_BONE_COUNT) { pp_step |= aiProcess_SplitByBoneCount; }
			if (gm_enum & GMA_PP_DEBONE) { pp_step |= aiProcess_Debone; }
			if (gm_enum & GMA_PP_GLOBAL_SCALE) { pp_step |= aiProcess_GlobalScale; }
			if (gm_enum & GMA_PP_EMBED_TEXTURES) { pp_step |= aiProcess_EmbedTextures; }
			if (gm_enum & GMA_PP_FORCE_GEN_NORMALS) { pp_step |= aiProcess_ForceGenNormals; }
			if (gm_enum & GMA_PP_DROP_NORMALS) { pp_step |= aiProcess_DropNormals; }
			if (gm_enum & GMA_PP_GEN_BOUNDING_BOXES) { pp_step |= aiProcess_GenBoundingBoxes; }
			return aiPostProcessSteps(pp_step);
		}

		aiTextureType ConvertGMEnum(GMA_TEXTURE_TYPE gm_enum)
		{
			switch (gm_enum)
			{
			case GMA_TEXTURE_TYPE_NONE: return aiTextureType_NONE; break;
			case GMA_TEXTURE_TYPE_DIFFUSE: return aiTextureType_DIFFUSE; break;
			case GMA_TEXTURE_TYPE_SPECULAR: return aiTextureType_SPECULAR; break;
			case GMA_TEXTURE_TYPE_AMBIENT: return aiTextureType_AMBIENT; break;
			case GMA_TEXTURE_TYPE_EMISSIVE: return aiTextureType_EMISSIVE; break;
			case GMA_TEXTURE_TYPE_HEIGHT: return aiTextureType_HEIGHT; break;
			case GMA_TEXTURE_TYPE_NORMALS: return aiTextureType_NORMALS; break;
			case GMA_TEXTURE_TYPE_SHININESS: return aiTextureType_SHININESS; break;
			case GMA_TEXTURE_TYPE_OPACITY: return aiTextureType_OPACITY; break;
			case GMA_TEXTURE_TYPE_DISPLACEMENT: return aiTextureType_DISPLACEMENT; break;
			case GMA_TEXTURE_TYPE_LIGHTMAP: return aiTextureType_LIGHTMAP; break;
			case GMA_TEXTURE_TYPE_REFLECTION: return aiTextureType_REFLECTION; break;
			case GMA_TEXTURE_BASE_COLOR: return aiTextureType_BASE_COLOR; break;
			case GMA_TEXTURE_NORMAL_CAMERA: return aiTextureType_NORMAL_CAMERA; break;
			case GMA_TEXTURE_EMISSION_COLOR: return aiTextureType_EMISSION_COLOR; break;
			case GMA_TEXTURE_METALNESS: return aiTextureType_METALNESS; break;
			case GMA_TEXTURE_DIFFUSE_ROUGHNESS: return aiTextureType_DIFFUSE_ROUGHNESS; break;
			case GMA_TEXTURE_AMBIENT_OCCLUSION: return aiTextureType_AMBIENT_OCCLUSION; break;
			case GMA_TEXTURE_TYPE_UNKNOWN: return aiTextureType_UNKNOWN; break;
			default: return aiTextureType_UNKNOWN; break;
			}
		}

		aiLightSourceType ConvertGMEnum(GMA_LIGHT_SOURCE_TYPE gm_enum)
		{
			switch (gm_enum)
			{
			case GMA_LIGHT_SOURCE_UNDEFINED: return aiLightSource_UNDEFINED; break;
			case GMA_LIGHT_SOURCE_DIRECTIONAL: return aiLightSource_DIRECTIONAL; break;
			case GMA_LIGHT_SOURCE_POINT: return aiLightSource_POINT; break;
			case GMA_LIGHT_SOURCE_SPOT: return aiLightSource_SPOT; break;
			case GMA_LIGHT_SOURCE_AMBIENT: return aiLightSource_AMBIENT; break;
			case GMA_LIGHT_SOURCE_AREA: return aiLightSource_AREA; break;
			default: return aiLightSource_UNDEFINED; break;
			}
		}

		aiShadingMode ConvertGMEnum(GMA_SHADING_MODE gm_enum)
		{
			switch (gm_enum)
			{
			case GMA_SHADING_MODE_FLAT: return aiShadingMode_Flat; break;
			case GMA_SHADING_MODE_GOURAUD: return aiShadingMode_Gouraud; break;
			case GMA_SHADING_MODE_PHONG: return aiShadingMode_Phong; break;
			case GMA_SHADING_MODE_BLINN: return aiShadingMode_Blinn; break;
			case GMA_SHADING_MODE_TOON: return aiShadingMode_Toon; break;
			case GMA_SHADING_MODE_OREN_NAYAR: return aiShadingMode_OrenNayar; break;
			case GMA_SHADING_MODE_MINNAERT: return aiShadingMode_Minnaert; break;
			case GMA_SHADING_MODE_COOK_TORRANCE: return aiShadingMode_CookTorrance; break;
			case GMA_SHADING_MODE_NO_SHADING: return aiShadingMode_NoShading; break;
			case GMA_SHADING_MODE_FRESNEL: return aiShadingMode_Fresnel; break;
			default: return aiShadingMode_NoShading; break;
			}
		}

		aiBlendMode ConvertGMEnum(GMA_BLEND_MODE gm_enum)
		{
			switch (gm_enum)
			{
			case GMA_BLEND_MODE_DEFAULT: return aiBlendMode_Default; break;
			case GMA_BLEND_MODE_ADDITIVE: return aiBlendMode_Additive; break;
			default: return aiBlendMode_Default; break;
			}
		}

		aiTextureOp ConvertGMEnum(GMA_TEXTURE_OPERATION gm_enum)
		{
			switch (gm_enum)
			{
			case GMA_TEXTURE_OP_MULTIPLY: return aiTextureOp_Multiply; break;
			case GMA_TEXTURE_OP_ADD: return aiTextureOp_Add; break;
			case GMA_TEXTURE_OP_SUBTRACT: return aiTextureOp_Subtract; break;
			case GMA_TEXTURE_OP_DIVIDE: return aiTextureOp_Divide; break;
			case GMA_TEXTURE_OP_SMOOTH_ADD: return aiTextureOp_SmoothAdd; break;
			case GMA_TEXTURE_OP_SIGNED_ADD: return aiTextureOp_SignedAdd; break;
			default: return aiTextureOp_Multiply; break;
			}
		}

		aiTextureMapping ConvertGMEnum(GMA_TEXTURE_MAPPING gm_enum)
		{
			switch (gm_enum)
			{
			case GMA_TEXTURE_MAPPING_UV: return aiTextureMapping_UV; break;
			case GMA_TEXTURE_MAPPING_SPHERE: return aiTextureMapping_SPHERE; break;
			case GMA_TEXTURE_MAPPING_CYLINDER: return aiTextureMapping_CYLINDER; break;
			case GMA_TEXTURE_MAPPING_BOX: return aiTextureMapping_BOX; break;
			case GMA_TEXTURE_MAPPING_PLANE: return aiTextureMapping_PLANE; break;
			case GMA_TEXTURE_MAPPING_OTHER: return aiTextureMapping_OTHER; break;
			default: return aiTextureMapping_UV; break;
			}
		}

		aiTextureMapMode ConvertGMEnum(GMA_TEXTURE_MAP_MODE gm_enum)
		{
			switch (gm_enum)
			{
			case GMA_TEXTURE_MAP_MODE_WRAP: return aiTextureMapMode_Wrap; break;
			case GMA_TEXTURE_MAP_MODE_CLAMP: return aiTextureMapMode_Clamp; break;
			case GMA_TEXTURE_MAP_MODE_MIRROR: return aiTextureMapMode_Mirror; break;
			case GMA_TEXTURE_MAP_MODE_DECAL: return aiTextureMapMode_Decal; break;
			default: return aiTextureMapMode_Wrap; break;
			}
		}

		aiTextureFlags ConvertGMEnum(GMA_TEXTURE_FLAGS gm_enum)
		{
			int pp_step = 0;
			if (gm_enum & GMA_TEXTURE_FLAGS_INVERT) { pp_step |= aiTextureFlags_Invert; }
			if (gm_enum & GMA_TEXTURE_FLAGS_USE_ALPHA) { pp_step |= aiTextureFlags_UseAlpha; }
			if (gm_enum & GMA_TEXTURE_FLAGS_IGNORE_ALPHA) { pp_step |= aiTextureFlags_IgnoreAlpha; }
			return aiTextureFlags(pp_step);
		}

		aiPrimitiveType ConvertGMEnum(GMA_PRIMITIVE_TYPE gm_enum)
		{
			int pp_step = 0;
			if (gm_enum & GMA_PRIMITIVE_TYPE_POINT) { pp_step |= aiPrimitiveType_POINT; }
			if (gm_enum & GMA_PRIMITIVE_TYPE_LINE) { pp_step |= aiPrimitiveType_LINE; }
			if (gm_enum & GMA_PRIMITIVE_TYPE_TRIANGLE) { pp_step |= aiPrimitiveType_TRIANGLE; }
			if (gm_enum & GMA_PRIMITIVE_TYPE_POLYGON) { pp_step |= aiPrimitiveType_POLYGON; }
			return aiPrimitiveType(pp_step);
		}

		aiAnimBehaviour ConvertGMEnum(GMA_ANIMATION_BEHAVIOUR gm_enum)
		{
			switch (gm_enum)
			{
			case GMA_ANIMATION_BEHAVIOUR_DEFAULT: return aiAnimBehaviour_DEFAULT; break;
			case GMA_ANIMATION_BEHAVIOUR_CONSTANT: return aiAnimBehaviour_CONSTANT; break;
			case GMA_ANIMATION_BEHAVIOUR_LINEAR: return aiAnimBehaviour_LINEAR; break;
			case GMA_ANIMATION_BEHAVIOUR_REPEAT: return aiAnimBehaviour_REPEAT; break;
			default: return aiAnimBehaviour_DEFAULT; break;
			}
		}
	}

	namespace AI_TO_GM
	{
		using namespace GMEnums;

		GMA_POST_PROCESS ConvertAIEnum(aiPostProcessSteps ai_enum)
		{
			int pp_step = 0;
			if (ai_enum & aiProcess_CalcTangentSpace) { pp_step |= GMA_PP_CALC_TANGENT_SPACE; }
			if (ai_enum & aiProcess_JoinIdenticalVertices) { pp_step |= GMA_PP_JOIN_IDENTICAL_VERTICES; }
			if (ai_enum & aiProcess_MakeLeftHanded) { pp_step |= GMA_PP_MAKE_LEFT_HANDED; }
			if (ai_enum & aiProcess_Triangulate) { pp_step |= GMA_PP_TRIANGULATE; }
			if (ai_enum & aiProcess_RemoveComponent) { pp_step |= GMA_PP_REMOVE_COMPONENT; }
			if (ai_enum & aiProcess_GenNormals) { pp_step |= GMA_PP_GEN_NORMALS; }
			if (ai_enum & aiProcess_GenSmoothNormals) { pp_step |= GMA_PP_GEN_SMOOTH_NORMALS; }
			if (ai_enum & aiProcess_SplitLargeMeshes) { pp_step |= GMA_PP_SPLIT_LARGE_MESHES; }
			if (ai_enum & aiProcess_PreTransformVertices) { pp_step |= GMA_PP_PRETRANSFORM_VERTICES; }
			if (ai_enum & aiProcess_LimitBoneWeights) { pp_step |= GMA_PP_LIMIT_BONE_WEIGHTS; }
			if (ai_enum & aiProcess_ValidateDataStructure) { pp_step |= GMA_PP_VALIDATE_DATA_STRUCTURE; }
			if (ai_enum & aiProcess_ImproveCacheLocality) { pp_step |= GMA_PP_IMPROVE_CACHE_LOCALITY; }
			if (ai_enum & aiProcess_RemoveRedundantMaterials) { pp_step |= GMA_PP_REMOVE_REDUNDANT_MATERIALS; }
			if (ai_enum & aiProcess_FixInfacingNormals) { pp_step |= GMA_PP_FIX_INFACING_NORMALS; }
			if (ai_enum & aiProcess_PopulateArmatureData) { pp_step |= GMA_PP_POPULATE_ARMATURE_DATA; }
			if (ai_enum & aiProcess_SortByPType) { pp_step |= GMA_PP_SORT_BY_PTYPE; }
			if (ai_enum & aiProcess_FindDegenerates) { pp_step |= GMA_PP_FIND_DEGENERATES; }
			if (ai_enum & aiProcess_FindInvalidData) { pp_step |= GMA_PP_FIND_INVALID_DATA; }
			if (ai_enum & aiProcess_GenUVCoords) { pp_step |= GMA_PP_GEN_UV_COORDS; }
			if (ai_enum & aiProcess_TransformUVCoords) { pp_step |= GMA_PP_TRANSFORM_UV_COORDS; }
			if (ai_enum & aiProcess_FindInstances) { pp_step |= GMA_PP_FIND_INSTANCES; }
			if (ai_enum & aiProcess_OptimizeMeshes) { pp_step |= GMA_PP_OPTIMIZE_MESHES; }
			if (ai_enum & aiProcess_OptimizeGraph) { pp_step |= GMA_PP_OPTIMIZE_GRAPH; }
			if (ai_enum & aiProcess_FlipUVs) { pp_step |= GMA_PP_FLIP_UVS; }
			if (ai_enum & aiProcess_FlipWindingOrder) { pp_step |= GMA_PP_FLIP_WINDING_ORDER; }
			if (ai_enum & aiProcess_SplitByBoneCount) { pp_step |= GMA_PP_SPLIT_BONE_COUNT; }
			if (ai_enum & aiProcess_Debone) { pp_step |= GMA_PP_DEBONE; }
			if (ai_enum & aiProcess_GlobalScale) { pp_step |= GMA_PP_GLOBAL_SCALE; }
			if (ai_enum & aiProcess_EmbedTextures) { pp_step |= GMA_PP_EMBED_TEXTURES; }
			if (ai_enum & aiProcess_ForceGenNormals) { pp_step |= GMA_PP_FORCE_GEN_NORMALS; }
			if (ai_enum & aiProcess_DropNormals) { pp_step |= GMA_PP_DROP_NORMALS; }
			if (ai_enum & aiProcess_GenBoundingBoxes) { pp_step |= GMA_PP_GEN_BOUNDING_BOXES; }
			if (ai_enum & GMA_PP_GLOBAL_SCALE) { pp_step |= aiProcess_GlobalScale; }
			if (ai_enum & GMA_PP_EMBED_TEXTURES) { pp_step |= aiProcess_EmbedTextures; }
			if (ai_enum & GMA_PP_FORCE_GEN_NORMALS) { pp_step |= aiProcess_ForceGenNormals; }
			if (ai_enum & GMA_PP_DROP_NORMALS) { pp_step |= aiProcess_DropNormals; }
			if (ai_enum & GMA_PP_GEN_BOUNDING_BOXES) { pp_step |= aiProcess_GenBoundingBoxes; }
			return GMA_POST_PROCESS(pp_step);
		}

		GMA_TEXTURE_TYPE ConvertAIEnum(aiTextureType ai_enum)
		{
			switch (ai_enum)
			{
			case aiTextureType_NONE: return GMA_TEXTURE_TYPE_NONE; break;
			case aiTextureType_DIFFUSE: return GMA_TEXTURE_TYPE_DIFFUSE; break;
			case aiTextureType_SPECULAR: return GMA_TEXTURE_TYPE_SPECULAR; break;
			case aiTextureType_AMBIENT: return GMA_TEXTURE_TYPE_AMBIENT; break;
			case aiTextureType_EMISSIVE: return GMA_TEXTURE_TYPE_EMISSIVE; break;
			case aiTextureType_HEIGHT: return GMA_TEXTURE_TYPE_HEIGHT; break;
			case aiTextureType_NORMALS: return GMA_TEXTURE_TYPE_NORMALS; break;
			case aiTextureType_SHININESS: return GMA_TEXTURE_TYPE_SHININESS; break;
			case aiTextureType_OPACITY: return GMA_TEXTURE_TYPE_OPACITY; break;
			case aiTextureType_DISPLACEMENT: return GMA_TEXTURE_TYPE_DISPLACEMENT; break;
			case aiTextureType_LIGHTMAP: return GMA_TEXTURE_TYPE_LIGHTMAP; break;
			case aiTextureType_REFLECTION: return GMA_TEXTURE_TYPE_REFLECTION; break;
			case aiTextureType_BASE_COLOR: return GMA_TEXTURE_BASE_COLOR; break;
			case aiTextureType_NORMAL_CAMERA: return GMA_TEXTURE_NORMAL_CAMERA; break;
			case aiTextureType_EMISSION_COLOR: return GMA_TEXTURE_EMISSION_COLOR; break;
			case aiTextureType_METALNESS: return GMA_TEXTURE_METALNESS; break;
			case aiTextureType_DIFFUSE_ROUGHNESS: return GMA_TEXTURE_DIFFUSE_ROUGHNESS; break;
			case aiTextureType_AMBIENT_OCCLUSION: return GMA_TEXTURE_AMBIENT_OCCLUSION; break;
			case aiTextureType_UNKNOWN: return GMA_TEXTURE_TYPE_UNKNOWN; break;
			default: return GMA_TEXTURE_TYPE_UNKNOWN; break;
			}
		}

		GMA_LIGHT_SOURCE_TYPE ConvertAIEnum(aiLightSourceType ai_enum)
		{
			switch (ai_enum)
			{
			case aiLightSource_UNDEFINED: return GMA_LIGHT_SOURCE_UNDEFINED; break;
			case aiLightSource_DIRECTIONAL: return GMA_LIGHT_SOURCE_DIRECTIONAL; break;
			case aiLightSource_POINT: return GMA_LIGHT_SOURCE_POINT; break;
			case aiLightSource_SPOT: return GMA_LIGHT_SOURCE_SPOT; break;
			case aiLightSource_AMBIENT: return GMA_LIGHT_SOURCE_AMBIENT; break;
			case aiLightSource_AREA: return GMA_LIGHT_SOURCE_AREA; break;
			default: return GMA_LIGHT_SOURCE_UNDEFINED; break;
			}
		}

		GMA_SHADING_MODE ConvertAIEnum(aiShadingMode ai_enum)
		{
			switch (ai_enum)
			{
			case aiShadingMode_Flat: return GMA_SHADING_MODE_FLAT; break;
			case aiShadingMode_Gouraud: return GMA_SHADING_MODE_GOURAUD; break;
			case aiShadingMode_Phong: return GMA_SHADING_MODE_PHONG; break;
			case aiShadingMode_Blinn: return GMA_SHADING_MODE_BLINN; break;
			case aiShadingMode_Toon: return GMA_SHADING_MODE_TOON; break;
			case aiShadingMode_OrenNayar: return GMA_SHADING_MODE_OREN_NAYAR; break;
			case aiShadingMode_Minnaert: return GMA_SHADING_MODE_MINNAERT; break;
			case aiShadingMode_CookTorrance: return GMA_SHADING_MODE_COOK_TORRANCE; break;
			case aiShadingMode_NoShading: return GMA_SHADING_MODE_NO_SHADING; break;
			case aiShadingMode_Fresnel: return GMA_SHADING_MODE_FRESNEL; break;
			default: return GMA_SHADING_MODE_NO_SHADING; break;
			}
		}

		GMA_BLEND_MODE ConvertAIEnum(aiBlendMode ai_enum)
		{
			switch (ai_enum)
			{
			case aiBlendMode_Default: return GMA_BLEND_MODE_DEFAULT; break;
			case aiBlendMode_Additive: return GMA_BLEND_MODE_ADDITIVE; break;
			default: return GMA_BLEND_MODE_DEFAULT; break;
			}
		}

		GMA_TEXTURE_OPERATION ConvertAIEnum(aiTextureOp ai_enum)
		{
			switch (ai_enum)
			{
			case aiTextureOp_Multiply: return GMA_TEXTURE_OP_MULTIPLY; break;
			case aiTextureOp_Add: return GMA_TEXTURE_OP_ADD; break;
			case aiTextureOp_Subtract: return GMA_TEXTURE_OP_SUBTRACT; break;
			case aiTextureOp_Divide: return GMA_TEXTURE_OP_DIVIDE; break;
			case aiTextureOp_SmoothAdd: return GMA_TEXTURE_OP_SMOOTH_ADD; break;
			case aiTextureOp_SignedAdd: return GMA_TEXTURE_OP_SIGNED_ADD; break;
			default: return GMA_TEXTURE_OP_MULTIPLY; break;
			}
		}

		GMA_TEXTURE_MAPPING ConvertAIEnum(aiTextureMapping ai_enum)
		{
			switch (ai_enum)
			{
			case aiTextureMapping_UV: return GMA_TEXTURE_MAPPING_UV; break;
			case aiTextureMapping_SPHERE: return GMA_TEXTURE_MAPPING_SPHERE; break;
			case aiTextureMapping_CYLINDER: return GMA_TEXTURE_MAPPING_CYLINDER; break;
			case aiTextureMapping_BOX: return GMA_TEXTURE_MAPPING_BOX; break;
			case aiTextureMapping_PLANE: return GMA_TEXTURE_MAPPING_PLANE; break;
			case aiTextureMapping_OTHER: return GMA_TEXTURE_MAPPING_OTHER; break;
			default: return GMA_TEXTURE_MAPPING_UV; break;
			}
		}

		GMA_TEXTURE_MAP_MODE ConvertAIEnum(aiTextureMapMode ai_enum)
		{
			switch (ai_enum)
			{
			case aiTextureMapMode_Wrap: return GMA_TEXTURE_MAP_MODE_WRAP; break;
			case aiTextureMapMode_Clamp: return GMA_TEXTURE_MAP_MODE_CLAMP; break;
			case aiTextureMapMode_Mirror: return GMA_TEXTURE_MAP_MODE_MIRROR; break;
			case aiTextureMapMode_Decal: return GMA_TEXTURE_MAP_MODE_DECAL; break;
			default: return GMA_TEXTURE_MAP_MODE_WRAP; break;
			}
		}

		GMA_TEXTURE_FLAGS ConvertAIEnum(aiTextureFlags ai_enum)
		{
			int pp_step = 0;
			if (ai_enum & aiTextureFlags_Invert) { pp_step |= GMA_TEXTURE_FLAGS_INVERT; }
			if (ai_enum & aiTextureFlags_UseAlpha) { pp_step |= GMA_TEXTURE_FLAGS_USE_ALPHA; }
			if (ai_enum & aiTextureFlags_IgnoreAlpha) { pp_step |= GMA_TEXTURE_FLAGS_IGNORE_ALPHA; }
			return GMA_TEXTURE_FLAGS(pp_step);
		}

		GMA_PRIMITIVE_TYPE ConvertAIEnum(aiPrimitiveType ai_enum)
		{
			int pp_step = 0;
			if (ai_enum & aiPrimitiveType_POINT) { pp_step |= GMA_PRIMITIVE_TYPE_POINT; }
			if (ai_enum & aiPrimitiveType_LINE) { pp_step |= GMA_PRIMITIVE_TYPE_LINE; }
			if (ai_enum & aiPrimitiveType_TRIANGLE) { pp_step |= GMA_PRIMITIVE_TYPE_TRIANGLE; }
			if (ai_enum & aiPrimitiveType_POLYGON) { pp_step |= GMA_PRIMITIVE_TYPE_POLYGON; }
			return GMA_PRIMITIVE_TYPE(pp_step);
		}

		GMA_ANIMATION_BEHAVIOUR ConvertAIEnum(aiAnimBehaviour ai_enum)
		{
			switch (ai_enum)
			{
			case aiAnimBehaviour_DEFAULT: return GMA_ANIMATION_BEHAVIOUR_DEFAULT; break;
			case aiAnimBehaviour_CONSTANT: return GMA_ANIMATION_BEHAVIOUR_CONSTANT; break;
			case aiAnimBehaviour_LINEAR: return GMA_ANIMATION_BEHAVIOUR_LINEAR; break;
			case aiAnimBehaviour_REPEAT: return GMA_ANIMATION_BEHAVIOUR_REPEAT; break;
			default: return GMA_ANIMATION_BEHAVIOUR_DEFAULT; break;
			}
		}

		GMA_MORPH_METHOD ConvertAIEnum(aiMorphingMethod ai_enum)
		{
			switch (ai_enum)
			{
			case aiMorphingMethod_VERTEX_BLEND: return GMA_MORPH_METHOD_VERTEX_BLEND; break;
			case aiMorphingMethod_MORPH_NORMALIZED: return GMA_MORPH_METHOD_MORPH_NORMALIZED; break;
			case aiMorphingMethod_MORPH_RELATIVE: return GMA_MORPH_METHOD_MORPH_RELATIVE; break;
			default: return GMA_MORPH_METHOD_VERTEX_BLEND; break;
			}
		}
	}
}

using namespace GMAssimpEnums;
using namespace GMAssimpEnums::GMEnums;
using namespace GMAssimpEnums::GM_TO_AI;
using namespace GMAssimpEnums::AI_TO_GM;

#define USE_GM_ENUM_LAYER

export double IsWorking()
{
	return 1.0;
}

export double Reset()
{
	importer_id = 0;
	importers.clear();

	act_importer = NULL;
	act_scene = NULL;
	act_mesh = NULL;
	act_material = NULL;
	act_light = NULL;
	act_camera = NULL;
	act_node = NULL;
	act_bone = NULL;
	act_animation = NULL;
	act_node_anim = NULL;
	act_mesh_anim = NULL;

	return true;
}

void SceneDeleted(aiScene* scene)
{
	//check if a resource is in this scene
	if (act_scene == scene) { act_scene = NULL; }
	if (act_mesh_scene == scene)
	{
		act_mesh = NULL;
		act_bone = NULL;
	}
	if (act_material_scene == scene) { act_material = NULL; }
	if (act_light_scene == scene) { act_light = NULL; }
	if (act_camera_scene == scene) { act_camera = NULL; }
	if (act_node_scene == scene) { act_node = NULL; }
	if (act_animation_scene == scene)
	{
		act_animation = NULL;
		act_node_anim = NULL;
		act_mesh_anim = NULL;
	}
}

namespace Importer
{
	export double CreateImporter()
	{
		importers[importer_id];
		importer_id++;
		return importer_id - 1;
	}

	export double BindImporter(double importer_id)
	{
		map <uint, Assimp::Importer>::iterator it = importers.find(importer_id);
		if (it != importers.end())
		{
			if (act_importer != &it->second)
			{
				act_importer = &it->second;
			}
			return true;
		}
		else
		{
			act_importer = NULL;
			return false;
		}
	}

	export double DeleteImporter(double importer_id)
	{
		map <uint, Assimp::Importer>::iterator it = importers.find(importer_id);
		if (it != importers.end())
		{
			if (act_importer == &it->second)
			{
				act_importer = NULL;
			}
			//check if a resource is in this scene/importer
			SceneDeleted((aiScene*)it->second.GetScene());
			//delete the scene
			importers.erase(it);
			return true;
		}

		return false;
	}

	export double ReadFile(const char* filename, double flags)
	{
		if (act_importer)
		{
#ifdef	USE_GM_ENUM_LAYER
			uint ai_flags = (uint)ConvertGMEnum(GMA_POST_PROCESS((uint)flags));
#else
			uint ai_flags = flags;
#endif

			SceneDeleted((aiScene*)act_importer->GetScene());
			return act_importer->ReadFile(filename, ai_flags) != NULL;
		}
		return false;
	}
	//Nuove
	export double ImporterApplyPostProcessing(double flags)
	{
		if (act_importer)
		{
#ifdef USE_GM_ENUM_LAYER
			uint ai_flags = (uint)ConvertGMEnum(GMA_POST_PROCESS((uint)flags));
#else
			uint ai_flags = flags;
#endif

			SceneDeleted((aiScene*)act_importer->GetScene());
			return act_importer->ApplyPostProcessing(ai_flags) != NULL;
		}
		return false;
	}

	export double ImporterFreeScene()
	{
		if (act_importer)
		{
			SceneDeleted((aiScene*)act_importer->GetScene());
			act_importer->FreeScene();
			return true;
		}
		return false;
	}

	export const char* GetImporterErrorString()
	{
		if (act_importer)
		{
			return (char*)act_importer->GetErrorString();
		}
		return "";
	}

	export const char* GetImporterExtensionList()
	{
		if (act_importer)
		{
			ret_string = "";
			act_importer->GetExtensionList(ret_string);
			return (char*)ret_string.C_Str();
		}
		return "";
	}

	export double GetImporterPropertyBool(char* name, double error_return)
	{
		if (act_importer)
		{
			return act_importer->GetPropertyBool(name, error_return);
		}
		return error_return;
	}

	export double GetImporterPropertyFloat(char* name, double error_return)
	{
		if (act_importer)
		{
			return act_importer->GetPropertyFloat(name, error_return);
		}
		return error_return;
	}

	export double GetImporterPropertyInteger(char* name, double error_return)
	{
		if (act_importer)
		{
			return act_importer->GetPropertyInteger(name, error_return);
		}
		return error_return;
	}

	export const char* GetImporterPropertyString(char* name, char* error_return)
	{
		if (act_importer)
		{
			ret_string = act_importer->GetPropertyString(name, error_return).c_str();
			return (char*)ret_string.C_Str();
		}
		return error_return;
	}

	export double CheckImporterExtensionSupported(char* name)
	{
		if (act_importer)
		{
			return act_importer->IsExtensionSupported(name);
		}
		return false;
	}

	export double SetImporterPropertyBool(char* name, double value)
	{
		if (act_importer)
		{
			act_importer->SetPropertyBool(name, value);
		}
		return true;
	}

	export double SetImporterPropertyFloat(char* name, double value)
	{
		if (act_importer)
		{
			act_importer->SetPropertyFloat(name, value);
		}
		return true;
	}

	export double SetImporterPropertyInteger(char* name, double value)
	{
		if (act_importer)
		{
			act_importer->SetPropertyInteger(name, value);
		}
		return true;
	}

	export double SetImporterPropertyString(char* name, char* value)
	{
		if (act_importer)
		{
			act_importer->SetPropertyString(name, value);
		}
		return true;
	}

	export double ImporterValidateFlags(double flags)
	{
		if (act_importer)
		{
#ifdef USE_GM_ENUM_LAYER
			uint ai_flags = (uint)ConvertGMEnum(GMA_POST_PROCESS((uint)flags));
#else
			uint ai_flags = flags;
#endif

			return act_importer->ValidateFlags(ai_flags);
		}
		return false;
	}
}

namespace Scene
{
	export double BindScene()
	{
		if (act_importer)
		{
			if (act_scene != act_importer->GetScene())
			{
				act_scene = (aiScene*)act_importer->GetScene();
			}
			return true;
		}
		return false;
	}

	export double GetMeshNum()
	{
		if (act_scene)
		{
			return act_scene->mNumMeshes;
		}
		return 0;
	}

	export double GetMaterialNum()
	{
		if (act_scene)
		{
			return act_scene->mNumMaterials;
		}
		return 0;
	}

	export double GetLightNum()
	{
		if (act_scene)
		{
			return act_scene->mNumLights;
		}
		return 0;
	}

	export double GetCameraNum()
	{
		if (act_scene)
		{
			return act_scene->mNumCameras;
		}
		return 0;
	}

	export double GetAnimationNum()
	{
		if (act_scene)
		{
			return act_scene->mNumAnimations;
		}
		return 0;
	}

}

namespace Mesh
{
	namespace Proprieties
	{
		export double BindMesh(double mesh_id)
		{
			if (act_scene)
			{
				if (mesh_id < 0 || mesh_id >= act_scene->mNumMeshes)
				{
					act_mesh_scene = NULL;
					act_mesh = NULL;
					return false;
				}
				else
				{
					act_mesh_scene = act_scene;
					act_mesh = act_mesh_scene->mMeshes[(uint)mesh_id];
					return true;
				}
			}
			else
			{
				act_mesh_scene = NULL;
				act_mesh = NULL;
				return false;
			}
		}

		export double GetMeshMaterialIndex()
		{
			if (!act_mesh) { return -1; }
			return act_mesh->mMaterialIndex;
		}

		export double MeshHasBones()
		{
			if (!act_mesh) { return false; }
			return act_mesh->HasBones();
		}

		export double MeshHasFaces()
		{
			if (!act_mesh) { return false; }
			return act_mesh->HasFaces();
		}

		export double MeshHasPositions()
		{
			if (!act_mesh) { return false; }
			return act_mesh->HasPositions();
		}

		export double MeshHasNormals()
		{
			if (!act_mesh) { return false; }
			return act_mesh->HasNormals();
		}

		export double MeshHasTexCoords(double texture_channel)
		{
			if (!act_mesh) { return false; }
			return act_mesh->HasTextureCoords((uint)texture_channel);
		}

		export double MeshHasVertexColors(double color_channel)
		{
			if (!act_mesh) { return false; }
			return act_mesh->HasVertexColors((uint)color_channel);
		}

		export double MeshHasTangents()
		{
			if (!act_mesh) { return false; }
			return act_mesh->HasTangentsAndBitangents();
		}

		export double GetMeshUVChannelsNum()
		{
			if (!act_mesh) { return 0; }
			return act_mesh->GetNumUVChannels();
		}

		export double GetMeshColorChannelsNum()
		{
			if (!act_mesh) { return 0; }
			return act_mesh->GetNumColorChannels();
		}

		export const char* GetMeshName()
		{
			if (!act_mesh) { return ""; }
			return (char*)act_mesh->mName.C_Str();
		}

		export double GetMeshPrimitiveTypes()
		{
			if (!act_mesh) { return 0; }
#ifdef USE_GM_ENUM_LAYER
			return ConvertAIEnum(aiPrimitiveType(act_mesh->mPrimitiveTypes));
#else
			return act_mesh->mPrimitiveTypes;
#endif
		}

		export double GetMeshMorphMethod()
		{
			if (!act_mesh) { return 0; }
#ifdef USE_GM_ENUM_LAYER
			return ConvertAIEnum(aiMorphingMethod(act_mesh->mMethod));
#else
			return act_mesh->mMethod;
#endif
		}

		export double GetMeshAABBMinX()
		{
			if (!act_mesh) { return 0; }
			return act_mesh->mAABB.mMin.x;
		}

		export double GetMeshAABBMinY()
		{
			if (!act_mesh) { return 0; }
			return act_mesh->mAABB.mMin.y;
		}

		export double GetMeshAABBMinZ()
		{
			if (!act_mesh) { return 0; }
			return act_mesh->mAABB.mMin.z;
		}

		export double GetMeshAABBMaxX()
		{
			if (!act_mesh) { return 0; }
			return act_mesh->mAABB.mMax.x;
		}

		export double GetMeshAABBMaxY()
		{
			if (!act_mesh) { return 0; }
			return act_mesh->mAABB.mMax.y;
		}

		export double GetMeshAABBMaxZ()
		{
			if (!act_mesh) { return 0; }
			return act_mesh->mAABB.mMax.z;
		}

		export const char* GetMeshTextureCoordsName(double texture_channel)
		{
			if (!act_mesh) { return ""; }
			if (texture_channel >= act_mesh->GetNumUVChannels()) { return ""; }
			return act_mesh->mTextureCoordsNames[(uint)texture_channel]->C_Str();
		}
	}

	namespace Data
	{
		export double GetMeshBonesNum()
		{
			if (!act_mesh) { return 0; }
			return act_mesh->mNumBones;
		}

		export double GetMeshFacesNum()
		{
			if (!act_mesh) { return 0; }
			return act_mesh->mNumFaces;
		}

		export double GetMeshVerticesNum()
		{
			if (!act_mesh) { return 0; }
			return act_mesh->mNumVertices;
		}

		export double GetMeshFaceVerticesNum(double face_id)
		{
			if (!act_mesh) { return 0; }
			if (face_id < 0 || face_id >= act_mesh->mNumFaces) { return 0; }
			return act_mesh->mFaces[(uint)face_id].mNumIndices;
		}

		export double GetMeshFaceVertexIndex(double face_id, double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (face_id < 0 || face_id >= act_mesh->mNumFaces) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mFaces[(uint)face_id].mNumIndices) { return 0; }
			return act_mesh->mFaces[(uint)face_id].mIndices[(uint)vertex_id];
		}

		export double GetMeshVertexX(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mVertices[(uint)vertex_id].x;
		}

		export double GetMeshVertexY(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mVertices[(uint)vertex_id].y;
		}

		export double GetMeshVertexZ(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mVertices[(uint)vertex_id].z;
		}

		export double GetMeshNormalX(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (!act_mesh->HasNormals()) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mNormals[(uint)vertex_id].x;
		}

		export double GetMeshNormalY(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (!act_mesh->HasNormals()) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mNormals[(uint)vertex_id].y;
		}

		export double GetMeshNormalZ(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (!act_mesh->HasNormals()) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mNormals[(uint)vertex_id].z;
		}

		export double GetMeshTexCoordU(double vertex_id, double texture_channel)
		{
			if (!act_mesh) { return 0; }
			if (!(texture_channel < act_mesh->GetNumUVChannels())) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mTextureCoords[(uint)texture_channel][(uint)vertex_id].x;
		}

		export double GetMeshTexCoordV(double vertex_id, double texture_channel)
		{
			if (!act_mesh) { return 0; }
			if (!(texture_channel < act_mesh->GetNumUVChannels())) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mTextureCoords[(uint)texture_channel][(uint)vertex_id].y;
		}

		export double GetMeshTexCoordW(double vertex_id, double texture_channel)
		{
			if (!act_mesh) { return 0; }
			if (!(texture_channel < act_mesh->GetNumUVChannels())) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mTextureCoords[(uint)texture_channel][(uint)vertex_id].z;
		}

		export double GetMeshVertexColorGM(double vertex_id, double color_channel)
		{
			if (!act_mesh) { return 0; }
			if (!(color_channel < act_mesh->GetNumColorChannels())) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			aiColor4D col = act_mesh->mColors[(uint)color_channel][(uint)vertex_id];
			return aiColorToGmColor(aiColor3D(col.r, col.g, col.b));
		}

		export double GetMeshVertexColorR(double vertex_id, double color_channel)
		{
			if (!act_mesh) { return 0; }
			if (!(color_channel < act_mesh->GetNumColorChannels())) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			aiColor4D col = act_mesh->mColors[(uint)color_channel][(uint)vertex_id];
			return col.r;
		}

		export double GetMeshVertexColorG(double vertex_id, double color_channel)
		{
			if (!act_mesh) { return 0; }
			if (!(color_channel < act_mesh->GetNumColorChannels())) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			aiColor4D col = act_mesh->mColors[(uint)color_channel][(uint)vertex_id];
			return col.g;
		}

		export double GetMeshVertexColorB(double vertex_id, double color_channel)
		{
			if (!act_mesh) { return 0; }
			if (!(color_channel < act_mesh->GetNumColorChannels())) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			aiColor4D col = act_mesh->mColors[(uint)color_channel][(uint)vertex_id];
			return col.b;
		}

		export double GetMeshVertexAlpha(double vertex_id, double color_channel)
		{
			if (!act_mesh) { return 0; }
			if (!(color_channel < act_mesh->GetNumColorChannels())) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			aiColor4D col = act_mesh->mColors[(uint)color_channel][(uint)vertex_id];
			return col.a;
		}

		export double GetMeshTangentX(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (!act_mesh->HasTangentsAndBitangents()) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mTangents[(uint)vertex_id].x;
		}

		export double GetMeshTangentY(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (!act_mesh->HasTangentsAndBitangents()) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mTangents[(uint)vertex_id].y;
		}

		export double GetMeshTangentZ(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (!act_mesh->HasTangentsAndBitangents()) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mTangents[(uint)vertex_id].z;
		}

		export double GetMeshBitangentX(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (!act_mesh->HasTangentsAndBitangents()) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mBitangents[(uint)vertex_id].x;
		}

		export double GetMeshBitangentY(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (!act_mesh->HasTangentsAndBitangents()) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mBitangents[(uint)vertex_id].y;
		}

		export double GetMeshBitangentZ(double vertex_id)
		{
			if (!act_mesh) { return 0; }
			if (!act_mesh->HasTangentsAndBitangents()) { return 0; }
			if (vertex_id < 0 || vertex_id >= act_mesh->mNumVertices) { return 0; }
			return act_mesh->mBitangents[(uint)vertex_id].z;
		}
	}
}

namespace Material
{
	namespace Proprieties
	{
		export double BindMaterial(double material_id)
		{
			if (act_scene)
			{
				if (material_id < 0 || material_id >= act_scene->mNumMaterials)
				{
					act_material_scene = NULL;
					act_material = NULL;
					return false;
				}
				else
				{
					act_material_scene = act_scene;
					act_material = act_material_scene->mMaterials[(uint)material_id];
					return true;
				}
			}
			else
			{
				act_material_scene = NULL;
				act_material = NULL;
				return false;
			}
		}

		export double CheckMaterialEnableWireframe()
		{
			if (!act_material) { return 0; }
			int check;
			act_material->Get(AI_MATKEY_ENABLE_WIREFRAME, check);
			return check;
		}

		export double CheckMaterialTwoSided()
		{
			if (!act_material) { return 0; }
			int check;
			act_material->Get(AI_MATKEY_TWOSIDED, check);
			return check;
		}

		export const char* GetMaterialName()
		{
			if (!act_material) { return ""; }
			return (char*)act_material->GetName().C_Str();
		}


		export double GetMaterialShadingModel()
		{
			if (!act_material) { return GMA_SHADING_MODE_NO_SHADING; }
			int value;
			act_material->Get(AI_MATKEY_SHADING_MODEL, value);

#ifdef USE_GM_ENUM_LAYER
			return ConvertAIEnum(aiShadingMode(value));
#else
			return value;
#endif
		}

		export double GetMaterialBlendFunc()
		{
			if (!act_material) { return GMA_BLEND_MODE_DEFAULT; }
			int value;
			act_material->Get(AI_MATKEY_BLEND_FUNC, value);

#ifdef USE_GM_ENUM_LAYER
			return ConvertAIEnum(aiBlendMode(value));
#else
			return value;
#endif
		}

		export double GetMaterialTextureBlend(double t, double n)
		{
			if (!act_material) { return 0; }
#ifdef USE_GM_ENUM_LAYER
			uint ai_t = (uint)ConvertGMEnum(GMA_TEXTURE_TYPE((uint)t));
#else
			uint ai_t = t;
#endif

			float value;
			act_material->Get(AI_MATKEY_TEXBLEND((uint)ai_t, (uint)n), value);
			return value;
		}

		export double GetMaterialTextureOperation(double t, double n)
		{
			if (!act_material) { return GMA_TEXTURE_OP_MULTIPLY; }
#ifdef USE_GM_ENUM_LAYER
			uint ai_t = (uint)ConvertGMEnum(GMA_TEXTURE_TYPE((uint)t));
#else
			uint ai_t = t;
#endif

			int value;
			act_material->Get(AI_MATKEY_TEXOP((uint)ai_t, (uint)n), value);

#ifdef USE_GM_ENUM_LAYER
			return ConvertAIEnum(aiTextureOp(value));
#else
			return value;
#endif
		}

		export double GetMaterialMapping(double t, double n)
		{
			if (!act_material) { return GMA_TEXTURE_MAPPING_UV; }
#ifdef USE_GM_ENUM_LAYER
			uint ai_t = (uint)ConvertGMEnum(GMA_TEXTURE_TYPE((uint)t));
#else
			uint ai_t = t;
#endif

			int value;
			act_material->Get(AI_MATKEY_MAPPING((uint)ai_t, (uint)n), value);

#ifdef USE_GM_ENUM_LAYER
			return ConvertAIEnum(aiTextureMapping(value));
#else
			return value;
#endif
		}

		export double GetMaterialUVWSource(double t, double n)
		{
			if (!act_material) { return 0; }
#ifdef USE_GM_ENUM_LAYER
			uint ai_t = (uint)ConvertGMEnum(GMA_TEXTURE_TYPE((uint)t));
#else
			uint ai_t = t;
#endif

			int value;
			act_material->Get(AI_MATKEY_UVWSRC((uint)ai_t, (uint)n), value);
			return value;
		}

		export double GetMaterialMappingModeU(double t, double n)
		{
			if (!act_material) { return GMA_TEXTURE_MAP_MODE_WRAP; }
#ifdef USE_GM_ENUM_LAYER
			uint ai_t = (uint)ConvertGMEnum(GMA_TEXTURE_TYPE((uint)t));
#else
			uint ai_t = t;
#endif

			int value;
			act_material->Get(AI_MATKEY_MAPPINGMODE_U((uint)ai_t, (uint)n), value);

#ifdef USE_GM_ENUM_LAYER
			return ConvertAIEnum(aiTextureMapMode(value));
#else
			return value;
#endif
		}

		export double GetMaterialMappingModeV(double t, double n)
		{
			if (!act_material) { return GMA_TEXTURE_MAP_MODE_WRAP; }
#ifdef USE_GM_ENUM_LAYER
			uint ai_t = (uint)ConvertGMEnum(GMA_TEXTURE_TYPE((uint)t));
#else
			uint ai_t = t;
#endif

			int value;
			act_material->Get(AI_MATKEY_MAPPINGMODE_V((uint)ai_t, (uint)n), value);

#ifdef USE_GM_ENUM_LAYER
			return ConvertAIEnum(aiTextureMapMode(value));
#else
			return value;
#endif
		}

		export double GetMaterialTextureMapAxisX(double t, double n)
		{
			if (!act_material) { return 0; }
#ifdef USE_GM_ENUM_LAYER
			uint ai_t = (uint)ConvertGMEnum(GMA_TEXTURE_TYPE((uint)t));
#else
			uint ai_t = t;
#endif

			aiVector3D value;
			act_material->Get(AI_MATKEY_TEXMAP_AXIS((uint)ai_t, (uint)n), value);
			return value.x;
		}

		export double GetMaterialTextureMapAxisY(double t, double n)
		{
			if (!act_material) { return 0; }
#ifdef USE_GM_ENUM_LAYER
			uint ai_t = (uint)ConvertGMEnum(GMA_TEXTURE_TYPE((uint)t));
#else
			uint ai_t = t;
#endif

			aiVector3D value;
			act_material->Get(AI_MATKEY_TEXMAP_AXIS((uint)ai_t, (uint)n), value);
			return value.y;
		}

		export double GetMaterialTextureMapAxisZ(double t, double n)
		{
			if (!act_material) { return 0; }
#ifdef USE_GM_ENUM_LAYER
			uint ai_t = (uint)ConvertGMEnum(GMA_TEXTURE_TYPE((uint)t));
#else
			uint ai_t = t;
#endif

			aiVector3D value;
			act_material->Get(AI_MATKEY_TEXMAP_AXIS((uint)ai_t, (uint)n), value);
			return value.z;
		}

		export double GetMaterialTextureFlags(double t, double n)
		{
			if (!act_material) { return 0; }
#ifdef USE_GM_ENUM_LAYER
			uint ai_t = (uint)ConvertGMEnum(GMA_TEXTURE_TYPE((uint)t));
#else
			uint ai_t = t;
#endif

			int value;
			act_material->Get(AI_MATKEY_TEXFLAGS((uint)ai_t, (uint)n), value);

#ifdef USE_GM_ENUM_LAYER
			return ConvertAIEnum(aiTextureFlags(value));
#else
			return value;
#endif
		}
	}

	namespace Data
	{
		export const char* GetMaterialTextureName(double t, double n)
		{
			if (!act_material) { return ""; }
#ifdef USE_GM_ENUM_LAYER
			uint ai_t = (uint)ConvertGMEnum(GMA_TEXTURE_TYPE((uint)t));
#else
			uint ai_t = t;
#endif
			ret_string = "";
			act_material->Get(AI_MATKEY_TEXTURE(ai_t, (uint)n), ret_string);
			return (char*)ret_string.C_Str();
		}

		export double GetMaterialDiffuseColorGM()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_DIFFUSE, col);
			return aiColorToGmColor(col);
		}

		export double GetMaterialDiffuseColorR()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_DIFFUSE, col);
			return col.r;
		}

		export double GetMaterialDiffuseColorG()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_DIFFUSE, col);
			return col.g;
		}

		export double GetMaterialDiffuseColorB()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_DIFFUSE, col);
			return col.b;
		}

		export double GetMaterialAmbientColorGM()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_AMBIENT, col);
			return aiColorToGmColor(col);
		}

		export double GetMaterialAmbientColorR()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_AMBIENT, col);
			return col.r;
		}

		export double GetMaterialAmbientColorG()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_AMBIENT, col);
			return col.g;
		}

		export double GetMaterialAmbientColorB()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_AMBIENT, col);
			return col.b;
		}

		export double GetMaterialEmissiveColorGM()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_EMISSIVE, col);
			return aiColorToGmColor(col);
		}

		export double GetMaterialEmissiveColorR()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_EMISSIVE, col);
			return col.r;
		}

		export double GetMaterialEmissiveColorG()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_EMISSIVE, col);
			return col.g;
		}

		export double GetMaterialEmissiveColorB()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_EMISSIVE, col);
			return col.b;
		}

		export double GetMaterialSpecularColorGM()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_SPECULAR, col);
			return aiColorToGmColor(col);
		}

		export double GetMaterialSpecularColorR()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_SPECULAR, col);
			return col.r;
		}

		export double GetMaterialSpecularColorG()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_SPECULAR, col);
			return col.g;
		}

		export double GetMaterialSpecularColorB()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_SPECULAR, col);
			return col.b;
		}

		export double GetMaterialTransparentColorGM()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_TRANSPARENT, col);
			return aiColorToGmColor(col);
		}

		export double GetMaterialTransparentColorR()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_TRANSPARENT, col);
			return col.r;
		}

		export double GetMaterialTransparentColorG()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_TRANSPARENT, col);
			return col.g;
		}

		export double GetMaterialTransparentColorB()
		{
			if (!act_material) { return 0; }
			aiColor3D col;
			act_material->Get(AI_MATKEY_COLOR_TRANSPARENT, col);
			return col.b;
		}

		export double GetMaterialOpacity()
		{
			if (!act_material) { return 0; }
			float value;
			act_material->Get(AI_MATKEY_OPACITY, value);
			return value;
		}

		export double GetMaterialShininess()
		{
			if (!act_material) { return 0; }
			float value;
			act_material->Get(AI_MATKEY_SHININESS, value);
			return value;
		}

		export double GetMaterialShininessStrength()
		{
			if (!act_material) { return 0; }
			float value;
			act_material->Get(AI_MATKEY_SHININESS_STRENGTH, value);
			return value;
		}

		export double GetMaterialRefracti()
		{
			if (!act_material) { return 0; }
			float value;
			act_material->Get(AI_MATKEY_REFRACTI, value);
			return value;
		}
	}
}

namespace Light
{
	export double BindLight(double light_id)
	{
		if (act_scene)
		{
			if (light_id < 0 || light_id >= act_scene->mNumLights)
			{
				act_light_scene = NULL;
				act_light = NULL;
				return false;
			}
			else
			{
				act_light_scene = act_scene;
				act_light = act_light_scene->mLights[(uint)light_id];
				return true;
			}
		}
		else
		{
			act_light_scene = NULL;
			act_light = NULL;
			return false;
		}
	}

	export double GetLightConeInnerAngle()
	{
		if (!act_light) { return 0; }
		return act_light->mAngleInnerCone;
	}

	export double GetLightConeOuterAngle()
	{
		if (!act_light) { return 0; }
		return act_light->mAngleOuterCone;
	}

	export double GetLightConstantAttenutation()
	{
		if (!act_light) { return 0; }
		return act_light->mAttenuationConstant;
	}

	export double GetLightLinearAttenutation()
	{
		if (!act_light) { return 0; }
		return act_light->mAttenuationLinear;
	}

	export double GetLightQuadraticAttenutation()
	{
		if (!act_light) { return 0; }
		return act_light->mAttenuationQuadratic;
	}

	export double GetLightDiffuseColorGM()
	{
		if (!act_light) { return 0; }
		return aiColorToGmColor(act_light->mColorDiffuse);
	}

	export double GetLightDiffuseColorR()
	{
		if (!act_light) { return 0; }
		return act_light->mColorDiffuse.r;
	}

	export double GetLightDiffuseColorG()
	{
		if (!act_light) { return 0; }
		return act_light->mColorDiffuse.g;
	}

	export double GetLightDiffuseColorB()
	{
		if (!act_light) { return 0; }
		return act_light->mColorDiffuse.b;
	}

	export double GetLightAmbientColorGM()
	{
		if (!act_light) { return 0; }
		return aiColorToGmColor(act_light->mColorAmbient);
	}

	export double GetLightAmbientColorR()
	{
		if (!act_light) { return 0; }
		return act_light->mColorAmbient.r;
	}

	export double GetLightAmbientColorG()
	{
		if (!act_light) { return 0; }
		return act_light->mColorAmbient.g;
	}

	export double GetLightAmbientColorB()
	{
		if (!act_light) { return 0; }
		return act_light->mColorAmbient.b;
	}

	export double GetLightSpecularColorGM()
	{
		if (!act_light) { return 0; }
		return aiColorToGmColor(act_light->mColorSpecular);
	}

	export double GetLightSpecularColorR()
	{
		if (!act_light) { return 0; }
		return act_light->mColorSpecular.r;
	}

	export double GetLightSpecularColorG()
	{
		if (!act_light) { return 0; }
		return act_light->mColorSpecular.g;
	}

	export double GetLightSpecularColorB()
	{
		if (!act_light) { return 0; }
		return act_light->mColorSpecular.b;
	}

	export double GetLightDirectionX()
	{
		if (!act_light) { return 0; }
		return act_light->mDirection.x;
	}

	export double GetLightDirectionY()
	{
		if (!act_light) { return 0; }
		return act_light->mDirection.y;
	}

	export double GetLightDirectionZ()
	{
		if (!act_light) { return 0; }
		return act_light->mDirection.z;
	}

	export const char* GetLightName()
	{
		if (!act_light) { return ""; }
		return (char*)act_light->mName.C_Str();
	}

	export double GetLightPositionX()
	{
		if (!act_light) { return 0; }
		return act_light->mPosition.x;
	}

	export double GetLightPositionY()
	{
		if (!act_light) { return 0; }
		return act_light->mPosition.y;
	}

	export double GetLightPositionZ()
	{
		if (!act_light) { return 0; }
		return act_light->mPosition.z;
	}

	export double GetLightSizeX()
	{
		if (!act_light) { return 0; }
		return act_light->mSize.x;
	}

	export double GetLightSizeY()
	{
		if (!act_light) { return 0; }
		return act_light->mSize.y;
	}

	export double GetLightUpX()
	{
		if (!act_light) { return 0; }
		return act_light->mUp.x;
	}

	export double GetLightUpY()
	{
		if (!act_light) { return 0; }
		return act_light->mUp.y;
	}

	export double GetLightUpZ()
	{
		if (!act_light) { return 0; }
		return act_light->mUp.z;
	}

	export double GetLightSourceType()
	{
		if (!act_light) { return GMA_LIGHT_SOURCE_UNDEFINED; }
#ifdef USE_GM_ENUM_LAYER
		return ConvertAIEnum(act_light->mType);
#else
		return act_light->mType;
#endif
	}
}

namespace Camera
{
	export double BindCamera(double camera_id)
	{
		if (act_scene)
		{
			if (camera_id < 0 || camera_id >= act_scene->mNumCameras)
			{
				act_camera_scene = NULL;
				act_camera = NULL;
				return false;
			}
			else
			{
				act_camera_scene = act_scene;
				act_camera = act_camera_scene->mCameras[(uint)camera_id];
				return true;
			}
		}
		else
		{
			act_camera_scene = NULL;
			act_camera = NULL;
			return false;
		}
	}

	export double GetCameraAspect()
	{
		if (!act_camera) { return 0; }
		return act_camera->mAspect;
	}

	export double GetCameraClipPlaneFar()
	{
		if (!act_camera) { return 0; }
		return act_camera->mClipPlaneFar;
	}

	export double GetCameraClipPlaneNear()
	{
		if (!act_camera) { return 0; }
		return act_camera->mClipPlaneNear;
	}

	export double GetCameraHorizontalFov()
	{
		if (!act_camera) { return 0; }
		return act_camera->mHorizontalFOV;
	}

	export double GetCameraLookAtX()
	{
		if (!act_camera) { return 0; }
		return act_camera->mLookAt.x;
	}

	export double GetCameraLookAtY()
	{
		if (!act_camera) { return 0; }
		return act_camera->mLookAt.y;
	}

	export double GetCameraLookAtZ()
	{
		if (!act_camera) { return 0; }
		return act_camera->mLookAt.z;
	}

	export const char* GetCameraName()
	{
		if (!act_camera) { return ""; }
		return (char*)act_camera->mName.C_Str();
	}

	export double GetCameraPositionX()
	{
		if (!act_camera) { return 0; }
		return act_camera->mPosition.x;
	}

	export double GetCameraPositionY()
	{
		if (!act_camera) { return 0; }
		return act_camera->mPosition.y;
	}

	export double GetCameraPositionZ()
	{
		if (!act_camera) { return 0; }
		return act_camera->mPosition.z;
	}

	export double GetCameraUpX()
	{
		if (!act_camera) { return 0; }
		return act_camera->mUp.x;
	}

	export double GetCameraUpY()
	{
		if (!act_camera) { return 0; }
		return act_camera->mUp.y;
	}

	export double GetCameraUpZ()
	{
		if (!act_camera) { return 0; }
		return act_camera->mUp.z;
	}

	export double BindCameraMatrix()
	{
		if (!act_camera) { return false; }
		act_camera->GetCameraMatrix(act_matrix);
		return true;
	}
}

namespace Matrix
{
	export double GetMatrixA1()
	{
		return act_matrix.a1;
	}
	export double GetMatrixA2()
	{
		return act_matrix.a2;
	}
	export double GetMatrixA3()
	{
		return act_matrix.a3;
	}
	export double GetMatrixA4()
	{
		return act_matrix.a4;
	}
	export double GetMatrixB1()
	{
		return act_matrix.b1;
	}
	export double GetMatrixB2()
	{
		return act_matrix.b2;
	}
	export double GetMatrixB3()
	{
		return act_matrix.b3;
	}
	export double GetMatrixB4()
	{
		return act_matrix.b4;
	}
	export double GetMatrixC1()
	{
		return act_matrix.c1;
	}
	export double GetMatrixC2()
	{
		return act_matrix.c2;
	}
	export double GetMatrixC3()
	{
		return act_matrix.c3;
	}
	export double GetMatrixC4()
	{
		return act_matrix.c4;
	}
	export double GetMatrixD1()
	{
		return act_matrix.d1;
	}
	export double GetMatrixD2()
	{
		return act_matrix.d2;
	}
	export double GetMatrixD3()
	{
		return act_matrix.d3;
	}
	export double GetMatrixD4()
	{
		return act_matrix.d4;
	}
}

namespace Node
{
	export double BindSceneNode()
	{
		if (act_scene)
		{
			act_node_scene = act_scene;
			act_node = act_node_scene->mRootNode;
			return true;
		}
		else
		{
			act_node_scene = NULL;
			act_node = NULL;
			return false;
		}
	}

	export double GetNodeChildrenNum()
	{
		if (!act_node) { return 0; }
		return act_node->mNumChildren;
	}

	export double GetNodeMeshNum()
	{
		if (!act_node) { return 0; }
		return act_node->mNumMeshes;
	}

	export const char* GetNodeName()
	{
		if (!act_node) { return ""; }
		return (char*)act_node->mName.C_Str();
	}

	export double GetNodeMeshIndex(double mesh_id)
	{
		if (!act_node) { return -1; }
		if (mesh_id < 0 || mesh_id >= act_node->mNumMeshes)
		{
			return -1;
		}
		else
		{
			return act_node->mMeshes[(uint)mesh_id];
		}
	}

	export double BindNodeParent()
	{
		if (!act_node) { return false; }
		act_node = act_node->mParent;
		if (act_node == NULL)
		{
			act_node_scene = NULL;
			return false;
		}
		return true;
	}

	export double BindNodeChild(double node_id)
	{
		if (!act_node) { return false; }
		if (node_id < 0 || node_id >= act_node->mNumChildren)
		{
			act_node_scene = NULL;
			act_node = NULL;
			return false;
		}
		else
		{
			act_node = act_node->mChildren[(uint)node_id];
			return true;
		}
	}

	export double CheckChildNodeExist(char* name)
	{
		if (!act_node) { return false; }
		return act_node->FindNode(name) != NULL;
	}

	export double BindNodeChildFromName(char* name)
	{
		if (!act_node) { return false; }
		act_node = act_node->FindNode(name);
		if (act_node == NULL) {
			act_node_scene = NULL;
			return false;
		}
		return true;
	}

	export double BindNodeMatrix()
	{
		if (!act_node)
		{
			act_matrix = aiMatrix4x4();
			return false;
		}
		act_matrix = act_node->mTransformation;
		return true;
	}
}

namespace Bone
{
	export double BindMeshBone(double bone_id)
	{
		if (!act_mesh) { return false; }
		if (bone_id < 0 || bone_id >= act_mesh->mNumBones)
		{
			return false;
		}
		else
		{
			act_bone = act_mesh->mBones[(uint)bone_id];
			return true;
		}
	}

	export double GetBoneNumWeights()
	{
		if (!act_bone) { return 0; }
		return act_bone->mNumWeights;
	}

	export const char* GetBoneName()
	{
		if (!act_bone) { return ""; }
		return (char*)act_bone->mName.C_Str();
	}

	export double GetBoneVertexIndex(double bone_vert_id)
	{
		if (!act_bone) { return 0; }
		if (bone_vert_id < 0 || bone_vert_id >= act_bone->mNumWeights)
		{
			return 0;
		}
		else
		{
			return act_bone->mWeights[(uint)bone_vert_id].mVertexId;
		}
	}

	export double GetBoneVertexWeight(double bone_vert_id)
	{
		if (!act_bone) { return 0; }
		if (bone_vert_id < 0 || bone_vert_id >= act_bone->mNumWeights)
		{
			return 0;
		}
		else
		{
			return act_bone->mWeights[(uint)bone_vert_id].mWeight;
		}
	}

	export double BindBoneOffsetMatrix()
	{
		if (!act_bone) { return false; }
		act_matrix = act_bone->mOffsetMatrix;
		return true;
	}
}

namespace Animation
{
	namespace General
	{
		export double BindAnimation(double anim_id)
		{
			if (act_scene)
			{
				if (anim_id < 0 || anim_id >= act_scene->mNumAnimations)
				{
					act_animation_scene = NULL;
					act_animation = NULL;
					return false;
				}
				else
				{
					act_animation_scene = act_scene;
					act_animation = act_animation_scene->mAnimations[(uint)anim_id];
					return true;
				}
			}
			else
			{
				act_animation_scene = NULL;
				act_animation = NULL;
				return false;
			}
		}

		export double GetAnimationDuration()
		{
			if (!act_animation) { return 0; }
			return act_animation->mDuration;
		}

		export double GetAnimationTicksPerSecond()
		{
			if (!act_animation) { return 0; }
			return act_animation->mTicksPerSecond;
		}

		export double GetAnimationNodeChannelsNum()
		{
			if (!act_animation) { return 0; }
			return act_animation->mNumChannels;
		}

		export double GetAnimationMeshChannelsNum()
		{
			if (!act_animation) { return 0; }
			return act_animation->mNumMeshChannels;
		}

		export const char* GetAnimationName()
		{
			if (!act_animation) { return ""; }
			return (char*)act_animation->mName.C_Str();
		}
	}

	namespace NodeAnimations
	{
		export double BindNodeAnimation(double node_anim_id)
		{
			if (!act_animation)
			{
				act_node_anim = NULL;
				return false;
			}
			if (node_anim_id < 0 || node_anim_id >= act_animation->mNumChannels)
			{
				act_node_anim = NULL;
				return false;
			}
			else
			{
				act_node_anim = act_animation->mChannels[(uint)node_anim_id];
				return true;
			}
		}

		export const char* GetNodeAnimNodeName()
		{
			if (!act_node_anim) { return ""; }
			return (char*)act_node_anim->mNodeName.C_Str();
		}

		export double GetNodeAnimPositionKeysNum()
		{
			if (!act_node_anim) { return 0; }
			return act_node_anim->mNumPositionKeys;
		}

		export double GetNodeAnimRotationKeysNum()
		{
			if (!act_node_anim) { return 0; }
			return act_node_anim->mNumRotationKeys;
		}

		export double GetNodeAnimScalingKeysNum()
		{
			if (!act_node_anim) { return 0; }
			return act_node_anim->mNumScalingKeys;
		}

		export double GetNodeAnimPositionKeyTime(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumPositionKeys)
			{
				return 0;
			}
			return act_node_anim->mPositionKeys[(uint)key_id].mTime;
		}

		export double GetNodeAnimPositionKeyValueX(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumPositionKeys)
			{
				return 0;
			}
			return act_node_anim->mPositionKeys[(uint)key_id].mValue.x;
		}

		export double GetNodeAnimPositionKeyValueY(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumPositionKeys)
			{
				return 0;
			}
			return act_node_anim->mPositionKeys[(uint)key_id].mValue.y;
		}

		export double GetNodeAnimPositionKeyValueZ(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumPositionKeys)
			{
				return 0;
			}
			return act_node_anim->mPositionKeys[(uint)key_id].mValue.z;
		}

		export double GetNodeAnimRotationKeyTime(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumRotationKeys)
			{
				return 0;
			}
			return act_node_anim->mRotationKeys[(uint)key_id].mTime;
		}

		export double GetNodeAnimRotationKeyQuaternionX(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumRotationKeys)
			{
				return 0;
			}
			return act_node_anim->mRotationKeys[(uint)key_id].mValue.x;
		}

		export double GetNodeAnimRotationKeyQuaternionY(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumRotationKeys)
			{
				return 0;
			}
			return act_node_anim->mRotationKeys[(uint)key_id].mValue.y;
		}

		export double GetNodeAnimRotationKeyQuaternionZ(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumRotationKeys)
			{
				return 0;
			}
			return act_node_anim->mRotationKeys[(uint)key_id].mValue.z;
		}

		export double GetNodeAnimRotationKeyQuaternionW(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumRotationKeys)
			{
				return 0;
			}
			return act_node_anim->mRotationKeys[(uint)key_id].mValue.w;
		}

		export double GetNodeAnimScalingKeyTime(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumScalingKeys)
			{
				return 0;
			}
			return act_node_anim->mScalingKeys[(uint)key_id].mTime;
		}

		export double GetNodeAnimScalingKeyValueX(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumScalingKeys)
			{
				return 0;
			}
			return act_node_anim->mScalingKeys[(uint)key_id].mValue.x;
		}

		export double GetNodeAnimScalingKeyValueY(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumScalingKeys)
			{
				return 0;
			}
			return act_node_anim->mScalingKeys[(uint)key_id].mValue.y;
		}

		export double GetNodeAnimScalingKeyValueZ(double key_id)
		{
			if (!act_node_anim) { return 0; }
			if (key_id < 0 || key_id >= act_node_anim->mNumScalingKeys)
			{
				return 0;
			}
			return act_node_anim->mScalingKeys[(uint)key_id].mValue.z;
		}

		export double GetNodeAnimPostState()
		{
			if (!act_node_anim) { return GMA_ANIMATION_BEHAVIOUR_DEFAULT; }
#ifdef USE_GM_ENUM_LAYER
			return ConvertAIEnum(act_node_anim->mPostState);
#else
			return act_node_anim->mPostState;
#endif
		}

		export double GetNodeAnimPreState()
		{
			if (!act_node_anim) { return GMA_ANIMATION_BEHAVIOUR_DEFAULT; }
#ifdef USE_GM_ENUM_LAYER
			return ConvertAIEnum(act_node_anim->mPreState);
#else
			return act_node_anim->mPreState;
#endif
		}
	}

	namespace MeshAnimations
	{
		export double BindMeshAnimation(double mesh_anim_id)
		{
			if (!act_animation) { return false; }
			if (mesh_anim_id < 0 || mesh_anim_id >= act_animation->mNumMeshChannels)
			{
				act_mesh_anim = NULL;
				return false;
			}
			else
			{
				act_mesh_anim = act_animation->mMeshChannels[(uint)mesh_anim_id];
				return true;
			}
		}

		export const char* GetMeshAnimNodeName()
		{
			if (!act_mesh_anim) { return ""; }
			return (char*)act_mesh_anim->mName.C_Str();
		}

		export double GetMeshAnimKeysNum()
		{
			if (!act_mesh_anim) { return 0; }
			return act_mesh_anim->mNumKeys;
		}

		export double GetMeshAnimKeyTime(double key_id)
		{
			if (!act_mesh_anim) { return 0; }
			return act_mesh_anim->mKeys[(uint)key_id].mTime;
		}

		export double GetMeshAnimKeyValue(double key_id)
		{
			if (!act_mesh_anim) { return 0; }
			return act_mesh_anim->mKeys[(uint)key_id].mValue;
		}
	}
}
