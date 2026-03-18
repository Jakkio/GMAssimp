// @author		Giacomo Marton
// @version		1.0.0


/**
 * A single influence of a bone on a vertex.
 */
function aiTextureProperty() constructor {
	
	// Default values just for feather type detection
	path = "";
	uvw_source = 0;
	operation = aiTextureOp.ADD;
	mapping = aiTextureMapping.UV;
	mapping_mode_u = aiTextureMapMode.WRAP;
	mapping_mode_v = aiTextureMapMode.WRAP;
	mapping_axis = new aiVector3D(0.0, 0.0, 1.0);
	blend = 0.0;
	uv_transform = new aiUVTransform();
	flags = aiTextureFlags.USE_ALPHA;
	
	// Undefined for all values
	path = undefined;
	uvw_source = undefined;
	operation = undefined;
	mapping = undefined;
	mapping_mode_u = undefined;
	mapping_mode_v = undefined;
	mapping_axis = undefined;
	blend = undefined;
	uv_transform = undefined;
	flags = undefined;
}