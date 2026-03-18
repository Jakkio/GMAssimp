/**
 * Data structure for a material.
 * Each material can have as many properties they want,
 * that means that all variables can be undefined and you always need to check them before use.
 * Texture list are arrays that can be empty but never undefined, and they contain aiTextureProperty structs.
 * Each struct inside this arrays follow the same rule as material: all values can be undefined.
 */
function aiMaterial() constructor {
		
	/// @ignore
	static __read_bound = function() {
		
		//Textures arrays preparation;
		
		///Fake function just to force feather recognize the right type
		///@returns {Array<Struct.aiTextureProperty>}
		var _feather_force = function() {return []}
		texture_none =						_feather_force();
		texture_diffuse =					_feather_force();
		texture_specular =					_feather_force();
		texture_ambient =					_feather_force();
		texture_emissive =					_feather_force();
		texture_height =					_feather_force();
		texture_normals =					_feather_force();
		texture_shininess =					_feather_force();
		texture_opacity =					_feather_force();
		texture_displacement =				_feather_force();
		texture_lightmap =					_feather_force();
		texture_reflection =				_feather_force();
		texture_base_color =				_feather_force();
		texture_normal_camera =				_feather_force();
		texture_emission_color =			_feather_force();
		texture_metalness =					_feather_force();
		texture_diffuse_roughness =			_feather_force();
		texture_ambient_occlusion =			_feather_force();
		texture_unknown =					_feather_force();
		texture_sheen =						_feather_force();
		texture_clearcoat =					_feather_force();
		texture_transmission =				_feather_force();
		texture_maya_base =					_feather_force();
		texture_maya_specular =				_feather_force();
		texture_maya_specular_color =		_feather_force();
		texture_maya_specular_roughness =	_feather_force();
		texture_anisotropy =				_feather_force();
		texture_gltf_metallic_roughness =	_feather_force();
		
		/// @ignore
		var _get_texture_property = function(_tex_type, _i) {
			var _tex_array = [];
			
			switch (_tex_type) {
				case aiTextureType.NONE:					_tex_array = texture_none					; break;
				case aiTextureType.DIFFUSE:					_tex_array = texture_diffuse				; break;
				case aiTextureType.SPECULAR:				_tex_array = texture_specular				; break;
				case aiTextureType.AMBIENT:					_tex_array = texture_ambient				; break;
				case aiTextureType.EMISSIVE:				_tex_array = texture_emissive				; break;
				case aiTextureType.HEIGHT:					_tex_array = texture_height					; break;
				case aiTextureType.NORMALS:					_tex_array = texture_normals				; break;
				case aiTextureType.SHININESS:				_tex_array = texture_shininess				; break;
				case aiTextureType.OPACITY:					_tex_array = texture_opacity				; break;
				case aiTextureType.DISPLACEMENT:			_tex_array = texture_displacement			; break;
				case aiTextureType.LIGHTMAP:				_tex_array = texture_lightmap				; break;
				case aiTextureType.REFLECTION:				_tex_array = texture_reflection				; break;
				case aiTextureType.BASE_COLOR:				_tex_array = texture_base_color				; break;
				case aiTextureType.NORMAL_CAMERA:			_tex_array = texture_normal_camera			; break;
				case aiTextureType.EMISSION_COLOR:			_tex_array = texture_emission_color			; break;
				case aiTextureType.METALNESS:				_tex_array = texture_metalness				; break;
				case aiTextureType.DIFFUSE_ROUGHNESS:		_tex_array = texture_diffuse_roughness		; break;
				case aiTextureType.AMBIENT_OCCLUSION:		_tex_array = texture_ambient_occlusion		; break;
				case aiTextureType.UNKNOWN:					_tex_array = texture_unknown				; break;
				case aiTextureType.SHEEN:					_tex_array = texture_sheen					; break;
				case aiTextureType.CLEARCOAT:				_tex_array = texture_clearcoat				; break;
				case aiTextureType.TRANSMISSION:			_tex_array = texture_transmission			; break;
				case aiTextureType.MAYA_BASE:				_tex_array = texture_maya_base				; break;
				case aiTextureType.MAYA_SPECULAR:			_tex_array = texture_maya_specular			; break;
				case aiTextureType.MAYA_SPECULAR_COLOR:		_tex_array = texture_maya_specular_color	; break;
				case aiTextureType.MAYA_SPECULAR_ROUGHNESS:	_tex_array = texture_maya_specular_roughness; break;
				case aiTextureType.ANISOTROPY:				_tex_array = texture_anisotropy				; break;
				case aiTextureType.GLTF_METALLIC_ROUGHNESS:	_tex_array = texture_gltf_metallic_roughness; break;
			}
			
			// Fill array with new needed texture properties
			var _len = array_length(_tex_array);
			for (var _t = _len; _t <= _i; _t++) {
				_tex_array[_t] = new aiTextureProperty();
			}
			//Returns texure property
			return _tex_array[_i];
		}
		
		#endregion
		
		
		name = undefined;
		twosided = undefined;
		shading_model = undefined;
		enable_wireframe = undefined;
		blend_func = undefined;
		opacity = undefined;
		transparency_factor = undefined;
		bump_scaling = undefined;
		shininess = undefined;
		reflectivity = undefined;
		shininess_strength = undefined;
		refracti = undefined;
		color_diffuse = undefined;
		color_ambient = undefined;
		color_specular = undefined;
		color_emissive = undefined;
		color_transparent = undefined;
		color_reflective = undefined;
		global_background_image = undefined;
		global_shader_language = undefined;
		shader_vertex = undefined;
		shader_fragment = undefined;
		shader_geo = undefined;
		shader_tessellation = undefined;
		shader_primitive = undefined;
		shader_compute = undefined;
		use_color_map = undefined;
		base_color = undefined;
		
		
		
		var _prop_num = ASSIMP_GetMaterialPropertyNum();
		for (var _i = 0; _i < _prop_num; _i++) {
			
			var _prop_name = ASSIMP_GetMaterialPropertyName(_i);
			var _prop_tex_type = ASSIMP_GetMaterialPropertyTextureType(_i);
			var _prop_tex_index = ASSIMP_GetMaterialPropertyTextureIndex(_i);
			var _texture_property;
			
			switch (_prop_name) {
				case "$mat.name":
					name = ASSIMP_GetMaterialName();	//String
					break;
				case "$mat.twosided":
					twosided = ASSIMP_CheckMaterialTwoSided() == true;	//Bool
					break;
				case "$mat.shadingm":
					shading_model = ASSIMP_GetMaterialShadingModel();	//enum aiShadingMode
					break;
				case "$mat.wireframe":
					enable_wireframe = ASSIMP_CheckMaterialEnableWireframe() == true;	//Bool
					break;
				case "$mat.blend":
					blend_func = ASSIMP_GetMaterialBlendFunc();	//enum aiBlendMode
					break;
				case "$mat.opacity":
					opacity = ASSIMP_GetMaterialOpacity();
					break;
				case "$mat.transparencyfactor":
					transparency_factor = ASSIMP_GetMaterialTransparencyFactor();
					break;
				case "$mat.bumpscaling":
					bump_scaling = ASSIMP_GetMaterialBumpScaling();
					break;
				case "$mat.shininess":
					shininess = ASSIMP_GetMaterialShininess();
					break;
				case "$mat.reflectivity":
					reflectivity = ASSIMP_GetMaterialReflectivity();
					break;
				case "$mat.shinpercent":
					shininess_strength = ASSIMP_GetMaterialShininessStrength();
					break;
				case "$mat.refracti":
					refracti = ASSIMP_GetMaterialRefracti();
					break;
				case "$clr.diffuse":
					color_diffuse = new aiColor3D(	ASSIMP_GetMaterialDiffuseColorR(),
													ASSIMP_GetMaterialDiffuseColorG(),
													ASSIMP_GetMaterialDiffuseColorB() );
					break;
				case "$clr.ambient":
					color_ambient = new aiColor3D(	ASSIMP_GetMaterialAmbientColorR(),
													ASSIMP_GetMaterialAmbientColorG(),
													ASSIMP_GetMaterialAmbientColorB() );
					break;
				case "$clr.specular":
					color_specular = new aiColor3D(	ASSIMP_GetMaterialSpecularColorR(),
													ASSIMP_GetMaterialSpecularColorG(),
													ASSIMP_GetMaterialSpecularColorB() );
					break;
				case "$clr.emissive":
					color_emissive = new aiColor3D(	ASSIMP_GetMaterialEmissiveColorR(),
													ASSIMP_GetMaterialEmissiveColorG(),
													ASSIMP_GetMaterialEmissiveColorB() );
					break;
				case "$clr.transparent":
					color_transparent = new aiColor3D(	ASSIMP_GetMaterialTransparentColorR(),
														ASSIMP_GetMaterialTransparentColorG(),
														ASSIMP_GetMaterialTransparentColorB() );
					break;
				case "$clr.reflective":
					color_reflective = new aiColor3D(	ASSIMP_GetMaterialReflectiveColorR(),
														ASSIMP_GetMaterialReflectiveColorG(),
														ASSIMP_GetMaterialReflectiveColorB() );
					break;
				case "?bg.global":
					global_background_image = ASSIMP_GetMaterialGlobalBackgroundImage();
					break;
				case "?sh.lang":
					global_shader_language = ASSIMP_GetMaterialGlobalShaderLanguage();
					break;
				case "?sh.vs":
					shader_vertex = ASSIMP_GetMaterialShaderVertex();
					break;
				case "?sh.fs":
					shader_fragment = ASSIMP_GetMaterialShaderFragment();
					break;
				case "?sh.gs":
					shader_geo = ASSIMP_GetMaterialShaderGeo();
					break;
				case "?sh.ts":
					shader_tessellation = ASSIMP_GetMaterialShaderTessellation();
					break;
				case "?sh.ps":
					shader_primitive = ASSIMP_GetMaterialShaderPrimitive();
					break;
				case "?sh.cs":
					shader_compute = ASSIMP_GetMaterialShaderCompute();
					break;
				
				//// PBR material support
				//case "$mat.useColorMap":
				//	use_color_map = ASSIMP_GetMaterialUseColorMap();
				//	break;
				
				//// Metallic/Roughness Workflow
				//case "$clr.base":
				//	base_color = ASSIMP_GetMaterialBaseColor();
				//	break;
				#region Texture properties
				
				case "$tex.file":
					_texture_property = _get_texture_property(_prop_tex_type, _prop_tex_index);
					_texture_property.path = ASSIMP_GetMaterialTextureName(_prop_tex_type, _prop_tex_index);
					//String that starts with * and a number after, its considered as index in importer array
					if (string_starts_with(_texture_property.path, "*")) {
						_texture_property.path = real(string_copy(_texture_property.path, 2, 9999999));
					}
					break;
				case "$tex.uvwsrc":
					_texture_property = _get_texture_property(_prop_tex_type, _prop_tex_index);
					_texture_property.uvw_source = ASSIMP_GetMaterialUVWSource(_prop_tex_type, _prop_tex_index);
					break;
				case "$tex.op":	//enum aiTextureOp
					_texture_property = _get_texture_property(_prop_tex_type, _prop_tex_index);
					_texture_property.operation = ASSIMP_GetMaterialTextureOperation(_prop_tex_type, _prop_tex_index);
					break;
				case "$tex.mapping":	//enum aiTextureMapping
					_texture_property = _get_texture_property(_prop_tex_type, _prop_tex_index);
					_texture_property.mapping = ASSIMP_GetMaterialMapping(_prop_tex_type, _prop_tex_index);
					break;
				case "$tex.blend":
					_texture_property = _get_texture_property(_prop_tex_type, _prop_tex_index);
					_texture_property.blend = ASSIMP_GetMaterialTextureBlend(_prop_tex_type, _prop_tex_index);
					break;
				case "$tex.mapmodeu":	//enum aiTextureMapMode
					_texture_property = _get_texture_property(_prop_tex_type, _prop_tex_index);
					_texture_property.mapping_mode_u = ASSIMP_GetMaterialMappingModeU(_prop_tex_type, _i);
					break;
				case "$tex.mapmodev":	//enum aiTextureMapMode
					_texture_property = _get_texture_property(_prop_tex_type, _prop_tex_index);
					_texture_property.mapping_mode_v = ASSIMP_GetMaterialMappingModeV(_prop_tex_type, _i);
					break;
				case "$tex.mapaxis":
					_texture_property = _get_texture_property(_prop_tex_type, _prop_tex_index);
					_texture_property = _get_texture_property(_prop_tex_type, _prop_tex_index);
					_texture_property.mapping_axis = new aiVector3D(ASSIMP_GetMaterialTextureMapAxisX(_prop_tex_type, _i),
																	ASSIMP_GetMaterialTextureMapAxisY(_prop_tex_type, _i),
																	ASSIMP_GetMaterialTextureMapAxisZ(_prop_tex_type, _i) );
					break;
				case "$tex.uvtrafo":
					_texture_property = _get_texture_property(_prop_tex_type, _prop_tex_index);
					var _transform = new aiUVTransform();
					_transform.mTranslation = new aiVector2D(	ASSIMP_GetMaterialTextureUVTransformTranslationX(_prop_tex_type, _prop_tex_index),
																ASSIMP_GetMaterialTextureUVTransformTranslationY(_prop_tex_type, _prop_tex_index) );
					_transform.mScaling = new aiVector2D(	ASSIMP_GetMaterialTextureUVTransformScalingX(_prop_tex_type, _prop_tex_index),
															ASSIMP_GetMaterialTextureUVTransformScalingY(_prop_tex_type, _prop_tex_index) );
					_transform.mRotation = ASSIMP_GetMaterialTextureUVTransformRotation(_prop_tex_type, _prop_tex_index);
					_texture_property.uv_transform = _transform;
					break;
				case "$tex.flags":	//enum aiTextureFlags
					_texture_property = _get_texture_property(_prop_tex_type, _prop_tex_index);
					_texture_property.flags = ASSIMP_GetMaterialTextureFlags(_prop_tex_type, _prop_tex_index);
					break;
				
				#endregion
			}
		}
		
		
		show_debug_message(json_stringify(self, true))
		show_message(self)
		
	}
		
}