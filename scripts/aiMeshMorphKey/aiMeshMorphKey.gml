/**
 * A time-value pair specifying morph mesh animation data for the given time.
 * Contains an array of values and weights for morph target animation.
 */
function aiMeshMorphKey() constructor {
	/** The time of this key */
	mTime = 0;
	
	/** Array of values and weights for this morph key. Each entry contains a value and weight pair. */
	mValues = [];
}
