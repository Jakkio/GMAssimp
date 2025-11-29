// @author		Giacomo Marton
// @version		1.0.0


/**
 * A single bone of a mesh.
 * A bone has a name by which it can be found in the frame hierarchy and by which it can be addressed by animations. In addition it has a number of influences on vertices.
 */
function aiBone() constructor {
	// The name of the bone
	mName = "";
	
	// Matrix that transforms from mesh space to bone space in bind pose
	mOffsetMatrix = matrix_build_identity();
	
	// The vertices affected by this bone
	mWeights = [];
}