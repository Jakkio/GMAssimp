/**
 * Data structure for a material.
 * Material data is stored using a key-value structure. A single key-value pair is called a 'material property'.
 * C++ users should use the provided member functions of aiMaterial to process material properties.
 */
function aiMaterial() constructor {
	
	/** The name of the material. */
	mName = "";
	
	// Material properties - 
	// @todo currently not fully implemented
	mMaterialIndex = 0;
	mPrimitiveTypes = 0;
	mNumVertices = 0;
	mVertices = [];
	mNormals = [];
	mTangents = [];
	mBitangents = [];
	mColors = [];
	mUVChannels = [];
	mFaces = [];
	mBones = [];
	mAnimMeshes = [];
	
	/**
	 * Returns the number of color channels in this material.
	 * @return {Real} The number of color channels
	 */
	static GetNumColorChannels = function() {
		return array_length(mColors);
	}
	
	
	
	/// @ignore
	static __read_bound = function() {
		
	}
}
