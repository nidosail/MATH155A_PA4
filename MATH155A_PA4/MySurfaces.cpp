//
//  MySurfaces.cpp
//
//   Sets up and renders 
//     - the ground plane, and
//     - the surface of rotation
//   for the Math 155A project #4.
//
//   Comes supplied with the code for Sam Buss's "X".
//


// Use the static library (so glew32.dll is not needed):
#define GLEW_STATIC
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "LinearR3.h"		// Adjust path as needed.
#include "LinearR4.h"		// Adjust path as needed.
#include "MathMisc.h"       // Adjust path as needed

#include "MySurfaces.h"
#include "SurfaceProj.h"


// ************************
// General data helping with setting up VAO (Vertex Array Objects)
//    and Vertex Buffer Objects.
// ***********************
const int NumObjects = 2;
const int iFloor = 0;
const int iCircularSurf = 1;

unsigned int myVBO[NumObjects];  // a Vertex Buffer Object holds an array of data
unsigned int myVAO[NumObjects];  // a Vertex Array Object - holds info about an array of vertex data;
unsigned int myEBO[NumObjects];  // a Element Array Buffer Object - holds an array of elements (vertex indices)

// **********************
// This sets up geometries needed for the "Initial" (the 3-D alphabet letter)
//  It is called only once.
// **********************
void MySetupSurfaces() {
    // Initialize the VAO's, VBO's and EBO's for the ground plane,
    // and the surface of rotation. Give them the "aPos" location,
    // and the "aNormal" location in the shader program.
    // No data is loaded into the VBO's or EBO's until the "Remesh"
    //   routines are called.

    // For the floor:
    // Allocate the needed Vertex Array Objects (VAO's),
    //      Vertex Buffer Objects (VBO's) and Element Array Buffer Objects (EBO's)
    // Since the floor has normal (0,1,0) everywhere, it will be given as
    // generic vertex attribute, not loaded in the VBO as a per-vertex value.
    // The color is also a generic vertex attribute.
    glGenVertexArrays(NumObjects, &myVAO[0]);
    glGenBuffers(NumObjects, &myVBO[0]);
    glGenBuffers(NumObjects, &myEBO[0]);

    glBindVertexArray(myVAO[iFloor]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFloor]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iFloor]);

    glVertexAttribPointer(vPos_loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Store vertices in the VBO
    glEnableVertexAttribArray(vPos_loc);									// Enable the stored vertices
    
    // For the circular surface:
    // Allocate the needed VAO, VBO< EBO
    // The normal vectors is specified separately for each vertex. (It is not a generic attribute.)
    // The color is still a generic vertex attribute.
    glBindVertexArray(myVAO[iCircularSurf]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iCircularSurf]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iCircularSurf]);

    glVertexAttribPointer(vPos_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Store vertices in the VBO
    glEnableVertexAttribArray(vPos_loc);									// Enable the stored vertices
    glVertexAttribPointer(vNormal_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Store normals in the VBO
    glEnableVertexAttribArray(vNormal_loc);                                 // Enabled the stored normals (so they are not generic)

    // No data has been loaded into the VBO's yet.
    // This is done next by the "Remesh" routines.

    MyRemeshSurfaces();
    
    check_for_opengl_errors();      // Watch the console window for error messages!
}

// **********************************************
// MODIFY THIS ROUTINE TO CALL YOUR OWN CODE IN
//   MyRemeshFloor AND MyRemeshCircularSurf
// INSTEAD OF THE "DEMO" VERSIONS.
// **********************************************

void MyRemeshSurfaces() 
{
    // WRITE MyRemeshFloor (see below) AND USE IT INSTEAD OF RemeshPlaneDemo
     RemeshFloorDemo();
    //MyRemeshFloor();

    // WRITE MyRemeshCircularSurf (see below) AND USE IT INSTEAD OF RemeshCircularDemo
    // RemeshCircularDemo();
    // MyRemeshCircularSurf();

    check_for_opengl_errors();      // Watch the console window for error messages!
}

// **********************************************
// MODIFY THIS ROUTINE TO CALL YOUR OWN CODE IN
//   MyRemeshFloor AND MyRemeshCircularSurf
// INSTEAD OF THE "DEMO" VERSIONS.
// **********************************************

void MyRenderSurfaces() {
    // WRITE MyRemeshFloor (see below) AND USE IT INSTEAD OF RemeshPlaneDemo
    // RenderFloorDemo();
    MyRenderFloor();

    // WRITE MyRemeshCircularSurf (see below) AND USE IT INSTEAD OF RemeshCircularDemo
    // RenderCircularDemo();
    // MyRenderCircularSurf();

    check_for_opengl_errors();      // Watch the console window for error messages!
}

// *********************************************
// THE CODE FOR THE NEXT FOUR "Demo" ROUIINTES BELOW GIVES SIMPLE FIXED SIZE OBJECTS:
// A plane gridded into 4x4 array of rectangles (triangulated)
// and Circular piece with 4 slices, and 4 rings.
// THIS CODE WILL NOT BE USED IN YOUR PROGRAMMING SOLUTION.
// INSTEAD, FINISH WRITING MyRemeshFloor() and MyRemeshCircularSurf() below.
// *********************************************************

// Make the floor a 4x4 grid of triangulated quads.
// Render it as four triangle strips.
void RemeshFloorDemo()
{
    // Floor vertices.
    ///*
    float floorVerts[][3] = {
        {-5.0f, 0.0f, -5.0f },  {-2.5f, 0.0f, -5.0f }, { 0.0f, 0.0f, -5.0f }, { 2.5f, 0.0f, -5.0f }, { 5.0f, 0.0f, -5.0f },  // Back row
        { -5.0f, 0.0f, -2.5f }, { -2.5f, 0.0f, -2.5f }, { 0.0f, 0.0f, -2.5f }, { 2.5f, 0.0f, -2.5f }, { 5.0f, 0.0f, -2.5f },  // Fourth row
        { -5.0f, 0.0f,  0.0f }, { -2.5f, 0.0f,  0.0f }, { 0.0f, 0.0f,  0.0f }, { 2.5f, 0.0f,  0.0f }, { 5.0f, 0.0f,  0.0f },  // Third row
        { -5.0f, 0.0f,  2.5f }, { -2.5f, 0.0f,  2.5f }, { 0.0f, 0.0f,  2.5f }, { 2.5f, 0.0f,  2.5f }, { 5.0f, 0.0f,  2.5f },  // Second row
        { -5.0f, 0.0f,  5.0f }, { -2.5f, 0.0f,  5.0f }, { 0.0f, 0.0f,  5.0f }, { 2.5f, 0.0f,  5.0f }, { 5.0f, 0.0f,  5.0f },  // Front row
    };
    printf("size of floorVerts: %3d \n", sizeof(floorVerts));
    //*/
    
    
    ///*
    //  --------- area for testing your code -----------
    
    int stripLen = (meshRes + 1) * 2; // array length of a triangle strip
    int numFloorVerts = (meshRes + 1)*(meshRes + 1);
    
    //float* floorVerts = new float[3 * numFloorVerts];
    
    // Floor elements (indices to vertices in a triangle strip)
    int numFloorElts = meshRes * 2 * (meshRes + 1);
    //unsigned int* floorElements = new unsigned int[numFloorElts];
    
    /*
    // YOU CAN NOW ACCESS floorVerts AND floorElements WITH THE SAME
    // SYNTAX AS ARRAYS.  FOR EXAMPLE,
    // floorVerts[0], floorVerts[1], floorVerts[2] ARE THE x,y,z
    // COMPONENTS OF THE FIRST VERTEX.
    
    // CALCULATE THE CONTENTS OF THE TWO ARRAYS.
    // THEN LOAD THE DATA INTO THE VBO AND EBO BUFFERS.
    
    // Calculate all vertex values
    
    for (int l = 0; l < meshRes + 1; l++) { // indices along z
        for (int m = 0; m < meshRes + 1; m++) { // indices along x dimension
            float xcoord = (((float)m / (float)meshRes) * 10.0) - 5.0; // define x coordinate as a float
            float zcoord = (((float)l / (float)meshRes) * 10.0) - 5.0; // define y coordinate as a float
            int index = 3 * (((meshRes + 1) * l) + m);
            printf("the index: %d \n", index);
            floorVerts[index] = xcoord;
            floorVerts[index + 1] = 0.0f; // y remains constant throughout
            floorVerts[index + 2] = zcoord;
        }
    }
    for (int i = 0; i < 75; i++) {
        printf("%f \n", floorVerts[i]);
    }
    //  -------- ^^area for testing your code^^ ---------
     */
    
    
    unsigned int* floorElements = new unsigned int[numFloorElts];
    // create floor element array
    for (int i = 0; i < (meshRes + 1) * (meshRes); i++) {
        floorElements[i * 2] = i;
        floorElements[i * 2 + 1] = i + (meshRes + 1);
        //cout << floorElements;
    }
    for (int k = 0; k < numFloorElts; k++) {
        printf("%d, ", floorElements[k]);
    }
    printf("\n");
    

    /*
    // Floor elements (indices to vertices in a triangle strip)
    unsigned int floorElements[] = {
        0,5,1,6,2,7,3,8,4,9,            // Elements for first triangle strip (back strip)
        5,10,6,11,7,12,8,13,9,14,       // Elements for second triangle strip
        10,15,11,16,12,17,13,18,14,19,  // Elements for third triangle strip
        15,20,16,21,17,22,18,23,19,24,  // Elements for fourth triangle strip (front strip)
    };
    */
    
    
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFloor]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVerts) * sizeof(float), floorVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iFloor]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*floorElements) * sizeof(unsigned int), floorElements, GL_STATIC_DRAW);
}

