#version 430

layout(std140, binding=0) uniform CameraData {
    mat4 viewProjMatrix;
    mat4 invViewProjMatrix;
    vec3 position;
    vec3 direction;
} camera;

#define M_PI 3.1415926535897932384626433832795

vec3 getLightRadiance(vec3 n, vec3 diffuse, vec3 specular, float shininess, vec3 v, vec3 l) {
    float diffuseIntensity = max(dot(n, l), 0.);

    vec3 reflectDir = reflect(-l, n);
    float specularIntensity = pow(max(dot(v, reflectDir), 0.), shininess);

    return diffuseIntensity * diffuse + specularIntensity * specular;
}

// Based on https://www.shadertoy.com/view/Msf3WH
vec2 hash(vec2 p) {
    p = vec2( dot(p,vec2(127.1,311.7)),
    dot(p,vec2(269.5,183.3)) );
    return -1.0 + 2.0*fract(sin(p)*43758.5453123);
}

float simplexNoise(vec2 p) {
    const float K1 = 0.366025404; // (sqrt(3)-1)/2;
    const float K2 = 0.211324865; // (3-sqrt(3))/6;

    vec2 i = floor(p + (p.x+p.y)*K1);

    vec2 a = p - i + (i.x+i.y)*K2;
    vec2 o = step(a.yx,a.xy);
    vec2 b = a - o + K2;
    vec2 c = a - 1.0 + 2.0*K2;

    vec3 h = max( 0.5-vec3(dot(a,a), dot(b,b), dot(c,c) ), 0.0 );

    vec3 n = h*h*h*h*vec3(dot(a,hash(i+0.0)), dot(b,hash(i+o)), dot(c,hash(i+1.0)));

    return dot(n, vec3(70.0));
}

float fbm4(vec2 p) {
    mat2 m = mat2(1.6, 1.2, -1.2, 1.6);
    float f;
    f  = 0.5000 * simplexNoise(p); p = m * p;
    f += 0.2500 * simplexNoise(p); p = m * p;
    f += 0.1250 * simplexNoise(p); p = m * p;
    f += 0.0625 * simplexNoise(p); p = m * p;
    return f;
}

float heightMap(vec2 worldPos) {
    return (0.2 + fbm4(worldPos / 2000) * 0.5) * clamp((abs(worldPos.x) - 650)/2, 0, 2000) + min(0, (abs(worldPos.x) - 650));
}
