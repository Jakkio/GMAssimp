// @author		Giacomo Marton
// @version		1.0.0


/**
 * An axis-aligned bounding box.
 * @param	{Struct.aiVector3D} _min		The minimum dimension.
 * @param	{Struct.aiVector3D} _max		The maximum dimension.
 */
function aiAABB(_min = new aiVector3D(), _max = new aiVector3D()) constructor {
	mMin = _min;
	mMax = _max;
}