void RemeshCircularDemo()
{
    // Circular surface as four triangle strips (low resolution)
    // Both vertex positions AND normal vectors
    // Note how this corresponds to the call to glVertexAttribPointer and glEnableVertexAttribArray
    //      in MySetupSurfaces() above.
    float circularVerts[] = {
        // Vertex positions     Normals (please make them *unit* vectors)
        0.0f, 1.0f, 0.0f,       0.0f, 1.0f, 0.0f,        // Central vertex
        0.0f, 0.866f, 0.5f,     0.0f, 0.866f, 0.5f,     // Over positive z axis
        0.0f, 0.5f, 0.866f,     0.0f, 0.5f, 0.866f,     
        0.5f, 0.866f, 0.0f,     0.5f, 0.866f, 0.0f,     // Over positive x-axis
        0.866f, 0.5f, 0.0f,     0.866f, 0.5f, 0.0f,
        0.0f, 0.866f, -0.5f,    0.0f, 0.866f, -0.5f,    // Over negative z axis
        0.0f, 0.5f, -0.866f,    0.0f, 0.5f, -0.866f,
        -0.5f, 0.866f, 0.0f,    -0.5f, 0.866f, 0.0f,    // Over negative x-axis
        -0.866f, 0.5f, 0.0f,    -0.866f, 0.5f, 0.0f,
    };
    // Circular elements (indices to vertices in triangle strips)
    unsigned int circularElements[] = {
        0, 1, 3, 2, 4,            // Elements for first triangle strip 
        0, 3, 5, 4, 6,            // Elements for second triangle strip
        0, 5, 7, 6, 8,            // Elements for third triangle strip
        0, 7, 1, 8, 2            // Elements for fourth triangle strip 
    };
    glBindVertexArray(myVAO[iCircularSurf]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iCircularSurf]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circularVerts) * sizeof(float), circularVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iCircularSurf]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(circularElements) * sizeof(unsigned int), circularElements, GL_STATIC_DRAW);
}

