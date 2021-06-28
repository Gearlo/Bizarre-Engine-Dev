#!/usr/bin/env python
# -*- coding: utf-8 -*-
from Bizarre import Bizarre, BGame, BVector3f, BVector2f, BSystemContext, BInputContext, ON_WORKING_DIR, SPRITE_ROTATE_NONE, SPRITE_ROTATE_HALF_Z, SPRITE_ROTATE_FULL
import model as testModel
import random

'''
    En este ejemplo se hace una cuadricula de sprites separados aunque lo adecuado para evitar errores de
    visualización sería que la cuadricula fuese una sola malla en lugar de muchas individuales
'''

class compositedMeshExample(BGame):
    def __init__(self):
        self.mouse_dx = 0.0 # almacenará el movimiento horizontal del mouse
        self.mouse_dy = 0.0 # almacenará el movimiento vertical del mouse

        self.TreesNumber = 100 # numero de arboles
        self.RocksNumber = 10 # numero de rocas
        self.GrassNumber = 5000 # numero de pastos
    
    def onBegin(self):
        engine = Bizarre() # obtener la instancia en ejecución del motor
        world = engine.getWorld() # obtener el gestor de mundo (gestiona las escenas y otras cosas)
        worldScene = world.getWorldScene() # obtener la escena de mundo, acá se cargan los objetos principales del juego
        skyScene = world.getSkyScene() # está escena sirve para cargar en ella objetos que se verán fijos al fondo, como el cielo y las nubes
        guiScene = world.getGuiScene() # en esta escena se cargan objetos 2D, como sprites o el HUD
        
        self.systemContext = BSystemContext() # El contexto del sistema tiene algunos métodos simples pero útiles       
        self.inputContext = BInputContext() #obtener instancia del contexto de entrada y colocarlo como miembro de la clase
        self.worldCamera = worldScene.getCurrentCamera() # obtener la camara principal de la escena de mundo
        self.renderInfo = engine.getRenderInfo() # obtiene un objeto tipo BRenderInfo, el cual tiene información y funciones relacionadas al renderizado de pantalla

        self.worldCamera.setPosition( BVector3f(7.48113, -6.50764, 5.34367) )
        self.worldCamera.setEulerRotation( BVector3f(63.5593, 0, 46.6919) )

        self.systemContext.hideCursor() # ocultar el cursor
        self.renderInfo.disableTextureFilter(True)
        #self.renderInfo.disableTextureCompression(False)
        assetsManager = engine.getAssetsManager() # obtener instancia del gestor de assets
        

        subMesh0 = {}
        subMesh0['vertices'] = testModel.vertices
        subMesh0['texCoords'] = testModel.texCoords
        subMesh0['indices'] = testModel.indices

        mesh = assetsManager.createMesh( subMeshes = [ subMesh0 ] )
        subMesh = mesh.getSubMesh(0)

        cModel = worldScene.addNewCompositedModel()
        baseMesh = cModel.getMesh()
        baseMesh.allocTextures(1)
        baseMesh.addNewTexture( assetsManager.loadTexture( 'textures/pixels/box/iron_block.png' ) )

        for i in range(8):
            for j in range(8):
                cModel.addCompositeSubMesh( subMesh, BVector3f( 2.0*i, 2.0*j, 0.0 ) )
        
        cModel.bake()

        screen_size = self.systemContext.getScreenSize() # obtener el tamaño de la pantalla
        self.systemContext.setCursorPosition(screen_size[0]/2, screen_size[1]/2) # centrar el mouse en la pantalla

        
    def onUpdate(self):
        self.mouse_dx = self.inputContext.getAxis("MOUSE_X") # obtener que tanto se ha movido horizontalmente el mouse conrespecto al centro de la pantalla desde el último fotograma renderizado 
        self.mouse_dy = self.inputContext.getAxis("MOUSE_Y")

        self.mouse_dx = ( self.mouse_dx - .5 ) * 20 # aplicar ajustes al movimiento del mpuse
        self.mouse_dy = ( self.mouse_dy - .5 ) * 20 

        camera_r = self.worldCamera.getEulerRotation()# obtener rotación actual de la camara

        camera_r.z = camera_r.z - self.mouse_dx  # si el mouse se ha movido desde el ultimo fotograma renderizado entonces agregarlo al valor de rotación de la camara
        camera_r.x = camera_r.x - self.mouse_dy 

        screen_size = self.systemContext.getScreenSize() # obtener el tamaño de la pantalla
        self.systemContext.setCursorPosition(screen_size[0]/2, screen_size[1]/2) # centrar el mouse en la pantalla para reiniciar el movimiento del mismo

        self.worldCamera.setEulerRotation( camera_r ) # asignar la nueva rotación a la camara

        cameraPosition = self.worldCamera.getPosition() # obtenr posicion actual de la camara
        displace = BVector3f(.0, .0, .0)

        if self.inputContext.isKeyPressed('A'): # saber si la tecla A esta presionada
            displace.x = displace.x - 0.08 # alterar la posici[on] de la camara

        if self.inputContext.isKeyPressed('D'): # saber si la tecla D esta presionada
            displace.x = displace.x + 0.08

        if self.inputContext.isKeyPressed('W'): # saber si la tecla W esta presionada
            displace.z = displace.z - 0.08

        if self.inputContext.isKeyPressed('S'): # saber si la tecla S esta presionada
            displace.z = displace.z + 0.08

        displace = self.worldCamera.getRotatedVector(displace)
        cameraPosition.add(displace)

        self.worldCamera.setPosition( cameraPosition ) # asignar nueva posici[on]



