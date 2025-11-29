function aiNodeAnim() constructor {
	mNodeName = "";
	mPreState = aiAnimBehaviour.DEFAULT;
	mPostState = aiAnimBehaviour.DEFAULT;
	mPositionKeys = [];
	mRotationKeys = [];
	mScalingKeys = [];
	
	
	/// @ignore
	static __read_bound = function() {
		mNodeName = ASSIMP_GetNodeAnimNodeName();
		mPreState = ASSIMP_GetNodeAnimPreState();
		mPostState = ASSIMP_GetNodeAnimPostState();
		
		var _mNumPositionKeys = ASSIMP_GetNodeAnimPositionKeysNum();
		for (var _i = 0; _i < _mNumPositionKeys; _i++) {
			var _key = new aiVectorKey();
			_key.mTime = ASSIMP_GetNodeAnimPositionKeyTime(_i);
			_key.mValue = new aiVector3D(	ASSIMP_GetNodeAnimPositionKeyValueX(_i),
											ASSIMP_GetNodeAnimPositionKeyValueY(_i),
											ASSIMP_GetNodeAnimPositionKeyValueZ(_i) );
			_key.mInterpolation = ASSIMP_GetNodeAnimPositionKeyInterpolation(_i);
			array_push(mPositionKeys, _key);
		}
		
		var _mNumRotationKeys = ASSIMP_GetNodeAnimRotationKeysNum();
		for (var _i = 0; _i < _mNumRotationKeys; _i++) {
			var _key = new aiQuatKey();
			_key.mTime = ASSIMP_GetNodeAnimRotationKeyTime(_i);
			_key.mValue = new aiQuaternion(	ASSIMP_GetNodeAnimRotationKeyQuaternionX(_i),
											ASSIMP_GetNodeAnimRotationKeyQuaternionY(_i),
											ASSIMP_GetNodeAnimRotationKeyQuaternionZ(_i),
											ASSIMP_GetNodeAnimRotationKeyQuaternionW(_i) );
			_key.mInterpolation = ASSIMP_GetNodeAnimRotationKeyInterpolation(_i);
			array_push(mRotationKeys, _key);
		}
		
		var _mNumScalingKeys = ASSIMP_GetNodeAnimScalingKeysNum();
		for (var _i = 0; _i < _mNumScalingKeys; _i++) {
			var _key = new aiVectorKey();
			_key.mTime = ASSIMP_GetNodeAnimScalingKeyTime(_i);
			_key.mValue = new aiVector3D(	ASSIMP_GetNodeAnimScalingKeyValueX(_i),
											ASSIMP_GetNodeAnimScalingKeyValueY(_i),
											ASSIMP_GetNodeAnimScalingKeyValueZ(_i) );
			_key.mInterpolation = ASSIMP_GetNodeAnimScalingKeyInterpolation(_i);
			array_push(mScalingKeys, _key);
		}
		
	}
}