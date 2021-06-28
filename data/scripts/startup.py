#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
    Al iniciar, el motor buscar un modulo llamado startup en la carpera raíz y en scripts/
    por lo tanto debe existir en alguno de los directorios, a su vez en dicho modulo es donde
    debe iniciarlizarse el resto del mismo mediante la API expuesta a Python

'''


# importando modulos y objetos del motor
'''
    El modulo mediante el cual un programa de Python se puede comunicar con el motor se llama 
    Bizarre, en este caso se importan los siguientes objectos:
    
    Bizarre  : una clase del mismo nombre del módulo, es la columna vertebral del motor, el nodo raíz
    BGame    : es una clase para heredar, la lógica de un programa deberá escribirse clase heredada (ver más adelante)
    BVector3f: vector de 3 componentes

    BInputContext : contexto de entrada, es una clase que permite obtener datos de entrada sobre el ratón, mouse y Joystick
    
    ON_WORKING_DIR  : constante, sirve para especificar al motor que busque un asset en la carpeta de trabajo
    ON_ABSOLUTE_DIR : constante, sirve para especificar al motor que la ruta de un assets es la ruta absoluta

    GUI_ALIGN_LEFT y otros: constantes, sirven para alinear texto de diferentes maneras
'''
from Bizarre import Bizarre, BGame, BVector3f, ON_WORKING_DIR, ON_ABSOLUTE_DIR
from Bizarre import BInputContext
from Bizarre import GUI_ALIGN_LEFT, GUI_ALIGN_UP, GUI_ALIGN_UP_OUTER, GUI_ALIGN_DOWN, GUI_ALIGN_DOWN_OUTER

# importando ejemplos de uso del motor
from Examples.Escenes import CampfireExample, MeshViewerExample, MeshViewer2Example
from Examples.Escenes2 import SpritesExample, compositedMeshExample
from Examples.Geometry import MeshHandling

'''
    Se construirá en menú simple para seleccionar el ejemplo que se quiere visualizar,
    para eso se hará una clase heredada de BGame y se sobreescribirán los siguientes métodos:

        onBegin : esta es la función de inicio, se ejecutará al principio y en ella se configura todo
        onUpdate : se ejecuta después de se renderiza cada fotograma, acá suele escribirse la lógica del juego

