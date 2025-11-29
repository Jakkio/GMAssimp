/**
 * Represents a two-dimensional vector.
 * @param {Real} _x X component
 * @param {Real} _y Y component
 */
function aiVector2D(_x = 0, _y = 0) constructor {
	x = _x;
	y = _y;
	
	/**
	 * Checks if this vector is equal to another vector.
	 * @param {Struct.aiVector2D} _other The other vector to compare with
	 * @return {Bool} True if vectors are equal, false otherwise
	 */
	static equal = function(_other) {
		return	x == _other.x &&
				y == _other.y ;
	}
	
	/**
	 * Calculates the length of the vector.
	 * @return {Real} The length of the vector
	 */
	static length = function() {
		return sqrt(x*x + y*y);
	}
	
	/**
	 * Normalizes the vector to unit length.
	 * @return {Struct.aiVector2D} Reference to self for chaining
	 */
	static normalize = function() {
		var f = sqrt(x*x + y*y);
		if f != 0 {
			x /= f;
			y /= f;
		}
		return self;
	}
	
	/**
	 * Calculates the squared length of the vector.
	 * @return {Real} The squared length of the vector
	 */
	static square_length = function() {
		return x*x + y*y;
	}
}