class SpritesExample(BGame):
    def __init__(self):
    
        #self.gridPosition = BVector3f( .0, .0, .0 )
        self.plantNumber = 15 # número de plantas 
        self.plantsRange = [31, 35] # rango de los sprites de plantas que se elegirán aleatoriamente 

        self.spriteSize = 3.0 # tamaño del sprite
        '''
        La siguiente lista bidimensional representa la cuadricula, el numero
        es el numero de sprite que se mostrará en cada casilla
        '''
        self.gridDef = []
        self.gridDef.append(  [ 9,14,14,14,14,14,14,14,14,14,14,14, 7]  )
        self.gridDef.append(  [ 9, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 7]  )
        self.gridDef.append(  [ 9, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 7]  )
        self.gridDef.append(  [ 9, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 7]  )
        self.gridDef.append(  [ 9, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 7]  )
        self.gridDef.append(  [ 9, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 8, 7]  )
        self.gridDef.append(  [ 9, 1, 0, 1, 0, 1, 0, 1, 0, 1, 8, 8, 7]  )
        self.gridDef.append(  [ 9, 0, 1, 0, 1, 0, 1, 0, 8, 8, 9, 9, 7]  )
        self.gridDef.append(  [ 9, 1, 0, 1, 0, 1, 0, 8, 8, 9, 9,14, 7]  )
        self.gridDef.append(  [ 9, 0, 1, 0, 1, 0, 1, 8, 9, 9,14,14, 7]  )
        self.gridDef.append(  [ 9, 1, 0, 8, 8, 8, 8, 8, 9,14,14,14, 7]  )
        self.gridDef.append(  [ 9, 8, 8, 8, 9, 9, 9, 9,14,14,14,14, 7]  )
        self.gridDef.append(  [ 9, 9, 9, 9, 9,14,14,14,14,14,14,14, 7]  )
        self.gridDef.append(  [ 9,14,14,14,14,14,14,14,14,14,14,14, 7]  )

    def onBegin(self):
        engine = Bizarre() # obtener la instancia en ejecución del motor
        world = engine.getWorld() # obtener el gestor de mundo (gestiona las escenas y otras cosas)
        worldScene = world.getWorldScene() # obtener la escena de mundo, acá se cargan los objetos principales del juego
        skyScene = world.getSkyScene() # está escena sirve para cargar en ella objetos que se verán fijos al fondo, como el cielo y las nubes
        guiScene = world.getGuiScene() # en esta escena se cargan objetos 2D, como sprites o el HUD
        
        self.systemContext = BSystemContext() # El contexto del sistema tiene algunos métodos simples pero útiles       
        self.inputContext = BInputContext() #obtener instancia del contexto de entrada y colocarlo como miembro de la clase
        self.worldCamera = worldScene.getCurrentCamera() # obtener la camara principal de la escena de mundo
        self.renderInfo = engine.getRenderInfo() # obtiene un objeto tipo BRenderInfo, el cual tiene información y funciones relacionadas al renderizado de pantalla

        #self.systemContext.hideCursor() # ocultar el cursor
        self.renderInfo.disableTextureFilter(True)
        assetsManager = engine.getAssetsManager() # obtener instancia del gestor de assets

        skyMeshRef = assetsManager.loadMesh( "meshs/campfire/sky.xml", ON_WORKING_DIR ) # leer el cielo usado en campfire

        gradientRef   = assetsManager.loadTexture( "textures/gradient0.png", ON_WORKING_DIR ) # carga una textura que se usará como cielo
        textureCatalog = assetsManager.loadTexture( "textures/pixels/pack0.png", ON_WORKING_DIR ) # carga una textura que se usará como cielo

        skyObj = skyScene.addNewModel( skyMeshRef ) # agregar el cielo de campifire en la escena de cielo
        skyObj.getMesh().getTexture(0).setTextureRef(gradientRef) # cambiar la textura del cielo
        
        i = 0 # contador vertical
        j = 0 # contador horizontal
        for row in self.gridDef: # por cada fila
            j = 0
            for spriteNumber in row: # por cada sprite
                sprite = worldScene.addNewSprite( textureCatalog, self.spriteSize, True ) # agregar un nuevo sprite en escena 3D
                sprite.setRotationType(SPRITE_ROTATE_NONE) # el sprite no rotará por si mismo, la misma se definirá por el programador
                sprite.setPosition( BVector3f( i*self.spriteSize - self.spriteSize*len(self.gridDef)/2.0, j*self.spriteSize - self.spriteSize*len(row)/2.0, 0) ) #posicionar el sprite
                sprite.setTilesNumber(6, 6) # es la cantidad de sprites horizontales y verticales que tiene la imagen que se usará
                sprite.setTile(spriteNumber) # definir que sprite se usará en la casilla
                #si es un sprite de muro y esta en el border frontal
                if spriteNumber in (6,7,8,9,10) and j == 0:
                    p = sprite.getPosition()
                    p.y = p.y + (self.spriteSize / 2.0)
                    p.z = p.z + (self.spriteSize / 2.0)
                    sprite.setPosition(p)
                    sprite.setEulerRotation( BVector3f( 90.0, .0, .0) )
                #si es un sprite de muro y esta en el border trasero
                if spriteNumber in (6,7,8,9,10) and j == len(row) - 1:
                    p = sprite.getPosition()
                    p.y = p.y - (self.spriteSize / 2.0)
                    p.z = p.z + (self.spriteSize / 2.0)
                    sprite.setPosition(p)
                    sprite.setEulerRotation( BVector3f( 90.0, .0, .0) )
                j = j + 1
            i = i + 1

        '''
            Crear sprites de plantas con sprites y posiciones aleatorias
        '''
        for i in range( self.plantNumber ): # ciclo, la cantidad de interaciones está definida por la variable self.plantsNumber
            sprite = worldScene.addNewSprite( textureCatalog, self.spriteSize/4.0, True )
            sprite.setTilesNumber(6, 6)
            sprite.setRotationType(SPRITE_ROTATE_HALF_Z) # los sprites giraran en el eje z hacia la camara
            sprite.setTile( int( random.uniform( self.plantsRange[0], self.plantsRange[1]) ) ) # elegir aleatyoriamente el sprite
            x = random.uniform(-10.0, 10.0) # posiion aleatoria en x entre -10 y 10
            y = random.uniform(-10.0, 10.0) # posiion aleatoria en y entre -10 y 10
            s = random.uniform(1.6, 1.7) # escala aleatoria en x entre -1.6 y 1.7
            sprite.setPosition( BVector3f(x, y, ((self.spriteSize/6.0)/2*s) +0.2) )
            sprite.setScale( BVector3f(s, s, s) )
            sprite.setEulerRotation( BVector3f(-90.0, .0, .0) )


        #posicionar camara
        self.worldCamera.setPosition( BVector3f(-0.879999995232, -10.7999925613, 12.5599918365) )
        self.worldCamera.setEulerRotation( BVector3f(40.0, 0.0, .0) )

        
    def onUpdate(self):
        position = self.worldCamera.getPosition()
        rotation = self.worldCamera.getEulerRotation()

        #mover camara si es necesario
        if self.inputContext.isKeyPressed('A'): # saber si la tecla A esta presionada
            position.x = position.x - 0.08 # alterar la posici[on] de la camara

        if self.inputContext.isKeyPressed('D'): # saber si la tecla D esta presionada
            position.x = position.x + 0.08

        if self.inputContext.isKeyPressed('W'): # saber si la tecla W esta presionada
            position.y = position.y + 0.08

        if self.inputContext.isKeyPressed('S'): # saber si la tecla S esta presionada
            position.y = position.y - 0.08

        if self.inputContext.isKeyPressed('SPACE'): # saber si la tecla S esta presionada
            position.z = position.z + 0.08

        if self.inputContext.isKeyPressed('B'): # saber si la tecla S esta presionada
            position.z = position.z - 0.08

        if self.inputContext.isKeyPressed('UP'): # saber si la tecla S esta presionada
            rotation.x = rotation.x + 0.2
        
        if self.inputContext.isKeyPressed('DOWN'): # saber si la tecla S esta presionada
            rotation.x = rotation.x - 0.2

        if self.inputContext.isKeyPressed('RIGHT'): # saber si la tecla S esta presionada
            rotation.z = rotation.z - 0.2
        
        if self.inputContext.isKeyPressed('LEFT'): # saber si la tecla S esta presionada
            rotation.z = rotation.z + 0.2

        self.worldCamera.setPosition( position )
        self.worldCamera.setEulerRotation( rotation )