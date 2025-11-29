function aiMeshAnim() constructor {
	mName = "";
	mKeys = [];
	
	
	/// @ignore
	static __read_bound = function() {
		mName = ASSIMP_GetMeshAnimNodeName();
		
		var _mNumKeys = ASSIMP_GetMeshAnimKeysNum();
		for (var _i = 0; _i < _mNumKeys; _i++) {
			var _key = new aiMeshKey();
			_key.mTime = ASSIMP_GetMeshAnimKeyTime(_i);
			_key.mValue = ASSIMP_GetMeshAnimKeyValue(_i);
			array_push(mKeys, _key);
		}
		
	}
}