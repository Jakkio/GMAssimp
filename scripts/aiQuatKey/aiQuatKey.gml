/**
 * A time-value pair specifying a rotation for the given time.
 * Rotations are expressed with quaternions.
 */
function aiQuatKey() constructor {
	/** The time of this key */
	mTime = 0;
	
	/** The value of this key as a quaternion */
	mValue = new aiQuaternion();
	
	/** The interpolation method to use (aiAnimInterpolation) */
	mInterpolation = aiAnimInterpolation.LINEAR;
}
