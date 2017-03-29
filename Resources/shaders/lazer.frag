#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
#else
varying vec4 v_fragmentColor;
#endif

void main()
{
    //if(mod(CC_SinTime[1], 0.005) > 0.003)
    //    discard;

    gl_FragColor = vec4(v_fragmentColor.xyz, 1);
}