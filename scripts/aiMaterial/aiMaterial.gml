/**
 * Data structure for a material.
 * Material data is dynamic, all variables are created on the fly.
 * So, before using them, you must check if they esists or not inside the structure.
 * mName is the only variable that will always exists.
 */
function aiMaterial() constructor {
	
	/** The name of the material. */
	mName = "";
	
	
	
	
	/// @ignore
	static __read_bound = function() {
		mName = ASSIMP_GetMaterialName();
		
		var _prop_num = ASSIMP_GetMaterialPropertyNum();
		
		for (var _i = 0; _i < _prop_num; _i++) {
			var _prop_name = ASSIMP_GetMaterialPropertyName(_i);
			switch (_prop_name) {
				case "$mat.twosided":
					twosided = ASSIMP_CheckMaterialTwoSided();	//Bool
					break;
				case "$mat.shadingm":
					shading_model = ASSIMP_GetMaterialShadingModel();	//enum aiShadingMode
					break;
				case "$mat.wireframe":
					enable_wireframe = ASSIMP_CheckMaterialEnableWireframe();	//Bool
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
			}
		}
	}
		
}