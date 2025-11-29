/**
 * An animation consists of keyframe data for a number of nodes.
 * For each node affected by the animation a separate series of data is given.
 */
function aiAnimation() constructor {
	/** The name of the animation. If the modeling package this data was exported from does support only a single animation channel, this name is usually empty. */
	mName = "";
	
	/** Duration of the animation in ticks. */
	mDuration = -1;
	
	/** Ticks per second. 0 if not specified in the imported file */
	mTicksPerSecond = 0;
	
	/** The node animation channels. Each channel affects a single node. The array is mNumChannels in size. */
	mChannels = [];
	
	/** The mesh animation channels. Each channel affects a single mesh and defines vertex-based animation. The array is mNumMeshChannels in size. */
	mMeshChannels = [];
	
	/** The morph mesh animation channels. Each channel affects a single mesh. The array is mNumMorphMeshChannels in size. */
	mMorphMeshChannels = [];
	
	
	/// @ignore
	static __read_bound = function() {
		mName = ASSIMP_GetAnimationName();
		mDuration = ASSIMP_GetAnimationDuration();
		mTicksPerSecond = ASSIMP_GetAnimationTicksPerSecond();
		
		var _num_node_channels = ASSIMP_GetAnimationNodeChannelsNum();
		for (var _i = 0; _i < _num_node_channels; _i++) {
			ASSIMP_BindNodeAnimation(_i);
			var _node = new aiNodeAnim();
			_node.__read_bound();
			array_push(mChannels, _node);
		}
		
		var _num_mesh_channels = ASSIMP_GetAnimationMeshChannelsNum();
		for (var _i = 0; _i < _num_mesh_channels; _i++) {
			ASSIMP_BindMeshAnimation(_i);
			var _manim = new aiMeshAnim();
			_manim.__read_bound();
			array_push(mMeshChannels, _manim);
		}
		
		var _num_morph_channels = ASSIMP_GetAnimationMorphMeshChannelsNum();
		for (var _i = 0; _i < _num_morph_channels; _i++) {
			ASSIMP_BindMorphMeshAnimation(_i);
			var _morph = new aiMeshMorphAnim();
			_morph.__read_bound();
			array_push(mMorphMeshChannels, _morph);
		}
		
	}
}
