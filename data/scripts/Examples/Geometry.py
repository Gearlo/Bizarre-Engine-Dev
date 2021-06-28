#!/usr/bin/env python
# -*- coding: utf-8 -*-

from Bizarre import Bizarre, BGame, BVector3f,BVector2f, BMeshRef, U_USHORT, ON_WORKING_DIR, BImage
import model as testModel
from random import randint

#from math import min

class MeshHandling(BGame):
    def __init__(self):
        pass

    def onBegin(self):
        engine = Bizarre() # obtener la instancia en ejecución del motor
        world = engine.getWorld() # obtener el gestor de mundo (gestiona las escenas y otras cosas)
        worldScene = world.getWorldScene() # obtener la escena de mundo, acá se cargan los objetos principales del juego
        skyScene = world.getSkyScene() # está escena sirve para cargar en ella objetos que se verán fijos al fondo, como el cielo y las nubes
        guiScene = world.getGuiScene() # en esta escena se cargan objetos 2D, como sprites o el HUD

        self.worldCamera = worldScene.getCurrentCamera() # obtener la camara principal de la escena de mundo
        self.worldCamera.setPosition( BVector3f( 3.583, -3.40742, 2.23069) )
        self.worldCamera.setEulerRotation( BVector3f( 63.5607, -0.00023, 46.693) )
        
        self.assetsManager = engine.getAssetsManager()

        subMesh0 = {}
        subMesh0['vertices'] = testModel.vertices
        subMesh0['texCoords'] = testModel.texCoords
        subMesh0['indices'] = testModel.indices
        
        self.renderInfo = engine.getRenderInfo()
        self.renderInfo.disableTextureFilter(True)
        #self.renderInfo.disableTextureCompression(False)


        self.image = BImage(16, 16, 4)
        for i in range(16):
            for j in range(16):
                self.image.writePixel( i, j, i*9, 255, 255, min( 255*(j%2) + 255*(i%2), 255) )   

        texture0 = self.assetsManager.loadTexture('textures/colorGrid.png', ON_WORKING_DIR)
        self.texture1 = self.assetsManager.createTexture( 'testTexture', self.image )

        #mesh = self.assetsManager.createMesh( subMeshes = [ subMesh0, subMesh1 ], textureRefs = [ texture0 ] )

        mesh = self.assetsManager.createMesh( subMeshes = [ subMesh0 ], textureRefs = [ self.texture1 ] )


        meshRef = BMeshRef( mesh,"testMesh" )   
        self.obj = worldScene.addNewModel( meshRef )

        self.i = 1

    def onUpdate(self):
        self.i = self.i + 1 
        if self.i > 10:
            self.image.writePixel( randint(0, 15), randint(0, 15), randint(0, 255), randint(0, 255), randint(0, 255), 255 )
            self.texture1.update()
            self.i = 0

        p = self.obj.getEulerRotation()
        p.z = p.z + .30
        self.obj.setEulerRotation( p )