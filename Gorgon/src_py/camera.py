from PyQt4 import QtOpenGL, QtCore
from vector_lib import *

try:
    from OpenGL.GL import *
    from OpenGL.GLU import *
    from OpenGL.GLUT import *
except ImportError:
    app = QtGui.QApplication(sys.argv)
    QtGui.QMessageBox.critical(None, "OpenGL grabber", "PyOpenGL must be installed to run Gorgon.", QtGui.QMessageBox.Ok | QtGui.QMessageBox.Default, QtGui.QMessageBox.NoButton)
    sys.exit(1)
    
class Camera(QtOpenGL.QGLWidget):
    def __init__(self, scene, parent=None):        
        
        QtOpenGL.QGLWidget.__init__(self, parent)

        #print("Depth Buffer:", self.format().depthBufferSize(), 
        #      " Red: ", self.format().redBufferSize(), 
        #      " Green: ", self.format().greenBufferSize(), 
       #       " Blue: ", self.format().blueBufferSize(), 
       #       " Alpha:", self.format().alphaBufferSize())

        
        self.aspectRatio = 1.0;        
        self.near = 10;
        self.far = 500;
        self.setEyeZoom(0.25)

        self.scene = scene
        
        self.setCenter(0, 0, 0)
        self.setEye(0, -4, 0) 
        self.setUp(0, 0, 1)     
        self.setEyeRotation(0, 0, 0)

        self.lastPos = QtCore.QPoint()
        
        for s in self.scene:
            self.connect(s, QtCore.SIGNAL("viewerSetCenter(float, float, float, float, float, float)"), self.sceneSetCenter)
            self.connect(s, QtCore.SIGNAL("modelChanged()"), self.updateGL)
            self.connect(s, QtCore.SIGNAL("modelLoaded()"), self.updateGL)
            self.connect(s, QtCore.SIGNAL("modelUnloaded()"), self.updateGL)
            self.connect(s, QtCore.SIGNAL("modelVisualizationChanged()"), self.updateGL)
 
    def setEye(self, x, y, z):
        self.eye = [x, y, z]
        try:
            self.look = vectorNormalize([self.center[0] - self.eye[0], self.center[1] - self.eye[1], self.center[2] - self.eye[2]])
            self.right = vectorNormalize(vectorCrossProduct(self.look, self.up))            #print("Eye: right :", self.right)        
        except:
            self.look = [0,1,0]
            self.right = [-1,0,0]
    
    def setCenter(self, x, y, z):
        self.center = [x, y, z]
        try:
            self.look = vectorNormalize([self.center[0] - self.eye[0], self.center[1] - self.eye[1], self.center[2] - self.eye[2]])
            self.right = vectorNormalize(vectorCrossProduct(self.look, self.up))
        except:
            self.look = [0,1,0]
            self.right = [-1,0,0]
        
    def setUp(self, x, y, z):
        self.up = vectorNormalize([x, y, z])
        try:
            self.right = vectorNormalize(vectorCrossProduct(self.look, self.up))
            self.up = vectorNormalize(vectorCrossProduct(self.look, self.right))
        except:
            self.right = [-1,0,0]
        
    def setEyeRotation(self, yaw, pitch, roll):
        self.eyeRotation = [yaw, pitch, roll]
    
    def setEyeZoom(self, value):
        self.eyeZoom = min(max(value, 0.0001), 0.9999);
        self.setGlProjection()
        
    def setNearFar(self, near, far):
        self.near = near
        self.far = far
        self.setGlProjection()
    
    def sceneSetCenter(self, minX, minY, minZ, maxX, maxY, maxZ):        
        self.setCenter((minX+maxX)/2.0, (minY+maxY)/2.0, (minZ+maxZ)/2.0)
        self.setEye(self.center[0] , self.center[1], self.center[2] - 2*(maxZ-minZ))        
        self.setUp(0, -1, 0)
        #radius = vectorDistance([minX, minY, minZ], [maxX, maxY, maxZ]) / 2.0;
        #eyeDistance = vectorDistance(self.center, self.eye)
        #self.setNearFar(max(eyeDistance-radius, 0.1), eyeDistance + 2*radius)
        
        self.setGluLookAt()                
        self.initializeSceneMatrix()      
        self.updateGL()

    
    def initializeSceneMatrix(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()        
        self.sceneMatrix = glGetFloatv( GL_MODELVIEW_MATRIX )
    
    def minimumSizeHint(self):
        return QtCore.QSize(50, 50)

    def sizeHint(self):
        return QtCore.QSize(400, 400)     
       
    def initializeGL(self):
        afPropertiesAmbient = [0.50, 0.50, 0.50, 1.00] 
        afPropertiesDiffuse = [0.75, 0.75, 0.75, 1.00] 
        afPropertiesSpecular = [0.0, 0.0, 0.0, 1.00]
        glClearColor( 0.0, 0.0, 0.0, 1.0 )
        glClearDepth( 5.0 )
        
        afLightPosition = [1000,1000,1000]
        
        glLightfv( GL_LIGHT0, GL_AMBIENT,  afPropertiesAmbient);
        glLightfv( GL_LIGHT0, GL_DIFFUSE,  afPropertiesDiffuse) 
        glLightfv( GL_LIGHT0, GL_SPECULAR, afPropertiesSpecular) 
        glLightfv( GL_LIGHT0, GL_POSITION, afLightPosition)

        glEnable( GL_LIGHT0 ) 


        afLightPosition = [-1000,-1000,-1000]        
        glLightfv( GL_LIGHT1, GL_AMBIENT,  afPropertiesAmbient);
        glLightfv( GL_LIGHT1, GL_DIFFUSE,  afPropertiesDiffuse) 
        glLightfv( GL_LIGHT1, GL_SPECULAR, afPropertiesSpecular) 
        glLightfv( GL_LIGHT1, GL_POSITION, afLightPosition)

        glEnable( GL_LIGHT1 ) 

        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        self.sceneMatrix = glGetFloatv( GL_MODELVIEW_MATRIX )
        
              
    def setGluLookAt(self):
        gluLookAt(self.eye[0], self.eye[1], self.eye[2], 
                  self.center[0], self.center[1], self.center[2], 
                  self.up[0], self.up[1], self.up[2])
        
    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        
        glPushMatrix()
        glTranslatef(self.center[0], self.center[1], self.center[2])
        glRotatef(self.eyeRotation[0], self.up[0], self.up[1], self.up[2])
        glRotatef(self.eyeRotation[1], self.right[0], self.right[1], self.right[2])       
        glRotatef(self.eyeRotation[2], self.look[0], self.look[1], self.look[2])
        glTranslated(-self.center[0], -self.center[1], -self.center[2])      
        glMultMatrixf(self.sceneMatrix)
        self.sceneMatrix = glGetFloatv( GL_MODELVIEW_MATRIX )
        glPopMatrix()
        
        self.setEyeRotation(0, 0, 0)
        self.drawScene()

               
    def drawScene(self):
        
        self.setGluLookAt()
        
        glPushMatrix()                
        glMultMatrixf(self.sceneMatrix)            
        glPushName(0)
        for s in self.scene:         
            s.draw()
           
        glPopName()
        glPopMatrix()
    
       
#    def pickObject(self, x, y):
#        SIZE = 100
#        viewport = list(glGetIntegerv(GL_VIEWPORT))
#
#        glSelectBuffer(SIZE)
#        glRenderMode(GL_SELECT)
#
#        glInitNames()
#
#        glMatrixMode(GL_PROJECTION)
#        glPushMatrix()
#        glLoadIdentity()
#        gluPickMatrix(x, viewport[3]-y, 10, 10, viewport)
#        gluPerspective(45, self.ratio, 0.1, 1000)
#
#        self.drawScene(False)
#        
#        glMatrixMode(GL_PROJECTION)
#        glPopMatrix()
#        glFlush()
#
#        bufferStack = glRenderMode(GL_RENDER)
#        for hit_record in bufferStack:
#            min_depth, max_depth, names = hit_record
#            namelist = list(names)
#            for n in namelist:
#                print n
#            print min_depth, max_depth, names 
        
    def resizeGL(self, width, height):
        self.aspectRatio = width/(1.0*height)
        glViewport(0,0, width, height)
        self.setGlProjection()
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

    def setGlProjection(self):
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(180 * self.eyeZoom, self.aspectRatio, self.near, self.far)
        
    def mousePressEvent(self, event):
        self.lastPos = QtCore.QPoint(event.pos())
        
        #self.pickObject(event.x(), event.y())

    def mouseMoveEvent(self, event):
        dx = event.x() - self.lastPos.x()
        dy = event.y() - self.lastPos.y()

        if event.buttons() & QtCore.Qt.LeftButton:
            self.setEyeRotation(dx, -dy, 0)
        elif event.buttons() & QtCore.Qt.RightButton:
            self.setEyeRotation(0, 0, dx)
        
        self.lastPos = QtCore.QPoint(event.pos())

        self.updateGL()
    
    def wheelEvent(self, event):
        direction = event.delta()/abs(event.delta())
        self.setEyeZoom(self.eyeZoom + direction * 10.0/360.0)
        self.updateGL()                          