#pragma comment(lib,"glew32.lib")


#pragma comment(lib,"opengl32.lib")
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>

#include "Vector3.h"
#include "Mesh.h"
#include "VertexBufferObject.h"
#include "IndexBufferObject.h"

void Init(void);
void Shut_Down(int return_code);
void Main_Loop(void);
void Draw_Square(float red, float green, float blue);
void Draw(void);
void DrawMesh(void);
float rotate_y = 0,
      rotate_z = 0;
const float rotations_per_tick = .2;
 
VertexBufferObject* theVBO;
IndexBufferObject* theIBO;
	
GLuint vbo_cube;
GLuint ibo_cube_elements, vbo_cube_normals;
GLint attribute_coord3d;
GLuint program;

int main(void)
{
  Init();
  Main_Loop();
  Shut_Down(0);
}

void print_log(GLuint object)
{
  GLint log_length = 0;
  if (glIsShader(object))
    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else if (glIsProgram(object))
    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else {
    fprintf(stderr, "printlog: Not a shader or a program\n");
    return;
  }
 
  char* log = (char*)malloc(log_length);
 
  if (glIsShader(object))
    glGetShaderInfoLog(object, log_length, NULL, log);
  else if (glIsProgram(object))
    glGetProgramInfoLog(object, log_length, NULL, log);
 
  fprintf(stderr, "%s", log);
  int a;
  std::cin >> a;
  free(log);
}

char* file_read(const char* filename)
{
  FILE* in = fopen(filename, "rb");
  if (in == NULL) return NULL;
 
  int res_size = BUFSIZ;
  char* res = (char*)malloc(res_size);
  int nb_read_total = 0;
 
  while (!feof(in) && !ferror(in)) {
    if (nb_read_total + BUFSIZ > res_size) {
      if (res_size > 10*1024*1024) break;
      res_size = res_size * 2;
      res = (char*)realloc(res, res_size);
    }
    char* p_res = res + nb_read_total;
    nb_read_total += fread(p_res, 1, BUFSIZ, in);
  }
 
  fclose(in);
  res = (char*)realloc(res, nb_read_total + 1);
  res[nb_read_total] = '\0';
  return res;
}
GLuint create_shader(const char* filename, GLenum type)
{
  const GLchar* source = file_read(filename);
  if (source == NULL) {
    fprintf(stderr, "Error opening %s: ", filename); perror("");
    return 0;
  }
  GLuint res = glCreateShader(type);
  const GLchar* sources[2] = {
#ifdef GL_ES_VERSION_2_0
    "#version 100\n"
    "#define GLES2\n",
#else
    "#version 120\n",
#endif
    source };
  glShaderSource(res, 2, sources, NULL);
  free((void*)source);
 
  glCompileShader(res);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
  if (compile_ok == GL_FALSE) {
    fprintf(stderr, "%s:", filename);
    print_log(res);
    glDeleteShader(res);
    return 0;
  }
 
  return res;
}


void Init(void)
{
	const int window_width = 800,
			window_height = 600;
  

	if (glfwInit() != GL_TRUE)
	Shut_Down(1);
	// 800 x 600, 16 bit color, no depth, alpha or stencil buffers, windowed
	if (glfwOpenWindow(window_width, window_height, 5, 6, 5,
						0, 0, 0, GLFW_WINDOW) != GL_TRUE)
	Shut_Down(1);
	glfwSetWindowTitle("SteenGraph");
 
	// set the projection matrix to a normal frustum with a max depth of 50
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect_ratio = ((float)window_height) / window_width;
	glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 5000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
    return ;
  }
	//Mesh* theMesh = new Mesh();

	 GLfloat cube_vertices[] = {
   
	  
	   // front
    -1.0, -1.0,  1.0,
     1.0, -1.0,  1.0,
     1.0,  1.0,  1.0,
    -1.0,  1.0,  1.0,
	// top
	 -1.0, 1.0, 1.0,
	 1.0, 1.0, 1.0,
	 1.0, 1.0, -1.0,
	 -1.0, 1.0, -1.0,
    // back
    -1.0, -1.0, -1.0,
     1.0, -1.0, -1.0,
     1.0,  1.0, -1.0,
    -1.0,  1.0, -1.0,
	// bottom
	-1.0, -1.0, 1.0,
	1.0, -1.0, 1.0,
	1.0, -1.0, -1.0,
	-1.0, -1.0, -1.0,
	// left
	-1.0, -1.0, 1.0,
	-1.0, -1.0, -1.0,
	-1.0, 1.0, -1.0,
	-1.0, 1.0, 1.0,
	// right
	1.0, -1.0, 1.0,
	1.0, -1.0, -1.0,
	1.0, 1.0, -1.0,
	1.0, 1.0, 1.0,
  };

  
  GLushort cube_elements[] = {
   // front
	  0,1,2,3,
	  //top
	  4,5,6,7,
	  //back
	  8,11,10,9,
	  //bottom
	  12,15,14,13,
	  //left
	  19,18,17,16,
	  //right
	  20,21,22,23,
  };
  GLfloat cube_normals[] = {
	 // front
	 0.0, 0.0, 1.0,
	 0.0, 0.0, 1.0,
	 0.0, 0.0, 1.0,
	 0.0, 0.0, 1.0,
	 // top
	 0.0, 1.0, 0.0,
	 0.0, 1.0, 0.0,
	 0.0, 1.0, 0.0,
	 0.0, 1.0, 0.0,
	 // back
	 0.0, 0.0,-1.0,
	 0.0, 0.0,-1.0,
	 0.0, 0.0,-1.0,
	 0.0, 0.0,-1.0,
	 // bottom
	 0.0,-1.0, 0.0,
	 0.0,-1.0, 0.0,
	 0.0,-1.0, 0.0,
	 0.0,-1.0, 0.0,
	 // left
	-1.0, 0.0, 0.0,
	-1.0, 0.0, 0.0,
	-1.0, 0.0, 0.0,
	-1.0, 0.0, 0.0,
	// right
	 1.0, 0.0, 0.0,
	 1.0, 0.0, 0.0,
	 1.0, 0.0, 0.0,
	 1.0, 0.0, 0.0,

  };

	theVBO = new VertexBufferObject(cube_vertices,sizeof(cube_vertices));
	theIBO = new IndexBufferObject(cube_elements,sizeof(cube_elements));
	

	GLint link_ok = GL_FALSE;

  GLuint vs, fs;
  if ((vs = create_shader("triangle.v.glsl", GL_VERTEX_SHADER))   == 0) return;
  if ((fs = create_shader("triangle.f.glsl", GL_FRAGMENT_SHADER)) == 0) return;

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    fprintf(stderr, "glLinkProgram:");
    print_log(program);
    return;
  }

  char* attribute_name = "coord3d";
  attribute_coord3d= glGetAttribLocation(program, attribute_name);
  if (attribute_coord3d == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return;
  }
  
 glUseProgram(program);

}
 
