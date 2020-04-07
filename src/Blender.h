#ifndef Blender_h
#define Blender_h
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BLENDER_EXEC_PATH ("/Applications/Blender.app/Contents/MacOS/Blender")
#define BLEND_FILE_PATH ("Blender/Example\\ Map.blend")
#define PYTHON_SCRIPT_PATH ("Blender/getFrame.py")

int captureImages(double xPosition, double yPosition, double rotation);

#endif
