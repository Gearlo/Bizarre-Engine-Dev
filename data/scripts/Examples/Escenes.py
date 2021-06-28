#!/usr/bin/env python
# -*- coding: utf-8 -*-

from Bizarre import Bizarre, BGame, BVector3f, BVector2f, BInputContext, ON_WORKING_DIR, BSystemContext, GUI_ALIGN_LEFT, GUI_ALIGN_CENTER
from math import pi as PI, fabs, cos, sin
import random


from Bizarre import BMeshRef, U_USHORT

'''
    En este ejemplo, se creará una scena de minibosque con arboles y rocas en posiciones aleatorias
'''
class CampfireExample(BGame):
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

        self.systemContext.hideCursor() # ocultar el cursor
        #self.renderInfo.disableTextureFilter(True)
        self.renderInfo.disableTextureCompression(False)
        assetsManager = engine.getAssetsManager() # obtener instancia del gestor de assets
        
        '''
            A continuación se cargan las referencias de varios objetos para la escena, dichos objetos están
            en un archivo de texto plano escrito en notación xml, estos se pueden crear en blender y exportarlos
            con el addon maratis exportes (se encuentra en la carpeta tools), un punto a tomar en cuenta es que 
            el material de dichos objetos debe tener un Emit alto, ya que en la escena no hay fuentes de luz.
        '''
        skyMeshRef = assetsManager.loadMesh( "meshs/campfire/sky.xml", ON_WORKING_DIR ) # cielo, esta es una esfera con una textura 360
        groundRef = assetsManager.loadMesh( "meshs/campfire/ground.xml", ON_WORKING_DIR ) # suelo
        rockRef = assetsManager.loadMesh( "meshs/campfire/rock0.xml", ON_WORKING_DIR ) # roca
        pineRef = assetsManager.loadMesh( "meshs/campfire/pine.xml", ON_WORKING_DIR ) # arbol
        grassRef = assetsManager.loadMesh( "meshs/campfire/grass.xml", ON_WORKING_DIR ) # arbol

        skyScene.addNewModel( skyMeshRef ) # agregar el cielo a la escena de cielo
        worldScene.addNewModel( groundRef ) # agregar suelo a la escena de mundo
  
        rocks = [] # lista de las rocas que se posicionarán aleatoriamente
        for i in range( self.RocksNumber ): # ciclo, la cantidad de interaciones está definida por la variable self.RocksNumber
            rockN = worldScene.addNewModel( rockRef ) # cargar una roca en la escena de mundo
            x = random.uniform(-90.0, 90.0) # definir una posición en x aleatoria entre -90 y 90
            y = random.uniform(-90.0, 90.0) # definir una posición en y aleatoria entre -90 y 90
            rz = random.uniform(0.0, 360.0) # definir una rotación en z aleatoria entre 0 y 360°
            s = random.uniform(0.6, 1.7) # definir una escala aleatoria entre 60 y 170 por ciento
            rockN.setPosition( BVector3f(x, y, -0.772713) ) # establecer la posición x y y calculadas aleatoriamente y la z predefinida
            rockN.setEulerRotation( BVector3f(.0, .0, rz) ) # establecer rotación aleatoria en z
            rockN.setScale( BVector3f(s, s, s) ) # establecer escala
            rocks.append( rockN ) # agregar la roca a la lista


        pines = [] # lista de los arboles que se posicionarán aleatoriamente
        for i in range( self.TreesNumber ): # ciclo, la cantidad de interaciones está definida por la variable self.TreesNumber
            pineN = worldScene.addNewModel( pineRef ) # cargar un arbol en la escena de mundo
            x = random.uniform(-90.0, 90.0)
            y = random.uniform(-90.0, 90.0)
            rz = random.uniform(0.0, 360.0)
            s = random.uniform(0.6, 1.7)
            pineN.setPosition( BVector3f(x, y, -0.772713) )
            pineN.setEulerRotation( BVector3f(.0, .0, rz) )
            pineN.setScale( BVector3f(s, s, s) )
            pines.append( pineN )

        grasss = [] # lista de los arboles que se posicionarán aleatoriamente
        for i in range( self.GrassNumber ): # ciclo, la cantidad de interaciones está definida por la variable self.TreesNumber
            grasssN = worldScene.addNewModel( grassRef ) # cargar un arbol en la escena de mundo
            x = random.uniform(-90.0, 90.0)
            y = random.uniform(-90.0, 90.0)
            rz = random.uniform(0.0, 360.0)
            s = random.uniform(0.6, 2.7)
            grasssN.setPosition( BVector3f(x, y, -2.6) )
            grasssN.setEulerRotation( BVector3f(.0, .0, rz) )
            grasssN.setScale( BVector3f(s, s, s) )
            grasss.append( pineN )

        self.worldCamera.setPosition( BVector3f(.0,.0,3.0) ) # posicionar la camara princiap de la escena de mundo
        self.worldCamera.setEulerRotation( BVector3f( 0.0,.0,.0) ) # asignar una rotación para la camara princiap de la escena de mundo

        '''
            Crear un sprite invisible, el texto que en el se mostrará será la cantidad de fps con que se ejecuta el programa
        '''
        textureRef0 = assetsManager.loadTexture("textures/invisible-background.png", ON_WORKING_DIR)
        fontRef0 = assetsManager.loadFont("fonts/Roboto-Light.ttf", ON_WORKING_DIR)

        self.sprite0 = guiScene.addNewSprite( textureRef0, 0.08 )
        self.sprite0.setPosition( BVector3f( 0.005, 0.005, .0) )
        self.sprite0.addText(fontRef0, "fps" )
        self.sprite0.setTextSize( 6.0 )

        screen_size = self.systemContext.getScreenSize() # obtener el tamaño de la pantalla
        self.systemContext.setCursorPosition(screen_size[0]/2, screen_size[1]/2) # centrar el mouse en la pantalla

        
    def onUpdate(self):
        self.mouse_dx = self.inputContext.getAxis("MOUSE_X") # obtener que tanto se ha movido horizontalmente el mouse conrespecto al centro de la pantalla desde el último fotograma renderizado 
        self.mouse_dy = self.inputContext.getAxis("MOUSE_Y")

        self.mouse_dx = ( self.mouse_dx - .5 ) * 20 # aplicar ajustes al movimiento del mpuse
        self.mouse_dy = ( self.mouse_dy - .5 ) * 20 

        self.sprite0.setText( str( self.renderInfo.getFps() ) )# mostrar la cantidad de fps hasta el momento

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
        