void Shut_Down(int return_code)
{
  glfwTerminate();
  exit(return_code);
}
 
void Main_Loop(void)
{
  // the time of the previous frame
  double old_time = glfwGetTime();
  // this just loops as long as the program runs
  while(1)
  {
    // calculate time elapsed, and the amount by which stuff rotates
    double current_time = glfwGetTime(),
           delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
    old_time = current_time;
    // escape to quit, arrow keys to rotate view
    if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
      break;
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
      rotate_y += delta_rotate;
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
      rotate_y -= delta_rotate;
    // z axis always rotates
    rotate_z += delta_rotate;
 
    // clear the buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // draw the figure
    Draw();
	DrawMesh();
	// reset view matrix
	glLoadIdentity();
	// move view back a bit
	glTranslatef(0, 4, -30);
	
    // swap back and front buffers
    glfwSwapBuffers();
  }
}

void DrawMesh(void)
{
	glUseProgram(program);

	glEnableVertexAttribArray(attribute_coord3d);
	/* Describe our vertices array to OpenGL (it can't guess its format automatically) */
	glBindBuffer(GL_ARRAY_BUFFER, theVBO->GetAdress());
	//glBindBuffer(GL_ARRAY_BUFFER, vbo_cube);
	glVertexAttribPointer(
	attribute_coord3d, // attribute
	3,                 // number of elements per vertex, here (x,y)
	GL_FLOAT,          // the type of each element
	GL_FALSE,          // take our values as-is
	0,                 // no extra data between each position
	0                  // offset of first element
	);

  
	/* Push each element in buffer_vertices to the vertex shader */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIBO->GetAdress());
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_QUADS, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glDisableVertexAttribArray(attribute_coord3d);

}
 
void Draw_Square(float red, float green, float blue)
{
  // Draws a square with a gradient color at coordinates 0, 10
  glBegin(GL_QUADS);
  {
    glColor3f(red, green, blue);
    glVertex2i(1, 11);
    glColor3f(red * .8, green * .8, blue * .8);
    glVertex2i(-1, 11);
    glColor3f(red * .5, green * .5, blue * .5);
    glVertex2i(-1, 9);
    glColor3f(red * .8, green * .8, blue * .8);
    glVertex2i(1, 9);
  }
  glEnd();
}
 
void Draw(void)
{
  // reset view matrix
  glLoadIdentity();
  // move view back a bit
  glTranslatef(0, 0, -30);
  // apply the current rotation
  glRotatef(rotate_y, 0, 1, 0);
  glRotatef(rotate_z, 0, 0, 1);
  // by repeatedly rotating the view matrix during drawing, the
  // squares end up in a circle
  int i = 0, squares = 15;
  float red = 0, blue = 1;
  for (; i < squares; ++i){
    glRotatef(360.0/squares, 0, 0, 1);
    // colors change for each square
    red += 1.0/12;
    blue -= 1.0/12;
    Draw_Square(red, .6, blue);
  }
}
