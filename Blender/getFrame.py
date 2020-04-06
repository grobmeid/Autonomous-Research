import os
import bpy
import threading
import sys

for window in bpy.context.window_manager.windows:
    screen = window.screen


argv = sys.argv
argv = argv[argv.index("--") + 1:] 


Cameras = ['Camera_Center', 'Camera_Left', 'Camera_Right']

filepath = bpy.data.filepath
exportPath = os.path.dirname(filepath) + "/CameraData/"

Car = o = bpy.data.objects["Car"]

Car.location = [float(argv[0]), float(argv[1]), 0.5];
Car.rotation_euler = [0, 0, float(argv[2])]

scn = bpy.context.scene

for camera in Cameras:
    bpy.context.scene.camera = bpy.context.scene.objects[camera]
    area = next(area for area in screen.areas if area.type == 'VIEW_3D')
    area.spaces[0].region_3d.view_perspective = 'CAMERA'
    scn.render.filepath = exportPath + camera
    bpy.ops.render.opengl(write_still=True)
    pass

bpy.ops.wm.quit_blender()