'''
class startMenu(BGame):
    def __init__(self):
        pass
    
    def onBegin(self):
        engine = Bizarre() # obtener la instancia en ejecución del motor
        world = engine.getWorld() # obtener el gestor de mundo (gestiona las escenas y otras cosas)
        worldScene = world.getWorldScene() # obtener la escena de mundo, acá se cargan los objetos principales del juego
        skyScene = world.getSkyScene() # está escena sirve para cargar en ella objetos que se verán fijos al fondo, como el cielo y las nubes
        guiScene = world.getGuiScene() # en esta escena se cargan objetos 2D, como sprites o el HUD
        self.inputContext = BInputContext() #obtener instancia del contexto de entrada y colocarlo como miembro de la clase

        skyCamera = skyScene.getCurrentCamera() # obtener la camara principal de la escena de cielos
        skyCamera.setClearColor( BVector3f( 0.7, 0.7, 0.8 ) ) # definir un color de fondo para dicha camara
        
        worldCamera = worldScene.getCurrentCamera()
        worldCamera.setPosition( BVector3f(7.48113, -6.50764, 5.34367) )
        worldCamera.setEulerRotation( BVector3f(63.5593, 0, 46.6919) )

        self.renderInfo = engine.getRenderInfo() # obtiene un objeto tipo BRenderInfo, el cual tiene información y funciones relacionadas al renderizado de pantalla

        self.renderInfo.disableTextureFilter(True)

        '''
            Para cargar un asset en una escena determinada, se requiere primero, cargar su referencia,
            como su nombre lo dice, es una referencia al archivo del asset y a su definición en memoria,
            cuando esta referencia se carga en una escena se crea un objeto asociado a la misma, varios
            objetos pueden copartir la misma referencia
        '''
        assetsManager = engine.getAssetsManager() # obtener instancia del gestor de assets
        assetsManager.loadPackage('test.npk') # cargar el paquete de archivos test.npk
        soundRef = assetsManager.loadSound('music/mr_doubt.xm', ON_WORKING_DIR) # cargar un archivo de sonido y obtener su referencia
        #soundRef2 = assetsManager.loadSound('music/laments-the-mortal-coil.wav', ON_WORKING_DIR)
        sound = worldScene.addNewSound(soundRef) # cargar el sonido en la escena de mundo
        sound.play() #reproducir el sonido
        sound.setLooping(True)
        #textureRef0 = assetsManager.loadTexture("textures/transparent-background.png", ON_WORKING_DIR) # cagar una imagen png y obtener su referencia
        textureRef0 = assetsManager.loadTexture("untitled.png") # esta imagen se encuenta en el paquete test.npk
        fontRef0 = assetsManager.loadFont("fonts/Roboto-Light.ttf", ON_WORKING_DIR) # cargar una fuente y obtener su referencia

        '''
            Un sprite es una imagen plana, puede cargarse tanto en una escena 3D o una 2D, si se
            carga en una escena 2D su tamaño y posición se gestionará con valores relativos de 0 a 1
            donde 1.0 es el tamaño total de la pantalla, existe por el momento un pequeño problema con
            el ratio de la resolución.

            Para facilitar la creación de HUDs, a los sprites se les puede agregar texto
        '''
        sprite0 = guiScene.addNewSprite( textureRef0, 0.8 ) # agregar la imagen png cargada anteriormente como sprite y con un tamaño del 80% del ancho de la pantalla
        sprite0.setPosition( BVector3f( 0.2, 0.1, .0) ) # posicionar al 20 de la anchura y 10% de la altura
        sprite0.addText(fontRef0, "Bizarre Starter Pack \n 1 - Campfire \n 2 - Object Viewer \n 3 - Geometry & Texture Manipulation" ) #Agrear un texto de multiples líneas usando el archivo de tipografías cargado anteriormente
        sprite0.setTextSize( 5.0 ) # cambiar el tamaño del text a 5
        sprite0.setTextHAlign(GUI_ALIGN_LEFT) #alinear el texto horizontalmente
        sprite0.setTextVAlign(GUI_ALIGN_UP) #alinear el texto verticalmente

    '''
        En la función update solo se hará una cosa, esperar a que el usuario seleccione un ejemplo a cargar
        para hacerlo, se utiliza la función setGame() de la clase Bizarre, esta recibe la instancia de una clase heredada de BGame
        la cual se iniciará y se destruirá la actual, no es estrictamente necesario que la clase herede de BGame, pero sí debe tener
        los mismos métodos de la misma.
    '''
    def onUpdate(self):
        if self.inputContext.onKeyDown('1'): # saber si se acaba de presionar la tecla 1 del teclado
            Bizarre().setGame( CampfireExample() ) # inciciar ejemplo

        if self.inputContext.onKeyDown('2'): # saber si se acaba de presionar la tecla 1 del teclado
            Bizarre().setGame( MeshViewerExample() ) # inciciar ejemplo

        if self.inputContext.onKeyDown('4'): # saber si se acaba de presionar la tecla 1 del teclado
            Bizarre().setGame( MeshViewer2Example() ) # inciciar ejemplo

        if self.inputContext.onKeyDown('0'): 
            Bizarre().setGame( compositedMeshExample() )

        if self.inputContext.onKeyDown('3'):
            Bizarre().setGame( MeshHandling() )
    
    '''
        Este método se ejecuta cuando al cambiar a otro BGame
    '''
    def onEnd(self):
        pass

engine = Bizarre() # obtener instancia activa del motor
'''
    La función start es la más imporante del en el modulo startup, esta es la que pone a trabajar todo el motor
    recibe una serie de parametros de configuración, muchos de los cuales son poco usados, pero al que se necesita
    asignar un valor necesariamente el parametro game, a este se le asigna una instancia de clase heredada de BGame 
    que será la que se ejecutará al arrancar todos los sistemas del motor, otros parametros importantes son los de 
    pantalla, como windows_width, window_height, etc.
'''
engine.start( window_title = 'Bizarre test', window_width = 1024, window_height = 768, window_fullscreen = False, game = startMenu() )