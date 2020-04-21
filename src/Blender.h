#ifndef Blender_h
#define Blender_h

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#define BLENDER_EXEC_PATH ("/Applications/Blender.app/Contents/MacOS/Blender")
#define BLEND_FILE_PATH ("Blender/Example\\ Map.blend")
#define PYTHON_SCRIPT_PATH ("Blender/getFrame.py")
#include <pthread.h>
#include <unistd.h>
#endif

#ifdef WIN32
#define BLENDER_EXEC_PATH ("\"BlenderEXEC\\blender.exe\"")
#define BLEND_FILE_PATH ("\"Blender\\Example Map.blend\"")
#define PYTHON_SCRIPT_PATH ("\"Blender\\getFrame.py\"")
#include <Windows.h>
#endif



int captureImages(double xPosition, double yPosition, double rotation);

#endif
