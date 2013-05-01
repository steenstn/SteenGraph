attribute vec3 coord3d;


void main(void) {

   gl_Position = gl_ModelViewProjectionMatrix *  vec4(coord3d, 1.0);
  // gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
   // pos = gl_ModelViewProjectionMatrix *  vec4(coord3d, 1.0);
    
	// vec4 theNormal = vec4(normal,1.0);
   // n= gl_NormalMatrix * theNormal.xyz;
	// //n = normalize(n);
	// vec4 theCotangent = vec4(cotangent,1.0);
	// ct= gl_NormalMatrix * (theCotangent.xyz);
	// ct = normalize(ct);
	
//	lightPos=vec3(0.0,0.0,0.0);
  // n = gl_Normal;
  // cP = (vec4(0.0,0.0,0.0,1.0)).xyz;
	// cP = (gl_ModelViewProjectionMatrix * vec4(0.0,0.0,1.0,1.0)).xyz;
   // cP =(gl_ModelViewProjectionMatrix *  vec4(coord3d, 1.0)).xyz*-1.0;
 // f_texCoord = texCoord;
}
