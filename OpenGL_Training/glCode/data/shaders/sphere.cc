#version 120
#extension GL_EXT_geometry_shader4 : enable
varying vec3 normal;
uniform int res;
uniform float radius;

void main()
{
    float prevrad = 0;
    float prevz = 0;
    for ( int iv=0; iv<gl_VerticesIn; iv++ )
    {
	for ( int j=0; j<=res; j++ ) 
	{
	    float anglv = float(j) * 2 * 3.14159 / float(res);
	    float currad = cos( anglv ) * radius;
	    float curz = sin( anglv ) * radius;
	    for ( int i=0; i<=res; i++ )
	    {
		float anglh = float(i) * 2.0 * 3.14159 / float(res); 
		if ( j!= 0 )
		{
		    vec4 prevpos = vec4( prevrad*cos(anglh), prevrad*sin(anglh), prevz, 1 );
		    gl_Position = gl_PositionIn[iv] + prevpos;
		    EmitVertex();
    		    
		    vec4 curpos = vec4( currad*cos(anglh), currad*sin(anglh), curz, 1  );
		    gl_Position = gl_PositionIn[iv] + curpos;
		    EmitVertex();
		}
	    }

	    prevrad = currad;
	    prevz = curz;
	}
	EndPrimitive();
    }
}
