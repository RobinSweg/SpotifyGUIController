#version 100

// Set floats to 10 bits, required in opengles 
precision mediump float;

uniform vec4 uColour;

void main() {
    gl_FragColor = uColour;
}