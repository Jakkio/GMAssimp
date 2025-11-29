/**
 * Describes vertex-based animations for a single mesh.
 * Meshes carry the animation data for each frame. The purpose of aiMeshAnim is to define keyframes
 * linking each mesh attachment to a particular point in time.
 */
function aiMeshAnim() constructor {
	/** Name of the mesh to be animated. An empty string is not allowed, animated meshes need to be named. */
	mName = "";
	
	/** Array of aiMeshKey structures. Size of the array is given by the number of keys. */
	mKeys = [];
	
	
	/// @ignore
	static __read_bound = function() {
		mName = ASSIMP_GetMeshAnimName();
		
		var _mNumKeys = ASSIMP_GetMeshAnimKeysNum();
		for (var _i = 0; _i < _mNumKeys; _i++) {
			var _key = new aiMeshKey();
			_key.mTime = ASSIMP_GetMeshAnimKeyTime(_i);
			_key.mValue = ASSIMP_GetMeshAnimKeyValue(_i);
			array_push(mKeys, _key);
		}
		
	}
}
