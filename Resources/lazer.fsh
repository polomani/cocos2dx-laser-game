#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
varying mediump vec2 v_screenY;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
varying float v_screenY;
#endif

void main()
{
    vec4 texColor = v_fragmentColor;// * step(0.0, 1.0 - length(v_texCoord));;
    if(texColor.a < 0.2)
        discard;

    if(mod(v_screenY + CC_SinTime[1], 0.005) > 0.0025)
        discard;

    gl_FragColor = vec4(texColor.xyz, 0.2);
}