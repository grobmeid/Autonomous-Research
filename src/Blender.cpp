#include "Blender.h"

int captureImages(double xPosition, double yPosition, double rotation) {
  /***************************************************
  This block is currently nonfunctional, execv leads to Blender reaching
  a segmentation fault
    pid_t childID = fork();
    if (childID == 0) {

        char const* blendFile[] = "Example Map.blend";
        char const* flags[] = "-P getFrame.py";
        char argString[] = EXECV_ARGS;
        char* const argv[] = {argString};
        int t = execv(BLENDER_EXEC_PATH, NULL);
        printf("%d\n", t);


    }
  *************************************************/
    char callString[316];
    int strlen = sprintf(callString, "%s -b %s -P %s -- %f %f %f", BLENDER_EXEC_PATH, BLEND_FILE_PATH, PYTHON_SCRIPT_PATH, xPosition, yPosition, rotation);
    if (strlen < 0) {
      /* UH OH */
    }
    system(callString);
    return 1;
}