void RenderFloorDemo()
{
    glBindVertexArray(myVAO[iFloor]);

    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    glVertexAttrib3f(vNormal_loc, 0.0, 1.0, 0.0);    // Generic vertex attribute: Normal is (0,1,0) for the floor.
    glVertexAttrib3f(vColor_loc, 1.0f, 0.4f, 0.4f);	 // Generic vertex attribute: Color (light red) for the floor. 
    viewMatrix.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

    // Draw the four triangle strips
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)0);                              // Draw first triangle strip (back strip)
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));    // Draw second triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(20 * sizeof(unsigned int)));    // Draw third triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));    // Draw fourth triangle strip (front strip)
}

void RenderFloorDemo1()
{
    glBindVertexArray(myVAO[iFloor]);
    
    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    glVertexAttrib3f(vNormal_loc, 0.0, 1.0, 0.0);    // Generic vertex attribute: Normal is (0,1,0) for the floor.
    glVertexAttrib3f(vColor_loc, 1.0f, 0.4f, 0.4f);     // Generic vertex attribute: Color (light red) for the floor.
    viewMatrix.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    
    // Draw the four triangle strips
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)0);                              // Draw first triangle strip (back strip)
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));    // Draw second triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(20 * sizeof(unsigned int)));    // Draw third triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));    // Draw fourth triangle strip (front strip)
}