#######################################################################################################
#######################################################################################################
#######################################################################################################

from os import listdir
from os.path import isfile, join


class MeshViewerExample(BGame):
    def __init__(self):
        self.Hangle = .0 # acá se almacena el angulo horizontal de la camara
        self.Vangle = .0 # acá se almacena el angulo vertical de la camara
        self.radius = 5.0 # radio de la orbita de la camara, controla que tan lejos se visualiza el objeto
        self.center = BVector3f(.0, .0, .0) # La posición donde se mostrará el objeto

    def onBegin(self):
        self.engine = Bizarre()
        world = self.engine.getWorld()
        worldScene = world.getWorldScene()
        skyScene = world.getSkyScene()
        guiScene = world.getGuiScene()

        self.systemContext = BSystemContext()        
        self.inputContext = BInputContext()
        self.systemContext.hideCursor()

        renderInfo = self.engine.getRenderInfo()
        renderInfo.disableTextureFilter(True) # desabilitar el suavizado de texturas para que las texturas pequeñas puedan verse como pixel art

        assetsManager = self.engine.getAssetsManager()
        
        skyMeshRef = assetsManager.loadMesh( "meshs/campfire/sky.xml", ON_WORKING_DIR ) # leer el cielo usado en campfire
        objectForViewRef = assetsManager.loadMesh( "meshs/simpleCube.xml", ON_WORKING_DIR ) # se carga un cubo, a este cubo se le cambiará las texturas

        gradientRef   = assetsManager.loadTexture( "textures/gradient0.png", ON_WORKING_DIR ) # carga una textura que se usará como cielo
        pixelTreesRef = assetsManager.loadTexture( "textures/pixels/trees.png", ON_WORKING_DIR ) # cargar una pequeña textura pixel art

        self.boxTextureCurrent = 0 # aquí se almacenará la textura que se estará visualizando
        '''
            Se cargarán todas las imagenes PNG que se encuentren en la carpeta textures/pixels/box/ y mediante las teclas direccionales
            podrá cambiarse la textura del objeto secuencialmente
        '''
        boxTexturesDir = self.systemContext.getWorkingDirectory() + '/textures/pixels/box/' # obtener ruta completa de la carpeta
        boxTexturesNames = [ f for f in listdir(boxTexturesDir) if isfile(join(boxTexturesDir, f)) and '.png' in f] # obtener el nombre de todas las imagenes png en la carpeta
        boxTexturesNames.sort() # ordenar los nombres de las imagenes
        self.boxTextures = [] # aqui se guardarán las referencias de las texturas

        for textureName in boxTexturesNames: # ciclo, iterar todas las imagenes
            self.boxTextures.append( assetsManager.loadTexture( "textures/pixels/box/" + textureName, ON_WORKING_DIR ) ) # carga la referencia de una textura y la almacena en la lista

        skyObj = skyScene.addNewModel( skyMeshRef ) # agregar el cielo de campifire en la escena de cielo
        skyObj.getMesh().getTexture(0).setTextureRef(gradientRef) # cambiar la textura del cielo

        self.objectForView = worldScene.addNewModel( objectForViewRef ) # agregar el cubo en la escena de mundo
        self.objectForView.getMesh().getTexture(0).setTextureRef( self.boxTextures[ self.boxTextureCurrent ] ) # cambiar la textura del cubo

        self.worldCamera = worldScene.getCurrentCamera()
        #self.worldCamera.setPosition( self.center ) 
        self.worldCamera.lookAt( self.center ) # alinear la camara para que observe a un punto especifico

        sprite0 = guiScene.addNewSprite( pixelTreesRef, 0.09 ) # agregar la pequeña textura pixel art de arboles
        sprite0.setPosition( BVector3f( 0.1, 0.1, .0) ) # asignar posición a la textura anterior
        
        self.inputContext = self.engine.getInputContext()
        s_size = self.systemContext.getScreenSize()
        self.systemContext.setCursorPosition(s_size[0]/2, s_size[1]/2)


    def onUpdate(self):
        #ver la textura anterior
        if self.inputContext.onKeyDown('LEFT'):
            self.boxTextureCurrent = self.boxTextureCurrent - 1 # cambiar el numero de la textura actual
            self.objectForView.getMesh().getTexture(0).setTextureRef( self.boxTextures[ self.boxTextureCurrent % len( self.boxTextures ) ] ) # cambiar la textura del cubo por la texura actual

        #ver la textura siguiente
        if self.inputContext.onKeyDown('RIGHT'):
            self.boxTextureCurrent = self.boxTextureCurrent + 1 # cambiar el numero de la textura actual
            self.objectForView.getMesh().getTexture(0).setTextureRef( self.boxTextures[ self.boxTextureCurrent % len( self.boxTextures ) ] ) # cambiar la textura del cubo por la texura actual

        # actualizar la orbita de la camara
        self.updateCamera()

    #orbita de la camara
    def updateCamera(self):
        axis_step = BVector2f(.0,.0)

        axis_step.x = self.inputContext.getAxis('MOUSE_X') - 0.5
        axis_step.y = self.inputContext.getAxis('MOUSE_Y') - 0.5

        self.Hangle = self.Hangle - axis_step.x
        self.Vangle = self.Vangle + axis_step.y


        Vlimit = PI/2.0
        if self.Vangle < -Vlimit:
            self.Vangle = -Vlimit
        elif self.Vangle > Vlimit:
            self.Vangle = Vlimit

        if fabs(self.Hangle) >= (2.0*PI):
            self.Hangle = .0

        newPos = BVector3f(.0, .0 ,.0)

        Hradius = self.radius - (1.0/3.0) * (self.radius * cos(self.Vangle))
        newPos.x = Hradius * cos(self.Hangle)
        newPos.y = Hradius * sin(self.Hangle)
        newPos.z = (self.radius * 1.5) * sin(self.Vangle)

        self.worldCamera.setPosition(newPos)
        self.worldCamera.lookAt(self.center)

        s_size = self.systemContext.getScreenSize()
        self.systemContext.setCursorPosition(s_size[0]/2, s_size[1]/2)


