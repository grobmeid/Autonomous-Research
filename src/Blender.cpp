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
    int strlen = sprintf(callString, "%s -b %s", BLENDER_EXEC_PATH, BLEND_FILE_PATH);
    if (strlen < 0) {
     //TODO 
    }

    printf("CALL STRING\n %s \n", callString);
    system("ls Blender");
    system(callString);
  
    return 1;
}

