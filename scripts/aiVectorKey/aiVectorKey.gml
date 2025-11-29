/**
 * A time-value pair specifying a 3D vector for the given time.
 * Used for position and scaling animation keys.
 */
function aiVectorKey() constructor {
	/** The time of this key */
	mTime = 0;
	
	/** The value of this key as a 3D vector */
	mValue = new aiVector3D();
	
	/** The interpolation method to use (aiAnimInterpolation) */
	mInterpolation = aiAnimInterpolation.LINEAR;
}
