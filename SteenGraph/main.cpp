#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"opengl32.lib")

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>

#include "Vector3.h"
#include "RenderObject.hpp"
#include "Shader.hpp"

void Init(void);
void Shut_Down(int return_code);
void Main_Loop(void);
void Draw_Square(float red, float green, float blue);
void Draw(void);
void DrawMesh(RenderObject& r);

float rotate_y = 0,
      rotate_z = 0;
const float rotations_per_tick = .2;
 
VertexBufferObject* theVBO;
IndexBufferObject* theIBO;

VertexBufferObject* theVBO2;
IndexBufferObject* theIBO2;

Shader* theShader;

RenderObject* renderObject, *renderObject2;

GLuint vbo_cube_normals;
GLint attribute_coord3d;
GLuint program;

int main(void)
{
  Init();
  Main_Loop();
  Shut_Down(0);
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
	
	theVBO2 = new VertexBufferObject(cube_vertices,sizeof(cube_vertices));
	theIBO2 = new IndexBufferObject(cube_elements,sizeof(cube_elements));

	theShader = new Shader("triangle.v.glsl", "triangle.f.glsl");

	renderObject = new RenderObject(*theVBO, *theIBO2, *theShader);
	renderObject2 = new RenderObject(*theVBO2, *theIBO2, *theShader);

	program = *theShader->GetProgram();
	char* attribute_name = "coord3d";
	attribute_coord3d = glGetAttribLocation(program, attribute_name);
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
	
	// reset view matrix
	glLoadIdentity();
	// move view back a bit
	
    // swap back and front buffers
    glfwSwapBuffers();
  }
}

void DrawMesh(RenderObject& r)
{
	glUseProgram(program);
	
	glEnableVertexAttribArray(attribute_coord3d);
	/* Describe our vertices array to OpenGL (it can't guess its format automatically) */
	glBindBuffer(GL_ARRAY_BUFFER, r.GetVBO()->GetAdress());
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r.GetIBO()->GetAdress());
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_QUADS, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glDisableVertexAttribArray(attribute_coord3d);

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
	DrawMesh(*renderObject);
	
	glTranslatef(0, 4, 5);
	DrawMesh(*renderObject2);
}
