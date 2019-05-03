in vec3 fsPos;

layout(location=0) out vec4 outAlbedoMetallic;
layout(location=1) out vec4 outNormalRoughness;
layout(location=2) out vec4 outEmissive;
layout(location=3) out vec4 outWorldPos;

void main() {
    outAlbedoMetallic = vec4(0.);
    outNormalRoughness = vec4(0.);
    outEmissive = vec4(1., 1., 0., 1.);
    outWorldPos = vec4(fsPos, length(camera.position.xyz - fsPos));
}
