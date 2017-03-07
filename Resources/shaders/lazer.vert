attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

// will be passed from setUniformVec4()
uniform vec4 lazer_color; 

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
#else
varying vec4 v_fragmentColor;
#endif

void main()
{
    v_fragmentColor = lazer_color;
    gl_Position = CC_MVPMatrix * a_position;
}