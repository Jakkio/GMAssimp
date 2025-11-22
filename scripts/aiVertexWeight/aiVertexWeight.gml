// @author		Giacomo Marton
// @version		1.0.0


/**
 * A single influence of a bone on a vertex.
 * @param	{Real} _pID			ID
 * @param	{Real} _pWeight		Vertex weight factor 
 */
function aiVertexWeight(_pID = 0, _pWeight = 0) constructor {
	//Index of the vertex which is influenced by the bone
	mVertexId = _pID;
	
	// The strength of the influence in the range (0...1)
	// The influence from all bones at one vertex amounts to 1
	mWeight = _pWeight;
}