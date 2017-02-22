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
    vec4 texColor = v_fragmentColor;
    if(mod(CC_SinTime[1], 0.005) > 0.002)
        discard;

    gl_FragColor = vec4(texColor.xyz, 1);
}