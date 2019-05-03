in vec2 vsTexPos;

uniform sampler2D inTex;
uniform vec2 viewportSize;

layout(location=0) out vec4 outTex;

#define FXAA_REDUCE_MIN 1. / 128.
#define FXAA_REDUCE_MUL 1. / 8.
#define FXAA_SPAN_MAX 8.

vec3 fxaa(vec2 fragCoord, vec2 rcpFrame) {
    vec3 rgbNW = texture(inTex, (fragCoord + vec2(-1., -1.)) * rcpFrame).xyz;
    vec3 rgbNE = texture(inTex, (fragCoord + vec2(1., -1.)) * rcpFrame).xyz;
    vec3 rgbSW = texture(inTex, (fragCoord + vec2(-1., 1.)) * rcpFrame).xyz;
    vec3 rgbSE = texture(inTex, (fragCoord + vec2(1., 1.)) * rcpFrame).xyz;
    vec3 rgbM = texture(inTex, fragCoord * rcpFrame).xyz;
    vec3 luma = vec3(0.299, 0.587, 0.114);
    float lumaNW = dot(rgbNW, luma);
    float lumaNE = dot(rgbNE, luma);
    float lumaSW = dot(rgbSW, luma);
    float lumaSE = dot(rgbSE, luma);
    float lumaM = dot(rgbM, luma);
    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    vec2 dir;
    dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
    dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));

    float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * FXAA_REDUCE_MUL), FXAA_REDUCE_MIN);
    float rcpDirMin = 1. / (min(abs(dir.x), abs(dir.y)) + dirReduce);
    dir = min(
        vec2(FXAA_SPAN_MAX, FXAA_SPAN_MAX),
        max(
            vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),
            dir * rcpDirMin
        )
    ) * rcpFrame;

    vec3 rgbA = 0.5 * (
        texture(inTex, fragCoord * rcpFrame + dir * (1. / 3. - 0.5)).xyz
        + texture(inTex, fragCoord * rcpFrame + dir * (2. / 3. - 0.5)).xyz
    );
    vec3 rgbB = rgbA * 0.5 + 0.25 * (
        texture(inTex, fragCoord * rcpFrame + dir * -0.5).xyz
        + texture(inTex, fragCoord * rcpFrame + dir * 0.5).xyz
    );

    float lumaB = dot(rgbB, luma);
    if ((lumaB < lumaMin) || (lumaB > lumaMax)) {
        return rgbA;
    } else {
        return rgbB;
    }
}

void main() {
    outTex = vec4(fxaa(vsTexPos * viewportSize, 1. / viewportSize), 1.);
}
