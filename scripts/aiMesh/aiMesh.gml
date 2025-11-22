/// Constants defined in the dll, it must be recompiled and update this script if you wanto to change them
#macro AI_MAX_BONE_WEIGHTS				0x7fffffff
#macro AI_MAX_FACE_INDICES				0x7fff
#macro AI_MAX_FACES						0x7fffffff
#macro AI_MAX_NUMBER_OF_COLOR_SETS		0x8
#macro AI_MAX_NUMBER_OF_TEXTURECOORDS	0x8
#macro AI_MAX_VERTICES					0x7fffffff



function aiMesh() constructor {
	
	mPrimitiveTypes = 0;
	mNumVertices = 0;
	mNumFaces = 0;
	mVertices = [];
	mNormals = [];
	mTangents = [];
	mBitangents = [];
	mNumColorChannels = 0;
	mColors = [];
	mTextureCoords = array_create(AI_MAX_NUMBER_OF_TEXTURECOORDS, []);
	mTextureCoordsNames = [];
	mNumUVComponents = array_create(AI_MAX_NUMBER_OF_TEXTURECOORDS, 0);
	mFaces = [];
	mNumBones = 0;
	mBones = [];
	mMaterialIndex = 0;
	mName = "";
	mAnimMeshes = [];
	/**
	 *  Method of morphing when anim-meshes are specified.
	 *  @see aiMorphingMethod to learn more about the provided morphing targets.
	 */
	mMethod = 0;
	mAABB = new aiAABB();
	
	static GetNumColorChannels = function() {
		return mNumColorChannels;	
	}
	
	static GetNumUVChannels = function() {
		return array_length(mTextureCoords);	
	}
	
	static HasBones = function() {
		return mNumBones > 0;	
	}
	
	static HasFaces = function() {
		return mFaces > 0;	
	}
	
	static HasNormals = function() {
		return mNormals > 0;	
	}
	
	static HasPositions = function() {
		return mVertices > 0;	
	}
	
	static HasTangentsAndBitangents = function() {
		return mTangents > 0;	
	}
	
	static HasTextureCoords = function() {
		for (var _i = 0; _i < mNumUVComponents; _i++) {
			if ( array_length(mTextureCoords[_i]) > 0 ) {
				return true;	
			}
		}
		return false;
	}
	
	static HasVertexColors = function() {
		for (var _i = 0; _i < GetNumColorChannels(); _i++) {
			if ( array_length(mColors[_i]) > 0 ) {
				return true;	
			}
		}
		return false;
	}
	
	
	
	/// @ignore
	static __read_bound = function() {
		ASSIMP_GetMeshFacesNum()
		
		mName = ASSIMP_GetMeshName();
		
		mPrimitiveTypes = ASSIMP_GetMeshPrimitiveTypes();
		
		mMaterialIndex = ASSIMP_GetMeshMaterialIndex();
		
		mNumFaces = ASSIMP_GetMeshFacesNum();
			for (var _f = 0; _f < mNumFaces; _f++) {
				var _face = new aiFace();
				_face.mNumIndices = ASSIMP_GetMeshFaceVerticesNum(_f);
				for (var _i = 0; _i < mNumIndices; _i++) {
					array_push(_face.mIndices, ASSIMP_GetMeshFaceVertexIndex(_f, _i))
				}
				array_push(mFaces, _face);
			}
		
		mNumVertices = ASSIMP_GetMeshVerticesNum();
			for (var _i = 0; _i < mNumVertices; _i++) {
				var _v = new aiVector3D();
				_v.x = ASSIMP_GetMeshVertexX(_i);
				_v.y = ASSIMP_GetMeshVertexY(_i);
				_v.z = ASSIMP_GetMeshVertexZ(_i);
				array_push(mVertices, _v);
			}
		
		// Normals
		if (ASSIMP_MeshHasNormals()()) {
			for (var _i = 0; _i < mNumVertices; _i++) {
				var _v = new aiVector3D();
				_v.x = ASSIMP_GetMeshNormalX()(_i);
				_v.y = ASSIMP_GetMeshNormalY(_i);
				_v.z = ASSIMP_GetMeshNormalZ(_i);
				array_push(mNormals, _v);
			}
		}
		
		// Tangents
		if (ASSIMP_MeshHasTangents()) {
			for (var _i = 0; _i < mNumVertices; _i++) {
				var _v = new aiVector3D();
				_v.x = ASSIMP_GetMeshTangentX()(_i);
				_v.y = ASSIMP_GetMeshTangentY(_i);
				_v.z = ASSIMP_GetMeshTangentZ(_i);
				array_push(mTangents, _v);
			}
			for (var _i = 0; _i < mNumVertices; _i++) {
				var _v = new aiVector3D();
				_v.x = ASSIMP_GetMeshBitangentX(_i);
				_v.y = ASSIMP_GetMeshBitangentY(_i);
				_v.z = ASSIMP_GetMeshBitangentZ(_i);
				array_push(mBitangents, _v);
			}
		}
		
		mNumBones = ASSIMP_GetMeshBonesNum();
			for (var _i = 0; _i < mNumBones; _i++) {
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
				_bone.mNumWeights = ASSIMP_GetBoneNumWeights();
				_bone.mWeights = array_create(mNumWeights, 0);
				for (var _w = 0; _w < mNumWeights; _w++) {
					mWeights[_w] = new aiVertexWeight(
						ASSIMP_GetBoneVertexIndex(_w),
						ASSIMP_GetBoneVertexWeight(_w)
					);
				}
				
				array_push(mBones, _bone);
			}
		
		mNumColorChannels = ASSIMP_GetMeshColorChannelsNum();
			for (var _ch = 0; _ch < mNumColorChannels; _ch++) {
				var _color_ch = [];
				for (var _i = 0; _i < mNumColorChannels; _i++) {
					var _col = new aiColor4D(
						ASSIMP_GetMeshVertexColorR(_i, _ch),
						ASSIMP_GetMeshVertexColorG(_i, _ch),
						ASSIMP_GetMeshVertexColorB(_i, _ch),
						ASSIMP_GetMeshVertexAlpha(_i, _ch)
					);
				
					array_push(_color_ch, _col);
				}
				array_push(mColors, _color_ch);
			}
		
		
		
		
		
		mNumUVComponents = array_create(AI_MAX_NUMBER_OF_TEXTURECOORDS, 0);
		mTextureCoords = array_create(AI_MAX_NUMBER_OF_TEXTURECOORDS, []);
		mTextureCoordsNames = [];
		
		
		
		
		mAnimMeshes = [];
		
		
		mMethod = ASSIMP_GetMeshMorphMethod();
		
		mAABB.mMin.x = ASSIMP_GetMeshAABBMinX();
		mAABB.mMin.y = ASSIMP_GetMeshAABBMinY();
		mAABB.mMin.z = ASSIMP_GetMeshAABBMinZ();
		mAABB.mMax.x = ASSIMP_GetMeshAABBMaxX();
		mAABB.mMax.y = ASSIMP_GetMeshAABBMaxY();
		mAABB.mMax.z = ASSIMP_GetMeshAABBMaxZ();
	}
}