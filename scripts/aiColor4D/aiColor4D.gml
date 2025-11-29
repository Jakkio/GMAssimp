/**
 * Represents a color value with red, green, blue and alpha components.
 * Color values range from 0 to 1.
 * @param {Real} _r Red component
 * @param {Real} _g Green component
 * @param {Real} _b Blue component
 * @param {Real} _a Alpha component
 */
function aiColor4D(_r = 0, _g = 0, _b = 0, _a = 0) constructor {
	r = _r;
	g = _g;
	b = _b;
	a = _a;
	
	/**
	 * Converts to a single variable color compatible with other game maker functions.
	 * Note: Alpha component is not included in the conversion.
	 * @return {Real} GameMaker color value
	 */
	static to_gm_color = function() {
		return make_colour_rgb(r*255, g*255, b*255);
	}
}
