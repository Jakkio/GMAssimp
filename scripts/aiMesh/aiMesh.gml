/// Constants defined in the dll, it must be recompiled and update this script if you wanto to change them
#macro AI_MAX_BONE_WEIGHTS				0x7fffffff
#macro AI_MAX_FACE_INDICES				0x7fff
#macro AI_MAX_FACES						0x7fffffff
#macro AI_MAX_NUMBER_OF_COLOR_SETS		0x8
#macro AI_MAX_NUMBER_OF_TEXTURECOORDS	0x8
#macro AI_MAX_VERTICES					0x7fffffff


enum aiPrimitiveType
{
	POINT		= 0x1,
	LINE		= 0x2,
	TRIANGLE	= 0x4,
	POLYGON		= 0x8
}


/**
 * A mesh represents a geometry or model with a single material.
 * It usually consists of a number of vertices and a series of primitives/faces referencing the vertices.
 * In addition there might be a series of bones, each of them addressing a number of vertices with a certain weight.
 */
function aiMesh() constructor {
	
	/** The name of the mesh. Meshes can be named, but this is not a requirement. */
	mName = "";
	
	/** The material used by this mesh. A mesh uses only a single material. */
	mMaterialIndex = 0;
	
	/** The types of primitives contained in this mesh. This is a bitwise combination of aiPrimitiveType flags. */
	mPrimitiveTypes = 0;
	
	/** The number of vertices in this mesh. This is also the size of all of the per-vertex data arrays. */
	mNumVertices = 0;
	
	/** Vertex positions. This array is always present in a mesh. */
	mVertices = [];
	
	/** Vertex normals. The array contains normalized vectors, NULL if not present. */
	mNormals = [];
	
	/** Vertex tangents. The tangent of a vertex points in the direction of the positive X texture axis. */
	mTangents = [];
	
	/** Vertex bitangents. The bitangent of a vertex points in the direction of the positive Y texture axis. */
	mBitangents = [];
	
	/** Vertex color sets. A mesh may contain 0 to AI_MAX_NUMBER_OF_COLOR_SETS vertex colors per vertex. */
	mColors = [];
	
	/** Vertex texture coords, also known as UV channels. A mesh may contain 0 to AI_MAX_NUMBER_OF_TEXTURECOORDS per vertex. */
	mUVChannels = [];
	
	/** The faces the mesh is constructed from. Each face refers to a number of vertices by their indices. */
	mFaces = [];
	
	/** The bones of this mesh. A bone consists of a name by which it can be found in the frame hierarchy and a set of vertex weights. */
	mBones = [];
	
	/** The animation meshes attached to this mesh. */
	mAnimMeshes = [];
	/**
	 *  Method of morphing when anim-meshes are specified.
	 *  @see aiMorphingMethod to learn more about the provided morphing targets.
	 */
	mMethod = aiMorphingMethod.UNKNOWN;
	mAABB = new aiAABB();
	
	/**
	 * Returns the number of color channels in this mesh.
	 * @return {Real} The number of color channels
	 */
	static GetNumColorChannels = function() {
		return array_length(mColors);
	}
	
	/**
	 * Returns the number of UV channels in this mesh.
	 * @return {Real} The number of UV channels
	 */
	static GetNumUVChannels = function() {
		return array_length(mUVChannels);
	}
	
	/**
	 * Checks whether the mesh contains bones.
	 * @return {Bool} True if the mesh has bones, false otherwise
	 */
	static HasBones = function() {
		return array_length(mNumBones) > 0;
	}
	
	/**
	 * Checks whether the mesh contains faces.
	 * @return {Bool} True if the mesh has faces, false otherwise
	 */
	static HasFaces = function() {
		return array_length(mFaces) > 0;
	}
	
	/**
	 * Checks whether the mesh contains normals.
	 * @return {Bool} True if the mesh has normals, false otherwise
	 */
	static HasNormals = function() {
		return array_length(mmNormalsFaces) > 0;
	}
	
	/**
	 * Checks whether the mesh contains vertex positions.
	 * @return {Bool} True if the mesh has positions, false otherwise
	 */
	static HasPositions = function() {
		return array_length(mVertices) > 0;
	}
	
	/**
	 * Checks whether the mesh contains tangents and bitangents.
	 * @return {Bool} True if the mesh has tangents and bitangents, false otherwise
	 */
	static HasTangentsAndBitangents = function() {
		return array_length(mTangents) > 0;
	}
	
	
	
	/// @ignore
	static __read_bound = function() {
		ASSIMP_GetMeshFacesNum()
		
		mName = ASSIMP_GetMeshName();
		
		mPrimitiveTypes = ASSIMP_GetMeshPrimitiveTypes();
		
		mMaterialIndex = ASSIMP_GetMeshMaterialIndex();
		
		var _mNumFaces = ASSIMP_GetMeshFacesNum();
		mFaces = array_create(_mNumFaces, 0);	//Preallocation
		for (var _f = 0; _f < _mNumFaces; _f++) {
			var _face = new aiFace();
			_face.mNumIndices = ASSIMP_GetMeshFaceVerticesNum(_f);
			for (var _i = 0; _i < _face.mNumIndices; _i++) {
				array_push(_face.mIndices, ASSIMP_GetMeshFaceVertexIndex(_f, _i))
			}
			mFaces[_f]= _face;
		}
		
		mNumVertices = ASSIMP_GetMeshVerticesNum();
		mVertices = array_create(mNumVertices, 0);	//Preallocation
		for (var _i = 0; _i < mNumVertices; _i++) {
			var _v = new aiVector3D();
			_v.x = ASSIMP_GetMeshVertexX(_i);
			_v.y = ASSIMP_GetMeshVertexY(_i);
			_v.z = ASSIMP_GetMeshVertexZ(_i);
			mVertices[_i] = _v;
		}
		
		// Normals
		if (ASSIMP_MeshHasNormals()) {
			mNormals = array_create(mNumVertices, 0);	//Preallocation
			for (var _i = 0; _i < mNumVertices; _i++) {
				var _v = new aiVector3D();
				_v.x = ASSIMP_GetMeshNormalX(_i);
				_v.y = ASSIMP_GetMeshNormalY(_i);
				_v.z = ASSIMP_GetMeshNormalZ(_i);
				mNormals[_i] = _v;
			}
		}
		
		// Tangents
		if (ASSIMP_MeshHasTangents()) {
			mTangents = array_create(mNumVertices, 0);	//Preallocation
			for (var _i = 0; _i < mNumVertices; _i++) {
				var _v = new aiVector3D();
				_v.x = ASSIMP_GetMeshTangentX(_i);
				_v.y = ASSIMP_GetMeshTangentY(_i);
				_v.z = ASSIMP_GetMeshTangentZ(_i);
				mTangents[_i] = _v;
			}
			mBitangents = array_create(mNumVertices, 0);	//Preallocation
			for (var _i = 0; _i < mNumVertices; _i++) {
				var _v = new aiVector3D();
				_v.x = ASSIMP_GetMeshBitangentX(_i);
				_v.y = ASSIMP_GetMeshBitangentY(_i);
				_v.z = ASSIMP_GetMeshBitangentZ(_i);
				mBitangents[_i] = _v;
			}
		}
		
		var _mNumBones = ASSIMP_GetMeshBonesNum();
			for (var _i = 0; _i < _mNumBones; _i++) {
				ASSIMP_BindMeshBone(_i);
				
				var _bone = new aiBone();
				_bone.mName = ASSIMP_GetBoneName();
				ASSIMP_BindBoneOffsetMatrix();
				_bone.mOffsetMatrix = [
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
				var _mNumWeights = ASSIMP_GetBoneNumWeights();
				_bone.mWeights = array_create(_mNumWeights, 0);
				for (var _w = 0; _w < _mNumWeights; _w++) {
					mWeights[_w] = new aiVertexWeight(
						ASSIMP_GetBoneVertexIndex(_w),
						ASSIMP_GetBoneVertexWeight(_w)
					);
				}
				
				array_push(mBones, _bone);
			}
		
		var _mNumColorChannels = ASSIMP_GetMeshColorChannelsNum();
			for (var _ch = 0; _ch < _mNumColorChannels; _ch++) {
				var _color_ch = array_create(_mNumColorChannels, 0);	//Preallocation
				for (var _i = 0; _i < mNumVertices; _i++) {
					_color_ch[_i] = new aiColor4D(
						ASSIMP_GetMeshVertexColorR(_i, _ch),
						ASSIMP_GetMeshVertexColorG(_i, _ch),
						ASSIMP_GetMeshVertexColorB(_i, _ch),
						ASSIMP_GetMeshVertexAlpha(_i, _ch)
					);
				
				}
				array_push(mColors, _color_ch);
			}
		
		var _numUVChannels = ASSIMP_GetMeshUVChannelsNum();
			for (var _ch = 0; _ch < _numUVChannels; _ch++) {
				var _uv_ch = new aiUVChannel();
				_uv_ch.mName = ASSIMP_GetMeshTextureCoordsName(_ch);
				_uv_ch.mNumComponents = ASSIMP_GetMeshNumUVComponents(_ch);
				var _tex_coords = array_create(_numUVChannels, 0);	//Preallocation
				for (var _i = 0; _i < mNumVertices; _i++) {
					_tex_coords[_i] = new aiVector3D(
						ASSIMP_GetMeshTexCoordU(_i, _ch),
						ASSIMP_GetMeshTexCoordV(_i, _ch),
						ASSIMP_GetMeshTexCoordW(_i, _ch)
					);
				}
				_uv_ch.mTextureCoords = _tex_coords;
				array_push(mUVChannels, _uv_ch);
			}
			
		var _mNumAnimMeshes = ASSIMP_GetMeshAnimMeshNum();
			for (var _i = 0; _i < _mNumAnimMeshes; _i++) {
				var _anim_mesh = new aiAnimMesh();
				_anim_mesh.mName = ASSIMP_GetMeshAnimMeshName(_i);
				
				if (ASSIMP_GetMeshAnimMeshHasPositions(_i)) {
					for (var _j = 0; _j < mNumVertices; _j++) {
						var _v = new aiVector3D();
						_v.x = ASSIMP_GetMeshAnimMeshVertexX(_i, _j);
						_v.y = ASSIMP_GetMeshAnimMeshVertexY(_i, _j);
						_v.z = ASSIMP_GetMeshAnimMeshVertexZ(_i, _j);
						array_push(_anim_mesh.mVertices, _v);
					}
				}
				
				if (ASSIMP_GetMeshAnimMeshHasNormals(_i)) {
					for (var _j = 0; _j < mNumVertices; _j++) {
						var _v = new aiVector3D();
						_v.x = ASSIMP_GetMeshAnimMeshNormalX(_i, _j);
						_v.y = ASSIMP_GetMeshAnimMeshNormalY(_i, _j);
						_v.z = ASSIMP_GetMeshAnimMeshNormalZ(_i, _j);
						array_push(_anim_mesh.mNormals, _v);
					}
				}
				
				if (ASSIMP_GetMeshAnimMeshHasTangents(_i)) {
					for (var _j = 0; _j < mNumVertices; _j++) {
						var _v = new aiVector3D();
						_v.x = ASSIMP_GetMeshAnimMeshTangentX(_i, _j);
						_v.y = ASSIMP_GetMeshAnimMeshTangentY(_i, _j);
						_v.z = ASSIMP_GetMeshAnimMeshTangentZ(_i, _j);
						array_push(_anim_mesh.mTangents, _v);
					}
				}
				
				if (ASSIMP_GetMeshAnimMeshHasBitangents(_i)) {
					for (var _j = 0; _j < mNumVertices; _j++) {
						var _v = new aiVector3D();
						_v.x = ASSIMP_GetMeshAnimMeshBitangentX(_i, _j);
						_v.y = ASSIMP_GetMeshAnimMeshBitangentY(_i, _j);
						_v.z = ASSIMP_GetMeshAnimMeshBitangentZ(_i, _j);
						array_push(_anim_mesh.mBitangents, _v);
					}
				}
		
				_mNumColorChannels = ASSIMP_GetMeshColorChannelsNum();
					for (var _ch = 0; _ch < _mNumColorChannels; _ch++) {
						if (ASSIMP_GetMeshAnimMeshHasColors(_i, _ch)) {
							var _color_ch = array_create(_mNumColorChannels, 0);	//Preallocation
							for (var _j = 0; _j < mNumVertices; _j++) {
								_color_ch[_i] = new aiColor4D(
									ASSIMP_GetMeshAnimMeshVertexColorR(_i, _ch, _j),
									ASSIMP_GetMeshAnimMeshVertexColorG(_i, _ch, _j),
									ASSIMP_GetMeshAnimMeshVertexColorB(_i, _ch, _j),
									ASSIMP_GetMeshAnimMeshVertexColorA(_i, _ch, _j)
								);
				
							}
							array_push(_anim_mesh.mColors, _color_ch);
						}
					}
		
				_numUVChannels = ASSIMP_GetMeshUVChannelsNum();
					for (var _ch = 0; _ch < _numUVChannels; _ch++) {
						if (ASSIMP_GetMeshAnimMeshHasTexCoords(_i, _ch)) {
							var _uv_ch = new aiUVChannel();
							_uv_ch.mName = ASSIMP_GetMeshTextureCoordsName(_ch);
							_uv_ch.mNumComponents = ASSIMP_GetMeshNumUVComponents(_ch);
							var _tex_coords = array_create(_numUVChannels, 0);	//Preallocation
							for (var _j = 0; _j < mNumVertices; _j++) {
								_tex_coords[_i] = new aiVector3D(
									ASSIMP_GetMeshAnimMeshTexCoordU(_i, _ch, _j),
									ASSIMP_GetMeshAnimMeshTexCoordV(_i, _ch, _j),
									ASSIMP_GetMeshAnimMeshTexCoordW(_i, _ch, _j)
								);
							}
							_uv_ch.mTextureCoords = _tex_coords;
							array_push(_anim_mesh.mUVChannels, _uv_ch);
						}
					}
				
				array_push(mAnimMeshes, _anim_mesh);
			}
		
		mMethod = ASSIMP_GetMeshMorphMethod();
		
		mAABB.mMin.x = ASSIMP_GetMeshAABBMinX();
		mAABB.mMin.y = ASSIMP_GetMeshAABBMinY();
		mAABB.mMin.z = ASSIMP_GetMeshAABBMinZ();
		mAABB.mMax.x = ASSIMP_GetMeshAABBMaxX();
		mAABB.mMax.y = ASSIMP_GetMeshAABBMaxY();
		mAABB.mMax.z = ASSIMP_GetMeshAABBMaxZ();
	}
}