class MeshViewer2Example(BGame):
    def __init__(self):
        self.Hangle = .0 # acá se almacena el angulo horizontal de la camara
        self.Vangle = .0 # acá se almacena el angulo vertical de la camara
        self.radius = 25.0 # radio de la orbita de la camara, controla que tan lejos se visualiza el objeto
        self.center = BVector3f(.0, .0, .0) # La posición donde se mostrará el objeto

    def onBegin(self):
        self.engine = Bizarre()
        world = self.engine.getWorld()
        worldScene = world.getWorldScene()
        skyScene = world.getSkyScene()
        guiScene = world.getGuiScene()

        self.systemContext = BSystemContext()        
        self.inputContext = BInputContext()
        self.systemContext.hideCursor()

        renderInfo = self.engine.getRenderInfo()
        renderInfo.disableTextureFilter(True) # esta función desabilita el suavizado de texturas para que las texturas pequeñas puedan verse como pixel art
        renderInfo.disableTextureCompression(False) # habilitar la compresión de texturas
        #renderInfo.changeRenderer('StandardRenderer')

        assetsManager = self.engine.getAssetsManager()
        
        skyMeshRef = assetsManager.loadMesh( "meshs/campfire/sky.xml", ON_WORKING_DIR ) # leer el cielo usado en campfire
        objectForViewRef = assetsManager.loadMesh( "meshs/hexMap.mesh", ON_WORKING_DIR ) # se carga un cubo, a este cubo se le cambiará las texturas
        objectForViewRef2 = assetsManager.loadMesh( "meshs/hexMapPlants.mesh", ON_WORKING_DIR ) # se carga un cubo, a este cubo se le cambiará las texturas

        gradientRef   = assetsManager.loadTexture( "textures/gradient0.png", ON_WORKING_DIR ) # carga una textura que se usará como cielo

        skyObj = skyScene.addNewModel( skyMeshRef ) # agregar el cielo de campifire en la escena de cielo
        skyObj.getMesh().getTexture(0).setTextureRef(gradientRef) # cambiar la textura del cielo

        
        #light0 = worldScene.addNewLight()
        #light0.setPosition( BVector3f(5.24248, -2.43676, 3.69036) )
        #light0.setRadius( 30.0 )
        #light0.setIntensity( 1.0 )
        #print dir(light0)

        self.objectForView = worldScene.addNewModel( objectForViewRef ) # agregar el cubo en la escena de mundo
        self.objectForView2 = worldScene.addNewModel( objectForViewRef2 ) 
        #self.objectForView.getMesh().getTexture(0).setTextureRef( self.boxTextures[ self.boxTextureCurrent ] ) # cambiar la textura del cubo

        self.worldCamera = worldScene.getCurrentCamera()
        self.worldCamera.enableOrtho(True)
        self.worldCamera.setFov(15.0)
    

        self.worldCamera.lookAt( self.center ) # alinear la camara para que observe a un punto especifico

        #sprite0 = guiScene.addNewSprite( pixelTreesRef, 0.09 ) # agregar la pequeña textura pixel art de arboles
        #sprite0.setPosition( BVector3f( 0.1, 0.1, .0) ) # asignar posición a la textura anterior
        
        self.inputContext = self.engine.getInputContext()
        s_size = self.systemContext.getScreenSize()
        self.systemContext.setCursorPosition(s_size[0]/2, s_size[1]/2)


    def onUpdate(self):
        #ver la textura anterior
        if self.inputContext.onKeyDown('LEFT'):
            self.worldCamera.setFov( self.worldCamera.getFov() + 1 )

        #ver la textura siguiente
        if self.inputContext.onKeyDown('RIGHT'):
            self.worldCamera.setFov( self.worldCamera.getFov() - 1 )
        
        # actualizar la orbita de la camara
        self.updateCamera()

    #orbita de la camara
    def updateCamera(self):
        axis_step = BVector2f(.0,.0)

        axis_step.x = self.inputContext.getAxis('MOUSE_X') - 0.5
        axis_step.y = self.inputContext.getAxis('MOUSE_Y') - 0.5

        self.Hangle = self.Hangle - axis_step.x
        self.Vangle = self.Vangle + axis_step.y


        Vlimit = PI/2.0
        if self.Vangle < -Vlimit:
            self.Vangle = -Vlimit
        elif self.Vangle > Vlimit:
            self.Vangle = Vlimit

        if fabs(self.Hangle) >= (2.0*PI):
            self.Hangle = .0

        newPos = BVector3f(.0, .0 ,.0)

        Hradius = self.radius - (1.0/3.0) * (self.radius * cos(self.Vangle))
        newPos.x = Hradius * cos(self.Hangle)
        newPos.y = Hradius * sin(self.Hangle)
        newPos.z = (self.radius * 1.5) * sin(self.Vangle)

        self.worldCamera.setPosition(newPos)
        self.worldCamera.lookAt(self.center)

        s_size = self.systemContext.getScreenSize()
        self.systemContext.setCursorPosition(s_size[0]/2, s_size[1]/2)