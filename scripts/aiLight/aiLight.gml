/**
 * Helper structure to describe a light source.
 * Assimp supports multiple sorts of light sources, including spot lights, point lights and directional lights.
 * All of them are defined with just a single structure and distinguished by their parameters.
 */
function aiLight() constructor {
	
	/** The name of the light source. */
	mName = "";
	
	/** The type of the light source (aiLightSourceType). */
	mType = aiLightSourceType.UNDEFINED;
	
	/** Position of the light source in space. Relative to the transformation of the node corresponding to the light. */
	mPosition = new aiVector3D();
	
	/** Direction of the light source in space. Relative to the transformation of the node corresponding to the light. */
	mDirection = new aiVector3D();
	
	/** Up direction of the light source in space. Relative to the transformation of the node corresponding to the light. */
	mUp = new aiVector3D();
	
	/** Constant light attenuation factor. */
	mAttenuationConstant = 0;
	
	/** Linear light attenuation factor. */
	mAttenuationLinear = 1;
	
	/** Quadratic light attenuation factor. */
	mAttenuationQuadratic = 0;
	
	/** Diffuse color of the light source. */
	mColorDiffuse = new aiColor3D();
	
	/** Specular color of the light source. */
	mColorSpecular = new aiColor3D();
	
	/** Ambient color of the light source. */
	mColorAmbient = new aiColor3D();
	
	/** Inner angle of a spot light's light cone. */
	mAngleInnerCone = pi*2;
	
	/** Outer angle of a spot light's light cone. */
	mAngleOuterCone = pi*2;
	
	/** Size of area light source. */
	mSize = new aiVector2D();
	
	
	/// @ignore
	static __read_bound = function() {
		mName = ASSIMP_GetLightName();
		
		mType = ASSIMP_GetLightSourceType();
		
		mPosition = new aiVector3D(
			ASSIMP_GetLightPositionX(),
			ASSIMP_GetLightPositionY(),
			ASSIMP_GetLightPositionZ()
		);
		
		mDirection = new aiVector3D(
			ASSIMP_GetLightDirectionX(),
			ASSIMP_GetLightDirectionY(),
			ASSIMP_GetLightDirectionZ()
		);
		
		mUp = new aiVector3D(
			ASSIMP_GetLightUpX(),
			ASSIMP_GetLightUpY(),
			ASSIMP_GetLightUpZ()
		);
		
		mAttenuationConstant = ASSIMP_GetLightConstantAttenutation();
		
		mAttenuationLinear = ASSIMP_GetLightLinearAttenutation();
		
		mAttenuationQuadratic = ASSIMP_GetLightQuadraticAttenutation();
		
		mColorDiffuse = new aiColor3D(
			ASSIMP_GetLightDiffuseColorR(),
			ASSIMP_GetLightDiffuseColorG(),
			ASSIMP_GetLightDiffuseColorB()
		);
		
		mColorSpecular = new aiColor3D(
			ASSIMP_GetLightSpecularColorR(),
			ASSIMP_GetLightSpecularColorG(),
			ASSIMP_GetLightSpecularColorB()
		);
		
		mColorAmbient = new aiColor3D(
			ASSIMP_GetLightAmbientColorR(),
			ASSIMP_GetLightAmbientColorG(),
			ASSIMP_GetLightAmbientColorB()
		);
		
		mAngleInnerCone = ASSIMP_GetLightConeInnerAngle();
		
		mAngleOuterCone = ASSIMP_GetLightConeOuterAngle();
		
		mSize = new aiVector2D(
			ASSIMP_GetLightSizeX(),
			ASSIMP_GetLightSizeY()
		);
	}
}
