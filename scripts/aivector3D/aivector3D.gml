function aivector3D(_x = 0, _y = 0, _z = 0) constructor{
	x = _x;
	y = _y;
	z = _z;
	
	static equal = function(_other) {
		return	x == _other.x &&
				y == _other.y &&
				z == _other.z ;
	}
	
	static length = function() {
		return sqrt(x*x + y*y + z*z);
	}
	
	static normalize = function() {
		var f = sqrt(x*x + y*y + z*z);
		if f != 0 {
			x /= f;
			y /= f;
			z /= f;
		}
		return self;
	}
	
	static square_length = function() {
		return x*x + y*y + z*z;
	}
}