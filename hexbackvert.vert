#version 120
#extension GL_EXT_gpu_shader4 : enable
uniform float time = 0.00;
uniform float side_len = 130;
uniform vec2 offset = vec2(3.0, 3.0);
uniform float time_scale = 0.01;
uniform float pattern_quant = 4.0;
uniform vec2 TEXTURE_PIXEL_SIZE = vec2(30, 30);
uniform sampler2D texture;
uniform bool played = true;
uniform int currentLineHeight = 0;

vec3 palette(float t, vec3 a, vec3 b, vec3 c, vec3 d)
{
	return a + b*cos(6.28*(c*t*(1+currentLineHeight/4.0) + d));
}

vec2 closest_point_hex(vec2 pos, float a)
{
	float h = a*sqrt(3.0);
	float d1 = mod(pos.x, 1.5*a);
	float d2 = abs(1.5*a - mod(pos.x, 1.5*a));
	vec2 p1;
	p1.x = (2.0*pos.x - d1 + d2)/2.0;
	int n = int(p1.x/(1.5 * a));
	p1.y = float(n%2 == 0)*(pos.y - mod(pos.y, h)) + float(n%2 == 1)*(((pos.y - h/2.0) - mod((pos.y - h/2.0), h)) + h/2.0);
	vec2 p2 = vec2(p1.x, p1.y + h);
	vec2 p3 = vec2(p1.x - 1.5*a, (p1.y + p2.y)/2.0);
	vec2 p4 = vec2(p1.x + 1.5*a, p3.y);
	vec2 min1, min2;
	if (length(pos - p1) < length(pos - p2))
		min1 = p1;
	else
		min1 = p2;
	if (length(pos - p3) < length(pos - p4))
		min2 = p3;
	else
		min2 = p4;
	if (length(pos - min1) < length(pos - min2))
		return min1;
	return min2;
}

bool is_in_hexagon(vec2 point, vec2 centre, float a)
{
	vec2 s = point - centre;
	s = vec2(s.x*sign(s.x), s.y*sign(s.y));
	
	return s.y < a*sqrt(3.0)/2.0 && s.x < a*1.42265/2.0 + (s.y - a/2.0)*(-inversesqrt(3.0));
}

float rand(vec2 seed){
    return fract(sin(dot(seed.xy ,vec2(1.98,7.2))) * 758.54);
}

vec3 random_pattern(vec2 seed, vec2 pos)
{
	pos *= 4.0;
	seed = fract(seed*pattern_quant);
	float a = (2.0*3.14159264*rand(seed)) - 3.141592654;
	mat2 rot = mat2(vec2(cos(a), -sin(a)),
					vec2(sin(a), cos(a)));
	pos *= rot;
	float sc = 10.0*rand(seed) + 2.0;
	pos = floor(pos*sc);
	pos = pos - floor(pos/2.0)*2.0;
	return palette(0.61 + (pos.x + pos.y + seed.x + seed.y)/10.0, vec3(0.5), vec3(0.5), vec3(1.0), vec3(0.4, 0.3, 0.2));
}

void main()
{
	float a = side_len;
	vec2 UV = gl_FragCoord.xy;
	vec2 total_offset = offset + vec2(cos(time*time_scale), sin(time*time_scale));
	vec2 pos = UV + vec2(total_offset.x, total_offset.y);
	pos.x *= TEXTURE_PIXEL_SIZE.y/TEXTURE_PIXEL_SIZE.x;
	vec2 point = closest_point_hex(pos, a);
	gl_FragColor = vec4(vec3(1.0, 1.0, 1.0) - random_pattern(point, (pos - point)), 1.0);
	//COLOR = vec4(palette(floor(UV.x*100.0)/10.0, vec3(0.5), vec3(0.5), vec3(1.0), vec3(0.4, 0.3, 0.2)), 1.0);
	//bool is_border = is_in_hexagon(pos, point, side_len) && !is_in_hexagon(pos, point, side_len - border_width);
	//COLOR = vec4(float(is_border)*border_color + float(!is_border)*random_color(point));
}

