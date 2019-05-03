in vec3 fsPos;
in vec3 fsNormal;
in vec2 fsUv;

layout(location=0) out vec4 outAlbedoMetallic;
layout(location=1) out vec4 outNormalRoughness;
layout(location=2) out vec4 outEmissive;
layout(location=3) out vec4 outWorldPos;

uniform sampler2D albedoMap;
//uniform sampler2D normalMap; // todo: normal mapping
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D emissiveMap;

uniform vec3 extraEmissive;

void main() {
    vec3 albedoColor = texture(albedoMap, fsUv).rgb;
    float metallic = texture(metallicMap, fsUv).x;
    float roughness = texture(roughnessMap, fsUv).x;
    vec3 emissive = texture(emissiveMap, fsUv).rgb;

    outAlbedoMetallic = vec4(albedoColor, metallic);
    outNormalRoughness = vec4(fsNormal, 1. - roughness);
    outEmissive = vec4(emissive + extraEmissive, 1);
    outWorldPos = vec4(fsPos, length(camera.position.xyz - fsPos));
}
