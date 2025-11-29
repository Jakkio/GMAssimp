/**
 * Describes the animation of a single node.
 * The name specifies the bone/node which is affected by this animation channel.
 * The keyframes are given in three separate series of values, one each for position, rotation and scaling.
 */
function aiNodeAnim() constructor {
	/** The name of the node affected by this animation. The node must exist and it must be unique. */
	mNodeName = "";
	
	/** The behavior of the animation before the first key is encountered. */
	mPreState = aiAnimBehaviour.DEFAULT;
	
	/** The behavior of the animation after the last key was processed. */
	mPostState = aiAnimBehaviour.DEFAULT;
	
	/** The position keys of this animation channel. Positions are specified as 3D vector. */
	mPositionKeys = [];
	
	/** The rotation keys of this animation channel. Rotations are given as quaternions. */
	mRotationKeys = [];
	
	/** The scaling keys of this animation channel. Scalings are specified as 3D vector. */
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
