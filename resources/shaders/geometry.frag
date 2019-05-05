in vec3 fsPos;
in vec3 fsNormal;
in vec2 fsUv;

layout(location=0) out vec4 outDiffuseShininess;
layout(location=1) out vec4 outSpecular;
layout(location=2) out vec4 outEmissive;
layout(location=3) out vec4 outNormal;
layout(location=4) out vec4 outWorldPos;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2D shininessMap;
uniform sampler2D emissiveMap;

uniform vec3 extraEmissive;

void main() {
    vec4 diffuseColor = texture(diffuseMap, fsUv);
    vec3 specularColor = texture(specularMap, fsUv).rgb;
    float shininess = texture(shininessMap, fsUv).x;
    vec3 emissiveColor = texture(emissiveMap,  fsUv).rgb + extraEmissive;
	
	if (diffuseColor.a < 0.1) {
		discard;
	}

	outDiffuseShininess = vec4(diffuseColor.rgb, shininess);
    outSpecular = vec4(specularColor, 0.);
    outEmissive = vec4(emissiveColor, 1.);
    outNormal = vec4(fsNormal, 0.);
    outWorldPos = vec4(fsPos, length(camera.position.xyz - fsPos));
}
