attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

// will be passed from setUniformVec4()
uniform vec4 lazer_color; 

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
varying mediump float v_screenY;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
varying float v_screenY;
#endif

void main()
{
    float alpha = 1.0;
    if(CC_Random01[0] < 0.5)
        alpha = 0.0;

    float blueshade = 1.0;
    v_fragmentColor = lazer_color;//vec4(0.0, 0.5 * blueshade, blueshade, alpha);
    v_texCoord = a_texCoord;
    gl_Position = CC_MVPMatrix * a_position;
    v_screenY = gl_Position.y;
}