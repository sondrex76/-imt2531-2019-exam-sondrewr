layout(location=0) in vec2 vsPos;

out vec2 vsTexPos;

void main() {
    gl_Position = vec4(vsPos * 2. - 1., 0, 1);
    vsTexPos = vsPos;
}
