var _filename;
//_filename = "OrientationTest.glb";
_filename = "BoxTextured.glb";


importer = new aiImporter();
scene = importer.ReadFile(	working_directory + "/" + _filename,
							aiProcess.CONVERT_TO_LEFT_HANDED |
							aiProcess.TARGET_REALTIME_MAX_QUALITY |
							aiProcess.SPLIT_BONE_COUNT |
							aiProcess.OPTIMIZE_GRAPH |
							aiProcess.OPTIMIZE_MESHES |
							aiProcess.VALIDATE_DATA_STRUCTURE |
							aiProcess.GEN_BOUNDING_BOXES
							);

