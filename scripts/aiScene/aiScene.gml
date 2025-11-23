function aiScene() constructor {
	
	mName = "";
	//mFlags = 0;
	mRootNode = new aiNode();
	mMeshes = [];
	mMaterials = [];
	mAnimations = [];
	mTextures = [];
	mLights = [];
	mCameras = [];
	//mMetaData = {};
	
	
	/// @ignore
	static __read_bound = function() {
		mName = ASSIMP_GetSceneName();
		
		var _num_textures = ASSIMP_GetTexturesNum();
		for (var _i = 0; _i < _num_textures; _i++) {
			var _spr = -1;
			// Avoid to load data from file if it's raw (maybe in the future)
			if (ASSIMP_GetTextureHeight(0) == 0) {
				var _embed_texture = "data:image/png;base64," + ASSIMP_GetTextureDataBase64(0);
				_spr = sprite_add(_embed_texture, 1, false, false, 0, 0);
			}
			array_push(mTextures, _spr);
		}
		//ASSIMP_BindSceneNode();
		//mRootNode = new aiNode();
		//mRootNode.__read_bound();
		
		//var _num_meshes = ASSIMP_GetMeshNum();
		//for (var _i = 0; _i < _num_meshes; _i++) {
		//	var _mesh = new aiMesh();
		//	ASSIMP_BindMesh(_i);
		//	_mesh.__read_bound();
		//	array_push(mMeshes, _mesh);
		//}
		
		//var _num_materials = ASSIMP_GetMaterialNum();
		//for (var _i = 0; _i < _num_materials; _i++) {
		//	var _material = new aiMaterial();
		//	ASSIMP_BindMaterial(_i);
		//	_material.__read_bound();
		//	array_push(mMaterials, _material);
		//}
		
		//var _num_lights = ASSIMP_GetLightNum();
		//for (var _i = 0; _i < _num_lights; _i++) {
		//	var _light = new aiLight();
		//	ASSIMP_BindLight(_i);
		//	_light.__read_bound();
		//	array_push(mLights, _light);
		//}
		
		//var _num_cameras = ASSIMP_GetCameraNum();
		//for (var _i = 0; _i < _num_cameras; _i++) {
		//	var _camera = new aiCamera();
		//	ASSIMP_BindCamera(_i);
		//	_camera.__read_bound();
		//	array_push(mCameras, _camera);
		//}
	}
	
}