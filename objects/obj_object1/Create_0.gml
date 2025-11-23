var _filename;
//_filename = "OrientationTest.glb";
_filename = "BoxTextured.glb";


importer = new aiImporter();
scene = importer.ReadFile(	working_directory + "/" + _filename,
							ASSIMP_PP.CONVERT_TO_LEFT_HANDED |
							ASSIMP_PP.TARGET_REALTIME_MAX_QUALITY |
							ASSIMP_PP.SPLIT_BONE_COUNT |
							ASSIMP_PP.OPTIMIZE_GRAPH |
							ASSIMP_PP.OPTIMIZE_MESHES |
							ASSIMP_PP.VALIDATE_DATA_STRUCTURE |
							ASSIMP_PP.GEN_BOUNDING_BOXES
							);
