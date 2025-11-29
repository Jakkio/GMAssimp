/**
 * Represents a three-dimensional vector.
 * @param {Real} _x X component
 * @param {Real} _y Y component
 * @param {Real} _z Z component
 */
function aiVector3D(_x = 0, _y = 0, _z = 0) constructor {
	x = _x;
	y = _y;
	z = _z;
	
	/**
	 * Checks if this vector is equal to another vector.
	 * @param {Struct.aiVector3D} _other The other vector to compare with
	 * @return {Bool} True if vectors are equal, false otherwise
	 */
	static equal = function(_other) {
		return	x == _other.x &&
				y == _other.y &&
				z == _other.z ;
	}
	
	/**
	 * Calculates the length of the vector.
	 * @return {Real} The length of the vector
	 */
	static length = function() {
		return sqrt(x*x + y*y + z*z);
	}
	
	/**
	 * Normalizes the vector to unit length.
	 * @return {Struct.aiVector3D} Reference to self for chaining
	 */
	static normalize = function() {
		var f = sqrt(x*x + y*y + z*z);
		if f != 0 {
			x /= f;
			y /= f;
			z /= f;
		}
		return self;
	}
	
	/**
	 * Calculates the squared length of the vector.
	 * @return {Real} The squared length of the vector
	 */
	static square_length = function() {
		return x*x + y*y + z*z;
	}
}