void RenderCircularDemo()
{
    glBindVertexArray(myVAO[iCircularSurf]);

    // Calculute the model view matrix for the circular surface
    LinearMapR4 matDemo = viewMatrix;
    matDemo.Mult_glTranslate(2.5, 1.0, 2.5);     // Center in the front right quadrant & raise up
    matDemo.Mult_glScale(3.0, 1.0, 3.0);         // Increase the circular diameter

    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    glVertexAttrib3f(vColor_loc, 1.0f, 0.8f, 0.4f);	 // Generic vertex attribute: Color (yellow-ish) for the circular surface. 
    matDemo.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

    // Draw the four triangle strips
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)0);                             // Draw first triangle strip 
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(5 * sizeof(unsigned int)));    // Draw second triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));   // Draw third triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(15 * sizeof(unsigned int)));   // Draw fourth triangle strip 

}


// *********************************************
// THE CODE BELOW MUST BE WRITTEN FOR PROJECT 4.
// *********************************************

void MyRemeshFloor()
{
    // Sample code for allocating arrays of floats and unsigned int's with new[] and delete[]
	// The code fragment for allocating/deleting arrays uses C++ new and delete[].
	// You may optionally instead use the Standard Template Library std::vector<float> if you wish.
    // Floor vertices.
    int stripLen = (meshRes + 1) * 2; // array length of a triangle strip
    
    int numFloorVerts = (meshRes + 1)*(meshRes + 1); // number of floor vertices needed
    
    float* floorVerts = new float[3 * numFloorVerts];
    // Floor elements (indices to vertices in a triangle strip)
    int numFloorElts = meshRes * 2 * (meshRes + 1);
    unsigned int* floorElements = new unsigned int[numFloorElts];
    // YOU CAN NOW ACCESS floorVerts AND floorElements WITH THE SAME
    // SYNTAX AS ARRAYS.  FOR EXAMPLE,
    // floorVerts[0], floorVerts[1], floorVerts[2] ARE THE x,y,z
    // COMPONENTS OF THE FIRST VERTEX.

    // CALCULATE THE CONTENTS OF THE TWO ARRAYS.
    // THEN LOAD THE DATA INTO THE VBO AND EBO BUFFERS.
    
    // Calculate all vertex values
    for (int l = 0; l < meshRes + 1; l++) { // indices along z
        for (int m = 0; m < meshRes + 1; m++) { // indices along x dimension
            float xcoord = (((float)m / (float)meshRes) * 10.0) - 5.0; // define x coordinate as a float
            float zcoord = (((float)l / (float)meshRes) * 10.0) - 5.0; // define y coordinate as a float
            int index = 3 * (((meshRes + 1) * l) + m);
            floorVerts[index] = xcoord;
            floorVerts[index + 1] = 0.0f; // y remains constant throughout
            floorVerts[index + 2] = zcoord;
        }
    }
    
    printf("size of floorVerts: %3lu \n", sizeof(floorVerts)); // check the size of floorverts
    
    
    // create floor element array
    for (int i = 0; i < ((meshRes + 1) * (meshRes + 1)) - (meshRes + 1); i++) {
            floorElements[i * 2] = i;
            floorElements[i * 2 + 1] = i + (meshRes + 1);
            //cout << floorElements;
    }
    

    // SOME SUGGESTED TEST CODE: Can be used to examine contents of your arrays
    printf("floorVerts:\n");
    for (int k = 0; k < numFloorVerts; k++) {
        printf("k =%3d:  pos = %7.4f, %7.4f, %7.4f. \n", k, floorVerts[3 * k], floorVerts[3 * k + 1], floorVerts[3 * k + 2]);
    }
    printf("floorElements:\n");
    for (int k = 0; k < numFloorElts; k++) {
        printf("%d, ", floorElements[k]);
    }
    printf("\n");


    // Load data into the VBO and EBO using glBindBuffer and glBufferData commands
    // YOU NEED TO WRITE THIS CODE FOR THE PROJECT 4
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFloor]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*floorVerts) * sizeof(float), floorVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iFloor]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*floorElements) * sizeof(unsigned int), floorElements, GL_STATIC_DRAW);

    // The array should have been copied into the GPU buffers now.
    // If you use "new" above, you MUST delete the arrays here to avoid a memory leak.
    
    delete[] floorElements;
    delete[] floorVerts;
    
}

