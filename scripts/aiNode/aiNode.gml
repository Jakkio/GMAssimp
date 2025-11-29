/**
 * A node in the imported hierarchy.
 * Each node has name, a parent node (except for the root node), a transformation relative to its parent
 * and possibly several child nodes. Simple file formats don't support hierarchical structures - for these formats
 * the imported scene does consist of only a single root node without children.
 */
function aiNode() constructor {
	/** The name of the node. The name might be empty (length of zero) but all nodes which need to be referenced by bones or animations are usually named. */
	mName = "";
	
	/** The transformation relative to the node's parent. */
	mTransformation = matrix_build_identity();
	
	/** The child nodes of this node. May be empty. */
	mChildren = [];
	
	/** The meshes of this node. Each entry is an index into the mesh list of the aiScene. May be empty. */
	mMeshes = [];
	//mMetaData = {};
	
	
	/// @ignore
	static __read_bound = function() {
		mName = ASSIMP_GetNodeName();
		
		mTransformation = [
			ASSIMP_GetMatrixA1(),
			ASSIMP_GetMatrixB1(),
			ASSIMP_GetMatrixC1(),
			ASSIMP_GetMatrixD1(),
			ASSIMP_GetMatrixA2(),
			ASSIMP_GetMatrixB2(),
			ASSIMP_GetMatrixC2(),
			ASSIMP_GetMatrixD2(),
			ASSIMP_GetMatrixA3(),
			ASSIMP_GetMatrixB3(),
			ASSIMP_GetMatrixC3(),
			ASSIMP_GetMatrixD3(),
			ASSIMP_GetMatrixA4(),
			ASSIMP_GetMatrixB4(),
			ASSIMP_GetMatrixC4(),
			ASSIMP_GetMatrixD4()
		];
		
		var _num_meshes = ASSIMP_GetNodeMeshNum();
		for (var _i = 0; _i <_num_meshes; _i++) {
			array_push(mMeshes, ASSIMP_GetNodeMeshIndex(_i));
		}
		
		var _num_nodes = ASSIMP_GetNodeMeshNum();
		for (var _i = 0; _i <_num_nodes; _i++) {
			var _node = new aiNode();
			ASSIMP_BindNodeChild(_i);
			_node.__read_bound();
			ASSIMP_BindNodeParent();
			
			array_push(mChildren, _node);
		}
		
	}
}
