/**
 * Helper structure to describe a virtual camera.
 * Cameras have a representation in the node graph and can be animated.
 * An important aspect is that the camera itself is also part of the scene graph.
 */
function aiCamera() constructor {
	
	/** The name of the camera. */
	mName = "";
	
	/** Position of the camera relative to the coordinate space defined by the corresponding node. */
	mPosition = new aiVector3D();
	
	/** 'Up' - vector of the camera coordinate system relative to the coordinate space defined by the corresponding node. */
	mUp = new aiVector3D(0, 1, 0);
	
	/** 'LookAt' - vector of the camera coordinate system relative to the coordinate space defined by the corresponding node. */
	mLookAt = new aiVector3D(0, 0, 1);
	
	/** Half horizontal field of view angle, in radians. */
	mHorizontalFOV = pi * 0.25;
	
	/** Distance of the near clipping plane from the camera. */
	mClipPlaneNear = 0.1;
	
	/** Distance of the far clipping plane from the camera. */
	mClipPlaneFar = 1000;
	
	/** Screen aspect ratio. */
	mAspect = 0;
	
	/** Half horizontal orthographic width, in scene units. */
	mOrthographicWidth = 0;
	
	/** Camera transformation matrix. */
	mMatrix = matrix_build_identity();
	
	
	/// @ignore
	static __read_bound = function() {
		mName = ASSIMP_GetCameraName();
		
		
		mPosition = new aiVector3D(
			ASSIMP_GetCameraPositionX(),
			ASSIMP_GetCameraPositionY(),
			ASSIMP_GetCameraPositionZ()
		);
		
		mUp = new aiVector3D(
			ASSIMP_GetCameraUpX(),
			ASSIMP_GetCameraUpY(),
			ASSIMP_GetCameraUpZ()
		);
		
		mLookAt = new aiVector3D(
			ASSIMP_GetCameraLookAtX(),
			ASSIMP_GetCameraLookAtY(),
			ASSIMP_GetCameraLookAtZ()
		);
		
		mHorizontalFOV = ASSIMP_GetCameraHorizontalFov();
		
		mClipPlaneNear = ASSIMP_GetCameraClipPlaneNear();
		
		mClipPlaneFar = ASSIMP_GetCameraClipPlaneFar();
		
		mAspect = ASSIMP_GetCameraAspect();
		
		mOrthographicWidth = ASSIMP_GetCameraOrthographicWidth();
		
		ASSIMP_BindCameraMatrix();
		mMatrix = [
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
		
	}
}
