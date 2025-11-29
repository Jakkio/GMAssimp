/**
 * A time-value pair specifying a certain mesh index for a given time.
 * Used in mesh animation to define keyframes.
 */
function aiMeshKey() constructor {
	/** The time of this key */
	mTime = 0;
	
	/** Index into the aiMesh::mAnimMeshes array of the mesh corresponding to the aiMeshAnim hosting this key frame. */
	mValue = 0;
}
