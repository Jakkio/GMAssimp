/**
 * Describes vertex-based animations for a single mesh or a group of meshes.
 * Meshes carry the animation data for each frame in their aiAnimMesh structures.
 * The purpose of aiMeshMorphAnim is to define keyframes linking each mesh attachment to a particular point in time.
 */
function aiMeshMorphAnim() constructor {
	/** Name of the mesh to be animated. An empty string is not allowed, animated meshes need to be named. */
	mName = "";
	
	/** Array of aiMeshKey structures. The array is mNumKeys in size. */
	mKeys = [];
	
	
	/// @ignore
	static __read_bound = function() {
		mName = ASSIMP_GetMorphMeshAnimName();
		
		var _mNumKeys = ASSIMP_GetMeshAnimKeysNum();
		for (var _i = 0; _i < _mNumKeys; _i++) {
			var _key = new aiMeshKey();
			_key.mTime = ASSIMP_GetMeshAnimKeyTime(_i);
			var _num_values = ASSIMP_GetMorphMeshAnimKeyNumValuesAndWeights(_i);
			for (var _j = 0; _j < _num_values; _j++) {
				var _value = {
					value: ASSIMP_GetMorphMeshAnimKeyValue(_i, _j),
					weight: ASSIMP_GetMorphMeshAnimKeyWeight(_i, _j)
				}
				array_push(_key.mValues, _value)
			}
			array_push(mKeys, _key);
		}
		
	}
}
