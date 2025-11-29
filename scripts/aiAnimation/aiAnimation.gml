function aiAnimation() constructor {
	mName = "";
	mDuration = -1;
	mTicksPerSecond = 0;
	mChannels = [];
	mMeshChannels = [];
	mMorphMeshChannels = [];
	
	
	/// @ignore
	static __read_bound = function() {
		mName = ASSIMP_GetAnimationName();
		mDuration = ASSIMP_GetAnimationDuration();
		mTicksPerSecond = ASSIMP_GetAnimationTicksPerSecond();
		
		var _num_channels = ASSIMP_GetAnimationNodeChannelsNum();
		for (var _i = 0; _i < _num_channels; _i++) {
			ASSIMP_BindNodeAnimation(_i);
			var _node = new aiNodeAnim();
			_node.__read_bound();
			array_push(mChannels, _node);
		}
		
		var _num_channels = ASSIMP_GetAnimationMeshChannelsNum();
		for (var _i = 0; _i < _num_channels; _i++) {
			ASSIMP_BindMeshAnimation(_i);
			var _manim = new aiMeshAnim();
			_manim.__read_bound();
			array_push(mMeshChannels, _manim);
		}
		
		//var _num_channels = ASSIMP_GetAnimationMorphMeshChannelsNum();
		//for (var _i = 0; _i < _num_channels; _i++) {
		//	ASSIMP_BindMorphMeshAnimation(_i);
		//	var _morph = new aiMorphMeshAnim();
		//	_morph.__read_bound();
		//	array_push(mMorphMeshChannels, _morph);
		//}
		
	}
}