// ****
// MyRemeshCircularSurf: To be written for Project 4.
// ****
void MyRemeshCircularSurf()
{
    // WRITE THIS ENTIRE ROUTINE FOR THE CIRCULAR SURFACE
    // ALLOCATE MEMORY FOR ARRAYS, AND 
    // CALCULATE THE VERTEX DATA NEEDED FOR THE CIRCULAR SURFACE
    // THIS INCLUDES VERTEX POSITIONS AND NORMALS.
    // THEN LOAD THE DATA INTO THE VBO AND EBO BUFFERS
    // AND DELETE ANY TEMPORARILY ALLOCATED MEMORY.

}

// ****
// MyRenderFloor: To be written for Project 4. Renders the square ground plane.
//    This will loop, giving glDrawElements(...) commands. (Compare to RenderFloorDemo above.)
// ****
void MyRenderFloor()
{
    glBindVertexArray(myVAO[iFloor]);
    
    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    glVertexAttrib3f(vNormal_loc, 0.0, 1.0, 0.0);    // Generic vertex attribute: Normal is (0,1,0) for the floor.
    glVertexAttrib3f(vColor_loc, 1.0f, 0.4f, 0.4f);     // Generic vertex attribute: Color (light red) for the floor.
    viewMatrix.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    
    // Draw the four triangle strips
    /*
    glDrawElements(GL_TRIANGLE_STRIP, 30, GL_UNSIGNED_INT, (void*)0);                              // Draw first triangle strip (back strip)
    glDrawElements(GL_TRIANGLE_STRIP, 30, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));    // Draw second triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 30, GL_UNSIGNED_INT, (void*)(60 * sizeof(unsigned int)));    // Draw third triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 30, GL_UNSIGNED_INT, (void*)(90 * sizeof(unsigned int)));    // Draw fourth triangle strip (front strip)
    */
    
    int stripLen = (meshRes + 1) * 2; // define the strip length for easier sytax down the line
    
    for (int i = 0; i < meshRes; i++) {
        int stripLeni = stripLen * i;
        glDrawElements(GL_TRIANGLE_STRIP, stripLen, GL_UNSIGNED_INT, (void*)(stripLen * i * sizeof(unsigned int)));
    }
    
    
/*    int stripLen = (meshRes + 1) * 2;
    glDrawElements(GL_TRIANGLE_STRIP, stripLen, GL_UNSIGNED_INT, (void*)((meshRes + 1) * sizeof(unsigned int)));
    */
}

// ****
// MyRenderCircularSurf: To be written for Project 4. Renders the circular surface.
//    This will loop, giving glDrawElements(...) commands. (Compare to RenderCircularDemo above.)
// ****
void MyRenderCircularSurf()
{
    // Render the circular surface using calls to glDrawElements.
    // YOU MUST WRITE THIS FUNCTION FOR PROJECT 4.
}

