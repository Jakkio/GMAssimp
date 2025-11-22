// @author		Giacomo Marton
// @version		1.0.0


/** An AnimMesh is an attachment to an #aiMesh stores per-vertex
 *  animations for a particular frame.
 *
 *  You may think of an #aiAnimMesh as a `patch` for the host mesh, which
 *  replaces only certain vertex data streams at a particular time.
 *  Each mesh stores n attached attached meshes (#aiMesh::mAnimMeshes).
 *  The actual relationship between the time line and anim meshes is
 *  established by #aiMeshAnim, which references singular mesh attachments
 *  by their ID and binds them to a time offset.
*/
function aiAnimMesh() constructor {
	
	mName = "";
	
	/**
	 * Weight of the AnimMesh.
	 */
	mWeight = 0;
	
	mVertices = [];
	mNormals = [];
	mTangents = [];
	mBitangents = [];
	mColors = [];
	mTextureCoords = [];
	
	
}