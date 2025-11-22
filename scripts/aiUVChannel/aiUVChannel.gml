// @author		Giacomo Marton
// @version		1.0.0


/**
 * A mesh can have multiple channels for UV
 */
function aiUVChannel() constructor {
	mName = "";
	/**
	 * Specifies the number of components for a given UV channel.
	 *
	 * Up to three channels are supported (UVW, for accessing volume
	 * or cube maps). If the value is 2 for a given channel n, the
	 * component p.z of mTextureCoords[n] is set to 0.0f.
	 * If the value is 1 for a given channel, p.y is set to 0.0f, too.
	 * @note 4D coordinates are not supported
	 */
	mNumUVComponents = 2;
	mTextureCoords = [];
}