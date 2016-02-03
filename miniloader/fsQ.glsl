#version 410 core
#define M_PI 3.1415926535897932384626433832795

uniform vec2 mousePos;
uniform vec2 res;

// minX, maxX, minY, maxY
const vec4 grid = vec4(-2.4, 2.4, -1.5, 1.5);
// borne, nbIt
const vec2 param = vec2(8.0, 50.0);

out vec4 finalColor;

vec4	multQ(vec4 q1, vec4 q2)
{
	vec4 res;

	res.x   = q1.x*q2.x - dot( q1.yzw, q2.yzw );
	res.yzw = q1.x*q2.yzw + q2.x*q1.yzw + cross( q1.yzw, q2.yzw );
	return res;
}

vec4	sqQ(vec4 q)
{
   vec4 res;

   res.x   = q.x*q.x - dot( q.yzw, q.yzw );
   res.yzw = 2*q.x*q.yzw;
   return res;
}

void	iterate(inout vec4 z, inout vec4 zd, vec4 c)
{
   for (int i = 0 ; i < param.y ; i++)
   {
      zd = 2.0 * multQ(z, zd);
      z  = sqQ(z) + c;

      if ( dot(z, z) > param.x )
      {
         break;
      }
   }
}

float castRayQ(inout vec3 rO, inout vec3 rD, vec4 c, float epsilon)
{
   float dist = epsilon * 10;

   while (dist > epsilon)
   {
      vec4 z  = vec4( rO, 0 );         
      vec4 zd = vec4( 1, 0, 0, 0 );  

      iterate(z, zd, c);

      float normZ = length( z );
      dist = 0.5 * normZ * log( normZ ) / length( zd );
      rO += rD * dist; 
      if (dot(rO, rO) > 3)
         break;
   }
   return dist;
}

void main()
{
	vec3	eye = vec3(0., 0., 1.);
	vec3	up	= vec3(0., 1., 0.);
	vec3	look = vec3(0., 0., 0.);
	float	eps = 0.003;

	vec2 pos = 2.0 * ( gl_FragCoord.xy / res.xy ) - 1.0; // bound screen coords to [0, 1]
	// camera matrix
	vec3 ww = normalize( look - eye );
	vec3 uu = normalize( cross(ww, up) );
	vec3 vv = normalize( cross(uu, ww) );
	vec3 rd = normalize( pos.x*uu + pos.y*vv + 2.0*ww );
	
	vec4 c = vec4(-1.0, 0.2, 0, 0);

	float dist = castRayQ(eye, rd, c, eps);

	if (dist < eps)
	{
		float col = sqrt(dist);
		finalColor = vec4(1.0f - col, 0., 0., 1.0);	
	}
	finalColor = vec4(0.12, 0.12, 0.12, 1.0);
}
