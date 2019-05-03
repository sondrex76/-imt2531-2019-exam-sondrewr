layout(location=0) in vec3 vsPos;

out vec3 fsPos;

uniform mat4 invLightMatrix;

void main() {
    vec4 worldPos = invLightMatrix * vec4(vsPos, 1.);
    worldPos /= worldPos.w;
    fsPos = worldPos.xyz;

    gl_Position = camera.viewProjMatrix * worldPos;
}
