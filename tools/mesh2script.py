try:
    import xmltodict
except ImportError:
    raise Exception('xmltodict not installed')

class maratisMesh:
    __vertices= []
    __uvs     = []
    #__triangles=[]
    __indices  =[]
    def __init__(self, file=None):
        if not file:
            raise Exception('You must define an input file')

        #try:
        meshFile = open( file, 'r' )
        rawMeshText = meshFile.read()
        rawMesh = xmltodict.parse(rawMeshText)

        rawVertices = rawMesh['Maratis']['Mesh']['SubMeshs']['SubMesh']['Vertices']['vertex']
        rawUvs = rawMesh['Maratis']['Mesh']['SubMeshs']['SubMesh']['TexCoords']['texCoord']	
        rawIndices = rawMesh['Maratis']['Mesh']['SubMeshs']['SubMesh']['Indices']['index']

        for vertex in rawVertices		:
            self.__vertices.append( [ float(vertex['@x']), float(vertex['@y']), float(vertex['@z']) ] )

        for uv in rawUvs:
            self.__uvs.append( [ float(uv['@x']), float(uv['@y']) ] )

        for indice in rawIndices:
            self.__indices.append( int(indice['@value']) )

        meshFile.close()
        del(rawMesh)
        del(rawMeshText)

        #for i in range( len(rawIndices) / 3 ):
        #    self.__triangles.append( [  int(rawIndices[ i*3 ]['@value']), int(rawIndices[ i*3 +1 ]['@value']), int(rawIndices[ i*3 +2 ]['@value']) ] )
        
        #except:
        #  raise Exception( file + ' is not a valid maratis file')

    def __verticesGetter(self):
        return self.__vertices

    def __uvsGetter(self):
        return self.__uvs

    #def __trianglesGetter(self):
    #    return self.__triangles

    def __indicesGetter(self):
        return self.__indices

    vertices = property(__verticesGetter)
    uvs = property(__uvsGetter)
    #triangles = property(__triangles)
    indices = property(__indicesGetter)

'''

meshFile = open( 'pyramid.mesh', 'r' )
rawMesh = meshFile.read()
mesh = xmltodict.parse(rawMesh)

vertices = mesh['Maratis']['Mesh']['SubMeshs']['SubMesh']['Vertices']['vertex']

for v in vertices:
    print str(v['@x'])

'''

mesh = maratisMesh('cube.mesh')
print 'Indices Number:' + str( len(mesh.indices) )

#print mesh.indices


f = open('model.py', 'w')

verticesText = 'vertices=['
for vertex in mesh.vertices:
    if verticesText[-1] != '[':
        verticesText = verticesText + ','
	
    verticesText = verticesText + 'BVector3f('+str(vertex[0])+','+str(vertex[1])+','+str(vertex[2])+')'
verticesText = verticesText +  ']'


UVsText = 'texCoords=['
for UV in mesh.uvs:
    if UVsText[-1] != '[':
        UVsText = UVsText + ','
    
    UVsText = UVsText + 'BVector2f('+str(UV[0])+','+str(UV[1])+')'
UVsText = UVsText +  ']'


indicesText = 'indices=['
for index in mesh.indices:
    if indicesText[-1] != '[':
        indicesText = indicesText + ','
    
    indicesText = indicesText + str(index)
indicesText = indicesText +  ']'

#for indice in mesh.indices:
#   vertex = mesh.vertices[ indice ]
#    uv = mesh.uvs[ indice ]

    #uv[0] = uv[0] * 2
    #uv[1] = uv[1] * 2

#    f.write(  '{' + str( uv[0] ).rjust(10) + ',' + str( uv[1] ).rjust(10) + ', 0xff000000,' + str(vertex[0]).rjust(10) + ',' + str(vertex[1]).rjust(10) + ',' + str(vertex[2]).rjust(10) + '},\n'  )

f.write( 'from Bizarre import BVector2f,BVector3f' + '\n' + verticesText + '\n' + UVsText + '\n' + indicesText + '\n' )

f.close()
#print mesh.vertices

#out_ = open( 'pyramid.json', 'w' )
#out_.write( json.dumps(o) )
