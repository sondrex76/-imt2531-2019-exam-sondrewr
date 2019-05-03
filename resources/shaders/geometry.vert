layout(location=0) in vec3 vsPos;
layout(location=1) in vec3 vsNormal;
layout(location=2) in vec2 vsUv;

out vec3 fsPos;
out vec3 fsNormal;
out vec2 fsUv;

uniform mat4 modelMatrix;
uniform mat4 modelNormMatrix;

void main() {
    vec4 worldPos = modelMatrix * vec4(vsPos, 1.);

    fsPos = worldPos.xyz;
    fsNormal = normalize((modelNormMatrix * vec4(vsNormal, 0)).xyz);
    fsUv = vsUv;

    gl_Position = camera.viewProjMatrix * worldPos;
}
